#ifndef _PpSttIotDeviceClientWnd_VC_h__
#define _PpSttIotDeviceClientWnd_VC_h__

#include "PpSttIotDeviceClientWnd.h"

//CPpSttIotDeviceClientWnd_MFC
class CPpSttIotDeviceClientWnd_MFC : public CPpSttIotDeviceClientWnd
{
	DECLARE_DYNAMIC(CTestControlWnd_Win)

public:
	CPpSttIotDeviceClientWnd_MFC();
	virtual ~CPpSttIotDeviceClientWnd_MFC();

	virtual BOOL CreateIotDeviceClientWnd();
	
protected:
    DECLARE_MESSAGE_MAP()

};

#endif // _PpSttIotDeviceClientWnd_VC_h__
