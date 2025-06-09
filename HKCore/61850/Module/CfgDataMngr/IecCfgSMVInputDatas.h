//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgDatasSMV.h  CIecCfgDatasSMV

#pragma once

// #include "IecCfgDataMngrGlobal.h"

#include "IecCfgDatasBase.h"
#include "IecCfg91Data.h"
#include "IecCfg92Data.h"
#include "IecCfg6044Data.h"
#include "IecCfgSmvRates.h"

#include "IecCfgSMVDatas.h"


class CIecCfgDatasSMVInput : public CIecCfgDatasBase
{
public:
	CIecCfgDatasSMVInput();
	virtual ~CIecCfgDatasSMVInput();


	CString  m_strSmvType;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASSMVINPUT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasSMVInputKey();     }


	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	virtual CIecCfgDataBase* CreateIecCfgData();
	virtual UINT GetIecCfgDataClassID();

	virtual BOOL IsCfgData(UINT nClassID)	{	return IsSmvData(nClassID);	}
	
	long GetSmvType()		{	return iecfg_GetSmvTypeByString(m_strSmvType);	}
	BOOL SetSmvType(long nSmvType);
	BOOL IsSmvType91()		{	return (SMVTYPE_91 == GetSmvType());	}
	BOOL IsSmvType92()		{	return (SMVTYPE_92 == GetSmvType());	}
	BOOL IsSmvType6044()		{	return (SMVTYPE_6044 == GetSmvType());	}

	BOOL IsSmvData(UINT nClassID);
	BOOL IsSmvData(CExBaseObject *pObj);
	virtual long GetMaxCfgDataCount()	{	return 8;	}

//˽�г�Ա����
private:
	CIecCfgSmvRates *m_pIecCfgSmvRates;
	CIecCfgDataSmvCommon m_oIecCfgDataSmvCommon;
	void FreeCfgDatas();

//˽�г�Ա�������ʷ���
public:
	void InitCfgDatasByCommon();
	void InitCommonFromCfgDatas();
	CIecCfgDataSmvCommon* GetCommonData()	{	return &m_oIecCfgDataSmvCommon;	}

	virtual BOOL ValidateFiberIndex(CIecCfgDataBase *pData);
	virtual BOOL ValidateFiberIndex();
	CIecCfgSmvRates* GetIecCfgSmvRates();
};

