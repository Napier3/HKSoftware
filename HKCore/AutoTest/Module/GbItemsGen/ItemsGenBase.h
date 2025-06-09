//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenClass.h  CItemsGenBase

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenEnable.h"
#include "ItemsGenInterface.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenCharItemLine.h"
#include "ItemGenRsltExpr.h"

/*
ģ�����ɹ����ģ������࣬Ϊģ������ʵ����ģ�������
�������ݽӿڡ�ʹ�ܹ��򡢲���ӳ������ɽڵ�
*/

class CItemsGenBase : public CExBaseList
{
public:
	CItemsGenBase();
	virtual ~CItemsGenBase();


//���غ���
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

//˽�г�Ա����
private:
	CItemsGenInterface *m_pItemsGenInterface;
	CItemsGenInterface *m_pItemsGenInterface_BK;   //�����Ŀ������ݣ�ģ������ʱ������ʵ������ʼ��
	CItemsGenEnable *m_pItemsGenEnable;
	CItemsGenParasMap *m_pItemsGenParasMap;
	CItemsGenCharItemLine *m_pCharItemLine;
	CItemGenRsltExpr *m_pRsltExpr;

//˽�г�Ա�������ʷ���
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

//���Ա������ʷ���
public:
	virtual BOOL IsEnable();
	void InitParasMapByUIParas(CDataGroup *pUIParas);
};

