//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChsGin.h  CIecCfgChsGin

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgGinCh.h"
#include "IecCfgChsBase.h"

class CIecCfgGinChs : public CIecCfgChsBase
{
public:
	CIecCfgGinChs();
	virtual ~CIecCfgGinChs();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSGIN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsGinKey();     }
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
#ifdef _USE_IN_AT02D_MODE_
//˽�г�Ա�������ʷ���
public:
	virtual void SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
#endif
};

