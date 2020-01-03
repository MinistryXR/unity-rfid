Attribute VB_Name = "rfidlib_aip_iso15683"
Option Explicit
















Public Declare Function ISO15693_CreateInvenParam Lib "rfidlib_aip_iso15693.dll" (ByVal hInvenParamSpecList As Long, ByVal AntennaID As Byte, ByVal en_afi As Byte, ByVal afi As Byte, ByVal slot_type As Byte) As Long
Public Declare Function ISO15693_ParseTagDataReport Lib "rfidlib_aip_iso15693.dll" (ByVal hTagReport As Long, ByRef aip_id As Long, ByRef tag_id As Long, ByRef ant_id As Long, ByRef dsfid As Byte, ByRef uid As Byte) As Long
Public Declare Function ISO15693_Connect Lib "rfidlib_aip_iso15693.dll" (ByVal hr As Long, ByVal tagType As Long, ByVal address_mode As Byte, ByRef uid As Byte, ByRef ht As Long) As Long

Public Declare Function ISO15693_ReadMultiBlocks Lib "rfidlib_aip_iso15693.dll" (ByVal RdHwnd As Long, ByVal hTag As Long, ByVal readSecSta As Byte, ByVal blkAddr As Long, ByVal numOfBlksToRead As Long, ByRef numOfBlksRead As Long, ByRef bufBlocks As Byte, ByVal nSize As Long, ByRef bytesBlkDatRead As Long) As Long
Public Declare Function ISO15693_WriteMultipleBlocks Lib "rfidlib_aip_iso15693.dll" (ByVal hr As Long, ByVal ht As Long, ByVal blkAddr As Long, ByVal numOfBlks As Long, ByRef newBlksData As Byte, ByVal bytesToWrite As Long) As Long
Public Declare Function ISO15693_WriteAFI Lib "rfidlib_aip_iso15693.dll" (ByVal hr As Long, ByVal ht As Long, ByVal afi As Byte) As Long
Public Declare Function NXPICODESLI_EableEAS Lib "rfidlib_aip_iso15693.dll" (ByVal hr As Long, ByVal ht As Long) As Long
Public Declare Function NXPICODESLI_DisableEAS Lib "rfidlib_aip_iso15693.dll" (ByVal hr As Long, ByVal ht As Long) As Long
