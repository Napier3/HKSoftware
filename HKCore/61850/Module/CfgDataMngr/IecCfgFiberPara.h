//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgFiberPara.h  CIecCfgFiberPara

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfgFiberPara : public CExBaseObject
{
public:
	CIecCfgFiberPara();
	virtual ~CIecCfgFiberPara();


	long  m_ntype;//LC ��� 0��Ӧ���׿�,1��Ӧǧ�׿�;   ST���  0��ӦB��   1��ӦFT3  2��ӦPPS
//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGFIBERPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgFiberParaKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

