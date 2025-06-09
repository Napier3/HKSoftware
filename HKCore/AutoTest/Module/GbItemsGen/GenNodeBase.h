//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenNode.h  CGenNodeBase

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenEnable.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenNameAdd.h"
#include "ItemsGenCommCmd.h"
#include "ItemsGenSysParaEdit.h"
#include "ItemsGenSafety.h"

/*
模板生成节点类的基类；可嵌套
定义了使能条件、数据映射、项目名称规则
*/
class CGenNodeBase : public CExBaseList
{
public:
	CGenNodeBase();
	virtual ~CGenNodeBase();


	CString  m_strType;
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CGENNODEBASE;   }
	virtual BSTR GetXmlElementKey()  {	ASSERT(FALSE);     return NULL;     }
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
	CItemsGenEnable *m_pItemsGenEnable;
	CItemsGenParasMap *m_pItemsGenParaMap;
	CItemsGenNameAdd *m_pItemsGenNameAdd;

	CItemsGenParasMap *m_pItemsGenParaMap_BK;   //一个node，可能为多个inst（实例）服务。为每一个inst服务时，参数映射应当都恢复成原始状态

	CItemsGenCommCmd *m_pItemsGenCommCmd;
	CItemsGenSafety *m_pItemsGenSafety;
	CItemsGenSysParaEdit *m_pItemsGenSysParaEdit;

//私有成员变量访问方法
public:
	CItemsGenEnable* GetItemsGenEnable()	{	return m_pItemsGenEnable;	}
	void SetItemsGenEnable(CItemsGenEnable* pItemsGenEnable)	{	m_pItemsGenEnable = pItemsGenEnable;	}
	CItemsGenParasMap* GetItemsGenParaMap()	{	return m_pItemsGenParaMap;	}
	void SetItemsGenParaMap(CItemsGenParasMap* pItemsGenParaMap)	{	m_pItemsGenParaMap = pItemsGenParaMap;	}
	CItemsGenNameAdd* GetItemsGenNameAdd()	{	return m_pItemsGenNameAdd;	}
	void SetItemsGenNameAdd(CItemsGenNameAdd* pItemsGenNameAdd)	{	m_pItemsGenNameAdd = pItemsGenNameAdd;	}

	CItemsGenParasMap* GetItemsGenParaMap_BK()	{	return m_pItemsGenParaMap_BK;	}

	CItemsGenCommCmd* GetItemsGenCommCmd()	{	return m_pItemsGenCommCmd;	}
	void SetItemsGenEnable(CItemsGenCommCmd* pItemsGenCommCmd)	{	m_pItemsGenCommCmd = pItemsGenCommCmd;	}
	CItemsGenSafety* GetItemsGenSafety()	{	return m_pItemsGenSafety;	}
	void SetItemsGenSafety(CItemsGenSafety* pItemsGenSafety)	{	m_pItemsGenSafety = pItemsGenSafety;	}
	CItemsGenSysParaEdit* GetItemsGenSysParaEdit()	{	return m_pItemsGenSysParaEdit;	}
	void SetItemsGenNameAdd(CItemsGenSysParaEdit* pItemsGenSysParaEdit)	{	m_pItemsGenSysParaEdit = pItemsGenSysParaEdit;	}

	void LogParasMapError();

//属性变量访问方法
public:
	virtual CString GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CString GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual BOOL IsEnable(CItemsGenInterface *pInterface);
	virtual CItemsGenInterface* GetGenInterface();
	virtual CItemsGenInterface* GetGenInterface_BK();
	virtual void InitParasMapByUIParas(CDataGroup *pUIParas);
	virtual void InitParasMapByInterface(CItemsGenInterface *pInterface);
	virtual void GetAllParasMap(CExBaseList &listParasMap);
	//根据Interface，处理需要保留表达式的参数数据
	virtual void InitParasMapByInterface_Ex(CItemsGenInterface *pInterface);
	virtual void ResetParasMap();
};

