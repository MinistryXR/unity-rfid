Namespace RFIDLIB
    Class rfidlib_aip_iso14443A
        Public Declare Function ISO14443A_CreateInvenParam Lib "rfidlib_aip_iso14443A.dll" (ByVal hInvenParamSpecList As UIntPtr, ByVal AntennaID As Byte) As Integer

        Public Declare Function ISO14443A_ParseTagDataReport Lib "rfidlib_aip_iso14443A.dll" (ByVal hTagReport As UIntPtr, ByRef aip_id As UInt32, ByRef tag_id As UInt32, ByRef ant_id As UInt32, ByVal uid As Byte(), ByRef uidlen As Byte) As Integer

        Public Declare Function NTAG21x_Connect Lib "rfidlib_aip_iso14443A.dll" (ByVal hr As UIntPtr, ByVal uid As Byte(), ByRef ht As UIntPtr)

    End Class
End Namespace