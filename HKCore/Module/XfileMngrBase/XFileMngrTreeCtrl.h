#pragma once


#include "XFolderTreeCtrl.h"
// CXFileMngrTreeCtrl

class CXFileMngrTreeCtrl : public CXFolderTreeCtrl
{
public:
	CXFileMngrTreeCtrl();
	virtual ~CXFileMngrTreeCtrl();

public:
	CXFile* GetCurrSelFile();

protected:
	virtual BOOL CanInsert(CExBaseObject* pObj);
	virtual void InitContextMenuTree(CMenu &menu,CExBaseObject* pObj);

};

