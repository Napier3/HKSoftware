//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//BkmkDataProcessMngr.h  CBkmkDataProcessMngr

#pragma once

#include "ReportTemplateConfigGlobal.h"


#include "BkmkDataProcess.h"

class CBkmkDataProcessMngr : public CExBaseList
{
public:
	CBkmkDataProcessMngr();
	virtual ~CBkmkDataProcessMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CBKMKDATAPROCESSMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CBkmkDataProcessMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL ProcessData(const CString &strID, CString &strValue, CString &strAdd, long nPrecision);

private:

};

