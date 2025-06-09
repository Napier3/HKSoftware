#include "stdafx.h"
#include "SimpacTestAscii2.h"

CSimpacTestAscii2::CSimpacTestAscii2()
{
	m_nIsConnectSuccess = 0;
	m_fRunTime = 0;
	m_fAbsErr = 0;
	m_bReadMeas = FALSE;
	//yzj 2021-09-24 ���ݿ��в���address�ֶ�,��д��01
	m_strAddress = _T("01");
	m_bIsXTimerRunning = FALSE;
}

CSimpacTestAscii2::~CSimpacTestAscii2( void )
{

}

int CSimpacTestAscii2::open_socket( char *ipaddr, unsigned short port, SOCKET *sock )
{
	if (m_nIsConnectSuccess > 0)
	{
		return 1;
	}

	struct sockaddr_in saddr; /* remote socket address */

	/* init socket address structure */
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ipaddr);

	/* create socket */
	*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (*sock == INVALID_SOCKET)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("Socket����ʧ��"));
		return (0);
	}
	else
	{
		/* Connect to host */
		if (connect(*sock, (struct sockaddr *)&saddr, sizeof(SOCKADDR)))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�޷���������---IP=%S---Port=%d"), ipaddr, port);
			return (0);
		}

		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("���ӳɹ�"));
		return 1;
	}
}

int CSimpacTestAscii2::send_command( SOCKET so, char *cmd )
{
	if (m_nIsConnectSuccess <= 0)
	{
		return 0;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����%s"), cmd);

	int len, numsent;
	len = strlen(cmd);
	numsent = send (so, cmd, len, 0);

	if (numsent != len)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("����ʧ��"));
		return 0;
	}
	else
	{
		return 1;
	}
}

//����ֵ����0����ʾ����ִ�гɹ�������ִ��ʧ��
int CSimpacTestAscii2::receive_answer( SOCKET so )
{
	char RecString[1000];	 /* receive buffer */
	int numrec;				/* number of received characters */ 
	numrec = recv(so, RecString, 1000, 0);
	m_strRespond = _T("");

	switch (numrec)
	{
	case -1:
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("����ʧ��"));
		break;
	case  0:
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("���������ѹر�"));
		break;

	default:
		{
			RecString[numrec] = 0;		/* terminate string */
			m_strRespond = RecString;

			if (m_bReadMeas)
			{
				//���ظ�ʽ 0010.0 0015.0 0020.0 0025.0 ...(�¶��趨ֵ �¶�ʵ��ֵ ʪ���趨ֵ ʪ��ʵ��ֵ)
				//float fTemperature, fHumidity;
				//sscanf(RecString, "%f %f %f %f %f", &fTemperature, &m_fTemperature_Read, &fHumidity, &m_fHumidity_Read);
				
				//yzj 2021-9-24 ��ʱ��ô����
				CString strTemp = RecString;
				strTemp = strTemp.Mid(strTemp.Find(' ') + 1);
				CString strTemperature_Read = strTemp.Mid(0, strTemp.Find(' '));
				strTemp = strTemp.Mid(strTemp.Find(' ') + 1);
				strTemp = strTemp.Mid(strTemp.Find(' ') + 1);
				CString strHumidity_Read = strTemp.Mid(0, strTemp.Find(' '));
				m_fTemperature_Read = (float)CString_To_double(strTemperature_Read);
				m_fHumidity_Read = (float)CString_To_double(strHumidity_Read);
			}
		}	
	}

	return numrec;
}

char * CSimpacTestAscii2::CheckSum( char *buffer )
{
	const char ASCII[] = _T("0123456789ABCDEF");

	static char Hex[10];
	static int nA1,nA2;
	unsigned int i;
	int nSum;
	int nLen = strlen(buffer);

	nSum = 256;
	for (i = 0; i<nLen; i++)
	{
		nSum -= buffer[i];

		if (nSum < 0)
		{
			nSum += 256;
		}
	}

	nA1 = (nSum & 0xF0)>>4;
	nA2 = nSum & 0x0F;
	Hex[0] = ASCII[nA1];
	Hex[1] = ASCII[nA2];
	Hex[2] = 0;

	return (Hex);
}

int CSimpacTestAscii2::SendASCII_OneCommand(CString strCommand)
{
	if (m_nIsConnectSuccess <= 0)
	{
		return 0;
	}

	char Command[100];

	if (WSAStartup(0x101,&m_wsaData))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("WinSock��ʼ��ʧ��"));
		return(-1);
	}

	sprintf(Command,"%c1?8E%c",STX,ETX);
	send_command(m_hSocket,Command);

	Sleep(10);
	
	return receive_answer(m_hSocket);
}

int CSimpacTestAscii2::SendASCII_TwoCommand(CString strCommand)
{
	if (m_nIsConnectSuccess <= 0)
	{
		return 0;
	}
	char Command[100];

 	if (WSAStartup(0x101,&m_wsaData))
 	{
 		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("WinSock��ʼ��ʧ��"));
 		return(-1);
 	}
	CString_to_char(strCommand,Command);
	send_command(m_hSocket, Command);

	Sleep(10);

	return receive_answer(m_hSocket);
}
//$01I<CR>  //��ȡʵ��ֵ
CString CSimpacTestAscii2::Cmd_ReadMeas()    
{
	CString strPrompt;
	strPrompt = _T("I");
	return strPrompt;
}

CString CSimpacTestAscii2::float_format(float fVal)
{//0040.0

	//yzj 2021-9-24 ���븺���ж�
	BOOL bIsNegative = FALSE;
	if (fVal < 0)
	{
		fVal = abs(fVal);
		bIsNegative = TRUE;
	}

	CString strValue;
	strValue.Format(_T("%.1f"), fVal);
	long nLen = strValue.GetLength();
	int i = 0;

	if (nLen >= 6)
	{
		return strValue;
	}

	nLen = 6 - nLen;

	for (i=0; i<nLen; i++)
	{
		strValue.Insert(0, '0');
	}

	if(bIsNegative)
	{
		strValue = _T("-") + strValue;
	}

	return strValue;
}

//$01E 0010.0 0012.0 0100.0 0000.0 01000000000000000000000000000000
//�����¿���Ŀ���¶ȡ�ʪ�ȣ��ﵽĿ��ֵ֮�󣬳�ʱ�䱣��
//ǰ�������ֱ���ʪ��  ����λ���Ʒ�������,Ϊ�̶�ֵ   0100...�еڶ�λ��1�ǿ��ƿ���
CString CSimpacTestAscii2::Cmd_Run()
{
	CString strPrompt;

	strPrompt = _T("E ")
		+ float_format(m_fTemperature) + _T(" ")
		+ float_format(m_fHumidity) + _T(" 0100.0 0000.0 01000000000000000000000000000000");

// 	strHeat = parserFaultPara(&m_oEquation,m_pMacro->GetFaultParas(),_T("NominalValueTemperature"));
// 	strHum = parserFaultPara(&m_oEquation,m_pMacro->GetFaultParas(),_T("NominalValueHumidity"));
// 	strPrompt = _T("E ") + strHeat + _T(" ") + strHum + _T(" 0100.0 0000.0 01000000000000000000000000000000");

	return strPrompt;
}

//$01E ####.# ####.# 0000.0 0000.0 00000000000000000000000000000000    ֹͣ����
//���õ��¶ȡ�ʪ�ȣ���������
CString CSimpacTestAscii2::Cmd_Stop()
{
	CString strPrompt;

	strPrompt = _T("E ")
		+ float_format(m_fTemperature) + _T(" ")
		+ float_format(m_fHumidity) + _T(" 0000.0 0000.0 00000000000000000000000000000000");

// 	CString strHeat,strHum;
// 
// 	strHeat = parserFaultPara(&m_oEquation,m_pMacro->GetFaultParas(),_T("NominalValueTemperature"));
// 	strHum = parserFaultPara(&m_oEquation,m_pMacro->GetFaultParas(),_T("NominalValueHumidity"));
// 	strPrompt = _T("E ") + strHeat + _T(" ") + strHum + _T(" 0000.0 0000.0 00000000000000000000000000000000");

	return strPrompt;
}
//$01P 0000<CR>�����Եڼ����Ѵ�� <����> ����  0000����ֹͣ <����> ���� 
//�����<����>��ʾͨ���������õ�һЩ�������� ��40������1Сʱ֮����80������5Сʱ,��Ԥ���ڻ��������ú�
CString CSimpacTestAscii2::StartingProgram()
{
	CString strPrompt;
	strPrompt.Format(_T("P %d"), m_nProgramNumber);
// 	CString strNumber;
// 	strNumber = parserFaultPara(&m_oEquation,m_pMacro->GetFaultParas(),_T("ProgramNumber"));
// 	strPrompt = _T("P ") + strNumber;
	return strPrompt;
}
//$01F<CR>  ��ȡ������Ϣ
CString CSimpacTestAscii2::ReadingError()
{
	CString strPrompt;
	strPrompt = _T("F");
	return strPrompt;
}
//$01Q<CR>  ȷ�����д���
CString CSimpacTestAscii2::AcknowledgeError()
{
	CString strPrompt;
	strPrompt = _T("Q");
	return strPrompt;
}
//���Ӧ���Ƕ��಻��Ҫ��,�Ͷ�ȡ������Ϣ�ظ�
//CString CSimpacTestAscii2::DescriptionRate()
//{
//	CString strPrompt;
//	strPrompt = _T("F");
//	return strPrompt;
//}

BOOL CSimpacTestAscii2::Connect()
{
// 	//������  
// 	m_nIsConnectSuccess = TRUE;
// 	return m_nIsConnectSuccess;

	if (m_nIsConnectSuccess > 0)
	{
		return m_nIsConnectSuccess;
	}

	char pszIp[32];
	CString_to_char(m_strIP, pszIp);

	if(!open_socket(pszIp,m_nPort,&m_hSocket))
	{
		m_nIsConnectSuccess = 0;
	}
	else
	{
		m_nIsConnectSuccess = 1;
	}

	return m_nIsConnectSuccess;
}

BOOL CSimpacTestAscii2::DisConnect()
{
	if (m_nIsConnectSuccess <= 0)
	{
		return m_nIsConnectSuccess;
	}

	shutdown(m_hSocket, SD_BOTH);

	if ( closesocket( m_hSocket ) == SOCKET_ERROR )
	{
		
	}

	m_hSocket = NULL;
	m_nIsConnectSuccess = 0;

	return m_nIsConnectSuccess;
}


//[$]              [01]             [cmd]            [\r]
//��ʼ�ַ�  ���ߵ�ַ  ��������    ���з���
LONG CSimpacTestAscii2::Test( const CString &strMacroID)
{
	//�����StopTest����ֱ�ӷ��ء�
	//StopTest�����ǲ�����Ŀ�л����Զ������Զ��·���StopTest
	//�˴�ֱ�ӷ�����Ϊ�˱����¿����������
	//shaolei 20211018
	if (strMacroID == SIMPAC_MACRO_ID_StopTest)
	{
		return 0;
	}

	if (! Connect())
	{
		return 0;
	}

// 	//������
// 	return 1;

	CString strCmd;

	strCmd = _T("$");

	m_strRespond.Empty();
	m_strResult.Empty();

	strCmd += m_strAddress;

	m_bReadMeas = FALSE;
	
	//2021-10-8 yzj ����ģ�����������
	if (strMacroID == SIMPAC_MACRO_ID_ReadMeas)
	{
		strCmd += Cmd_ReadMeas();
		m_bReadMeas = TRUE;
	}
	else if (strMacroID == SIMPAC_MACRO_ID_ManualTest)
	{
		strCmd += Cmd_Run();
	}
	else if (strMacroID == SIMPAC_MACRO_ID_StopManualTest)
	{
		strCmd += Cmd_Stop();
	}

	//2021-9-1  lijunqing ������ʱ����
	else if (strMacroID == _T("StartingProgram"))
	{
		strCmd += StartingProgram();
	}
	else if (strMacroID == _T("ReadingError"))
	{
		strCmd += ReadingError();
	}
	else if (strMacroID == _T("AcknowledgeError"))
	{
		strCmd += AcknowledgeError();
	}
	/*else if (strMacroID == _T("DescriptionRate"))
	{
		strPrompt += DescriptionRate();
	}*/
	else
	{
		strCmd = _T("");
	}

	if (strCmd.GetLength() <= 0)
	{
		return 0;
	}

	strCmd += _T("\r");

	return SendASCII_TwoCommand(strCmd);
}

void CSimpacTestAscii2::StopTest()
{
	if (m_nIsConnectSuccess <= 0)
	{
		return;
	}

	Test(SIMPAC_MACRO_ID_StopTest);
}

//�Ƿ�ִ�в��Խ��������������¶ȡ�ʪ�ȴﵽĿ���趨ֵ
BOOL simpac_cmp_float_in_err_range(float fStand, float fMeas, float fMin, float fAbs, float fReal)
{
	if ( fabs(fStand) < fMin)
	{
		return fabs(fStand - fMeas) < fAbs;
	}

	return  fabs(fStand - fMeas) / fabs(fStand) < fReal;
}

BOOL CSimpacTestAscii2::IsAbsErrFinished()
{
	//2021-10-11 yzj ����ʹ�þ������
	//BOOL b1 = simpac_cmp_float_in_err_range(m_fTemperature, m_fTemperature_Read, 10, 0.2f, 0.05f);
	//BOOL b2 = simpac_cmp_float_in_err_range(m_fHumidity, m_fHumidity_Read, 10, 0.2f, 0.05);
	BOOL b1 = abs(m_fTemperature - m_fTemperature_Read) < m_fAbsErr;
	BOOL b2 = abs(m_fHumidity - m_fHumidity_Read) < m_fAbsErr;

	return b1 && b2;
}

BOOL CSimpacTestAscii2::IsRunTimeFinished()
{
	return (m_fRunTime <= 0);
}

BOOL CSimpacTestAscii2::IsTestFinished()
{
	if(m_strJdgType == SIMPAC_PARA_IDX_AbsErr)
	{
		return IsAbsErrFinished();
	}
	else if(m_strJdgType == SIMPAC_PARA_IDX_RunTime)
	{
		return IsRunTimeFinished();
	}

	return (IsAbsErrFinished() || IsRunTimeFinished());
}



