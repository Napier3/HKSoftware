//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementLined.h  CCharElementLined

#pragma once

#include "CharElementLineBase.h"



class CCharElementLined : public CCharElementLineBase
{
public:
	CCharElementLined();
	virtual ~CCharElementLined();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strXe;
	CString  m_strYe;

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINED;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinedKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);

	virtual void GetBeginPoint(CString &strX, CString &strY);
	virtual void GetEndPoint(CString &strX, CString &strY);
	virtual void SetBeginPoint(const CString &strX, const CString &strY);
	virtual void SetEndPoint(const CString &strX, const CString &strY);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);

public:
	virtual void SetDoublePoint();
};

