Namespace RFIDLIB
    Class rfidlib_aip_iso15693


        Public Declare Function ISO15693_CreateInvenParam Lib "rfidlib_aip_iso15693.dll" (ByVal hInvenParamSpecList As UIntPtr, ByVal AntennaID As Byte, ByVal en_afi As Byte, ByVal afi As Byte, ByVal slot_type As Byte) As UIntPtr

        Public Declare Function ISO15693_ParseTagDataReport Lib "rfidlib_aip_iso15693.dll" (ByVal hTagReport As UIntPtr, ByRef aip_id As UInt32, ByRef tag_id As UInt32, ByRef ant_id As UInt32, ByRef dsfid As [Byte], ByVal uid As [Byte]()) As Integer

        Public Declare Function ISO15693_Connect Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal tagType As UInt32, ByVal address_mode As [Byte], ByVal uid As [Byte](), ByRef ht As UIntPtr) As Integer

        Public Declare Function ISO15693_ReadMultiBlocks Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal readSecSta As [Byte], ByVal blkAddr As UInt32, ByVal numOfBlksToRead As UInt32, ByRef numOfBlksRead As UInt32, _
        ByVal bufBlocks As [Byte](), ByVal nSize As UInt32, ByRef bytesBlkDatRead As UInt32) As Integer

        Public Declare Function ISO15693_WriteMultipleBlocks Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal blkAddr As UInt32, ByVal numOfBlks As UInt32, ByVal newBlksData As [Byte](), ByVal bytesToWrite As UInt32) As Integer

        Public Declare Function ISO15693_LockMultipleBlocks Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal blkAddr As UInt32, ByVal numOfBlks As UInt32) As Integer

        Public Declare Function ISO15693_WriteMultipleBlocks Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal blkAddr As Long, ByVal numOfBlks As Long, ByRef newBlksData As Byte, ByVal bytesToWrite As Long) As Integer

        Public Declare Function ISO15693_WriteAFI Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal afi As Byte) As Integer

        Public Declare Function ISO15693_LockAFI Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr) As Integer

        Public Declare Function ISO15693_WriteDSFID Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal dsfid As Byte) As Integer

        Public Declare Function ISO15693_LockDSFID Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr) As Integer

        Public Declare Function NXPICODESLI_EableEAS Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr) As Integer

        Public Declare Function NXPICODESLI_DisableEAS Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr) As Integer

        Public Declare Function NXPICODESLI_LockEAS Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr) As Integer

        Public Declare Function NXPICODESLI_EASCheck Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UInteger, ByVal ht As UIntPtr, ByRef EASStatus As Byte) As Integer

        Public Declare Function ISO15693_GetSystemInfo Lib "rfidlib_aip_iso15693.dll" (ByVal hr As UIntPtr, ByVal ht As UIntPtr, ByVal uid As Byte(), ByRef dsfid As Byte, ByRef afi As Byte, ByRef blkSize As UInt32, ByRef numOfBloks As UInt32, ByRef icRef As Byte) As Integer
    End Class
End Namespace