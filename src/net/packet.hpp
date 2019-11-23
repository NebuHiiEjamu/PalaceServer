#ifndef _PACKET_H
#define _PACKET_H

#include <cstdint>

constexpr std::uint32_t idAltLogonReply = 0x72657032;
constexpr std::uint32_t idAssetNew = 0x61417374;
constexpr std::uint32_t idAssetQuery = 0x71417374;
constexpr std::uint32_t idAssetRegister = 0x72417374;
constexpr std::uint32_t idAssetSend = 0x73417374;
constexpr std::uint32_t idAuthenticate = 0x61757468;
constexpr std::uint32_t idAuthenticationReply = 0x61757472;
constexpr std::uint32_t idBlowThru = 0x625C6F77;
constexpr std::uint32_t idDisplayUrl = 0x6475726C;
constexpr std::uint32_t idThisIsYourIdReverse = 0x72796974;
constexpr std::uint32_t idDoorLock = 0x6C6F636B;
constexpr std::uint32_t idDoorUnlock = 0x756E6C6F;
constexpr std::uint32_t idDraw = 0x64726177;
constexpr std::uint32_t idExtendedInfo = 0x73496E66;
constexpr std::uint32_t idFileNotFound = 0x666E6665;
constexpr std::uint32_t idFileQuery = 0x7146696C;
constexpr std::uint32_t idFileSend = 0x7346696C;
constexpr std::uint32_t idGlobalMessage = 0x676D7367;
constexpr std::uint32_t idHttp = 0x48545450;
constexpr std::uint32_t idInitConnection = 0x634C6F67;
constexpr std::uint32_t idKillUser = 0x6B696C6C;
constexpr std::uint32_t idRoomList = 0x724C7374;
constexpr std::uint32_t idUserList = 0x754C7374;
constexpr std::uint32_t idLogOff = 0x62796520;
constexpr std::uint32_t idLogon = 0x72656769;
constexpr std::uint32_t idNavigationError = 0x73457272;
constexpr std::uint32_t idNoOp = 0x4E4F4F50;
constexpr std::uint32_t idImageDelete = 0x46505371;
constexpr std::uint32_t idImageMove = 0x704C6F63;
constexpr std::uint32_t idImageNew = 0x6E506374;
constexpr std::uint32_t idImageSetInfo = 0x73506374;
constexpr std::uint32_t idPing = 0x70696E67;
constexpr std::uint32_t idPong = 0x706F6E67;
constexpr std::uint32_t idPropDelete = 0x64507270;
constexpr std::uint32_t idPropMove = 0x6D507270;
constexpr std::uint32_t idPropNew = 0x6E507270;
constexpr std::uint32_t idPropSetInfo = 0x73507270;
constexpr std::uint32_t idResport = 0x72657370;
constexpr std::uint32_t idRoomMessage = 0x726D7367;
constexpr std::uint32_t idRoomInfo = 0x726F6F6D;
constexpr std::uint32_t idRoomInfoEnd = 0x656E6472;
constexpr std::uint32_t idRoomGoto = 0x6E617652;
constexpr std::uint32_t idRoomNew = 0x6E526F6D;
constexpr std::uint32_t idRoomSetInfo = 0x73526F6D;
constexpr std::uint32_t idServerDown = 0x646F776E;
constexpr std::uint32_t idServerInfo = 0x73696E66;
constexpr std::uint32_t idServerUp = 0x696E6974;
constexpr std::uint32_t idServerMessage = 0x736D7367;
constexpr std::uint32_t idSpotDelete = 0x6F705364;
constexpr std::uint32_t idSpotMove = 0x636F4C73;
constexpr std::uint32_t idSpotNew = 0x6F70536E;
constexpr std::uint32_t idSpotSetInfo = 0x6F705373;
constexpr std::uint32_t idSpotState = 0x73537461;
constexpr std::uint32_t idSuperUser = 0x73757372;
constexpr std::uint32_t idTalk = 0x74616C6B;
constexpr std::uint32_t idThisIsMyId = 0x74696D79;
constexpr std::uint32_t idThisIsYourId = 0x74697972;
constexpr std::uint32_t idTropser = 0x70736572;
constexpr std::uint32_t idUserColor = 0x75737243;
constexpr std::uint32_t idUserInfo = 0x75737244;
constexpr std::uint32_t idUserEnter = 0x77707273;
constexpr std::uint32_t idUserExit = 0x65707273;
constexpr std::uint32_t idUserFace = 0x75737246;
constexpr std::uint32_t idRoomUserList = 0x72707273;
constexpr std::uint32_t idUserLog = 0x6C6F6720;
constexpr std::uint32_t idUserMove = 0x754C6F63;
constexpr std::uint32_t idUserName = 0x7573724E;
constexpr std::uint32_t idUserNew = 0x6E707273;
constexpr std::uint32_t idUserProp = 0x75737250;
constexpr std::uint32_t idUserStatus = 0x75537461;
constexpr std::uint32_t idVersion = 0x76657273;
constexpr std::uint32_t idWhisper = 0x77686973;
constexpr std::uint32_t idWhisperMessage = 0x776D7367;
constexpr std::uint32_t idXTalk = 0x78746C6B;
constexpr std::uint32_t idXWhisper = 0x78776973;

constexpr std::uint32_t idProp = 0x50726F70;
constexpr std::uint32_t idUserBase = 0x55736572;
constexpr std::uint32_t idIpUserBase = 0x49557372;

constexpr std::uint32_t idInfoName = 0x4E414D45;
constexpr std::uint32_t idInfoPassword = 0x50415353;
constexpr std::uint32_t idInfoType = 0x54595045;
constexpr std::uint32_t idInfoAvatarUrl = 0x4155524C;
constexpr std::uint32_t idInfoVersion = 0x56455253;
constexpr std::uint32_t idInfoFlag = 0x464C4147;
constexpr std::uint32_t idInfoUserCount = 0x4E555352;
constexpr std::uint32_t idInfoImageUrl = 0x4855524C;

constexpr std::uint32_t idErrorAuthentication = 0x41555448;
constexpr std::uint32_t idErrorUnknown = 0x554E4B4E;

#endif // _PACKET_H
