//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChs91.h  CIecCfgChs91

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg91Ch.h"
#include "IecCfgChsBase.h"

class CIecCfg91Chs : public CIecCfgChsBase
{
public:
	CIecCfg91Chs();
	virtual ~CIecCfg91Chs();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS91;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs91Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();
	virtual void InitAfterRead();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

