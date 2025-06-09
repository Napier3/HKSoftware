//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportTemplateDef.h  CRptTemp_ReportTemplateDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_TitleDef.h"
#include "RptTemp_TextDef.h"
#include "RptTemp_GridDef.h"

class CRptTemp_ReportTemplateDef : public CExBaseList
{
public:
	CRptTemp_ReportTemplateDef();
	virtual ~CRptTemp_ReportTemplateDef();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ReportTemplateDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CString GetDataMode();
};

