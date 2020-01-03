VERSION 5.00
Begin VB.Form MainForm 
   Caption         =   "ISO15693 reader sample"
   ClientHeight    =   7170
   ClientLeft      =   6135
   ClientTop       =   4890
   ClientWidth     =   9555
   LinkTopic       =   "Form1"
   ScaleHeight     =   7170
   ScaleWidth      =   9555
   Begin VB.Frame Frame2 
      Caption         =   "Serial"
      Height          =   735
      Left            =   120
      TabIndex        =   27
      Top             =   600
      Width           =   3015
      Begin VB.ComboBox cmbCOMName 
         Height          =   315
         Left            =   1080
         TabIndex        =   29
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label8 
         Caption         =   "COM Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   28
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.ComboBox cmbCOMMType 
      Height          =   315
      Left            =   1320
      Style           =   2  'Dropdown List
      TabIndex        =   26
      Top             =   240
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Height          =   5535
      Left            =   120
      TabIndex        =   2
      Top             =   1320
      Width           =   9375
      Begin VB.ComboBox cmbUID 
         Height          =   315
         Left            =   4320
         TabIndex        =   24
         Top             =   840
         Width           =   2415
      End
      Begin VB.ComboBox cmbBlockCnt 
         Height          =   315
         Left            =   4800
         Style           =   2  'Dropdown List
         TabIndex        =   23
         Top             =   1920
         Width           =   1215
      End
      Begin VB.ComboBox cmbStartBlk 
         Height          =   315
         Left            =   4800
         Style           =   2  'Dropdown List
         TabIndex        =   21
         Top             =   1440
         Width           =   1215
      End
      Begin VB.TextBox txtAFI 
         Height          =   375
         Left            =   4440
         TabIndex        =   17
         Text            =   "00"
         Top             =   3600
         Width           =   615
      End
      Begin VB.TextBox txtBlockData 
         Height          =   375
         Left            =   4560
         TabIndex        =   15
         Text            =   "00000000"
         Top             =   2520
         Width           =   3495
      End
      Begin VB.CommandButton bntDisableEAS 
         Caption         =   "Disable EAS"
         Enabled         =   0   'False
         Height          =   375
         Left            =   5880
         TabIndex        =   14
         Top             =   4320
         Width           =   1335
      End
      Begin VB.CommandButton bntEnableEAS 
         Caption         =   "Enable EAS"
         Enabled         =   0   'False
         Height          =   375
         Left            =   4320
         TabIndex        =   13
         Top             =   4320
         Width           =   1335
      End
      Begin VB.CommandButton bntWriteAFI 
         Caption         =   "Write AFI"
         Enabled         =   0   'False
         Height          =   375
         Left            =   6000
         TabIndex        =   12
         Top             =   3600
         Width           =   1335
      End
      Begin VB.CommandButton bntWriteBlock 
         Caption         =   "Write Blocks"
         Enabled         =   0   'False
         Height          =   375
         Left            =   6000
         TabIndex        =   11
         Top             =   3000
         Width           =   1335
      End
      Begin VB.CommandButton bntReadBlock 
         Caption         =   "Read Blocks"
         Enabled         =   0   'False
         Height          =   375
         Left            =   4440
         TabIndex        =   10
         Top             =   3000
         Width           =   1335
      End
      Begin VB.CommandButton bntDisconnect 
         Caption         =   "Disconnect"
         Enabled         =   0   'False
         Height          =   375
         Left            =   8040
         TabIndex        =   8
         Top             =   840
         Width           =   975
      End
      Begin VB.CommandButton bntConnect 
         Caption         =   "Connect"
         Height          =   375
         Left            =   6840
         TabIndex        =   7
         Top             =   840
         Width           =   975
      End
      Begin VB.CommandButton bntInventory 
         Caption         =   "Inventory"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2880
         TabIndex        =   5
         Top             =   480
         Width           =   1095
      End
      Begin VB.ListBox listTagsFound 
         Height          =   2985
         Left            =   240
         TabIndex        =   3
         Top             =   960
         Width           =   3015
      End
      Begin VB.Label Label6 
         Caption         =   "Block Cnt:"
         Height          =   375
         Left            =   3840
         TabIndex        =   22
         Top             =   1920
         Width           =   855
      End
      Begin VB.Label Label5 
         Caption         =   "Start Block:"
         Height          =   255
         Left            =   3840
         TabIndex        =   20
         Top             =   1440
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "Hex"
         Height          =   255
         Index           =   1
         Left            =   8160
         TabIndex        =   19
         Top             =   2640
         Width           =   495
      End
      Begin VB.Label Label4 
         Caption         =   "Hex"
         Height          =   255
         Index           =   0
         Left            =   5160
         TabIndex        =   18
         Top             =   3720
         Width           =   495
      End
      Begin VB.Label Label3 
         Caption         =   "AFI:"
         Height          =   375
         Left            =   3960
         TabIndex        =   16
         Top             =   3720
         Width           =   375
      End
      Begin VB.Label Label2 
         Caption         =   "Blocks:"
         Height          =   495
         Left            =   3600
         TabIndex        =   9
         Top             =   2520
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "UID:"
         Height          =   375
         Left            =   3840
         TabIndex        =   6
         Top             =   960
         Width           =   495
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
         Left            =   240
         TabIndex        =   4
         Top             =   480
         Width           =   2250
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
   Begin VB.Label Label7 
      Caption         =   "COMM Type:"
      Height          =   375
      Left            =   240
      TabIndex        =   25
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

Private Sub bntDisableEAS_Click()
Dim iret As Integer

iret = NXPICODESLI_DisableEAS(hReader, hTag)
If iret = 0 Then
    MsgBox "Disable ok"
Else
    MsgBox "Disable fail"
End If
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
Dim ByteUid(0 To 7) As Byte
Dim dnhReport As Long
Dim dsfid As Byte
Dim AIPtype As Long
Dim tagType As Long
Dim AntId As Long
'Dim uid(8) As Byte
Dim suid As String
Dim i As Long
Dim temps As String


listTagsFound.Clear
cmbUID.Clear
labTagFound.Caption = "Tag Found: 0"

Rtn = RDR_TagInventory(hReader, 1, 0, 0, 0) 'send inventory command to reader and save tag report at the buffer
If Rtn = 0 Then
    'inventory ok ,then get tag report from buffer
    
    dnhReport = RDR_GetTagDataReport(hReader, 1) 'get first report
    Do While dnhReport <> 0
       Rtn = ISO15693_ParseTagDataReport(dnhReport, AIPtype, AntId, AntId, dsfid, ByteUid(0))
       If Rtn = 0 Then
        suid = ""

        suid = BytesToHex(ByteUid, 8)
        listTagsFound.AddItem suid
        cmbUID.AddItem suid
       End If
       
       dnhReport = RDR_GetTagDataReport(hReader, 2) 'get next report
    Loop
    
End If
labTagFound.Caption = "Tag Found: " + str(listTagsFound.ListCount)
If cmbUID.ListCount > 0 Then
  cmbUID.ListIndex = 0
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
       ConnStr = "RDType=M201;CommType=USB;AddrMode=0;SerNum=" 'M201 open string
    Else
       ConnStr = "RDType=M201;CommType=COM;COMName=" + cmbCOMName.Text + ";BaudRate=38400;Frame=8E1"
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




Private Sub Command1_Click()

End Sub

Private Sub Command2_Click()

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

Private Sub cmbBlockCnt_Change()
Dim idx As Integer
Dim i As Integer
idx = cmbBlockCnt.ListIndex
For i = 0 To idx
   txtBlockData.Text = txtBlockData.Text + "00000000"
Next

End Sub

Private Sub Form_Load()
    Dim i As Integer
    Dim nCnt As Long
    Dim iret As Long
    Dim nameBuf As String * 64
    Dim comName As String
    hReader = 0  'set reader handle to NULL
    hTag = 0 ' set tag handle to null
    iret = RDR_LoadReaderDrivers(StrPtr(".\"))
    iret = RDR_GetLoadedReaderDriverCount()
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
    
End Sub

