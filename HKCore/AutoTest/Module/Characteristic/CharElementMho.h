//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementMho.h  CCharElementMho

#pragma once

#include "CharElement.h"



class CCharElementMho : public CCharElement, public CXDrawData_Circle
{
public:
	CCharElementMho();
	virtual ~CCharElementMho();


	CString  m_strForwardReach;
	CString  m_strAngle;
	CString  m_strOffset;

	double  m_fForwardReach;
	double  m_fAngle;
	double  m_fOffset;

// 	double  m_fXCenter;
// 	double  m_fYCenter;
// 	double  m_fXRadius;
// 	double  m_fYRadius;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTMHO;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementMhoKey();     }
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
	virtual void CalTestLines(UINT nTestLineMode);
	virtual CXDrawBase* CreateDrawElement();
};

