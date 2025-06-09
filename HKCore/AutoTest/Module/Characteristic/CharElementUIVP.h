//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementUIVP.h  CCharElementUIVP

#pragma once

#include "CharElementInverse.h"



class CCharElementUIVP : public CCharElementInverse
{
public:
	CCharElementUIVP();
	virtual ~CCharElementUIVP();


	CString  m_strA;
	CString  m_strB;
	CString  m_strC;
	CString  m_strD;
	CString  m_strE;
	CString  m_strP;
	CString  m_strK;
	CString  m_strVp;
	
	double  m_fA;
	double  m_fB;
	double  m_fC;
	double  m_fD;
	double  m_fE;
	double  m_fP;
	double  m_fK;
	double  m_fVp;

	bool	m_bUType;//false-��ѹ(X�᷶Χ(0,Vp)) ture-��ѹ(X�᷶Χ(Vp,�����))
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTUIVP;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementUIVPKey();     }
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

