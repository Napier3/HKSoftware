//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

#include "IecCfg92Ch.h"

class CIecCfg92ChIn : public CIecCfg92Ch
{
public:
	CIecCfg92ChIn();
	virtual ~CIecCfg92ChIn();

	CString m_strCfg92DoDesc;
	CString m_strCfg92dUVal;
	long m_nFiberIndex;
	long m_nFiber2Index;
	long m_nAccuratyLevel;//׼ȷ��
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92CHIN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg92ChInKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitCh();

public:
	void InitAccLevelByName();
};

