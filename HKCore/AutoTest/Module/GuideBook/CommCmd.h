#pragma once

#include "GbItemBase.h"
#include "GuideBookDefine.h"
#include "Cmd.h"
#include "Cpu.h"
#include "GbCommCmdConfig/GbCommCmd.h"
#include "../../../Module/DataMngr/DatasetValid/DsvScript.h"
#include "../XLanguageResourceAts.h"
extern long g_nOptrAddToAllCmdBeforeIs1;// = 1;
extern CExBaseList *g_pOptrAddToAllCmdRootItems;// = NULL;

//cell-mode
//col-mode
//row-mode
//ncount
//index
#define COMMCMD_DATAEX_MODE_CELL  0
#define COMMCMD_DATAEX_MODE_COL   1
#define COMMCMD_DATAEX_MODE_ROW  2
#define COMMCMD_DATAEX_MODE_COUNT  3

#define CmdExecModeForMgbrpt_ALLRPT      0
#define CmdExecModeForMgbrpt_MAINRPT   1

static const CString g_bstrCommCmdDataExModeID[] = {_T("cell-mode"),  _T("col-mode"),  _T("row-mode")};
//static const CString g_bstrCommCmdDataExModeName[] = {g_sLangTxt_CellpAdding/*_T("单元格填充")*/,  g_sLangTxt_ColumnFillMmode/*_T("列填充模式")*/, g_sLangTxt_HnagFillMmode/*_T("行填充模式")*/};
static CString g_bstrCommCmdDataExModeName[] = {_T("")/*_T("单元格填充")*/,  _T("列填充模式"),_T("行填充模式")};

inline CString Gb_GetCommCmdDataExModeName(const CString &bstrID)
{
	long nIndex = 0;
	CString strName = g_bstrCommCmdDataExModeName[COMMCMD_DATAEX_MODE_CELL];

	for (nIndex=0; nIndex<COMMCMD_DATAEX_MODE_COUNT; nIndex++)
	{
		if (bstrID == g_bstrCommCmdDataExModeID[nIndex])
		{
			strName = g_bstrCommCmdDataExModeName[nIndex];
			break;
		}
	}

	return strName;
}

class CCommCmd : public CGbItemBase
{
public:
	CCommCmd();
	virtual ~CCommCmd();
	virtual CGbItemBase* CloneForTempFile();

	static CCommCmd* _New(CBaseObject *pParent=NULL)
	{
		CCommCmd *pNew = new CCommCmd();
		pNew->SetParent(pParent);
		pNew->InitAfterRead();
		pNew->InitCmd();
		return pNew;
	}

	static const CString g_strDsvResultID_All;
	static const CString g_strDsvResultID_t;
	static const CString g_strDsvResultID_All_Trip;
	static const CString g_strDsvResultID_More;
	static const CString g_strDsvResultID_Miss;
	static const CString g_strDsvResultID_AppearForErr;
	static const CString g_strDsvResultID_Trip_desc;
	static const CString g_strDsvResultID_Std;
	static const CString g_strParas_Name_Val;

	static const CString g_strCmdID_ReadSoe;//_T("ReadSoe")
	static const CString g_strCmdID_ReadLog;//_T("ReadLog")
	static const CString g_strCmdID_StartRecord; //StartRecord
	static const CString g_strCmdID_ReadDir; //ReadDir
	static const CString g_strCmdID_ReadFile; //ReadFile
	static const CString g_strCmdID_Para_TimeStart; //tmStart
	static const CString g_strCmdID_Para_TimeEnd; //tmEnd

	static const CString g_strCmdID_LoadIecfg; //_T("LoadIecfg")
	static const CString g_strCmdID_Para_IefcgFile; 

public:
	CString m_strCommCmdID;
	CString m_strRwOptr;   //
	BOOL m_bWzdHasInitDataset;
	long m_nSortSoeByT;      //是否对SOE按照进行时间排序
	long m_nDsvRunAfterResultScript;
	long m_nCmdExecModeForMgbrpt;  //装置多通道的情况下，通讯命令执行模式

	//2022-10-3  lijunqing 针对智能测试终端软件平台，基于HTML报告模板，通信命令是否需要将关联的数据集填写到
	//报告中，采用标记进行表示，以提高程序运行的效率，否则通过接口函数查询或者每次都将数据传入报告模板进行填写
	//程序运行效率很低
	//修改后，需要修改相关的脚本函数，查找报告数据时，在m_pValues找不到，需要再从Dataset再找一遍：还没处理 2023-2-14 shaolei
	long m_nFillRptDataset;

public:
	void InitCmd();
	CCmd* GetCmd();
	CShortDatas* GetRptDataEx()		{		return m_pRptDataEx;		}
	CShortData* FindRptDataEx(const CString &bstrID);
	CShortData* FindRptDataExDataType(const CString &bstrDataTypeID);

	BOOL IsUseDeviceEx()
	{
		if (m_pCmd == NULL)
		{
			return FALSE;
		}

		return m_pCmd->m_nUseDeviceEx;
	}

	CDsvScript* GetDsvScript();
	CDsvScript* GetDsvScriptRef()	{	return m_pDsvScript;	}
	BOOL HasDsvScript();
	CItemsRsltExprScript* GetItemsRsltExprScript();

	void ReplaceDsvScript(CDsvScript *pSrcDsvScript);
	BOOL IsSortSoe()	{	return (m_nSortSoeByT == 1);	}
	BOOL IsDsvRunAfterResultScript()	{	return (m_nDsvRunAfterResultScript == 1);	}
	BOOL IsCommCmdParaDS();
	CGbCommCmdMms* GetGbCommCmd();

protected:
	CCmd*   m_pCmd;
	CTags* m_pRptTags;   //兼容老版本，不再使用
	CShortDatas* m_pRptDataEx;
	CDsvScript *m_pDsvScript;   //2015-4-7
	
	virtual BOOL GetItemParaValue(const CString &strValueID, double &dValue);
	long SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew=FALSE);
	void TransToRptDataEx();

	//重写父类方法
public:
	virtual UINT GetClassID()		{		return GBCLASSID_COMMCMD;			}
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strCommCmdKey;	}
	virtual void InitAfterRead();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL Update(CBaseObject* pDest);


	CString GetCommCmdID()				{		return m_strCommCmdID;		}
	void SetCommCmdID(const CString& strType)	{m_strCommCmdID = strType;}
	BOOL IsReadSoe();
	BOOL IsLoadIecfg();
	BOOL IsReadLog();
	BOOL IsReadLogEx();
	BOOL IsReset();
	BOOL IsLogCmd();

	BOOL IsCmdExecModeForMgbrpt_MainRpt();
	BOOL IsCmdExecModeForMgbrpt_AllRpt();

	void AddCommCmdRptTags(CValues *pValues);
	void UpdateCmdData(CCmd *pCmd, UINT nDataID, BOOL bShowLog)
	{
		if (m_strCommCmdID != ((CCommCmd*)pCmd->GetParent())->m_strCommCmdID)
		{
			return;
		}

		if (m_pCmd != NULL)
		{
			m_pCmd->UpdateCmdData(pCmd, nDataID, bShowLog);
		}
	}

#ifdef GUIDEBOOK_DEV_MODE
	virtual void GenerateDevReports();
	void GenerateRdAnalogReports(CValues *pValues);
#endif

	BOOL IsWrite();
	BOOL IsRead();
	BOOL IsCmdNeedDataset();
	BOOL IsUseConnect();
	BOOL IsFirstSubItem();
	BOOL IsBeginModeSynchro();
	BOOL IsBeginModeAsynchronous();
	void SetBeginModeSynchro();
	void SetBeginModeAsynchronous();
	BOOL IsCommCmdNeedWriteRptEx();

	CCpu* GetCurrCpu();
	CDataSet* GetDataset();
	CDataSet* GetDataset(long nCpusIndex);
	CDataSet* GetDataset(const CString &strDatasetPath, long nCpusIndex);
	long GetWriteDataObjList(CExBaseList &oList, long nCpusIndex);
	CShortDatas* GetWriteShortDatas(long nCpusIndex);
	CDvmDataset* GetWriteDvmDataset(long nCpusIndex, CString *pStringPath=NULL);
	CDvmDataset* GetNewDvmDataset(long nCpusIndex); //2021-10-14  lijunqing
	void CalWriteDvmDataset(CDataSet *pDataset, long nCpusIndex);
	//shaolei 2022-12-06
	void WriteDataToDvm(CDataSet *pDataSet, CDvmDataset *pDvmDataset, long nCpusIndex);
	void WriteDataToDvmGrp(CDataSetGroup *pDataSetGrp, CDvmDatasetGroup *pDvmDatasetGrp, long nCpusIndex);
	void WriteDataToDvmGrp(CDataSetGroup *pDataSetGrp, CDvmDatasetGroup *pDvmDatasetGrp, const CString &strDataPath, CValue *pValue, long nCpusIndex);
	void WriteDataToDvmGrp(CDataObj *pDataObj, CDvmData *pDvmData, const CString &strDataPath, CValue *pValue, long nCpusIndex);
	void WriteDataToDvmGrp(CDataObjValue *pDataObjValue, CDvmValue *pDvmValue, const CString &strDataPath, CValue *pValue, long nCpusIndex);

	//通讯命令是否关联
	BOOL IsCmdRptDataset();
	CDataObj* FindDataObj(const CString &strPath, long nCpusIndex);
	long GetCpusIndex();
	long GetCpusIndexEx();
	CString FindDataObjValue_Name(const CString &strPath, long nCpusIndex);   //shaolei  20211017

//2021-10-14  lijunqing  移植到DataObj
 	CString CalValue(CValue *pValue);
// 
// private:
// 	CString CalValue_MinMax(CExBaseObject *pDevice, CValue *pValue, double dValue);
	
public:
	virtual BOOL RunResultScript();
	virtual BOOL RunResultScript(CString &strSyntax, BOOL bInitTrue=TRUE);
	virtual BOOL RunDsvScript();  //20170523
	virtual BOOL RunDsvScript(CDvmDataset **ppRptDvmDataset);
	virtual BOOL RunDsvScript(CDvmDataset **ppRptDvmDataset, CReport *pReport, BOOL bSetRsltJdg);

	void CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2);
	void CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2);
	void SetSoeTripDesc(const char *pszRptID, const char *pszSoeID);
	long GetRepeatTimes(CString *pstrMode);

	long CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr);
	long CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr);

	void ClearCommCmdParas();
	void AddCommCmdParaValue(const CString &strValID, const CString &strValue);
private:
	void InitParas_NameAndVal(CValues *pValues);
	void InitDsvRpt_All(CValues *pValues);
	void InitDsvRpt_All_Trip(CValues *pValues);
	void InitDsvRpt_All_More(CValues *pValues);
	void InitDsvRpt_All_Miss(CValues *pValues);
	void InitDsvRpt_All_AppearForErr(CValues *pValues);
	void InitDsvRpt_Std(CValues *pValues);
	CDvmValue* FindDvmValue(CExBaseList *pList, const CString &strID);
	CDvmValue* FindDvmValue(CExBaseList *pList, const CString &strID, const CString &strValue);
	CDvmData* FindDvmData(CExBaseList *pList, const CString &strID, const CString &strValue);
	CDvmData* FindDvmDataByName(CExBaseList *pList, const CString &strName, const CString &strValue);

	CDvmValue* FindRptValue(const CString &strID, const CString &strValue=_T(""));

public:
	virtual long CalTestTimeLong();
	virtual void ClearItemInDbState();
	virtual long GetItemTestCount();
};