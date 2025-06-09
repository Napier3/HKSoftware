//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementLiner.h  CCharElementLiner

#pragma once

#include "CharElementLineBase.h"



class CCharElementLiner : public CCharElementLineBase
{
public:
	CCharElementLiner();
	virtual ~CCharElementLiner();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strAngle;
	CString  m_strLengthUse;

	double  m_fLengthUse;

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINER;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinerKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);
	
	virtual void GetBeginPoint(CString &strX, CString &strY);
	virtual void SetBeginPoint(const CString &strX, const CString &strY);
	virtual void BeforeCalTestLines();//2023.6.2 zhouhj   ���Ӹ���m_fLengthUse  m_strLengthUse ��ֵ

//˽�г�Ա����
private:
	void UpdateLengthUse();

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines_Plumb();
	virtual void CalTestLines_Vert();
	virtual void CalTestLines_Horz();

	void GetXeYe(double &dXe, double &dYe);
};

