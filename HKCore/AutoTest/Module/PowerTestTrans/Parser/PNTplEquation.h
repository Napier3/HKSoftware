//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PNTplEquation.h  CPNTplEquation

#pragma once

#include "PNTplMngrGlobal.h"



class CPNTplEquation : public CExBaseObject
{
public:
	CPNTplEquation();
	virtual ~CPNTplEquation();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPNTPLEQUATION;   }
	virtual BSTR GetXmlElementKey()  {      return CPNTplMngrXmlRWKeys::CPNTplEquationKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
	double m_fValueCal;
	BOOL m_bHasCal;

//˽�г�Ա�������ʷ���
public:
	double GetValue();
	BOOL HasCal()	{	return m_bHasCal;	}
	void SetValueCal(double dCal);
};

