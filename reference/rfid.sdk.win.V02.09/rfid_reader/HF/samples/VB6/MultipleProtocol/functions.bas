Attribute VB_Name = "functions"
Option Explicit

Public Const GENERIC_READ = &H80000000
Public Const GENERIC_WRITE = &H40000000
Public Const FILE_SHARE_READ = &H1
Public Const FILE_SHARE_WRITE = &H2
Public Const OPEN_EXISTING = 3
Public Const FILE_FLAG_BACKUP_SEMANTICS = &H2000000
Public Const INVALID_HANDLE_VALUE = -1

Public Type FILETIME
    dwLowDateTime   As Long
    dwHighDateTime  As Long
End Type

Public Type SECURITY_ATTRIBUTES
    nLength                 As Long
    lpSecurityDescriptor    As Long
    bInheritHandle          As Long
End Type

Public Type WIN32_FIND_DATA
    dwFileAttributes As Long
    ftCreationTime As FILETIME
    ftLastAccessTime As FILETIME
    ftLastWriteTime As FILETIME
    nFileSizeHigh As Long
    nFileSizeLow As Long
    dwReserved0 As Long
    dwReserved1 As Long
    cFileName As String * 256
    cAlternate As String * 14
End Type

Public Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Public Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

Public Const CP_UTF8 = 65001
Public Declare Function WideCharToMultiByte Lib "kernel32" (ByVal CodePage As Long, ByVal dwFlags As Long, ByVal lpWideCharStr As Long, ByVal cchWideChar As Long, ByVal lpMultiByteStr As Long, ByVal cchMultiByte As Long, ByVal lpDefaultChar As Long, ByVal lpUsedDefaultChar As Long) As Long
Public Declare Function MultiByteToWideChar Lib "kernel32" (ByVal CodePage As Long, ByVal dwFlags As Long, ByVal lpMultiByteStr As Long, ByVal cbMultiByte As Long, ByVal lpWideCharStr As Long, ByVal cchWideChar As Long) As Long

Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)



Public hReader  As Long
Public hTag As Long
Public HexMatrix(15, 15) As Byte



Public Function FileExists(sSource As String) As Boolean
On Error Resume Next
    'Thorogh FileExists function
    If Right(sSource, 2) = ":\" Then
        Dim allDrives As String
        allDrives = Space$(64)
        Call GetLogicalDriveStrings(Len(allDrives), allDrives)
        FileExists = InStr(1, allDrives, Left(sSource, 1), 1) > 0
        Exit Function
    Else
        If Not sSource = "" Then
            Dim WFD As WIN32_FIND_DATA
            Dim hFile As Long
            hFile = FindFirstFile(sSource, WFD)
            FileExists = hFile <> INVALID_HANDLE_VALUE
            Call FindClose(hFile)
        Else
            FileExists = False
        End If
    End If
End Function

Public Sub AddToLog(LogData As String, Optional Opt As Long = 0)
Dim FF As Integer
On Error Resume Next
    
    If Not FileExists(App.path & "\LogData") Then MkDir App.path & "\LogData"
    
    Select Case Opt
      Case 0 ' Error LogData
           FF = FreeFile
           Open App.path & "\LogData\" & App.EXEName & ".log" For Append As #FF
           Print #FF, Now, LogData: Close #FF
      Case -1 'logdata ªË¡¶
           If FileExists(App.path & "\LogData\" & App.EXEName & ".log") Then
              Name App.path & "\LogData\" & App.EXEName & ".log" As App.path & "\LogData\" & Format(Now, "yymmdd-hhmmss") & ".bak"
              'Call FileCopy(App.path & "\LogData\" & App.ExeName & ".log", App.path & "\LogData\" & format(Now, "yymmdd-hhmmss") & ".bak")
              'Kill App.path & "\LogData\" & App.ExeName & ".log"
           End If
      Case Else
        
    End Select
    
End Sub



Public Function BytesToHex(bits() As Byte, ByVal size As Integer) As String
    Dim i As Long
    Dim b
    Dim s As String

    If size = 0 Then
        For Each b In bits
            If b < 16 Then
                s = s & "0" & Hex(b)
            Else
                s = s & Hex(b)
            End If
        Next
    Else
        For i = 0 To size - 1
            b = bits(i)
            If b < 16 Then
                s = s & "0" & Hex(b)
            Else
                s = s & Hex(b)
            End If
        Next
    End If
    BytesToHex = s
End Function

Public Function HexToBytes(str As String) As Byte()
    Dim rst() As Byte
    Dim i As Long, j As Long
    i = Len(str)
    j = i \ 2 - 1
    ReDim rst(j)
    For i = 0 To j
        rst(i) = CByte("&H" & Mid$(str, i + i + 1, 2))
    Next
    HexToBytes = rst()
End Function

