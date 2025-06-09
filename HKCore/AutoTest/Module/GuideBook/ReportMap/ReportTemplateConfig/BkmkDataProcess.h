//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//BkmkDataProcess.h  CBkmkDataProcess

#pragma once

#include "ReportTemplateConfigGlobal.h"

#define BKMKDATA_OPTR_NONE  0
#define BKMKDATA_OPTR_GT    1
#define BKMKDATA_OPTR_LT    2
#define BKMKDATA_OPTR_GTE   3
#define BKMKDATA_OPTR_LTE   4
#define BKMKDATA_OPTR_E     5
#define BKMKDATA_OPTR_ADD   6
#define BKMKDATA_OPTR_SUB   7
#define BKMKDATA_OPTR_DIV   8
#define BKMKDATA_OPTR_MUL   9
#define BKMKDATA_OPTR_VALREVISED   10

//2019-7-18  系统固定的处理定义
// <process name="值为空，删除整行" id="val_eq_null_del_row" optr="" value="" txt-true="" txt-false="" append-text=""/>
// <process name="值为空，删除整列" id="val_eq_null_del_col" optr="" value="" txt-true="" txt-false="" append-text=""/>

#define SYS_BKMK_DATA_PROCESS_v_null_del_row    _T("val_eq_null_del_row")
#define SYS_BKMK_DATA_PROCESS_v_null_del_col    _T("val_eq_null_del_col")

inline BOOL IsSysBkmkDataProcess(const CString &strBkmkDataProcess)
{
	if (strBkmkDataProcess == SYS_BKMK_DATA_PROCESS_v_null_del_row)
	{
		return TRUE;
	}

	if (strBkmkDataProcess == SYS_BKMK_DATA_PROCESS_v_null_del_col)
	{
		return TRUE;
	}

	return FALSE;
}

class CBkmkDataProcess : public CExBaseList
{
public:
	CBkmkDataProcess();
	virtual ~CBkmkDataProcess();

	CString  m_strOptr;
	CString  m_strValue;
	CString  m_strTextTrue;
	CString  m_strTextFalse;
	CString  m_strTextAppend;
//重载函数
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CBKMKDATAPROCESS;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CBkmkDataProcessKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

//私有成员变量
private:
	DWORD  m_dwOptr;
	double m_dValue;

//私有成员变量访问方法
public:
	BOOL ProcessData(CString &strValue, CString &strAdd, long nPrecision);

private:
	BOOL ProcessData_GT(CString &strValue);
	BOOL ProcessData_LT(CString &strValue);
	BOOL ProcessData_GTE(CString &strValue);
	BOOL ProcessData_LTE(CString &strValue);
	BOOL ProcessData_E(CString &strValue);
	BOOL ProcessData_ADD(CString &strValue);
	BOOL ProcessData_SUB(CString &strValue);
	BOOL ProcessData_DIV(CString &strValue);
	BOOL ProcessData_MUL(CString &strValue);
	BOOL ProcessData_ValRevised(CString &strValue, long nPrecision);

};

