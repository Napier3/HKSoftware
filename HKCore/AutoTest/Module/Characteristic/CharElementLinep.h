//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementLinep.h  CCharElementLinep

#pragma once

#include "CharElementLineBase.h"

class CCharElementLinep : public CCharElementLineBase
{
public:
	CCharElementLinep();
	virtual ~CCharElementLinep();


	CString  m_strZ;
	CString  m_strPh;
	CString  m_strAngle;
	
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINEP;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinepKey();     }
    virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
    virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);

};

