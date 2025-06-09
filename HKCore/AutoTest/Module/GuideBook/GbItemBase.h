#pragma once

#include "GuideBookDefine.h"
#include "reports.h"
#include "ScriptText.h"
#include "ReportMap/ReportMap.h"
#include "TestTypeMngr.h"
#include "../../../Module/TestMacro/TestMacros.h"
#include "ItemsRsltExprScript.h"
#include "../../../Module/TestMacro/TestMacrosFile.h"
#include "../GuideBookExportConfig.h"

//lijunqing 2022-9-24
#include "ItemRsltExprRun.h"
/*
	CGbItemBase为测试项目类的基类
	测试项目类包含 CSafety,CCommCmd,CMacroTest,CItems,CSysParaEdit
*/

#define SCRIPTID_ERROR				0
#define SCRIPTID_INITSCRIPT		1
#define SCRIPTID_RESULTSCRIPT	2
#define SCRIPTID_NAMESCRIPT		3

#define WM_GBITEM_TEST_STATE (WM_USER + 1231)

class CGbItemBase;
class CItems;

typedef CTLinkListEx<CGbItemBase> CGbItemBaseList;

class CGbItemBase : public CExBaseList
{
public:
	CGbItemBase();
	virtual ~CGbItemBase();

	static const CString g_strItemFilePathKey;
	static const CString g_strReportFilePathKey;
	static const CString g_strItemPathKey_gbrpt;
	static const CString g_strItemPathKey_ItemIndex;
	static const CString g_strItemPathKey_ItemName;
	static const CString g_strItemPathKey_ItemID;
	//static const CString g_strItemPathKey;

//属性
public:
	long m_nIndex;
	long m_nTkID;
	long m_nShow;
	long m_nEnable;
	long m_nExecType;
	long m_nBatchItem;

	long m_nSelect;
	long m_nRsltJdg;
	CString m_strRsltDsc;
	
	long m_nExpandState;		//记录GuideBookTree中节点的展开状态
	long m_nBreakLoopState;           //重复次数的循环状态

	//2019-4-27  lijunqing //多装置模式下，每台装置都单独执行
	long m_nMdvTestEach;  

protected:
	long m_nState;

public:
	CScriptText* m_pInitScriptText;
	CScriptText* m_pResultScriptText;
	CScriptText* m_pNameScriptText;
	CReports* m_pReports;
	CReportsBack* m_pReportsBack;

	CReportMap *m_pRptMap;
	CExBaseObject *m_pRptRef; //报告模板编辑的关联对象

	CExBaseList m_oSubGbItems;
	BOOL        m_bIsSubItem;     //作为子项目运行

	//lijunqing 2022-9-24
	CItemRsltExprRun *m_pRsltExprRun;

//公共接口
public:
	CReportMap* GetReportMap();
	CString GetPathName();

	void SetName(CString strName) { m_strName = strName;}
	CString GetName() { return m_strName;}
	void SetID(CString strID) { m_strID = strID;}
	CString GetID() { return m_strID;}
	void SetIndex(long nIndex) { m_nIndex = nIndex;}
	long GetIndex() { return m_nIndex;}	
	virtual void SetTkID(long nTkID); //{ m_nTkID = nTkID;}
	long GetTkID() {return m_nTkID;}	
	void SetShow(long nShow) { m_nShow = nShow;}
	long GetShow() {return m_nShow;}
	void SetEnable(long nEnable) { m_nEnable = nEnable;}
	long GetEnable() { return m_nEnable;}
	virtual void SetSelect(long nSelect); //{ m_nSelect = nSelect;}
	long GetSelect() { return m_nSelect;}
	void SetState(long nState);
	void UpdateRsltJdgByState(long nState);
	BOOL IsTestFinish();
	void SetRsltJdg(long nRsltJdg);
	void SetRsltJdg(CReport *pReport, long nRsltJdg);
	long GetRsltJdg() { return m_nRsltJdg;}
	void SetRsltDsc(CString strRsltDsc) { m_strRsltDsc = strRsltDsc;}
	CString GetRsltDsc() { return m_strRsltDsc;}
	void SetExpandState(long nExpandState)		{		m_nExpandState = nExpandState;		}
	long GetExpandState()												{		return m_nExpandState;							}
	BOOL IsMdvTestEach()			{	return m_nMdvTestEach == 1;	}

	BOOL IsEnableAndShow();
	BOOL InitStateByReport();      //根据报告数据设置state
	BOOL ValidResultScript();

	void CreateReports();
	void DeleteReport();
	BOOL HasReport();
	BOOL HasReportEx();
	CReport* AddReport(long nRepeatTimes, long nTestIndex);	
	CReport* AddReport(const CString &strName, const CString &strReportID);	

	CReport* AddReport(CShortDatas  *pDatas);	
	CReport* AddReport(CValues* pValues);
	void DeleteReport(CReport *pReport);

	BOOL SetReportValues(CValues* pValues);
	BOOL SetReportValues(CShortDatas  *pDatas);	

	//shaolei  2023-7-3 新增两个形参：
	//nCurrTestTimes：当前的测试测次；
	//nRepeatTimes：重复测试次数
	virtual BOOL RunResultScript(CString &strSyntax, BOOL bInitTrue=TRUE, long nCurrTestTimes=1,long nRepeatTimes=1);
	virtual BOOL RunRsltExpr_Only(long nCurrTestTimes, long nRepeatTimes);
	virtual BOOL RunInitScriptScript(CString &strSyntax);

	void UpdateItemsReport();
	CGbItemBase* GetFirstParentItems();
	CGbItemBase* FindItemByID(const CString &strID, UINT nClassID);

#ifdef GUIDEBOOK_DEV_MODE
	virtual void GenerateDevReports();
#endif

	virtual BOOL CopyChildren(CBaseObject* pDest)	;


	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	//virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

	CReports* GetReports();			
	CReports* GetReportsBack()	{	return m_pReportsBack;	}			
	CReport* GetCurrReport();			
	CReport* GetReport(long nIndex);	
	CReport* GetReport(const CString &strID);
	CScriptText* GetInitScriptText();				
	CScriptText* GetResultScriptText();			
	CScriptText* GetNameScriptText();
	CValue* FindRecordFile();
	CItems* GetRsltExprScriptItems();

	virtual long SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew=FALSE);
	virtual long SetItemReportValue(const CString &strValueID,const CString &strValue);
	virtual long SetItemReportValue(BSTR strValueID,BSTR strValue);
	double GetItemParaValue(const char* pszValueID);
	virtual BOOL GetItemParaValue(const CString &strValueID, double &dValue);
	double GetItemReportValue(const char* pszValueID);
	BOOL GetItemReportValue(const char* pszValueID, char *pszValue);
	BOOL GetItemReportValue(const char* pszValueID, char *pszValue, long nIndex);
	virtual BOOL GetItemReportValue(const CString & strValueID, double &dValue);
	virtual BOOL GetItemReportValue(const CString & strValueID, long &nValue);
	virtual BOOL GetItemReportValue(const CString & strValueID, CString &strValue);
	double GetItemReportExValue(long nIndex, const char* pszValueID);
	BOOL GetItemReportExValue(const char* pszDataID, const char* pszValueID, CString &strValue);
	long GetItemReportExCount();
	long CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID);
	long LGetItemReportDataCount(const CString &strDataID, long nDataValue);

	virtual void AdjustReprtDatas(){};

	//保存二进制临时文件
	BOOL SaveBinaryTempFile(const CString &strTempFilePath,const CString& strTempFileName);
	BOOL OpenBinaryTempFile();
	BOOL OpenBinaryTempFileReport(CBinarySerialBuffer &oBuffer);
	BOOL OpenBinaryTempFile(const CString& strFileName);
	BOOL OpenBinaryTempFile(const CString& strFileName, 	CBinarySerialBuffer &oBuffer);
	BOOL SaveXmlTempFile(const CString &strTempFilePath,const CString& strTempFileName);
	BOOL OpenXmlTempFile(const CString& strFileName);
	void ClearReportDatasByMap(const CString& strTempFilePath, const CString& strTempFileName, const CString &strXmlFile, BOOL bIsWriteTestTempFile);
    void GetReportDatasByMap(CExBaseList *pListDatas);

	virtual CGbItemBase* CloneForTempFile(const CString& strTempFileName);
	virtual void FreeCloneForTempFile();
	virtual CGbItemBase* CloneForTempFile();
	virtual CGbItemBase* OpenBinaryTempFileForRpt(const CString& strTempFileName);
	virtual CGbItemBase* OpenBinaryTempFileForRpt(const CString& strTempFileName, 	CBinarySerialBuffer &oBuffer);
	virtual void ClearItemInDbState();

//重写父类方法
public:
	virtual UINT GetClassID()		{		return GBCLASSID_ITEMBASE;		}
	//串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{		return NULL;	}
	virtual void InitAfterRead();

	//编辑
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL CanPaste(UINT nClassID);

	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	//项目的状态串行化，用于测试过程中临时文件的存储
	virtual long SerializeState(CBinarySerialBuffer &oBinaryBuffer);

	CExBaseList* GetSubGbItems()				{		return &m_oSubGbItems;	}
	long GetSubGbItemsCount()					{		return m_oSubGbItems.GetCount();	}

//////////////////////////////////////////////////////////////////////////
//测试项目的Path
public:
	long SelectItems(const CString &strPath, CGbItemBaseList &oListDest);
	CGbItemBase* SelectItem(const CString &strPath);

	BOOL InitSubIems();

protected:
	virtual long SelectChildrenItems(const CString &strPath, CGbItemBaseList &oListDest)		{		return 0;		};
	virtual long SelectItemsLeft_Var(const CString &strPath, const CString &strPathLeft, const CString &strPathRight, CGbItemBaseList &oListDest);
	
	long GetSubGbItemsRsltJdg();

public:
	//获取项目关联的设备的CPU
	virtual CExBaseObject* GetCpu(const CString &strCpu);
	virtual CExBaseObject* GetCpu(long nCpuIndex);
	virtual long GetCpuIndex(const CString &strCpu);

	virtual void ClearReport(BOOL bBack=TRUE);
	virtual CString GetItemStringPath();
	virtual void ReplaceSrciptText(CScriptText *pScript, UINT nScriptClassID, CGbItemBase *pSrcGbItem, BOOL bShowLog);
	virtual double CalRptValMax(const CString &strValID, double &dMax);
	virtual double CalRptValMin(const CString &strValID, double &dMax);
	virtual long CalRptValSum(const CString &strValID, double &dValue, long &nCount);

	virtual long CalTestTimeLong()	{	return 0;	}

	virtual long GetState();
	virtual long GetStateEx();
	BOOL IsSkipState();

	virtual BOOL Parse_Item_File_Path(const CString &strEpxr, CGbItemBase **ppSelectItem);

public:
	//2020-02-03  lijq update items paras
	//virtual BOOL Update(CBaseObject* pDest);
	virtual BOOL UpdateOwn(CBaseObject* pDest);
	virtual BOOL UpdateChildren(CBaseObject* pDest);
	void AfterUpdateItemIndex(long nOldIndex);

	BOOL GetTestTime(CString &strBeginTime, CString &strEndTime, BOOL bUseParent);
	CString GetActLogic_String();
	void GetItemsCount(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);

	//shaolei 20220607
	virtual void SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect);
	//shaolei 20221020
	virtual CGbItemBase* GetPrevItem(CGbItemBase *pCurrItem);
	virtual CGbItemBase* GetNextItem(CGbItemBase *pCurrItem);
	CItemRsltExprRun* GetRsltExpr();
	void GetRsltExpr(CString &strRsltExpr);
	virtual CGbItemBase* FindItemByIDHas(const CString &strID);
	virtual CGbItemBase* FindItemByIDHas(const CString &strID, UINT nClassID);
	//获取项目的测试次数。
	virtual long GetItemTestCount()	{	return 1;	}

	//shaolei 2023-8-15
	virtual void DeleteChildItem_Commcmd(BOOL bRecursion = TRUE);
	virtual BOOL IsHasChildItem(UINT nClassID);
	virtual long GetChildItem(UINT nClassID, CExBaseList *pList, BOOL bRecursion = FALSE);

	//shaolei  2024-4-18
	virtual BOOL IsAncestorOf(CGbItemBase *pItem);
protected:
	void UpdateItem(CItems *pDestItems, CGbItemBase *pNewItem);

};

BOOL Gb_Parse_Item_File_Path(const CString &strEpxr, const CString &strPathKey, CString &strPath, CString &strAppend);
BOOL Gb_ISTestingSubtem(CGbItemBase *pItem);
CGbItemBase* Gb_GetParentItem(CBaseObject *pObj);
DWORD Gb_UpdateGbItemTestStateByChildren(CExBaseList *pGbItems);
DWORD Gb_UpdateGbItemParentTestState(CExBaseList *pGbItem);
DWORD Gb_UpdateMacroTestItemTestStateByChildren(CGbItemBase *pMacroTestItem);

CTestTypes* Gb_GetTestTypes(CExBaseObject *pObject);
CString Gb_GetWaveFilePath(const CString &strFile);
CString Gb_GetItemPathName(CExBaseObject *pObject, UINT nRootClassID = GBCLASSID_GUIDEBOOK);
BOOL Gb_IsGuideBookTemplate(CExBaseObject *pObj);
BOOL Gb_IsDeviceChildNode(CExBaseObject *pObj);

CString Gb_GetItemPathID(CExBaseObject *pObject, UINT nRootClassID = GBCLASSID_GUIDEBOOK);
CExBaseObject* Gb_GetItemByPathID(const CString &strIDPath, CExBaseList *pRoot);
BOOL Gb_IsItemsTestFinished(CExBaseList *pList);

//2021-10-14  lijunqing 移到DataObj
// BOOL Gb_CalParaExpression(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CValues *pValues=NULL);
// BOOL Gb_CalParaExpressionEx(const CString &strExpress, CExBaseList *pObjDevice, double &dValue, BOOL bLogError, CString &strValue);
void Gb_SetItemsAllItemState(CExBaseList *pList, long nState);

void Gb_AddToRptValues(CDvmDataset *pDataset, CValues *pValues,  BOOL bUseReserved=FALSE);
void Gb_AddToRptValues(CDvmData *pData, CValues *pValues,  BOOL bUseReserved=FALSE);
void Gb_AddToRptValues(CDvmData *pData, CValues *pValues,  const CString &strAttrID);
void Gb_AddToRptValues(CDataSet *pDataset, CValues *pValues,  BOOL bUseReserved=FALSE);
void Gb_AddToRptValues(CDataObj *pData, CValues *pValues,  BOOL bUseReserved=FALSE);
void Gb_AddToRptValues(CDvmValue *pData, CValues *pValues,  BOOL bUseReserved=FALSE);
void Gb_AddToRptValues(CDvmValue *pData, CValues *pValues,  const CString &strAttrID);
void Gb_AddToRptValues(CDataObjValue *pData, CValues *pValues,  BOOL bUseReserved=FALSE);

//shaolei 20221012
void Gb_AddToRptDataset(CDataSet *pDataset, CDvmDataset *pRptDataset,  BOOL bUseReserved=FALSE);
void Gb_AddToRptDataset(CDataObj *pData, CDvmDataset *pRptDataset,  BOOL bUseReserved=FALSE);
void Gb_AddToRptDataset(CDataObjValue *pData, CDvmData *pRptData,  BOOL bUseReserved=FALSE);
void Gb_AddToRptDataset(CDataObjValue *pData, CDvmValue *pRptValue,  BOOL bUseReserved=FALSE);

BOOL Gb_IsDsvTextWithValue(CExBaseObject *pObj);
BOOL Gb_IsDsvTextWithUtcTime(CExBaseObject *pObj);
UINT Gb_GetImgIndex(CExBaseObject* pGbNode);
CTestMacrosFile* Gb_GetTestMacroFile(CExBaseObject *pItem);
CString Gb_GetDllCallFile(CExBaseObject *pItem);

//2019-12-31  lijunqing  多模型，指定哪个模型的数据对象
long Gb_GetDvmIndexFromPath(const CString &strDataPath);
CExBaseObject* Gb_FindVariableByID(CExBaseObject *pGbObj, const CString &strID);
long Gb_GetDvmIndexByObj(CExBaseObject *pGbObj);

CString Gb_GetItemTempFilePath(CGbItemBase* pItem);
CString ats_GetBinaryTempFilePath(CGbItemBase* pItem);

//2021-2-23  lijunqing : 
CTestControlBaseInterface*  tctrl_GetTestControl(CExBaseObject *pItem);
//shaolei 20210819 
//获取该项目下所有子项的统计结果，返回：合格|不合格
//有一个不合格即返回不合格
CString Gb_GetSummaryRslt(CGbItemBase *pItem);

//获取最近的,为功能类节点的CItems父节点  shaolei   20211110
//默认形参为非功能类节点
CItems* Gb_GetFirstParentItems(CBaseObject *pObj, BOOL bType = FALSE);
//寻找下一个功能类节点
CItems* Gb_GetNextRootTypeItems(CExBaseObject *pCurrItems);

//shaolei 获取同ID的项目的集合 20220326
void Gb_GetAllItemsByID(CGbItemBase *pItem, const CString &strID, CExBaseList &oItemList, UINT nItemClassID);
//shaolei 获得子项目的数量，包括：CItems、CSafety、CSystemParaEdit、CCommCmd、CMacroTest
long Gb_GetChildItemsCount(CGbItemBase *pItem);

//shaolei 20220620  从模板中，筛选出项目：项目的ID包含特定的字符
//返回查找到的项目数量，放到形参pDestList中；
long Gb_GetItem_IDHas(const CString &strIDHas, CGbItemBase *pParentItem, CExBaseList *pDestList);

//处理SV接收压板一致性测试
//形参1：SV压板数据集；形参2：父项目列表；形参3：过滤的项目类型
void Gb_GenSvMatchItems(CExBaseList *pDataSet, CExBaseList *pItems, UINT nClassID = GBCLASSID_MACROTEST);

void Gb_AtsInitReport_Name(CReport *pReport);
void Gb_AtsInitReport_Name(CValue *pValue, CXExprNode *pNode);  

extern long g_nSmartTestMode;

//2023-9-11  李俊庆 拷贝时，只拷贝必要信息，用于给MES或者其他外部系统，去掉script、report-map等对象
extern long g_nGbCopyItemForMes;