//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg92ChsIn.h  CIecCfg92ChsIn

#pragma once

#include "IecCfg92Chs.h"
#include "IecCfg92ChIn.h"

class CIecCfg92ChsIn : public CIecCfg92Chs
{
public:
	CIecCfg92ChsIn();
	virtual ~CIecCfg92ChsIn();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS92IN;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs92InKey();     }
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
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
#endif
};

