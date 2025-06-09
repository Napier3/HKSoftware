//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenEnable.h  CItemsGenEnable

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenData.h"
#include "ItemsGenInterface.h"

class CItemsGenEnable : public CExBaseList
{
public:
	CItemsGenEnable();
	virtual ~CItemsGenEnable();


	CString  m_strMode;  //使能模式：与=and；或=or；非=not
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENENABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenEnableKey();     }
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
	BOOL IsEnableMode_And()	{	return m_strMode == GB_ITEMS_GEN_ENABLE_AND;	}
	BOOL IsEnableMode_Or()	{	return m_strMode == GB_ITEMS_GEN_ENABLE_OR;		}
	BOOL IsEnableMode_Not()	{	return m_strMode == GB_ITEMS_GEN_ENABLE_NOT;	}
	//判断使能时，Interface中传递的参数的值，已经从界面获取
	BOOL IsEnable(CItemsGenInterface *pInterface);
	BOOL IsEnable_And(CItemsGenInterface *pInterface);
	BOOL IsEnable_Or(CItemsGenInterface *pInterface);
	BOOL IsEnable_Not(CItemsGenInterface *pInterface);


};

