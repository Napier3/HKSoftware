//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SysRptData.h  CSysRptData

#pragma once

#include "ReportTemplateConfigGlobal.h"



class CSysRptData : public CExBaseObject
{
public:
	CSysRptData();
	virtual ~CSysRptData();


//重载函数
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CSYSRPTDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CSysRptDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

