#pragma once

#include "..\..\Module\BaseClass\BaseList.h"
#include "GuideBook.h"
#include "MacroTest.h"
#include "MacroCharItems.h"
#include "Safety.h"
#include "Safety.h"
#include "CommCmd.h"
#include "SysParaEdit.h"
#include "GbCommCmdSplit.h"

#include "..\..\Module\System\StringVariableReplace.h"
#include "..\..\Module\System\StringVariableReplaceU.h"

#define MINLEN_SCRIPT_TEXT   10

class CGbVarReplacePara
{
public:
	CGbVarReplacePara()
	{
		m_pDestDataRef = NULL;
	}
	virtual ~CGbVarReplacePara(){}
	
	CExBaseObject *m_pDestDataRef;
	CString m_strSrcID;
	CString m_strDestID;
};

class CGbVarReplaceBaseObj : public CBaseObject
{
public:
	CGbVarReplaceBaseObj();
	virtual ~CGbVarReplaceBaseObj();
	
	CExBaseObject *m_pGbItemRef;
	CExBaseObject *m_pGbObjRef;
	CString *m_pTextRef;

	
public:
	virtual long CalBuffer();
	virtual void BuidBuffer(TCHAR **ppBuffer);
	virtual BOOL Replace(CGbVarReplacePara *pReplacePara);
	virtual BOOL FinishReplace();

protected:
	long m_nBufLength;
	TCHAR *m_pRefSrcBuf;
	TCHAR *m_pRefDestBuf;
};

class CGbVarReplace_RptData : public CGbVarReplaceBaseObj
{
public:
	CGbVarReplace_RptData();
	virtual ~CGbVarReplace_RptData();

public:
	virtual BOOL Replace(CGbVarReplacePara *pReplacePara);

private:
	BOOL m_bHasReplaced;
};

class CGbVarReplace_DsvScript : public CGbVarReplaceBaseObj
{
public:
	CGbVarReplace_DsvScript();
	virtual ~CGbVarReplace_DsvScript();

public:
	virtual long CalBuffer();
	virtual BOOL Replace(CGbVarReplacePara *pReplacePara);

private:
	void Replace(CDsvElement *pDsvElement, CGbVarReplacePara *pReplacePara);
	void Replace(CDsvEliminate *pDsvEliminate, CGbVarReplacePara *pReplacePara);

};

class CGbItemDvmVarQuery : public CBaseList
{
public:
	CGbItemDvmVarQuery();
	virtual ~CGbItemDvmVarQuery();

	void SetReplaceMacroTest(BOOL b=TRUE)	{	m_bReplaceMacroTest = b;	}
	void SetReplaceSafety(BOOL b=TRUE)		{	m_bReplaceSafety = b;		}
	void SetReplaceCommCmd(BOOL b=TRUE)		{	m_bReplaceCommCmd = b;		}
	void SetReplaceSysparaEdit(BOOL b=TRUE)		{	m_bReplaceSysparaEdit = b;		}


	static BOOL g_bShowReplaceItemPath;

// 	void SetDestObject(CExBaseObject *p)	{	m_pDestObject = p;	}

public:
	void BuildRepalce(CExBaseList *pGbItems);
	void Replace(CExBaseObject *pDestObject, const CString &strSrcID, const CString &strDestID);
	void FinishReplace();

//属性
protected:
	//替换开辟的临时缓冲区
	TCHAR *m_pBufferForReplace;
	long  m_nLenBufferForReplace;

	CExBaseList *m_pGbItemDest;
// 	CString m_strSrcID;
// 	CString m_strDestID;
	BOOL m_bReplaceMacroTest;
	BOOL m_bReplaceSafety;
	BOOL m_bReplaceCommCmd;
	BOOL m_bReplaceSysparaEdit;
	CExBaseList *m_pGuideBook;

// 	CExBaseObject *m_pDestObject;

protected:
	virtual void BuildItems(CExBaseList *pGbItemDest);
	virtual void BuildItem(CExBaseObject *pGbItemDest);
	virtual void Build(CGbItemBase *pGbObj);
	virtual void Build(CMacroTest *pGbObj);
	virtual void Build(CMacroCharItems *pGbObj);
	virtual void Build(CCommCmd *pGbObj);
	virtual void Build(CSafety *pGbObj);
	virtual void Build(CSysParaEdit *pGbObj);
	virtual void Build(CString &strText);
	virtual void Build(CScriptText *pText);
	virtual void Build(CDsvScript *pDsvScript);
	virtual void Build_RptData(CReportMap *pRptMap, CExBaseObject *pRptData);
	virtual void Build(CCharacteristics *pCharacteristics);

	virtual void ShowReplaceItemPath(CExBaseObject *pItem);

	void BuildBuffer();
	void Build_Characteristics(UINT nClassID, CExBaseObject *pGbItemDest);

protected:
	CFile m_fileVarReplace;
	BOOL m_bFileVarReplace;
};

