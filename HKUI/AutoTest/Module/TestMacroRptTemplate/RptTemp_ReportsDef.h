//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportsDef.h  CRptTemp_ReportsDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_RpeortDef.h"
#include "RptTemp_ValueDef.h"

class CRptTemp_ReportsDef : public CExBaseList
{
public:
	CRptTemp_ReportsDef();
	virtual ~CRptTemp_ReportsDef();

	//其它项目的相对路径，设置为一个“相对路径”，仅在一个模块生成一个固化报告时实现。
	//对于遥测试验，报告数据就是在电气量的子项目：通讯命令中
	CString  m_strData_Path;  
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_REPORTSDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ReportsDefKey();     }
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
	CRptTemp_ReportDef *m_pRpeortDef;

//私有成员变量访问方法
public:
	CRptTemp_ReportDef* GetRpeortDef()	{	return m_pRpeortDef;	}

//属性变量访问方法
public:
};

