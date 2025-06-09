//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SysRptDataMngr.h  CSysRptDataMngr

#pragma once

#include "ReportTemplateConfigGlobal.h"


#include "SysRptData.h"

class CSysRptDataMngr : public CExBaseList
{
public:
	CSysRptDataMngr();
	virtual ~CSysRptDataMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CSYSRPTDATAMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CSysRptDataMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

class CMgrpCmbnDataMngr : public CSysRptDataMngr
{
public:
	CMgrpCmbnDataMngr(){};
	virtual ~CMgrpCmbnDataMngr(){};

public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CMGRPCMBNDATAMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CMgrpCmbnDataMngrKey();     }

};