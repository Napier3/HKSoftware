//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg91StateWordBit.h  CIecCfg91StateWordBit

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfg91StateWordBit : public CExBaseObject
{
public:
	CIecCfg91StateWordBit();
	virtual ~CIecCfg91StateWordBit();


	CString  m_strDataType;
	CString  m_strValue;
	long  m_nIndex;

	CString m_strText;
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91STATEWORDBIT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91StateWordBitKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

