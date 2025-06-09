#pragma once

#include "..\GuideBook\GuideBook.h"
#include "..\GuideBook\Items.h"
#include "..\..\..\Module\DataMngr\DatasetValid\DsvScript.h"

#define GBITEMREPLACE_MODE_ALL_CHILDREN      0
#define GBITEMREPLACE_MODE_LEVEL1_CHILDREN   1


class CGbItemReplaceTool : public CExBaseList
{
public:
	CGbItemReplaceTool();
	virtual ~CGbItemReplaceTool();

	virtual BOOL UpdateMacroTestParaData(CGbItemBase *pMacroTest, CShortData  *pData, const CString &strMacroID, BOOL bShowLog = TRUE);
	virtual BOOL UpdateScript(CGbItemBase *pGbItem, CScriptText  *pScript, const CString &strItemID, BOOL bShowLog = TRUE);
	virtual BOOL UpdateDsvScript(CGbItemBase *pGbItem, CDsvScript  *pDsvScript, const CString &strCommCmdID, const CString &strNameHas, BOOL bShowLog = TRUE);

	void SetParentWnd(CWnd *pWnd)	{	m_pParentWnd = pWnd;	}
protected:
	CGbItemBase   *m_pGbCurrItem;   //当前项目
	CExBaseObject *m_pGbSrcObj;   //替换的源数据对象
	long          m_nMode;
	CItems        *m_pReplaceRootItems;     //替换的项目分类根节点
	CString       m_strItemID;
	BOOL          m_bUseSameID;

	CWnd *m_pParentWnd;

protected:
	void SelectReplaceRootItems();
	virtual void UpdateMacroTestParaData(CExBaseList *pItems, const CShortData  *pData, const CString &strMacroID, BOOL bShowLog = TRUE);
	virtual void UpdateScript(CExBaseList *pList, CScriptText  *pScript, UINT nClassItem, UINT nScriptClassID, BOOL bShowLog = TRUE);
	virtual void UpdateDsvScript(CExBaseList *pList, CDsvScript  *pDsvScript, const CString &strNameHas, BOOL bShowLog = TRUE);
};
