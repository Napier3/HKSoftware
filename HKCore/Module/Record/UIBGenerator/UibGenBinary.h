//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UibGenBinary.h  CUibGenBinary

#pragma once

#include "UIBGeneratorGlobal.h"



class CUibGenBinary : public CExBaseObject
{
public:
	CUibGenBinary();
	virtual ~CUibGenBinary();


	long  m_nValue;
	float  m_fTurnTime;
	float  m_fHoldTime;
//���غ���
public:
	virtual UINT GetClassID() {    return UIBGCLASSID_CUIBGENBINARY;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBGeneratorXmlRWKeys::CUibGenBinaryKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

