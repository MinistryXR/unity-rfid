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
        Me.Label1 = New System.Windows.Forms.Label
        Me.ComboBoxReader = New System.Windows.Forms.ComboBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.ComboBoxComm = New System.Windows.Forms.ComboBox
        Me.ButtonOpen = New System.Windows.Forms.Button
        Me.ButtonClose = New System.Windows.Forms.Button
        Me.Label3 = New System.Windows.Forms.Label
        Me.ComboBoxCom = New System.Windows.Forms.ComboBox
        Me.LabelBaud = New System.Windows.Forms.Label
        Me.ComboBoxBaud = New System.Windows.Forms.ComboBox
        Me.LabelFrame = New System.Windows.Forms.Label
        Me.ComboBoxFrame = New System.Windows.Forms.ComboBox
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.GroupBoxNet = New System.Windows.Forms.GroupBox
        Me.TextBoxPort = New System.Windows.Forms.TextBox
        Me.LabelPort = New System.Windows.Forms.Label
        Me.TextBoxIpAddress = New System.Windows.Forms.TextBox
        Me.LabelIP = New System.Windows.Forms.Label
        Me.TabNxpIcodeSli = New System.Windows.Forms.TabPage
        Me.TextBoxDSFID = New System.Windows.Forms.TextBox
        Me.TextBoxAFI = New System.Windows.Forms.TextBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.LabelAFI = New System.Windows.Forms.Label
        Me.ButtonLockBlock = New System.Windows.Forms.Button
        Me.ButtonWriteBlock = New System.Windows.Forms.Button
        Me.ButtonLockDSFID = New System.Windows.Forms.Button
        Me.ButtonLockAFI = New System.Windows.Forms.Button
        Me.ButtonLockEAS = New System.Windows.Forms.Button
        Me.ButtonCheckEAS = New System.Windows.Forms.Button
        Me.ButtonDisableEAS = New System.Windows.Forms.Button
        Me.ButtonWriteDSFID = New System.Windows.Forms.Button
        Me.ButtonEnableEAS = New System.Windows.Forms.Button
        Me.ButtonWriteAFI = New System.Windows.Forms.Button
        Me.ButtonReadBlock = New System.Windows.Forms.Button
        Me.ComboBoxBlockNum = New System.Windows.Forms.ComboBox
        Me.ComboBoxBlockAddr = New System.Windows.Forms.ComboBox
        Me.LabelBlockNum = New System.Windows.Forms.Label
        Me.LabelBlockAddr = New System.Windows.Forms.Label
        Me.TextBoxBlockBuffer = New System.Windows.Forms.TextBox
        Me.LabelBlkBuffer = New System.Windows.Forms.Label
        Me.ButtonGetTagInfor = New System.Windows.Forms.Button
        Me.ButtonDisconnect = New System.Windows.Forms.Button
        Me.ButtonConnect = New System.Windows.Forms.Button
        Me.ComboBoxUIDs = New System.Windows.Forms.ComboBox
        Me.LabelUIDs = New System.Windows.Forms.Label
        Me.TabControlFun = New System.Windows.Forms.TabControl
        Me.TabPageInventory = New System.Windows.Forms.TabPage
        Me.ButtonStop = New System.Windows.Forms.Button
        Me.ButtonStart = New System.Windows.Forms.Button
        Me.ListViewUIDs = New System.Windows.Forms.ListView
        Me.ColumnHeader1 = New System.Windows.Forms.ColumnHeader
        Me.ColumnHeader2 = New System.Windows.Forms.ColumnHeader
        Me.ColumnHeader3 = New System.Windows.Forms.ColumnHeader
        Me.ColumnHeader4 = New System.Windows.Forms.ColumnHeader
        Me.ColumnHeader5 = New System.Windows.Forms.ColumnHeader
        Me.ButtonGetReaderInfo = New System.Windows.Forms.Button
        Me.GroupBox1.SuspendLayout()
        Me.GroupBoxNet.SuspendLayout()
        Me.TabNxpIcodeSli.SuspendLayout()
        Me.TabControlFun.SuspendLayout()
        Me.TabPageInventory.SuspendLayout()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(39, 25)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(47, 12)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Reader:"
        '
        'ComboBoxReader
        '
        Me.ComboBoxReader.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBoxReader.FormattingEnabled = True
        Me.ComboBoxReader.Location = New System.Drawing.Point(92, 22)
        Me.ComboBoxReader.Name = "ComboBoxReader"
        Me.ComboBoxReader.Size = New System.Drawing.Size(93, 20)
        Me.ComboBoxReader.TabIndex = 1
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(203, 24)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(77, 12)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "Communicate:"
        '
        'ComboBoxComm
        '
        Me.ComboBoxComm.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBoxComm.FormattingEnabled = True
        Me.ComboBoxComm.Location = New System.Drawing.Point(286, 21)
        Me.ComboBoxComm.Name = "ComboBoxComm"
        Me.ComboBoxComm.Size = New System.Drawing.Size(71, 20)
        Me.ComboBoxComm.TabIndex = 3
        '
        'ButtonOpen
        '
        Me.ButtonOpen.Location = New System.Drawing.Point(374, 20)
        Me.ButtonOpen.Name = "ButtonOpen"
        Me.ButtonOpen.Size = New System.Drawing.Size(75, 23)
        Me.ButtonOpen.TabIndex = 4
        Me.ButtonOpen.Text = "Open"
        Me.ButtonOpen.UseVisualStyleBackColor = True
        '
        'ButtonClose
        '
        Me.ButtonClose.Location = New System.Drawing.Point(457, 21)
        Me.ButtonClose.Name = "ButtonClose"
        Me.ButtonClose.Size = New System.Drawing.Size(75, 23)
        Me.ButtonClose.TabIndex = 4
        Me.ButtonClose.Text = "Close"
        Me.ButtonClose.UseVisualStyleBackColor = True
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
        'ComboBoxCom
        '
        Me.ComboBoxCom.FormattingEnabled = True
        Me.ComboBoxCom.Location = New System.Drawing.Point(64, 22)
        Me.ComboBoxCom.Name = "ComboBoxCom"
        Me.ComboBoxCom.Size = New System.Drawing.Size(91, 20)
        Me.ComboBoxCom.TabIndex = 6
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
        'ComboBoxBaud
        '
        Me.ComboBoxBaud.FormattingEnabled = True
        Me.ComboBoxBaud.Location = New System.Drawing.Point(64, 54)
        Me.ComboBoxBaud.Name = "ComboBoxBaud"
        Me.ComboBoxBaud.Size = New System.Drawing.Size(91, 20)
        Me.ComboBoxBaud.TabIndex = 6
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
        'ComboBoxFrame
        '
        Me.ComboBoxFrame.FormattingEnabled = True
        Me.ComboBoxFrame.Location = New System.Drawing.Point(64, 86)
        Me.ComboBoxFrame.Name = "ComboBoxFrame"
        Me.ComboBoxFrame.Size = New System.Drawing.Size(91, 20)
        Me.ComboBoxFrame.TabIndex = 6
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.ComboBoxFrame)
        Me.GroupBox1.Controls.Add(Me.LabelFrame)
        Me.GroupBox1.Controls.Add(Me.ComboBoxBaud)
        Me.GroupBox1.Controls.Add(Me.LabelBaud)
        Me.GroupBox1.Controls.Add(Me.ComboBoxCom)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Location = New System.Drawing.Point(72, 66)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(183, 124)
        Me.GroupBox1.TabIndex = 7
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Serial interface"
        '
        'GroupBoxNet
        '
        Me.GroupBoxNet.Controls.Add(Me.TextBoxPort)
        Me.GroupBoxNet.Controls.Add(Me.LabelPort)
        Me.GroupBoxNet.Controls.Add(Me.TextBoxIpAddress)
        Me.GroupBoxNet.Controls.Add(Me.LabelIP)
        Me.GroupBoxNet.Location = New System.Drawing.Point(305, 66)
        Me.GroupBoxNet.Name = "GroupBoxNet"
        Me.GroupBoxNet.Size = New System.Drawing.Size(311, 124)
        Me.GroupBoxNet.TabIndex = 8
        Me.GroupBoxNet.TabStop = False
        Me.GroupBoxNet.Text = "Net"
        '
        'TextBoxPort
        '
        Me.TextBoxPort.Location = New System.Drawing.Point(114, 75)
        Me.TextBoxPort.Name = "TextBoxPort"
        Me.TextBoxPort.Size = New System.Drawing.Size(172, 21)
        Me.TextBoxPort.TabIndex = 1
        Me.TextBoxPort.Text = "9909"
        '
        'LabelPort
        '
        Me.LabelPort.AutoSize = True
        Me.LabelPort.Location = New System.Drawing.Point(73, 79)
        Me.LabelPort.Name = "LabelPort"
        Me.LabelPort.Size = New System.Drawing.Size(35, 12)
        Me.LabelPort.TabIndex = 0
        Me.LabelPort.Text = "Port:"
        '
        'TextBoxIpAddress
        '
        Me.TextBoxIpAddress.Location = New System.Drawing.Point(114, 24)
        Me.TextBoxIpAddress.Name = "TextBoxIpAddress"
        Me.TextBoxIpAddress.Size = New System.Drawing.Size(172, 21)
        Me.TextBoxIpAddress.TabIndex = 1
        Me.TextBoxIpAddress.Text = "192.168.0.222"
        '
        'LabelIP
        '
        Me.LabelIP.AutoSize = True
        Me.LabelIP.Location = New System.Drawing.Point(37, 30)
        Me.LabelIP.Name = "LabelIP"
        Me.LabelIP.Size = New System.Drawing.Size(71, 12)
        Me.LabelIP.TabIndex = 0
        Me.LabelIP.Text = "IP address:"
        '
        'TabNxpIcodeSli
        '
        Me.TabNxpIcodeSli.BackColor = System.Drawing.Color.WhiteSmoke
        Me.TabNxpIcodeSli.Controls.Add(Me.TextBoxDSFID)
        Me.TabNxpIcodeSli.Controls.Add(Me.TextBoxAFI)
        Me.TabNxpIcodeSli.Controls.Add(Me.Label4)
        Me.TabNxpIcodeSli.Controls.Add(Me.LabelAFI)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonLockBlock)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonWriteBlock)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonLockDSFID)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonLockAFI)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonLockEAS)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonCheckEAS)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonDisableEAS)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonWriteDSFID)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonEnableEAS)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonWriteAFI)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonReadBlock)
        Me.TabNxpIcodeSli.Controls.Add(Me.ComboBoxBlockNum)
        Me.TabNxpIcodeSli.Controls.Add(Me.ComboBoxBlockAddr)
        Me.TabNxpIcodeSli.Controls.Add(Me.LabelBlockNum)
        Me.TabNxpIcodeSli.Controls.Add(Me.LabelBlockAddr)
        Me.TabNxpIcodeSli.Controls.Add(Me.TextBoxBlockBuffer)
        Me.TabNxpIcodeSli.Controls.Add(Me.LabelBlkBuffer)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonGetTagInfor)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonDisconnect)
        Me.TabNxpIcodeSli.Controls.Add(Me.ButtonConnect)
        Me.TabNxpIcodeSli.Controls.Add(Me.ComboBoxUIDs)
        Me.TabNxpIcodeSli.Controls.Add(Me.LabelUIDs)
        Me.TabNxpIcodeSli.Location = New System.Drawing.Point(4, 22)
        Me.TabNxpIcodeSli.Name = "TabNxpIcodeSli"
        Me.TabNxpIcodeSli.Padding = New System.Windows.Forms.Padding(3)
        Me.TabNxpIcodeSli.Size = New System.Drawing.Size(596, 258)
        Me.TabNxpIcodeSli.TabIndex = 0
        Me.TabNxpIcodeSli.Text = "NXP ICODE SLI"
        Me.TabNxpIcodeSli.UseVisualStyleBackColor = True
        '
        'TextBoxDSFID
        '
        Me.TextBoxDSFID.Location = New System.Drawing.Point(145, 193)
        Me.TextBoxDSFID.Name = "TextBoxDSFID"
        Me.TextBoxDSFID.Size = New System.Drawing.Size(66, 21)
        Me.TextBoxDSFID.TabIndex = 10
        Me.TextBoxDSFID.Text = "00"
        '
        'TextBoxAFI
        '
        Me.TextBoxAFI.Location = New System.Drawing.Point(145, 157)
        Me.TextBoxAFI.Name = "TextBoxAFI"
        Me.TextBoxAFI.Size = New System.Drawing.Size(66, 21)
        Me.TextBoxAFI.TabIndex = 10
        Me.TextBoxAFI.Text = "00"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(68, 196)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(71, 12)
        Me.Label4.TabIndex = 9
        Me.Label4.Text = "DSFID(Hex):"
        '
        'LabelAFI
        '
        Me.LabelAFI.AutoSize = True
        Me.LabelAFI.Location = New System.Drawing.Point(83, 160)
        Me.LabelAFI.Name = "LabelAFI"
        Me.LabelAFI.Size = New System.Drawing.Size(59, 12)
        Me.LabelAFI.TabIndex = 9
        Me.LabelAFI.Text = "AFI(Hex):"
        '
        'ButtonLockBlock
        '
        Me.ButtonLockBlock.Location = New System.Drawing.Point(441, 117)
        Me.ButtonLockBlock.Name = "ButtonLockBlock"
        Me.ButtonLockBlock.Size = New System.Drawing.Size(100, 25)
        Me.ButtonLockBlock.TabIndex = 8
        Me.ButtonLockBlock.Text = "Lock block"
        Me.ButtonLockBlock.UseVisualStyleBackColor = True
        '
        'ButtonWriteBlock
        '
        Me.ButtonWriteBlock.Location = New System.Drawing.Point(289, 117)
        Me.ButtonWriteBlock.Name = "ButtonWriteBlock"
        Me.ButtonWriteBlock.Size = New System.Drawing.Size(100, 25)
        Me.ButtonWriteBlock.TabIndex = 8
        Me.ButtonWriteBlock.Text = "Write block"
        Me.ButtonWriteBlock.UseVisualStyleBackColor = True
        '
        'ButtonLockDSFID
        '
        Me.ButtonLockDSFID.Location = New System.Drawing.Point(403, 190)
        Me.ButtonLockDSFID.Name = "ButtonLockDSFID"
        Me.ButtonLockDSFID.Size = New System.Drawing.Size(100, 25)
        Me.ButtonLockDSFID.TabIndex = 8
        Me.ButtonLockDSFID.Text = "Lock DSFID"
        Me.ButtonLockDSFID.UseVisualStyleBackColor = True
        '
        'ButtonLockAFI
        '
        Me.ButtonLockAFI.Location = New System.Drawing.Point(403, 153)
        Me.ButtonLockAFI.Name = "ButtonLockAFI"
        Me.ButtonLockAFI.Size = New System.Drawing.Size(100, 25)
        Me.ButtonLockAFI.TabIndex = 8
        Me.ButtonLockAFI.Text = "Lock AFI"
        Me.ButtonLockAFI.UseVisualStyleBackColor = True
        '
        'ButtonLockEAS
        '
        Me.ButtonLockEAS.Location = New System.Drawing.Point(464, 224)
        Me.ButtonLockEAS.Name = "ButtonLockEAS"
        Me.ButtonLockEAS.Size = New System.Drawing.Size(100, 25)
        Me.ButtonLockEAS.TabIndex = 8
        Me.ButtonLockEAS.Text = "Lock EAS"
        Me.ButtonLockEAS.UseVisualStyleBackColor = True
        '
        'ButtonCheckEAS
        '
        Me.ButtonCheckEAS.Location = New System.Drawing.Point(349, 224)
        Me.ButtonCheckEAS.Name = "ButtonCheckEAS"
        Me.ButtonCheckEAS.Size = New System.Drawing.Size(100, 25)
        Me.ButtonCheckEAS.TabIndex = 8
        Me.ButtonCheckEAS.Text = "Check EAS"
        Me.ButtonCheckEAS.UseVisualStyleBackColor = True
        '
        'ButtonDisableEAS
        '
        Me.ButtonDisableEAS.Location = New System.Drawing.Point(230, 227)
        Me.ButtonDisableEAS.Name = "ButtonDisableEAS"
        Me.ButtonDisableEAS.Size = New System.Drawing.Size(100, 25)
        Me.ButtonDisableEAS.TabIndex = 8
        Me.ButtonDisableEAS.Text = "Disable EAS"
        Me.ButtonDisableEAS.UseVisualStyleBackColor = True
        '
        'ButtonWriteDSFID
        '
        Me.ButtonWriteDSFID.Location = New System.Drawing.Point(255, 193)
        Me.ButtonWriteDSFID.Name = "ButtonWriteDSFID"
        Me.ButtonWriteDSFID.Size = New System.Drawing.Size(100, 25)
        Me.ButtonWriteDSFID.TabIndex = 8
        Me.ButtonWriteDSFID.Text = "Write DSFID"
        Me.ButtonWriteDSFID.UseVisualStyleBackColor = True
        '
        'ButtonEnableEAS
        '
        Me.ButtonEnableEAS.Location = New System.Drawing.Point(111, 224)
        Me.ButtonEnableEAS.Name = "ButtonEnableEAS"
        Me.ButtonEnableEAS.Size = New System.Drawing.Size(100, 25)
        Me.ButtonEnableEAS.TabIndex = 8
        Me.ButtonEnableEAS.Text = "Enable EAS"
        Me.ButtonEnableEAS.UseVisualStyleBackColor = True
        '
        'ButtonWriteAFI
        '
        Me.ButtonWriteAFI.Location = New System.Drawing.Point(255, 153)
        Me.ButtonWriteAFI.Name = "ButtonWriteAFI"
        Me.ButtonWriteAFI.Size = New System.Drawing.Size(100, 25)
        Me.ButtonWriteAFI.TabIndex = 8
        Me.ButtonWriteAFI.Text = "Write AFI"
        Me.ButtonWriteAFI.UseVisualStyleBackColor = True
        '
        'ButtonReadBlock
        '
        Me.ButtonReadBlock.Location = New System.Drawing.Point(145, 117)
        Me.ButtonReadBlock.Name = "ButtonReadBlock"
        Me.ButtonReadBlock.Size = New System.Drawing.Size(100, 25)
        Me.ButtonReadBlock.TabIndex = 8
        Me.ButtonReadBlock.Text = "Read block"
        Me.ButtonReadBlock.UseVisualStyleBackColor = True
        '
        'ComboBoxBlockNum
        '
        Me.ComboBoxBlockNum.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBoxBlockNum.FormattingEnabled = True
        Me.ComboBoxBlockNum.Location = New System.Drawing.Point(403, 86)
        Me.ComboBoxBlockNum.Name = "ComboBoxBlockNum"
        Me.ComboBoxBlockNum.Size = New System.Drawing.Size(121, 20)
        Me.ComboBoxBlockNum.TabIndex = 7
        '
        'ComboBoxBlockAddr
        '
        Me.ComboBoxBlockAddr.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.ComboBoxBlockAddr.FormattingEnabled = True
        Me.ComboBoxBlockAddr.Location = New System.Drawing.Point(154, 86)
        Me.ComboBoxBlockAddr.Name = "ComboBoxBlockAddr"
        Me.ComboBoxBlockAddr.Size = New System.Drawing.Size(121, 20)
        Me.ComboBoxBlockAddr.TabIndex = 7
        '
        'LabelBlockNum
        '
        Me.LabelBlockNum.AutoSize = True
        Me.LabelBlockNum.Location = New System.Drawing.Point(314, 89)
        Me.LabelBlockNum.Name = "LabelBlockNum"
        Me.LabelBlockNum.Size = New System.Drawing.Size(83, 12)
        Me.LabelBlockNum.TabIndex = 6
        Me.LabelBlockNum.Text = "Block number:"
        '
        'LabelBlockAddr
        '
        Me.LabelBlockAddr.AutoSize = True
        Me.LabelBlockAddr.Location = New System.Drawing.Point(59, 89)
        Me.LabelBlockAddr.Name = "LabelBlockAddr"
        Me.LabelBlockAddr.Size = New System.Drawing.Size(89, 12)
        Me.LabelBlockAddr.TabIndex = 6
        Me.LabelBlockAddr.Text = "Block address:"
        '
        'TextBoxBlockBuffer
        '
        Me.TextBoxBlockBuffer.Location = New System.Drawing.Point(155, 53)
        Me.TextBoxBlockBuffer.Name = "TextBoxBlockBuffer"
        Me.TextBoxBlockBuffer.Size = New System.Drawing.Size(382, 21)
        Me.TextBoxBlockBuffer.TabIndex = 5
        '
        'LabelBlkBuffer
        '
        Me.LabelBlkBuffer.AutoSize = True
        Me.LabelBlkBuffer.Location = New System.Drawing.Point(42, 56)
        Me.LabelBlkBuffer.Name = "LabelBlkBuffer"
        Me.LabelBlkBuffer.Size = New System.Drawing.Size(107, 12)
        Me.LabelBlkBuffer.TabIndex = 4
        Me.LabelBlkBuffer.Text = " Block data(hex):"
        '
        'ButtonGetTagInfor
        '
        Me.ButtonGetTagInfor.Location = New System.Drawing.Point(464, 19)
        Me.ButtonGetTagInfor.Name = "ButtonGetTagInfor"
        Me.ButtonGetTagInfor.Size = New System.Drawing.Size(126, 23)
        Me.ButtonGetTagInfor.TabIndex = 3
        Me.ButtonGetTagInfor.Text = "Get Information"
        Me.ButtonGetTagInfor.UseVisualStyleBackColor = True
        '
        'ButtonDisconnect
        '
        Me.ButtonDisconnect.Location = New System.Drawing.Point(363, 19)
        Me.ButtonDisconnect.Name = "ButtonDisconnect"
        Me.ButtonDisconnect.Size = New System.Drawing.Size(86, 23)
        Me.ButtonDisconnect.TabIndex = 3
        Me.ButtonDisconnect.Text = "Disconnect"
        Me.ButtonDisconnect.UseVisualStyleBackColor = True
        '
        'ButtonConnect
        '
        Me.ButtonConnect.Location = New System.Drawing.Point(255, 17)
        Me.ButtonConnect.Name = "ButtonConnect"
        Me.ButtonConnect.Size = New System.Drawing.Size(86, 23)
        Me.ButtonConnect.TabIndex = 3
        Me.ButtonConnect.Text = "Connect"
        Me.ButtonConnect.UseVisualStyleBackColor = True
        '
        'ComboBoxUIDs
        '
        Me.ComboBoxUIDs.FormattingEnabled = True
        Me.ComboBoxUIDs.Location = New System.Drawing.Point(79, 19)
        Me.ComboBoxUIDs.Name = "ComboBoxUIDs"
        Me.ComboBoxUIDs.Size = New System.Drawing.Size(155, 20)
        Me.ComboBoxUIDs.TabIndex = 1
        '
        'LabelUIDs
        '
        Me.LabelUIDs.AutoSize = True
        Me.LabelUIDs.Location = New System.Drawing.Point(42, 22)
        Me.LabelUIDs.Name = "LabelUIDs"
        Me.LabelUIDs.Size = New System.Drawing.Size(29, 12)
        Me.LabelUIDs.TabIndex = 0
        Me.LabelUIDs.Text = "UID:"
        '
        'TabControlFun
        '
        Me.TabControlFun.Controls.Add(Me.TabPageInventory)
        Me.TabControlFun.Controls.Add(Me.TabNxpIcodeSli)
        Me.TabControlFun.Location = New System.Drawing.Point(12, 205)
        Me.TabControlFun.Name = "TabControlFun"
        Me.TabControlFun.SelectedIndex = 0
        Me.TabControlFun.Size = New System.Drawing.Size(604, 284)
        Me.TabControlFun.TabIndex = 9
        '
        'TabPageInventory
        '
        Me.TabPageInventory.BackColor = System.Drawing.Color.WhiteSmoke
        Me.TabPageInventory.Controls.Add(Me.ButtonStop)
        Me.TabPageInventory.Controls.Add(Me.ButtonStart)
        Me.TabPageInventory.Controls.Add(Me.ListViewUIDs)
        Me.TabPageInventory.Location = New System.Drawing.Point(4, 22)
        Me.TabPageInventory.Name = "TabPageInventory"
        Me.TabPageInventory.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPageInventory.Size = New System.Drawing.Size(596, 258)
        Me.TabPageInventory.TabIndex = 1
        Me.TabPageInventory.Text = "Inventory"
        Me.TabPageInventory.UseVisualStyleBackColor = True
        '
        'ButtonStop
        '
        Me.ButtonStop.Location = New System.Drawing.Point(475, 78)
        Me.ButtonStop.Name = "ButtonStop"
        Me.ButtonStop.Size = New System.Drawing.Size(100, 35)
        Me.ButtonStop.TabIndex = 1
        Me.ButtonStop.Text = "Stop"
        Me.ButtonStop.UseVisualStyleBackColor = True
        '
        'ButtonStart
        '
        Me.ButtonStart.Location = New System.Drawing.Point(475, 28)
        Me.ButtonStart.Name = "ButtonStart"
        Me.ButtonStart.Size = New System.Drawing.Size(100, 35)
        Me.ButtonStart.TabIndex = 1
        Me.ButtonStart.Text = "Start"
        Me.ButtonStart.UseVisualStyleBackColor = True
        '
        'ListViewUIDs
        '
        Me.ListViewUIDs.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.ColumnHeader1, Me.ColumnHeader2, Me.ColumnHeader3, Me.ColumnHeader4, Me.ColumnHeader5})
        Me.ListViewUIDs.GridLines = True
        Me.ListViewUIDs.Location = New System.Drawing.Point(6, 6)
        Me.ListViewUIDs.Name = "ListViewUIDs"
        Me.ListViewUIDs.Size = New System.Drawing.Size(446, 246)
        Me.ListViewUIDs.TabIndex = 0
        Me.ListViewUIDs.UseCompatibleStateImageBehavior = False
        Me.ListViewUIDs.View = System.Windows.Forms.View.Details
        '
        'ColumnHeader1
        '
        Me.ColumnHeader1.Text = "Protocol"
        Me.ColumnHeader1.Width = 70
        '
        'ColumnHeader2
        '
        Me.ColumnHeader2.Text = "Tag type"
        Me.ColumnHeader2.Width = 67
        '
        'ColumnHeader3
        '
        Me.ColumnHeader3.Text = "UID"
        Me.ColumnHeader3.Width = 93
        '
        'ColumnHeader4
        '
        Me.ColumnHeader4.Text = "Antenna"
        Me.ColumnHeader4.Width = 80
        '
        'ColumnHeader5
        '
        Me.ColumnHeader5.Text = "Read count"
        Me.ColumnHeader5.Width = 171
        '
        'ButtonGetReaderInfo
        '
        Me.ButtonGetReaderInfo.Location = New System.Drawing.Point(541, 22)
        Me.ButtonGetReaderInfo.Name = "ButtonGetReaderInfo"
        Me.ButtonGetReaderInfo.Size = New System.Drawing.Size(89, 23)
        Me.ButtonGetReaderInfo.TabIndex = 4
        Me.ButtonGetReaderInfo.Text = "Reader Infor"
        Me.ButtonGetReaderInfo.UseVisualStyleBackColor = True
        '
        'MainFrm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(642, 501)
        Me.Controls.Add(Me.TabControlFun)
        Me.Controls.Add(Me.GroupBoxNet)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.ButtonGetReaderInfo)
        Me.Controls.Add(Me.ButtonClose)
        Me.Controls.Add(Me.ButtonOpen)
        Me.Controls.Add(Me.ComboBoxComm)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.ComboBoxReader)
        Me.Controls.Add(Me.Label1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Name = "MainFrm"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "TagAccess"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBoxNet.ResumeLayout(False)
        Me.GroupBoxNet.PerformLayout()
        Me.TabNxpIcodeSli.ResumeLayout(False)
        Me.TabNxpIcodeSli.PerformLayout()
        Me.TabControlFun.ResumeLayout(False)
        Me.TabPageInventory.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents ComboBoxReader As System.Windows.Forms.ComboBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents ComboBoxComm As System.Windows.Forms.ComboBox
    Friend WithEvents ButtonOpen As System.Windows.Forms.Button
    Friend WithEvents ButtonClose As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents ComboBoxCom As System.Windows.Forms.ComboBox
    Friend WithEvents LabelBaud As System.Windows.Forms.Label
    Friend WithEvents ComboBoxBaud As System.Windows.Forms.ComboBox
    Friend WithEvents LabelFrame As System.Windows.Forms.Label
    Friend WithEvents ComboBoxFrame As System.Windows.Forms.ComboBox
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBoxNet As System.Windows.Forms.GroupBox
    Friend WithEvents LabelIP As System.Windows.Forms.Label
    Friend WithEvents TextBoxPort As System.Windows.Forms.TextBox
    Friend WithEvents LabelPort As System.Windows.Forms.Label
    Friend WithEvents TextBoxIpAddress As System.Windows.Forms.TextBox
    Friend WithEvents TabNxpIcodeSli As System.Windows.Forms.TabPage
    Friend WithEvents TabControlFun As System.Windows.Forms.TabControl
    Friend WithEvents ComboBoxUIDs As System.Windows.Forms.ComboBox
    Friend WithEvents LabelUIDs As System.Windows.Forms.Label
    Friend WithEvents ButtonDisconnect As System.Windows.Forms.Button
    Friend WithEvents ButtonConnect As System.Windows.Forms.Button
    Friend WithEvents TabPageInventory As System.Windows.Forms.TabPage
    Friend WithEvents ListViewUIDs As System.Windows.Forms.ListView
    Friend WithEvents ButtonStart As System.Windows.Forms.Button
    Friend WithEvents ButtonStop As System.Windows.Forms.Button
    Friend WithEvents ColumnHeader1 As System.Windows.Forms.ColumnHeader
    Friend WithEvents ColumnHeader2 As System.Windows.Forms.ColumnHeader
    Friend WithEvents ColumnHeader3 As System.Windows.Forms.ColumnHeader
    Friend WithEvents ColumnHeader4 As System.Windows.Forms.ColumnHeader
    Friend WithEvents ColumnHeader5 As System.Windows.Forms.ColumnHeader
    Friend WithEvents TextBoxBlockBuffer As System.Windows.Forms.TextBox
    Friend WithEvents LabelBlkBuffer As System.Windows.Forms.Label
    Friend WithEvents LabelBlockAddr As System.Windows.Forms.Label
    Friend WithEvents LabelBlockNum As System.Windows.Forms.Label
    Friend WithEvents ComboBoxBlockNum As System.Windows.Forms.ComboBox
    Friend WithEvents ComboBoxBlockAddr As System.Windows.Forms.ComboBox
    Friend WithEvents ButtonWriteBlock As System.Windows.Forms.Button
    Friend WithEvents ButtonReadBlock As System.Windows.Forms.Button
    Friend WithEvents ButtonGetTagInfor As System.Windows.Forms.Button
    Friend WithEvents ButtonGetReaderInfo As System.Windows.Forms.Button
    Friend WithEvents LabelAFI As System.Windows.Forms.Label
    Friend WithEvents TextBoxAFI As System.Windows.Forms.TextBox
    Friend WithEvents ButtonLockBlock As System.Windows.Forms.Button
    Friend WithEvents ButtonWriteAFI As System.Windows.Forms.Button
    Friend WithEvents ButtonLockAFI As System.Windows.Forms.Button
    Friend WithEvents TextBoxDSFID As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents ButtonLockDSFID As System.Windows.Forms.Button
    Friend WithEvents ButtonWriteDSFID As System.Windows.Forms.Button
    Friend WithEvents ButtonDisableEAS As System.Windows.Forms.Button
    Friend WithEvents ButtonEnableEAS As System.Windows.Forms.Button
    Friend WithEvents ButtonCheckEAS As System.Windows.Forms.Button
    Friend WithEvents ButtonLockEAS As System.Windows.Forms.Button

End Class
