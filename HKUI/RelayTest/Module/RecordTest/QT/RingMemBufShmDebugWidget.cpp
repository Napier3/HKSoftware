#include "RingMemBufShmDebugWidget.h"
#include "ui_RingMemBufShmDebugWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/SmartCap/XSttCap_61850.h"

#include <QMessageBox>
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
//#include "../../Module/UI/SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


QRingMemBufShmDebugWidget::QRingMemBufShmDebugWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRingMemBufShmDebugWidget)
{
    ui->setupUi(this);
	InitLanguage();
	Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint;
	
	this->setWindowFlags(flags);

// 	connect(ui->m_Btn_WriteDetectPkg,SIGNAL(clicked()),this,SLOT(on_m_Btn_WriteDetectPkg_clicked()));
// 	connect(ui->m_Btn_WriteRcvPkg,SIGNAL(clicked()),this,SLOT(on_m_Btn_WriteRcvPkg_clicked()));

	m_bOpenCapFile = FALSE;
	m_nSendBufSize = MAX_CAP_SEND_BUFFER;
	m_nSendBufSizeTotal = 0;

	//2022-6-11  李俊庆  为方便调试，从文件中读取抓包文件
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += "at02d_debug.txt";
	CFile oFile;
	CString strFileName;
	strFileName = "120000.at02d";
	
	if (oFile.Open(strFile, CFile::modeRead))
	{
		char pszBufferRead[255];
		memset(pszBufferRead, 255, 0);
		long nLen = oFile.GetLength();
		
		if (oFile.Read(pszBufferRead, nLen) > 0)
		{
			pszBufferRead[nLen] = 0;
			strFileName = pszBufferRead;
		}

		oFile.Close();
	}

	ui->m_edtFileName->setText(strFileName);
	ui->m_edtSendLength->setText(QString::number(m_nSendBufSize, 10));
	ui->m_edtSendLengthTotal->setText(QString::number(m_nSendBufSizeTotal, 10));

	connect(&m_oTimerWrite,   SIGNAL(timeout()),    this,   SLOT(slot_Timer_AutoWrite()));
	m_nAutoWritePkg = 0;
	m_nLeftBufferLen = 0;
	m_nSendLength = 0;

	SetRingMemBufShmFont();
}

QRingMemBufShmDebugWidget::~QRingMemBufShmDebugWidget()
{
    delete ui;
}

void QRingMemBufShmDebugWidget::SetRingMemBufShmFont()
{
	ui->m_btnAutoWrite->setFont(*g_pSttGlobalFont);
	ui->m_Btn_WriteRcvPkg->setFont(*g_pSttGlobalFont);
	ui->m_Btn_WriteDetectPkg->setFont(*g_pSttGlobalFont);
	ui->m_edtSendLengthTotal->setFont(*g_pSttGlobalFont);
	ui->m_lblSendLength->setFont(*g_pSttGlobalFont);
	ui->m_edtSendLength->setFont(*g_pSttGlobalFont);
	ui->m_edtFileName->setFont(*g_pSttGlobalFont);
	ui->m_lblFileName->setFont(*g_pSttGlobalFont);
	ui->m_lblSendLength_2->setFont(*g_pSttGlobalFont);
}

void QRingMemBufShmDebugWidget::on_m_Btn_WriteDetectPkg_clicked()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += "DetectTest.xml";
	CSttParas oSttParas;

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = oSttParas.OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	
	if (!bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, strFile + " not exist!");
		return;
	}

	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	pNative->m_oSttAtsClient.OnRtData(&oSttParas);
}

void QRingMemBufShmDebugWidget::GetSendLength()
{
	CString strText = ui->m_edtSendLength->text();
	m_nSendBufSize = strText.toLong();

	if (1024 > m_nSendBufSize)
	{
		m_nSendBufSize = 1024;
		ui->m_edtSendLength->setText(QString::number(m_nSendBufSize, 10));
	}
	else if (m_nSendBufSize > MAX_CAP_SEND_BUFFER)
	{
		m_nSendBufSize = MAX_CAP_SEND_BUFFER;
		ui->m_edtSendLength->setText(QString::number(m_nSendBufSize, 10));
	}
}

#include "../RingMemBuf.h"
extern CSttRcdBufferRcvMsg *g_pSttRcdSndRingBuf;

void QRingMemBufShmDebugWidget::on_m_Btn_WriteRcvPkg_clicked()
{
	if (!m_bOpenCapFile)
	{
		CString strFile;
		strFile = _P_GetLibraryPath();
		strFile += ui->m_edtFileName->text();
		m_bOpenCapFile = m_oCapFile.Open(strFile, CFile::modeRead);

		if (!m_bOpenCapFile)
		{
			CXMessageBox::information(this, "", /*"打开文件失败"*/g_sLangTxt_Gradient_OpenfileFail.GetString()); //lcq
			return;
		}

		m_nSendBufSizeTotal = 0;
		ui->m_edtSendLengthTotal->setText(QString::number(m_nSendBufSizeTotal, 10));
	}

	GetSendLength();
	long nLen = m_oCapFile.Read(m_pBuffer, m_nSendBufSize);

	if (nLen == 0)
	{
		if (m_nAutoWritePkg)
		{
			m_oTimerWrite.stop();
		}

		m_bOpenCapFile = false;
		m_oCapFile.Close();
		CXMessageBox::information(this, "",/* "发送完成"*/g_sLangTxt_Gradient_SendComplete.GetString()); //lcq
		return ;
	}

	//CXSttCap_61850 *pSttCap61850 = g_theXSmartCapMngr->GetSttCap_61850();
	//pSttCap61850->OnRcdBufRcv(m_pBuffer, nLen);
	DebugWriteRcvPkg(m_pBuffer, nLen);

	m_nSendBufSizeTotal += nLen;
	ui->m_edtSendLengthTotal->setText(QString::number(m_nSendBufSizeTotal, 10));

}

void QRingMemBufShmDebugWidget::DebugWriteRcvPkgHead(BYTE *pBuffer, long nLen)
{

	if (m_nLeftBufferLen > 0)
	{
		memcpy(m_pBufferHead, m_pBufferLeft, m_nLeftBufferLen);
	}

	memcpy(m_pBufferHead + m_nLeftBufferLen, m_pBuffer, nLen);
	m_nSendLength = 0;

	SST_AT02_PKT_HEAD oHead ;
	long nLenLeft = nLen + m_nLeftBufferLen;
	EPBUFFERPOS oBuffPos;
	memset(&oBuffPos, 0, sizeof(EPBUFFERPOS));

	oBuffPos.pBuffer = m_pBufferHead;
	oBuffPos.nIndex = 0;
	oBuffPos.nPrevIndex = 0;
	oBuffPos.nBufLength = nLenLeft;
	nLenLeft = Ep_BufferLeave(&oBuffPos);
	long nPrevIndex = 0;
	DWORD dwHeadFrm = 0;
	long nPkgLen = 0;
	long nErrorCount = 0;

	while (nLenLeft > 0)
	{
		if (nLenLeft > sizeof(SST_AT02_PKT_HEAD))
		{
			nPrevIndex = oBuffPos.nIndex;
			dwHeadFrm = Ep_BufferGetDWord2(&oBuffPos);

			while(dwHeadFrm != STT_AT02_FIXED_HEAD)
			{
				Ep_OffsetBufferCurr(&oBuffPos,1);
				nLenLeft = Ep_BufferLeave(&oBuffPos);

				if (nLenLeft<STT_AT02_FIXED_HEAD_LEN)
				{
					memcpy(m_pBufferLeft, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
					m_nLeftBufferLen = nLenLeft;
					break;
				}

				dwHeadFrm = Ep_BufferGetDWord2(&oBuffPos);
			}
		}

		nPrevIndex = oBuffPos.nIndex;

		if (nLenLeft < sizeof(SST_AT02_PKT_HEAD))
		{
			oBuffPos.nIndex = nPrevIndex;
			nLenLeft = Ep_BufferLeave(&oBuffPos);
			memcpy(m_pBufferLeft, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
			m_nLeftBufferLen = nLenLeft;
			break;
		}

		memcpy(m_pBufferHeadSend + m_nSendLength, Ep_GetBufferCurr(&oBuffPos), sizeof(SST_AT02_PKT_HEAD));
		m_nSendLength += sizeof(SST_AT02_PKT_HEAD);
		xsmartcap_ReadHead(&oBuffPos, oHead);

		if (oHead.len <= 0 || oHead.len >= 1024)
		{//异常的长度
			oBuffPos.nIndex = nPrevIndex;
			Ep_OffsetBufferCurr(&oBuffPos,1);
			nLenLeft = Ep_BufferLeave(&oBuffPos);
			continue;
		}

		nLenLeft = Ep_BufferLeave(&oBuffPos);
		nPkgLen = oHead.len*4 - sizeof(SST_AT02_PKT_HEAD) + 4;

		if (nLenLeft < nPkgLen)
		{//报文长度不够，则结束，
			m_nLeftBufferLen = 0;
			break;
		}
		else
		{
			Ep_OffsetBufferCurr(&oBuffPos, nPkgLen);
			nLenLeft = Ep_BufferLeave(&oBuffPos);		//完整帧之后的剩余长度
		}

		//剩余帧长度不满一帧头拷贝到m_pBufferLeft
		if (nLenLeft < sizeof(SST_AT02_PKT_HEAD))
		{
			memcpy(m_pBufferLeft, Ep_GetBufferCurr(&oBuffPos), nLenLeft);
			m_nLeftBufferLen = nLenLeft;
			break;
		}
	}

	if (m_nSendLength > 0)
	{
		g_pSttRcdSndRingBuf->OnRcdBufRcv(m_pBufferHeadSend, m_nSendLength);
	}
}

void QRingMemBufShmDebugWidget::DebugWriteRcvPkg(BYTE *pBuffer, long nLen)
{
	if (CXCapPkgBufferMngrInterface::Is_XSmartCapDebugHead())
	{
		DebugWriteRcvPkgHead(pBuffer, nLen);
	}
	else
	{
		g_pSttRcdSndRingBuf->OnRcdBufRcv(m_pBuffer, nLen);
	}
}

void QRingMemBufShmDebugWidget::on_m_btnAutoWrite_clicked()
{
	m_nAutoWritePkg = 1;
	m_oTimerWrite.start(100);
}

void QRingMemBufShmDebugWidget::slot_Timer_AutoWrite()
{
	on_m_Btn_WriteRcvPkg_clicked();
}

void QRingMemBufShmDebugWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_lblFileName,g_sLangTxt_Native_FileName,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblSendLength,g_sLangTxt_IEC_SendLength,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblSendLength_2,g_sLangTxt_IEC_SendLength_2,XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_Btn_WriteDetectPkg,g_sLangTxt_IEC_WriteDetectPkg,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_WriteRcvPkg,g_sLangTxt_IEC_WriteRcvPkg,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnAutoWrite,g_sLangTxt_IEC_AutoWrite,XLang_Ctrls_QPushButton);
}
