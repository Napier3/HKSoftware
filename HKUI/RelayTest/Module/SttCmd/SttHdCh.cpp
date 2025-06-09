//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttHdCh.cpp  CSttHdCh


#include "stdafx.h"
#include "SttHdCh.h"
#include "SttChMap.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long g_nSttWeekUseMode = STT_WEEK_USE_MODE_NORMAL;//zhouhj 2023.8.3 用于设置弱信号的缺省变比


CSttHdCh::CSttHdCh()
{
	//初始化属性
	m_fCoef = 1.0f;

	//初始化成员变量
}

CSttHdCh::~CSttHdCh()
{
}

long CSttHdCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strCoefKey2, oNode, m_fCoef);

	return 0;
}

long CSttHdCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strCoefKey2, oElement, m_fCoef);

	return 0;
}

long CSttHdCh::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fCoef);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fCoef);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fCoef);
	}
	return 0;
}

void CSttHdCh::InitAfterRead()
{
}

BOOL CSttHdCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttHdCh *p = (CSttHdCh*)pObj;

	if (p->m_fCoef != m_fCoef)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttHdCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttHdCh *p = (CSttHdCh*)pDest;
	p->m_fCoef = m_fCoef;

	return TRUE;
}

CBaseObject* CSttHdCh::Clone()
{
	CSttHdCh *p = new CSttHdCh();
	Copy(p);
	return p;
}

CBaseObject* CSttHdCh::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttHdCh *p = new CSttHdCh();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttHdCh::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTHDCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttHdCh::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		pNew = new CDvmData();
	}

	return pNew;
}

CExBaseObject* CSttHdCh::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pNew = new CDvmData();
	}

	return pNew;
}

void CSttHdCh::SetTransRate_Weak(float fPrimValue,float fSecondValue)
{
	CDvmData *pData = (CDvmData*)FindByID(_T("Primary_Weak"));

	if (pData == NULL)
	{
		pData = new CDvmData;
		pData->m_strName = _T("Primary_Weak");
		pData->m_strID = pData->m_strName;
		pData->m_strDataType = _T("FLOAT");
		AddNewChild(pData);
	}

	pData->m_strValue.Format(_T("%.3f"),fPrimValue);

	pData = (CDvmData*)FindByID(_T("Secondary_Weak"));

	if (pData == NULL)
	{
		pData = new CDvmData;
		pData->m_strName = _T("Secondary_Weak");
		pData->m_strID = pData->m_strName;
		pData->m_strDataType = _T("FLOAT");
		AddNewChild(pData);
	}

	pData->m_strValue.Format(_T("%.3f"),fSecondValue);

	m_fCoef = fPrimValue/fSecondValue;
}

float CSttHdCh::GetPrimaryValue_Float()
{
	CDvmData *pData = GetPrimaryValue_DvmData();
	float fValue = CString_To_double(pData->m_strValue);
	return fValue;
}

float CSttHdCh::GetSecondaryValue_Float()
{
	CDvmData *pData = GetSecondaryValue_DvmData();
	float fValue = CString_To_double(pData->m_strValue);
	return fValue;
}

CDvmData* CSttHdCh::GetPrimaryValue_DvmData()
{
	CDvmData *pData = (CDvmData*)FindByID(_T("Primary_Weak"));

	if (pData == NULL)
	{
		pData = new CDvmData;
		pData->m_strName = _T("Primary_Weak");
		pData->m_strID = pData->m_strName;
		pData->m_strDataType = _T("FLOAT");
		CSttChMap *pChMap = (CSttChMap*)GetAncestor(STTCMDCLASSID_CSTTCHMAP);

		if (g_nSttWeekUseMode == STT_WEEK_USE_MODE_DistriTerm)
		{
			pData->m_strValue = _T("1.0");
		}
		else
		{
			if (pChMap == NULL)
			{
				pData->m_strValue = _T("7.07");
			}
			else if (pChMap->m_strID.IsEmpty())
			{
				pData->m_strValue = _T("7.07");
			}
			else if (pChMap->m_strID.GetAt(0) == 'U')
			{
				pData->m_strValue = _T("120.0");
			}
			else if (pChMap->m_strID.GetAt(0) == 'I')
			{
				pData->m_strValue = _T("30.0");
			}
		}

		AddNewChild(pData);
		float fSecondaryValue = GetSecondaryValue_Float();
		m_fCoef = CString_To_double(pData->m_strValue)/fSecondaryValue;
	}

	return pData;
}

CDvmData* CSttHdCh::GetSecondaryValue_DvmData()
{
	CDvmData *pData = (CDvmData*)FindByID(_T("Secondary_Weak"));

	if (pData == NULL)
	{
		pData = new CDvmData;
		pData->m_strName = _T("Secondary_Weak");
		pData->m_strID = pData->m_strName;
		pData->m_strDataType = _T("FLOAT");
		double dSecondValue = 7.07f;

		if (g_nSttWeekUseMode == STT_WEEK_USE_MODE_DistriTerm)
		{
			pData->m_strValue = _T("1.0");
			dSecondValue = 1.0f;
		}
		else
		{
			pData->m_strValue = _T("7.07");
		}

		AddNewChild(pData);
		float fPrimaryValue = GetPrimaryValue_Float();
		m_fCoef = fPrimaryValue/dSecondValue;
	}

	return pData;
}

void CSttHdCh::SetWeakRateValue(float fWeakRateValue,BOOL bPrimaryValue)
{
	float fWeakRateValue2 = 1;
	CDvmData *pWeakRateData = NULL;

	if (bPrimaryValue)
	{
		fWeakRateValue2 = GetSecondaryValue_Float();
		pWeakRateData = GetPrimaryValue_DvmData();
		pWeakRateData->m_strValue.Format(_T("%.3f"),fWeakRateValue);
		m_fCoef = fWeakRateValue/fWeakRateValue2;
	} 
	else
	{
		fWeakRateValue2 = GetPrimaryValue_Float();
		pWeakRateData = GetSecondaryValue_DvmData();
		pWeakRateData->m_strValue.Format(_T("%.3f"),fWeakRateValue);
		m_fCoef = fWeakRateValue2/fWeakRateValue;
	}
}

void CSttHdCh::UpdateWeekRateValue()
{
	float fSecondValue = GetSecondaryValue_Float();
	float fPrimaryValue = GetPrimaryValue_Float();
	m_fCoef = fPrimaryValue/fSecondValue;
}



