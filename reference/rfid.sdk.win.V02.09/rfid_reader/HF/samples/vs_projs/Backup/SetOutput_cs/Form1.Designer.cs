namespace SetOutput_cs
{
    partial class Form1
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
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.cmbCommuncateType = new System.Windows.Forms.ComboBox();
            this.label35 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.textPort = new System.Windows.Forms.TextBox();
            this.label34 = new System.Windows.Forms.Label();
            this.textIp = new System.Windows.Forms.TextBox();
            this.label33 = new System.Windows.Forms.Label();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cmbFrame = new System.Windows.Forms.ComboBox();
            this.cmbBaud = new System.Windows.Forms.ComboBox();
            this.cmbComName = new System.Windows.Forms.ComboBox();
            this.cmbDevType = new System.Windows.Forms.ComboBox();
            this.label29 = new System.Windows.Forms.Label();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnOpen = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label16 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.btnSetOutput = new System.Windows.Forms.Button();
            this.textStopTime = new System.Windows.Forms.TextBox();
            this.cmbFrequency = new System.Windows.Forms.ComboBox();
            this.textActTime = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.checkedListOutput = new System.Windows.Forms.CheckedListBox();
            this.groupBox4.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.cmbCommuncateType);
            this.groupBox4.Controls.Add(this.label35);
            this.groupBox4.Controls.Add(this.groupBox9);
            this.groupBox4.Controls.Add(this.groupBox7);
            this.groupBox4.Controls.Add(this.cmbDevType);
            this.groupBox4.Controls.Add(this.label29);
            this.groupBox4.Controls.Add(this.btnClose);
            this.groupBox4.Controls.Add(this.btnOpen);
            this.groupBox4.Location = new System.Drawing.Point(12, 12);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(486, 200);
            this.groupBox4.TabIndex = 43;
            this.groupBox4.TabStop = false;
            // 
            // cmbCommuncateType
            // 
            this.cmbCommuncateType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbCommuncateType.FormattingEnabled = true;
            this.cmbCommuncateType.Location = new System.Drawing.Point(135, 42);
            this.cmbCommuncateType.Name = "cmbCommuncateType";
            this.cmbCommuncateType.Size = new System.Drawing.Size(100, 20);
            this.cmbCommuncateType.TabIndex = 46;
            this.cmbCommuncateType.SelectedIndexChanged += new System.EventHandler(this.cmbCommuncateType_SelectedIndexChanged);
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(14, 45);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(119, 12);
            this.label35.TabIndex = 45;
            this.label35.Text = "Communication type:";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.textPort);
            this.groupBox9.Controls.Add(this.label34);
            this.groupBox9.Controls.Add(this.textIp);
            this.groupBox9.Controls.Add(this.label33);
            this.groupBox9.Location = new System.Drawing.Point(250, 73);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(192, 94);
            this.groupBox9.TabIndex = 44;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "TCP Option";
            // 
            // textPort
            // 
            this.textPort.Enabled = false;
            this.textPort.Location = new System.Drawing.Point(84, 56);
            this.textPort.Name = "textPort";
            this.textPort.Size = new System.Drawing.Size(56, 21);
            this.textPort.TabIndex = 3;
            this.textPort.Text = "9909";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(35, 60);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(35, 12);
            this.label34.TabIndex = 2;
            this.label34.Text = "Port:";
            // 
            // textIp
            // 
            this.textIp.Enabled = false;
            this.textIp.Location = new System.Drawing.Point(84, 20);
            this.textIp.Name = "textIp";
            this.textIp.Size = new System.Drawing.Size(95, 21);
            this.textIp.TabIndex = 1;
            this.textIp.Text = "192.168.0.222";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(20, 24);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(53, 12);
            this.label33.TabIndex = 0;
            this.label33.Text = "IP Addr:";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label3);
            this.groupBox7.Controls.Add(this.label2);
            this.groupBox7.Controls.Add(this.label1);
            this.groupBox7.Controls.Add(this.cmbFrame);
            this.groupBox7.Controls.Add(this.cmbBaud);
            this.groupBox7.Controls.Add(this.cmbComName);
            this.groupBox7.Location = new System.Drawing.Point(12, 73);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(183, 110);
            this.groupBox7.TabIndex = 42;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Serial interface";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 39;
            this.label3.Text = "Frame:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 39;
            this.label2.Text = "Baud:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 39;
            this.label1.Text = "COM name:";
            // 
            // cmbFrame
            // 
            this.cmbFrame.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbFrame.FormattingEnabled = true;
            this.cmbFrame.Items.AddRange(new object[] {
            "8E1",
            "8N1",
            "8O1"});
            this.cmbFrame.Location = new System.Drawing.Point(77, 72);
            this.cmbFrame.Name = "cmbFrame";
            this.cmbFrame.Size = new System.Drawing.Size(93, 20);
            this.cmbFrame.TabIndex = 38;
            // 
            // cmbBaud
            // 
            this.cmbBaud.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBaud.FormattingEnabled = true;
            this.cmbBaud.Items.AddRange(new object[] {
            "9600",
            "38400",
            "57600",
            "115200"});
            this.cmbBaud.Location = new System.Drawing.Point(77, 46);
            this.cmbBaud.Name = "cmbBaud";
            this.cmbBaud.Size = new System.Drawing.Size(93, 20);
            this.cmbBaud.TabIndex = 38;
            // 
            // cmbComName
            // 
            this.cmbComName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbComName.FormattingEnabled = true;
            this.cmbComName.Location = new System.Drawing.Point(77, 20);
            this.cmbComName.Name = "cmbComName";
            this.cmbComName.Size = new System.Drawing.Size(93, 20);
            this.cmbComName.TabIndex = 38;
            // 
            // cmbDevType
            // 
            this.cmbDevType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbDevType.FormattingEnabled = true;
            this.cmbDevType.Location = new System.Drawing.Point(135, 17);
            this.cmbDevType.Name = "cmbDevType";
            this.cmbDevType.Size = new System.Drawing.Size(101, 20);
            this.cmbDevType.TabIndex = 41;
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(13, 19);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(77, 12);
            this.label29.TabIndex = 40;
            this.label29.Text = "Reader Type:";
            // 
            // btnClose
            // 
            this.btnClose.Enabled = false;
            this.btnClose.Location = new System.Drawing.Point(382, 26);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(87, 27);
            this.btnClose.TabIndex = 2;
            this.btnClose.Text = "close reader";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(281, 25);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(87, 27);
            this.btnOpen.TabIndex = 1;
            this.btnOpen.Text = "open reader";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Controls.Add(this.label15);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.btnSetOutput);
            this.groupBox1.Controls.Add(this.textStopTime);
            this.groupBox1.Controls.Add(this.cmbFrequency);
            this.groupBox1.Controls.Add(this.textActTime);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.checkedListOutput);
            this.groupBox1.Location = new System.Drawing.Point(12, 236);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(511, 183);
            this.groupBox1.TabIndex = 44;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "GPIO output";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(377, 104);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(47, 12);
            this.label16.TabIndex = 11;
            this.label16.Text = "* 100ms";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(389, 53);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(47, 12);
            this.label15.TabIndex = 10;
            this.label15.Text = "* 100ms";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.label14.Location = new System.Drawing.Point(135, 17);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(347, 12);
            this.label14.TabIndex = 9;
            this.label14.Text = "Note:Pause duration will be Effective only when number >1";
            // 
            // btnSetOutput
            // 
            this.btnSetOutput.Enabled = false;
            this.btnSetOutput.Location = new System.Drawing.Point(268, 138);
            this.btnSetOutput.Name = "btnSetOutput";
            this.btnSetOutput.Size = new System.Drawing.Size(92, 31);
            this.btnSetOutput.TabIndex = 8;
            this.btnSetOutput.Text = "Set Output";
            this.btnSetOutput.UseVisualStyleBackColor = true;
            this.btnSetOutput.Click += new System.EventHandler(this.btnSetOutput_Click);
            // 
            // textStopTime
            // 
            this.textStopTime.Location = new System.Drawing.Point(280, 102);
            this.textStopTime.Name = "textStopTime";
            this.textStopTime.Size = new System.Drawing.Size(92, 21);
            this.textStopTime.TabIndex = 7;
            this.textStopTime.Text = "1";
            // 
            // cmbFrequency
            // 
            this.cmbFrequency.FormattingEnabled = true;
            this.cmbFrequency.Location = new System.Drawing.Point(280, 76);
            this.cmbFrequency.Name = "cmbFrequency";
            this.cmbFrequency.Size = new System.Drawing.Size(93, 20);
            this.cmbFrequency.TabIndex = 6;
            // 
            // textActTime
            // 
            this.textActTime.Location = new System.Drawing.Point(280, 49);
            this.textActTime.Name = "textActTime";
            this.textActTime.Size = new System.Drawing.Size(92, 21);
            this.textActTime.TabIndex = 5;
            this.textActTime.Text = "1";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(204, 104);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(65, 12);
            this.label13.TabIndex = 4;
            this.label13.Text = "Stop time:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(204, 79);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(65, 12);
            this.label12.TabIndex = 3;
            this.label12.Text = "Frequency:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(204, 52);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 12);
            this.label11.TabIndex = 2;
            this.label11.Text = "Active time:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(20, 30);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(83, 12);
            this.label10.TabIndex = 1;
            this.label10.Text = "Warning Port:";
            // 
            // checkedListOutput
            // 
            this.checkedListOutput.FormattingEnabled = true;
            this.checkedListOutput.Location = new System.Drawing.Point(17, 49);
            this.checkedListOutput.Name = "checkedListOutput";
            this.checkedListOutput.Size = new System.Drawing.Size(131, 116);
            this.checkedListOutput.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(560, 449);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox4);
            this.Name = "Form1";
            this.Text = "Set Output";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ComboBox cmbCommuncateType;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.TextBox textPort;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.TextBox textIp;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cmbComName;
        private System.Windows.Forms.ComboBox cmbDevType;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cmbFrame;
        private System.Windows.Forms.ComboBox cmbBaud;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button btnSetOutput;
        private System.Windows.Forms.TextBox textStopTime;
        private System.Windows.Forms.ComboBox cmbFrequency;
        private System.Windows.Forms.TextBox textActTime;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckedListBox checkedListOutput;
    }
}

