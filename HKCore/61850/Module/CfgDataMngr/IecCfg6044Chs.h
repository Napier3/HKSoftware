//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChs6044.h  CIecCfgChs6044

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg6044Ch.h"
#include "IecCfg6044CommonCh.h"
#include "IecCfgChsBase.h"

class CIecCfg6044Chs : public CIecCfgChsBase
{
public:
	CIecCfg6044Chs();
	virtual ~CIecCfg6044Chs();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHS6044;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChs6044Key();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();
	virtual void InitAfterRead();

	CString CreateVolCurrChID_AT02D(CExBaseList *pHasModifiedChListRef,const CString &strPrefix,const CString &strSuffix,
		const CString &strChID,long nChProtMeasType = 0);//���һ��������ʶͨ���ı���/�������  0-������,1-����,2����

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex);//�ܺ�� 2024.3.2  ����AT02����
#endif
};

