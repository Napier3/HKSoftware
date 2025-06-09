#pragma once
#include "../../../module/gridctrl/gridctrl.h"
#include "../GuideBook/GuideBookInterface.h"
#include "vector"

class CSysParaGrid :	public CGridCtrl
{
public:
	CSysParaGrid(void);
	~CSysParaGrid(void);

	virtual void FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd);

	void InitGrid(BOOL bEditable);
	void InitGridTitle(); //初始化标题

	void InitVariables_Sets(CExBaseList *pSets, CValues * pValues);

	//要在GridCtrl中显示的项目
	void InitVariables_Datas(CExBaseList* pShortDatas,CValues * pValues);
	void UpdateVariables();

	//修改的值保存到对应的ShortData中
	void SetShortDataValue(long nRow,long nCol);
	void SetVectorDataValue(long nRow,long nCol);

	//////////////////////////////////////////////////////////////////////////
	//最新，采用数据集格式
	void InitVariables_Dataset(CExBaseList *pDatas, CValues * pValues);
	void OnEndEdit(long nRow,long nCol);
	
private:
	CString m_strType;
	CExBaseList* m_pShortDatas;
	CExBaseList *m_pCurVectorSet;

	CValues * m_pValues;


	CExBaseList *m_pListDatas;


private:
	void ShowOneParaObject(CShortData * ParaObject,long nRow/*,_bstr_t strValue*/);
	//void ShowOneParaObject(CSet* pSet,long nRow/*,_bstr_t strValue*/);
	void InitValueColor(const CString &strValue, const CString &strDefValue, GV_ITEM &Item);
	void InitGvItem(GV_ITEM &Item);
	
	void ShowOneData(CDataObj* pData,long nRow/*,_bstr_t strValue*/);

	void ResetVaraibles();
	void UpdateVariables1();
	void UpdateVariables2();
	void UpdateVariables_Dataset();


};
