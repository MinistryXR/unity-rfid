#ifndef __RFIDLIB_H__
#define __RFIDLIB_H__



/* Air interface protocol type id */
#ifndef __RFID_APL_ID_H__
#define __RFID_APL_ID_H__
enum rfid_APL_id {
	RFID_APL_UNKNOWN_ID = 0,
	RFID_APL_ISO15693_ID,
	RFID_APL_ISO14443A_ID,
	RFID_APL_ISO14443B_ID,
	RFID_APL_EPCGEN2_ID,       //UHF
	RFID_APL_ISO18000P3M3,
};
#endif

#ifndef RFID_UNKNOWN_PICC_ID
#define RFID_UNKNOWN_PICC_ID					0
#endif


/* ISO15693 tag type id */
#ifndef __RFID_ISO15693_PICC_ID__
#define __RFID_ISO15693_PICC_ID__
/* ISO15693 PICC id*/
enum 
{
   RFID_ISO15693_PICC_ICODE_SLI_ID = 1,
   RFID_ISO15693_PICC_TI_HFI_PLUS_ID,
   RFID_ISO15693_PICC_ST_SERIES_ID,		    /* ST serial ,ST can not identify tag type by UID */
   RFID_ISO15693_PICC_FUJ_MB89R118C_ID,
   RFID_ISO15693_PICC_ST_M24LR64_ID,
   RFID_ISO15693_PICC_ST_M24LR16E_ID,	
   RFID_ISO15693_PICC_ICODE_SLIX_ID,
   RFID_ISO15693_PICC_TIHFI_STANDARD_ID,
   RFID_ISO15693_PICC_TIHFI_PRO_ID,             // password
   RFID_ISO15693_PICC_ICODE_SLIX2_ID,
   RFID_ISO15693_PICC_CIT83128_ID,				/* 北京华大*/
   RFID_ISO15693_PICC_ST_LRI2k_ID,
   RFID_ISO15693_PICC_ICODE_SLI_L_ID,
   RFID_ISO15693_PICC_ICODE_SLIX_L_ID,
   RFID_ISO15693_PICC_ICODE_SLI_S_ID,
   RFID_ISO15693_PICC_ICODE_SLIX_S_ID,
   RFID_ISO15693_PICC_RF430FR12XH_ID,
   RFID_ISO15693_PICC_ST25DVXX_ID,
} ;
#endif


/* ISO14443A tag type id */
enum
{
	RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID =1,    // Ultralight
	RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID,
	RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID,
	RFID_ISO14443A_PICC_NXP_DESFIRE_EV1_ID,
	RFID_ISO14443A_PICC_NTAG21x_ID,
} ;
/*
*	rfidlib api
*/
#if defined(_WIN64)
#define RFIDLIB_API				__fastcall	
#else
#define RFIDLIB_API				__stdcall		
#endif



/*
*	variable types
*/



#ifndef err_t
#define  err_t					INT32
#endif

#ifndef NO_ERR
#define NO_ERR                                  0
#endif

#ifndef mem_ptr_t
#define mem_ptr_t									HANDLE		
#endif

#define RFID_HANDLE_NULL							0
typedef void *RFID_HANDLE;
#define RFID_READER_HANDLE							RFID_HANDLE
#define RFID_TAG_HANDLE								RFID_HANDLE
#define RFID_DN_HANDLE								RFID_HANDLE
#define MEM_PTR_T									RFID_HANDLE
#define RFID_NFC_HANDLE                             RFID_HANDLE
#define	WIN_MSG_t									UINT




// callback event type
enum
{
	RFIDLIB_EVNT_GETBUF_REPORT_FOUND = 1,
	RFIDLIB_EVNT_GETBUF_ERROR ,
	RFIDLIB_EVNT_GETBUF_EXIT,
} ;




/*
*	RFID field name 
*/
//#define RFIDLIB_FN_NULL									""
//#define RFIDLIB_FN_AIPINVENPARAM						"AIPInvnParam"
//#define RFIDLIB_FN_AIP_TYPE								"AIPType"		/* id of APL type */				
//#define RFIDLIB_FN_TAG_TYPE								"TagType"		/* id of picc type */
//#define RFIDLIB_FN_TAG_ACCESS							"TagAccess"
//#define RFIDLIB_FN_ACCESS_CODE							"AccessCode"    /* Tag access code */
//#define RFIDLIB_FN_ACCESS_PARAM							"AccessParam"
//#define RFIDLIB_FN_AIP_CONNPRM							"AIPConnParam"  /* Air protocol connection parameters */
//#define RFIDLIB_FN_ANT_ID								"AntennaID"		/* antenna id */
//#define RFIDLIB_FN_TAGDATA								"TagData"		/* Tag data */
//#define RFIDLIB_FN_ADDR_MODE							"AddrMode"
//#define RFIDLIB_FN_UID									"UID"
//#define RFIDLIB_FN_IS_READ_SSB							"ToReadSSB"	/* read security status byte ? */
//#define RFIDLIB_FN_BLOCK_NO								"BlockNo"		/* block no */
//#define RFIDLIB_FN_BLK_DATA								"BlockData"		/* block data */
//#define RFIDLIB_FN_NUM_OF_BLK							"NumberOfBlocks"	/* number of block */
//#define RFIDLIB_FN_AFI									"AFI"
//#define RFIDLIB_FN_DSFID								"DSFID"
//#define RFIDLIB_FN_BLK_SIZE								"BlockSize"
//#define RFIDLIB_FN_IC_REF								"IC_reference"
//#define RFIDLIB_FN_SECTOR_NO							"SectorNo"
//#define RFIDLIB_FN_ACC_TYPE								"AccessType"
//#define RFIDLIB_FN_EAS_FLAG								"EAS_flag"
//#define RFIDLIB_FN_INVENPRM_ISO15693					"InvenParmISO15693"
//#define RFIDLIB_FN_AIRPROTINVENCMDSETTINGS				"AirProtInvenCmdSettings"
//#define RFIDLIB_FN_SLOTTYPE								"SlotType"
//#define RFIDLIB_FN_STATUS								"Status"
//#define RFIDLIB_FN_EXTENSION							"Extension"
//#define RFIDLIB_FN_TAGDATAREPORT						"TagDataReport"
//#define RFIDLIB_FN_IDENTIFIER							"Identifier"
//#define RFIDLIB_FN_AIPTAGDATA							"AirProtTagData"
//#define RFIDLIB_FN_CFG_BYTE								"CFG_byte"		
//#define RFIDLIB_FN_ENERGY_HARVESTING					"EnergyHarvesting"
//#define RFIDLIB_FN_EH_MODE								"EH_mode"
//#define RFIDLIB_FN_CFG_DO								"CFG_DO"
//#define RFIDLIB_FN_CTRL_REG_EH_EN						"CtrolReg_EH_Enable"
//#define RFIDLIB_FN_CTRL_REG								"ControlRegister"
//#define RFIDLIB_FN_PWD_NO								"PasswordNo"
//#define RFIDLIB_FN_PWD_OLD								"OldPassword"
//#define RFIDLIB_FN_PWD_NEW								"NewPassword"
//#define RFIDLIB_FN_PWD									"Password"
//#define RFIDLIB_FN_RANDOMNUM							"RandomNum"
//#define RFIDLIB_FN_BANDTYPE								"BandType"		
//#define RFIDLIB_FN_OUTPUTNO								"OutputNo"
//#define RFIDLIB_FN_OUTMODE								"OutMode"
//#define RFIDLIB_FN_OUTFREQUENCE							"OutFrequency"
//#define RFIDLIB_FN_OUTACTIVEDURATION					"OutActiveDuration"
//#define RFIDLIB_FN_OUTINACTIVEDURATION					"OutInactiveDuration"
//#define RFIDLIB_FN_PAGENO								"PageNo"
//#define RFIDLIB_FN_PAGEDATA								"PageData"
//#define RFIDLIB_FN_LOCKINGPAGES							"LockingPages"
//#define RFIDLIB_FN_LOCKCFGAREA							"LockingCFGArea"
//#define RFIDLIB_FN_LOCKPAGETYPE							"LockingPageType"
//#define RFIDLIB_FN_UIDLEN								"UIDLen"
//#define RFIDLIB_FN_KEYTYPE								"KeyType"
//#define RFIDLIB_FN_KEY									"Key"
//#define RFIDLIB_FN_MFVALUE								"MFValue"   // mifare block value for increment ordecrement
//#define RFIDLIB_FN_AUTOTRANF							"AutoTransfer"  // mifare classic 
//#define RFIDLIB_FN_SECTOR_NO							"SectorNo"		// sector no 
//#define RFIDLIB_FN_AUTOAUTH								"AutoAuth"
//#define RFIDLIB_FN_AUTH0								"Auth0"			//for ultralight C
//#define RFIDLIB_FN_AUTH1								"Auth1"			//for ultralight C
//#define RFIDLIB_FN_SELTYPE								"SelType"
//#define RFIDLIB_FN_SESSION								"Session"
//#define RFIDLIB_FN_Q									"Q"
//#define RFIDLIB_FN_SELECTPARAM							"SelectParam"
//#define RFIDLIB_FN_TARGER								"Target"
//#define RFIDLIB_FN_ACTION								"Action"
//#define RFIDLIB_FN_MEMBANK								"MemBank"
//#define RFIDLIB_FN_POINTER								"Pointer"
//#define RFIDLIB_FN_MASKBITS								"MaskBits"
//#define RFIDLIB_FN_MASKBITSLEN							"MaskBitsLen"
//#define RFIDLIB_FN_TRUNCATE								"Truncate"
//#define RFIDLIB_FN_MEMBANK								"MemBank"
//#define RFIDLIB_FN_STARTWORD							"StartWord"
//#define RFIDLIB_FN_WORDCOUNT							"WordCnt"
//#define RFIDLIB_FN_RECOMMISSION							"Recommission"
//#define RFIDLIB_FN_MASK									"Mask"
//#define RFIDLIB_FN_TAGCOMMANDSET						"TagCommandSet"
//#define RFIDLIB_FN_STOPTRIGGER							"StopTrigger"
//
//
//
//// Get capability
//#define RFIDLIB_FN_SW_VERSION							"SW_Version"
//#define RFIDLIB_FN_PRODUCTID							"ProductID"
//#define RFIDLIB_FN_PRODUCTSERIAL						"ProductSerialNum"
//
//// Event method 
//#define RFIDLIB_FN_EVTMED_TYPE							"TypeOfEventMeth"
//#define RFIDLIB_FN_EVTMED_MSG							"MsgOfEventMeth"
//#define RFIDLIB_FN_EVTMED_WND							"hWndOfEventMeth"
//#define RFIDLIB_FN_EVTMED_CB							"CallbckOfEventMeth"
//
//
//#define RFIDLIB_FN_CARDDATA								"CardData"
//#define RFIDLIB_FN_DIRECTION							"Direction"
//#define RFIDLIB_FN_DATETIME								"Datetime"
//#define RFIDLIB_FN_EVENTTYPE							"EventType"


// Event method 
#define RFID_EVTMED_USE_MSG								1			// use sendmessage
#define RFID_EVTMED_USE_CB								2			// use call back function
#define RFID_EVTMED_USE_POSTMSG							3           // use postmessage
typedef VOID (__stdcall *RFID_EVENT_CALLBACK)(WPARAM wparam, LPARAM lparam) ; 
typedef VOID (__stdcall *RFID_EVENT_CALLBACK_NEW)(void *inParam,WPARAM wparam, LPARAM lparam) ;
//Inventory type 
#define AI_TYPE_NEW										1     // new antenna inventory  (reset RF power)
#define AI_TYPE_CONTINUE								2	  // continue antenna inventory ;


// Move position 
#define RFID_NO_SEEK				0					// No seeking 
#define RFID_SEEK_FIRST				1					// Seek first
#define RFID_SEEK_NEXT				2					// Seek next 
#define RFID_SEEK_LAST				3					// Seek last



/* 
* inventory stop trigger type
*/
enum
{
	INVEN_STOP_TRIGGER_TYPE_Tms,   
	INVEN_STOP_TRIGGER_TYPE_N_attempt,
	INVEN_STOP_TRIGGER_TYPE_N_found,
	INVEN_STOP_TRIGGER_TYPE_TIMEOUT,
} ;


/*
usb enum information
*/
#define HID_ENUM_INF_TYPE_SERIALNUM				1
#define HID_ENUM_INF_TYPE_DRIVERPATH			2


/*
* Output Name
*/
#define OUTPUT_NAME_BUZZER_INBOARD		"Buzzer"
#define OUTPUT_NAME_RELAY1				"Relay#1"







/*
* Open connection string 
*/
#define CONNSTR_NAME_RDTYPE				"RDType"
#define CONNSTR_NAME_COMMTYPE			"CommType"

/*
* communication interface type
*/
#define CONNSTR_NAME_COMMTYPE_COM		"COM"
#define CONNSTR_NAME_COMMTYPE_USB		"USB"
#define CONNSTR_NAME_COMMTYPE_NET		"NET"
#define CONNSTR_NAME_COMMTYPE_BLUETOOTH  "BLUETOOTH"

//USB Param
#define CONNSTR_NAME_HIDADDRMODE	    "AddrMode"
#define CONNSTR_NAME_HIDSERNUM		    "SerNum"
//COM Param
#define CONNSTR_NAME_COMNAME			"COMName"
#define CONNSTR_NAME_COMBARUD			"BaudRate"
#define CONNSTR_NAME_COMFRAME			"Frame"
#define CONNSTR_NAME_BUSADDR			"BusAddr"
//Netword
#define CONNSTR_NAME_REMOTEIP	"RemoteIP"
#define CONNSTR_NAME_REMOTEPORT	"RemotePort"
#define CONNSTR_NAME_LOCALIP	"LocalIP"

//Bluetooth
#define CONNSTR_NAME_BLUETOOTH_SERNUM   "Addr"


#define CONNSTR_NAME_CHECK_ONLINE		"CheckOnline"


/*
* Get loaded reader driver option 
*/
#define LOADED_RDRDVR_OPT_CATALOG					"CATALOG"
#define LOADED_RDRDVR_OPT_NAME						"NAME"
#define LOADED_RDRDVR_OPT_ID						"ID"
#define LOADED_RDRDVR_OPT_COMMTYPESUPPORTED			"COMM_TYPE_SUPPORTED"

/*
* Reader driver type
*/
#define RDRDVR_TYPE_READER					"Reader" // general reader
#define RDRDVR_TYPE_MTGATE					"MTGate" // meeting gate
#define RDRDVR_TYPE_LSGATE					"LSGate" // Library secure gate


/* supported communication type */
enum
{
	COMMTYPE_COM_EN =0x01,
	COMMTYPE_USB_EN =0x02,
	COMMTYPE_NET_EN =0x04,
	COMMTYPE_BLUETOOTH_EN = 0x08,
};


/*
* GPO Output Mode 
*/
enum
{
	OUTPUT_MODE_NOCHANGE,
	OUTPUT_MODE_ON,
	OUTPUT_MODE_OFF,
	OUTPUT_MODE_FLASH ,
} ;


/*
*  ISO18000p3m3 
*/
// meta flags 
#define ISO18000p3m3_META_BIT_MASK_EPC						0x01
 
// begin round sel 
enum
{
	ISO18000p3m3_BEGIN_ROUND_SEL_ALL =0 ,
	ISO18000p3m3_BEGIN_ROUND_SEL_DEASSERT_SL =0x02,
	ISO18000p3m3_BEGIN_ROUND_SEL_ASSERT_SL=0x03,
};
// session
enum
{
	ISO18000p3m3_S0 =0x00 ,
	ISO18000p3m3_S2= 0x02,
};

#define ISO18000p3m3_Dynamic_Q				0xFF



/*
* ISO18000-6C
*/

// session
enum
{
	ISO18000p6C_S0 =0x00,
	ISO18000p6C_S1 =0x01,
	ISO18000p6C_S2= 0x02,
	ISO18000p6C_S3= 0x03,
};
// inventory target
#define ISO18000p6C_TARGET_A			0x00
#define ISO18000p6C_TARGET_B			0x01


// inventory Sel type
#define ISO18000p6C_SEL_TYPE_ALL		0x00 
#define ISO18000p6C_SEL_TYPE_negate_SL	0x01
#define ISO18000p6C_SEL_TYPE_SL			0x02

//Q value
#define ISO18000p6C_Dynamic_Q			0xFF
/*
* meta data bit mask
*/
#define ISO18000p6C_META_BIT_MASK_EPC						0x01
#define ISO18000P6C_META_BIT_MASK_TIMESTAMP					0x02
#define ISO18000P6C_META_BIT_MASK_FREQUENCY					0x04
#define ISO18000p6C_META_BIT_MASK_RSSI						0x08
#define ISO18000P6C_META_BIT_MASK_READCOUNT					0x10 
#define ISO18000P6C_META_BIT_MASK_TAGDATA					0x20



// selection target
//b000: Inventoried (S0)
//b001: Inventoried (S1)
//b010: Inventoried (S2)
//b011: Inventoried (S3)
//b100: SL
//b101: RFU
//b110: RFU
//b111: RFU
#define ISO18000p6C_SELECT_TARGET_INV_S0			0x00
#define ISO18000p6C_SELECT_TARGET_INV_S1			0x01
#define ISO18000p6C_SELECT_TARGET_INV_S2			0x02
#define ISO18000p6C_SELECT_TARGET_INV_S3			0x03
#define ISO18000p6C_SELECT_TARGET_INV_SL			0x04


/* select action type
0x00: assert SL or inventoried → A deassert SL or inventoried → B
0x01: assert SL or inventoried → A do nothing
0x02: do nothing deassert SL or inventoried → B
0x03: negate SL or (A → B, B → A) do nothing
0x04: deassert SL or inventoried → B assert SL or inventoried → A
0x05: deassert SL or inventoried → B do nothing
0x06: do nothing assert SL or inventoried → A
0x07: do nothing negate SL or (A → B, B → A)
*/

// Memory bank type
#define ISO18000p6C_MEM_BANK_RFU					0x00
#define ISO18000p6C_MEM_BANK_EPC					0x01
#define ISO18000p6C_MEM_BANK_TID					0x02
#define ISO18000p6C_MEM_BANK_USER					0x03


#endif
