//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SysRptDataMngr.h  CSysRptDataMngr

#pragma once

#include "ReportTemplateConfigGlobal.h"


#include "SysRptData.h"

class CSysRptDataMngr : public CExBaseList
{
public:
	CSysRptDataMngr();
	virtual ~CSysRptDataMngr();


//重载函数
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CSYSRPTDATAMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CSysRptDataMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
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