Imports System.Collections.Generic
Imports System.Text

Namespace RFIDLIB
    Public Delegate Sub RFIDLIB_EVENT_CALLBACK(wparam As UIntPtr, lparam As UIntPtr)    'stdcall
    Public Delegate Sub RFID_EVENT_CALLBACK_NEW(inParam As UIntPtr, wparam As UIntPtr, lparam As UIntPtr)   'stdcall

    Class rfidlib_def

        ' Air protocol id
        Public Const RFID_APL_UNKNOWN_ID As Integer = 0
        Public Const RFID_APL_ISO15693_ID As Integer = 1
        Public Const RFID_APL_ISO14443A_ID As Integer = 2
        Public Const RFID_APL_ISO14443B_ID As Integer = 3
        Public Const RFID_APL_EPCGEN2_ID As Integer = 4
        Public Const RFID_APL_ISO18000P3M3 As Integer = 5

        ' ISO15693 Tag type id
        Public Const RFID_UNKNOWN_PICC_ID As Integer = 0
        Public Const RFID_ISO15693_PICC_ICODE_SLI_ID As Integer = 1
        Public Const RFID_ISO15693_PICC_TI_HFI_PLUS_ID As Integer = 2
        Public Const RFID_ISO15693_PICC_ST_SERIES_ID As Integer = 3         ' ST  serial 
        Public Const RFID_ISO15693_PICC_FUJ_MB89R118C_ID As Integer = 4
        Public Const RFID_ISO15693_PICC_ST_M24LR64_ID As Integer = 5
        Public Const RFID_ISO15693_PICC_ST_M24LR16E_ID As Integer = 6
        Public Const RFID_ISO15693_PICC_ICODE_SLIX_ID As Integer = 7
        Public Const RFID_ISO15693_PICC_TIHFI_STANDARD_ID As Integer = 8
        Public Const RFID_ISO15693_PICC_TIHFI_PRO_ID As Integer = 9
        Public Const RFID_ISO15693_PICC_ICODE_SLIX2_ID As Integer = 10
        Public Const RFID_ISO15693_PICC_CIT83128_ID As Integer = 11
        Public Const RFID_ISO15693_PICC_ST_LRI2k_ID As Integer = 12

        'ISO14443a tag type id 
        Public Const RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID As Integer = 1
        Public Const RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID As Integer = 2
        Public Const RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID As Integer = 3


        'Inventory type 
        Public Const AI_TYPE_NEW As Integer = 1        ' new antenna inventory  (reset RF power)
        Public Const AI_TYPE_CONTINUE As Integer = 2    ' continue antenna inventory ;

        ' Move position 
        Public Const RFID_NO_SEEK As Integer = 0    ' No seeking 
        Public Const RFID_SEEK_FIRST As Integer = 1 ' Seek first
        Public Const RFID_SEEK_NEXT As Integer = 2  ' Seek next 
        Public Const RFID_SEEK_LAST As Integer = 3  ' Seek last

        '
        '        usb enum information
        '        
        Public Const HID_ENUM_INF_TYPE_SERIALNUM As Integer = 1
        Public Const HID_ENUM_INF_TYPE_DRIVERPATH As Integer = 2




        '
        '                * Open connection string 
        '                
        Public Const CONNSTR_NAME_RDTYPE As String = "RDType"
        Public Const CONNSTR_NAME_COMMTYPE As String = "CommType"

        Public Const CONNSTR_NAME_COMMTYPE_COM As String = "COM"
        Public Const CONNSTR_NAME_COMMTYPE_USB As String = "USB"
        Public Const CONNSTR_NAME_COMMTYPE_NET As String = "NET"
        Public Const CONNSTR_NAME_COMMTYPE_BLUETOOTH As String = "BLUETOOTH"

        'HID Param
        Public Const CONNSTR_NAME_HIDADDRMODE As String = "AddrMode"
        Public Const CONNSTR_NAME_HIDSERNUM As String = "SerNum"
        'COM Param
        Public Const CONNSTR_NAME_COMNAME As String = "COMName"
        Public Const CONNSTR_NAME_COMBARUD As String = "BaudRate"
        Public Const CONNSTR_NAME_COMFRAME As String = "Frame"
        Public Const CONNSTR_NAME_BUSADDR As String = "BusAddr"
        'TCP,UDP
        Public Const CONNSTR_NAME_REMOTEIP As String = "RemoteIP"
        Public Const CONNSTR_NAME_REMOTEPORT As String = "RemotePort"
        Public Const CONNSTR_NAME_LOCALIP As String = "LocalIP"
        'Bluetooth
        Public Const CONNSTR_NAME_BLUETOOTH_SN As String = "Addr"


        '
        '        * Get loaded reader driver option 
        '        
        Public Const LOADED_RDRDVR_OPT_CATALOG As String = "CATALOG"
        Public Const LOADED_RDRDVR_OPT_NAME As String = "NAME"
        Public Const LOADED_RDRDVR_OPT_ID As String = "ID"
        Public Const LOADED_RDRDVR_OPT_COMMTYPESUPPORTED As String = "COMM_TYPE_SUPPORTED"

        '
        '        * Reader driver type
        '        
        Public Const RDRDVR_TYPE_READER As String = "Reader"    ' general reader
        Public Const RDRDVR_TYPE_MTGATE As String = "MTGate"    ' meeting gate
        Public Const RDRDVR_TYPE_LSGATE As String = "LSGate"    ' Library secure gate

        ' supported product type 

        Public Const COMMTYPE_COM_EN As Byte = &H1
        Public Const COMMTYPE_USB_EN As Byte = &H2
        Public Const COMMTYPE_NET_EN As Byte = &H4


        'Q value
        Public Const ISO18000p6C_Dynamic_Q As Byte = &HFF


    End Class
End Namespace