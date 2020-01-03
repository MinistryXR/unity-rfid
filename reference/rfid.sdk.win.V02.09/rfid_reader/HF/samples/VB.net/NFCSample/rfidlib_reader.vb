Imports System.Text
Namespace RFIDLIB
    Class rfidlib_reader

        Public Declare Function RDR_LoadReaderDrivers Lib "rfidlib_reader.dll" (ByVal path As String) As Integer
        Public Declare Function RDR_GetLoadedReaderDriverCount Lib "rfidlib_reader.dll" () As UInt32
        Public Declare Function RDR_Open Lib "rfidlib_reader.dll" (ByVal ConnStr As String, ByRef RdHwnd As UIntPtr) As Integer
        Public Declare Function RDR_CreateInvenParamSpecList Lib "rfidlib_reader.dll" () As UIntPtr
        Public Declare Function RDR_GetLoadedReaderDriverOpt Lib "rfidlib_reader.dll" (ByVal idx As UInt32, ByVal opt As String, ByVal valueBuffer As StringBuilder, ByRef nSize As UInt32) As Integer

        Public Declare Function RDR_Close Lib "rfidlib_reader.dll" (ByVal RdHwnd As UIntPtr) As Long
        Public Declare Function RDR_TagInventory Lib "rfidlib_reader.dll" (ByVal RdHwnd As UIntPtr, ByVal AIType As Byte, ByVal AntennaCount As Byte, ByVal AntennaIDs As Byte(), ByVal InvenParamSpecList As UIntPtr) As Integer
        Public Declare Function RDR_GetTagDataReport Lib "rfidlib_reader.dll" (ByVal RdHwnd As UIntPtr, ByVal pos As Byte) As UIntPtr
        Public Declare Function RDR_TagDisconnect Lib "rfidlib_reader.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr) As Integer

        Public Declare Function HID_Enum Lib "rfidlib_reader.dll" (ByVal DevId As String) As Long
        Public Declare Function HID_GetEnumItem Lib "rfidlib_reader.dll" (ByVal indx As Long, ByVal infType As Byte, ByVal infBuffer As StringBuilder, ByRef nSize As Long) As Long
        Public Declare Function COMPort_Enum Lib "rfidlib_reader.dll" () As Long
        Public Declare Function COMPort_GetEnumItem Lib "rfidlib_reader.dll" (ByVal idx As UInt32, ByVal nameBuf As StringBuilder, ByVal nSize As Long) As Long

        Public Declare Function RDR_GetAIPTypeName Lib "rfidlib_reader.dll" (ByVal hr As UIntPtr, ByVal AIP_ID As UInt32, ByVal nameBuf As StringBuilder, ByRef nSize As UInt32) As Integer

        Public Declare Function RDR_GetTagTypeName Lib "rfidlib_reader.dll" (ByVal hr As UIntPtr, ByVal AIP_ID As UInt32, ByVal TAG_ID As UInt32, ByVal nameBuf As StringBuilder, ByRef nSize As UInt32) As Integer
        Public Declare Function DNODE_Destroy Lib "rfidlib_reader.dll" (ByVal dn As UIntPtr) As Integer
        Public Declare Function RDR_SetCommuImmeTimeout Lib "rfidlib_reader.dll" (ByVal hr As UIntPtr) As Integer
        Public Declare Function RDR_ResetCommuImmeTimeout Lib "rfidlib_reader.dll" (ByVal hr As UIntPtr) As Integer
        Public Declare Function RDR_GetReaderInfor Lib "rfidlib_reader.dll" (ByVal hr As UIntPtr, ByVal Type As [Byte], ByVal buffer As StringBuilder, ByRef nSize As UInt32) As Integer
    End Class
End Namespace

