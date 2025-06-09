#pragma once
#include "EditDialogInterfaceList.h"
#include "EditTabCtrl.h"

class CEditDialogInterfaceTabList : public CEditDialogInterfaceList
{
public:
	CEditDialogInterfaceTabList();
	virtual ~CEditDialogInterfaceTabList(void);

public:
	virtual void CreateEdit(CExBaseObject* pObj, CWnd* pParent);

	//
	virtual void CreateTabCtrl();
	virtual void InitTabCtrl() = 0;


	// Ù–‘
protected:
	CEditTabCtrl m_TabCtrl;
};
