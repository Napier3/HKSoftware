//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroSelfDefGen.h  CMacroSelfDefGen

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"

#include "ItemGenRsltExpr.h"
#include "ItemsGenParasMap.h"

//固定生成一个CItems，用于存放客户需要的自定义添加的测试点
//例如：距离保护定值校验，增加“定点测试”
class CMacroSelfDefGen : public CExBaseList
{
public:
	CMacroSelfDefGen();
	virtual ~CMacroSelfDefGen();

	CString  m_strMacroID;
	long  m_nNewItems;
//重载函数
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CMacroSelfDefGenKey();     }
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
	CItemGenRsltExpr *m_pItemGenRsltExpr;

//私有成员变量访问方法
public:
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}
	CItemGenRsltExpr* GetItemGenRsltExpr()	{	return m_pItemGenRsltExpr;	}
	void SetItemGenRsltExpr(CItemGenRsltExpr* pItemGenRsltExpr)	{	m_pItemGenRsltExpr = pItemGenRsltExpr;	}

//属性变量访问方法
public:
	void InitParasMapByUIParas(CDataGroup *pUIParas);
};

