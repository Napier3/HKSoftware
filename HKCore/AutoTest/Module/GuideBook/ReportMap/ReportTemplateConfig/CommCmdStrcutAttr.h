//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CommCmdStrcutAttr.h  CCommCmdStrcutAttr

#pragma once

#include "ReportTemplateConfigGlobal.h"



class CCommCmdStrcutAttr : public CExBaseObject
{
public:
	CCommCmdStrcutAttr();
	virtual ~CCommCmdStrcutAttr();


//重载函数
public:
	virtual UINT GetClassID() {    return RPTCFGCLASSID_CCOMMCMDSTRCUTATTR;   }
	virtual BSTR GetXmlElementKey()  {      return CReportTemplateConfigXmlRWKeys::CCommCmdStrcutAttrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

