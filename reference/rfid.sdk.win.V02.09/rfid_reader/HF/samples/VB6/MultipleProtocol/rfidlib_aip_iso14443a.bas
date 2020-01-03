Attribute VB_Name = "rfidlib_aip_iso14443a"
Option Explicit








Public Declare Function ISO14443A_CreateInvenParam Lib "rfidlib_aip_iso14443a.dll" (ByVal hInvenParamSpecList As Long, ByVal AntennaID As Byte) As Long
Public Declare Function ISO14443A_ParseTagDataReport Lib "rfidlib_aip_iso14443a.dll" (ByVal hTagReport As Long, ByRef aip_id As Long, ByRef tag_id As Long, ByRef ant_id As Long, ByRef uid As Byte, ByRef uidLen As Byte) As Long
Public Declare Function MFCL_Connect Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal tagType As Long, ByRef uid As Byte, ByRef ht As Long) As Long
Public Declare Function MFCL_Authenticate Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte, ByVal keyType As Byte, ByRef key As Byte) As Long
Public Declare Function MFCL_ReadBlock Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte, ByRef blkData As Byte, ByVal nSize As Long) As Long
Public Declare Function MFCL_WriteBlock Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte, ByRef blkData As Byte) As Long
Public Declare Function MFCL_FormatValueBlock Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte, ByVal initValue As Long) As Long
Public Declare Function MFCL_Increment Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte, ByVal val As Long) As Long
Public Declare Function MFCL_Decrement Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte, ByVal val As Long) As Long
Public Declare Function MFCL_Transfer Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte) As Long
Public Declare Function MFCL_Restore Lib "rfidlib_aip_iso14443a.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Byte) As Long

