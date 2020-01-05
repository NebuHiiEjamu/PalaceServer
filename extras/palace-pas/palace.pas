unit palace;

interface
	uses fpsock;

	const
		MansionVersion = $00010016;
		MaxUserProps = 9;

		DC_Path = 0;
		DC_Shape = 1;
		DC_Text = 2;
		DC_Detonate = 3;
		DC_Delete = 4;
		DC_Ellipse = 5;

		SI_AVATAR_URL = $00000001;
		SI_SERVER_VERSION = $00000002;
		SI_SERVER_TYPE = $00000004;
		SI_SERVER_FLAGS = $00000008;
		SI_NUM_USERS = $00000010;
		SI_SERVER_NAME = $00000020;
		SI_HTTP_URL = $00000040;

		SI_EXT_NAME = $4E414D45;
		SI_EXT_PASS = $50415353;
		SI_EXT_TYPE = $54595045;

		SI_ERR_AUTH = $41555448;
		SI_ERR_UNKN = $554E4B4E;

		SI_INF_AURL = $4155524C;
		SI_INF_VERS = $56455253;
		SI_INF_TYPE = SI_EXT_TYPE;
		SI_INF_FLAG = $464C4147;
		SI_INF_NUM_USERS = $4E555352;
		SI_INF_NAME = SI_EXT_NAME;
		SI_INF_HURL = $4855524C;

		FF_DirectPlay = $0001;
		FF_ClosedServer = $0002;
		FF_GuestsAreMembers = $0004;
		FF_Unused1 = $0008;
		FF_InstantPalace = $0010;
		FF_PalacePresents = $0020;

		PLAT_Macintosh = 0;
		PLAT_Windows95 = 1;
		PLAT_WindowsNT = 2;
		PLAT_Unix = 3;

		RF_AuthorLocked = $0001;
		RF_Private = $0002;
		RF_NoPainting = $0004;
		RF_Closed = $0008;
		RF_CyborgFreeZone = $0010;
		RF_Hidden = $0020;
		RF_NoGuests = $0040;
		RF_WizardsOnly = $0080;
		RF_DropZone = $0100;
		RF_NoLooseProps = $0200;

		U_SuperUser = $0001;
		U_God = $0002;
		U_Kill = $0004;
		U_Guest = $0008;
		U_Banished = $0010;
		U_Penalized = $0020;
		U_CommError = $0040;
		U_Gag = $0080;
		U_Pin = $0100;
		U_Hide = $0200;
		U_RejectESP = $0400;
		U_RejectPrivate = $0800;
		U_PropGag = $1000;

		LI_AUXFLAGS_UnknownMach = 0;
		LI_AUXFLAGS_Mac68k = 1;
		LI_AUXFLAGS_MacPPC = 2;
		LI_AUXFLAGS_Win16 = 3;
		LI_AUXFLAGS_Win32 = 4;
		LI_AUXFLAGS_Java = 5;
		LI_AUXFLAGS_OSMask = $0000000F;
		LI_AUXFLAGS_Authenticate = $80000000;

		LI_ULCAPS_ASSETS_PALACE = $00000001;
		LI_ULCAPS_ASSETS_FTP = $00000002;
		LI_ULCAPS_ASSETS_HTTP = $00000004;
		LI_ULCAPS_ASSETS_OTHER = $00000008;
		LI_ULCAPS_FILES_PALACE = $00000010;
		LI_ULCAPS_FILES_FTP = $00000020;
		LI_ULCAPS_FILES_HTTP = $00000040;
		LI_ULCAPS_FILES_OTHER = $00000080;
		LI_ULCAPS_EXTEND_PKT = $00000100;

		LI_DLCAPS_ASSETS_PALACE = $00000001;
		LI_DLCAPS_ASSETS_FTP = $00000002;
		LI_DLCAPS_ASSETS_HTTP = $00000004;
		LI_DLCAPS_ASSETS_OTHER = $00000008;
		LI_DLCAPS_FILES_PALACE = $00000010;
		LI_DLCAPS_FILES_FTP = $00000020;
		LI_DLCAPS_FILES_HTTP = $00000040;
		LI_DLCAPS_FILES_OTHER = $00000080;
		LI_DLCAPS_FILES_HTTPSrvr = $00000100;
		LI_DLCAPS_EXTEND_PKT = $00000200;

		LI_2DENGINECAP_PALACE = $00000001;
		LI_2DENGINECAP_DOUBLEBYTE = $00000002;

		LI_2DGRAPHCAP_GIF87 = $00000001;
		LI_2DGRAPHCAP_GIF89a = $00000002;
		LI_2DGRAPHCAP_JPG = $00000004;
		LI_2DGRAPHCAP_TIFF = $00000008;
		LI_2DGRAPHCAP_TARGA = $00000010;
		LI_2DGRAPHCAP_BMP = $00000020;
		LI_2DGRAPHCAP_PCT = $00000040;

		LI_3DENGINECAP_VRML1 = $00000001;
		LI_3DENGINECAP_VRML2 = $00000002;

		SE_InternalError = 0;
		SE_RoomUnknown = 1;
		SE_RoomFull = 2;
		SE_RoomClosed = 3;
		SE_CantAuthor = 4;
		SE_PalaceFull = 5;

		PE_Select = $00000001;
		PE_Lock = $00000002;
		PE_Unlock = $00000004;
		PE_Hide = $00000008;
		PE_Show = $00000010;
		PE_Startup = $00000020;
		PE_Alarm = $00000040;
		PE_Custom = $00000080;
		PE_InChat = $00000100;
		PE_PropChange = $00000200;
		PE_Enter = $00000400;
		PE_Leave = $00000800;
		PE_OutChat = $00001000;
		PE_SignOn = $00002000;
		PE_SignOff = $00004000;
		PE_Macro0 = $00008000;
		PE_Macro1 = $00010000;
		PE_Macro2 = $00020000;
		PE_Macro3 = $00040000;
		PE_Macro4 = $00080000;
		PE_Macro5 = $00100000;
		PE_Macro6 = $00200000;
		PE_Macro7 = $00400000;
		PE_Macro8 = $00800000;
		PE_Macro9 = $01000000;

		HS_Draggable = $01;
		HS_DontMoveHere = $02;
		HS_Invisible = $04;
		HS_ShowName = $08;
		HS_ShowFrame = $0010;
		HS_Shadow = $0020;
		HS_Fill = $0040;

		HS_Normal = 0;
		HS_Door = 1;
		HS_ShutableDoor = 2;
		HS_LockableDoor = 3;
		HS_Bolt = 4;
		HS_NavArea = 5;

		HS_Unlock = 0;
		HS_Lock = 1;

		K_Unknown = 0;
		K_LoggedOff = 1;
		K_CommError = 2;
		K_Flood = 3;
		K_KilledByPlayer = 4;
		K_ServerDown = 5;
		K_Unresponsive = 6;
		K_KilledBySysop = 7;
		K_ServerFull = 8;
		K_InvalidSerialNumber = 9;
		K_DuplicateUser = 10;
		K_DeathPenaltyActive = 11;
		K_Banished = 12;
		K_BanishKill = 13;
		K_NoGuests = 14;
		K_DemoExpired = 15;
		K_Verbose = 16;

		PM_AllowGuests = $0001;
		PM_AllowCyborgs = $0002;
		PM_AllowPainting = $0004;
		PM_AllowCustomProps = $0008;
		PM_AllowWizards = $0010;
		PM_WizardsMayKill = $0020;
		PM_WizardsMayAuthor = $0040;
		PM_PlayersMayKill = $0080;
		PM_CyborgsMayKill = $0100;
		PM_DeathPenalty = $0200;
		PM_PurgeInactiveProps = $0400;
		PM_KillFlooders = $0800;
		PM_NoSpoofing = $1000;
		PM_MemberCreatedRooms = $2000;

		SO_SaveSessionKeys = $00000001;
		SO_PasswordSecurity = $00000002;
		SO_ChatLog = $00000004;
		SO_NoWhisper = $00000008;
		SO_AllowDemoMembers = $00000010;
		SO_Authenticate = $00000020;
		SO_PoundProtect = $00000040;
		SO_SortOptions = $00000080;
		SO_AuthTrackLogoff = $00000100;
		SO_JavaSecure = $00000200;

		FACE_Closed = 0;
		FACE_Smile = 1;
		FACE_TiltDown = 2;
		FACE_Talk = 3;
		FACE_WinkLeft = 4;
		FACE_Normal = 5;
		FACE_WinkRight = 6;
		FACE_TiltLeft = 7;
		FACE_TiltUp = 8;
		FACE_TiltRight = 9;
		FACE_Sad = 10;
		FACE_Blotto = 11;
		FACE_Angry = 12;

		MSG_ALTLOGONREPLY = $72657032;
		MSG_ASSETNEW = $61417374;
		MSG_ASSETQUERY = $71417374;
		MSG_ASSETREGI = $72417374;
		MSG_ASSETSEND = $73417374;
		MSG_AUTHENTICATE = $61757468;
		MSG_AUTHRESPONSE = $61757472;
		MSG_BLOWTHRU = $626C6F77;
		MSG_DISPLAYURL = $6475726C;
		MSG_DIYIT = $72796974;
		MSG_DOORLOCK = $6C6F636B;
		MSG_DOORUNLOCK = $756E6C6F;
		MSG_DRAW = $64726177;
		MSG_EXTENDEDINFO = $73496E66;
		MSG_FILENOTFND = $666E6665;
		MSG_FILEQUERY = $7146696C;
		MSG_FILESEND = $7346696C;
		MSG_GMSG = $676D7367;
		MSG_HTTPSERVER = $48545450;
		MSG_INITCONNECTION = $634C6F67;
		MSG_KILLUSER = $6B696C6C;
		MSG_LISTOFALLROOMS = $724C7374;
		MSG_LISTOFALLUSERS = $754C7374;
		MSG_LOGOFF = $62796520;
		MSG_LOGON = $72656769;
		MSG_NAVERROR = $73457272;
		MSG_NOOP = $4E4F4F50;
		MSG_PICTDEL = $46505371;
		MSG_PICTMOVE = $704C6F63;
		MSG_PICTNEW = $6E506374;
		MSG_PICTSETDESC = $73506374;
		MSG_PING = $70696E67;
		MSG_PONG = $706F6E67;
		MSG_PROPDEL = $64507270;
		MSG_PROPMOVE = $6D507270;
		MSG_PROPNEW = $6E507270;
		MSG_PROPSETDESC = $73507270;
		MSG_RESPORT = $72657370;
		MSG_RMSG = $726D7367;
		MSG_ROOMDESC = $726F6F6D;
		MSG_ROOMDESCEND = $656E6472;
		MSG_ROOMGOTO = $6E617652;
		MSG_ROOMNEW = $6E526F6D;
		MSG_ROOMSETDESC = $73526F6D;
		MSG_SERVERDOWN = $646F776E;
		MSG_SERVERINFO = $73696E66;
		MSG_SERVERUP = $696E6974;
		MSG_SMSG = $736D7367;
		MSG_SPOTDEL = $6F705364;
		MSG_SPOTMOVE = $636F4C73;
		MSG_SPOTNEW = $6F70536E;
		MSG_SPOTSETDESC = $6F705373;
		MSG_SPOTSTATE = $73537461;
		MSG_SUPERUSER = $73757372;
		MSG_TALK = $74616C6B;
		MSG_TIMYID = $74696D79;
		MSG_TIYID = $74697972;
		MSG_TROPSER = $70736572;
		MSG_USERCOLOR = $75737243;
		MSG_USERDESC = $75737244;
		MSG_USERENTER = $77707273;
		MSG_USEREXIT = $65707273;
		MSG_USERFACE = $75737246;
		MSG_USERLIST = $72707273;
		MSG_USERLOG = $6C6F6720;
		MSG_USERMOVE = $754C6F63;
		MSG_USERNAME = $7573724E;
		MSG_USERNEW = $6E707273;
		MSG_USERPROP = $75737250;
		MSG_USERSTATUS = $75537461;
		MSG_VERSION = $76657273;
		MSG_WHISPER = $77686973;
		MSG_WMSG = $776D7367;
		MSG_XTALK = $78746C6B;
		MSG_XWHISPER = $78776973;
	
	type
		TPalaceStream = class(tsocketstream)
		public
			function ReadCString: rawbytestring;
			function ReadPString: rawbytestring;
			procedure WriteCString(s: rawbytestring);
			procedure WritePString(s: rawbytestring);
		end;

implementation

end.
