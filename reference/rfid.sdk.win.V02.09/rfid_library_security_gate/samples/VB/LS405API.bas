Attribute VB_Name = "Module1"
Public Declare Function RDR_LoadReaderDrivers Lib "rfidlib_reader.dll" (ByVal path As Long) As Long
Public Declare Function RDR_GetLoadedReaderDriverCount Lib "rfidlib_reader.dll" () As Integer
Public Declare Function RDR_Open Lib "rfidlib_reader.dll" (ByVal ConnStr As Long, ByRef RdHwnd As Long) As Long
Public Declare Function RDR_Close Lib "rfidlib_reader.dll" (ByVal hr As Long) As Integer
Public Declare Function RDR_GetReaderLastReturnError Lib "rfidlib_reader.dll" (ByVal hr As Long) As Integer
Public Declare Function RDR_GetTagDataReport Lib "rfidlib_reader.dll" (ByVal hr As Long, ByVal Seekpos As Byte) As Long
Public Declare Function RDR_GetTagDataReportCount Lib "rfidlib_reader.dll" (ByVal hr As Long) As Long

Public Declare Function RDR_CreateSetOutputOperations Lib "rfidlib_reader.dll" () As Long
Public Declare Function RDR_AddOneOutputOperation Lib "rfidlib_reader.dll" (ByVal hOperas As Long, ByVal outNo As Byte, ByVal outMode As Byte, ByVal outFrequency As Long, ByVal outActiveDuration As Long, ByVal outInactiveDuration As Long) As Integer
Public Declare Function RDR_SetOutput Lib "rfidlib_reader.dll" (ByVal hr As Long, ByVal outputOpers As Long) As Integer
Public Declare Function DNODE_Destroy Lib "rfidlib_reader.dll" (ByVal hr As Long) As Integer

Public Declare Function LSG_CmdGetReports Lib "rfidlib_LSGate.dll" (ByVal hr As Long, ByVal Flag As Byte, ByVal recordsToGet As Byte) As Integer
Public Declare Function LSG_ParseSCEventData Lib "rfidlib_LSGate.dll" (ByVal hr As Long, ByVal slData As Long, ByVal nSize As Long, ByRef dir As Byte, ByRef m_time As Byte) As Integer
Public Declare Function LSG_CmdGetCurrentFlowOfPeople Lib "rfidlib_LSGate.dll" (ByVal hr As Long, ByRef inFlow As Long, ByRef outFlow As Long) As Integer
Public Declare Function LSG_CmdResetFlowOfPeople Lib "rfidlib_LSGate.dll" (ByVal hr As Long, ByVal mFlg As Byte) As Integer
Public Declare Function LSG_CmdReverseDirection Lib "rfidlib_LSGate.dll" (ByVal hr As Long) As Integer
Public Declare Function LSG_CmdGetSystemTime Lib "rfidlib_LSGate.dll" (ByVal hr As Long, ByRef year As Long, ByRef month As Byte, ByRef day As Byte, ByRef hour As Byte, ByRef minute As Byte, ByRef second As Byte) As Integer
Public Declare Function LSG_CmdSetSystemTime Lib "rfidlib_LSGate.dll" (ByVal hr As Long, ByVal year As Long, ByVal month As Byte, ByVal day As Byte, ByVal hour As Byte, ByVal minute As Byte, ByVal second As Byte) As Integer
Public Const RFID_SEEK_FIRST = 1
Public Const RFID_SEEK_NEXT = 2
