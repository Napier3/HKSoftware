//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg6044Ch.h  CIecCfg6044Ch

#pragma once

#include "IecCfg6044CommonCh.h"


class CIecCfg6044CommonChIn : public CIecCfg6044CommonCh
{
public:
	CIecCfg6044CommonChIn();
	virtual ~CIecCfg6044CommonChIn();

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG6044COMMONCHIN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg6044CommonChInKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	long m_nAccuratyLevel;//׼ȷ��

};

