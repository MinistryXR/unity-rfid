<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainFrm
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.ComboBoxFrame = New System.Windows.Forms.ComboBox
        Me.LabelFrame = New System.Windows.Forms.Label
        Me.ComboBoxBaud = New System.Windows.Forms.ComboBox
        Me.LabelBaud = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.ComboBoxCom = New System.Windows.Forms.ComboBox
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.ButtonClose = New System.Windows.Forms.Button
        Me.ButtonOpen = New System.Windows.Forms.Button
        Me.ComboBoxComm = New System.Windows.Forms.ComboBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.ComboBoxReader = New System.Windows.Forms.ComboBox
        Me.GroupBoxNet = New System.Windows.Forms.GroupBox
        Me.TextBoxPort = New System.Windows.Forms.TextBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.TextBoxIpAddress = New System.Windows.Forms.TextBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.groupBox4 = New System.Windows.Forms.GroupBox
        Me.buttonDisconnect = New System.Windows.Forms.Button
        Me.buttonConnect = New System.Windows.Forms.Button
        Me.tabControl1 = New System.Windows.Forms.TabControl
        Me.tabPage1 = New System.Windows.Forms.TabPage
        Me.checkBoxLock = New System.Windows.Forms.CheckBox
        Me.buttonWriteUri = New System.Windows.Forms.Button
        Me.buttonReadUri = New System.Windows.Forms.Button
        Me.textBoxUriAddress = New System.Windows.Forms.TextBox
        Me.labelAddr = New System.Windows.Forms.Label
        Me.buttonInventory = New System.Windows.Forms.Button
        Me.comboBoxUid = New System.Windows.Forms.ComboBox
        Me.Label6 = New System.Windows.Forms.Label
        Me.GroupBox1.SuspendLayout()
        Me.GroupBoxNet.SuspendLayout()
        Me.groupBox4.SuspendLayout()
        Me.tabControl1.SuspendLayout()
        Me.tabPage1.SuspendLayout()
        Me.SuspendLayout()
        '
        'ComboBoxFrame
        '
        Me.ComboBoxFrame.FormattingEnabled = True
        Me.ComboBoxFrame.Location = New System.Drawing.Point(64, 86)
        Me.ComboBoxFrame.Name = "ComboBoxFrame"
        Me.ComboBoxFrame.Size = New System.Drawing.Size(91, 20)
        Me.ComboBoxFrame.TabIndex = 6
        '
        'LabelFrame
        '
        Me.LabelFrame.AutoSize = True
        Me.LabelFrame.Location = New System.Drawing.Point(17, 90)
        Me.LabelFrame.Name = "LabelFrame"
        Me.LabelFrame.Size = New System.Drawing.Size(41, 12)
        Me.LabelFrame.TabIndex = 5
        Me.LabelFrame.Text = "Frame:"
        '
        'ComboBoxBaud
        '
        Me.ComboBoxBaud.FormattingEnabled = True
        Me.ComboBoxBaud.Location = New System.Drawing.Point(64, 54)
        Me.ComboBoxBaud.Name = "ComboBoxBaud"
        Me.ComboBoxBaud.Size = New System.Drawing.Size(91, 20)
        Me.ComboBoxBaud.TabIndex = 6
        '
        'LabelBaud
        '
        Me.LabelBaud.AutoSize = True
        Me.LabelBaud.Location = New System.Drawing.Point(23, 57)
        Me.LabelBaud.Name = "LabelBaud"
        Me.LabelBaud.Size = New System.Drawing.Size(35, 12)
        Me.LabelBaud.TabIndex = 5
        Me.LabelBaud.Text = "Baud:"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(24, 13)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(47, 12)
        Me.Label1.TabIndex = 10
        Me.Label1.Text = "Reader:"
        '
        'ComboBoxCom
        '
        Me.ComboBoxCom.FormattingEnabled = True
        Me.ComboBoxCom.Location = New System.Drawing.Point(64, 22)
        Me.ComboBoxCom.Name = "ComboBoxCom"
        Me.ComboBoxCom.Size = New System.Drawing.Size(91, 20)
        Me.ComboBoxCom.TabIndex = 6
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.ComboBoxFrame)
        Me.GroupBox1.Controls.Add(Me.LabelFrame)
        Me.GroupBox1.Controls.Add(Me.ComboBoxBaud)
        Me.GroupBox1.Controls.Add(Me.LabelBaud)
        Me.GroupBox1.Controls.Add(Me.ComboBoxCom)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Location = New System.Drawing.Point(26, 46)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(183, 124)
        Me.GroupBox1.TabIndex = 19
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Serial interface"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(29, 25)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(29, 12)
        Me.Label3.TabIndex = 5
        Me.Label3.Text = "COM:"
        '
        'ButtonClose
        '
        Me.ButtonClose.Location = New System.Drawing.Point(442, 9)
        Me.ButtonClose.Name = "ButtonClose"
        Me.ButtonClose.Size = New System.Drawing.Size(75, 23)
        Me.ButtonClose.TabIndex = 17
        Me.ButtonClose.Text = "Close"
        Me.ButtonClose.UseVisualStyleBackColor = True
        '
        'ButtonOpen
        '
        Me.ButtonOpen.Location = New System.Drawing.Point(359, 8)
        Me.ButtonOpen.Name = "ButtonOpen"
        Me.ButtonOpen.Size = New System.Drawing.Size(75, 23)
        Me.ButtonOpen.TabIndex = 18
        Me.ButtonOpen.Text = "Open"
        Me.ButtonOpen.UseVisualStyleBackColor = True
        '
        'ComboBoxComm
        '
        Me.ComboBoxComm.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBoxComm.FormattingEnabled = True
        Me.ComboBoxComm.Location = New System.Drawing.Point(271, 9)
        Me.ComboBoxComm.Name = "ComboBoxComm"
        Me.ComboBoxComm.Size = New System.Drawing.Size(71, 20)
        Me.ComboBoxComm.TabIndex = 15
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(188, 12)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(77, 12)
        Me.Label2.TabIndex = 14
        Me.Label2.Text = "Communicate:"
        '
        'ComboBoxReader
        '
        Me.ComboBoxReader.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBoxReader.FormattingEnabled = True
        Me.ComboBoxReader.Location = New System.Drawing.Point(77, 10)
        Me.ComboBoxReader.Name = "ComboBoxReader"
        Me.ComboBoxReader.Size = New System.Drawing.Size(93, 20)
        Me.ComboBoxReader.TabIndex = 11
        '
        'GroupBoxNet
        '
        Me.GroupBoxNet.Controls.Add(Me.TextBoxPort)
        Me.GroupBoxNet.Controls.Add(Me.Label4)
        Me.GroupBoxNet.Controls.Add(Me.TextBoxIpAddress)
        Me.GroupBoxNet.Controls.Add(Me.Label5)
        Me.GroupBoxNet.Location = New System.Drawing.Point(229, 46)
        Me.GroupBoxNet.Name = "GroupBoxNet"
        Me.GroupBoxNet.Size = New System.Drawing.Size(288, 124)
        Me.GroupBoxNet.TabIndex = 20
        Me.GroupBoxNet.TabStop = False
        Me.GroupBoxNet.Text = "Net"
        '
        'TextBoxPort
        '
        Me.TextBoxPort.Location = New System.Drawing.Point(97, 75)
        Me.TextBoxPort.Name = "TextBoxPort"
        Me.TextBoxPort.Size = New System.Drawing.Size(172, 21)
        Me.TextBoxPort.TabIndex = 1
        Me.TextBoxPort.Text = "9909"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(56, 79)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(35, 12)
        Me.Label4.TabIndex = 0
        Me.Label4.Text = "Port:"
        '
        'TextBoxIpAddress
        '
        Me.TextBoxIpAddress.Location = New System.Drawing.Point(97, 24)
        Me.TextBoxIpAddress.Name = "TextBoxIpAddress"
        Me.TextBoxIpAddress.Size = New System.Drawing.Size(172, 21)
        Me.TextBoxIpAddress.TabIndex = 1
        Me.TextBoxIpAddress.Text = "192.168.0.222"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(20, 30)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(71, 12)
        Me.Label5.TabIndex = 0
        Me.Label5.Text = "IP address:"
        '
        'groupBox4
        '
        Me.groupBox4.Controls.Add(Me.buttonDisconnect)
        Me.groupBox4.Controls.Add(Me.buttonConnect)
        Me.groupBox4.Controls.Add(Me.tabControl1)
        Me.groupBox4.Controls.Add(Me.buttonInventory)
        Me.groupBox4.Controls.Add(Me.comboBoxUid)
        Me.groupBox4.Controls.Add(Me.Label6)
        Me.groupBox4.Location = New System.Drawing.Point(26, 181)
        Me.groupBox4.Name = "groupBox4"
        Me.groupBox4.Size = New System.Drawing.Size(501, 256)
        Me.groupBox4.TabIndex = 21
        Me.groupBox4.TabStop = False
        Me.groupBox4.Text = "NFC"
        '
        'buttonDisconnect
        '
        Me.buttonDisconnect.Location = New System.Drawing.Point(400, 21)
        Me.buttonDisconnect.Name = "buttonDisconnect"
        Me.buttonDisconnect.Size = New System.Drawing.Size(75, 23)
        Me.buttonDisconnect.TabIndex = 4
        Me.buttonDisconnect.Text = "Disconnect"
        Me.buttonDisconnect.UseVisualStyleBackColor = True
        '
        'buttonConnect
        '
        Me.buttonConnect.Location = New System.Drawing.Point(311, 21)
        Me.buttonConnect.Name = "buttonConnect"
        Me.buttonConnect.Size = New System.Drawing.Size(75, 23)
        Me.buttonConnect.TabIndex = 4
        Me.buttonConnect.Text = "Connect"
        Me.buttonConnect.UseVisualStyleBackColor = True
        '
        'tabControl1
        '
        Me.tabControl1.Controls.Add(Me.tabPage1)
        Me.tabControl1.Location = New System.Drawing.Point(12, 51)
        Me.tabControl1.Name = "tabControl1"
        Me.tabControl1.SelectedIndex = 0
        Me.tabControl1.Size = New System.Drawing.Size(476, 199)
        Me.tabControl1.TabIndex = 3
        '
        'tabPage1
        '
        Me.tabPage1.BackColor = System.Drawing.SystemColors.Control
        Me.tabPage1.Controls.Add(Me.checkBoxLock)
        Me.tabPage1.Controls.Add(Me.buttonWriteUri)
        Me.tabPage1.Controls.Add(Me.buttonReadUri)
        Me.tabPage1.Controls.Add(Me.textBoxUriAddress)
        Me.tabPage1.Controls.Add(Me.labelAddr)
        Me.tabPage1.Location = New System.Drawing.Point(4, 22)
        Me.tabPage1.Name = "tabPage1"
        Me.tabPage1.Padding = New System.Windows.Forms.Padding(3)
        Me.tabPage1.Size = New System.Drawing.Size(468, 173)
        Me.tabPage1.TabIndex = 0
        Me.tabPage1.Text = "URI"
        '
        'checkBoxLock
        '
        Me.checkBoxLock.AutoSize = True
        Me.checkBoxLock.Location = New System.Drawing.Point(295, 76)
        Me.checkBoxLock.Name = "checkBoxLock"
        Me.checkBoxLock.Size = New System.Drawing.Size(48, 16)
        Me.checkBoxLock.TabIndex = 4
        Me.checkBoxLock.Text = "Lock"
        Me.checkBoxLock.UseVisualStyleBackColor = True
        '
        'buttonWriteUri
        '
        Me.buttonWriteUri.Location = New System.Drawing.Point(157, 67)
        Me.buttonWriteUri.Name = "buttonWriteUri"
        Me.buttonWriteUri.Size = New System.Drawing.Size(111, 33)
        Me.buttonWriteUri.TabIndex = 3
        Me.buttonWriteUri.Text = "Write"
        Me.buttonWriteUri.UseVisualStyleBackColor = True
        '
        'buttonReadUri
        '
        Me.buttonReadUri.Location = New System.Drawing.Point(157, 119)
        Me.buttonReadUri.Name = "buttonReadUri"
        Me.buttonReadUri.Size = New System.Drawing.Size(111, 33)
        Me.buttonReadUri.TabIndex = 2
        Me.buttonReadUri.Text = "Read"
        Me.buttonReadUri.UseVisualStyleBackColor = True
        '
        'textBoxUriAddress
        '
        Me.textBoxUriAddress.Location = New System.Drawing.Point(104, 29)
        Me.textBoxUriAddress.Name = "textBoxUriAddress"
        Me.textBoxUriAddress.Size = New System.Drawing.Size(324, 21)
        Me.textBoxUriAddress.TabIndex = 1
        '
        'labelAddr
        '
        Me.labelAddr.AutoSize = True
        Me.labelAddr.Location = New System.Drawing.Point(45, 33)
        Me.labelAddr.Name = "labelAddr"
        Me.labelAddr.Size = New System.Drawing.Size(53, 12)
        Me.labelAddr.TabIndex = 0
        Me.labelAddr.Text = "Address:"
        '
        'buttonInventory
        '
        Me.buttonInventory.Location = New System.Drawing.Point(221, 21)
        Me.buttonInventory.Name = "buttonInventory"
        Me.buttonInventory.Size = New System.Drawing.Size(75, 23)
        Me.buttonInventory.TabIndex = 2
        Me.buttonInventory.Text = "Inventory"
        Me.buttonInventory.UseVisualStyleBackColor = True
        '
        'comboBoxUid
        '
        Me.comboBoxUid.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.comboBoxUid.FormattingEnabled = True
        Me.comboBoxUid.Location = New System.Drawing.Point(75, 24)
        Me.comboBoxUid.Name = "comboBoxUid"
        Me.comboBoxUid.Size = New System.Drawing.Size(136, 20)
        Me.comboBoxUid.TabIndex = 1
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(16, 27)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(53, 12)
        Me.Label6.TabIndex = 0
        Me.Label6.Text = "Tag Uid:"
        '
        'MainFrm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(542, 449)
        Me.Controls.Add(Me.groupBox4)
        Me.Controls.Add(Me.GroupBoxNet)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.ButtonClose)
        Me.Controls.Add(Me.ButtonOpen)
        Me.Controls.Add(Me.ComboBoxComm)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.ComboBoxReader)
        Me.Name = "MainFrm"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "NFCSample"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBoxNet.ResumeLayout(False)
        Me.GroupBoxNet.PerformLayout()
        Me.groupBox4.ResumeLayout(False)
        Me.groupBox4.PerformLayout()
        Me.tabControl1.ResumeLayout(False)
        Me.tabPage1.ResumeLayout(False)
        Me.tabPage1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents ComboBoxFrame As System.Windows.Forms.ComboBox
    Friend WithEvents LabelFrame As System.Windows.Forms.Label
    Friend WithEvents ComboBoxBaud As System.Windows.Forms.ComboBox
    Friend WithEvents LabelBaud As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents ComboBoxCom As System.Windows.Forms.ComboBox
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents ButtonClose As System.Windows.Forms.Button
    Friend WithEvents ButtonOpen As System.Windows.Forms.Button
    Friend WithEvents ComboBoxComm As System.Windows.Forms.ComboBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents ComboBoxReader As System.Windows.Forms.ComboBox
    Friend WithEvents GroupBoxNet As System.Windows.Forms.GroupBox
    Friend WithEvents TextBoxPort As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents TextBoxIpAddress As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Private WithEvents groupBox4 As System.Windows.Forms.GroupBox
    Private WithEvents buttonDisconnect As System.Windows.Forms.Button
    Private WithEvents buttonConnect As System.Windows.Forms.Button
    Private WithEvents tabControl1 As System.Windows.Forms.TabControl
    Private WithEvents tabPage1 As System.Windows.Forms.TabPage
    Private WithEvents checkBoxLock As System.Windows.Forms.CheckBox
    Private WithEvents buttonWriteUri As System.Windows.Forms.Button
    Private WithEvents buttonReadUri As System.Windows.Forms.Button
    Private WithEvents textBoxUriAddress As System.Windows.Forms.TextBox
    Private WithEvents labelAddr As System.Windows.Forms.Label
    Private WithEvents buttonInventory As System.Windows.Forms.Button
    Private WithEvents comboBoxUid As System.Windows.Forms.ComboBox
    Private WithEvents Label6 As System.Windows.Forms.Label

End Class
