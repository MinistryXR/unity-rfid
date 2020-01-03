VERSION 5.00
Begin VB.Form MainForm 
   Caption         =   "ISO15693 reader sample"
   ClientHeight    =   7305
   ClientLeft      =   6135
   ClientTop       =   4890
   ClientWidth     =   15660
   LinkTopic       =   "Form1"
   ScaleHeight     =   7305
   ScaleWidth      =   15660
   Begin VB.Frame Frame3 
      Caption         =   "ISO14443a operation"
      Height          =   5055
      Left            =   9480
      TabIndex        =   30
      Top             =   1560
      Width           =   5055
      Begin VB.CommandButton Command1 
         Caption         =   "Auth"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2160
         TabIndex        =   47
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton BntWriteISO14443a 
         Caption         =   "Write"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2160
         TabIndex        =   46
         Top             =   3240
         Width           =   975
      End
      Begin VB.CommandButton BntReadISO14443a 
         Caption         =   "Read"
         Height          =   375
         Left            =   960
         TabIndex        =   45
         Top             =   3240
         Width           =   975
      End
      Begin VB.TextBox txtBlockDataISO14443a 
         Height          =   375
         Left            =   1080
         TabIndex        =   43
         Text            =   "11223344556677889900112233445566"
         Top             =   2640
         Width           =   3135
      End
      Begin VB.ComboBox cmbBlockAddr 
         Height          =   315
         Left            =   960
         Style           =   2  'Dropdown List
         TabIndex        =   41
         Top             =   2040
         Width           =   1095
      End
      Begin VB.TextBox txtKey 
         Height          =   375
         Left            =   960
         TabIndex        =   38
         Text            =   "FFFFFFFFFFFF"
         Top             =   1440
         Width           =   2415
      End
      Begin VB.ComboBox cmbKeyType 
         Height          =   315
         Left            =   960
         Style           =   2  'Dropdown List
         TabIndex        =   36
         Top             =   960
         Width           =   1215
      End
      Begin VB.CommandButton bntDiscISO14443a 
         Caption         =   "Disconnect"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3720
         TabIndex        =   34
         Top             =   360
         Width           =   975
      End
      Begin VB.CommandButton bntConnISO14443a 
         Caption         =   "Connect"
         Height          =   375
         Left            =   2520
         TabIndex        =   33
         Top             =   360
         Width           =   975
      End
      Begin VB.ComboBox cmbUIDISO14443a 
         Height          =   315
         Left            =   720
         TabIndex        =   32
         Top             =   360
         Width           =   1575
      End
      Begin VB.Label Label15 
         Caption         =   "Hex"
         Height          =   375
         Left            =   4200
         TabIndex        =   44
         Top             =   2640
         Width           =   375
      End
      Begin VB.Label Label14 
         Caption         =   "Block Data:"
         Height          =   375
         Left            =   120
         TabIndex        =   42
         Top             =   2640
         Width           =   1215
      End
      Begin VB.Label Label13 
         Caption         =   "Block Addr:"
         Height          =   255
         Left            =   120
         TabIndex        =   40
         Top             =   2040
         Width           =   855
      End
      Begin VB.Label Label12 
         Caption         =   "Hex"
         Height          =   375
         Left            =   3600
         TabIndex        =   39
         Top             =   1440
         Width           =   735
      End
      Begin VB.Label Label11 
         Caption         =   "Key:"
         Height          =   375
         Left            =   480
         TabIndex        =   37
         Top             =   1440
         Width           =   495
      End
      Begin VB.Label Label10 
         Caption         =   "Key type:"
         Height          =   375
         Left            =   240
         TabIndex        =   35
         Top             =   960
         Width           =   735
      End
      Begin VB.Label Label9 
         Caption         =   "UID:"
         Height          =   255
         Left            =   240
         TabIndex        =   31
         Top             =   360
         Width           =   735
      End
   End
   Begin VB.CommandButton bntInventory 
      Caption         =   "Inventory"
      Enabled         =   0   'False
      Height          =   375
      Left            =   2400
      TabIndex        =   28
      Top             =   1560
      Width           =   1095
   End
   Begin VB.ListBox listTagsFound 
      Height          =   4545
      Left            =   120
      TabIndex        =   27
      Top             =   2040
      Width           =   3615
   End
   Begin VB.Frame Frame2 
      Caption         =   "Serial"
      Height          =   735
      Left            =   120
      TabIndex        =   24
      Top             =   600
      Width           =   3015
      Begin VB.ComboBox cmbCOMName 
         Height          =   315
         Left            =   1080
         TabIndex        =   26
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label8 
         Caption         =   "COM Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   25
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.ComboBox cmbCOMMType 
      Height          =   315
      Left            =   1320
      Style           =   2  'Dropdown List
      TabIndex        =   23
      Top             =   240
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Caption         =   "ISO15693 Operation"
      Height          =   5055
      Left            =   3960
      TabIndex        =   2
      Top             =   1560
      Width           =   5415
      Begin VB.ComboBox cmbUID 
         Height          =   315
         Left            =   600
         TabIndex        =   21
         Top             =   480
         Width           =   2415
      End
      Begin VB.ComboBox cmbBlockCnt 
         Height          =   315
         Left            =   1200
         Style           =   2  'Dropdown List
         TabIndex        =   20
         Top             =   1680
         Width           =   1215
      End
      Begin VB.ComboBox cmbStartBlk 
         Height          =   315
         Left            =   1200
         Style           =   2  'Dropdown List
         TabIndex        =   18
         Top             =   1200
         Width           =   1215
      End
      Begin VB.TextBox txtAFI 
         Height          =   375
         Left            =   1200
         TabIndex        =   14
         Text            =   "00"
         Top             =   3600
         Width           =   615
      End
      Begin VB.TextBox txtBlockData 
         Height          =   375
         Left            =   1200
         TabIndex        =   12
         Text            =   "00000000"
         Top             =   2160
         Width           =   3495
      End
      Begin VB.CommandButton bntDisableEAS 
         Caption         =   "Disable EAS"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2520
         TabIndex        =   11
         Top             =   4320
         Width           =   1335
      End
      Begin VB.CommandButton bntEnableEAS 
         Caption         =   "Enable EAS"
         Enabled         =   0   'False
         Height          =   375
         Left            =   960
         TabIndex        =   10
         Top             =   4320
         Width           =   1335
      End
      Begin VB.CommandButton bntWriteAFI 
         Caption         =   "Write AFI"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2880
         TabIndex        =   9
         Top             =   3600
         Width           =   1215
      End
      Begin VB.CommandButton bntWriteBlock 
         Caption         =   "Write Blocks"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2880
         TabIndex        =   8
         Top             =   2760
         Width           =   1335
      End
      Begin VB.CommandButton bntReadBlock 
         Caption         =   "Read Blocks"
         Enabled         =   0   'False
         Height          =   375
         Left            =   1200
         TabIndex        =   7
         Top             =   2760
         Width           =   1335
      End
      Begin VB.CommandButton bntDisconnect 
         Caption         =   "Disconnect"
         Enabled         =   0   'False
         Height          =   375
         Left            =   4320
         TabIndex        =   5
         Top             =   480
         Width           =   975
      End
      Begin VB.CommandButton bntConnect 
         Caption         =   "Connect"
         Height          =   375
         Left            =   3120
         TabIndex        =   4
         Top             =   480
         Width           =   975
      End
      Begin VB.Label Label6 
         Caption         =   "Block Cnt:"
         Height          =   375
         Left            =   240
         TabIndex        =   19
         Top             =   1680
         Width           =   855
      End
      Begin VB.Label Label5 
         Caption         =   "Start Block:"
         Height          =   255
         Left            =   240
         TabIndex        =   17
         Top             =   1200
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "Hex"
         Height          =   255
         Index           =   1
         Left            =   4800
         TabIndex        =   16
         Top             =   2280
         Width           =   495
      End
      Begin VB.Label Label4 
         Caption         =   "Hex"
         Height          =   255
         Index           =   0
         Left            =   1920
         TabIndex        =   15
         Top             =   3600
         Width           =   495
      End
      Begin VB.Label Label3 
         Caption         =   "AFI:"
         Height          =   375
         Left            =   840
         TabIndex        =   13
         Top             =   3600
         Width           =   375
      End
      Begin VB.Label Label2 
         Caption         =   "Blocks:"
         Height          =   495
         Left            =   240
         TabIndex        =   6
         Top             =   2160
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "UID:"
         Height          =   375
         Left            =   240
         TabIndex        =   3
         Top             =   480
         Width           =   495
      End
   End
   Begin VB.CommandButton bntClose 
      Caption         =   "Close"
      Enabled         =   0   'False
      Height          =   375
      Left            =   3720
      TabIndex        =   1
      Top             =   720
      Width           =   1095
   End
   Begin VB.CommandButton bntOpen 
      Caption         =   "Open"
      Height          =   375
      Left            =   3720
      TabIndex        =   0
      Top             =   240
      Width           =   1095
   End
   Begin VB.Label labTagFound 
      Caption         =   "Tag found: 0"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   120
      TabIndex        =   29
      Top             =   1560
      Width           =   2250
   End
   Begin VB.Label Label7 
      Caption         =   "COMM Type:"
      Height          =   375
      Left            =   240
      TabIndex        =   22
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub bntClose_Click()
RDR_Close (hReader) 'Close
hReader = 0 'set reader handle to NULL
bntOpen.Enabled = True
bntClose.Enabled = False
bntInventory.Enabled = False
End Sub

Private Sub bntConnect_Click()
Dim iret As Long
Dim uid() As Byte
Dim tstr As String

If hTag <> 0 Then
  MsgBox "please disconnect tag first"
  Exit Sub
End If

If cmbUID.Text = "" Then
   MsgBox "input UID please"
   Exit Sub
End If
uid = HexToBytes(cmbUID.Text)

iret = ISO15693_Connect(hReader, 1, 1, uid(0), hTag)
If iret <> 0 Then
    MsgBox "Connect fail"
Else
   bntConnect.Enabled = False
   bntDisconnect.Enabled = True
   bntReadBlock.Enabled = True
   bntWriteBlock.Enabled = True
   bntWriteAFI.Enabled = True
   bntEnableEAS.Enabled = True
   bntDisableEAS.Enabled = True
End If
End Sub

Private Sub bntConnISO14443a_Click()
Dim iret As Long
Dim uid() As Byte
Dim tstr As String

If hTag <> 0 Then
  MsgBox "please disconnect tag first"
  Exit Sub
End If

If cmbUIDISO14443a.Text = "" Then
   MsgBox "input UID please"
   Exit Sub
End If
uid = HexToBytes(cmbUIDISO14443a.Text)

iret = MFCL_Connect(hReader, 0, uid(0), hTag)
If iret <> 0 Then
    MsgBox "Connect fail"
Else
   bntConnISO14443a.Enabled = False
   bntDiscISO14443a.Enabled = True
   Command1.Enabled = True
   BntReadISO14443a.Enabled = True
   BntWriteISO14443a.Enabled = True
End If
End Sub

Private Sub bntDisableEAS_Click()
Dim iret As Integer

iret = NXPICODESLI_DisableEAS(hReader, hTag)
If iret = 0 Then
    MsgBox "Disable ok"
Else
    MsgBox "Disable fail"
End If
End Sub

Private Sub bntDiscISO14443a_Click()
Dim iret As Long
iret = RDR_TagDisconnect(hReader, hTag)
hTag = 0 ' set tag handle to null
   bntConnISO14443a.Enabled = True
   bntDiscISO14443a.Enabled = False
   Command1.Enabled = False
   BntReadISO14443a.Enabled = False
   BntWriteISO14443a.Enabled = False
End Sub

Private Sub bntDisconnect_Click()
Dim iret As Long
iret = RDR_TagDisconnect(hReader, hTag)
hTag = 0 ' set tag handle to null
bntConnect.Enabled = True
bntDisconnect.Enabled = False
bntReadBlock.Enabled = False
bntWriteBlock.Enabled = False
bntWriteAFI.Enabled = False
bntEnableEAS.Enabled = False
bntDisableEAS.Enabled = False
End Sub

Private Sub bntEnableEAS_Click()
Dim iret As Long

iret = NXPICODESLI_EableEAS(hReader, hTag)
If iret = 0 Then
    MsgBox "Enable ok"
Else
    MsgBox "Enable fail"
End If
End Sub

Private Sub bntInventory_Click()
Dim Rtn       As Long
Dim ByteUid(0 To 64) As Byte
Dim dnhReport As Long
Dim dsfid As Byte
Dim AIPtype As Long
Dim tagType As Long
Dim AntId As Long
Dim uidLen As Byte
Dim uidLenOf3m3 As Long
Dim suid As String
Dim metaFlg As Long
Dim i As Long
Dim temps As String
Dim hInvParams  As Long


listTagsFound.Clear
cmbUID.Clear
labTagFound.Caption = "Tag Found: 0"


hInvParams = RDR_CreateInvenParamSpecList()
If (hInvParams <> 0) Then
    'Enable ISO15693 inventory
    ISO15693_CreateInvenParam hInvParams, 0, 0, 0, 0
    'Enable ISO14443a inventory
    ISO14443A_CreateInvenParam hInvParams, 0
    
    'Enable ISO18000P3M3
    ISO18000p3m3_CreateInvenParam hInvParams, 0, 0, 0, 255
End If

Rtn = RDR_TagInventory(hReader, 1, 0, 0, hInvParams) 'send inventory command to reader and save tag report at the buffer
If Rtn = 0 Then
    'inventory ok ,then get tag report from buffer
    
    dnhReport = RDR_GetTagDataReport(hReader, 1) 'get first report
    Do While dnhReport <> 0
       ' Try to check it is ISO15693 tag report
       Rtn = ISO15693_ParseTagDataReport(dnhReport, AIPtype, tagType, AntId, dsfid, ByteUid(0))
       If Rtn = 0 Then
        suid = ""
        suid = BytesToHex(ByteUid, 8)
        listTagsFound.AddItem "ISO15693" + "," + suid
        cmbUID.AddItem suid
       End If
       ' Try to check it is ISO14443a tag report
       uidLen = UBound(ByteUid) + 1
       Rtn = ISO14443A_ParseTagDataReport(dnhReport, AIPtype, tagType, AntId, ByteUid(0), uidLen)
       If Rtn = 0 Then
        suid = ""
        suid = BytesToHex(ByteUid, uidLen)
        listTagsFound.AddItem "ISO14443A" + "," + suid
        cmbUIDISO14443a.AddItem suid
       End If
       'Try to check it is ISO180003M3 tag report
        uidLenOf3m3 = UBound(ByteUid) + 1
       Rtn = ISO18000p3m3_ParseTagDataReport(dnhReport, AIPtype, tagType, AntId, metaFlg, ByteUid(0), uidLenOf3m3)
       If Rtn = 0 Then
         suid = ""
         suid = BytesToHex(ByteUid, uidLenOf3m3)
         listTagsFound.AddItem "ISO18000P3M3" + "," + suid
       End If
       
       dnhReport = RDR_GetTagDataReport(hReader, 2) 'get next report
    Loop
    
End If

If hInvParams <> 0 Then
   DNODE_Destroy (hInvParams)
End If
labTagFound.Caption = "Tag Found: " + str(listTagsFound.ListCount)
If cmbUID.ListCount > 0 Then
  cmbUID.ListIndex = 0
End If

If cmbUIDISO14443a.ListCount > 0 Then
   cmbUIDISO14443a.ListIndex = 0
End If


End Sub

Private Sub bntOpen_Click()
Dim Rtn       As Long
Dim BtyStr()  As Byte
Dim ConnStr   As String
Dim DriverCnt As Integer
Dim path As String


On Error Resume Next
    
    If cmbCOMMType.ListIndex = 0 Then
       ConnStr = "RDType=RL8000;CommType=USB;AddrMode=0;SerNum=" 'USBHID open string
    Else
       ConnStr = "RDType=RL8000;CommType=COM;COMName=" + cmbCOMName.Text + ";BaudRate=38400;Frame=8E1"  'Serial open string
    End If

    Rtn = RDR_Open(StrPtr(ConnStr), hReader) 'try to open usb hid communication, and save reader handle to hReader(global variable)
    If Rtn <> 0 Then
          MsgBox "Open Fail: " & Rtn
    Else
          ' Open ok ,hReader > 0
          
          bntOpen.Enabled = False
          bntClose.Enabled = True
          bntInventory.Enabled = True
    End If

End Sub




Private Sub bntReadBlock_Click()
Dim iret As Long
Dim nBlkRead As Long
Dim buffer(64) As Byte
Dim bufSize As Long
Dim nByteRead As Long
Dim blokStr As String
Dim blockStart As Long
Dim blockCnt As Long

nByteRead = nBlkRead = 0
bufSize = UBound(buffer) + 1
blockStart = cmbStartBlk.ListIndex
blockCnt = cmbBlockCnt.ListIndex + 1
iret = ISO15693_ReadMultiBlocks(hReader, hTag, 0, blockStart, blockCnt, nBlkRead, buffer(0), bufSize, nByteRead)
If iret = 0 Then
    blokStr = BytesToHex(buffer, nByteRead)
    txtBlockData.Text = blokStr
Else
    MsgBox "Read fail"
End If
End Sub

Private Sub BntReadISO14443a_Click()
Dim iret As Long
Dim buffer(16) As Byte
Dim bufSize As Long
Dim blokStr As String
Dim blockStart As Long


bufSize = UBound(buffer) + 1
blockStart = cmbBlockAddr.ListIndex
iret = MFCL_ReadBlock(hReader, hTag, blockStart, buffer(0), bufSize)
If iret = 0 Then
    blokStr = BytesToHex(buffer, 16)
    txtBlockDataISO14443a.Text = blokStr
Else
    MsgBox "Read fail"
End If
End Sub

Private Sub bntWriteAFI_Click()
Dim iret As Long
Dim afi As Byte

afi = CByte("&H" & txtAFI.Text)
iret = ISO15693_WriteAFI(hReader, hTag, afi)
If iret = 0 Then
    MsgBox "write ok"
Else
   MsgBox "write fail"
End If
End Sub

Private Sub bntWriteBlock_Click()

Dim iret As Long

Dim startBlk As Long
Dim BlkNum As Long
Dim blkDataBuff() As Byte
Dim nSize As Long

startBlk = cmbStartBlk.ListIndex
BlkNum = cmbBlockCnt.ListIndex + 1
blkDataBuff = HexToBytes(txtBlockData.Text)
nSize = UBound(blkDataBuff) + 1
iret = ISO15693_WriteMultipleBlocks(hReader, hTag, startBlk, BlkNum, blkDataBuff(0), nSize)
If iret = 0 Then
    MsgBox "write ok"
Else
    MsgBox "write fail"
End If
End Sub

Private Sub BntWriteISO14443a_Click()
Dim iret As Long

Dim startBlk As Long
Dim blkDataBuff() As Byte
Dim nSize As Long

startBlk = cmbBlockAddr.ListIndex
blkDataBuff = HexToBytes(txtBlockDataISO14443a.Text)
nSize = UBound(blkDataBuff) + 1
iret = MFCL_WriteBlock(hReader, hTag, startBlk, blkDataBuff(0))
If iret = 0 Then
    MsgBox "write ok"
Else
    MsgBox "write fail"
End If
End Sub

Private Sub cmbBlockCnt_Change()
Dim idx As Integer
Dim i As Integer
idx = cmbBlockCnt.ListIndex
For i = 0 To idx
   txtBlockData.Text = txtBlockData.Text + "00000000"
Next

End Sub

Private Sub Command1_Click()
Dim iret As Long
Dim key() As Byte
Dim keyType As Byte
Dim blockAddr As Byte
keyType = cmbKeyType.ListIndex
blockAddr = cmbBlockAddr.ListIndex

key = HexToBytes(txtKey.Text)
iret = MFCL_Authenticate(hReader, hTag, blockAddr, keyType, key(0))
If iret = 0 Then

    MsgBox "ok"
Else

   MsgBox "fail"
End If
End Sub

Private Sub Command2_Click()

End Sub

Private Sub Form_Load()
    Dim i As Integer
    Dim nCnt As Long
    Dim iret As Long
    Dim nameBuf As String * 64
    Dim comName As String
    hReader = 0  'set reader handle to NULL
    hTag = 0 ' set tag handle to null
    RDR_LoadReaderDrivers (StrPtr(".\"))   'load rfidlib_ANM201.dll or other drivers
    
    For i = 0 To 27
      cmbStartBlk.AddItem str(i)
    Next
    cmbStartBlk.ListIndex = 0
    For i = 1 To 16
      cmbBlockCnt.AddItem str(i)
    Next
    cmbBlockCnt.ListIndex = 0
    
    cmbCOMMType.AddItem "USB"
    cmbCOMMType.AddItem "COM"
    cmbCOMMType.ListIndex = 0
    
    nCnt = COMPort_Enum()
    For i = 0 To (nCnt - 1)
       iret = COMPort_GetEnumItem(i, nameBuf, 64)
       If iret = 0 Then
          comName = StrConv(nameBuf, vbFromUnicode)
          cmbCOMName.AddItem comName
       End If
    Next
    If nCnt > 0 Then
        cmbCOMName.ListIndex = 0
    End If
    
    cmbKeyType.AddItem "Key A"
    cmbKeyType.AddItem "Key B"
    cmbKeyType.ListIndex = 0
    
    For i = 0 To 63
       cmbBlockAddr.AddItem str(i)
    Next
    cmbBlockAddr.ListIndex = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
If hReader <> 0 Then
   MsgBox "please close reader before exit"
   Cancel = -1
End If
End Sub
