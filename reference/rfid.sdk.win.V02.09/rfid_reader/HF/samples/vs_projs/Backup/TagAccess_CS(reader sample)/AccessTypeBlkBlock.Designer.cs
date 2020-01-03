namespace WindowsApplication2
{
    partial class AccessTypeBlkBlock
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
            this.type = new System.Windows.Forms.ColumnHeader();
            this.Read = new System.Windows.Forms.ColumnHeader();
            this.Write = new System.Windows.Forms.ColumnHeader();
            this.increase = new System.Windows.Forms.ColumnHeader();
            this.descrease = new System.Windows.Forms.ColumnHeader();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.type,
            this.Read,
            this.Write,
            this.increase,
            this.descrease});
            this.listView1.FullRowSelect = true;
            this.listView1.GridLines = true;
            this.listView1.Location = new System.Drawing.Point(47, 25);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(495, 286);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            // 
            // type
            // 
            this.type.Text = "类型";
            this.type.Width = 94;
            // 
            // Read
            // 
            this.Read.Text = "读";
            this.Read.Width = 92;
            // 
            // Write
            // 
            this.Write.Text = "写";
            this.Write.Width = 117;
            // 
            // increase
            // 
            this.increase.Text = "冲值";
            this.increase.Width = 88;
            // 
            // descrease
            // 
            this.descrease.Text = "扣值";
            this.descrease.Width = 145;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(349, 348);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(115, 38);
            this.button1.TabIndex = 1;
            this.button1.Text = "确定";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(151, 348);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(115, 37);
            this.button2.TabIndex = 2;
            this.button2.Text = "取消";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // AccessTypeBlkBlock
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(599, 429);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.listView1);
            this.Name = "AccessTypeBlkBlock";
            this.Text = "AccessTypeBlkBlock";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ColumnHeader type;
        private System.Windows.Forms.ColumnHeader Read;
        private System.Windows.Forms.ColumnHeader Write;
        private System.Windows.Forms.ColumnHeader increase;
        private System.Windows.Forms.ColumnHeader descrease;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}