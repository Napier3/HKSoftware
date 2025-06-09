#pragma once

#include "../GuideBook.h"

#include "../../../../Module/XVM/XLuaToXvmToolBase.h"

class CGbsLuaToXvmTool : public CXLuaToXvmToolBase
{
public:
	CGbsLuaToXvmTool();
	virtual ~CGbsLuaToXvmTool();

protected:
	//2020-7-9 lijunqing  ¶îÍâµÄÌæ»»
	virtual void ReplaceEx();

	virtual BOOL NeedLuaToXVM(CExBaseList *pTemplate);

	virtual BOOL IsScript(CExBaseObject *p)
	{
		return Gb_IsScript(p);
	}

	virtual BOOL NeedBuild(CExBaseObject *pPpObjctDest)
	{
		return (((CScriptText*)pPpObjctDest)->m_strScriptText.GetLength() > MINLEN_SCRIPT_TEXT);
	}

	virtual CString* GetItemScript(CExBaseObject *pPpObjctDest)
	{
		return &((CScriptText*)pPpObjctDest)->m_strScriptText;
	}

	virtual void ShowReplaceItemPath(CExBaseObject *pItem);

};

