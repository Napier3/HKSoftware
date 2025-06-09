//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgReportsMngr.h  CTtmgReportsMngr

#pragma once

#include "TestTasksMngrGenerateGlobal.h"


#include "TtmgReports.h"

class CTtmgReportsMngr : public CExBaseList
{
public:
	CTtmgReportsMngr();
	virtual ~CTtmgReportsMngr();

	CTtmgReports *m_pReportsError;
	CTtmgReports *m_pReportsSucc;
	
	CTtmgReports *m_pReportsDestructive;
	CTtmgReports *m_pReportsNonDestructive;
	CTtmgReports *m_pReportsSummary;

	CTtmgReport  *m_pReportSumAllSuc;
	CTtmgReport  *m_pReportSumError;
	CTtmgReport  *m_pReportSumSucc;
//重载函数
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGREPORTSMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgReportsMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

