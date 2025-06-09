#pragma once

#include "../BaseClass/BaseList.h"
#include "../BaseClass/ExBaseList.h"

#include "../System/StringVariableReplaceU.h"
#include "../System/StringVariableReplace.h"

#define MINLEN_SCRIPT_TEXT   10

class CXLuaVarReplacePara
{
public:
	CXLuaVarReplacePara()
	{
		m_pDestDataRef = NULL;
	}
	virtual ~CXLuaVarReplacePara(){}
	
	CExBaseObject *m_pDestDataRef;
	CString m_strSrcID;
	CString m_strDestID;
};

class CXLuaVarReplaceBaseObj : public CBaseObject
{
public:
	CXLuaVarReplaceBaseObj();
	virtual ~CXLuaVarReplaceBaseObj();
	
	CExBaseObject *m_pPpObjctRef;
	CExBaseObject *m_pGbObjRef;
	CString *m_pTextRef;
	CExBaseObject *m_pPpScript;
	
public:
	virtual long CalBuffer();
	virtual void BuidBuffer(TCHAR **ppBuffer);
	virtual BOOL Replace(CXLuaVarReplacePara *pReplacePara, BOOL bValidSeparator=TRUE);
	virtual void ProcessVarDef();
	virtual BOOL FinishReplace();

protected:
	long m_nBufLength;
	TCHAR *m_pRefSrcBuf;
	TCHAR *m_pRefDestBuf;

	BOOL GetNextVarDef(TCHAR *pBuf, TCHAR *pBufEnd, TCHAR **ppVarBegin, TCHAR **ppVarEnd);
	void Offset(TCHAR* &pBuf);
	void CopyVars(TCHAR* &pCurr, long nSrcLen, TCHAR* &pEnd, TCHAR * &pDestCurr, TCHAR* &pBegin, long &nReplaceCount);
};

class CXLuaToXvmToolBase : public CBaseList
{
public:
	CXLuaToXvmToolBase();
	virtual ~CXLuaToXvmToolBase();

	static BOOL g_bShowReplaceItemPath;

public:
	BOOL LuaToXvm(const CString &strFile, CString &strDestFile);
	BOOL LuaToXvm(CExBaseList *pTemplate);
	void BuildRepalce(CExBaseList *pPpObjcts);
	void Replace(const CString &strSrcID, const CString &strDestID, BOOL bValidSeparator=TRUE);
	void ProcessVarDef();
	void FinishReplace();

protected:
	void LuaToXvm();

	//2020-7-9 lijunqing  额外的替换
	virtual void ReplaceEx();

//属性
protected:
	//替换开辟的临时缓冲区
	TCHAR *m_pBufferForReplace;
	long  m_nLenBufferForReplace;

	CExBaseList *m_pObjctDest;
	CExBaseList *m_pTemplate;

	CString m_strLuaToXvmScript;

protected:
	virtual BOOL NeedLuaToXVM(CExBaseList *pTemplate) = 0;
	virtual BOOL IsScript(CExBaseObject *p) = 0;
	virtual BOOL NeedBuild(CExBaseObject *pPpObjctDest) = 0;
	virtual CString* GetItemScript(CExBaseObject *pPpObjctDest) = 0;
	virtual void ShowReplaceItemPath(CExBaseObject *pItem) = 0;

	virtual void BuildItem(CExBaseObject *pPpObjctDest);
	virtual void BuildItems(CExBaseList *pPpObjctDest);

	void BuildBuffer();

protected:
	CFile m_fileVarReplace;
	BOOL m_bFileVarReplace;
};

