using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Linq;
using System.Collections.Generic;

namespace EncodingConverter
{
    public enum LineEnding {LF, CRLF, CR, Mixed_CR_CRLF, Mixed_CR_LF, Mixed_CRLF_LF, Mixed_All, None};

    public enum ConvertResult { OK, Skip, CannotReadFile, CannotWriteFile, UnknownEncoding };

    public struct ConvertCommand
    {
        public ConvertCommand(string filepath, Encoding enc, LineEnding endg, bool dontConvertEndings)
        {
            path = filepath;
            newEncoding = enc;
            newLineEnding = endg;
            dontTouchEndings = dontConvertEndings;
        }

        public string path;
        public Encoding newEncoding;
        public LineEnding newLineEnding;
        bool dontTouchEndings;
    }

    public delegate void AddToActionListDelegate(string filename, string oldEncodingName, string oldLineEndingName, ConvertResult action);
    public delegate void AddToResultListDelegate(ConvertCommand cmd, ConvertResult result);

    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

        public static string AboutProgram = "Описание:\nПриложение для преобразования кодировок текстовых файлов.\n"+
                "Для получения подробной информации о консольном интерфейсе запустите с параметрами -nogui -help.\n"+
                "Версия: 1.0 beta\nПлатформа: .NET Framework 3.5\nЛицензия: MIT\n\n"+
                "Автор:\nВольнов Александр (gammaker)\n\nЕсли вам понравилась эта программа,\n"+
                "пожалуйста, пожертвуйте\nЯндекс.Деньги: https://money.yandex.ru/to/410011926720740";

        public static string HelpCLI = "-help\n Показывает эту информацию.\n\n"+
            "-nogui\nЗапустить без графического интерфейса.\n\n"+
            "-dir=\"path/to/directory\"\nЗадаёт директорию для сканирования или конвертирования.\n\n"+
            "-not-recursive\nНе сканировать подпапки.\n\n"+
            "-convert\nНе только анализировать, но и запустить конверсию всех найденных файлов.\n\n"+
            "-filter=\"*.ext1|*.ext2|...\"\nЗадаёт маску для отбора найденных файлов по имени или расширению.\n\n"+
            "-encoding=\"Target encoding name\"\nЗадаёт название кодировки, в которую будут преобразовываться все найденные файлы.\n"+
                "Если параметр отсутствует, кодировки не преобразуются.\nПоддерживаемые кодировки: {0}\n\n"+
            "-line-ending={CR, LF, CRLF}\nУказать, как преобразовывать конец строки. Если параметр отсутствует, конец строки не преобразуется.\n\n"+
            "-output-level={0,1,2,3}\n0 - ничего не выводить.\n1 - вывести только ошибки.\n2 - вывести общую информацию.\n"+
            "3 - вывести список файлов , при обработке которых произошла ошибка.\n4 - вывести список всех обработанных файлов.";

        static Encoding input_UTF8_no_BOM = new UTF8Encoding(encoderShouldEmitUTF8Identifier: false, throwOnInvalidBytes: true);
        //static Encoding input_CP1251 = Encoding.GetEncoding(1251, new EncoderExceptionFallback(), new DecoderExceptionFallback());
        static Encoding input_CP1251 = Encoding.Default;// Encoding.GetEncoding("GB2312", new EncoderExceptionFallback(), new DecoderExceptionFallback());

        static string[] endings = new string[] {"\n", "\r\n", "\r"};
        public static string[] lineEndingNames = new string[]
        {
            "Unix (LF)", "Windows (CRLF)", "CR",
            "CR + CRLF", "CR + LF", "CRLF + LF", "CR + CRLF + LF", "None"
        };


        public static string[] encodingNames = new string[]
        {
            "UTF-8 (no BOM)",
            "UTF-8 BOM",
            "UTF-16 LE",
            "UTF-16 BE",
            "UTF-32 LE",
            "UTF-32 BE",
            "GB2312"/*,
            "KOI8-R",
            "KOI8-U"*/
        };

        static Encoding[] encodings = new Encoding[]
        {
            new UTF8Encoding(encoderShouldEmitUTF8Identifier: false, throwOnInvalidBytes: true),
            Encoding.UTF8,
            Encoding.Unicode,
            Encoding.BigEndianUnicode,
            Encoding.UTF32,
            new UTF32Encoding(true, true),
            Encoding.GetEncoding("GB2312", new EncoderReplacementFallback("?"), new DecoderReplacementFallback("?"))/*,
            Encoding.GetEncoding(20866, new EncoderReplacementFallback("?"), new DecoderReplacementFallback("?")),
            Encoding.GetEncoding(21866, new EncoderReplacementFallback("?"), new DecoderReplacementFallback("?"))*/
        };

        internal static void SetSrcEncodingDefault(Encoding _en)
        {
            input_CP1251=_en;
            inputEncodings.SetValue(_en, 1);
            inputEncodingNames.SetValue(_en.EncodingName, 1);
        }

        public static Encoding[] inputEncodings = new Encoding[] {input_UTF8_no_BOM, input_CP1251};
        public static string[] inputEncodingNames = new string[] {encodingNames[0], encodingNames[6]};

        public static Encoding GetEncodingByName(string name)
        {
            for (int i = 0; i < encodingNames.Length; i++)
                if (encodingNames[i]==name) return encodings[i];
            return null;
        }

        public static string GetEncodingName(Encoding enc)
        {
            for (int i = 0; i < encodings.Length; i++)
                if (encodings[i]==enc) return encodingNames[i];
            return null;
        }

        public static LineEnding GetLineEndingByName(string name)
        {
            for (int i = 0; i < lineEndingNames.Length; i++)
                if (lineEndingNames[i]==name) return (LineEnding)i;
            return LineEnding.None;
        }

        public static string GetLineEndingName(LineEnding le)
        {
            return lineEndingNames[(int)le];
        }

        public static LineEnding DetermineLineEnding(string str)
        {
            bool hasCRLF = str.Contains("\r\n");
            string temp = hasCRLF? str.Replace("\r\n", " "): str;
            bool hasCR = temp.Contains("\r");
            bool hasLF = temp.Contains("\n");
            if(hasCRLF && hasCR && hasLF) return LineEnding.Mixed_All;
            if(hasCRLF && hasCR) return LineEnding.Mixed_CR_CRLF;
            if(hasCRLF && hasLF) return LineEnding.Mixed_CRLF_LF;
            if(hasCR && hasLF) return LineEnding.Mixed_CR_LF;
            if(hasCRLF) return LineEnding.CRLF;
            if(hasCR) return LineEnding.CR;
            if(hasLF) return LineEnding.LF;
            return LineEnding.None;
        }

        static Regex newline_pattern = new Regex(@"\r\n|\r|\n", RegexOptions.Compiled);
        public static string ReplaceLineEndings(string str, LineEnding ending)
        {
            return newline_pattern.Replace(str, endings[(int)ending]);
        }

        public static string DecodeString(byte[] bytes, out string oldEncodingName)
        {
            bool isASCII = true;

            foreach(byte b in bytes)
            {
                if (b < 128) continue;
                isASCII = false;
                break;
            }

            if(isASCII)
            {
                oldEncodingName = "ASCII";
                return Encoding.ASCII.GetString(bytes);
            }

            if (bytes.Length >= 3 && bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF)
            {
                oldEncodingName = "UTF-8 BOM";
                return Encoding.UTF8.GetString(bytes, 3, bytes.Length - 3);
            }

            if (bytes.Length >= 4 && bytes[0] == 0xFF && bytes[1] == 0xFE && bytes[2] == 0 && bytes[3] == 0)
            {
                oldEncodingName = "UTF-32 LE";
                return Encoding.UTF32.GetString(bytes, 4, bytes.Length - 4);
            }

            if (bytes.Length >= 4 && bytes[0] == 0 && bytes[1] == 0 && bytes[2] == 0xFE && bytes[3] == 0xFF)
            {
                oldEncodingName = "UTF-32 BE";
                return new UTF32Encoding(true, false).GetString(bytes, 4, bytes.Length-4);
            }

            if(bytes.Length>=2 && bytes[0]==0xFF && bytes[1]==0xFE)
            {
                oldEncodingName = "UTF-16 LE";
                return Encoding.Unicode.GetString(bytes, 2, bytes.Length-2);
            }

            if (bytes.Length >= 2 && bytes[0] == 0xFE && bytes[1] == 0xFF)
            {
                oldEncodingName = "UTF-16 BE";
                return Encoding.BigEndianUnicode.GetString(bytes, 2, bytes.Length-2);
            }

            for(int i=0; i<inputEncodings.Count(); i++)
            {
                var enc = inputEncodings[i];
                string text;
                try { text=enc.GetString(bytes); }
                catch(Exception) { continue; }
                oldEncodingName = inputEncodingNames[i];
                return text;
            }

            oldEncodingName = "Unknown";
            return null;
        }

        public static void AnalyzeFile(string filename, out string oldEncodingName, out LineEnding oldEnding)
        {
            var bytes = File.ReadAllBytes(filename);
            string text = DecodeString(bytes, out oldEncodingName);
            oldEnding = DetermineLineEnding(text);
        }

        public static void ConvertFile(string filename, Encoding newEncoding, LineEnding newLineEnding)
        {
            var bytes = File.ReadAllBytes(filename);
            string oldEncodingName;
            string text = DecodeString(bytes, out oldEncodingName);
            if(newLineEnding!=LineEnding.None) text = ReplaceLineEndings(text, newLineEnding);
            File.WriteAllText(filename, text, newEncoding);
        }

        

        

        

        static public List<ConvertCommand> RunAnalyzeProcess(string path, string filters,
            bool recursive, Encoding newEncoding, LineEnding newLineEnding, AddToActionListDelegate addToActionList)
        {
            var searchOption = recursive? SearchOption.AllDirectories: SearchOption.TopDirectoryOnly;
            var files = filters.Split('|').SelectMany(filter => Directory.GetFiles(path, filter, searchOption));
            List<ConvertCommand> result = new List<ConvertCommand>(files.Count());
            foreach(var file in files)
            {
                string oldEncodingName = "Unknown";
                LineEnding oldEnding = LineEnding.None;
                ConvertResult action = ConvertResult.OK;
                try
                {
                    AnalyzeFile(file, out oldEncodingName, out oldEnding);
                    if(oldEncodingName == "Unknown") action = ConvertResult.UnknownEncoding;
                }
                catch(IOException) {action = ConvertResult.CannotReadFile;}
                catch(UnauthorizedAccessException) {action = ConvertResult.CannotReadFile;}

                if(GetEncodingByName(oldEncodingName) != newEncoding ||
                    oldEnding != newLineEnding && oldEnding!=LineEnding.None && newLineEnding!=LineEnding.None)
                {
                    result.Add( new ConvertCommand(file, newEncoding, newLineEnding==LineEnding.None? oldEnding: newLineEnding, newLineEnding==LineEnding.None) );
                }
                else action = ConvertResult.Skip;
                
                if(addToActionList!=null) addToActionList(file, oldEncodingName, GetLineEndingName(oldEnding), action);
            }
            return result;
        }

        static public void RunConvertProcess(List<ConvertCommand> commands, AddToResultListDelegate addToResultList)
        {
            foreach(var cmd in commands)
            {
                ConvertResult res = ConvertResult.OK;
                try
                {
                    ConvertFile(cmd.path, cmd.newEncoding, cmd.newLineEnding);
                }
                catch(IOException) {res = ConvertResult.CannotWriteFile;}
                catch(UnauthorizedAccessException) {res = ConvertResult.CannotWriteFile;}
                if(addToResultList!=null) addToResultList(cmd, res);
            }
        }
    }
}
