//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenClass.h  CItemsGenBase

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenEnable.h"
#include "ItemsGenInterface.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenCharItemLine.h"
#include "ItemGenRsltExpr.h"

/*
模板生成规则的模板类基类，为模板生成实例的模板类基类
定义数据接口、使能规则、参数映射和生成节点
*/

class CItemsGenBase : public CExBaseList
{
public:
	CItemsGenBase();
	virtual ~CItemsGenBase();


//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENBASE;   }
	virtual BSTR GetXmlElementKey()  {     ASSERT(FALSE);	 return NULL;     }
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
	CItemsGenInterface *m_pItemsGenInterface;
	CItemsGenInterface *m_pItemsGenInterface_BK;   //保留的拷贝数据，模板生成时，不随实例而初始化
	CItemsGenEnable *m_pItemsGenEnable;
	CItemsGenParasMap *m_pItemsGenParasMap;
	CItemsGenCharItemLine *m_pCharItemLine;
	CItemGenRsltExpr *m_pRsltExpr;

//私有成员变量访问方法
public:
	CItemsGenInterface* GetItemsGenInterface()	{	return m_pItemsGenInterface;	}
	void SetItemsGenInterface(CItemsGenInterface* pItemsGenInterface)	{	m_pItemsGenInterface = pItemsGenInterface;	}
	CItemsGenEnable* GetItemsGenEnable()	{	return m_pItemsGenEnable;	}
	void SetItemsGenEnable(CItemsGenEnable* pItemsGenEnable)	{	m_pItemsGenEnable = pItemsGenEnable;	}
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}
	CItemGenRsltExpr* GetItemsGenRsltExpr()	{	return m_pRsltExpr;	}
	void SetItemsGenRsltExpr(CItemGenRsltExpr* pRsltExpr)	{	m_pRsltExpr = pRsltExpr;	}

	CItemsGenInterface* GetItemsGenInterface_BK()	{	return m_pItemsGenInterface_BK;	}

//属性变量访问方法
public:
	virtual BOOL IsEnable();
	void InitParasMapByUIParas(CDataGroup *pUIParas);
};

