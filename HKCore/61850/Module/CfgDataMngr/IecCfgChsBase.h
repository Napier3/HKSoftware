//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChsBase.h  CIecCfgChsBase

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgDataChBase.h"

class CIecCfgChsBase : public CExBaseList
{
public:
	CIecCfgChsBase();
	virtual ~CIecCfgChsBase();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual CIecCfgDataChBase* CreateChannel() = 0;

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void RemoveTailCh(long nCountRemove, CExBaseList &oListRemove);
	virtual BOOL SetChannelNum(long nChannelNum);
	virtual long GetChannels(CExBaseList &oListCh);
	virtual long GetUsedChsCount();
	virtual void InitChs();
};

