#pragma once

#include "MonitorQueryConfig.h"
// CEpQueryConfigTreeCtrl

class CEpQueryConfigTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CEpQueryConfigTreeCtrl)

protected:
	CMonitorQueryConfig *m_pCapConfig;

	BOOL CanShow(UINT nClassID);
	BOOL CanShow(CExBaseObject *pObj);
	void ShowObj(CExBaseObject *pObj, HTREEITEM hParent);

public:
	CEpQueryConfigTreeCtrl();
	virtual ~CEpQueryConfigTreeCtrl();

	void ShowCapConfig(CMonitorQueryConfig *pCapConfig);
	void UpdateObj(CExBaseObject *pObj);
	void ShowObj(CExBaseObject *pObj);
	void DeleteObj(CExBaseObject *pObj);

protected:
	DECLARE_MESSAGE_MAP()
};


