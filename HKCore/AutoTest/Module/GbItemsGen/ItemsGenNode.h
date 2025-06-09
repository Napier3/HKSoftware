//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenNode.h  CItemsGenNode

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "GenNodeBase.h"
#include "ItemGenRsltExpr.h"

class CItemsGenNode : public CGenNodeBase
{
public:
	CItemsGenNode();
	virtual ~CItemsGenNode();

//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENNODE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenNodeKey();     }
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

//˽�г�Ա����
private:
	CItemGenRsltExpr *m_pRsltExpr;

//˽�г�Ա�������ʷ���
public:
	CItemGenRsltExpr* GetRsltExpr();

//���Ա������ʷ���
public:
	BOOL IsNodeType_Items()		{	return m_strType == GB_ITEMS_GEN_NODETYPE_ITEMS;	}
	BOOL IsNodeType_CommCmd()	{	return m_strType == GB_ITEMS_GEN_NODETYPE_COMMCMD;	}
	BOOL IsNodeType_MacroTest()	{	return m_strType == GB_ITEMS_GEN_NODETYPE_MACROTEST;	}
	BOOL IsNodeType_None()		{	return m_strType == GB_ITEMS_GEN_NODETYPE_NONE;	}
	BOOL IsNodeType_Safety()	{	return m_strType == GB_ITEMS_GEN_NODETYPE_SAFETY;	}
	BOOL IsNodeType_SysParaEdit()	{	return m_strType == GB_ITEMS_GEN_NODETYPE_SYSPARAEDIT;	}
	virtual CString GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CString GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	CString GetNameAdd_Name_Own(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	CString GetNameAdd_ID_Own(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CItemsGenInterface* GetGenInterface();
	virtual CItemsGenInterface* GetGenInterface_BK();
};
