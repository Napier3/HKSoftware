//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharTestLineDefine.h  CCharTestLineDefine

#pragma once

#include "CharacteristicGlobal.h"



class CCharTestLineDefine : public CExBaseObject
{
public:
	CCharTestLineDefine();
	virtual ~CCharTestLineDefine();


	CString  m_strExprAngle;
	CString  m_strExprX;
	CString  m_strExprY;
	CString  m_strExprR;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARTESTLINEDEFINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharTestLineDefineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

