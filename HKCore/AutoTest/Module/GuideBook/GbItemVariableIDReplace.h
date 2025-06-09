#pragma once

#include "GuideBook.h"
#include "MacroTest.h"
#include "MacroCharItems.h"
#include "Safety.h"
#include "Safety.h"
#include "CommCmd.h"
#include "SysParaEdit.h"
#include "GbCommCmdSplit.h"

#include "..\..\..\Module\System\StringVariableReplace.h"
#include "..\..\..\Module\System\StringVariableReplaceU.h"

class CGbItemVariableIDReplace
{
public:
	CGbItemVariableIDReplace();
	virtual ~CGbItemVariableIDReplace();

	void Replace(CExBaseList *pGbItemDest, const CString &strSrcID, const CString &strDestID);
	void ReplaceGbtBatchItemGroup(CExBaseList *pBatchGroup, const CString &strSrcID, const CString &strDestID);
	void ReplaceScriptLibLocal(CExBaseList *pGbItemDest, const CString &strSrcID, const CString &strDestID);
	
	void SetReplaceMacroTest(BOOL b=TRUE)	{	m_bReplaceMacroTest = b;	}
	void SetReplaceSafety(BOOL b=TRUE)		{	m_bReplaceSafety = b;		}
	void SetReplaceCommCmd(BOOL b=TRUE)		{	m_bReplaceCommCmd = b;		}
	void SetReplaceSysparaEdit(BOOL b=TRUE)		{	m_bReplaceSysparaEdit = b;		}


	static BOOL g_bShowReplaceItemPath;

	void SetDestObject(CExBaseObject *p)	{	m_pDestObject = p;	}
// Ù–‘
protected:
#ifdef _UNICODE
	CStringVariableReplaceU m_oReplace;
#else
	CStringVariableReplace m_oReplace;
#endif

	CExBaseList *m_pGbItemDest;
	CString m_strSrcID;
	CString m_strDestID;
	BOOL m_bReplaceMacroTest;
	BOOL m_bReplaceSafety;
	BOOL m_bReplaceCommCmd;
	BOOL m_bReplaceSysparaEdit;
	CExBaseList *m_pGuideBook;
	CExBaseList *m_pLocalScriptLib;

	CExBaseObject *m_pDestObject;

	virtual void ReplaceItems(CExBaseList *pGbItemDest);
	virtual void ReplaceItem(CExBaseObject *pGbItemDest);
	virtual void Replace(CGbItemBase *pGbObj);

	virtual void Replace(CMacroTestPara *pMacroTestPara);
	virtual void Replace(CMacroTest *pGbObj);
	virtual void Replace(CMacroCharItems *pGbObj);

	virtual void Replace(CCommCmd *pGbObj);
	virtual void Replace(CSafety *pGbObj);
	virtual void Replace(CSysParaEdit *pGbObj);
	virtual void Replace(CString &strText);
	virtual void Replace(CScriptText *pText);
	virtual void Replace(CDsvScript *pDsvScript);
	virtual void Replace(CDsvElement *pDsvElement);
	virtual void Replace(CDsvEliminate *pDsvEliminate);
	virtual void Replace_RptData(CReportMap *pRptMap, CExBaseObject *pRptData);
	virtual void ShowReplaceItemPath(CExBaseObject *pItem);
	
	virtual void Replace(CCharacteristics *pCharacteristics);

protected:
	void Replace_Characteristics(UINT nClassID, CExBaseObject *pGbItemDest);
	void ReplaceBatchItemRef(CExBaseList *pBatchItemRef);

};

