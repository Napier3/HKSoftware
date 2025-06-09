//SttAssistInterface.h
#ifndef _SttAssistInterface_H__
#define _SttAssistInterface_H__

#include "../../../Module/DataMngr/DataGroup.h"


class CSttAssistInterface
{
public:
	CSttAssistInterface();
	virtual ~CSttAssistInterface();
	
public:
	virtual void assist_init();
	virtual void assist_wnd_show(const CString &strWndID, CSttAssistInterface *pWnd, bool bShow);
	virtual void assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas);
	virtual void assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue);
	virtual bool assist_event(const CString &strEventID, CExBaseObject *pSttParas);

};


#endif//_SttAssistInterface_H__
