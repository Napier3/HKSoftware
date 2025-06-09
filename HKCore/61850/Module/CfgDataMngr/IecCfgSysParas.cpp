//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSysParas.cpp  CIecCfgSysParas


#include "stdafx.h"
#include "IecCfgSysParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecCfgSysParas::CIecCfgSysParas()
{
	//初始化属性
	m_nPkgSendType = _IECCFG_SYSPARAS_PKG_SEND_TYPE_EndKeepSend_;
// 	m_nSecSyn = _IECCFG_SYSPARAS_SEC_SYN_DisEnable_;
// 	m_nBCodeLogic = _IECCFG_SYSPARAS_B_CODE_LOGIC_Positive_;
// 	m_nIec1588Type = _IECCFG_SYSPARAS_IEC1588_TYPE_PeerDelay_;
	m_nPrimParas = 0;
	m_nPrimOutput = 1;

	//初始化成员变量
	m_pPrimRates = NULL;
	m_pPrimRatesIn = NULL;
	m_pFiberParas = NULL;
	m_pFiberParasIn= NULL;
}

CIecCfgSysParas::~CIecCfgSysParas()
{
}

long CIecCfgSysParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPkg_Send_TypeKey, oNode, m_nPkgSendType);
// 	xml_GetAttibuteValue(pXmlKeys->m_strSec_SynKey, oNode, m_nSecSyn);
// 	xml_GetAttibuteValue(pXmlKeys->m_strBcode_LogicKey, oNode, m_nBCodeLogic);
// 	xml_GetAttibuteValue(pXmlKeys->m_strIec1588_TypeKey, oNode, m_nIec1588Type);
	xml_GetAttibuteValue(pXmlKeys->m_strPrim_ParasKey, oNode, m_nPrimParas);
	xml_GetAttibuteValue(pXmlKeys->m_strPrim_OutputKey, oNode, m_nPrimOutput);
	return 0;
}

long CIecCfgSysParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPkg_Send_TypeKey, oElement, m_nPkgSendType);
// 	xml_SetAttributeValue(pXmlKeys->m_strSec_SynKey, oElement, m_nSecSyn);
// 	xml_SetAttributeValue(pXmlKeys->m_strBcode_LogicKey, oElement, m_nBCodeLogic);
// 	xml_SetAttributeValue(pXmlKeys->m_strIec1588_TypeKey, oElement, m_nIec1588Type);
	xml_SetAttributeValue(pXmlKeys->m_strPrim_ParasKey, oElement, m_nPrimParas);
	xml_SetAttributeValue(pXmlKeys->m_strPrim_OutputKey, oElement, m_nPrimOutput);
	return 0;
}

long CIecCfgSysParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nPkgSendType);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nSecSyn);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nBCodeLogic);
// 		BinarySerializeCalLen(oBinaryBuffer, m_nIec1588Type);
		BinarySerializeCalLen(oBinaryBuffer, m_nPrimParas);
		BinarySerializeCalLen(oBinaryBuffer, m_nPrimOutput);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nPkgSendType);
// 		BinarySerializeRead(oBinaryBuffer, m_nSecSyn);
// 		BinarySerializeRead(oBinaryBuffer, m_nBCodeLogic);
// 		BinarySerializeRead(oBinaryBuffer, m_nIec1588Type);
		BinarySerializeRead(oBinaryBuffer, m_nPrimParas);
		BinarySerializeRead(oBinaryBuffer, m_nPrimOutput);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nPkgSendType);
// 		BinarySerializeWrite(oBinaryBuffer, m_nSecSyn);
// 		BinarySerializeWrite(oBinaryBuffer, m_nBCodeLogic);
// 		BinarySerializeWrite(oBinaryBuffer, m_nIec1588Type);
		BinarySerializeWrite(oBinaryBuffer, m_nPrimParas);
		BinarySerializeWrite(oBinaryBuffer, m_nPrimOutput);
	}
	return 0;
}

void CIecCfgSysParas::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CFGCLASSID_CIECCFGPRIMRATES)
		{
			m_pPrimRates = (CIecCfgPrimRates*)p;
		}
		if (nClassID == CFGCLASSID_CIECCFGPRIMRATESIN)
		{
			m_pPrimRatesIn = (CIecCfgPrimRatesIn*)p;
		}		
		else if (nClassID == CFGCLASSID_CIECCFGFIBERPARAS)
		{
			m_pFiberParas = (CIecCfgFiberParas*)p;
			m_pFiberParas->InitCommon(IECCFG_MAX_LC_FIBER_NUM,IECCFG_MAX_ST_FIBER_NUM);
		}
		else if (nClassID == CFGCLASSID_CIECCFGFIBERPARAIN)
		{
			m_pFiberParasIn = (CIecCfgFiberParasIn*)p;
			//m_pFiberParasIn->InitCommon(IECCFG_MAX_LC_FIBER_NUM,IECCFG_MAX_ST_FIBER_NUM);
		}
	}
}

BOOL CIecCfgSysParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgSysParas *p = (CIecCfgSysParas*)pObj;

	if(m_nPkgSendType != p->m_nPkgSendType)
	{
		return FALSE;
	}

// 	if(m_nSecSyn != p->m_nSecSyn)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_nBCodeLogic != p->m_nBCodeLogic)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_nIec1588Type != p->m_nIec1588Type)
// 	{
// 		return FALSE;
// 	}

	if(m_nPrimParas != p->m_nPrimParas)
	{
		return FALSE;
	}

	if(m_nPrimOutput != p->m_nPrimOutput)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgSysParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgSysParas *p = (CIecCfgSysParas*)pDest;

	p->m_nPkgSendType = m_nPkgSendType;
// 	p->m_nSecSyn = m_nSecSyn;
// 	p->m_nBCodeLogic = m_nBCodeLogic;
// 	p->m_nIec1588Type = m_nIec1588Type;
	p->m_nPrimParas = m_nPrimParas;
	p->m_nPrimOutput = m_nPrimOutput;
	return TRUE;
}

CBaseObject* CIecCfgSysParas::Clone()
{
	CIecCfgSysParas *p = new CIecCfgSysParas();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgSysParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecCfgSysParas *p = new CIecCfgSysParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecCfgSysParas::CanPaste(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGPRIMRATES)
	{
		return TRUE;
	}

	if (nClassID == CFGCLASSID_CIECCFGFIBERPARAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgSysParas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgPrimRatesKey)
	{
		if (m_pPrimRates == NULL)
		{
			m_pPrimRates = new CIecCfgPrimRates();
		}
		
		return m_pPrimRates;
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgPrimRatesInKey)
	{
		if (m_pPrimRatesIn == NULL)
		{
			m_pPrimRatesIn = new CIecCfgPrimRatesIn();
		}

		return m_pPrimRatesIn;
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgFiberParasKey)
	{
		if (m_pFiberParas == NULL)
		{
			m_pFiberParas = new CIecCfgFiberParas();
		}

		return m_pFiberParas;
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgFiberParasInKey)
	{
		if (m_pFiberParasIn == NULL)
		{
			m_pFiberParasIn = new CIecCfgFiberParasIn();
		}

		return m_pFiberParasIn;
	}
	return NULL;
}

CExBaseObject* CIecCfgSysParas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
//	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGPRIMRATES)
	{
		if (m_pPrimRates == NULL)
		{
		m_pPrimRates = new CIecCfgPrimRates();
		}

		return m_pPrimRates;
	}
	else if (nClassID == CFGCLASSID_CIECCFGPRIMRATESIN)
	{
		if (m_pPrimRatesIn == NULL)
		{
			m_pPrimRatesIn = new CIecCfgPrimRatesIn();
		}

		return m_pPrimRatesIn;
	}
	else if (nClassID == CFGCLASSID_CIECCFGFIBERPARAS)
	{
		if (m_pFiberParas == NULL)
		{
		m_pFiberParas = new CIecCfgFiberParas();
	}

		return m_pFiberParas;
	}
	else if (nClassID == CFGCLASSID_CIECCFGFIBERPARAIN)
	{
		if (m_pFiberParasIn == NULL)
		{
			m_pFiberParasIn = new CIecCfgFiberParasIn();
		}

		return m_pFiberParasIn;
	}

	return NULL;
}

CIecCfgPrimRates* CIecCfgSysParas::GetPrimRates()
{
	if (m_pPrimRates == NULL)
	{
		m_pPrimRates = new CIecCfgPrimRates();
		AddNewChild(m_pPrimRates);
	}

	return m_pPrimRates;
}

CIecCfgPrimRatesIn* CIecCfgSysParas::GetPrimRatesIn()
{
	if (m_pPrimRatesIn == NULL)
	{
		m_pPrimRatesIn = new CIecCfgPrimRatesIn();
		AddNewChild(m_pPrimRatesIn);
		m_pPrimRatesIn->InitCommon(IECCFG_MAX_PT_CT_NUM,IECCFG_MAX_PT_CT_NUM);
	}

	if (m_pPrimRatesIn->GetCount() == 0)
	{
		m_pPrimRatesIn->InitCommon(IECCFG_MAX_PT_CT_NUM,IECCFG_MAX_PT_CT_NUM);
	}

	return m_pPrimRatesIn;
}

CIecCfgFiberParas* CIecCfgSysParas::GetFiberParas()
{
	if (m_pFiberParas == NULL)
	{
		m_pFiberParas = new CIecCfgFiberParas();
		m_pFiberParas->InitCommon(IECCFG_MAX_LC_FIBER_NUM,IECCFG_MAX_ST_FIBER_NUM);
		AddNewChild(m_pFiberParas);
	}

	return m_pFiberParas;
}

CIecCfgFiberParasIn* CIecCfgSysParas::GetFiberParasIn()
{
	if (m_pFiberParasIn == NULL)
	{
		m_pFiberParasIn = new CIecCfgFiberParasIn();
		//m_pFiberParasIn->InitCommon(IECCFG_MAX_LC_FIBER_NUM,IECCFG_MAX_ST_FIBER_NUM);

		AddNewChild(m_pFiberParasIn);
	}

	return m_pFiberParasIn;
}



void CIecCfgSysParas::InitPrimRatesFiberParas(long nCT_GroupNum,long nPT_GroupNum,long nFiberLC_Num,long nFiberST_Num)
{
	GetPrimRates();
	GetPrimRatesIn();
	GetFiberParas();
	GetFiberParasIn();

	m_pPrimRates->InitCommon(nCT_GroupNum,nPT_GroupNum);
	m_pPrimRatesIn->InitCommon(nCT_GroupNum,nPT_GroupNum);
	m_pFiberParas->InitCommon(nFiberLC_Num,nFiberST_Num);
	//m_pFiberParasIn->InitCommon(nFiberLC_Num,nFiberST_Num);
}
