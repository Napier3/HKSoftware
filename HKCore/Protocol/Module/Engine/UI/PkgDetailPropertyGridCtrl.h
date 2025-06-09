#pragma once

#include "..\PpTemplate.h"
#include "..\PpPackageDetail.h"

#include "..\RByteBlock.h"
#include "..\WByteBlock.h"
#include "..\RBbDataSets.h"
#include "..\RBbDataSet.h"
#include "..\RBbData.h"
#include "..\WBbData.h"
#include "..\RDataByteBlock.h"
#include "..\WDataByteBlock.h"

// CPkgDetailPropertyGridCtrl
#define WM_PP_PROP_SELCHANGED  (WM_USER + 1433)

class CPkgDetailPropertyGridCtrl : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(CPkgDetailPropertyGridCtrl)

public:
	CPkgDetailPropertyGridCtrl();
	virtual ~CPkgDetailPropertyGridCtrl();
	void ShowPkgDetail(CPpPackageDetail *pPkg);

	virtual void OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel);

protected:
	typedef struct  PropGridItemParent
	{
		CMFCPropertyGridCtrl *pGrid;
		CMFCPropertyGridProperty *pProperty;
	}PROPGRIDITEMPARENT, *PPROPGRIDITEMPARENT;

	void InitPropGridItemParent(PROPGRIDITEMPARENT &oPropGridItemParent)
	{
		oPropGridItemParent.pGrid = NULL;
		oPropGridItemParent.pProperty = NULL;
	}
	void InitPropGridItemParent(PPROPGRIDITEMPARENT pPropGridItemParent)
	{
		pPropGridItemParent->pGrid = NULL;
		pPropGridItemParent->pProperty = NULL;
	}

	void AddItem(PROPGRIDITEMPARENT &oPropGridItemParent, CMFCPropertyGridProperty *pItem)
	{
		if (oPropGridItemParent.pGrid != NULL)
		{
			oPropGridItemParent.pGrid->AddProperty(pItem);
		}
		else if (oPropGridItemParent.pProperty != NULL)
		{
			oPropGridItemParent.pProperty->AddSubItem(pItem);
		}
		else
		{
			ASSERT (FALSE);
		}
	}

	void AddItem(PPROPGRIDITEMPARENT pPropGridItemParent, CMFCPropertyGridProperty *pItem)
	{
		AddItem(*pPropGridItemParent, pItem);
	}

	CMFCPropertyGridProperty* ShowExBaseList(CExBaseList *pList, PPROPGRIDITEMPARENT pParent, BOOL bShowVariablesNode);

	CMFCPropertyGridProperty* ShowByteBlock(CByteBlock *pByteBlock, PPROPGRIDITEMPARENT pParent);
	CMFCPropertyGridProperty* ShowRByteBlock(CRByteBlock *pByteBlock, PPROPGRIDITEMPARENT pParent);
	CMFCPropertyGridProperty* ShowWByteBlock(CWByteBlock *pByteBlock, PPROPGRIDITEMPARENT pParent);

	CMFCPropertyGridProperty* ShowVariables(CBbVariables *pVariables, PPROPGRIDITEMPARENT pParent, BOOL bNewNode);
	CMFCPropertyGridProperty* ShowVariable(CBbVariable *pVariable, PPROPGRIDITEMPARENT pParent);
	
// 	CMFCPropertyGridProperty* ShowDataSets(CRBbDataSets *pDataSets, PPROPGRIDITEMPARENT pParent);
// 	CMFCPropertyGridProperty* ShowDataSet(CRBbDataSet *pDataSet, PPROPGRIDITEMPARENT pParent);
	
	CMFCPropertyGridProperty* ShowData(CBbData *pData, PPROPGRIDITEMPARENT pParent);
	CMFCPropertyGridProperty* ShowRData(CRBbData *pData, PPROPGRIDITEMPARENT pParent);
	CMFCPropertyGridProperty* ShowWData(CWBbData *pData, PPROPGRIDITEMPARENT pParent);

	CMFCPropertyGridProperty* ShowDataBlock(CDataByteBlock *pDataBlock, PPROPGRIDITEMPARENT pParent);
	CMFCPropertyGridProperty* ShowRDataBlock(CRDataByteBlock *pDataBlock, PPROPGRIDITEMPARENT pParent);
	CMFCPropertyGridProperty* ShowWDataBlock(CWDataByteBlock *pDataBlock, PPROPGRIDITEMPARENT pParent);
	
private:

protected:
	DECLARE_MESSAGE_MAP()
};

CExBaseObject* Pp_GetRefPpData(CMFCPropertyGridProperty *pCurr);
