#pragma once

#include "PpTemplate.h"

#include "../../../Module/XVM/XLuaToXvmToolBase.h"
// 
// #define MINLEN_SCRIPT_TEXT   10
// 
// class CPpsVarReplacePara
// {
// public:
// 	CPpsVarReplacePara()
// 	{
// 		m_pDestDataRef = NULL;
// 	}
// 	virtual ~CPpsVarReplacePara(){}
// 	
// 	CExBaseObject *m_pDestDataRef;
// 	CString m_strSrcID;
// 	CString m_strDestID;
// };
// 
// class CPpsVarReplaceBaseObj : public CBaseObject
// {
// public:
// 	CPpsVarReplaceBaseObj();
// 	virtual ~CPpsVarReplaceBaseObj();
// 	
// 	CExBaseObject *m_pPpObjctRef;
// 	CExBaseObject *m_pGbObjRef;
// 	CString *m_pTextRef;
// 	CPpScript *m_pPpScript;
// 	
// public:
// 	virtual long CalBuffer();
// 	virtual void BuidBuffer(TCHAR **ppBuffer);
// 	virtual BOOL Replace(CPpsVarReplacePara *pReplacePara, BOOL bValidSeparator=TRUE);
// 	virtual void ProcessVarDef();
// 	virtual BOOL FinishReplace();
// 
// protected:
// 	long m_nBufLength;
// 	TCHAR *m_pRefSrcBuf;
// 	TCHAR *m_pRefDestBuf;
// 
// 	BOOL GetNextVarDef(wchar_t *pBuf, wchar_t *pBufEnd, wchar_t **ppVarBegin, wchar_t **ppVarEnd);
// };

class CPpsLuaToXvmTool : public CXLuaToXvmToolBase
{
public:
	CPpsLuaToXvmTool();
	virtual ~CPpsLuaToXvmTool();

protected:
	virtual BOOL NeedLuaToXVM(CExBaseList *pTemplate);

	virtual BOOL IsScript(CExBaseObject *p)
	{
		return PPCLASSID_PPSCRIPT == p->GetClassID();
	}

	virtual BOOL NeedBuild(CExBaseObject *pPpObjctDest)
	{
		return (((CPpScript*)pPpObjctDest)->m_strScript.GetLength() > MINLEN_SCRIPT_TEXT);
	}

	virtual CString* GetItemScript(CExBaseObject *pPpObjctDest)
	{
		return &((CPpScript*)pPpObjctDest)->m_strScript;
	}

	virtual void ShowReplaceItemPath(CExBaseObject *pItem);

// 	static BOOL g_bShowReplaceItemPath;
// 
// public:
// 	BOOL LuaToXvm(CPpTemplate *pPpTemplate);
// 	void BuildRepalce(CExBaseList *pPpObjcts);
// 	void Replace(const CString &strSrcID, const CString &strDestID, BOOL bValidSeparator=TRUE);
// 	void ProcessVarDef();
// 	void FinishReplace();
// 
// //属性
// protected:
// 	//替换开辟的临时缓冲区
// 	TCHAR *m_pBufferForReplace;
// 	long  m_nLenBufferForReplace;
// 
// 	CExBaseList *m_pPpObjctDest;
// 	CExBaseList *m_pPpTemplate;
// 
// 
// protected:
// 	virtual void BuildItems(CExBaseList *pPpObjctDest);
// 	virtual void BuildItem(CExBaseObject *pPpObjctDest);
// 
// 	virtual void ShowReplaceItemPath(CExBaseObject *pItem);
// 
// 	void BuildBuffer();
// 
// protected:
// 	CFile m_fileVarReplace;
// 	BOOL m_bFileVarReplace;
};

