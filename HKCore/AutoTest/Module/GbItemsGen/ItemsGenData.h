//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenData.h  CItemsGenData

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenInterface.h"
class CItemsGenInterface;

class CItemsGenData : public CExBaseObject
{
public:
	CItemsGenData();
	virtual ~CItemsGenData();


	CString  m_strDataType;
	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL IsEnable(CItemsGenInterface *pInterface);
};

