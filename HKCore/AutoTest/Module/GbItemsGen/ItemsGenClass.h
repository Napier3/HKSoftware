//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenClass.h  CItemsGenClass

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ParasGenNode.h"
#include "ItemsGenBase.h"

/*
模板生成规则的模板类，为模板生成实例的模板
定义数据接口、使能规则、参数映射和生成节点
该类定义的生成节点的类型为：CParasGenNode，模板生成规则的结构与模板结构不一致
*/

class CItemsGenClass : public CItemsGenBase
{
public:
	CItemsGenClass();
	virtual ~CItemsGenClass();


//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENCLASS;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenClassKey();     }
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
};

