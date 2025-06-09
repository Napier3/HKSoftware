#ifndef _SttRemoteCtrlDbRWTool_h_
#define _SttRemoteCtrlDbRWTool_h_

#include "Stt_RemoteRegRT.h"


BOOL Stt_DeleteAllRealTimeDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys);

CStt_RemoteRegRT *Stt_InitRegisterDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys,CStt_RemoteRegHis &oRemoteRegHis);

BOOL Stt_InitUnRegisterDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys,CStt_RemoteRegRT &oRemoteRegRT);

BOOL Stt_UpdateUserDB(CXDbBaseLib *pXDbLib, CXmlRWKeys *pXmlRWKeys
				  ,CStt_RemoteRegRT *pRemoteRegRT,CStt_RemoteRegRT &oUserList);

#endif