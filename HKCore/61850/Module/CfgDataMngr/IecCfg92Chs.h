//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChs92.h  CIecCfgChs92

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg92Ch.h"
#include "IecCfgChsBase.h"

class CIecCfg92Chs : public CIecCfgChsBase
{
public:
	CIecCfg92Chs();
	virtual ~CIecCfg92Chs();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS92;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs92Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();

	void SetSelState_SelectAll();
	void SetSelState_UnSelectAll();
	void SetSelState_SelProtCurrAll();
	void SetSelState_SelMeasCurrAll();
	void SetSelState_SelVolAll();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//�ܺ�� 20200616  ����AT02����
#endif
};

