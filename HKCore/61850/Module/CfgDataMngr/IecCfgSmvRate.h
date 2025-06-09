//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgSmvRate.h  CIecCfgSmvRate

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfgSmvRate : public CExBaseObject
{
public:
	CIecCfgSmvRate();
	virtual ~CIecCfgSmvRate();


	float  m_fRate;

	//2023/10/12 wjs ��������
	long m_nCodeValue;//��ֵ
	long m_nMeasCurrCodeValue;//����������ֵ
	float m_fPrimValue;//һ�ζֵ
	CString m_strAliasName;//�������ͣ������� 

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGSMVRATE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgSmvRateKey();     }
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
	BOOL IsVolChsGroup();
	BOOL IsDcFT3VolChsGroup();
	BOOL IsDcFT3CurChsGroup();
	BOOL IsAcFT3VolChsGroup();
	BOOL IsAcFT3CurChsGroup();

	//2023/10-20 wjs
	void InitDefaultAliasName();
};

CString st_GetSmvRateID(const CString& strAppCh,BOOL bDCFT3 = FALSE);

