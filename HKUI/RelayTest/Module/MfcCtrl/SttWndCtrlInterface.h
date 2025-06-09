#pragma once

#include "..\..\..\Module\DataMngr\DataGroup.h"

class CSttWndCtrlInterface;

class CSttWndCtrlMsgRcvInterface : public CTLinkList<CSttWndCtrlInterface>
{
public:
	CSttWndCtrlMsgRcvInterface();
	virtual ~CSttWndCtrlMsgRcvInterface();

public:
	virtual void OnSttDataChanged(CDvmData *pData){};
	virtual void ShowDatas();
	virtual void SaveDatas();

	virtual void ClearRefData();
};

// SttWndCtrlInterface
class CSttWndCtrlInterface
{
public:
	CSttWndCtrlInterface();
	virtual ~CSttWndCtrlInterface();

	void AttacthMsgRcv(CSttWndCtrlMsgRcvInterface *pMsgRcv)	{	m_pSttWndCtrlMsgRcv = pMsgRcv;	}

protected:
	CDvmData *m_pRefData;
	CSttWndCtrlMsgRcvInterface *m_pSttWndCtrlMsgRcv;

	virtual void OnSttDataChanged();

public:
	virtual void InitSttWnd(CDvmData *pData);
	virtual void InitSttWnd(CDvmData *pData, CSttWndCtrlMsgRcvInterface *pMsgRcv);
	virtual void ShowData();
	virtual void SaveData();
	virtual void GetDataValue(CDvmData *pData);
	virtual void SetDataValue(const CString &strValue);
	virtual void SetDataValue(long nValue);
};



