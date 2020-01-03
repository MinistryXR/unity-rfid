Attribute VB_Name = "rfidlib_aip_iso18000p3m3"
Option Explicit


Public Declare Function ISO18000p3m3_CreateInvenParam Lib "rfidlib_aip_iso18000p3m3.dll" (ByVal hInvenParamSpecList As Long, ByVal AntennaID As Byte, ByVal sel As Byte, ByVal session As Byte, ByVal Q As Byte) As Long

Public Declare Function ISO18000p3m3_ParseTagDataReport Lib "rfidlib_aip_iso18000p3m3" (ByVal hTagReport As Long, ByRef aip_id As Long, ByRef tag_id As Long, ByRef ant_id As Long, ByRef metaFlags As Long, ByRef tagdata As Byte, ByRef tagDataLen As Long) As Long
