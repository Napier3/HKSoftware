#pragma once

#include "MonitorCapConfig.h"
// CEpCapConfigTreeCtrl

class CEpCapConfigTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CEpCapConfigTreeCtrl)

protected:
	CMonitorCapConfig *m_pCapConfig;

	BOOL CanShow(UINT nClassID);
	BOOL CanShow(CExBaseObject *pObj);
	void ShowObj(CExBaseObject *pObj, HTREEITEM hParent);

public:
	CEpCapConfigTreeCtrl();
	virtual ~CEpCapConfigTreeCtrl();

	void ShowCapConfig(CMonitorCapConfig *pCapConfig);
	void UpdateObj(CExBaseObject *pObj);
	void ShowObj(CExBaseObject *pObj);
	void DeleteObj(CExBaseObject *pObj);

protected:
	DECLARE_MESSAGE_MAP()
};


