#include "stdafx.h"
#include "BlueDataPross.h"

CBlueDataPross::CBlueDataPross(void)
{
}

CBlueDataPross::~CBlueDataPross(void)
{
}

void CBlueDataPross::OpenBlueToothServer()
{
	StartBlueTooth_Thread();
	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("������״̬�������Ѵ�"));
}

void CBlueDataPross::CloseBlueToothServer()
{
	CloseSocket(BT_STATE_CLOSE);
	CLogPrint::LogString(XLOGLEVEL_ERROR, _T("������״̬�������ѹر�"));
}

//�����������յ�������
void CBlueDataPross::HandleClientCommand(BYTE *strCmmd)
{
	int nAllLen = CalcTotalLen(strCmmd);
 	int nDataLen = CalDataLen(strCmmd);
 
 	if (CalCRC(strCmmd,nAllLen))
 	{
 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("�ͻ�������<%s>У��������飡"),strCmmd);
 		return;
 	}

	BYTE bCmmd = strCmmd[7];
	switch(bCmmd)
	{
	case 0x81://�ƶ��ն��������������ͻ�ȡ����װ��ģ���ļ���ָ��
		ProssRecv0x81Data(strCmmd, nDataLen);
		break;
	case 0x85://�ƶ��ն�ÿ�յ�һ֡�ļ��������ݺ���������������һ��ȷ��ָ��
		ProssRecv0x85Data(strCmmd, nDataLen);
		break;
	case 0x87://�ƶ��ն��������������Ϳ�ʼ���Ե�ָ��
		ProssRecv0x87Data(strCmmd, nDataLen);
		break;
	case 0x90://�ƶ��ն˽����ϴ��ļ����Ƶ�ָ��
		ProssRecv0x90Data(strCmmd, nDataLen);
		break;
	case 0x91://Э����δ����
		ProssRecv0x91Data(strCmmd, nDataLen);
		break;
	case 0x92://�ƶ��ն��������������Ϳ������������ָ��
		ProssRecv0x92Data(strCmmd, nDataLen);
		break;
	case 0x94://�ƶ��ն�������������ȡ���Ա������Ƶ�ָ��
		ProssRecv0x94Data(strCmmd, nDataLen);
		break;
	case 0x97://�ƶ��ն�ÿ�յ�һ֡�ļ��������ݺ���������������һ��ȷ��ָ��
		ProssRecv0x97Data(strCmmd, nDataLen);
		break;
	case 0x98://�ƶ��ն�������������ȡ���Ը������Ƶ�ָ��
		ProssRecv0x98Data(strCmmd, nDataLen);
		break;
	}
}
void CBlueDataPross::ProssRecv0x81Data(BYTE *strCmmd, int nDataLen)
{
	int nData = strCmmd[13] & 0xFF - 48;
	m_strFileListName = _T("");
	POS pos = m_oTemplateMap.GetHeadPosition();
	while(pos)
	{
		CDataGroup *pObj =  (CDataGroup*)m_oTemplateMap.GetNext(pos);
		if (pObj != NULL)
		{
			m_strFileListName += pObj->m_strName + _T(":");
		}
	}
	if (m_strFileListName != _T(""))
	{
		m_strFileListName = m_strFileListName.Left(m_strFileListName.GetLength()-1);
	}
	char *pchSendMsg = NULL;
	long nSize = CString_to_char(m_strFileListName,&pchSendMsg);

	char *pszUtf8 = NULL;
	long nDestLen = 0;
	charGBK_to_charUtf8(pchSendMsg, nSize,&pszUtf8,nDestLen);

	SendMsg(pszUtf8,0x82,nDestLen);
	delete []pchSendMsg;
	delete []pszUtf8;
	CLogPrint::LogString(XLOGLEVEL_INFOR, _T("�ļ��б��ѷ���"));
}
void CBlueDataPross::ProssRecv0x85Data(BYTE *strCmmd, int nDataLen)
{
	int n = (strCmmd[13] & 0xFF - 48);
	if (n == 1)
	{
		if (m_oFile.m_hFile == INVALID_HANDLE_VALUE)
		{
			BOOL bRet = m_oFile.Open(m_strSendFile, CFile::modeRead | CFile::shareDenyWrite);
		}

		m_oFile.Seek(m_lSeekPos,CFile::begin);

		char byteFileContext[BT_TEXT_LEN] = {0};
		long nReadLeng = 0;
		nReadLeng = m_oFile.Read(byteFileContext,BT_TEXT_LEN);

		if (nReadLeng > 0)
		{
// 				char cFileName[BT_TEXT_LEN + 1] = {0};
// 				ValueToHex((BYTE*)byteFileContext,BT_TEXT_LEN,cFileName,FALSE,FALSE);
// 				CString str(cFileName);
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"%s\n",str);

			long nSendLen = SendMsg(byteFileContext,0x84,nReadLeng);
			Sleep(50);
			if (nSendLen > 0)
			{
				long nLen = nReadLeng + m_lSeekPos;
				m_lSeekPos += nSendLen - (BT_EX_LEN);
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�ļ��ѷ���%d�ֽ�"),nLen);
			}
			else
			{
				m_oFile.Close();
				return;
			}
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("�ļ�") + m_strSendFile + _T("���ͳɹ���"));
			SendMsg(_T(""),0x84,0);

			m_lSeekPos = 0;

			if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
			{
				m_oFile.Close();
			}
		}
	}
	else
	{
		if (m_oFile.m_hFile != INVALID_HANDLE_VALUE)
		{
			m_oFile.Close();
		}
	}
}
void CBlueDataPross::ProssRecv0x87Data(BYTE *strCmmd, int nDataLen)
{
	char cText[BT_FILE_NAME_MAX] = {0};
	int i = 0;
	for (i = 0; i < nDataLen; i++)
	{
		cText[i] = strCmmd[13 + i];
	}
	char *pchMsg;
	long lDataLen = 0;
	charUtf8_to_charGBK(cText,nDataLen,&pchMsg,lDataLen);

	CString strText = (CString)pchMsg;
//	CLogPrint::LogString(XLOGLEVEL_TRACE, strText);
// 	CString strTemplateName;
// 	strTemplateName = _T("110kV����118���PCS-943��·����װ�õ���");

	AfxGetApp()->PostThreadMessage(WM_SMARTTEST_CREAT,0,(LPARAM)(LPCTSTR)strText);
}
void CBlueDataPross::ProssRecv0x90Data(BYTE *strCmmd, int nDataLen)
{
	int nData = strCmmd[13] & 0xFF - 48;
	if (nData == 1)//�����ļ����ɹ�
	{
		m_lSeekPos = 0;

		CLogPrint::LogString(XLOGLEVEL_TRACE, m_strSendFile);
		BOOL bRet = m_oFile.Open(m_strSendFile, CFile::modeRead | CFile::shareDenyWrite);
		if (bRet == FALSE)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�ļ���ʧ��"));
			return;
		}
		m_nFileLength = m_oFile.GetLength();

		if(m_nFileLength == 0)
		{
			m_oFile.Close();
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�ļ�Ϊ��,����ʧ��"));
			return;
		}

		char cFileContext[BT_TEXT_LEN + 1]={0};
		m_oFile.SeekToBegin();
		long nReadLeng = 0;
		nReadLeng = m_oFile.Read(cFileContext,BT_TEXT_LEN);
		if (nReadLeng > 0)
		{
// 				char cFileName[BT_TEXT_LEN + 1] = {0};
// 				ValueToHex((BYTE*)cFileContext,BT_TEXT_LEN,cFileName,FALSE,FALSE);
// 				CString str(cFileName);
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"%s\n",str);

			long nSendLen = SendMsg(cFileContext,0x84,nReadLeng);
			Sleep(50);
			if (nSendLen > 0)
			{
				m_lSeekPos = nSendLen - (BT_EX_LEN);
				CLogPrint::LogString(XLOGLEVEL_TRACE, m_strSendFile + _T("���ڷ���"));
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�ļ��ѷ���%d�ֽ�"),m_lSeekPos);
			}
			else
			{
				m_oFile.Close();
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�������,����ʧ��"));
				return;
			}
		}
	}
	else
	{
		return;
	}
}
void CBlueDataPross::ProssRecv0x91Data(BYTE *strCmmd, int nDataLen)
{
	CString strFileName = m_strSendFile.Right(m_strSendFile.GetLength() - m_strSendFile.ReverseFind('\\')-1);
	SendMsg(strFileName,0x83,1);
	CLogPrint::LogString(XLOGLEVEL_TRACE,_T("�ļ���") + strFileName + _T("�ѷ���"));
}
void CBlueDataPross::ProssRecv0x92Data(BYTE *strCmmd, int nDataLen)
{
}
void CBlueDataPross::ProssRecv0x94Data(BYTE *strCmmd, int nDataLen)
{
}
void CBlueDataPross::ProssRecv0x97Data(BYTE *strCmmd, int nDataLen)
{
}
void CBlueDataPross::ProssRecv0x98Data(BYTE *strCmmd, int nDataLen)
{
}