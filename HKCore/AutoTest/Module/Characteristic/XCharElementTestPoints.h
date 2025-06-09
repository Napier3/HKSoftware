//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XCharElementTestPoints.h  CXCharElementTestPoints

#pragma once

#include "CharacteristicGlobal.h"

class CXCharElementTestPoints : public CExBaseObject
{
public:
	CXCharElementTestPoints();
	virtual ~CXCharElementTestPoints();

	CString  m_strFrom;
	CString  m_strTo;
	CString  m_strStep;

	double m_dFrom;
	double m_dTo;
	double m_dStep;
	
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTTESTPOINTS;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementTestPointsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

};

