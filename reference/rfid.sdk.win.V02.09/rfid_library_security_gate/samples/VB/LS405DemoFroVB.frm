VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Form1"
   ClientHeight    =   7170
   ClientLeft      =   -7275
   ClientTop       =   -2565
   ClientWidth     =   8850
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7170
   ScaleWidth      =   8850
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox RecordText 
      Height          =   2655
      Left            =   720
      MultiLine       =   -1  'True
      TabIndex        =   5
      Top             =   3960
      Width           =   5895
   End
   Begin VB.CommandButton GetRecord 
      Caption         =   "Get record"
      Height          =   495
      Left            =   6840
      TabIndex        =   4
      Top             =   3960
      Width           =   1455
   End
   Begin VB.CommandButton Close 
      Caption         =   "Close"
      Height          =   375
      Left            =   5400
      TabIndex        =   3
      Top             =   360
      Width           =   1095
   End
   Begin VB.CommandButton Open 
      Caption         =   "Open"
      Height          =   375
      Left            =   3840
      TabIndex        =   2
      Top             =   360
      Width           =   1095
   End
   Begin VB.TextBox IpText 
      Height          =   285
      Left            =   1320
      TabIndex        =   1
      Text            =   "192.168.1.222"
      Top             =   360
      Width           =   2055
   End
   Begin VB.Frame Frame1 
      Caption         =   "Record"
      Height          =   3375
      Left            =   360
      TabIndex        =   6
      Top             =   3600
      Width           =   8175
   End
   Begin VB.Frame Frame2 
      Caption         =   "Command"
      Height          =   2295
      Left            =   360
      TabIndex        =   7
      Top             =   960
      Width           =   8175
      Begin VB.CommandButton SetOutput 
         Caption         =   "Set Output"
         Height          =   495
         Left            =   4800
         TabIndex        =   13
         Top             =   1320
         Width           =   1575
      End
      Begin VB.CommandButton getSysTime 
         Caption         =   "Get time"
         Height          =   375
         Left            =   2520
         TabIndex        =   12
         Top             =   1320
         Width           =   1575
      End
      Begin VB.CommandButton setSysTime 
         Caption         =   "Set time"
         Height          =   375
         Left            =   480
         TabIndex        =   11
         Top             =   1320
         Width           =   1455
      End
      Begin VB.CommandButton reverseDir 
         Caption         =   "Reverse direction"
         Height          =   375
         Left            =   4800
         TabIndex        =   10
         Top             =   480
         Width           =   1695
      End
      Begin VB.CommandButton ResetFlow 
         Caption         =   "Reset flow of people"
         Height          =   375
         Left            =   2520
         TabIndex        =   9
         Top             =   480
         Width           =   1935
      End
      Begin VB.CommandButton GetFlow 
         Caption         =   "Get flow of people"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   480
         Width           =   1815
      End
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "IP addr:"
      Height          =   195
      Left            =   720
      TabIndex        =   0
      Top             =   360
      Width           =   555
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim hr As Long

Private Sub Close_Click()
If hr <> 0 Then
iret = RDR_Close(hr)
If iret = 0 Then
Me.Open.Enabled = True
Me.Close.Enabled = False
Me.IpText.Enabled = True
Me.GetRecord.Enabled = False
Me.RecordText.Enabled = False
Me.GetFlow.Enabled = False
Me.ResetFlow.Enabled = False
Me.reverseDir.Enabled = False
Me.setSysTime.Enabled = False
Me.getSysTime.Enabled = False
hr = 0
End If
End If
End Sub

Sub form_load()
Dim iret As Integer
Me.Open.Enabled = True
Me.Close.Enabled = False
Me.IpText.Enabled = True
Me.GetRecord.Enabled = False
Me.RecordText.Enabled = False
Me.GetFlow.Enabled = False
Me.ResetFlow.Enabled = False
Me.reverseDir.Enabled = False
Me.setSysTime.Enabled = False
Me.getSysTime.Enabled = False
iret = RDR_LoadReaderDrivers(StrPtr(".\"))
iret = RDR_GetLoadedReaderDriverCount()
hr = 0
End Sub

Sub Form_resize()
   Me.Move Me.Left + Me.Width, Me.Top + Me.Height
End Sub

Private Sub GetFlow_Click()
Dim m_in As Long
Dim m_out As Long
iret = LSG_CmdGetCurrentFlowOfPeople(hr, m_in, m_out)
If iret = 0 Then
    Dim sret As String
    sret = "In:" + Str(m_in) + ";" + "Out:" + Str(m_out)
    MsgBox (sret)
Else
    MsgBox ("Fail")
End If
End Sub

Private Sub GetRecord_Click()
Dim nCount As Long
Dim hReport As Long
Dim mFlg As Byte
Dim sRecord As String

mFlg = 0

Const LOOPCNT = 5  'Loop count for a time

For i = 1 To LOOPCNT
    iret = LSG_CmdGetReports(hr, mFlg, 10)
    
    If iret <> 0 Then
        GoTo LOOP_END
    End If
    
    nCount = RDR_GetTagDataReportCount(hr)
    If nCount = 0 Then
        GoTo LOOP_END
    End If
    
    hReport = RDR_GetTagDataReport(hr, RFID_SEEK_FIRST)
    Do While hReport <> 0
        Dim slData As String
        Dim mData As Long
        Dim dir As Byte
        Dim m_time(0 To 5) As Byte
        slData = String(64, 0)
        iret = LSG_ParseSCEventData(hReport, StrPtr(slData), 64, dir, m_time(0))
        If iret = 0 Then
            sRecord = sRecord + Left(slData, 16) + "\"
        End If
        hReport = RDR_GetTagDataReport(hr, RFID_SEEK_NEXT)
        mFlg = 1
    Loop
Next i
LOOP_END:
Me.RecordText.Text = sRecord
End Sub

Private Sub getSysTime_Click()
iret = LSG_CmdGetSystemTime(hr, m_year, m_mon, m_day, m_hour, m_min, m_sec)
If iret = 0 Then
sTime = Str(m_year) + "-" + Str(m_mon) + "-" + Str(m_day) + " " + Str(m_hour) + ":" + Str(m_min) + ":" + Str(m_sec)
MsgBox (sTime)
Else
MsgBox ("Fail")
End If
End Sub

Private Sub Open_Click()
Dim ConnStr As String
Dim iret As Integer
ConnStr = "RDType=LSG405;CommType=NET;RemoteIP=" + IpText.Text + ";RemotePort=6012;LocalIP="
iret = RDR_Open(StrPtr(ConnStr), hr)
If iret = 0 Then
Me.Open.Enabled = False
Me.Close.Enabled = True
Me.IpText.Enabled = False
Me.GetRecord.Enabled = True
Me.RecordText.Enabled = True
Me.GetFlow.Enabled = True
Me.ResetFlow.Enabled = True
Me.reverseDir.Enabled = True
Me.setSysTime.Enabled = True
Me.getSysTime.Enabled = True
End If

End Sub

Private Sub ResetFlow_Click()
iret = LSG_CmdResetFlowOfPeople(hr, 3)
If iret = 0 Then
MsgBox ("Success")
Else
MsgBox ("fail")
End If
End Sub

Private Sub reverseDir_Click()
iret = LSG_CmdReverseDirection(hr)
If iret = 0 Then
MsgBox ("Success")
Else
MsgBox ("fail")
End If
End Sub

Private Sub SetOutput_Click()
Dim dnOutputOper As Long
Dim activeDuration As Byte
Dim outFrequency As Byte
Dim outActiveDuration As Byte
Dim iret As Integer
activeDuration = 1
outFrequency = 2
outActiveDuration = 1
dnOutputOper = RDR_CreateSetOutputOperations()
iret = RDR_AddOneOutputOperation(dnOutputOper, 1, 3, outFrequency, activeDuration * 100, outActiveDuration * 100)
If iret <> 0 Then
    GoTo LOOP_END
End If

iret = RDR_SetOutput(hr, dnOutputOper)

If iret = 0 Then
    MsgBox ("Success")
Else
    MsgBox ("fail")
End If

LOOP_END:
If dnOutputOper <> 0 Then
    DNODE_Destroy (dnOutputOper) ' The dnOutputOper must be destroyed here if the value is not null.
End If

End Sub

Private Sub setSysTime_Click()
m_year = year(Now)
m_mon = month(Now)
m_day = day(Now)
m_hour = hour(Now)
m_min = minute(Now)
m_sec = second(Now)
iret = LSG_CmdSetSystemTime(hr, m_year, m_mon, m_day, m_hour, m_min, m_sec)
If iret = 0 Then
MsgBox ("Success")
Else
MsgBox ("fail")
End If
End Sub
