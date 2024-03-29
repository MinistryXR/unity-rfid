unit rfidlib_def;

interface

const
RFID_APL_UNKNOWN_ID =  0;
RFID_APL_ISO15693_ID = 1;
        // Tag type id
RFID_UNKNOWN_PICC_ID =0 ;
RFID_ISO15693_PICC_ICODE_SLI_ID = 1 ;
RFID_ISO15693_PICC_TI_HFI_PLUS_ID=2;
RFID_ISO15693_PICC_ST_M24LRXX_ID=3;	  
RFID_ISO15693_PICC_FUJ_MB89R118C_ID=4;
RFID_ISO15693_PICC_ST_M24LR64_ID=5;
RFID_ISO15693_PICC_ST_M24LR16E_ID=6;
RFID_ISO15693_PICC_ICODE_SLIX_ID=7 ;
RFID_ISO15693_PICC_TIHFI_STANDARD_ID= 8 ;
RFID_ISO15693_PICC_TIHFI_PRO_ID =9;


//Inventory type
AI_TYPE_NEW=	1  ;   // new antenna inventory  (reset RF power)
AI_TYPE_CONTINUE	=2	;  // continue antenna inventory ;


// Move position
RFID_NO_SEEK	 =0		;			// No seeking
RFID_SEEK_FIRST=				1;					// Seek first
RFID_SEEK_NEXT	=			2	;				// Seek next
RFID_SEEK_LAST = 3;				// Seek last


{
usb enum information
}
HID_ENUM_INF_TYPE_SERIALNUM	=			1  ;
HID_ENUM_INF_TYPE_DRIVERPATH =			2  ;


{
* Get loaded reader driver option 
}
LOADED_RDRDVR_OPT_CATALOG	 ='CATALOG' ;
LOADED_RDRDVR_OPT_NAME		=				'NAME' ;
LOADED_RDRDVR_OPT_ID	 =					'ID'  ;
LOADED_RDRDVR_OPT_COMMTYPESUPPORTED		=	'COMM_TYPE_SUPPORTED';



{
* Reader driver type
}
RDRDVR_TYPE_READER=					'Reader' ; // general reader
RDRDVR_TYPE_MTGATE=					'MTGate' ; // meeting gate
RDRDVR_TYPE_LSGATE=					'LSGate' ; // Library secure gate



{
        * Open connection string 
}
CONNSTR_NAME_RDTYPE = 'RDType' ;
CONNSTR_NAME_COMMTYPE	=		'CommType';

CONNSTR_NAME_COMMTYPE_COM	=	'COM';
CONNSTR_NAME_COMMTYPE_USB	=	'USB';
CONNSTR_NAME_COMMTYPE_NET = 'NET';

//HID Param
CONNSTR_NAME_HIDADDRMODE=	    'AddrMode';
CONNSTR_NAME_HIDSERNUM	=	    'SerNum';
//COM Param
CONNSTR_NAME_COMNAME	=		'COMName';
CONNSTR_NAME_COMBARUD	=		'BaudRate';
CONNSTR_NAME_COMFRAME	=		'Frame';
CONNSTR_NAME_BUSADDR	=		'BusAddr';
//TCP,UDP
CONNSTR_NAME_REMOTEIP	='RemoteIP';
CONNSTR_NAME_REMOTEPORT=	'RemotePort';
CONNSTR_NAME_LOCALIP	='LocalIP';


{
 supported product type
 }

COMMTYPE_COM_EN =1 ;
COMMTYPE_USB_EN =2 ;
COMMTYPE_NET_EN = 4;

implementation

end.

