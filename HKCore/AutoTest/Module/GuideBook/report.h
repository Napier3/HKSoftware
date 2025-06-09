#pragma once

#include "GuideBookDefine.h"
#include "DataSet.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../Module/DataMngr/Tags.h"
#include "../GuideBookExportConfig.h"
#include "../../../Module/DataMngr/DvmValues.h"

#define RPTEX_QUERY_FLAG_VAL   0X0000F0F0

class CReport : public CExBaseObject
{
public:
	CReport();
	virtual ~CReport();

	static const CString g_pszCalReportKey;
	//属性
public:
	CValues *m_pValues;
	CString m_strBeginTime;
	CString m_strEndTime;

	//CTagsMngr *m_pRptDataEx;
	CDvmDatasetGroup *m_pRptDvmDataset; 
	CDvmLogs *m_pLogs;

	//公共接口
public:
	CString GetTestTime(long nMode);
	void SetBeginTime();
	void SetEndTime();
	void SetBeginTime(const CString &strBeginTime)							{		m_strBeginTime = strBeginTime;		}
	CString GetBeginTime()																{		return m_strBeginTime;		}
	void SetEndTime(const CString &strEndTime)								{		m_strEndTime = strEndTime;		}
	CString GetEndTime()																	{		return m_strEndTime;		}
	CValues* GetValues()										{		return m_pValues;			}
	BOOL SetReportValues(CValues* pValues);
	BOOL UpdateReportValues(CValues* pValues);
	BOOL SetReportValues(CDataSet* pDataset);
	BOOL SetReportValues(CExBaseList* pListDataObj);
	void UpdateReportValues(CReport *pSrcReport);

	BOOL SetReportValues(CShortDatas *pDatas);
	BOOL AppendReportValues(CExBaseList *pListDataObj);
	BOOL AddReportValues(CValues* pValues);
	void AddReportValues(CTags *pTags);
	BOOL AddReportEx(CShortDatas  *pDatas);
	BOOL AddReportEx(CShortData  *pData);
	BOOL AddReport(CShortDatas  *pDatas);
	BOOL AddReport(CShortData  *pData);
	BOOL AddReportDataset(CDvmDataset  *pDataset);
	BOOL AppendRptValues(CExBaseList *pListValue);
	//报告中，增加几个固定的结果值，用于绑定误差判断的计算值
	BOOL AddRptValues_ErrorCal();  

	CValue* FindReportData(const CString &strID);
	CValue* FindReportData(BSTR strID);
	BOOL FindReportData(const CString &strID, long &nValue);
	void SetResultJudge(long nResult);
	long GetResultJudge();
	BOOL IsCalReport();
	BOOL IsCalReportEx();
	void SetCalReport();
	void DeleteRptValues();  //删除所有的报告数据：m_pValues

	CValue* AddValue(BSTR bstrID);
	CValue* AddValue(const CString &strID, const CString &strValue);
	CValue* AddValue(BSTR bstrID, BSTR bstrName);
	CValue* AddValue(const CString &strID, const CString &strName, const CString &strValue);

	BOOL SetValue(const CString &strValueID,const CString &strValue);
	BOOL GetReportValue(const CString &strValueID, double &dValue);
	BOOL GetReportValue(const CString &strValueID, long &nValue);
	BOOL GetReportValue(const CString &strValueID, char *pszValue);
	BOOL GetReportValue(const CString &strValueID, CString &strValue);

	//根据数据ID，查找报告数据  shaolei 20220527   
	BOOL GetReportValueEx(const CString &strDataID, CString &strValue);

	CDvmValue* FindRptValueByID(const CString &strDataID, const CString &strAttrID);  
	CDvmValue* FindRptValueExByValueID(const CString &strValueID);   //根据ValueID，遍历扩展报告数据下所有扩展属性
	CDvmData* FindRptExDataByDataID(const CString &strDataID);   //根据ValueID，遍历扩展报告数据下所有数据

	void ClearReportDatas();
	void ClearReportDatasByMap();
	void ClearReportDatasByMap(CExBaseList *pReportMap, BOOL bClearValues, UINT nClearSoe);
	void ClearReportDatasByDsValid(CExBaseList *pReportMap); 
    void GetReportDatasByMap(CExBaseList *pReportMap, CExBaseList *pListDest);
    long GetTestIndex();
	//重写父类方法
public:
	virtual UINT GetClassID()		{		return GBCLASSID_REPORT;		}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);


	BOOL GetReportExValue(long nIndex, const CString &strValueID, CString &strValue);
	BOOL GetReportExValue(const CString &strDataID, const CString &strValueID, CString &strValue);
	CString GetLastRcdFile();
	void InitAfterSerializeOwn();

private:
	void AddResultJudgeKey(long nResult);

public:
	virtual void CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);
	virtual void ClearItemInDbState();

	void AddRptDvmDataset(CDvmDataset *pDvmDataset);
	void AddRptDvmDataset(CDvmDataset &oDvmDataset);
	void AddRptDvmDataset(CExBaseList &oDataList);

	//shaolei 2023-10-09
	void InitValues(CDvmValues *pSrc);
	void InitRptDvmDataset(CDvmDataset *pSrc);
};
