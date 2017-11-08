namespace EncodingConverter
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.resultListView = new System.Windows.Forms.ListView();
            this.pathHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.oldEncodingHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.oldLineEndingHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.actionHeader = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.pathTextBox = new System.Windows.Forms.TextBox();
            this.browseBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.subdirCheck = new System.Windows.Forms.CheckBox();
            this.analyzeBtn = new System.Windows.Forms.Button();
            this.convertBtn = new System.Windows.Forms.Button();
            this.encodingSelector = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.filterTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lineEndingSelector = new System.Windows.Forms.ComboBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this._srcEncodingDefault = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // resultListView
            // 
            this.resultListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.pathHeader,
            this.oldEncodingHeader,
            this.oldLineEndingHeader,
            this.actionHeader});
            this.resultListView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.resultListView.Location = new System.Drawing.Point(8, 178);
            this.resultListView.Margin = new System.Windows.Forms.Padding(8);
            this.resultListView.Name = "resultListView";
            this.resultListView.Size = new System.Drawing.Size(697, 284);
            this.resultListView.TabIndex = 0;
            this.resultListView.UseCompatibleStateImageBehavior = false;
            this.resultListView.View = System.Windows.Forms.View.Details;
            // 
            // pathHeader
            // 
            this.pathHeader.Text = "文件名";
            this.pathHeader.Width = 557;
            // 
            // oldEncodingHeader
            // 
            this.oldEncodingHeader.Text = "代码编码";
            this.oldEncodingHeader.Width = 150;
            // 
            // oldLineEndingHeader
            // 
            this.oldLineEndingHeader.Text = "旧行尾";
            this.oldLineEndingHeader.Width = 100;
            // 
            // actionHeader
            // 
            this.actionHeader.Text = "结果";
            this.actionHeader.Width = 100;
            // 
            // pathTextBox
            // 
            this.pathTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pathTextBox.Location = new System.Drawing.Point(103, 2);
            this.pathTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pathTextBox.Name = "pathTextBox";
            this.pathTextBox.Size = new System.Drawing.Size(439, 21);
            this.pathTextBox.TabIndex = 1;
            this.pathTextBox.TextChanged += new System.EventHandler(this.pathTextBox_TextChanged);
            // 
            // browseBtn
            // 
            this.browseBtn.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.browseBtn.Location = new System.Drawing.Point(576, 3);
            this.browseBtn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.browseBtn.Name = "browseBtn";
            this.browseBtn.Size = new System.Drawing.Size(100, 22);
            this.browseBtn.TabIndex = 2;
            this.browseBtn.Text = "选择目录";
            this.browseBtn.UseVisualStyleBackColor = true;
            this.browseBtn.Click += new System.EventHandler(this.browseBtn_Click);
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(56, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "源文件";
            // 
            // subdirCheck
            // 
            this.subdirCheck.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.subdirCheck.AutoSize = true;
            this.subdirCheck.Checked = true;
            this.subdirCheck.CheckState = System.Windows.Forms.CheckState.Checked;
            this.subdirCheck.Location = new System.Drawing.Point(548, 34);
            this.subdirCheck.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.subdirCheck.Name = "subdirCheck";
            this.subdirCheck.Size = new System.Drawing.Size(84, 16);
            this.subdirCheck.TabIndex = 4;
            this.subdirCheck.Text = "包含子目录";
            this.subdirCheck.UseVisualStyleBackColor = true;
            this.subdirCheck.CheckedChanged += new System.EventHandler(this.subdirCheck_CheckedChanged);
            // 
            // analyzeBtn
            // 
            this.analyzeBtn.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.analyzeBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.analyzeBtn.ForeColor = System.Drawing.Color.Black;
            this.analyzeBtn.Location = new System.Drawing.Point(576, 94);
            this.analyzeBtn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.analyzeBtn.Name = "analyzeBtn";
            this.analyzeBtn.Size = new System.Drawing.Size(100, 27);
            this.analyzeBtn.TabIndex = 5;
            this.analyzeBtn.Text = "扫描目录";
            this.analyzeBtn.UseVisualStyleBackColor = true;
            this.analyzeBtn.Click += new System.EventHandler(this.analyzeBtn_Click);
            // 
            // convertBtn
            // 
            this.convertBtn.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.convertBtn.Enabled = false;
            this.convertBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.convertBtn.ForeColor = System.Drawing.Color.Red;
            this.convertBtn.Location = new System.Drawing.Point(576, 132);
            this.convertBtn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.convertBtn.Name = "convertBtn";
            this.convertBtn.Size = new System.Drawing.Size(100, 24);
            this.convertBtn.TabIndex = 6;
            this.convertBtn.Text = "开始处理";
            this.convertBtn.UseVisualStyleBackColor = true;
            this.convertBtn.Click += new System.EventHandler(this.convertBtn_Click);
            // 
            // encodingSelector
            // 
            this.encodingSelector.FormattingEnabled = true;
            this.encodingSelector.Location = new System.Drawing.Point(103, 68);
            this.encodingSelector.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.encodingSelector.Name = "encodingSelector";
            this.encodingSelector.Size = new System.Drawing.Size(138, 20);
            this.encodingSelector.TabIndex = 7;
            this.encodingSelector.SelectedIndexChanged += new System.EventHandler(this.encodingSelector_Changed);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(44, 73);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "输出类型";
            // 
            // filterTextBox
            // 
            this.filterTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.filterTextBox.Location = new System.Drawing.Point(103, 30);
            this.filterTextBox.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.filterTextBox.Name = "filterTextBox";
            this.filterTextBox.Size = new System.Drawing.Size(439, 21);
            this.filterTextBox.TabIndex = 9;
            this.filterTextBox.Text = "*.txt|*.cpp|*.hpp|*.c|*.h|*.inl|*.inc|*.asm|*.cs|*.glsl|*.hlsl";
            this.filterTextBox.TextChanged += new System.EventHandler(this.filterTextBox_TextChanged);
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(56, 36);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 10;
            this.label3.Text = "扩展名";
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(68, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 13;
            this.label4.Text = "行尾";
            // 
            // lineEndingSelector
            // 
            this.lineEndingSelector.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.lineEndingSelector.FormattingEnabled = true;
            this.lineEndingSelector.Location = new System.Drawing.Point(103, 97);
            this.lineEndingSelector.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.lineEndingSelector.Name = "lineEndingSelector";
            this.lineEndingSelector.Size = new System.Drawing.Size(138, 20);
            this.lineEndingSelector.TabIndex = 12;
            this.lineEndingSelector.SelectedIndexChanged += new System.EventHandler(this.lineEndingSelector_Changed);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel2.ColumnCount = 4;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 76.87188F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 23.12812F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 21F));
            this.tableLayoutPanel2.Controls.Add(this._srcEncodingDefault, 0, 6);
            this.tableLayoutPanel2.Controls.Add(this.label5, 0, 6);
            this.tableLayoutPanel2.Controls.Add(this.subdirCheck, 2, 1);
            this.tableLayoutPanel2.Controls.Add(this.convertBtn, 2, 6);
            this.tableLayoutPanel2.Controls.Add(this.filterTextBox, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.label3, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.browseBtn, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.pathTextBox, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.label2, 0, 3);
            this.tableLayoutPanel2.Controls.Add(this.encodingSelector, 1, 3);
            this.tableLayoutPanel2.Controls.Add(this.label4, 0, 4);
            this.tableLayoutPanel2.Controls.Add(this.lineEndingSelector, 1, 4);
            this.tableLayoutPanel2.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.analyzeBtn, 2, 4);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(6, 6);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(6);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 7;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 10F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 7F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(701, 158);
            this.tableLayoutPanel2.TabIndex = 15;
            // 
            // _srcEncodingDefault
            // 
            this._srcEncodingDefault.DisplayMember = "EncodingName";
            this._srcEncodingDefault.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this._srcEncodingDefault.FormattingEnabled = true;
            this._srcEncodingDefault.Location = new System.Drawing.Point(103, 133);
            this._srcEncodingDefault.Name = "_srcEncodingDefault";
            this._srcEncodingDefault.Size = new System.Drawing.Size(240, 20);
            this._srcEncodingDefault.Sorted = true;
            this._srcEncodingDefault.TabIndex = 15;
            this._srcEncodingDefault.SelectedIndexChanged += new System.EventHandler(this._srcEncodingDefault_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 138);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(89, 12);
            this.label5.TabIndex = 14;
            this.label5.Text = "源文件默认编码";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.resultListView, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(2);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 170F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(713, 470);
            this.tableLayoutPanel1.TabIndex = 16;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(713, 470);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MinimumSize = new System.Drawing.Size(500, 279);
            this.Name = "Form1";
            this.Text = "文本文件编码转换";
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView resultListView;
        private System.Windows.Forms.ColumnHeader pathHeader;
        private System.Windows.Forms.ColumnHeader oldEncodingHeader;
        private System.Windows.Forms.ColumnHeader actionHeader;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.TextBox pathTextBox;
        private System.Windows.Forms.Button browseBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox subdirCheck;
        private System.Windows.Forms.Button analyzeBtn;
        private System.Windows.Forms.Button convertBtn;
        private System.Windows.Forms.ComboBox encodingSelector;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox filterTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ColumnHeader oldLineEndingHeader;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox lineEndingSelector;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox _srcEncodingDefault;
    }
}

