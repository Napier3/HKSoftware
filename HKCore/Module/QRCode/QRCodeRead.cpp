
// QRCodeReadDv.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "QRCodeRead.h"
#include "XBarcodeStrParser.h"

#define SERIAL_INPUTBUFFERLEN  4096//输入缓冲区长度。单位：bytes
#define SERIAL_OUTBUFFERLEN    4096//输出缓冲区长度。单位：bytes

// #define _use_CQRCodeReadDebugDlg

#ifdef _use_CQRCodeReadDebugDlg
#include "..\DialogBase\DynDialogEx.h"
#include "..\API\GloblaDrawFunctions.h"

class CQRCodeReadDebugDlg : public CDynDialogEx
{
public:
	CQRCodeReadDebugDlg(CWnd* pParent = NULL);
	virtual ~CQRCodeReadDebugDlg();

	CEdit m_editQRCodeText;
	CButton m_btnWrite;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnWriteQRCode();
};

CQRCodeReadDebugDlg::CQRCodeReadDebugDlg(CWnd* pParent)
	:CDynDialogEx(pParent)
{

}

CQRCodeReadDebugDlg::~CQRCodeReadDebugDlg()
{

}


void CQRCodeReadDebugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CQRCodeReadDebugDlg, CDynDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(2338, &CQRCodeReadDebugDlg::OnWriteQRCode)
END_MESSAGE_MAP()


void CQRCodeReadDebugDlg::OnCancel()
{
}

void CQRCodeReadDebugDlg::OnOK()
{
}

void CQRCodeReadDebugDlg::OnClose()
{
	//ShowWindow(SW_HIDE);
}

BOOL CQRCodeReadDebugDlg::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CRect rcClient(5, 5, 400, 80);
	CreateMultiEdit(m_editQRCodeText, rcClient, 2337, this);
	rcClient.top = rcClient.bottom + 5;
	rcClient.bottom = rcClient.top + 22;
	rcClient.right = rcClient.left + 80;
	CreateButton(m_btnWrite, _T("发送"), rcClient, 2338, this);

	m_editQRCodeText.SetFont(g_pGlobalFont11);
	m_btnWrite.SetFont(g_pGlobalFont11);

	GetWindowRect(rcClient);
	rcClient.right = rcClient.left + 420;
	rcClient.bottom = rcClient.top + 140;
	MoveWindow(rcClient);
	CenterWindow();

	SetWindowText(_T("二维码模拟输入"));

	return TRUE;
}

void CQRCodeReadDebugDlg::OnWriteQRCode()
{
	CString strText;
	m_editQRCodeText.GetWindowText(strText);
	char pszBuffer[1024];
	CString_to_char(strText, pszBuffer);
	CQRCodeRead::DebugWrite(pszBuffer);
}

CQRCodeReadDebugDlg *g_pCQRCodeReadDebugDlg = NULL;

#endif

//////////////////////////////////////////////////////////////////////////
//CQRCodeRead
CFile CQRCodeRead::m_file;

long CQRCodeRead::g_nQRCodeReadRef = 0;
CQRCodeRead* CQRCodeRead::g_pQRCodeRead = NULL;

CString CQRCodeRead::g_astrSeparateSrc[Separate_CHAR_MAP_MAX] 
= {_T("；"), _T("："), _T("，"), _T("="), _T(";"), _T(","), _T(":"), _T("")};
CString CQRCodeRead::g_astrSeparateDest[Separate_CHAR_MAP_MAX] 
= {_T(";"), _T(":"), _T(","), _T("="), _T("；"), _T("，"), _T("："), _T("")};


CQRCodeRead::CQRCodeRead()
{
// 	m_nBaud = 19200;
// 	m_nDatabits = 8;
// 	m_nStopsbits = 1;
// 	m_nParity = 0;
// 	m_nPortNo = 4;
//	m_nLogFile = 0;
// 	m_nEncodeType = QRCODE_EncodeType_none;

	m_pSerial = NULL;
	m_nRcvBufLen = 0;
	m_bExitQRCodeReadThread = FALSE;
	m_nMsgRcv = WM_QRCODEREAD_FINISH;
	m_bOpenSerialSucc = FALSE;
	m_bInOpenSerial = FALSE;
	m_pQRReadThread = NULL;
	m_nChnHeadCharInvalid = 0;
	m_nEncodeType = QRCODE_EncodeType_GBK;

// 	m_pQRCodeReadSepChars = NULL;
// 	m_pQRCodeReadSepEndChars = NULL;

	CQRCodeReadXmlRWKeys::Create();
}

CQRCodeRead::~CQRCodeRead()
{
	CQRCodeReadXmlRWKeys::Release();

	CloseQRCodeRead();

	if (m_nLogFile)
	{
		m_file.Close();
	}
}

CQRCodeRead* CQRCodeRead::Create()
{
	g_nQRCodeReadRef++;

	if (g_nQRCodeReadRef == 1)
	{
		g_pQRCodeRead = new CQRCodeRead();
		g_pQRCodeRead->OpenCfgFile();

#ifdef _use_CQRCodeReadDebugDlg
	g_pCQRCodeReadDebugDlg = new CQRCodeReadDebugDlg(AfxGetMainWnd());
	g_pCQRCodeReadDebugDlg->SetUseModeless();
	g_pCQRCodeReadDebugDlg->DoModal();
#endif
	}

	return g_pQRCodeRead;
}

void CQRCodeRead::Release()
{
	g_nQRCodeReadRef--;

	if (g_nQRCodeReadRef == 0)
	{
		delete g_pQRCodeRead;
		g_pQRCodeRead = NULL;

#ifdef _use_CQRCodeReadDebugDlg
	delete g_pCQRCodeReadDebugDlg;
	g_pCQRCodeReadDebugDlg = NULL;
#endif
	}
}

void CQRCodeRead::AttachMsgRcvWnd(CWnd *pMsgRcvWnd, UINT nMsg)
{
	ASSERT (g_pQRCodeRead != NULL);
	g_pQRCodeRead->In_AttachMsgRcvWnd(pMsgRcvWnd, nMsg);
}

void CQRCodeRead::DetachMsgWnd()
{
	ASSERT (g_pQRCodeRead != NULL);
	g_pQRCodeRead->In_DetachMsgWnd();
}

long CQRCodeRead::GetQRCodeValues(CValues &oValues, BOOL bFreeValues)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_GetQRCodeValues(oValues, bFreeValues);
}

CString CQRCodeRead::GetQRCodeData()
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_GetQRCodeData();
}


void CQRCodeRead::InitQRCodeReadParser(char chSeparateChar, char chSeparateEndChar)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_InitQRCodeReadParser(chSeparateChar, chSeparateEndChar);
}

void CQRCodeRead::InitQRCodeReadParser(const CString &strSeparateChar, const CString &strSeparateEndChar)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_InitQRCodeReadParser(strSeparateChar, strSeparateEndChar);
}

void CQRCodeRead::GetDatas(CExBaseList *pDatas)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_GetDatas(pDatas);
}

void CQRCodeRead::GetDatas(CDvmDataset *pDatas)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_GetDatas(pDatas);
}

void CQRCodeRead::NewDatas(CShortDatas *pDatas)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_NewDatas(pDatas);
}

void CQRCodeRead::NewDatas(CDvmDataset *pDatas)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_NewDatas(pDatas);
}

void CQRCodeRead::DebugWrite(char *pszBuffer)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_DebugWrite(pszBuffer);
}

BOOL CQRCodeRead::Match(CDvmDataset *pDatas)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_Match(pDatas);
}

BOOL CQRCodeRead::Match(CShortDatas *pDatas)
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->In_Match(pDatas);
}

long CQRCodeRead::GetQrCodeEnType()
{
	ASSERT (g_pQRCodeRead != NULL);
	return g_pQRCodeRead->m_nEncodeType;
}

void CQRCodeRead::SetQrCodeEnType(long nEnType)
{
	ASSERT (g_pQRCodeRead != NULL);
	g_pQRCodeRead->m_nEncodeType = nEnType;
}

void CQRCodeRead::InputQRCodeString(const CString &strQRCode)
{
	ASSERT (g_pQRCodeRead != NULL);
	g_pQRCodeRead->In_InputQRCodeString(strQRCode);
}

void CQRCodeRead::InputQRCodeStringEx(const CString &strQRCode)
{
	ASSERT (g_pQRCodeRead != NULL);
	g_pQRCodeRead->In_InputQRCodeStringEx(strQRCode);
}

void CQRCodeRead::ValidateSepChars(const CString &strQRCode)
{
	ASSERT (g_pQRCodeRead != NULL);
	g_pQRCodeRead->In_ValidateSepChars(strQRCode);
}

//////////////////////////////////////////////////////////////////////////
//内部函数
long CQRCodeRead::In_GetQRCodeValues(CValues &oValues, BOOL bFreeValues)
{
	CValues *pValues = m_oXBarcodeStrParser.GetValues();
	long nCount = pValues->GetCount();

	oValues.AppendCloneEx(*pValues);

	if (bFreeValues)
	{
		pValues->DeleteAll();
	}
	
	return nCount;
}

CString CQRCodeRead::In_GetQRCodeData()
{
	return m_oXBarcodeStrParser.GetQRCodeData();
}

void CQRCodeRead::In_InitQRCodeReadParser(char chSeparateChar, char chSeparateEndChar)
{
	m_oXBarcodeStrParser.InitParser();

	if (m_strSeparateChar.GetLength() > 0)
	{
		m_oXBarcodeStrParser.SetSeparateChar(m_strSeparateChar, m_strSeparateEndChar);
	}
	else
	{
		m_oXBarcodeStrParser.SetSeparateChar(chSeparateChar, chSeparateEndChar);
	}
}

void CQRCodeRead::In_InitQRCodeReadParser(const CString &strSeparateChar, const CString &strSeparateEndChar)
{
	m_oXBarcodeStrParser.InitParser();
	m_oXBarcodeStrParser.SetSeparateChar(strSeparateChar, strSeparateEndChar);
}

void CQRCodeRead::In_GetDatas(CExBaseList *pDatas)
{
	m_oXBarcodeStrParser.GetDatas(pDatas);
}

void CQRCodeRead::In_GetDatas(CDvmDataset *pDatas)
{
	m_oXBarcodeStrParser.GetDatas(pDatas);
}

void CQRCodeRead::In_NewDatas(CShortDatas *pDatas)
{
	m_oXBarcodeStrParser.NewDatas(pDatas);
}

void CQRCodeRead::In_NewDatas(CDvmDataset *pDatas)
{
	m_oXBarcodeStrParser.NewDatas(pDatas);
}

void CQRCodeRead::In_DebugWrite(char *pszBuffer)
{
#ifdef _use_CQRCodeReadDebugDlg
	strcpy((char*)m_byteQRCodeBuffer, pszBuffer);
	m_nRcvBufLen = strlen(pszBuffer);
#endif
}

BOOL CQRCodeRead::In_Match(CDvmDataset *pDatas)
{
	CValues *pValues = m_oXBarcodeStrParser.GetValues();

// 	if (pDatas->GetCount() != pValues->GetCount())
// 	{
// 		return FALSE;
// 	}

	POS pos = pDatas->GetHeadPosition();
	CDvmData *pData = NULL;
	BOOL bMatch = TRUE;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDatas->GetNext(pos);

		if (pValues->FindByID(pData->m_strID) == NULL)
		{
			bMatch = FALSE;
			break;
		}
	}

	return bMatch;
}

BOOL CQRCodeRead::In_Match(CShortDatas *pDatas)
{
	CValues *pValues = m_oXBarcodeStrParser.GetValues();

	if (pDatas->GetCount() != pValues->GetCount())
	{
		return FALSE;
	}

	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	BOOL bMatch = TRUE;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);

		if (pValues->FindByID(pData->m_strID) == NULL)
		{
			bMatch = FALSE;
			break;
		}
	}

	return bMatch;
}

BOOL CQRCodeRead::OpenCfgFile()
{
	BOOL bRet = CQRCodeReadConfigs::OpenCfgFile();

	if (m_nLogFile == 1)
	{
		CString strFile;
		strFile = _P_GetBinPath();
		strFile += _T("QRCodeRead.txt");
		m_nLogFile = m_file.Open(strFile, CFile::modeWrite | CFile::modeCreate);
	}

	In_InitQRCodeReadParser(m_strSeparateChar, m_strSeparateEndChar);

	return bRet;
}

bool CQRCodeRead::InitQRCodeRead()
{
	if (m_pSerial == NULL)
	{
		m_pSerial = new CSerial();
	}

	m_bOpenSerialSucc = FALSE;

	if(m_pSerial->OpenSerial(m_nPortNo) == CODE_ERROR)
	{
		WriteLog("打开串口失败；\r\n");
		return false;
	}

	m_pSerial->SetSerialBufferSize(SERIAL_INPUTBUFFERLEN, SERIAL_OUTBUFFERLEN);
	m_pSerial->m_SerialDcbStruct.DCBlength = sizeof(DCB);

	if(m_pSerial->GetSerialAttributes() == CODE_ERROR)
	{
		WriteLog("获取串口属性口失败；\r\n");
		return false;
	}

	if(m_pSerial->SetSerialAttributes(m_nBaud,m_nDatabits,m_nStopsbits,m_nParity) == CODE_ERROR)
	{
		WriteLog("设置串口属性口失败；\r\n");
		return false;
	}

	m_bOpenSerialSucc = TRUE;
	return true;
}

void CQRCodeRead::CloseQRCodeRead()
{
	if (m_pSerial != NULL)
	{
		m_pSerial->CloseSerial();
		delete m_pSerial;
		m_pSerial = NULL;
		m_bOpenSerialSucc = FALSE;
	}
}

void CQRCodeRead::CreateQRCodeReadThread()
{
	if (m_pQRReadThread != NULL)
	{
		return;
	}

	m_bExitQRCodeReadThread = FALSE;
	m_pQRReadThread = AfxBeginThread(ReadSerialDataThread, (LPVOID)this); //启动线程 
	m_pQRReadThread->m_bAutoDelete = TRUE;
}

void CQRCodeRead::WriteLog(char *pszLog)
{
	if (m_nLogFile == 0 )
	{
		return;
	}

	m_file.Write(pszLog, strlen(pszLog));
}

void CQRCodeRead::In_InputQRCodeString(const CString &strQRCode)
{
	m_nRcvBufLen = CString_to_char(strQRCode, (char*)m_byteQRCodeBuffer);
	m_nRcvBufLen = strlen((char*)m_byteQRCodeBuffer);
	m_oXBarcodeStrParser.SetQRCodeString(ReadQRCodeBuffer(), QRCODE_EncodeType_ASCII);
}

void CQRCodeRead::In_InputQRCodeStringEx(const CString &strQRCode)
{
	In_InputQRCodeString(strQRCode);

	if (!m_oXBarcodeStrParser.HasValues())
	{
		m_strSeparateCharBk = m_strSeparateChar;
		m_strSeparateEndCharBk = m_strSeparateEndChar;
		ChangeSeparate(0);
	}
}


void CQRCodeRead::In_AttachMsgRcvWnd(CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_pMsgRcv = pMsgRcvWnd;
	m_nMsgRcv = nMsg;

//2018-1-5
// 	if (!m_bOpenSerialSucc)
// 	{
// 		InitQRCodeRead();
// 	}

	if (QRCODE_EncodeType_none == m_nEncodeType)
	{
		return;
	}

	CreateQRCodeReadThread();
}

void CQRCodeRead::In_DetachMsgWnd()
{
	if (m_pQRReadThread == NULL)
	{
		return;
	}

	m_bExitQRCodeReadThread = TRUE;
	long nCount = 0;

	if (m_bInOpenSerial)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("等待二维码扫描模块结束......"));
		CTickCount32 oTick;
		oTick.DoEvents(100);
	}

	while (m_pQRReadThread != NULL)
	{
		Sleep(10);

		if (nCount >= 500)
		{
			break;
		}

		nCount++;
	}

	//CloseQRCodeRead();

	m_pMsgRcv = NULL;
}


void CQRCodeRead::ReadQRCodeBuffer(char *pDestBuffer)
{
	memcpy(pDestBuffer, m_byteQRCodeBuffer, m_nRcvBufLen);
	pDestBuffer[m_nRcvBufLen] = 0;
	m_nRcvBufLen = 0;
}

char* CQRCodeRead::ReadQRCodeBuffer()
{
	m_byteQRCodeBuffer[m_nRcvBufLen] = 0;
	m_nRcvBufLen = 0;

	if (m_nChnHeadCharInvalid != 0)
	{//2021-1-7 lijunqing  中文时，第一个字符无效
		if (m_byteQRCodeBuffer[1] > 128)
		{
			return  (char*)(m_byteQRCodeBuffer+1);
		}
		else
		{
			 return (char*)m_byteQRCodeBuffer;
		}
	}
	else
	{
		return (char*)m_byteQRCodeBuffer;
	}
}

void CQRCodeRead::ReadSerialData()
{
	char byteBufferRead[1024];
	DWORD nReadLen = 0;
	char pszHexBuffer[4096];
	DWORD nReadTotalLen = 0;

	while (TRUE)
	{
		if (m_bExitQRCodeReadThread)
		{
			break;
		}

		nReadLen = 0;
		m_pSerial->RecieveData(byteBufferRead,nReadLen);
		nReadTotalLen = 0;

		if (nReadLen > 0)
		{
			memcpy(m_byteQRCodeBuffer+m_nRcvBufLen, byteBufferRead, nReadLen);
			m_nRcvBufLen += nReadLen;
			nReadTotalLen += nReadLen;

			do 
			{
				if (m_bExitQRCodeReadThread)
				{
					break;
				}

				Sleep(50);
				m_pSerial->RecieveData(byteBufferRead,nReadLen);

				if (nReadLen > 0)
				{
					memcpy(m_byteQRCodeBuffer+m_nRcvBufLen, byteBufferRead, nReadLen);
					m_nRcvBufLen += nReadLen;
					nReadTotalLen += nReadLen;
				}
			} while (nReadLen > 0);

			if (m_nLogFile)
			{
				ValueToHex(m_byteQRCodeBuffer, m_nRcvBufLen, pszHexBuffer, TRUE, FALSE);
				WriteLog(pszHexBuffer);
			}

			if (m_bExitQRCodeReadThread)
			{
				break;
			}
		}

#ifdef _use_CQRCodeReadDebugDlg
		nReadTotalLen = m_nRcvBufLen;
#endif

		if (nReadTotalLen > 0)
		{
			//解析收到的二维码，发送消息
			if (m_nEncodeType == QRCODE_EncodeType_GBK)
			{
				m_byteQRCodeBuffer[m_nRcvBufLen] = 0;
				ConvertUtf8ToGBK(m_byteQRCodeBuffer);
				m_nRcvBufLen = strlen((char*)m_byteQRCodeBuffer);
				nReadTotalLen = m_nRcvBufLen;
			}
			else if (m_nEncodeType == QRCODE_EncodeType_ASCII)
			{
				m_byteQRCodeBuffer[m_nRcvBufLen] = 0;
				m_nRcvBufLen = UnicodeToChar((char*)m_byteQRCodeBuffer ,m_nRcvBufLen);
				nReadTotalLen = m_nRcvBufLen;
			}

			//20190912  扫码枪第一个字符为异常字符的处理  lijunqing
			//此处还有错误，异常考虑不周到
			//OffsetSerialData();  2021-1-7  lijunqing 通过配置去除无效的第一个字符

			m_oXBarcodeStrParser.SetQRCodeString(ReadQRCodeBuffer(), m_nEncodeType);
			m_pMsgRcv->SendMessage(m_nMsgRcv,(WPARAM)m_byteQRCodeBuffer, m_nRcvBufLen);
			nReadTotalLen = 0;
		}

		if (m_bExitQRCodeReadThread)
		{
			break;
		}

		Sleep(200);
	}

	m_pQRReadThread = NULL;
}

BOOL CQRCodeRead::IsValidateChar(BYTE ch)
{
	if( ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
	{
		return TRUE;
	}

	if ('0' <= ch && ch <= '9')
	{
		return TRUE;
	}

	return FALSE;
}

void CQRCodeRead::OffsetSerialData()
{
	//20190912  扫码枪第一个字符为异常字符的处理  lijunqing
	//此处还有错误，异常考虑不周到
	long nOffset = 0;

	while (TRUE)
	{
		if (IsValidateChar(m_byteQRCodeBuffer[nOffset]) )
		{
			break;
		}

		nOffset++;
	}

	if (nOffset > 0)
	{
		nOffset = nOffset % 2;  //避免汉字作为关键字
		memcpy(m_byteQRCodeBuffer, m_byteQRCodeBuffer + nOffset, m_nRcvBufLen-nOffset);
		m_byteQRCodeBuffer[m_nRcvBufLen-nOffset] = 0;
		m_nRcvBufLen -= nOffset;
	}
}

void CQRCodeRead::WaiteInputQrCodeData()
{
	DWORD nReadLen = 0;
	DWORD nReadTotalLen = 0;

	while (TRUE)
	{
		if (m_bExitQRCodeReadThread)
		{
			break;
		}

		nReadTotalLen = m_nRcvBufLen;

		if (nReadTotalLen > 0)
		{
			//解析收到的二维码，发送消息
			if (m_nEncodeType == QRCODE_EncodeType_GBK)
			{
				m_byteQRCodeBuffer[m_nRcvBufLen] = 0;
				ConvertUtf8ToGBK(m_byteQRCodeBuffer);
				m_nRcvBufLen = strlen((char*)m_byteQRCodeBuffer);
				nReadTotalLen = m_nRcvBufLen;
			}
			else if (m_nEncodeType == QRCODE_EncodeType_ASCII)
			{
				m_byteQRCodeBuffer[m_nRcvBufLen] = 0;
				m_nRcvBufLen = UnicodeToChar((char*)m_byteQRCodeBuffer ,m_nRcvBufLen);
				nReadTotalLen = m_nRcvBufLen;
			}

			m_oXBarcodeStrParser.SetQRCodeString(ReadQRCodeBuffer(), m_nEncodeType);
			m_pMsgRcv->SendMessage(m_nMsgRcv,(WPARAM)m_byteQRCodeBuffer, m_nRcvBufLen);
			nReadTotalLen = 0;
		}

		if (m_bExitQRCodeReadThread)
		{
			break;
		}

		Sleep(200);
	}

	m_pQRReadThread = NULL;
}

UINT CQRCodeRead::ReadSerialDataThread(LPVOID pParam)
{
	CQRCodeRead *pQRCodeRead = (CQRCodeRead*)pParam;

#ifdef _use_CQRCodeReadDebugDlg
	pQRCodeRead->WaiteInputQrCodeData();
#else
	//2018-1-5
	if (!pQRCodeRead->m_bOpenSerialSucc)
	{
		pQRCodeRead->m_bInOpenSerial = TRUE;
		pQRCodeRead->InitQRCodeRead();
		pQRCodeRead->m_bInOpenSerial = FALSE;
	}

	if (pQRCodeRead->m_bOpenSerialSucc)
	{
		pQRCodeRead->ReadSerialData();
	}
	else
	{
		//如果没有关闭对话框，则显示信息
		if (!pQRCodeRead->m_bExitQRCodeReadThread)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("二维码扫描：打开串口COM %d失败"), pQRCodeRead->m_nPortNo);
		}
	}
#endif

	pQRCodeRead->CloseQRCodeRead();
	pQRCodeRead->m_pQRReadThread = NULL;

	return 1;
}


int CQRCodeRead::UnicodeToChar(char *UnicodeText, int UnicodeLength)
{
	wchar_t UnicodeWCH[100];
	int MultiLength = 0;
	int WideLength = 0;
	int SMLength = 0;

	while(MultiLength < UnicodeLength)
	{
		UnicodeWCH[WideLength++] = ((unsigned char )UnicodeText[MultiLength] << 8) 
			+ (unsigned char)UnicodeText[MultiLength+1];
		MultiLength += 2;
	}

	UnicodeWCH[WideLength] = 0;

	SMLength = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)UnicodeWCH, WideLength, 
		(LPSTR)UnicodeText, 161, NULL, NULL);

	return SMLength;
}
// 
// int CQRCodeRead::UnicodeToChar(char *UnicodeText, char *ASCText, int UnicodeLength)
// {
// 	wchar_t UnicodeWCH[100];
// 	int MultiLength = 0;
// 	int WideLength = 0;
// 	int SMLength = 0;
// 
// 	while(MultiLength < UnicodeLength)
// 	{
// 		UnicodeWCH[WideLength++] = ((unsigned char )UnicodeText[MultiLength] << 8) 
// 			+ (unsigned char)UnicodeText[MultiLength+1];
// 		MultiLength += 2;
// 	}
// 
// 	UnicodeWCH[WideLength] = 0;
// 
// 	SMLength = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)UnicodeWCH, WideLength, 
// 		(LPSTR)ASCText, 161, NULL, NULL);
// 
// 	return SMLength;
// }

void CQRCodeRead::ConvertUtf8ToGBK(BYTE *pszUtf8)
{
#ifdef UNICODE
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszUtf8, -1, NULL,0);
#else
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, NULL,0);
#endif

	wchar_t * wszGBK = new wchar_t[len];
	memset(wszGBK,0,len);

#ifdef UNICODE
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszUtf8, -1, wszGBK, len); 
#else
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, wszGBK, len); 
#endif

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	memset(pszUtf8, 0, len + 1);
	WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, (LPSTR)pszUtf8, len, NULL,NULL);

	delete[] wszGBK;
}


BOOL CQRCodeRead::ChangeSeparate(long nMapIndex)
{
	ChangeSeparate(m_strSeparateChar, m_strSeparateCharBk);
	ChangeSeparate(m_strSeparateEndChar, m_strSeparateEndCharBk);

	m_oXBarcodeStrParser.SetSeparateChar(m_strSeparateChar, m_strSeparateEndChar);

	return TRUE;
}

void CQRCodeRead::ChangeSeparate(CString &strSeparate, const CString &strValue)
{
	long nIndex=0;

	for (nIndex=0; nIndex<Separate_CHAR_MAP_MAX; nIndex++)
	{
		if (strValue == g_astrSeparateSrc[nIndex])
		{
			strSeparate = g_astrSeparateDest[nIndex];
			break;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////

CQRCodeReadXmlRWKeys* CQRCodeReadXmlRWKeys::g_pQRXmlKeys = NULL;
long CQRCodeReadXmlRWKeys::g_nQRXmlKeysRef = 0;

CString qr_GetEncodeTypeString(long nEncodeType)
{
	//m_nEncodeType = 0;为utf8编码   m_nEncodeType = 1;为GBK编码       m_nEncodeType = 2;为ASCII编码
// #define QRCODE_EncodeType_utf8     0
// #define QRCODE_EncodeType_GBK     1
// #define QRCODE_EncodeType_ASCII   2
// #define QRCODE_EncodeType_none    -1

	if (QRCODE_EncodeType_utf8 == nEncodeType)
	{
		return _T("utf8");
	}

	if (QRCODE_EncodeType_GBK == nEncodeType)
	{
		return _T("gbk");
	}

	if (QRCODE_EncodeType_ASCII == nEncodeType)
	{
		return _T("ascii");
	}

	return _T("ascii");
}

long qr_GetEncodeTypeID(const CString &strEncodeType)
{
	if (IsStringNumber(strEncodeType))
	{
		return CString_To_long(strEncodeType);
	}

	if (strEncodeType == _T("utf8"))
	{
		return QRCODE_EncodeType_utf8;
	}

	if (strEncodeType == _T("gbk"))
	{
		return QRCODE_EncodeType_GBK;
	}

	if (strEncodeType == _T("ascii"))
	{
		return QRCODE_EncodeType_ASCII;
	}

	return QRCODE_EncodeType_ASCII;
}

CQRCodeReadXmlRWKeys::CQRCodeReadXmlRWKeys()
{
	m_strSerialKey = L"ClockError";
	m_strValueKey = L"value";

	m_strPortNumberKey = L"port-number"; //port_number
	m_strBaudRateKey = L"baud-rate"; //baud-rate
	m_strParityKey = L"parity"; //parity
	m_strByteSizeKey = L"byte-size"; //byte-size
	m_strStopsbitKey = L"stop-bit"; //stop-bit

	m_strWriteLogKey = L"write_log";//WriteLog
	m_strEncodeTypeKey = L"encode_type";//EncodeType
	m_strSeparateCharKey = L"separate_char";//EncodeType
	m_strSeparateEndCharKey = L"separate_end_char";//EncodeType

	m_strQRCodeSepCharsKey = L"separate_chars"; //separate_chars
	m_strQRCodeSepEndCharsKey = L"separate_end_chars"; //separate_end_chars
	m_strChnHeadCharInvalidKey = L"chn-head-char-invalid";

	m_strQRCodeKey = L"qrcode-config";
}

CQRCodeReadXmlRWKeys::~CQRCodeReadXmlRWKeys()
{
}

CQRCodeReadXmlRWKeys* CQRCodeReadXmlRWKeys::Create()
{
	g_nQRXmlKeysRef++;

	if (g_nQRXmlKeysRef == 1)
	{
		g_pQRXmlKeys = new CQRCodeReadXmlRWKeys();
	}

	return g_pQRXmlKeys;
}

void CQRCodeReadXmlRWKeys::Release()
{
	g_nQRXmlKeysRef--;

	if (g_nQRXmlKeysRef == 0)
	{
		delete g_pQRXmlKeys;
		g_pQRXmlKeys = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//CQRCodeReadSepChar
CQRCodeReadSepChar::CQRCodeReadSepChar()
{

}

CQRCodeReadSepChar::~CQRCodeReadSepChar()
{

}

long CQRCodeReadSepChar::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys* pXmlKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	return 0;
}

long CQRCodeReadSepChar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys* pXmlKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);

	return 0;
}

//CQRCodeReadSepChars
CQRCodeReadSepChars::CQRCodeReadSepChars()
{

}

CQRCodeReadSepChars::~CQRCodeReadSepChars()
{

}

long CQRCodeReadSepChars::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys* pXmlKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSeparateCharKey, oElement, m_strID);

	return 0;
}

long CQRCodeReadSepChars::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys* pXmlKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSeparateCharKey, oElement, m_strID);

	return 0;
}

CExBaseObject* CQRCodeReadSepChars::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys *pQRKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	if (pQRKeys->CQRCodeSepCharKey() == strClassID)
	{
		return new CQRCodeReadSepChar();
	}

	return NULL;
}

void CQRCodeReadSepChars::AddSepChar(const CString &strSepChar)
{
	CQRCodeReadSepChar *pNew = new CQRCodeReadSepChar();
	pNew->m_strID = strSepChar;
	AddNewChild(pNew);
}

void CQRCodeReadSepChars::InitSepChars()
{
	if (m_strID.GetLength() > 0)
	{
		return;
	}

	CQRCodeReadSepChar *pSepChar = (CQRCodeReadSepChar*)GetHead();
	ASSERT (pSepChar != NULL);

	if (pSepChar == NULL)
	{
		return;
	}

	m_strID = pSepChar->m_strID;
}

//CQRCodeReadSepEndChars
CQRCodeReadSepEndChars::CQRCodeReadSepEndChars()
{
	
}

CQRCodeReadSepEndChars::~CQRCodeReadSepEndChars()
{

}

//CQRCodeReadConfigs
CQRCodeReadConfigs::CQRCodeReadConfigs()
{
	m_nBaud = 19200;
	m_nDatabits = 8;
	m_nStopsbits = 1;
	m_nParity = 0;
	m_nPortNo = 4;
	m_nEncodeType = QRCODE_EncodeType_none;
	m_nLogFile = 0;

	m_pQRCodeReadSepChars = NULL;
	m_pQRCodeReadSepEndChars = NULL;
}

CQRCodeReadConfigs::~CQRCodeReadConfigs()
{

}

long CQRCodeReadConfigs::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys* pXmlKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;
	CString strEncodeType;

	xml_GetElementText(pXmlKeys->m_strPortNumberKey, oElement, m_nPortNo);
	xml_GetElementText(pXmlKeys->m_strBaudRateKey, oElement, m_nBaud);
	xml_GetElementText(pXmlKeys->m_strParityKey, oElement, m_nParity);
	xml_GetElementText(pXmlKeys->m_strByteSizeKey, oElement, m_nDatabits);
	xml_GetElementText(pXmlKeys->m_strStopsbitKey, oElement, m_nStopsbits);
	xml_GetElementText(pXmlKeys->m_strWriteLogKey, oElement, m_nLogFile);
	xml_GetElementText(pXmlKeys->m_strEncodeTypeKey, oElement, strEncodeType);
	m_nEncodeType = qr_GetEncodeTypeID(strEncodeType);

	xml_GetElementText(pXmlKeys->m_strSeparateCharKey, oElement, m_strSeparateChar);
	xml_GetElementText(pXmlKeys->m_strSeparateEndCharKey, oElement, m_strSeparateEndChar);

	xml_GetElementText(pXmlKeys->m_strChnHeadCharInvalidKey, oElement, m_nChnHeadCharInvalid);
	return 0;
}

long CQRCodeReadConfigs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys* pXmlKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	xml_SetElementText(pXmlKeys->m_strPortNumberKey, oXMLDoc, oElement, m_nPortNo);
	xml_SetElementText(pXmlKeys->m_strBaudRateKey, oXMLDoc, oElement, m_nBaud);
	xml_SetElementText(pXmlKeys->m_strParityKey, oXMLDoc, oElement, m_nParity);
	xml_SetElementText(pXmlKeys->m_strByteSizeKey, oXMLDoc, oElement, m_nDatabits);
	xml_SetElementText(pXmlKeys->m_strStopsbitKey, oXMLDoc, oElement, m_nStopsbits);
	xml_SetElementText(pXmlKeys->m_strWriteLogKey, oXMLDoc, oElement, m_nLogFile);

	CString strEncodeType = qr_GetEncodeTypeString(m_nEncodeType);
	xml_SetElementText(pXmlKeys->m_strEncodeTypeKey, oXMLDoc, oElement, strEncodeType);

	//xml_SetElementText(pXmlKeys->m_strSeparateCharKey, oXMLDoc, oElement, m_strSeparateChar);
	//xml_SetElementText(pXmlKeys->m_strSeparateEndCharKey, oXMLDoc, oElement, m_strSeparateEndChar);
	xml_SetElementText(pXmlKeys->m_strChnHeadCharInvalidKey, oXMLDoc, oElement, m_nChnHeadCharInvalid);

	return 0;
}

CExBaseObject* CQRCodeReadConfigs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CQRCodeReadXmlRWKeys *pQRKeys = (CQRCodeReadXmlRWKeys*)pXmlRWKeys;

	if (pQRKeys->CQRCodeSepCharsKey() == strClassID)
	{
		m_pQRCodeReadSepChars = new CQRCodeReadSepChars();
		return m_pQRCodeReadSepChars;
	}

	if (pQRKeys->CQRCodeSepEndCharsKey() == strClassID)
	{
		m_pQRCodeReadSepEndChars = new CQRCodeReadSepEndChars();
		return m_pQRCodeReadSepEndChars;
	} 

	return NULL;
}

void CQRCodeReadConfigs::InitAfterRead()
{
	if (m_pQRCodeReadSepChars == NULL)
	{
		m_pQRCodeReadSepChars = new CQRCodeReadSepChars();
		AddNewChild(m_pQRCodeReadSepChars);
		m_pQRCodeReadSepChars->m_strID = _T("：");
		m_pQRCodeReadSepChars->AddSepChar(m_pQRCodeReadSepChars->m_strID);
	}

	if (m_pQRCodeReadSepEndChars == NULL)
	{
		m_pQRCodeReadSepEndChars = new CQRCodeReadSepEndChars();
		AddNewChild(m_pQRCodeReadSepEndChars);
		m_pQRCodeReadSepEndChars->m_strID = _T("，");
		m_pQRCodeReadSepEndChars->AddSepChar(m_pQRCodeReadSepEndChars->m_strID);
	}

	m_pQRCodeReadSepChars->InitSepChars();
	m_pQRCodeReadSepEndChars->InitSepChars();

	if (m_strSeparateChar.GetLength() == 0)
	{
		m_strSeparateChar = m_pQRCodeReadSepChars->m_strID;
	}

	if (m_strSeparateEndChar.GetLength() == 0)
	{
		m_strSeparateEndChar = m_pQRCodeReadSepEndChars->m_strID;
	}
}

CString CQRCodeReadConfigs::GetCfgFile()
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += _T("QRCodeReadConfig.xml");

	return strPath;
}

BOOL CQRCodeReadConfigs::OpenCfgFile()
{
	CString strPath = GetCfgFile();
	BOOL bRet = OpenXmlFile(strPath,CQRCodeReadXmlRWKeys::g_pQRXmlKeys);

	return bRet;
}

BOOL CQRCodeReadConfigs::SaveCfgFile()
{
	CString strPath = GetCfgFile();
	return SaveXmlFile(strPath,CQRCodeReadXmlRWKeys::g_pQRXmlKeys);
}

void CQRCodeReadConfigs::In_ValidateSepChars(const CString &strQRCode)
{
	long nSepBeginPos = -1, nSepCount = 0;
	long nSepEndBeginPos = -1, nSepEndCount = 0;

	In_ValidateSepChars(strQRCode, m_strSeparateChar, nSepBeginPos, nSepCount);
	In_ValidateSepChars(strQRCode, m_strSeparateEndChar, nSepEndBeginPos, nSepEndCount);
	BOOL bChange1 = FALSE, bChange2 = FALSE;

	if (nSepBeginPos <= 0 && nSepCount <= 0)
	{
		In_ValidateSepChars(strQRCode, m_strSeparateChar, m_pQRCodeReadSepChars, nSepBeginPos, nSepCount);
		bChange1 = (nSepBeginPos > 0);
	}

	if (nSepEndBeginPos <= 0 && nSepEndCount <= 0)
	{
		In_ValidateSepChars(strQRCode, m_strSeparateEndChar, m_pQRCodeReadSepEndChars, nSepEndBeginPos, nSepEndCount);
		bChange2 = (nSepEndBeginPos > 0);
	}

	if (bChange1 || bChange2)
	{
		SaveCfgFile();
	}
}

void CQRCodeReadConfigs::In_ValidateSepChars(const CString &strQRCode, const CString &strSepChar, long &nBeginPos, long &nCount)
{
	long nPos = strQRCode.Find(strSepChar, 0);

	if (nPos <= 0)
	{
		return;
	}

	nBeginPos = nPos;

	while (TRUE)
	{
		nCount++;
		nPos = strQRCode.Find(strSepChar, nPos+1);

		if (nPos < 0)
		{
			break;
		}
	}
}

void CQRCodeReadConfigs::In_ValidateSepChars(const CString &strQRCode, CString &strSepChar, CExBaseList *pListSepChars, long &nBeginPos, long &nCount)
{
	POS pos = pListSepChars->GetHeadPosition();
	CQRCodeReadSepChar *pSepChar = NULL;
	nBeginPos = -1;
	nCount = 0;

	while (pos != NULL)
	{
		pSepChar = (CQRCodeReadSepChar *)pListSepChars->GetNext(pos);
		In_ValidateSepChars(strQRCode, pSepChar->m_strID, nBeginPos, nCount);

		if (nBeginPos > 0 && nCount > 0)
		{
			strSepChar = pSepChar->m_strID;
			pListSepChars->m_strID = strSepChar;
			break;
		}
	}
}

typedef int (__cdecl *P_write_qrcode_file) (const char* strText, const char *strPngFile);

BOOL QR_WriteQRCodePngFile(const char *pszQRData, const char *pszPngFile)
{
	CString strDll;
	strDll = _P_GetBinPath();
	strDll += _T("WriteQRCodeFile.dll");
	BOOL bSucc = TRUE;
	HINSTANCE hMacroUILib = LoadLibrary(strDll);

	if (hMacroUILib == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DLL file [%s] not exist"), strDll);
		return FALSE;
	}

	BOOL bRet = TRUE;
	P_write_qrcode_file pFunc = NULL;
	pFunc = (P_write_qrcode_file)GetProcAddress(hMacroUILib, "write_qrcode_file");

	if (pFunc == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" [%s]  function write_qrcode_file not exist 函数入口没找到"), strDll);
		bRet = FALSE;
	}
	else
	{
		pFunc(pszQRData, pszPngFile);
	}

	FreeLibrary(hMacroUILib);

	return bRet;
}

