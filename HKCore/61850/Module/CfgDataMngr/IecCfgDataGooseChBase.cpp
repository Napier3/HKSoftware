//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataGooseChBase.cpp  CIecCfgDataGooseChBase


#include "stdafx.h"
#include "IecCfgDataGooseChBase.h"

CIecCfgDataGooseChBase::CIecCfgDataGooseChBase()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgDataGooseChBase::~CIecCfgDataGooseChBase()
{
}

long CIecCfgDataGooseChBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	InitDataTypeName();

	return 0;
}

long CIecCfgDataGooseChBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	return 0;
}

BOOL CIecCfgDataGooseChBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDataGooseChBase *p = (CIecCfgDataGooseChBase*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDataGooseChBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataChBase::CopyOwn(pDest);

	CIecCfgDataGooseChBase *p = (CIecCfgDataGooseChBase*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strDataTypeName = m_strDataTypeName;
	return TRUE;
}

CBaseObject* CIecCfgDataGooseChBase::Clone()
{
	CIecCfgDataGooseChBase *p = new CIecCfgDataGooseChBase();
	Copy(p);
	return p;
}

BOOL CIecCfgDataGooseChBase::IsUseChAppID()
{
	if (m_strDataType == g_strGooseChType_Single || m_strDataType == g_strGooseChType_Double)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CIecCfgDataGooseChBase::GetDataType(BYTE &byteDataType, BYTE &byteLen)
{
	iecfg_GooseGetDataType(m_strDataType, byteDataType);
	iecfg_GooseGetDataTypeLen(byteDataType, m_strAppChID, byteLen);

}

BYTE CIecCfgDataGooseChBase::GetDataType()
{
	BYTE byteDataType = 0;
	iecfg_GooseGetDataType(m_strDataType, byteDataType);
	return byteDataType;
}
BYTE  CIecCfgDataGooseChBase::GetDataLen()
{
	BYTE byteDataType = 0, byteLen = 0;
	iecfg_GooseGetDataType(m_strDataType, byteDataType);
	iecfg_GooseGetDataTypeLen(byteDataType, m_strAppChID, byteLen);
	return byteLen;

}

void CIecCfgDataGooseChBase::GetData(BYTE &byteLen, BYTE *byteData)
{

}
// 
// DWORD CIecCfgDataGooseChBase::CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// {
// 	pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_GOOSEOUT;
// 	return 0;
// }

CDataTypeValue* CIecCfgDataGooseChBase::FindGooseChTypeValue(const CString &strName)
{
	// 	CIecGooseChDataTypeMngr *pDataTtypeMngr = CIecGlobalDataMngr::GetGooseDataTypeMngr();
	// 	CDataType *pGooseChType = pDataTtypeMngr->m_pGooseChType;
	CDataTypeValue *pValue = NULL;
	CDataType *pGooseChType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GooseChDataType);

	if (pGooseChType == NULL)
	{
		return NULL;
	}

	pValue = (CDataTypeValue *)pGooseChType->FindByID(strName);

	if (pValue != NULL)
	{
		return pValue;
	}

	CString strText;
	strText = strName;
	strText.MakeUpper();

	if ((strText == "INT8")||(strText == "INT16"))
	{
		pValue = (CDataTypeValue *)pGooseChType->FindByID(_T("INT32"));
	}

	if ((strText == "INT8U")||(strText == "INT16U"))
	{
		pValue = (CDataTypeValue *)pGooseChType->FindByID(_T("INT32U"));
	}

	return pValue;
}


void CIecCfgDataGooseChBase::SetDataTypeByName(const CString &strName)
{
	CDataTypeValue *pValue = FindGooseChTypeValue(strName);

	if (pValue == NULL)
	{
		m_strDataType = g_strGooseChType_Single;
	}
	else
	{
		m_strDataType = pValue->m_strID;
	}

	//m_strAppChID = _T("无");
	InitDataTypeName(TRUE);
}

void CIecCfgDataGooseChBase::InitDataTypeName(BOOL bInitBin)
{
	CDataType *pGooseChType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GooseChDataType);
	CDataTypeValue *pValue = NULL;

	if (pGooseChType == NULL)
	{
		m_strAppChID = g_strAppChID_None;//_T("0");
		m_strDataTypeName = _T("0");
		return;
	}

	pValue = (CDataTypeValue *)pGooseChType->FindByID(m_strDataType);

	if (pValue == NULL)
	{
		m_strDataTypeName = _T("0");
	}
	else
	{
		m_strDataTypeName = pValue->m_strName;
	}

	if (!bInitBin)
	{
		return;
	}

	if (m_strDataType == g_strGooseChType_Single) //       = _T("single");
	{
		m_strAppChID = _T("v0");
	}
	else if (m_strDataType == g_strGooseChType_Double) //       = _T("double");
	{
		m_strAppChID = _T("v01");
	}
	else if (m_strDataType == g_strGooseChType_Time) //         = _T("time");
	{
		m_strAppChID = _T("UTCTime");
	}
	else if (m_strDataType == g_strGooseChType_Quality) //      = _T("quality");
	{
		m_strAppChID = _T("v0");
	}
	else if (m_strDataType == g_strGooseChType_Integer) //      = _T("integer");
	{
		m_strAppChID = _T("v0");
	}
	else if (m_strDataType == g_strGooseChType_Float) //        = _T("float");
	{
		m_strAppChID = _T("v0_0");
	}
	else if (m_strDataType == g_strGooseChType_String) //       = _T("string");
	{
		m_strAppChID = _T("");
	}
	else if (m_strDataType == g_strGooseChType_Struct) //       = _T("struct");
	{
		m_strAppChID = _T("");
	}
	else
	{
		m_strAppChID = _T("0");
	}
}

/*
		data_type	data_len	data_value
SPS		0x01[x83]	0x01		0x00 or 0x01
DPS		0x02[0x84]	0x02		0x06 + 1 byte (0x00, 0x40, 0x80, 0xC0)
Quality	0x84		0x03		0x03 + 2 bytes
Integer	0x85		0x04		4 bytes (integer value High byte…Low byte)
Float	0x87		0x05		0x08 + 4 bytes (float value High byte…low byte)
String	0x8a		<=65		string
Time	0x03[0x91]	0x08		0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
*/

// #define  DT_GooseChType_Single   0x01
// #define  DT_rGooseChType_Double  0x02
// #define  DT_rGooseChType_Time    0x03
// #define  DT_rGooseChType_Quality 0x84
// #define  DT_rGooseChType_Integer 0x85
// #define  DT_rGooseChType_Float   0x87
// #define  DT_rGooseChType_String  0x8a
// #define  DT_rGooseChType_Struct  0x8b

void iecfg_GooseGetDataType(const CString &strDataType, BYTE &byteDataType)
{
	if (strDataType == g_strGooseChType_Single) //       = _T("single");
	{
		byteDataType = DT_GooseChType_Single;
	}
	else if (strDataType == g_strGooseChType_Double) //       = _T("double");
	{
		byteDataType = DT_rGooseChType_Double;
	}
	else if (strDataType == g_strGooseChType_Time) //         = _T("time");
	{
		byteDataType = DT_rGooseChType_Time;
	}
	else if (strDataType == g_strGooseChType_Quality) //      = _T("quality");
	{
		byteDataType = DT_rGooseChType_Quality;
	}
	else if (strDataType == g_strGooseChType_Integer) //      = _T("integer");
	{
		byteDataType = DT_rGooseChType_Integer;
	}
	else if (strDataType == g_strGooseChType_Float) //        = _T("float");
	{
		byteDataType = DT_rGooseChType_Float;
	}
	else if (strDataType == g_strGooseChType_String) //       = _T("string");
	{
		byteDataType = DT_rGooseChType_String;
	}
	else if (strDataType == g_strGooseChType_Struct) //       = _T("struct");
	{
		byteDataType = DT_rGooseChType_Integer;
	}
	else
	{
		byteDataType = 0x01;
	}
}

void iecfg_GooseGetDataTypeLen(BYTE byteDataType, const CString &strAppChID, BYTE &byteLen)
{
	switch (byteDataType)
	{
	case   DT_GooseChType_Single://   0x01
		byteLen = 1;
		break;
	case   DT_rGooseChType_Double://  0x02
		byteLen = 2;
		break;
	case   DT_rGooseChType_Time://    0x03
		byteLen = 8;
		break;
	case   DT_rGooseChType_Quality:// 0x84
		byteLen = 3;
		break;
	case   DT_rGooseChType_Integer:// 0x85
		byteLen = 4;
		break;
	case   DT_rGooseChType_Float://   0x87
		byteLen = 5;
		break;
	case   DT_rGooseChType_String://  0x8a
		byteLen = strAppChID.GetLength();
		break;
	case   DT_rGooseChType_Struct://  0x8b
		byteLen = 1;
		break;
	default:
		byteLen = 1;
		break;
	}

}
