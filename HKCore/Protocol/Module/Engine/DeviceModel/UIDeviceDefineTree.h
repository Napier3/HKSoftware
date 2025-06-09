#pragma once

#include "..\..\..\..\Module\DataMngr\DvmDevice.h"
// CUIDeviceDefineTree

class CUIDeviceDefineTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CUIDeviceDefineTree)

public:
	CUIDeviceDefineTree();
	virtual ~CUIDeviceDefineTree();

	void ShowDevice(CExBaseList *pDeviceDefine);
	CDvmDataset* GetCurrSelDataset();
	CExBaseObject* GetCurrSelObject();
	void InsertDvmObject(CExBaseObject *pDvmObject);

private:
	void InsertDevice(CDvmDevice *pLDevice, HTREEITEM hParent);
	void InsertLdevice(CDvmLogicDevice *pLDevice, HTREEITEM hParent);
	void InsertDataset(CDvmDataset *pDataset, HTREEITEM hParent);

protected:
	DECLARE_MESSAGE_MAP()
};


