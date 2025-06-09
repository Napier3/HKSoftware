//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UibGenHarm.h  CUibGenHarm

#pragma once

#include "UIBGeneratorGlobal.h"



class CUibGenHarm : public CExBaseObject
{
public:
	CUibGenHarm();
	virtual ~CUibGenHarm();

	float  m_fValCoef;

	long  m_nUse;
	long  m_nIndex;
	float  m_fValue;
	float  m_fAngle;
//���غ���
public:
	virtual UINT GetClassID() {    return UIBGCLASSID_CUIBGENHARM;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBGeneratorXmlRWKeys::CUibGenHarmKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void Generate(long &nUibGenIndex, double &dCoef_FreqAngleT, double &dGenValue);

};

