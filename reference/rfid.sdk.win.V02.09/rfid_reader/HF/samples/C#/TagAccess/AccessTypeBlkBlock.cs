using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication2
{
    public partial class AccessTypeBlkBlock : Form
    {
        //int curIndex;
        int m_curSelectIndex;
        public AccessTypeBlkBlock()
        {
            InitializeComponent();
            //curIndex = 0;
            m_curSelectIndex = 0;
            ListViewItem lvi0 = new ListViewItem();
            lvi0.Text = "0";
            lvi0.SubItems.Add("key A|key B");
            lvi0.SubItems.Add("key A|key B");
            lvi0.SubItems.Add("key A|key B");
            lvi0.SubItems.Add("key A|key B");
            listView1.Items.Add(lvi0);

            ListViewItem lvi1 = new ListViewItem();
            lvi1.Text = "1";
            lvi1.SubItems.Add("key A|key B");
            lvi1.SubItems.Add("key B");
            lvi1.SubItems.Add("never");
            lvi1.SubItems.Add("never");
            listView1.Items.Add(lvi1);

            ListViewItem lvi2 = new ListViewItem();
            lvi2.Text = "2";
            lvi2.SubItems.Add("key A|key B");
            lvi2.SubItems.Add("never");
            lvi2.SubItems.Add("never");
            lvi2.SubItems.Add("never");
            listView1.Items.Add(lvi2);

            ListViewItem lvi3 = new ListViewItem();
            lvi3.Text = "3";
            lvi3.SubItems.Add("key A|key B");
            lvi3.SubItems.Add("key B");
            lvi3.SubItems.Add("key B");
            lvi3.SubItems.Add("key A|key B");
            listView1.Items.Add(lvi3);

            ListViewItem lvi4 = new ListViewItem();
            lvi4.Text = "4";
            lvi4.SubItems.Add("key A|key B");
            lvi4.SubItems.Add("never");
            lvi4.SubItems.Add("never");
            lvi4.SubItems.Add("key A|key B");
            listView1.Items.Add(lvi4);

            ListViewItem lvi5 = new ListViewItem();
            lvi5.Text = "5";
            lvi5.SubItems.Add("key B");
            lvi5.SubItems.Add("never");
            lvi5.SubItems.Add("never");
            lvi5.SubItems.Add("never");
            listView1.Items.Add(lvi5);

            ListViewItem lvi6 = new ListViewItem();
            lvi6.Text = "6";
            lvi6.SubItems.Add("key B");
            lvi6.SubItems.Add("key B");
            lvi6.SubItems.Add("never");
            lvi6.SubItems.Add("never");
            listView1.Items.Add(lvi6);

            ListViewItem lvi7 = new ListViewItem();
            lvi7.Text = "7";
            lvi7.SubItems.Add("never");
            lvi7.SubItems.Add("never");
            lvi7.SubItems.Add("never");
            lvi7.SubItems.Add("never");
            listView1.Items.Add(lvi7);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK; //Close();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //listView1.sel
            m_curSelectIndex = listView1.FocusedItem.Index;
        }
        public void setCurSelectIndex(int index)
        {
            //listView1.FocusedItem.Index = index;
            //listView1.set
        }

        public int getSelectIndex()
        {
            return m_curSelectIndex;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}