#include "stdafx.h"
#include "GuBeiTest.h"
#include "../../../../Module\Serial\Serial.h"
// #include "d:\Work\Source\IotAtsMngr\Module\Vm\GuBei\FileWriteApi.h"
CGuBeiTest::CGuBeiTest()
{
	m_nIsConnectSuccess = 0;//����״̬
	m_fRunTime = 0;
	m_fAbsErr = 0;
	m_bReadMeas = FALSE;//���͵������Ƕ�ȡ����ֵ
	//yzj 2021-09-24 ���ݿ��в���address�ֶ�,��д��01
	m_strAddress = _T("01");
	m_bIsXTimerRunning = FALSE;
}

CGuBeiTest::~CGuBeiTest( void )
{

}
//���ڷ�������
int CGuBeiTest::send_command( BYTE *cmd, int len)
{
	if (m_nIsConnectSuccess <= 0)
	{
		return 0;
	}
	if (!m_Serial.OpenSucc())
	{
		m_nIsConnectSuccess = 0;
		return 0;
	}
	//

	//WriteDownloadData(len, cmd);
	//
    //��Щ�ǲ��ɼ��ַ����޷����
    //CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����%s"),  cmd);
    int numsent = 0;
	numsent = m_Serial.SendData(cmd, len);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("�����%d"),  numsent);
	//printf("%d",numsent);
	//WriteDownloadData(len, cmd);
	if (numsent == CODE_ERROR)
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
int CGuBeiTest::receive_answer()
{
	BYTE bAllRec[4096] = {0};
	
	DWORD numrec ;				/* number of received characters */ 
 	m_Serial.RecieveData((char*)bAllRec,numrec);

	if (numrec == 0)
	{
		return 0;
	}

	
 	// CRC У��



	//��������

	return numrec;
}


unsigned int CGuBeiTest::crc_chk(BYTE *data,BYTE length)
{
	int j;
	unsigned int reg_crc=0xFFFF;
	while(length--)
	{
		reg_crc^=*data++;
		for(j=0;j<8;j++)
		{
			if(reg_crc&0x01)
			{/*LSB(b0)=1*/
				reg_crc=(reg_crc>>1)^0xA001;
			}
			else{
				reg_crc=reg_crc>>1;
			}
		}
	}
	return reg_crc;
}

int CGuBeiTest::SendASCII_OneCommand( )
{
	return 0;
}

int CGuBeiTest::SendASCII_TwoCommand()
{
	return 0;
}

//$01I<CR>  //��ȡʵ��ֵ
CString CGuBeiTest::Cmd_ReadMeas()    
{
	CString strPrompt;
	strPrompt = _T("I");
	return strPrompt;
}

CString CGuBeiTest::float_format(float fVal)
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
CString CGuBeiTest::Cmd_Run()
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
CString CGuBeiTest::Cmd_Stop()
{
	CString strPrompt;

	strPrompt = _T("E ")
		+ float_format(m_fTemperature) + _T(" ")
		+ float_format(m_fHumidity) + _T(" 0000.0 0000.0 00000000000000000000000000000000");

	return strPrompt;
}
//$01P 0000<CR>�����Եڼ����Ѵ�� <����> ����  0000����ֹͣ <����> ���� 
//�����<����>��ʾͨ���������õ�һЩ�������� ��40������1Сʱ֮����80������5Сʱ,��Ԥ���ڻ��������ú�
CString CGuBeiTest::StartingProgram()
{
	CString strPrompt;
	strPrompt.Format(_T("P %d"), m_nProgramNumber);
// 	CString strNumber;
// 	strNumber = parserFaultPara(&m_oEquation,m_pMacro->GetFaultParas(),_T("ProgramNumber"));
// 	strPrompt = _T("P ") + strNumber;
	return strPrompt;
}
//$01F<CR>  ��ȡ������Ϣ
CString CGuBeiTest::ReadingError()
{
	CString strPrompt;
	strPrompt = _T("F");
	return strPrompt;
}
//$01Q<CR>  ȷ�����д���
CString CGuBeiTest::AcknowledgeError()
{
	CString strPrompt;
	strPrompt = _T("Q");
	return strPrompt;
}


//����
BOOL CGuBeiTest::Connect()
{
	m_strError.Empty();

	if (m_nIsConnectSuccess > 0)
	{
		return m_nIsConnectSuccess;
	}

	m_Serial.SetUseOverlapped(FALSE);
	m_Serial.OpenSerialEx();
	
	if (!m_Serial.OpenSucc())
	{
		long nComm = 0;
		m_Serial.m_oConfig.GetSerialComm(nComm);//nComm�Ǵ��ں�
		
		m_strError.Format(_T("�򿪴���ʧ�ܣ���COM%d��"), nComm);
		CLogPrint::LogString(XLOGLEVEL_ERROR, m_strError);
		m_nIsConnectSuccess = 0;
	}
	else
	{
		m_nIsConnectSuccess = 1;
		m_Serial.SetSerialAttributesEx();
		m_Serial.SetSerialBufferSize(1024,512);//
		//m_Serial.SetSerialBufferSize(4096,2048);
	}


	return m_nIsConnectSuccess;
}

BOOL CGuBeiTest::DisConnect()
{
	if (m_nIsConnectSuccess <= 0)
	{
		return m_nIsConnectSuccess;
	}

	m_Serial.CloseSerial();

	m_nIsConnectSuccess = 0;

	return m_nIsConnectSuccess;
}


//[$]              [01]             [cmd]            [\r]
//��ʼ�ַ�  ���ߵ�ַ  ��������    ���з���
LONG CGuBeiTest::Test( const CString &strMacroID)
{
	//�����StopTest����ֱ�ӷ��ء�
	//StopTest�����ǲ�����Ŀ�л����Զ������Զ��·���StopTest
	//�˴�ֱ�ӷ�����Ϊ�˱����¿����������
	if (strMacroID == GUBEI_MACRO_ID_StopTest)
	{
		return 0;
	}

	if (! Connect())
	{
		return 0;
	}

	if (strMacroID == GUBEI_MACRO_ID_ReadMeas)
	{
        int i_temp = 0;
        int remain_time = 0;
        this->getTwoValue(ADDR_GET_TEMP, i_temp, remain_time);//�����¶�

        this->m_fTemperature_Read = i_temp/10000;

	}
	else if (strMacroID == GUBEI_MACRO_ID_ManualTest)
	{
        int set_temp = this->m_fTemperature*10000;
		int pre_temp = 0;
		this->setOneValue(ADDR_SET_TEMP, set_temp); //�����¶�
		//this->setOneValue(ADDR_YSJ_DELAY, 1); //�򿪵�Դ'
		this->setOneValue(ADDR_SB, 1); //��ˮ��
		this->getOneValue(ADDR_GET_TEMP, pre_temp); //��ȡ��ǰ�¶�
		if(pre_temp>set_temp&&pre_temp<400000)
		{
			this->setOneValue(ADDR_ZL, 1); //������
		}
        //��Ҫ���� ��Դ��ˮ�á�ѹ������
	}
	else if (strMacroID == GUBEI_MACRO_ID_StopManualTest)
	{
		this->setOneValue(ADDR_ZL, 0); // �ر�����
		this->setOneValue(ADDR_SB, 0); // �ر�ˮ��
		this->setOneValue(ADDR_YSJ_DELAY, 0); // �رյ�Դ
        //���ͽ���ָ��
        //��Ҫ����ʲôָ��������ĵ�û����ȷ˵��
	}
    
	return 1;
}

void CGuBeiTest::StopTest()
{
	if (m_nIsConnectSuccess <= 0)
	{
		return;
	}

	Test(GUBEI_MACRO_ID_StopTest);
}

//�Ƿ�ִ�в��Խ��������������¶ȡ�ʪ�ȴﵽĿ���趨ֵ
BOOL gubei_cmp_float_in_err_range(float fStand, float fMeas, float fMin, float fAbs, float fReal)
{
	if ( fabs(fStand) < fMin)
	{
		return fabs(fStand - fMeas) < fAbs;
	}

	return  fabs(fStand - fMeas) / fabs(fStand) < fReal;
}

BOOL CGuBeiTest::IsAbsErrFinished()
{
	//2021-10-11 yzj ����ʹ�þ������
	//BOOL b1 = simpac_cmp_float_in_err_range(m_fTemperature, m_fTemperature_Read, 10, 0.2f, 0.05f);
	//BOOL b2 = simpac_cmp_float_in_err_range(m_fHumidity, m_fHumidity_Read, 10, 0.2f, 0.05);
	BOOL b1 = abs(m_fTemperature - m_fTemperature_Read) < m_fAbsErr;
	//BOOL b2 = abs(m_fHumidity - m_fHumidity_Read) < m_fAbsErr;

	return b1 /*&& b2*/;
}

BOOL CGuBeiTest::IsRunTimeFinished()
{
	return (m_fRunTime <= 0);
}

BOOL CGuBeiTest::IsTestFinished()//G2023.3.6
{
	if(m_strJdgType == GUBEI_PARA_IDX_AbsErr)
	{
		return IsAbsErrFinished();
	}
	else if(m_strJdgType == GUBEI_PARA_IDX_RunTime)
	{
		return IsRunTimeFinished();
	}

	return (IsAbsErrFinished() || IsRunTimeFinished());
}


//�趨�¶�
int CGuBeiTest::setTemperature()
{
    BYTE bSendCmd[100] = {0};

    
    bSendCmd[0] = 0x01; //ADR
    bSendCmd[1] = 0x10; //CMD
    //Ҫд��Ĵ�����ʼλ��
    bSendCmd[2] = 0x00;
    bSendCmd[3] = 0x00;
    //д�뵽�����Ĵ���
    bSendCmd[4] = 0x00;
    bSendCmd[5] = 0x01;
    //��������Byte��
    bSendCmd[6] = 0x04;

    //�¶�
    int a = m_fTemperature*10000;
    //����
    bSendCmd[7] = (BYTE )((0xff000000 & a) >> 24);
    bSendCmd[8] = (BYTE )((0xff0000 & a) >> 16);
    bSendCmd[9] = (BYTE )((0xff00 & a) >> 8);
    bSendCmd[10] = (BYTE )(0xff & a); 

    //����crcУ��ֵ
    unsigned int crc = crc_chk(bSendCmd ,11);
    bSendCmd[11] = (BYTE )(0xff & crc);
    bSendCmd[12] = (BYTE )((0xff00 & crc) >> 8);

    //���ڷ�������
    if(0 == send_command(bSendCmd, 13))
    {
        return 0;
    }
    Sleep(20);

    //������Ӧ��Ϣ
    BYTE res[8] = {0};
    DWORD numrec ;				/* number of received characters */ 
    m_Serial.RecieveData((char*)res, numrec);

    //�ж���Ӧ��Ϣ�Ƿ� ����
    if (numrec < 8)
    {
        return 0;
    }

    for (int i=0;i<6;++i)
    {
        if (res[i] != bSendCmd[i])
        {
            return 0;
        }
    }

    //���crcУ��ֵ
    unsigned int crcRes = crc_chk(res , 6);
    BYTE  c1 = (BYTE)(0xff & crcRes);
    BYTE  c2 = (BYTE)((0xff00 & crcRes) >> 8);
    if(c1!=res[6]  ||  c2!=res[7])
    {
        return 0;
    }

    return 1;
}

//��ȡ1������
int CGuBeiTest::getOneValue( ADDR_REG addr,   int& value)
{
    BYTE bSendCmd[8] = {0};
    int len = sizeof(bSendCmd);

    bSendCmd[0] = 0x01; // �Ǳ��ַ
    bSendCmd[1] = 0x03; //CMD
    //��ʼ���ݵ�ַ
    bSendCmd[2] =  (BYTE )((0xff00 & addr) >> 8);
    bSendCmd[3] = (BYTE )(0xff & addr); 
    //��ȡ���ݼ���
    bSendCmd[4] = 0x00;
    bSendCmd[5] = 0x01;

    //����crcУ��ֵ
    unsigned int crc = crc_chk(bSendCmd , len-2);
    bSendCmd[len-2] = (BYTE )(0xff & crc);
    bSendCmd[len-1] = (BYTE )((0xff00 & crc) >> 8);
    //���ڷ�������
    if(0 == send_command(bSendCmd, len))
    {
        return 0;
    }
    Sleep(20);

    //������Ӧ��Ϣ
    BYTE res[13] = {0};
	
    int lenRec = sizeof(res);
    DWORD numrec ;				/* number of received characters */ 
    m_Serial.RecieveData((char*)res, numrec);
	/*
    //�ж���Ӧ��Ϣ�Ƿ� ����
    if (numrec < lenRec)
    {
        return 0;
    }

    for (int i=0;i<2;++i)
    {
        if (res[i] != bSendCmd[i])
        {
            return 0;
        }
    }

    //���crcУ��ֵ
    unsigned int crcRes = crc_chk(res , lenRec-2);
    BYTE  c1 = (BYTE)(0xff & crcRes);
    BYTE  c2 = (BYTE)((0xff00 & crcRes) >> 8);
    if(c1!=res[lenRec-2]  ||  c2!=res[lenRec-1])
    {
        return 0;
    }
	*/
	
    //��ȡ����
    value = Cal4ByteToInt(res, 3);

    return 1;
}

//��ȡ2������
int CGuBeiTest::getTwoValue(ADDR_REG addr,   int& value1,  int& value2)
{
    BYTE bSendCmd[8] = {0};
    int len = sizeof(bSendCmd);
 
    bSendCmd[0] = 0x01; // �Ǳ��ַ
    bSendCmd[1] = 0x03; //CMD
    //��ʼ���ݵ�ַ
    bSendCmd[2] =  (BYTE )((0xff00 & ADDR_YSJ_DELAY) >> 8);
    bSendCmd[3] = (BYTE )(0xff & ADDR_YSJ_DELAY); 
    //��ȡ���ݼ���
    bSendCmd[4] = 0x00;
    bSendCmd[5] = 0x02;

    //����crcУ��ֵ
    unsigned int crc = crc_chk(bSendCmd , len-2);
    bSendCmd[len-2] = (BYTE )(0xff & crc);
    bSendCmd[len-1] = (BYTE )((0xff00 & crc) >> 8);

    //���ڷ�������
    if(0 == send_command(bSendCmd, len))
    {
        return 0;
    }
    Sleep(20);

    BYTE res[13] = {0};
    int lenRec = sizeof(res);
    DWORD numrec ;				/* number of received characters */ 
    m_Serial.RecieveData((char*)res, numrec);

    //�ж���Ӧ��Ϣ�Ƿ� ����
    if (numrec < lenRec)
    {
        return 0;
    }

    for (int i=0;i<2;++i)
    {
        if (res[i] != bSendCmd[i])
        {
            return 0;
        }
    }

    //���crcУ��ֵ
    unsigned int crcRes = crc_chk(res , lenRec-2);
    BYTE  c1 = (BYTE)(0xff & crcRes);
    BYTE  c2 = (BYTE)((0xff00 & crcRes) >> 8);
    if(c1!=res[lenRec-2]  ||  c2!=res[lenRec-1])
    {
        return 0;
    }

    //��ȡ����
   value1= Cal4ByteToInt(res, 3);
   value1= Cal4ByteToInt(res, 7);
   return 1;
}

//int CGuBeiTest::getValue(ADDR_REG addr,  int* value,  int len)
//{
//    return 0;
//}

//����1������
int CGuBeiTest::setOneValue( ADDR_REG addr,   int value)
{
    
	BYTE bSendCmd[10] = {0};
    int len = sizeof(bSendCmd);

    bSendCmd[0] = 0x01; // �Ǳ��ַ
    bSendCmd[1] = 0x06; //CMD
    //��ʼ���ݵ�ַ
    bSendCmd[2] =  (BYTE)((0xff00 & addr) >> 8);
    bSendCmd[3] = (BYTE)(0xff & addr); 
    //��������
    bSendCmd[4] = (BYTE)((value >> 24) & 0xFF);
    bSendCmd[5] = (BYTE)((value >> 16) & 0xFF);
    bSendCmd[6] = (BYTE)((value >>  8) & 0xFF);
    bSendCmd[7] = (BYTE)( 0x000000ff & value); 

    //����crcУ��ֵ
    unsigned int crc = crc_chk(bSendCmd , 8);
    bSendCmd[8] = (BYTE)(0x00ff & crc);
    bSendCmd[9] = (BYTE)((0xff00 & crc) >> 8);

    //���ڷ�������
    if(0 == send_command(bSendCmd, len))
    {
        return 0;
    }

	CLogPrint::LogBuffer(bSendCmd, 0, len);

    Sleep(600);

    //������Ӧ��Ϣ
    BYTE res[10] = {0};//13
    int lenRec = sizeof(res);//10
    DWORD numrec = 0;				/* number of received characters */ 

	m_Serial.RecieveData((char*)res, numrec);//(char*)

	if (numrec > 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ReadData:"));
		CLogPrint::LogBuffer(res, 0, numrec);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ReadData: = 0"));
	}

    //�ж���Ӧ��Ϣ�Ƿ� ����
    if (numrec < lenRec)
    {
        return 0;
    }

    //�����Ӧ��Ϣ�Ƿ���Ч
   for (int i=0;i<lenRec;++i)
    {
        if(res[i] != bSendCmd[i])
        {
           return 0;
        }
   }

    return 1;
}

//����2������
int CGuBeiTest::setTwoValue(ADDR_REG addr,   int value1,  int value2)
{
    BYTE bSendCmd[17] = {0};
    int len = sizeof(bSendCmd);

    bSendCmd[0] = 0x01; // �Ǳ��ַ
    bSendCmd[1] = 0x10; //CMD
    //��ʼ���ݵ�ַ
    bSendCmd[2] =  (BYTE)((0xff00 & addr) >> 8);
    bSendCmd[3] = (BYTE)(0xff & addr); 
    //�Ĵ�������
    bSendCmd[4] = 0x00;
    bSendCmd[5] = 0x02;
    //���ݼ���
    bSendCmd[6] = 0x08;

    //value1
    bSendCmd[7] = (BYTE)((0xff000000 &value1) >> 24);
    bSendCmd[8] = (BYTE)((0xff0000 & value1) >> 16);
    bSendCmd[9] = (BYTE)((0xff00 & value1) >> 8);
    bSendCmd[10] = (BYTE)(0xff & value1); 
    //value2
    bSendCmd[11] = (BYTE)((0xff000000 &value2) >> 24);
    bSendCmd[12] = (BYTE)((0xff0000 & value2) >> 16);
    bSendCmd[13] = (BYTE)((0xff00 & value2) >> 8);
    bSendCmd[14] = (BYTE)(0xff & value2); 

    //����crcУ��ֵ
    unsigned int crc = crc_chk(bSendCmd , len-2);
    bSendCmd[len-2] = (BYTE)(0xff & crc);
    bSendCmd[len-1] = (BYTE)((0xff00 & crc) >> 8);

    //���ڷ�������
    if(0 == send_command(bSendCmd, len))
    {
        return 0;
    }
    Sleep(20);

    //������Ӧ��Ϣ
    BYTE res[8] = {0};
    int lenRec = sizeof(res);
    DWORD numrec ;				/* number of received characters */ 
    m_Serial.RecieveData((char*)res, numrec);

    //�ж���Ӧ��Ϣ�Ƿ� ����
    if (numrec < lenRec)
    {
        return 0;
    }

    //�����Ӧ��Ϣ�Ƿ���Ч
    for (int i=0;i<2;++i)
    {
        if (res[i] != bSendCmd[i])
        {
            return 0;
        }
    }

    //���crcУ��ֵ
    unsigned int crcRes = crc_chk(res , lenRec-2);
    BYTE  c1 = (BYTE)(0xff & crcRes);
    BYTE  c2 = (BYTE)((0xff00 & crcRes) >> 8);
    if(c1!=res[lenRec-2]  ||  c2!=res[lenRec-1])
    {
        return 0;
    }


    return 1;
}

//int CGuBeiTest::setValue(ADDR_REG addr,  int* value,  int len)
//{
//    return 0;
//}

int CGuBeiTest::Cal4ByteToInt( BYTE  *byteContext, int nIndex)
{
    int nValue;

    nValue = ((byteContext[nIndex] << 24) & 0xFF000000);
    nValue |=  ((byteContext[nIndex + 1] << 16) & 0xFF0000);
    nValue |= ((byteContext[nIndex + 2] << 8) & 0xFF00); 
    nValue |= byteContext[nIndex + 3] & 0xFF; 

    return nValue;
}
