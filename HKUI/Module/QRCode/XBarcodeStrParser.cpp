// XBarcodeStrParser.cpp: implementation of the CXBarcodeStrParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XBarcodeStrParser.h"
#include "..\MemBuffer\EquationBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define _use_qrcode_test

#ifdef _use_qrcode_test
#define _use_qrcode_flag  1
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXBarcodeStrParser::CXBarcodeStrParser()
{
	ZeroMemory(m_pszBarCodeBuffer, QRCODE_BUFFER_LEN);
	m_nBarCodeLen = 0;
	m_nBarCodeMode = BARCODE_MODE_TWO_SEPERATER;
	m_bShowLog = FALSE;
}

CXBarcodeStrParser::~CXBarcodeStrParser()
{

}

void CXBarcodeStrParser::SetSeparateChar(char chSeparateChar, char chSeparateCharEnd)
{
	if (chSeparateCharEnd != 0)
	{
		m_nBarCodeMode = BARCODE_MODE_TWO_SEPERATER;
	}
	else
	{
		m_nBarCodeMode = BARCODE_MODE_ONE_SEPERATER;
	}

	m_strSeparateEndChar = chSeparateCharEnd;
	m_strSeparateChar = chSeparateChar;
}

void CXBarcodeStrParser::SetSeparateChar(const CString &strSeparateChar, const CString &strSeparateEndChar)
{
	if (strSeparateEndChar.GetLength() > 0)
	{
		m_nBarCodeMode = BARCODE_MODE_TWO_SEPERATER;
	}
	else
	{
		m_nBarCodeMode = BARCODE_MODE_ONE_SEPERATER;
	}

	m_strSeparateEndChar = strSeparateEndChar;
	m_strSeparateChar = strSeparateChar;
}

void CXBarcodeStrParser::InitParser()
{
	m_nBarCodeLen = 0;
	ZeroMemory(m_pszBarCodeBuffer, QRCODE_BUFFER_LEN);
}


BOOL CXBarcodeStrParser::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_CHAR)
	{
		AddChars(pMsg->wParam);
		return TRUE;
	}

	return FALSE;
}

void CXBarcodeStrParser::AddChars(WPARAM wParam)
{
#ifdef _use_qrcode_test

#ifdef _use_qrcode_flag
	//strcpy(m_pszBarCodeBuffer, "类型:D30$厂商:XX集团$型号:DTU3001$ID:D3012345665466121223$硬件版本:HV20.11$生产日期:2013年2月8日$");
	strcpy(m_pszBarCodeBuffer, "Factory=XX集团;Model=DTU3001;SN=D3012345665466121223;DateProduce=2013年2月8日;DateManufac=2013年3月8日;CityCode=1234;CountyCode=5678;");
#else
	strcpy(m_pszBarCodeBuffer, "751234567890");
#endif

	m_nBarCodeLen = strlen(m_pszBarCodeBuffer)*2;

#else
	m_pszBarCodeBuffer[m_nBarCodeLen] = (wParam >> 8) & 0xFF;
	m_nBarCodeLen++;
	m_pszBarCodeBuffer[m_nBarCodeLen] = wParam & 0xFF;
	m_nBarCodeLen++;
#endif
}

void CXBarcodeStrParser::SetQRCodeString(char *pBuffer, long nEncodeType)
{
	strcpy(m_pszBarCodeBuffer, pBuffer);
	m_nBarCodeLen = strlen(pBuffer);
	CLogPrint::LogString(XLOGLEVEL_TRACE, m_pszBarCodeBuffer);
	OnQRCodeInput(nEncodeType);
}

// BOOL CXBarcodeStrParser::FinishBarCodeInput()
// {
// 	if (m_nBarCodeLen <= 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (m_oCTickCount32.GetTickCountLong(FALSE) > QRCODE_TIMERLONG)
// 	{
// 		OnQRCodeInput();
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
// }

void CXBarcodeStrParser::GetDatas(CShortDatas *pDatas)
{
	POS posValue = m_oValues.GetHeadPosition();
	POS posData = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	CValue *pValue = NULL;

	if (m_nBarCodeMode == BARCODE_MODE_TWO_SEPERATER)
	{
		while (posData != NULL)
		{
			pData = (CShortData *)pDatas->GetNext(posData);
			pValue = (CValue *)m_oValues.FindByID(pData->m_strID);

			if (pValue == NULL)
			{
				pValue = (CValue *)m_oValues.FindByID(pData->m_strName);
			}

			if (pValue != NULL)
			{
				pData->m_strValue = pValue->m_strValue;
			}
			else
			{
				pData->m_strValue.Empty();
			}
		}
	}
	else
	{
		while (posData != NULL && posValue != NULL)
		{
			pData = (CShortData *)pDatas->GetNext(posData);
			pValue = (CValue *)m_oValues.GetNext(posValue);

			pData->m_strValue = pValue->m_strValue;
		}
	}
}

void CXBarcodeStrParser::GetDatas(CDvmDataset *pDatas)
{
	POS posValue = m_oValues.GetHeadPosition();
	POS posData = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;
	CValue *pValue = NULL;

	if (m_nBarCodeMode == BARCODE_MODE_TWO_SEPERATER)
	{
		while (posData != NULL)
		{
			pData = (CDvmData *)pDatas->GetNext(posData);
			pValue = (CValue *)m_oValues.FindByID(pData->m_strID);

			if (pValue == NULL)
			{
				pValue = (CValue *)m_oValues.FindByID(pData->m_strName);
			}

			if (pValue != NULL)
			{
				pData->m_strValue = pValue->m_strValue;
			}
			else
			{
				pData->m_strValue.Empty();
			}
		}
	}
	else
	{
		while (posData != NULL && posValue != NULL)
		{
			pData = (CDvmData *)pDatas->GetNext(posData);
			pValue = (CValue *)m_oValues.GetNext(posValue);

			pData->m_strValue = pValue->m_strValue;
		}
	}
}

void CXBarcodeStrParser::NewDatas(CShortDatas *pDatas)
{
	ASSERT (m_nBarCodeMode == BARCODE_MODE_TWO_SEPERATER);

	POS posValue = m_oValues.GetHeadPosition();
	CShortData *pData = NULL;
	CValue *pValue = NULL;

	while (posValue != NULL)
	{
		pValue = (CValue *)m_oValues.GetNext(posValue);
		pData = new CShortData();
		pData->m_strName = pValue->m_strID;
		pData->m_strID = pValue->m_strID;
		pData->m_strValue = pValue->m_strValue;
		pDatas->AddNewChild(pData);
	}
}

void CXBarcodeStrParser::NewDatas(CDvmDataset *pDatas)
{
	ASSERT (m_nBarCodeMode == BARCODE_MODE_TWO_SEPERATER);

	POS posValue = m_oValues.GetHeadPosition();
	CDvmData *pData = NULL;
	CValue *pValue = NULL;

	while (posValue != NULL)
	{
		pValue = (CValue *)m_oValues.GetNext(posValue);
		pData = new CDvmData();
		pData->m_strName = pValue->m_strID;
		pData->m_strID = pValue->m_strID;
		pData->m_strValue = pValue->m_strValue;
		pDatas->AddNewChild(pData);
	}
}

void CXBarcodeStrParser::OnQRCodeInput(long nEncodeType)
{
	char pszBarCodeBuffer[QRCODE_BUFFER_LEN];
	ZeroMemory(pszBarCodeBuffer, QRCODE_BUFFER_LEN);

#ifdef _use_qrcode_test
	strcpy(pszBarCodeBuffer, m_pszBarCodeBuffer);
	long nLen = strlen(pszBarCodeBuffer);
#else
// 	long nLen = 0;
// 	
// 	if (nEncodeType == 0)
// 	{
// 		nLen = UnicodeToChar(m_pszBarCodeBuffer, pszBarCodeBuffer, m_nBarCodeLen);
// 	}
// 	else
// 	{
// 		memcpy(m_pszBarCodeBuffer, pszBarCodeBuffer, m_nBarCodeLen);
// 		nLen = m_nBarCodeLen;
// 	}

#endif

	m_strQRCodeData = pszBarCodeBuffer;

	if (m_bShowLog)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s"), m_strQRCodeData);
	}
	
	long nBarCodeLen = strlen (pszBarCodeBuffer);

	if (nBarCodeLen <= 13)
	{
		m_oValues.AddValue(_T("QRCode"), m_strQRCodeData);
		return;
	}

	if (m_nBarCodeMode == BARCODE_MODE_TWO_SEPERATER)
	{
		ParseBarCode2(pszBarCodeBuffer);
	}
	else
	{
		ParseBarCode1(pszBarCodeBuffer);
	}

	m_nBarCodeLen = 0;

	//添加装置二维码数据
	m_oValues.AddValue(_T("DeviceCode"), m_strQRCodeData);
}


void CXBarcodeStrParser::ParseBarCode2(const char *pBuffer)
{
	m_oValues.DeleteAll();
	long nBarCodeLen = strlen (pBuffer);
	CEquationBuffer oBuffer;
	oBuffer.SetSeparateChar(m_strSeparateChar);
	oBuffer.SetSeparateEndChar(m_strSeparateEndChar);
	oBuffer.InitBuffer(pBuffer, pBuffer + nBarCodeLen);

	CValue *pValue = NULL;
	POS pos = oBuffer.GetHeadPosition();
	CEquationKey *pKey = NULL;

	while (pos != NULL)
	{
		pKey = (CEquationKey *)oBuffer.GetNext(pos);
		pValue = m_oValues.AddValue(pKey->GetKeyName(), pKey->GetKeyValue());

		if (m_bShowLog)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] = [%s]"), pValue->m_strID, pValue->m_strValue);
		}
	}
}

void CXBarcodeStrParser::ParseBarCode1(const char *pBuffer)
{
	CShortData *pData = NULL;
	long nBarCodeLen = strlen (pBuffer);
	CBufferBase oBuffer;
	oBuffer.InitBuffer(pBuffer, pBuffer + nBarCodeLen);
	oBuffer.FormatBuffer(m_strSeparateChar.GetAt(0));
	CValue *pValue = NULL;

	const char *pString = oBuffer.GetString();
	CString strValue;

	while (oBuffer.IsPoiterInBuffer(pString))
	{
		strValue = pString;
		pValue = m_oValues.AddValue(_T("Value"), strValue);
		pString = oBuffer.NextString();
		pString = oBuffer.GetString();
	}
}
