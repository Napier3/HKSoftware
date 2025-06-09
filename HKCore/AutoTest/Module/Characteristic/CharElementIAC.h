//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementIAC.h  CCharElementIAC

#pragma once

#include "CharElementInverse.h"



class CCharElementIAC : public CCharElementInverse
{
public:
	CCharElementIAC();
	virtual ~CCharElementIAC();

	//double GBS_IAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta)

	CString  m_strTp;
	CString  m_strA;
	CString  m_strB;
	CString  m_strC;
	CString  m_strD;
	CString  m_strE;
	CString  m_strBeta;

	double  m_fTp;
	double  m_fA;
	double  m_fB;
	double  m_fC;
	double  m_fD;
	double  m_fE;
	double  m_fBeta;

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTIAC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementIACKey();     }
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

//˽�г�Ա����
protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines(UINT nTestLineMode);

	virtual double CalInverse(double dVal);
};

