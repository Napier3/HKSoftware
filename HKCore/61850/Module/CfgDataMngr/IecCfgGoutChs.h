//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChsGout.h  CIecCfgChsGout

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgGoutCh.h"
#include "IecCfgChsBase.h"

class CIecCfgGoutChs : public CIecCfgChsBase
{
public:
	CIecCfgGoutChs();
	virtual ~CIecCfgGoutChs();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSGOUT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsGoutKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pGoutList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
#endif
};

