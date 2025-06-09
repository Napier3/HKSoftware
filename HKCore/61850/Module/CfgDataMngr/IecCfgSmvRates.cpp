//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSmvRates.cpp  CIecCfgSmvRates


#include "stdafx.h"
#include "IecCfgSmvRates.h"
#include"../../../Module/API/GlobalConfigApi.h"

CIecCfgSmvRates::CIecCfgSmvRates()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgSmvRates::~CIecCfgSmvRates()
{
}

long CIecCfgSmvRates::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgSmvRates::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgSmvRates::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CIecCfgSmvRates::InitAfterRead()
{
}

BOOL CIecCfgSmvRates::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgSmvRates *p = (CIecCfgSmvRates*)pObj;

	return TRUE;
}

BOOL CIecCfgSmvRates::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgSmvRates *p = (CIecCfgSmvRates*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgSmvRates::Clone()
{
	CIecCfgSmvRates *p = new CIecCfgSmvRates();
	Copy(p);
	return p;
}

BOOL CIecCfgSmvRates::CanPaste(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGSMVRATE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecCfgSmvRates::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgSmvRateKey)
	{
		pNew = new CIecCfgSmvRate();
	}

	return pNew;
}

CExBaseObject* CIecCfgSmvRates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGSMVRATE)
	{
		pNew = new CIecCfgSmvRate();
	}

	return pNew;
}

CString CIecCfgSmvRates::GetCfgDefaultConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SmvRate.xml");

	return strFile;
}


BOOL CIecCfgSmvRates::OpenCfgDefaultConfigFile()
{
	CString strFile = GetCfgDefaultConfigFile();

	BOOL b = OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("config file [%s] is not exist"), strFile.GetString());
		InitDefault();
		SaveCfgDefaultConfigFile();
	}

	return b;
}

CIecCfgSmvRate* CIecCfgSmvRates::AddSmvRate(const CString &strName, float fRate)
{
	CIecCfgSmvRate *pNew = new CIecCfgSmvRate();
	pNew->m_strName = strName;
	pNew->m_strID = strName;
	pNew->m_fRate = fRate;
	AddNewChild(pNew);

	return pNew;
}

BOOL CIecCfgSmvRates::SaveCfgDefaultConfigFile()
{
	CString strFile = GetCfgDefaultConfigFile();

	BOOL b = SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	return b;
}

void CIecCfgSmvRates::InitDefault()
{
	AddSmvRate(SMV_RATEID_STR_UABCZ, 0.01f);
	AddSmvRate(SMV_RATEID_STR_IABC, 0.001f);

	AddSmvRate(SMV_RATEID_STR_UABCZ2, 0.01f);
	AddSmvRate(SMV_RATEID_STR_IABC2, 0.001f);

	AddSmvRate(SMV_RATEID_STR_UABCZ3, 0.01f);
	AddSmvRate(SMV_RATEID_STR_IABC3, 0.001f);

	AddSmvRate(SMV_RATEID_STR_UABCZ4, 0.01f);
	AddSmvRate(SMV_RATEID_STR_IABC4, 0.001f);

	AddSmvRate(SMV_RATEID_STR_UABCZ5, 0.01f);
	AddSmvRate(SMV_RATEID_STR_IABC5, 0.001f);

	AddSmvRate(SMV_RATEID_STR_UABCZ6, 0.01f);
	AddSmvRate(SMV_RATEID_STR_IABC6, 0.001f);
}

float CIecCfgSmvRates::GetSmvRate(const CString &strSmvRatrID)
{
	CIecCfgSmvRate *pFind = (CIecCfgSmvRate*)FindByID(strSmvRatrID);

	if (pFind == NULL)
	{
		return 0.01f;
	}

	return pFind->m_fRate;
}

float CIecCfgSmvRates::GetSmvRate(UINT nSmvRatrID)
{
	CString strSmvRateID = iecfg_GetSmvRateID(nSmvRatrID);

	return GetSmvRate(strSmvRateID);
}

void CIecCfgSmvRates::TransSmvRateID(const CString &strOldID,const CString &strNewID,float fDefautValue)
{
	CIecCfgSmvRate *pFind = (CIecCfgSmvRate*)FindByID(strOldID);

	if (pFind != NULL)
	{
		pFind->m_strName = strNewID;
		pFind->m_strID = pFind->m_strName;
	}
	else
	{
		pFind = (CIecCfgSmvRate*)FindByID(strNewID);
		
		if (pFind == NULL)
		{
			AddSmvRate(strNewID, fDefautValue);
		}
	}
}

void CIecCfgSmvRates::TransSmvRateID()
{
	//zhouhj 2024.6.6 需要兼容老的测试仪,该ID不能随意修改,仍采用老版方式
	TransSmvRateID(_T(""),SMV_RATEID_STR_UABCZ,0.01f);
	TransSmvRateID(_T(""),SMV_RATEID_STR_IABC,0.001f);

	TransSmvRateID(SMV_RATEID_STR_UABCZ2,SMV_RATEID_STR_PUABCZ,0.01f);
	TransSmvRateID(SMV_RATEID_STR_IABC2,SMV_RATEID_STR_PIABC,0.001f);

	TransSmvRateID(SMV_RATEID_STR_UABCZ3,SMV_RATEID_STR_SUABCZ,0.01f);
	TransSmvRateID(SMV_RATEID_STR_IABC3,SMV_RATEID_STR_SIABC,0.001f);

	TransSmvRateID(SMV_RATEID_STR_UABCZ4,SMV_RATEID_STR_TUABCZ,0.01f);
	TransSmvRateID(SMV_RATEID_STR_IABC4,SMV_RATEID_STR_TIABC,0.001f);

	TransSmvRateID(_T(""),SMV_RATEID_STR_UABCZ5,0.01f);
	TransSmvRateID(_T(""),SMV_RATEID_STR_IABC5,0.001f);

	TransSmvRateID(_T(""),SMV_RATEID_STR_UABCZ6,0.01f);
	TransSmvRateID(_T(""),SMV_RATEID_STR_IABC6,0.001f);

// 	TransSmvRateID(SMV_RATEID_STR_PUABCZ,SMV_RATEID_STR_UABCZ2,0.01f);
// 	TransSmvRateID(SMV_RATEID_STR_PIABC,SMV_RATEID_STR_IABC2,0.001f);
// 
// 	TransSmvRateID(SMV_RATEID_STR_SUABCZ,SMV_RATEID_STR_UABCZ3,0.01f);
// 	TransSmvRateID(SMV_RATEID_STR_SIABC,SMV_RATEID_STR_IABC3,0.001f);
// 
// 	TransSmvRateID(SMV_RATEID_STR_TUABCZ,SMV_RATEID_STR_UABCZ4,0.01f);
// 	TransSmvRateID(SMV_RATEID_STR_TIABC,SMV_RATEID_STR_IABC4,0.001f);
// 
// 	TransSmvRateID(_T(""),SMV_RATEID_STR_UABCZ5,0.01f);
// 	TransSmvRateID(_T(""),SMV_RATEID_STR_IABC5,0.001f);
// 
// 	TransSmvRateID(_T(""),SMV_RATEID_STR_UABCZ6,0.01f);
// 	TransSmvRateID(_T(""),SMV_RATEID_STR_IABC6,0.001f);
}

CString iecfg_GetSmvRateID(UINT nSmvRatrID)
{
	if (nSmvRatrID ==  SMV_RATEID_UINT_UABCZ)//   (_T("Uabcz"))
	{
		return SMV_RATEID_STR_UABCZ;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_IABC)//    (_T("Iabc"))
	{
		return SMV_RATEID_STR_IABC;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_UABCZ2)//  (_T("U2-abcz"))
	{
		return SMV_RATEID_STR_UABCZ2;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_IABC2)//   (_T("I2-abc"))
	{
		return SMV_RATEID_STR_IABC2;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_UABCZ3)//  (_T("U3-abcz"))
	{
		return SMV_RATEID_STR_UABCZ3;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_IABC3)//   (_T("I3-abc"))
	{
		return SMV_RATEID_STR_IABC3;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_UABCZ4)//  (_T("U4-abcz"))
	{
		return SMV_RATEID_STR_UABCZ4;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_IABC4)//   (_T("I4-abc"))
	{
		return SMV_RATEID_STR_IABC4;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_UABCZ5)//  (_T("U5-abcz"))
	{
		return SMV_RATEID_STR_UABCZ5;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_IABC5)//   (_T("I5-abc"))
	{
		return SMV_RATEID_STR_IABC5;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_UABCZ6)//  (_T("U6-abcz"))
	{
		return SMV_RATEID_STR_UABCZ6;
	}

	if (nSmvRatrID ==  SMV_RATEID_UINT_IABC6)//   (_T("I6-abc"))
	{
		return SMV_RATEID_STR_IABC6;
	}

	return SMV_RATEID_STR_UABCZ;
}


