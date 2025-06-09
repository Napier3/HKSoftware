#pragma once
#include "../../../../module/baseclass/exbaseobject.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Module/TCtrlCntrConfig.h"
#include "RptBkmk.h"
#include "RptArea.h"
#include "WordRptEditTools\RptBatchItemMaps.h"
#include "WordRptEditTools\RptBatchDataMaps.h"

#define BMK_NULL		0
#define BMK_BQ			1
#define BMK_PATH		2

class CRptData;
class CRptItems;
class CRptItem;
class CReportMap;
class CGuideBook;
class CGbItemBase;

class CRptEditInterface :	public CExBaseObject
{
public:
	CRptEditInterface(void);
	~CRptEditInterface(void);
	void InitRptEdit();
	virtual CString GetReportEditClassID()=0;
	virtual CString GetReportSuffix()=0;

	BOOL IsAuthority();

public:
	//属性
	CString         m_strGuideBookFile;
	CString			m_strReportMapFile;
	CString			m_strReportTemplateFile;
	CString			m_strPath;
	CGuideBook*		m_pGuideBook;
	BOOL			m_bSave;
	BOOL			m_bModified;

	//公共变量
	DWORD	m_dwMaxBkmkIndex;
	CExBaseList m_listWordBkmks;
	CExBaseList m_listRptBkmks;
	CRptItem  *m_pGbItemsMap;  //作业指导书的映射关系
	CDataType m_oPrecisionDataType;

	CWnd *			m_pWordWnd;
	HWND			m_hWordWnd;
	BOOL			m_bHasWord;

	int m_iFindIndex;	//20231010 huangliang 记录当前选中标签属于重复标签中的第几个

	CString m_strSelectPath;
	void CreatePathID(CGbItemBase *pItem, const CString &strDataID);

	CWordBkmk *m_pCurrBkmk;
	CWordBkmk *m_pBkmkForCopy;

	CAutoCriticSection m_oWordCriticSection;

	//重载函数
	virtual BOOL CreateWordApplication(BOOL bVisible=FALSE)=0;
	virtual BOOL OpenWordReportFile(const CString &strRptFile)=0;
	virtual BOOL NewWordReportFile()=0;

	virtual void InitAllBookmarks()=0;
	virtual void ExitWord(BOOL bExitApp=TRUE)=0;
	virtual long OpenWord(const CString &strGuideBookFile)=0;
	virtual CExBaseObject* AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode)=0;
	virtual void InsertBkmk(const CString &strBkmk){};
	virtual CExBaseObject* AddArea(CExBaseList *pRptArea)=0;
	virtual CExBaseObject* AddArea(CGbItemBase *pItem, long nStart, long nEnd)=0;
	virtual long GetCurrPos()=0;

	virtual long InitPage(BOOL bHort=FALSE)=0;
	virtual long Save()=0;
	virtual long SaveAs(const CString &strFile)=0;
	virtual long CloseWord()=0;
	virtual BOOL IsValidDoc()=0;
	virtual void ClearBkmkText(CRptBkmk *pBkmk)=0;
	virtual CString InitCurrBkmk()=0;
  	virtual long GetAllSelBkmk(CExBaseList &oListWordBkmk)=0;

	virtual BOOL CanAddArea()=0;
	virtual BOOL ReplaceBkmk(const CString &  strBkmkSrc, const CString &  strBkmkDest)=0;
	virtual BOOL UpdateBkmk(CRptBkmk *pRptBkmk)=0;

	virtual void InsertTitle(const CString &strTitle, long nTitleLevel)=0;
	virtual BOOL ActiveWindow(const CString &strTitle)=0;
	virtual long GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)=0;
	virtual long AdjustReport_DelArea(CRptArea *pArea)=0;

	virtual CExBaseObject * ReLocateBkmk()=0;

	virtual CWnd* AdjustSizeView()=0;
	virtual void SetAppVisible(BOOL bVisible)=0;
	virtual void SetDisplayStatusBar(BOOL bVisible)=0;

	virtual void CopyApp(CRptEditInterface *pRptEditDest)=0;
	virtual void rpt_RenameRptBkmks(CExBaseList *pList)=0;
	virtual void InsertWordEdit(CRptEditInterface *pRptEdit, long nAddRptGroupTitle)=0;

	virtual BOOL rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem)=0;
	virtual BOOL rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem)=0;
	virtual BOOL rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols)=0;
	virtual void InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks)=0;
	
	virtual void GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols)=0;
	virtual void GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows)=0;
	virtual void GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols)=0;

	//公共函数
	BOOL ChangeWordReportFile(const CString &strDocFile);
	void InitAllRptBkmks();
	virtual void AttachBookmarksAndRptBkmks();
	BOOL FindFile(const CString& strFileName);
	void Free();

	void InitBkmkMaxindex(BOOL bInitAs0);
	void SetMaxIndexInList(CExBaseList* pList);
	void InitMaxIndexInList();

	void DeleteWordBkmk(CWordBkmk *pBkmk);
	void DeleteAllErrorBkmk();

	CWordBkmk* GetCopyWordBkmk();
	CWordBkmk* CopyWordBkmk();
	void PasteWordBkmk();
	void InitPrecisionDataType();

	void InitAllRptBkmks(CExBaseList *pList);
	CWordBkmk* AddNewWordBookmarkToList(const CString &strBkmk)
	{
		CWordBkmk *p = new CWordBkmk();
		p->m_strID = strBkmk;
		m_listWordBkmks.AddTail(p);
		return p;
	}

	long Open(const CString &strGuideBookFile);
	long LocateBkmk(CRptData *pData, LONG nIndex);
	long DeleteBkmk(CExBaseObject *pObj, CTreeCtrl *pTree, BOOL bDeleteBkmk);
	virtual CExBaseObject* BindBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode, const CString &strBkmk);
	CExBaseObject* MapBkmk(CRptData *pData, CWordBkmk *pBkmk);
	CExBaseObject* InsertBkmk(CRptBkmk *pBkmk);
	void DelArea(CExBaseList *pRptArea);

	long Close(BOOL bSave);
	void ClearBkmksText();
	void ClearBkmksText(CExBaseList *pList);

	void SetWordWndFocus();
	CWordBkmk* GetCurrBkmk();
	BOOL ReplaceBkmk(CRptBkmk *pRptBkmk, CWordBkmk *pBkmk);
	CRptBkmk* GetCurrPosRptBkmk();

	long  AdjustReport_DelArea(CGbItemBase *pItem);
	CAutoCriticSection* GetAutoCriticSection()	{	return &m_oWordCriticSection;		}

	void SetRptItemBkmkState(CExBaseObject *pObj);
	CString GetUIDString();
	CString GetWordFileTitle();

	CRptBkmk* InsertCellBkmk(CGbItemBase *pItem, CExBaseObject *pData, const CString &strAttrID, const CString &strPrecision, long nRepeatIndex, const CString &strDataProcess, const CString &strFillMode);

private:
	BOOL            m_bHasModified; 

public:
	//File Mathods
//	virtual long Open(const CString &strGuideBookFile) = 0;
//	virtual long Save() = 0;
//	virtual long Close(BOOL bSave) = 0;

	//Bkmk Mathods
	virtual long LocateBkmk(const CString &  strBkmk) = 0;

	virtual CExBaseObject* FindRptBkmk(const CString & strBkmk);
	virtual long DeleteBkmk(const CString &  strBkmk, BOOL bSelect=FALSE)=0;

	virtual BOOL CheckChoosePoint(){ return TRUE;}

	//GuideBook Mathods
	CExBaseObject* AddRptData(CGbItemBase *pItem, CShortData *pData,const CString &strPrecision, long nRepeatIndex);
	CExBaseObject* AddRptData(CGbItemBase *pItem, CValue *oValue,const CString &strPrecision, long nRepeatIndex);
	CExBaseObject* AddRptData(CGbItemBase* pItem,const CString &strName, const CString &strID, const CString &strPrecision, long nRepeatIndex);
	CExBaseObject* AddRptData(CGbItemBase* pItem,CExBaseObject* pObj, const CString &strPrecision, long nRepeatIndex);
	CExBaseObject* AddRptData(CGbItemBase* pItem, const CString &strID, const CString &strPrecision, long nRepeatIndex);

	void SetMidified(BOOL b=TRUE)	{	m_bHasModified = b;		}
	BOOL HasModified()						{	return m_bHasModified;	}

protected:
	CExBaseObject* FindBkmk(CExBaseList *pList, const CString &strBkmk);
	CString GetDataIdPath(CExBaseObject *pData);

	//2023-06-01 huangliang 
	virtual CString CreateNewBkmk(CRptData *pData);
	virtual void UpdateToFaceTree(){}
	virtual void UpdateToFaceGrid(){}
};

CRptItem* Rpt_GetParentRptItem(CExBaseObject *pObj);
CReportMap* Rpt_GetParentRptMap(CExBaseObject *pObj);

inline int xml_CheckBkmk(const CString &strValue)
{
	if(strValue.GetLength() < 3)
		return BMK_NULL;

	try
	{
		if(strValue.Find(_T("$")) != -1)	//以bmk$开头路径标签
		{
			return BMK_PATH;
		}

		//CString strHead = strValue.Left(3);
		//strHead.MakeLower();
		//if(strHead == _T("bmk"))	//以bmk开头标记标签
		//{
		//	return BMK_BQ;
		//}
	}
	catch (...)
	{
	}	
	return BMK_NULL;
}