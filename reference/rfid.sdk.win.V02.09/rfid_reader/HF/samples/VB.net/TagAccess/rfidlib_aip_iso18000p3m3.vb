Namespace RFIDLIB
    Class rfidlib_aip_iso18000p3m3
        Public Declare Function ISO18000p3m3_CreateInvenParam Lib "rfidlib_aip_iso18000p3m3.dll" (ByVal hInvenParamSpecList As UIntPtr, ByVal AntennaID As Byte, ByVal sel As Byte, ByVal session As Byte, ByVal Q As Byte) As Integer

        Public Declare Function ISO18000p3m3_ParseTagDataReport Lib "rfidlib_aip_iso18000p3m3.dll" (ByVal hTagReport As UIntPtr, ByRef aip_id As UInt32, ByRef tag_id As UInt32, ByRef ant_id As UInt32, ByRef metaFlags As UInt32, ByVal tagdata As Byte(), ByRef tagDataLen As UInt32) As Integer
    End Class
End Namespace