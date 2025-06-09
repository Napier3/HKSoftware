#pragma once

/*
	功能描述：
*/
#include "../../../module/gridctrl/gridctrl.h"
#include "../GuideBook/GuideBookInterface.h"

class CUISftRsltWndInterface;

class CUISftRsltWndDsGrid :	public CGridCtrl
{
public:
	CUISftRsltWndDsGrid();
	virtual ~CUISftRsltWndDsGrid();

	void CreateGsGrid(CShortData *pData, UINT nID, CWnd *pParent);

private:
	void InitGrid();
	void InitGridTitle(); //初始化标题
	void ShowOneData(CDataObj* pData,long nRow/*,_bstr_t strValue*/);
	void UpdateVariables_Dataset();

	void InitGvItem(GV_ITEM &Item);

public:
	CUISftRsltWndInterface* m_pResultWndInterface;
	CExBaseObject *m_pData;
	CString m_strDvmDsPath;
	CExBaseList *m_pCurDataSet;
};