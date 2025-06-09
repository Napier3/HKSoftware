//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MacroSelfDefGen.h  CMacroSelfDefGen

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"

#include "ItemGenRsltExpr.h"
#include "ItemsGenParasMap.h"

//�̶�����һ��CItems�����ڴ�ſͻ���Ҫ���Զ�����ӵĲ��Ե�
//���磺���뱣����ֵУ�飬���ӡ�������ԡ�
class CMacroSelfDefGen : public CExBaseList
{
public:
	CMacroSelfDefGen();
	virtual ~CMacroSelfDefGen();

	CString  m_strMacroID;
	long  m_nNewItems;
//���غ���
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

//˽�г�Ա����
private:
	CItemsGenParasMap *m_pItemsGenParasMap;
	CItemGenRsltExpr *m_pItemGenRsltExpr;

//˽�г�Ա�������ʷ���
public:
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}
	CItemGenRsltExpr* GetItemGenRsltExpr()	{	return m_pItemGenRsltExpr;	}
	void SetItemGenRsltExpr(CItemGenRsltExpr* pItemGenRsltExpr)	{	m_pItemGenRsltExpr = pItemGenRsltExpr;	}

//���Ա������ʷ���
public:
	void InitParasMapByUIParas(CDataGroup *pUIParas);
};

