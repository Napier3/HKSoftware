//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdParaCondition.h  CSttGdParaCondition

#pragma once

#include "SttTestGridDefineGlobal.h"



class CSttGdParaCondition : public CExBaseObject
{
public:
	CSttGdParaCondition();
	virtual ~CSttGdParaCondition();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDPARACONDITION;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdParaConditionKey();     }
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

