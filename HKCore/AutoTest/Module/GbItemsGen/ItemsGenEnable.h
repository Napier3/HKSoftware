//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenEnable.h  CItemsGenEnable

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenData.h"
#include "ItemsGenInterface.h"

class CItemsGenEnable : public CExBaseList
{
public:
	CItemsGenEnable();
	virtual ~CItemsGenEnable();


	CString  m_strMode;  //ʹ��ģʽ����=and����=or����=not
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENENABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenEnableKey();     }
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

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL IsEnableMode_And()	{	return m_strMode == GB_ITEMS_GEN_ENABLE_AND;	}
	BOOL IsEnableMode_Or()	{	return m_strMode == GB_ITEMS_GEN_ENABLE_OR;		}
	BOOL IsEnableMode_Not()	{	return m_strMode == GB_ITEMS_GEN_ENABLE_NOT;	}
	//�ж�ʹ��ʱ��Interface�д��ݵĲ�����ֵ���Ѿ��ӽ����ȡ
	BOOL IsEnable(CItemsGenInterface *pInterface);
	BOOL IsEnable_And(CItemsGenInterface *pInterface);
	BOOL IsEnable_Or(CItemsGenInterface *pInterface);
	BOOL IsEnable_Not(CItemsGenInterface *pInterface);


};

