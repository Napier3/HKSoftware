//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestClientSingleTimer.cpp

#include "../SttTestClientSingleTimer.h"
#include "../SttTestClientBase.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long stt_test_singleclient_timer_create(long nTimerLong)
{
	return ::SetTimer(NULL, 1730, 5000, stt_test_single_client_timer_win);
}

void stt_test_singleclient_timer_free(long nTimerID)
{
	::KillTimer(NULL, nTimerID);
}
