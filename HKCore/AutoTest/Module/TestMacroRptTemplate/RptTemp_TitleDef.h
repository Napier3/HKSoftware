//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TitleDef.h  CRptTemp_TitleDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"
class CRptTemp_Items;

class CRptTemp_TitleDef : public CExBaseObject
{
public:
	CRptTemp_TitleDef();
	virtual ~CRptTemp_TitleDef();


	long  m_nLevel;     //相对于最近的items节点的标题等级
	CString  m_strText;
	CString  m_strItem_Id;
	long  m_nItem_Level;
	long  m_nItem_Level_2;
	long  m_nItem_Level_3;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TITLEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TitleDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	long GetTitleLevel();
	CRptTemp_Items* GetFirstItems_UseRptTitle();
};

