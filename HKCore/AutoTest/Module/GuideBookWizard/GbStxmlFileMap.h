#pragma once

#include "GbtBatchItem.h"

//////////////////////////////////////////////////////////////////////////
//映射组别功能
#define GBTSCRIPTMAP_FILTER_AND   0
#define GBTSCRIPTMAP_FILTER_OR    1
#define GBTSCRIPTMAP_FILTER_MAXCOUNT    10

#define GBTSCRIPTMAP_FILTER_MODE_HAVE    1
#define GBTSCRIPTMAP_FILTER_MODE_NOTHAVE 0

class CGbtDataScriptMapFilter
{
public:
	CGbtDataScriptMapFilter();
	virtual ~CGbtDataScriptMapFilter();

	DWORD m_dwFilterOptr;
	CString m_astrKey[GBTSCRIPTMAP_FILTER_MAXCOUNT];
	long    m_nKeyCount;
	DWORD   m_dwFilterMode;

public:
	BOOL Filter(const CString &strName);
	BOOL ParseScript(const CString &strScript);

private:
	BOOL Filter_And(const CString &strName);
	BOOL Filter_Or(const CString &strName);
};

class CGbtDataScriptMap : public CExBaseList
{
public:
	CGbtDataScriptMap();
	virtual ~CGbtDataScriptMap();

	virtual CBaseObject* Clone();
	virtual BOOL Copy(CBaseObject* pDest);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATASCRIPTMAP;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtDataScriptMapKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)	{	return 0;	}
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)	{	return 0;	}

	void InitByCopy(CGbtDataScriptMap *pSrc);

public:
	CGbtDataScript *m_pGbtDataScript;
	CString m_strDataValue;
	CString m_strRefObjName;
	CString m_strRefObjPath;

private:
	CExBaseObject *m_pRefObject;  //关联的数据对象

public:
	void SetRefObject(CExBaseObject *pRefObject, BOOL bRemoveAll=TRUE);
	CExBaseObject* GetRefObject()	{	return m_pRefObject;	}
	void InitGbtDataScript(CGbtDataScript *pGbtDataScript);
	void XMatch(CXMatchList &oXMatchList, BOOL bNotUpdateSingle,BOOL bNotUpdateNone);
	void XMatch(CXMatchList &oXMatchList, const CStringArray &strKey, BOOL bNotUpdateSingle,BOOL bNotUpdateNone);
	BOOL InitRefObject();
	CString GetRefObjIDPath();
	CString GetGbtDataScriptValue();

	BOOL HasAllKey(const CStringArray &astrKey, const CString &strName);
	BOOL HasKey(const CStringArray &astrKey, const CString &strName);
	void FilterByScript(CGbtDataScriptMapFilter &oFilter);

private:
	void Short();
	void AddRefObject(CExBaseObject *pRefObj);
};

class CGbtDataInterfaceMap : public CExBaseList
{
public:
	CGbtDataInterfaceMap();
	virtual ~CGbtDataInterfaceMap();

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATAINTERFACEMAP;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtDataInterfaceMapKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CGbtDataInterfaceMap *pSrc);

	void FilterByScript(CGbtDataScriptMapFilter &oFilter);

public:
	CGbtDataInterface *m_pGbtDataInterface;

public:
	void InitGbtDataInterface(CGbtDataInterface *pGbtDataInterface);
	void XMatch(CXMatchList &oXMatchList, BOOL bNotUpdateSingle,BOOL bNotUpdateNone);
	void XMatch(CXMatchList &oXMatchList, const CStringArray &strKey, BOOL bNotUpdateSingle,BOOL bNotUpdateNone);
	BOOL CanInsert();
	BOOL ValidateMapKeys(CString &strErrorMsg);
};

void wzd_InsertIecConfigMacroTest(const CString &strIecFile, CExBaseList *pParent);

CItems* GbtWzd_InsertRootItems(CExBaseList *pParentItems, const CString &strName, const CString &strID);

//数据集映射的一个组别，对应一个Items
class CGbInsertStxmlFile : public CExBaseList
{
public:
	CGbInsertStxmlFile();
	virtual ~CGbInsertStxmlFile();

	CString m_strKey;
	CStringArray m_astrKey;

//	CWordRptEdit *m_pWordRptEditSrc;
//	CWordRptEdit *m_pWordRptEditDest;
	CRptEditInterface *m_pRptEditSrc;
	CRptEditInterface *m_pRptEditDest;

	CString m_strStxmlFile;
	long m_bInsertFileRoot;
	long m_nAddRptGroupTitle;

	CString m_strIec61850ConfigFile;
	CGbtDataInterfaces *m_pGbtDataInterfaces;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTINSERTSTXMLFILE;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertStxmlFileKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//void InitByCopy(CGbInsertStxmlFile *pSrc, CDevice *pDevice, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void InitByCopy(CGbInsertStxmlFile *pSrc);

public:
//	void InitGbFileInsert(const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void InitGbFileInsert(const CString &strStxmlFile, CRptEditInterface *pDestRptEdit, CRptEditInterface *pSrcRptEdit);
//	void InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CRptEditInterface *pDestRptEdit, CRptEditInterface *pSrcRptEdit);

	void UpdateGbtDataInterfaceMaps();
	CExBaseObject* ExecInsert(CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	CExBaseObject* ExecInsertByBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	CExBaseObject* ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchItemGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	CItems* ExcuteInsertFile(CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	void XMatch(CXMatchList &oXMatchList, BOOL bNotUpdateSingle,BOOL bNotUpdateNone);

	void UpdateByBatchGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems);
	void UpdateByBatchGroup_GbtDatas(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems);
	void UpdateByBatchGroup_MacroTest(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems);
	BOOL ValidateMapKeys(CString &strErrorMsg);
	void SetKey(const CString &strKey);
	long GetProgressStepCount()		{		return GetCount() * 2;		}

	void InsertIecConfigMacroTest(CExBaseList *pParent)
	{
		wzd_InsertIecConfigMacroTest(m_strIec61850ConfigFile, pParent);
	}

	CDataObj *FindMapDataObj(const CString &strGbtDataID);

	//////////////////////////////////////////////////////////////////////////
	//过滤
	BOOL FilterByScript(CGbtDataScriptMapFilter &oFilter);

private:
	CItems* InsertByDataterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	void InitCommCmdItemDatasetPath(CDevice *pDevice, CExBaseList *pItems);
	void InitCommCmdItemDatasetPath(CDevice *pDevice, CCommCmd *pCommCmd);
	BOOL MakeCommCmdValusValidate(CCommCmd *pCommCmd);

	void InsertStxmlWord(CItems *pCurrItems, long nTitleLevel);
	void RenameRptBkmks(CExBaseList *pList);
	//void RenameRptBkmk(CExBaseObject *pBkmk);

	void UpdateByBatchItemRef(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems);
	void UpdateByBatchItemRef_MacroTest(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems);
	CExBaseObject* SelectByRefItem(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems);
	void UpdateItem_CommCmd(CExBaseObject *pItem, CGbtBatchItemRef *pBatchItemRef);
	void UpdateItem_MacroTest(CExBaseObject *pItem, CGbtBatchItemRef *pBatchItemRef);
	void ReplaceBatchItemGroup(CGbtBatchItemGroup *pBatchItemGroup, CGbtDataInterfaceMap *pGbtDataInterfaceMap);

	//////////////////////////////////////////////////////////////////////////
	//数据集列表
protected:
	CExBaseList m_listDataset;
	void InitDatasetList(CDevice *pDevice, CGbtDataInterfaceMap *pMap);

public:
	void InitDatasetList(CDevice *pDevice);
};



//CGbInsertStxmlFile管理对象，如果
class CGbInsertStxmlFileMngr : public CExBaseList
{
public:
	CGbInsertStxmlFileMngr();
	virtual ~CGbInsertStxmlFileMngr();
	long m_nAddRptGroupTitle;

	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTINSERTSTXMLFILEMNGR;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertStxmlFileMngrKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	CGbInsertStxmlFile *m_pHeadStxmlFile;

	CGbInsertStxmlFile* NewGbInsertStxmlFile();

public:
//	void InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CRptEditInterface *pDestRptEdit, CRptEditInterface *pSrcRptEdit);
	void XMatch(CXMatchList &oXMatchList, long nIndex, BOOL bNotUpdateSingle,BOOL bNotUpdateNone);
	CExBaseObject* ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);

	//void UpdateByBatchGroup(CGbtBatchItemGroup *pBatchGroup, CThreadProgressInterface *pThreadProgress);
	BOOL ValidateMapKeys(CString &strErrorMsg);
	long GetProgressStepCount();

	void InitByCopy(CGbInsertStxmlFileMngr *pSrc);
	CDataObj *FindMapDataObj(const CString &strGbtDataID);
	void InitDatasetList(CDevice *pDevice);

	void DeleteStxmlFile(long nIndex);

protected:
	void Validate();
};

class CGbWzdDatasetRef : public CExBaseObject
{
public:
	CGbWzdDatasetRef()	{	m_pDataSetRef = NULL;	}
	virtual ~CGbWzdDatasetRef()	{};

	CDataSet *m_pDataSetRef;

	void SetDataSet(CDataSet *pDataSet)
	{
		m_pDataSetRef = pDataSet;
		m_strName = pDataSet->m_strName;
		m_strID = pDataSet->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}

public:
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATASETREF;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbWzdDatasetRefKey();     }

};

class CGbWzdDatasetRefMngr : public CExBaseList
{
public:
	CGbWzdDatasetRefMngr(){};
	virtual ~CGbWzdDatasetRefMngr(){};

public:
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATASETREFMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbWzdDatasetRefsKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};
