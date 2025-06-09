#pragma once

#include "GuideBookDefine.h"
#include "report.h"

class CReports : public CExBaseList
{
public:
	CReports();
	virtual ~CReports();

//公共接口
public:
	CReport* AddReport(const CString &strName, const CString &strReportID);
	BOOL SetReportValues(CValues* pValues);
	BOOL SetReportValues(CShortDatas  *pDatas);
	void SetResultJudge(long nResult);
	void GetReportsForCal(CExBaseList &oReports);
	void GetReportsForCalEx(CExBaseList &oReports);

	BOOL HasReportEx();

//重写父类方法
public:
	virtual UINT GetClassID();

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual BSTR GetXmlElementKey();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL IsSame(CBaseObject* pObj);
	virtual void ClearItemInDbState();

	//2021-8-10 lijunqing
	void InitReports(CReports *pSrcReports);
};

class CReportsBack : public CReports
{
public:
	CReportsBack()	{};
	virtual ~CReportsBack(){};

	//重写父类方法
public:
	virtual UINT GetClassID()	{	return GBCLASSID_REPORTSBACK;	}
	virtual CBaseObject* Clone()
	{
		CReportsBack* pReports = new CReportsBack();

		Copy(pReports);

		return pReports;
	}
};

