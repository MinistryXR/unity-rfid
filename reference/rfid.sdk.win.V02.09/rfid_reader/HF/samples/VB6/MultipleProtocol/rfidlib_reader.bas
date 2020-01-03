Attribute VB_Name = "rfidlib_reader"

Option Explicit

















Public Declare Function RDR_LoadReaderDrivers Lib "rfidlib_reader.dll" (ByVal path As Long) As Long
Public Declare Function RDR_GetLoadedReaderDriverCount Lib "rfidlib_reader.dll" () As Integer
Public Declare Function RDR_Open Lib "rfidlib_reader.dll" (ByVal ConnStr As Long, ByRef RdHwnd As Long) As Long
Public Declare Function RDR_CreateInvenParamSpecList Lib "rfidlib_reader.dll" () As Long

Public Declare Function RDR_Close Lib "rfidlib_reader.dll" (ByVal RdHwnd As Long) As Long
Public Declare Function RDR_TagInventory Lib "rfidlib_reader.dll" (ByVal RdHwnd As Long, ByVal AIType As Byte, ByVal AntennaCount As Byte, ByVal AntennaIDs As Byte, ByVal InvenParamSpecList As Long) As Long
Public Declare Function RDR_GetTagDataReport Lib "rfidlib_reader.dll" (ByVal RdHwnd As Long, ByVal pos As Byte) As Long
Public Declare Function RDR_TagDisconnect Lib "rfidlib_reader.dll" (ByVal hr As Long, ByVal ht As Long) As Long

Public Declare Function HID_Enum Lib "rfidlib_reader.dll" (ByVal DevId As String) As Long
Public Declare Function HID_GetEnumItem Lib "rfidlib_reader.dll" (ByVal indx As Long, ByVal infType As Byte, ByVal infBuffer As String, ByRef nSize As Long) As Long
Public Declare Function COMPort_Enum Lib "rfidlib_reader.dll" () As Long
Public Declare Function COMPort_GetEnumItem Lib "rfidlib_reader.dll" (ByVal idx As Long, ByVal nameBuf As String, ByVal nSize As Long) As Long



Public Declare Function DNODE_Destroy Lib "rfidlib_reader.dll" (ByVal dn As Long) As Long
