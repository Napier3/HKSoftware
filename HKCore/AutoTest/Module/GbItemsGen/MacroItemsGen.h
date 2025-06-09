//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroItemsGen.h  CMacroItemsGen

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


#include "ItemsGenClass.h"
#include "ItemsGenInst.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenDefine.h"

class CMacroItemsGen : public CExBaseList
{
public:
	CMacroItemsGen();
	virtual ~CMacroItemsGen();

	CString  m_strMacroID;
	long  m_nNewItems;
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CMACROITEMSGEN;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CMacroItemsGenKey();     }
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
	CItemsGenParasMap *m_pItemsGenParasMap;
	CItemsGenClass *m_pItemsGenClass;
	CItemsGenDefine *m_pItemsGenDefine;

//私有成员变量访问方法
public:
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}
	CItemsGenClass* GetItemsGenClass()	{	return m_pItemsGenClass;	}
	void SetItemsGenClass(CItemsGenClass* pItemsGenClass)	{	m_pItemsGenClass = pItemsGenClass;	}
	CItemsGenDefine* GetItemsGenDefine()	{	return m_pItemsGenDefine;	}
	void SetItemsGenDefine(CItemsGenDefine* pItemsGenDefine)	{	m_pItemsGenDefine = pItemsGenDefine;	}

//属性变量访问方法
public:
	void InitParasMapByUIParas(CDataGroup *pUIParas);
};

