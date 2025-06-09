//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasSMV.cpp  CIecCfgDatasSMV


#include "stdafx.h"
#include "IecCfgSMVInputDatas.h"

#include "IecCfg92InputData.h"


// static const CString g_strSmvType91		= _T("9-1");
// static const CString g_strSmvType92		= _T("9-2");
// static const CString g_strSmvType6044	= _T("6044-8");

CIecCfgDatasSMVInput::CIecCfgDatasSMVInput()
{
	//初始化属性
 	m_strSmvType = g_strSmvType92;
// 	m_strSmvType = g_strSmvType6044;
//	m_strSmvType = g_strSmvType91;

	m_pIecCfgSmvRates = NULL;

	//初始化成员变量
	m_oIecCfgDataSmvCommon.SetParent(this);
}

CIecCfgDatasSMVInput::~CIecCfgDatasSMVInput()
{
}

long CIecCfgDatasSMVInput::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSmvTypeKey, oNode, m_strSmvType);
	return 0;
}
long CIecCfgDatasSMVInput::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CIecCfgDatasBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSmvTypeKey, oElement, m_strSmvType);
	return 0;
}

BOOL CIecCfgDatasSMVInput::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDatasBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDatasSMVInput *p = (CIecCfgDatasSMVInput*)pObj;

	if(m_strSmvType != p->m_strSmvType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDatasSMVInput::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasBase::CopyOwn(pDest);

	CIecCfgDatasSMVInput *p = (CIecCfgDatasSMVInput*)pDest;

	p->m_strSmvType = m_strSmvType;
	return TRUE;
}

CBaseObject* CIecCfgDatasSMVInput::Clone()
{
	CIecCfgDatasSMVInput *p = new CIecCfgDatasSMVInput();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgDatasSMVInput::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	if (strClassID == pXmlKeys->m_strCIecCfg92ChInKey)
	{
		pNew = new CIecCfg92InputData();//CIecCfg92InputData
	}

	return pNew;
}


CIecCfgDataBase* CIecCfgDatasSMVInput::CreateIecCfgData()// CIecCfgDataSmvChBase
{
	long nSmvType = iecfg_GetSmvTypeByString(m_strSmvType);

	CIecCfgDataBase *pNew = NULL;//CIecCfgDataSmvChBase

	switch (nSmvType)
	{
	case SMVTYPE_92:
		pNew = new CIecCfg92InputData();//CIecCfg92InputData
		break;
	default:
		pNew = new CIecCfg92InputData();//
		break;
	}
	return pNew;
}


void CIecCfgDatasSMVInput::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGSMVRATES)
		{
			m_pIecCfgSmvRates = (CIecCfgSmvRates *)p;
			break;
		}
	}

	if (m_pIecCfgSmvRates == NULL)
	{
		m_pIecCfgSmvRates = GetIecCfgSmvRates();
//		m_pIecCfgSmvRates->OpenCfgDefaultConfigFile();
	}
}

UINT CIecCfgDatasSMVInput::GetIecCfgDataClassID()
{
	long nSmvType = iecfg_GetSmvTypeByString(m_strSmvType);

	switch (nSmvType)
	{
	case SMVTYPE_91:
		return CFGCLASSID_CIECCFG91DATA;
		break;

	case SMVTYPE_92:
		return CFGCLASSID_CIECCFG92INPUTDATA;
		break;

	case SMVTYPE_6044:
		return CFGCLASSID_CIECCFG6044DATA;
		break;

	default:
		return CFGCLASSID_CIECCFG92INPUTDATA;
		break;
	}

	return CFGCLASSID_CIECCFG92INPUTDATA;
}


BOOL CIecCfgDatasSMVInput::IsSmvData(UINT nClassID)
{
	return ((nClassID == CFGCLASSID_CIECCFG91DATA)
		|| (nClassID == CFGCLASSID_CIECCFG92INPUTDATA)
		|| (nClassID == CFGCLASSID_CIECCFG6044DATA) );
}


BOOL CIecCfgDatasSMVInput::IsSmvData(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();

	return IsSmvData(nClassID);
}

void CIecCfgDatasSMVInput::FreeCfgDatas()
{
	POS pos = GetHeadPosition();
	POS posPrev = NULL;
	CIecCfgDatasBase *p = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CIecCfgDatasBase *)GetNext(pos);

		if (IsSmvData(p))
		{
			RemoveAt(posPrev);
			delete p;
		}
	}
}

BOOL CIecCfgDatasSMVInput::SetSmvType(long nSmvType)
{
	long nOldSmvType = GetSmvType();

	if (nSmvType == nOldSmvType)
	{
		return FALSE;
	}

	long nCount = GetCfgDataCount();
	m_strSmvType = iecfg_GetSmvTypeByID(nSmvType);
	FreeCfgDatas();

	SetCount(nCount);
	InitCommonFromCfgDatas();
	return TRUE;
}

void CIecCfgDatasSMVInput::InitCfgDatasByCommon()
{
	POS pos = GetHeadPosition();
	CIecCfgSmvDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgSmvDataBase *)GetNext(pos);

		if (IsSmvData(p))
		{
			p->InitByCommData(&m_oIecCfgDataSmvCommon);
		}
	}
}

void CIecCfgDatasSMVInput::InitCommonFromCfgDatas()
{
	POS pos = GetHeadPosition();
	CIecCfgSmvDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgSmvDataBase *)GetNext(pos);

		if (IsSmvData(p))
		{
			p->GetCommData(&m_oIecCfgDataSmvCommon);
			break;
		}
	}
}


BOOL CIecCfgDatasSMVInput::ValidateFiberIndex(CIecCfgDataBase *pData)
{
	CExBaseList oListUseDatas;
	GetUseDatas(oListUseDatas);
	POS pos = NULL;
	CIecCfgDataBase *pCurr = NULL;
	BOOL bTrue = TRUE;

	pos = oListUseDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pCurr = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);

		if (pCurr != pData)
		{
			if (pCurr->m_nFiberIndex == pData->m_nFiberIndex)
			{
				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("【%s】与【%s】输出光口冲突"), pData->GetCfgDataShortName(), pCurr->GetCfgDataShortName());
				bTrue = FALSE;
				break;
			}
		}
	}

	oListUseDatas.RemoveAll();

	//只进行提示，不返回错误
	return TRUE;
}


BOOL CIecCfgDatasSMVInput::ValidateFiberIndex()
{
	CExBaseList oListUseDatas;
	GetUseDatas(oListUseDatas);
	POS pos = NULL;
	CIecCfgDataBase *pData = NULL;
	BOOL bTrue = TRUE;
	pos = oListUseDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);

		if (!ValidateFiberIndex(pData))
		{
			bTrue = FALSE;
			break;
		}
	}

	oListUseDatas.RemoveAll();

	return bTrue;
}

CIecCfgSmvRates* CIecCfgDatasSMVInput::GetIecCfgSmvRates()
{
	if (m_pIecCfgSmvRates == NULL)
	{
		m_pIecCfgSmvRates = new CIecCfgSmvRates();
		AddNewChild(m_pIecCfgSmvRates);
	}

	return m_pIecCfgSmvRates;
}

