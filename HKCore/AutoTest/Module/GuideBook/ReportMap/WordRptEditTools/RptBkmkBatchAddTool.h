#pragma once

//功能描述 试验报告区域对象，子对象为CRptBkmk

#include "RptBatchConfig.h"
#include "..\..\MacroTest.h"

class CRptBkmkBatchAddTool : public CExBaseList
{
public:
	CRptBkmkBatchAddTool(void);
	virtual ~CRptBkmkBatchAddTool(void);

//属性
public:
	
//公共接口
public:
	BOOL Init(CExBaseObject *pItem, CRptEditInterface* pRptEdit);
	void GetBatchCellList(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit);

	BOOL OpenRptBatchConfigFile(CWnd *pParent);
	BOOL SaveRptBatchConfigFile(CWnd *pParent);

	CRptBatchConfig* GetRptBatchConfig()	{	return &m_oRptBatchConfig;	}

	BOOL IsRowItemColDataMode()	{	return m_oRptBatchConfig.IsRowItemColDataMode();	}
	BOOL IsRowDataColItemMode()	{	return m_oRptBatchConfig.IsRowDataColItemMode();	}

	BOOL SetMode(UINT nMode);
	CRptBatchItemMaps* GetItemsMap()	{	return m_oRptBatchConfig.GetRptBatchItemMaps();	}
	CRptBatchDataMaps* GetDatasMap()	{	return m_oRptBatchConfig.GetRptBatchDataMaps();	}

protected:
//	void GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell, MSWord::Selection &wordSelection);
//	void GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell, MSWord::Selection &wordSelection);
//	void GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell, MSWord::Selection &wordSelection);
	void GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit);
	void GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit);
	void GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell, CRptEditInterface* pRptEdit);

protected:
	CRptBatchConfig m_oRptBatchConfig;
	CString m_strRptBatchFile;
	CExBaseList *m_pItems;
//	MSWord::_Document m_oDoc;
	long  m_nRepeatCount;

	long m_nSelectionRows;
	long m_nSelectionCols;
	long m_nRows;
	long m_nCols;

	void SetRowsCols(long nRows, long nCols);
	virtual void InitDataMaps();

public:
	void SetRepeatCount(long nRepeatCount)	{	m_nRepeatCount = nRepeatCount;	}
	virtual void InitItemMaps();
	virtual void GetAllMacroTest(CExBaseList *pList);
	virtual CMacroTest* GetMacroTest();
	virtual void InitDataMaps(CExBaseObject *pData, const CString &strPrecision, const CString &strAttr, const CString &strDataProcess);
};

class CRptBkmkBatchAddToolYc : public CRptBkmkBatchAddTool
{
public:
	CRptBkmkBatchAddToolYc();
	virtual ~CRptBkmkBatchAddToolYc();

	CExBaseList m_listItemsRef;  //测试项目的索引

public:
	virtual void GetAllMacroTest(CExBaseList *pList);
	virtual void GetAllCommCmd(CExBaseList *pList);

	virtual void InitItemMaps();
	virtual void InitItemMapsEx(CExBaseList *pList);
	//void GetAllMacroTest(CExBaseList *pListDst, CExBaseList *pListSrc);

	virtual CMacroTest* GetMacroTest();
	virtual CCommCmd* GetCommCmd();
	virtual void InitDataMaps(CExBaseObject *pData, const CString &strPrecision, const CString &strAttr, const CString &strDataProcess);
};


//BOOL rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem, MSWord::Selection wordSelection);
//BOOL rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem, MSWord::Selection wordSelection);
//BOOL rpt_GetRptBkmkBatchRowsCols(MSWord::Selection wordSelection, long &nRows, long &nCols);
CExBaseList* rpt_GetItems(CExBaseObject *pItem);
void rpt_GetAllMacroTestItems(CExBaseList *pItems, CExBaseList *pListMacroTest);
void rpt_GetAllMacroTestItemsEx(CExBaseList *pListSrc, CExBaseList *pListDst);
