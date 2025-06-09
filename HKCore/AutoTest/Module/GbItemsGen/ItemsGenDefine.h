//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenDefine.h  CItemsGenDefine

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenNode.h"
#include "ItemsGenBase.h"
#include "ItemsGenInst.h"

/*
模板生成规则的模板类，为模板生成实例的模板
定义数据接口、使能规则、参数映射和生成节点
该类定义的生成节点的类型为：CIemsGenNode，模板生成规则的结构与模板结构一致
*/
class CItemsGenDefine : public CItemsGenBase
{
public:
	CItemsGenDefine();
	virtual ~CItemsGenDefine();


//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDefineKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CItemsGenInst* m_pCurrInst;  //当前正在执行生成的Inst实例

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	virtual CItemsGenInst* GetCurrentInst();
	void SetCurrentInst(CItemsGenInst* pInst);
};

