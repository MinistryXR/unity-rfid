namespace WindowsApplication2
{
    partial class AccessTypeTailBlock
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
            this.listView1 = new System.Windows.Forms.ListView();
            this.Type = new System.Windows.Forms.ColumnHeader();
            this.KeyARead = new System.Windows.Forms.ColumnHeader();
            this.KeyAWrite = new System.Windows.Forms.ColumnHeader();
            this.AccessCtrR = new System.Windows.Forms.ColumnHeader();
            this.AccessCtrW = new System.Windows.Forms.ColumnHeader();
            this.KeyBRead = new System.Windows.Forms.ColumnHeader();
            this.KeyBWrite = new System.Windows.Forms.ColumnHeader();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Type,
            this.KeyARead,
            this.KeyAWrite,
            this.AccessCtrR,
            this.AccessCtrW,
            this.KeyBRead,
            this.KeyBWrite});
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(12, 12);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(679, 284);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            // 
            // Type
            // 
            this.Type.Text = "类型";
            this.Type.Width = 57;
            // 
            // KeyARead
            // 
            this.KeyARead.Text = "密钥A(读)";
            this.KeyARead.Width = 83;
            // 
            // KeyAWrite
            // 
            this.KeyAWrite.Text = "密钥A（写）";
            this.KeyAWrite.Width = 71;
            // 
            // AccessCtrR
            // 
            this.AccessCtrR.Text = "存取条件（读）";
            this.AccessCtrR.Width = 126;
            // 
            // AccessCtrW
            // 
            this.AccessCtrW.Text = "存取条件（写）";
            this.AccessCtrW.Width = 113;
            // 
            // KeyBRead
            // 
            this.KeyBRead.Text = "密钥B（读）";
            this.KeyBRead.Width = 82;
            // 
            // KeyBWrite
            // 
            this.KeyBWrite.Text = "密钥B（写）";
            this.KeyBWrite.Width = 129;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(442, 313);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(101, 35);
            this.button1.TabIndex = 1;
            this.button1.Text = "确定";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(189, 313);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(98, 35);
            this.button2.TabIndex = 2;
            this.button2.Text = "取消";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // AccessTypeTailBlock
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(703, 360);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.listView1);
            this.Name = "AccessTypeTailBlock";
            this.Text = "AccessType";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ColumnHeader Type;
        private System.Windows.Forms.ColumnHeader KeyARead;
        private System.Windows.Forms.ColumnHeader KeyAWrite;
        private System.Windows.Forms.ColumnHeader AccessCtrR;
        private System.Windows.Forms.ColumnHeader AccessCtrW;
        private System.Windows.Forms.ColumnHeader KeyBRead;
        private System.Windows.Forms.ColumnHeader KeyBWrite;
        private System.Windows.Forms.Button button2;
    }
}