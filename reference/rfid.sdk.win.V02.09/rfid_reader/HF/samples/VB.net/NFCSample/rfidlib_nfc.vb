Imports System.Text

namespace RFIDLIB

    class rfidlib_nfc

        Public Declare Function nfc_CreateUriNdef Lib "rfidlib_nfc.dll" (ByVal sNetAddr As String, ByVal UriType As Byte) As UIntPtr

        Public Declare Function nfc_WriteNdef Lib "rfidlib_nfc.dll" (ByVal hReader As UIntPtr, ByVal hTag As UIntPtr, ByVal hNdef As UIntPtr, ByVal IsLock As Byte) As Integer

        Public Declare Function nfc_ReadNdef Lib "rfidlib_nfc.dll" (ByVal hReader As UIntPtr, ByVal hTag As UIntPtr, ByRef hNdef As UIntPtr, ByRef NdefType As Byte) As Integer

        Public Declare Function nfc_ParseNdefByUri Lib "rfidlib_nfc.dll" (ByVal hNdef As UIntPtr, ByVal sNetAddr As StringBuilder, ByVal NetAddrSize As UInt32, ByRef netType As Byte) As Integer
    End Class
End Namespace
