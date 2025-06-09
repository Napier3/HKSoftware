#pragma once


#include "..\DataGroup.h"
#include "DataGroupGrid.h"

class CDataGroupTreeCtrl : public CTreeCtrl
{
public:
	CDataGroupTreeCtrl();
	virtual ~CDataGroupTreeCtrl();

public:
	CDataGroup* GetCurrSelGroup();
	CExBaseObject* GetSelObject();

	HTREEITEM ShowCDataGroup(CDataGroup *pRootFolder, HTREEITEM hParent=TVI_ROOT);

protected:
	virtual BOOL CanInsert(CExBaseObject* pObj);

};

