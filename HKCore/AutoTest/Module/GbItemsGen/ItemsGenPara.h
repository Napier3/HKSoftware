//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenPara.h  CItemsGenPara

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


/*
��Ŀ���ɽڵ����ж����Լ����������Ĳ�����һ��CItemsGenPara��Ӧһ������
*/
class CItemsGenPara : public CExBaseObject
{
public:
	CItemsGenPara();
	virtual ~CItemsGenPara();


	CString  m_strDataType;
	CString  m_strValue;
	CString  m_strFormat;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenParaKey();     }
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
};

