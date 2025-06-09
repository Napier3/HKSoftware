//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenInst.h  CItemsGenInst

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenNameAdd.h"
#include "ItemsGenInterface.h"

/*
项目生成实例类
每个项目生成实例，都定义了参数映射表（该参数映射表定义的参数映射，应当不超出项目生成模板中定义的数据接口定义的所有数据）、项目名称定义
每个项目生成实例，都应该遍历项目生成模板中定义的项目生成节点，完成项目生成

通过paras-map，从界面参数中获取参数实际值，并将实际值赋值给模板类定义的interface
*/
class CItemsGenInst : public CExBaseList
{
public:
	CItemsGenInst();
	virtual ~CItemsGenInst();


	long  m_nNewItems;
	CString  m_strClass;
	CString  m_strCharacteristic;    //对于边界测试，该属性记录为特性曲线的ID
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENINST;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenInstKey();     }
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
	CItemsGenNameAdd *m_pItemsGenNameAdd;
	CItemsGenParasMap *m_pItemsGenParasMap;

//私有成员变量访问方法
public:
	CItemsGenNameAdd* GetItemsGenNameAdd()	{	return m_pItemsGenNameAdd;	}
	void SetItemsGenNameAdd(CItemsGenNameAdd* pItemsGenNameAdd)	{	m_pItemsGenNameAdd = pItemsGenNameAdd;	}
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}

//属性变量访问方法
public:
	BOOL IsClassMode_Class()	{	return m_strClass == GB_ITEMS_GEN_INST_CLASS_CLASS;		}
	BOOL IsClassMode_Define()	{	return m_strClass == GB_ITEMS_GEN_INST_CLASS_DEFINE;	}
	BOOL IsEnable(CDataGroup *pDataGroup);
	void InitInterfaceByUIParas(CDataGroup *pUIParas);
	CItemsGenInterface* GetInterface();
	CString GetNameAdd_Name(CDataGroup *pDataGroup);
	CString GetNameAdd_ID(CDataGroup *pDataGroup);
};

