//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MmsEngineDsCfg.h  CMmsEngineDsCfg

#pragma once

#include "MmsEngineConfigGlobal.h"



class CMmsEngineDsCfg : public CExBaseObject
{
public:
	CMmsEngineDsCfg();
	virtual ~CMmsEngineDsCfg();


	CString  m_strKey;
	long  m_nRead;
//���غ���
public:
	virtual UINT GetClassID() {    return MSCFGCLASSID_CMMSENGINEDSCFG;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsEngineConfigXmlRWKeys::CMmsEngineDsCfgKey();     }
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

