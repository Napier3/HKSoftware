#include "stdafx.h"
#include "SttProtocolDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//global functions
void stt_pp_data_free(STT_PP_DATA &oData)
{
	switch (oData.type)
	{
	case STT_PP_DATATYPE_STRING:
		delete oData.val.pszString;
		oData.val.pszString = NULL;
		break;

	case STT_PP_DATATYPE_CPTIMEINT32:
	case STT_PP_DATATYPE_CPTIMEINT56:
	case STT_PP_DATATYPE_BUFFER:
		delete oData.val.pBuf;
		oData.val.pBuf = NULL;
		break;

	default:
		break;
	}

	if (oData.pPpDatas != NULL)
	{
		for (int k=0; k<oData.nCount; k++)
		{
			stt_pp_data_free(oData.pPpDatas[k]);
		}

		delete oData.pPpDatas;
		oData.pPpDatas = NULL;
	}
}

void stt_pp_data_free(PSTT_PP_DATA pData)
{
	stt_pp_data_free(*pData);
	delete pData;
}


void stt_pp_data_get_ipVal(long len, STT_PP_VALUE &val, CString &strIP,CString &strMask)
{
	ASSERT((len == 8) || (len == 12));

	if (len == 8)
	{
		strIP.Format(_T("%u.%u.%u.%u"),val.pBuf[0], val.pBuf[1], val.pBuf[2], val.pBuf[3]);
		strMask.Format(_T("%u.%u.%u.%u"),val.pBuf[4],val.pBuf[5],val.pBuf[6],val.pBuf[7]);
	}
	else
	{
		strIP.Format(_T("%u.%u.%u.%u.%u.%u"),val.pBuf[0],val.pBuf[1],val.pBuf[2],val.pBuf[3],val.pBuf[4],val.pBuf[5]);
		strMask.Format(_T("%u.%u.%u.%u.%u.%u"),val.pBuf[6],val.pBuf[7],val.pBuf[8],val.pBuf[9],val.pBuf[10],val.pBuf[11]);
	}
}

void stt_pp_data_get_ipVal(STT_PP_DATA *pPpData,CString &strIP,CString &strMask)
{
	stt_pp_data_get_ipVal(pPpData->len, pPpData->val, strIP, strMask);
}

long stt_pp_value_set_string(STT_PP_VALUE &val, const CString &strData)
{
	long nLen = String_Char_Count(strData);
	val.pszString = new char[nLen+1];
	CString_to_char(strData, val.pszString);

	return nLen;
}

void stt_pp_data_set_string(STT_PP_DATA *pPpData,BYTE nDataID, const CString &strData)
{
	pPpData->id = nDataID;
	pPpData->type = STT_PP_DATATYPE_STRING;
	pPpData->len = (BYTE)stt_pp_value_set_string(pPpData->val, strData);
}


BOOL stt_pp_data_get_string(STT_PP_DATA *pPpData, CString &strData)
{
	if (pPpData->type == STT_PP_DATATYPE_STRING)
	{
		char *pNewString = new char[pPpData->len + 1];
		memcpy(pNewString, pPpData->val.pszString, pPpData->len);
		pNewString[pPpData->len] = 0;
		strData = pNewString;
		delete pNewString;

		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
CSttPpDatas::CSttPpDatas()
{

}

CSttPpDatas::~CSttPpDatas()
{
	DeleteAllDatas();
}

//结构体STT_PP_DATA没有实现析构函数，要是用stt_pp_data_free来释放
//CTLinkList::DeleteAll只释放对象本身，没有释放对象的子数据，所以实现DeleteAllDatas
void CSttPpDatas::DeleteAllDatas()
{
	POS pos = GetHeadPosition();
	PSTT_PP_DATA p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		stt_pp_data_free(p);
	}

	RemoveAll();
}

PSTT_PP_DATA CSttPpDatas::AddData(BYTE nDataID, const CString &strData)
{
	PSTT_PP_DATA pNew = (PSTT_PP_DATA)malloc(sizeof(STT_PP_DATA));
	stt_pp_data_set_string(pNew, nDataID, strData);
	pNew->id = nDataID;
	pNew->type = STT_PP_DATATYPE_STRING;
	return pNew;
}

BOOL CSttPpDatas::FindDataByID(BYTE id, CString &strValue)
{
	POS pos = GetHeadPosition();
	PSTT_PP_DATA p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->id == id)
		{
			return stt_pp_data_get_string(p, strValue);
		}
	}

	return FALSE;
}

BOOL CSttPpDatas::FindDataByID(BYTE id, long &nValue)
{
	POS pos = GetHeadPosition();
	PSTT_PP_DATA p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->id == id)
		{
			if (p->type == STT_PP_DATATYPE_LONG)
			{
				nValue = p->val.lVal;
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CSttPpDatas::FindDataByID(BYTE id, CString &strIP, CString &strMask)
{
	POS pos = GetHeadPosition();
	PSTT_PP_DATA p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->id == id)
		{
			stt_pp_data_get_ipVal(p, strIP, strMask);
			return TRUE;
		}
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//CSttPpDatasDriver
CSttPpDatasDriver::CSttPpDatasDriver()
{

}

CSttPpDatasDriver::CSttPpDatasDriver(CXObjectRefBase* lpXObject, BOOL bAutoRelease )
: CXObjectRefDriver(lpXObject, bAutoRelease)
{

}

CSttPpDatasDriver::CSttPpDatasDriver(const CSttPpDatasDriver& oXobjRefSrc)
: CXObjectRefDriver(oXobjRefSrc)
{

}

CSttPpDatas* CSttPpDatasDriver::CreateDatas()
{
	CSttPpDatas *pNew = new CSttPpDatas();
	m_lpXObject = pNew;
	m_lpXObject->AddRef();

	return pNew;
}

CSttPpDatas* CSttPpDatasDriver::GetDatas()
{
	return (CSttPpDatas*)m_lpXObject;
}

CSttPpDatasDriver::~CSttPpDatasDriver()
{


}

