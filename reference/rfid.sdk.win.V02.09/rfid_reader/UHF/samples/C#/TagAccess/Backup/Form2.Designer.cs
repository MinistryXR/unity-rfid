namespace WindowsApplication2
{
    partial class Form2
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.ckbSelEnable = new System.Windows.Forms.CheckBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label15 = new System.Windows.Forms.Label();
            this.txbSelMaskBits = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.cbbSelMaskBitsLen = new System.Windows.Forms.ComboBox();
            this.cbbSelPointer = new System.Windows.Forms.ComboBox();
            this.cbbSelMemBank = new System.Windows.Forms.ComboBox();
            this.cbbSelAction = new System.Windows.Forms.ComboBox();
            this.cbbSelTarget = new System.Windows.Forms.ComboBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.ckbMetaEnable = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ckbMetaTagData = new System.Windows.Forms.CheckBox();
            this.ckbMetaReadCnt = new System.Windows.Forms.CheckBox();
            this.ckbMetaRSS = new System.Windows.Forms.CheckBox();
            this.ckbMetaFrequency = new System.Windows.Forms.CheckBox();
            this.ckbMetaTimestamp = new System.Windows.Forms.CheckBox();
            this.ckbMetaAntennaID = new System.Windows.Forms.CheckBox();
            this.ckbMetaEPC = new System.Windows.Forms.CheckBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.cbbReadWordCnt = new System.Windows.Forms.ComboBox();
            this.ckbReadEnable = new System.Windows.Forms.CheckBox();
            this.cbbReadWordPtr = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cbbReadMemBank = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPageWrite = new System.Windows.Forms.TabPage();
            this.label19 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.txbWriteDatas = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cbbWriteWordCnt = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.ckbWriteEnable = new System.Windows.Forms.CheckBox();
            this.cbbWriteMemBank = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cbbWriteWordPtr = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPageLock = new System.Windows.Forms.TabPage();
            this.ckbLockEnable = new System.Windows.Forms.CheckBox();
            this.ckbLockKillPwd = new System.Windows.Forms.CheckBox();
            this.ckbLockAccessPwd = new System.Windows.Forms.CheckBox();
            this.ckbLockEPCMem = new System.Windows.Forms.CheckBox();
            this.ckbLockTIDMem = new System.Windows.Forms.CheckBox();
            this.ckbLockUserMem = new System.Windows.Forms.CheckBox();
            this.cbbLockKillPwd = new System.Windows.Forms.ComboBox();
            this.cbbLockAccessPwd = new System.Windows.Forms.ComboBox();
            this.cbbLockEPCMem = new System.Windows.Forms.ComboBox();
            this.cbbLockTIDMem = new System.Windows.Forms.ComboBox();
            this.cbbLockUserMem = new System.Windows.Forms.ComboBox();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.label17 = new System.Windows.Forms.Label();
            this.txbAccessPwd = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.txbTimeout = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.tabPageWrite.SuspendLayout();
            this.tabPageLock.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.tabPage6.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(167, 369);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(67, 25);
            this.button1.TabIndex = 2;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(281, 369);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(67, 25);
            this.button2.TabIndex = 3;
            this.button2.Text = "Cancel";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.Controls.Add(this.tabPage6);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(611, 351);
            this.tabControl1.TabIndex = 5;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.ckbSelEnable);
            this.tabPage1.Controls.Add(this.groupBox2);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(603, 325);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Selection";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // ckbSelEnable
            // 
            this.ckbSelEnable.AutoSize = true;
            this.ckbSelEnable.Location = new System.Drawing.Point(22, 16);
            this.ckbSelEnable.Name = "ckbSelEnable";
            this.ckbSelEnable.Size = new System.Drawing.Size(60, 16);
            this.ckbSelEnable.TabIndex = 13;
            this.ckbSelEnable.Text = "Enable";
            this.ckbSelEnable.UseVisualStyleBackColor = true;
            this.ckbSelEnable.CheckedChanged += new System.EventHandler(this.checkBox8_CheckedChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label15);
            this.groupBox2.Controls.Add(this.txbSelMaskBits);
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.cbbSelMaskBitsLen);
            this.groupBox2.Controls.Add(this.cbbSelPointer);
            this.groupBox2.Controls.Add(this.cbbSelMemBank);
            this.groupBox2.Controls.Add(this.cbbSelAction);
            this.groupBox2.Controls.Add(this.cbbSelTarget);
            this.groupBox2.Controls.Add(this.label14);
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Location = new System.Drawing.Point(18, 38);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(527, 185);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(429, 160);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(23, 12);
            this.label15.TabIndex = 12;
            this.label15.Text = "Hex";
            // 
            // txbSelMaskBits
            // 
            this.txbSelMaskBits.Location = new System.Drawing.Point(73, 156);
            this.txbSelMaskBits.Name = "txbSelMaskBits";
            this.txbSelMaskBits.Size = new System.Drawing.Size(342, 21);
            this.txbSelMaskBits.TabIndex = 11;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(2, 130);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(107, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "Mask Bits Length:";
            // 
            // cbbSelMaskBitsLen
            // 
            this.cbbSelMaskBitsLen.FormattingEnabled = true;
            this.cbbSelMaskBitsLen.Location = new System.Drawing.Point(116, 127);
            this.cbbSelMaskBitsLen.Name = "cbbSelMaskBitsLen";
            this.cbbSelMaskBitsLen.Size = new System.Drawing.Size(84, 20);
            this.cbbSelMaskBitsLen.TabIndex = 10;
            // 
            // cbbSelPointer
            // 
            this.cbbSelPointer.FormattingEnabled = true;
            this.cbbSelPointer.Location = new System.Drawing.Point(116, 96);
            this.cbbSelPointer.Name = "cbbSelPointer";
            this.cbbSelPointer.Size = new System.Drawing.Size(84, 20);
            this.cbbSelPointer.TabIndex = 9;
            // 
            // cbbSelMemBank
            // 
            this.cbbSelMemBank.FormattingEnabled = true;
            this.cbbSelMemBank.Items.AddRange(new object[] {
            "00: RFU",
            "01: EPC",
            "02: TID",
            "03: User"});
            this.cbbSelMemBank.Location = new System.Drawing.Point(116, 67);
            this.cbbSelMemBank.Name = "cbbSelMemBank";
            this.cbbSelMemBank.Size = new System.Drawing.Size(84, 20);
            this.cbbSelMemBank.TabIndex = 8;
            // 
            // cbbSelAction
            // 
            this.cbbSelAction.FormattingEnabled = true;
            this.cbbSelAction.Items.AddRange(new object[] {
            "00: assert SL or inventoried → A deassert SL or inventoried → B",
            "01: assert SL or inventoried → A do nothing",
            "02: do nothing deassert SL or inventoried → B",
            "03: negate SL or (A → B, B → A) do nothing",
            "04: deassert SL or inventoried → B assert SL or inventoried → A",
            "05: deassert SL or inventoried → B do nothing",
            "06: do nothing assert SL or inventoried → A",
            "07: do nothing negate SL or (A → B, B → A)"});
            this.cbbSelAction.Location = new System.Drawing.Point(116, 37);
            this.cbbSelAction.Name = "cbbSelAction";
            this.cbbSelAction.Size = new System.Drawing.Size(219, 20);
            this.cbbSelAction.TabIndex = 7;
            // 
            // cbbSelTarget
            // 
            this.cbbSelTarget.FormattingEnabled = true;
            this.cbbSelTarget.Items.AddRange(new object[] {
            "00: Inventoried (S0)",
            "01: Inventoried (S1)",
            "02: Inventoried (S2)",
            "03: Inventoried (S3)",
            "04: SL"});
            this.cbbSelTarget.Location = new System.Drawing.Point(116, 11);
            this.cbbSelTarget.Name = "cbbSelTarget";
            this.cbbSelTarget.Size = new System.Drawing.Size(219, 20);
            this.cbbSelTarget.TabIndex = 6;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(2, 160);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(65, 12);
            this.label14.TabIndex = 5;
            this.label14.Text = "Mask Bits:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(5, 99);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(77, 12);
            this.label12.TabIndex = 3;
            this.label12.Text = "Bit Pointer:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(8, 70);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(59, 12);
            this.label11.TabIndex = 2;
            this.label11.Text = "Mem Bank:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(20, 38);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 12);
            this.label10.TabIndex = 1;
            this.label10.Text = "Action:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(20, 11);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "Target:";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.ckbMetaEnable);
            this.tabPage2.Controls.Add(this.groupBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(603, 325);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Meta flags";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // ckbMetaEnable
            // 
            this.ckbMetaEnable.AutoSize = true;
            this.ckbMetaEnable.Location = new System.Drawing.Point(28, 23);
            this.ckbMetaEnable.Name = "ckbMetaEnable";
            this.ckbMetaEnable.Size = new System.Drawing.Size(60, 16);
            this.ckbMetaEnable.TabIndex = 8;
            this.ckbMetaEnable.Text = "Enable";
            this.ckbMetaEnable.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.ckbMetaTagData);
            this.groupBox1.Controls.Add(this.ckbMetaReadCnt);
            this.groupBox1.Controls.Add(this.ckbMetaRSS);
            this.groupBox1.Controls.Add(this.ckbMetaFrequency);
            this.groupBox1.Controls.Add(this.ckbMetaTimestamp);
            this.groupBox1.Controls.Add(this.ckbMetaAntennaID);
            this.groupBox1.Controls.Add(this.ckbMetaEPC);
            this.groupBox1.Location = new System.Drawing.Point(28, 45);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(304, 202);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            // 
            // ckbMetaTagData
            // 
            this.ckbMetaTagData.AutoSize = true;
            this.ckbMetaTagData.Location = new System.Drawing.Point(11, 169);
            this.ckbMetaTagData.Name = "ckbMetaTagData";
            this.ckbMetaTagData.Size = new System.Drawing.Size(72, 16);
            this.ckbMetaTagData.TabIndex = 7;
            this.ckbMetaTagData.Text = "Tag data";
            this.ckbMetaTagData.UseVisualStyleBackColor = true;
            // 
            // ckbMetaReadCnt
            // 
            this.ckbMetaReadCnt.AutoSize = true;
            this.ckbMetaReadCnt.Location = new System.Drawing.Point(11, 147);
            this.ckbMetaReadCnt.Name = "ckbMetaReadCnt";
            this.ckbMetaReadCnt.Size = new System.Drawing.Size(84, 16);
            this.ckbMetaReadCnt.TabIndex = 6;
            this.ckbMetaReadCnt.Text = "Read Count";
            this.ckbMetaReadCnt.UseVisualStyleBackColor = true;
            // 
            // ckbMetaRSS
            // 
            this.ckbMetaRSS.AutoSize = true;
            this.ckbMetaRSS.Location = new System.Drawing.Point(11, 125);
            this.ckbMetaRSS.Name = "ckbMetaRSS";
            this.ckbMetaRSS.Size = new System.Drawing.Size(48, 16);
            this.ckbMetaRSS.TabIndex = 4;
            this.ckbMetaRSS.Text = "RSSI";
            this.ckbMetaRSS.UseVisualStyleBackColor = true;
            // 
            // ckbMetaFrequency
            // 
            this.ckbMetaFrequency.AutoSize = true;
            this.ckbMetaFrequency.Location = new System.Drawing.Point(11, 103);
            this.ckbMetaFrequency.Name = "ckbMetaFrequency";
            this.ckbMetaFrequency.Size = new System.Drawing.Size(78, 16);
            this.ckbMetaFrequency.TabIndex = 3;
            this.ckbMetaFrequency.Text = "Frequency";
            this.ckbMetaFrequency.UseVisualStyleBackColor = true;
            // 
            // ckbMetaTimestamp
            // 
            this.ckbMetaTimestamp.AutoSize = true;
            this.ckbMetaTimestamp.Location = new System.Drawing.Point(11, 81);
            this.ckbMetaTimestamp.Name = "ckbMetaTimestamp";
            this.ckbMetaTimestamp.Size = new System.Drawing.Size(78, 16);
            this.ckbMetaTimestamp.TabIndex = 2;
            this.ckbMetaTimestamp.Text = "Timestamp";
            this.ckbMetaTimestamp.UseVisualStyleBackColor = true;
            // 
            // ckbMetaAntennaID
            // 
            this.ckbMetaAntennaID.AutoSize = true;
            this.ckbMetaAntennaID.Location = new System.Drawing.Point(11, 59);
            this.ckbMetaAntennaID.Name = "ckbMetaAntennaID";
            this.ckbMetaAntennaID.Size = new System.Drawing.Size(84, 16);
            this.ckbMetaAntennaID.TabIndex = 1;
            this.ckbMetaAntennaID.Text = "Antenna ID";
            this.ckbMetaAntennaID.UseVisualStyleBackColor = true;
            // 
            // ckbMetaEPC
            // 
            this.ckbMetaEPC.AutoSize = true;
            this.ckbMetaEPC.Checked = true;
            this.ckbMetaEPC.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ckbMetaEPC.Location = new System.Drawing.Point(11, 37);
            this.ckbMetaEPC.Name = "ckbMetaEPC";
            this.ckbMetaEPC.Size = new System.Drawing.Size(42, 16);
            this.ckbMetaEPC.TabIndex = 0;
            this.ckbMetaEPC.Text = "EPC";
            this.ckbMetaEPC.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.cbbReadWordCnt);
            this.tabPage3.Controls.Add(this.ckbReadEnable);
            this.tabPage3.Controls.Add(this.cbbReadWordPtr);
            this.tabPage3.Controls.Add(this.label5);
            this.tabPage3.Controls.Add(this.cbbReadMemBank);
            this.tabPage3.Controls.Add(this.label7);
            this.tabPage3.Controls.Add(this.label6);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(603, 325);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Inventory read";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // cbbReadWordCnt
            // 
            this.cbbReadWordCnt.FormattingEnabled = true;
            this.cbbReadWordCnt.Location = new System.Drawing.Point(110, 133);
            this.cbbReadWordCnt.Name = "cbbReadWordCnt";
            this.cbbReadWordCnt.Size = new System.Drawing.Size(90, 20);
            this.cbbReadWordCnt.TabIndex = 13;
            // 
            // ckbReadEnable
            // 
            this.ckbReadEnable.AutoSize = true;
            this.ckbReadEnable.Location = new System.Drawing.Point(110, 22);
            this.ckbReadEnable.Name = "ckbReadEnable";
            this.ckbReadEnable.Size = new System.Drawing.Size(60, 16);
            this.ckbReadEnable.TabIndex = 10;
            this.ckbReadEnable.Text = "Enable";
            this.ckbReadEnable.UseVisualStyleBackColor = true;
            // 
            // cbbReadWordPtr
            // 
            this.cbbReadWordPtr.FormattingEnabled = true;
            this.cbbReadWordPtr.Location = new System.Drawing.Point(110, 94);
            this.cbbReadWordPtr.Name = "cbbReadWordPtr";
            this.cbbReadWordPtr.Size = new System.Drawing.Size(90, 20);
            this.cbbReadWordPtr.TabIndex = 11;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(32, 134);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "Word Count:";
            // 
            // cbbReadMemBank
            // 
            this.cbbReadMemBank.FormattingEnabled = true;
            this.cbbReadMemBank.Items.AddRange(new object[] {
            "00: RFU",
            "01: EPC",
            "02: TID",
            "03: Use"});
            this.cbbReadMemBank.Location = new System.Drawing.Point(110, 59);
            this.cbbReadMemBank.Name = "cbbReadMemBank";
            this.cbbReadMemBank.Size = new System.Drawing.Size(90, 20);
            this.cbbReadMemBank.TabIndex = 9;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(45, 62);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 8;
            this.label7.Text = "Mem Bank:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(21, 97);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(83, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "Word Pointer:";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.tabControl2);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(603, 325);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Embedded commands";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPageWrite);
            this.tabControl2.Controls.Add(this.tabPageLock);
            this.tabControl2.Location = new System.Drawing.Point(6, 6);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(591, 323);
            this.tabControl2.TabIndex = 11;
            // 
            // tabPageWrite
            // 
            this.tabPageWrite.Controls.Add(this.label19);
            this.tabPageWrite.Controls.Add(this.label16);
            this.tabPageWrite.Controls.Add(this.txbWriteDatas);
            this.tabPageWrite.Controls.Add(this.label4);
            this.tabPageWrite.Controls.Add(this.cbbWriteWordCnt);
            this.tabPageWrite.Controls.Add(this.label3);
            this.tabPageWrite.Controls.Add(this.ckbWriteEnable);
            this.tabPageWrite.Controls.Add(this.cbbWriteMemBank);
            this.tabPageWrite.Controls.Add(this.label1);
            this.tabPageWrite.Controls.Add(this.cbbWriteWordPtr);
            this.tabPageWrite.Controls.Add(this.label2);
            this.tabPageWrite.Location = new System.Drawing.Point(4, 22);
            this.tabPageWrite.Name = "tabPageWrite";
            this.tabPageWrite.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageWrite.Size = new System.Drawing.Size(583, 297);
            this.tabPageWrite.TabIndex = 0;
            this.tabPageWrite.Text = "Write command";
            this.tabPageWrite.UseVisualStyleBackColor = true;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(221, 109);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(347, 12);
            this.label19.TabIndex = 17;
            this.label19.Text = "Note: the word pointer of EPC memory must be started at 2";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(478, 145);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(23, 12);
            this.label16.TabIndex = 16;
            this.label16.Text = "Hex";
            // 
            // txbWriteDatas
            // 
            this.txbWriteDatas.Location = new System.Drawing.Point(120, 144);
            this.txbWriteDatas.Name = "txbWriteDatas";
            this.txbWriteDatas.Size = new System.Drawing.Size(348, 21);
            this.txbWriteDatas.TabIndex = 15;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(48, 145);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 14;
            this.label4.Text = "Datas:";
            // 
            // cbbWriteWordCnt
            // 
            this.cbbWriteWordCnt.FormattingEnabled = true;
            this.cbbWriteWordCnt.Location = new System.Drawing.Point(121, 105);
            this.cbbWriteWordCnt.Name = "cbbWriteWordCnt";
            this.cbbWriteWordCnt.Size = new System.Drawing.Size(90, 20);
            this.cbbWriteWordCnt.TabIndex = 13;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(22, 108);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 12);
            this.label3.TabIndex = 12;
            this.label3.Text = "Word Count:";
            // 
            // ckbWriteEnable
            // 
            this.ckbWriteEnable.AutoSize = true;
            this.ckbWriteEnable.Location = new System.Drawing.Point(121, 17);
            this.ckbWriteEnable.Name = "ckbWriteEnable";
            this.ckbWriteEnable.Size = new System.Drawing.Size(60, 16);
            this.ckbWriteEnable.TabIndex = 1;
            this.ckbWriteEnable.Text = "Enable";
            this.ckbWriteEnable.UseVisualStyleBackColor = true;
            // 
            // cbbWriteMemBank
            // 
            this.cbbWriteMemBank.FormattingEnabled = true;
            this.cbbWriteMemBank.Items.AddRange(new object[] {
            "00: RFU",
            "01: EPC",
            "02: TID",
            "03: User"});
            this.cbbWriteMemBank.Location = new System.Drawing.Point(120, 39);
            this.cbbWriteMemBank.Name = "cbbWriteMemBank";
            this.cbbWriteMemBank.Size = new System.Drawing.Size(90, 20);
            this.cbbWriteMemBank.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(36, 42);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "Mem Bank:";
            // 
            // cbbWriteWordPtr
            // 
            this.cbbWriteWordPtr.FormattingEnabled = true;
            this.cbbWriteWordPtr.Location = new System.Drawing.Point(121, 70);
            this.cbbWriteWordPtr.Name = "cbbWriteWordPtr";
            this.cbbWriteWordPtr.Size = new System.Drawing.Size(90, 20);
            this.cbbWriteWordPtr.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(22, 73);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "Word Pointer:";
            // 
            // tabPageLock
            // 
            this.tabPageLock.Controls.Add(this.ckbLockEnable);
            this.tabPageLock.Controls.Add(this.ckbLockKillPwd);
            this.tabPageLock.Controls.Add(this.ckbLockAccessPwd);
            this.tabPageLock.Controls.Add(this.ckbLockEPCMem);
            this.tabPageLock.Controls.Add(this.ckbLockTIDMem);
            this.tabPageLock.Controls.Add(this.ckbLockUserMem);
            this.tabPageLock.Controls.Add(this.cbbLockKillPwd);
            this.tabPageLock.Controls.Add(this.cbbLockAccessPwd);
            this.tabPageLock.Controls.Add(this.cbbLockEPCMem);
            this.tabPageLock.Controls.Add(this.cbbLockTIDMem);
            this.tabPageLock.Controls.Add(this.cbbLockUserMem);
            this.tabPageLock.Location = new System.Drawing.Point(4, 22);
            this.tabPageLock.Name = "tabPageLock";
            this.tabPageLock.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageLock.Size = new System.Drawing.Size(583, 297);
            this.tabPageLock.TabIndex = 1;
            this.tabPageLock.Text = "Lock command";
            this.tabPageLock.UseVisualStyleBackColor = true;
            // 
            // ckbLockEnable
            // 
            this.ckbLockEnable.AutoSize = true;
            this.ckbLockEnable.Location = new System.Drawing.Point(93, 5);
            this.ckbLockEnable.Name = "ckbLockEnable";
            this.ckbLockEnable.Size = new System.Drawing.Size(60, 16);
            this.ckbLockEnable.TabIndex = 22;
            this.ckbLockEnable.Text = "Enable";
            this.ckbLockEnable.UseVisualStyleBackColor = true;
            // 
            // ckbLockKillPwd
            // 
            this.ckbLockKillPwd.AutoSize = true;
            this.ckbLockKillPwd.Location = new System.Drawing.Point(7, 175);
            this.ckbLockKillPwd.Name = "ckbLockKillPwd";
            this.ckbLockKillPwd.Size = new System.Drawing.Size(72, 16);
            this.ckbLockKillPwd.TabIndex = 21;
            this.ckbLockKillPwd.Text = "Kill Pwd";
            this.ckbLockKillPwd.UseVisualStyleBackColor = true;
            // 
            // ckbLockAccessPwd
            // 
            this.ckbLockAccessPwd.AutoSize = true;
            this.ckbLockAccessPwd.Location = new System.Drawing.Point(6, 142);
            this.ckbLockAccessPwd.Name = "ckbLockAccessPwd";
            this.ckbLockAccessPwd.Size = new System.Drawing.Size(84, 16);
            this.ckbLockAccessPwd.TabIndex = 20;
            this.ckbLockAccessPwd.Text = "Access Pwd";
            this.ckbLockAccessPwd.UseVisualStyleBackColor = true;
            // 
            // ckbLockEPCMem
            // 
            this.ckbLockEPCMem.AutoSize = true;
            this.ckbLockEPCMem.Location = new System.Drawing.Point(6, 106);
            this.ckbLockEPCMem.Name = "ckbLockEPCMem";
            this.ckbLockEPCMem.Size = new System.Drawing.Size(66, 16);
            this.ckbLockEPCMem.TabIndex = 19;
            this.ckbLockEPCMem.Text = "EPC Mem";
            this.ckbLockEPCMem.UseVisualStyleBackColor = true;
            // 
            // ckbLockTIDMem
            // 
            this.ckbLockTIDMem.AutoSize = true;
            this.ckbLockTIDMem.Location = new System.Drawing.Point(6, 67);
            this.ckbLockTIDMem.Name = "ckbLockTIDMem";
            this.ckbLockTIDMem.Size = new System.Drawing.Size(66, 16);
            this.ckbLockTIDMem.TabIndex = 18;
            this.ckbLockTIDMem.Text = "TID Mem";
            this.ckbLockTIDMem.UseVisualStyleBackColor = true;
            // 
            // ckbLockUserMem
            // 
            this.ckbLockUserMem.AutoSize = true;
            this.ckbLockUserMem.Location = new System.Drawing.Point(7, 31);
            this.ckbLockUserMem.Name = "ckbLockUserMem";
            this.ckbLockUserMem.Size = new System.Drawing.Size(72, 16);
            this.ckbLockUserMem.TabIndex = 17;
            this.ckbLockUserMem.Text = "User Mem";
            this.ckbLockUserMem.UseVisualStyleBackColor = true;
            // 
            // cbbLockKillPwd
            // 
            this.cbbLockKillPwd.FormattingEnabled = true;
            this.cbbLockKillPwd.Items.AddRange(new object[] {
            "00:readable and writeable from either the open or secured states",
            "01:permanently readable and writeable from either the open or secured states and " +
                "may never be locked",
            "02:readable and writeable from the secured state but not from the open state",
            "03:not readable or writeable from any state"});
            this.cbbLockKillPwd.Location = new System.Drawing.Point(93, 170);
            this.cbbLockKillPwd.Name = "cbbLockKillPwd";
            this.cbbLockKillPwd.Size = new System.Drawing.Size(484, 20);
            this.cbbLockKillPwd.TabIndex = 16;
            // 
            // cbbLockAccessPwd
            // 
            this.cbbLockAccessPwd.FormattingEnabled = true;
            this.cbbLockAccessPwd.Items.AddRange(new object[] {
            "00:readable and writeable from either the open or secured states",
            "01:permanently readable and writeable from either the open or secured states and " +
                "may never be locked",
            "02:readable and writeable from the secured state but not from the open state",
            "03:not readable or writeable from any state"});
            this.cbbLockAccessPwd.Location = new System.Drawing.Point(93, 139);
            this.cbbLockAccessPwd.Name = "cbbLockAccessPwd";
            this.cbbLockAccessPwd.Size = new System.Drawing.Size(484, 20);
            this.cbbLockAccessPwd.TabIndex = 14;
            this.cbbLockAccessPwd.SelectedIndexChanged += new System.EventHandler(this.comboBox4_SelectedIndexChanged);
            // 
            // cbbLockEPCMem
            // 
            this.cbbLockEPCMem.FormattingEnabled = true;
            this.cbbLockEPCMem.Items.AddRange(new object[] {
            "00:writeable from either the open or secured states",
            "01:permanently writeable from either the open or secured states and may never be " +
                "locked",
            "02:writeable from the secured state but not from the open state",
            "03:not writeable from any state"});
            this.cbbLockEPCMem.Location = new System.Drawing.Point(93, 102);
            this.cbbLockEPCMem.Name = "cbbLockEPCMem";
            this.cbbLockEPCMem.Size = new System.Drawing.Size(484, 20);
            this.cbbLockEPCMem.TabIndex = 12;
            // 
            // cbbLockTIDMem
            // 
            this.cbbLockTIDMem.FormattingEnabled = true;
            this.cbbLockTIDMem.Items.AddRange(new object[] {
            "00:writeable from either the open or secured states",
            "01:permanently writeable from either the open or secured states and may never be " +
                "locked",
            "02:writeable from the secured state but not from the open state",
            "03:not writeable from any state"});
            this.cbbLockTIDMem.Location = new System.Drawing.Point(93, 63);
            this.cbbLockTIDMem.Name = "cbbLockTIDMem";
            this.cbbLockTIDMem.Size = new System.Drawing.Size(484, 20);
            this.cbbLockTIDMem.TabIndex = 10;
            // 
            // cbbLockUserMem
            // 
            this.cbbLockUserMem.FormattingEnabled = true;
            this.cbbLockUserMem.Items.AddRange(new object[] {
            "00:writeable from either the open or secured states",
            "01:permanently writeable from either the open or secured states and may never be " +
                "locked",
            "02:writeable from the secured state but not from the open state",
            "03:not writeable from any state"});
            this.cbbLockUserMem.Location = new System.Drawing.Point(93, 27);
            this.cbbLockUserMem.Name = "cbbLockUserMem";
            this.cbbLockUserMem.Size = new System.Drawing.Size(484, 20);
            this.cbbLockUserMem.TabIndex = 7;
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.label17);
            this.tabPage5.Controls.Add(this.txbAccessPwd);
            this.tabPage5.Controls.Add(this.label8);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage5.Size = new System.Drawing.Size(603, 325);
            this.tabPage5.TabIndex = 4;
            this.tabPage5.Text = "Access password";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(223, 98);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(23, 12);
            this.label17.TabIndex = 2;
            this.label17.Text = "Hex";
            // 
            // txbAccessPwd
            // 
            this.txbAccessPwd.Location = new System.Drawing.Point(130, 95);
            this.txbAccessPwd.Name = "txbAccessPwd";
            this.txbAccessPwd.Size = new System.Drawing.Size(77, 21);
            this.txbAccessPwd.TabIndex = 1;
            this.txbAccessPwd.Text = "00000000";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(33, 98);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(101, 12);
            this.label8.TabIndex = 0;
            this.label8.Text = "Access password:";
            // 
            // tabPage6
            // 
            this.tabPage6.Controls.Add(this.txbTimeout);
            this.tabPage6.Controls.Add(this.label18);
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(603, 325);
            this.tabPage6.TabIndex = 5;
            this.tabPage6.Text = "Timeout";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // txbTimeout
            // 
            this.txbTimeout.Location = new System.Drawing.Point(119, 78);
            this.txbTimeout.Name = "txbTimeout";
            this.txbTimeout.Size = new System.Drawing.Size(99, 21);
            this.txbTimeout.TabIndex = 1;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(64, 81);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(53, 12);
            this.label18.TabIndex = 0;
            this.label18.Text = "Timeout:";
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(638, 405);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "Form2";
            this.Text = "Setting";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabControl2.ResumeLayout(false);
            this.tabPageWrite.ResumeLayout(false);
            this.tabPageWrite.PerformLayout();
            this.tabPageLock.ResumeLayout(false);
            this.tabPageLock.PerformLayout();
            this.tabPage5.ResumeLayout(false);
            this.tabPage5.PerformLayout();
            this.tabPage6.ResumeLayout(false);
            this.tabPage6.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.CheckBox ckbMetaEPC;
        private System.Windows.Forms.ComboBox cbbReadWordCnt;
        private System.Windows.Forms.CheckBox ckbReadEnable;
        private System.Windows.Forms.ComboBox cbbReadWordPtr;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cbbReadMemBank;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox ckbMetaEnable;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox ckbMetaTagData;
        private System.Windows.Forms.CheckBox ckbMetaReadCnt;
        private System.Windows.Forms.CheckBox ckbMetaRSS;
        private System.Windows.Forms.CheckBox ckbMetaFrequency;
        private System.Windows.Forms.CheckBox ckbMetaTimestamp;
        private System.Windows.Forms.CheckBox ckbMetaAntennaID;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TextBox txbAccessPwd;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txbSelMaskBits;
        private System.Windows.Forms.ComboBox cbbSelMaskBitsLen;
        private System.Windows.Forms.ComboBox cbbSelPointer;
        private System.Windows.Forms.ComboBox cbbSelMemBank;
        private System.Windows.Forms.ComboBox cbbSelAction;
        private System.Windows.Forms.ComboBox cbbSelTarget;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.CheckBox ckbSelEnable;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.TextBox txbTimeout;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPageWrite;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox txbWriteDatas;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cbbWriteWordCnt;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox ckbWriteEnable;
        private System.Windows.Forms.ComboBox cbbWriteMemBank;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbbWriteWordPtr;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabPage tabPageLock;
        private System.Windows.Forms.ComboBox cbbLockUserMem;
        private System.Windows.Forms.ComboBox cbbLockAccessPwd;
        private System.Windows.Forms.ComboBox cbbLockEPCMem;
        private System.Windows.Forms.ComboBox cbbLockTIDMem;
        private System.Windows.Forms.ComboBox cbbLockKillPwd;
        private System.Windows.Forms.CheckBox ckbLockKillPwd;
        private System.Windows.Forms.CheckBox ckbLockAccessPwd;
        private System.Windows.Forms.CheckBox ckbLockEPCMem;
        private System.Windows.Forms.CheckBox ckbLockTIDMem;
        private System.Windows.Forms.CheckBox ckbLockUserMem;
        private System.Windows.Forms.CheckBox ckbLockEnable;
    }
}