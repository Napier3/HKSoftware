//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementIUF.h  CCharElementIUF

#pragma once
#include "CharElementInverse.h"


class CCharElementIUF : public CCharElementInverse
{
public:
	CCharElementIUF();
	virtual ~CCharElementIUF();


	CString  m_strD;
	CString  m_strP;
	CString  m_strPickup;
	CString  m_strK;//Vnom/Fs���ѹ�ͶƵ�ʵı�ֵ
	
	double  m_fD;
	double  m_fP;
	double  m_fPickup;//��Ӧ�������Pickup
	double  m_fK;//Vnom/Fs���ѹ�ͶƵ�ʵı�ֵ

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTIUF;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementIUFKey();     }
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
protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual double CalInverse(double dVal);
};

