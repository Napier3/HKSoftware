#include "stdafx.h"
#include "Dtvp200Test.h"
#include "../../../../Module/System/TickCount32.h"
#include "../../../../SttStudio/Module/SttGlobalDef.h"

CDtvp200Test::CDtvp200Test()
{
	m_bIsXTimerRunning = FALSE;
	m_nIsConnectSuccess = 0;
	InitParas();
	m_nRunTime = 0;
	m_nJudgeCount = 0;

	m_nPitchRtAngle = 0;//内框角度   精度0.001
	m_fPitchRtAngle = 0.0;//内框实际角度
	m_nPitchRtSpeed = 0;//内框速度
	m_nPitchRtEnable = 0;//内框状态 0-电机自由 1-电机使能
	m_nPitchRtArrive = 0;//内框到达 0-未到达指定位置 1-到达指定位置

	m_nPositionRtAngle = 0;//外框角度   精度0.001
	m_fPositionRtAngle = 0.0;//外框实际角度
	m_nPositionRtSpeed = 0;//外框速度
	m_nPositionRtEnable = 0;//外框状态 0-电机自由 1-电机使能
	m_nPositionRtArrive = 0;//外框到达 0-未到达指定位置 1-到达指定位置
}

CDtvp200Test::~CDtvp200Test( void )
{
	
}

void CDtvp200Test::InitParas()
{
	m_nEnable[0] = 0;
	m_nEnable[1] = 0;
	m_nWrokModel[0] = 0;
	m_nWrokModel[1] = 0;
	m_nAngleControl[0] = 0;
	m_nAngleControl[1] = 0;
	m_nSpeedControl[0] = 0;
	m_nSpeedControl[1] = 0;
	m_nOrderSetting = DTVP_SET_ORDER_NOSET;
}

int CDtvp200Test::send_command(BYTE *cmd )
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
	char cstr[Comm_Text_SendLens] = {0};

	for (int i = 0;i< Comm_Text_SendLens;i++)
	{
		cstr[i] = cmd[i];
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("输出：%s"), cstr);
	int numsent;

	numsent = m_Serial.SendData(cstr,Comm_Text_SendLens);

	if (numsent == CODE_ERROR)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("发送失败"));
		return 0;
	}
	else
	{
		return 1;
	}
}

int CDtvp200Test::receive_answer()
{
	BYTE bAllRec[4096] = {0};
	BYTE bRec[Comm_Text_ReceiveLens] = {0};/* receive buffer */
	DWORD numrec;				/* number of received characters */ 
 	m_Serial.RecieveData((char*)bAllRec,numrec);

	if (numrec == 0)
	{
		return 0;
	}

	int nMul = numrec % Comm_Text_ReceiveLens;
	int n = 0;
	for (int i = numrec - Comm_Text_ReceiveLens - nMul;i < numrec - nMul;i++)
	{
		bRec[n++] = bAllRec[i];
	}
	
 	if (bRec[Comm_Text_ReceiveLens - 1] != CRC16(bRec,Comm_Text_ReceiveLens -1))
 	{
 		return 0;
 	}
	m_nPitchRtAngle = Cal4ByteToInt(bRec,3);
	m_fPitchRtAngle = m_nPitchRtAngle / 1000.0;
	m_nPitchRtSpeed = Cal4ByteToInt(bRec,7);
	m_nPitchRtEnable = GetLowByte(bRec[11]);
	m_nPitchRtArrive = GetHeigthByte(bRec[11]);

	m_nPositionRtAngle = Cal4ByteToInt(bRec,12);
	m_fPositionRtAngle = m_nPositionRtAngle / 1000.0;
	m_nPositionRtSpeed = Cal4ByteToInt(bRec,16);
	m_nPositionRtEnable = GetLowByte(bRec[20]);
	m_nPositionRtArrive = GetHeigthByte(bRec[20]);

	return numrec;
}

BOOL CDtvp200Test::Connect()
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
		m_Serial.m_oConfig.GetSerialComm(nComm);
		m_strError.Format(_T("打开串口失败！【COM%d】"), nComm);
		CLogPrint::LogString(XLOGLEVEL_ERROR, m_strError);
		m_nIsConnectSuccess = 0;
	}
	else
	{
		m_nIsConnectSuccess = 1;
		m_Serial.SetSerialAttributesEx();
		m_Serial.SetSerialBufferSize(1024,512);
	}
	m_nOrderSetting = DTVP_SET_ORDER_NOSET;//每次连接都重置

	return m_nIsConnectSuccess;
}

BOOL CDtvp200Test::DisConnect()
{
	if (m_nIsConnectSuccess <= 0)
	{
		return m_nIsConnectSuccess;
	}

	m_Serial.CloseSerial();

	m_nIsConnectSuccess = 0;

	return m_nIsConnectSuccess;
}

LONG CDtvp200Test::Test( const CString &strMacroID)
{
	int nOrder = 0; //指令编号 0-发送俯仰(内圈)指令 1-发送方位(外框)指令

	while(nOrder < 2)
	{
		if (! Connect())
		{
			return 0;
		}

		BYTE bSendCmd[Comm_Text_SendLens] = {0};

		bSendCmd[0] = 0xAA;
		bSendCmd[1] = 0xA5;
		bSendCmd[2] = 0x55;

		if (strMacroID == DTVP_MACRO_ID_SetEnable)
		{
			m_nOrderSetting = DTVP_SET_ORDER_SETENABLE;
			SetEnable(bSendCmd,nOrder);
		}
		else if (strMacroID == DTVP_MACRO_ID_AngleSet)
		{
			m_nOrderSetting = DTVP_SET_ORDER_SETANGLE;

			if (m_nSpeedControl[nOrder] > 0)//速度大于0的时候才发控制消息,否则不发
			{
				AngleSet(bSendCmd,nOrder);
			}
		}

		bSendCmd[Comm_Text_SendLens - 1] = CRC16(bSendCmd,Comm_Text_SendLens-1);
		
		if (!send_command(bSendCmd))
		{
			return 0;
		}

		CTickCount32 oTick;	//停100毫秒后发下一条指令
		oTick.DoEvents(100);

		nOrder++;
	}

	return 1;
}

void CDtvp200Test::StopTest()
{
	//停止测试时，将所有的参数恢复成初始化状态即可
	//InitParas();
}

void CDtvp200Test::SetEnable( BYTE *cmd ,int nOrder)
{
	if (nOrder == 0)
	{
		cmd[3] = 0x1E;
	}
	else
		cmd[3] = 0x2E;
	
	if (m_nEnable[nOrder] == 1)
	{
		cmd[8] = 0x00;
	}
	else
	{
		cmd[8] = 0x80;
	}
	
	cmd[4] = 0x00;
	cmd[5] = 0x00;
	cmd[6] = 0x00;
	cmd[7] = 0x00;
	
	cmd[9] = 0x00;
	cmd[10] = 0x00;
	cmd[11] = 0x00;
	cmd[12] = 0x00;
}

void CDtvp200Test::AngleSet( BYTE *cmd ,int nOrder)
{
	if (m_nWrokModel[nOrder] == 0)
	{
		if (nOrder == 0)
		{
			cmd[3] = 0x11;
		}
		else
		{
			cmd[3] = 0x21;
		}
		
		cmd[8] = 0x00;
	}
	else
	{
		if (nOrder == 0)
		{
			cmd[3] = 0x12;
		}
		else
		{
			cmd[3] = 0x22;
		}
		if (m_nAngleControl[nOrder] > 0)
		{
			cmd[8] = 0x00;
		}
		else
		{
			cmd[8] = 0x80;
		}
	}
		
	cmd[4] = (BYTE)(0xff & m_nAngleControl[nOrder]);
	cmd[5] = (BYTE)((0xff00 & m_nAngleControl[nOrder]) >> 8);
	cmd[6] = (BYTE)((0xff0000 & m_nAngleControl[nOrder]) >> 16);
	cmd[7] = (BYTE)((0xff000000 & m_nAngleControl[nOrder]) >> 24);

	cmd[9] = (BYTE)(0xff & abs(m_nSpeedControl[nOrder]));
	cmd[10] = (BYTE)((0xff00 & abs(m_nSpeedControl[nOrder])) >> 8);
	cmd[11] = (BYTE)((0xff0000 & abs(m_nSpeedControl[nOrder])) >> 16);
	cmd[12] = (BYTE)((0xff000000 & abs(m_nSpeedControl[nOrder])) >> 24);
}

BYTE CDtvp200Test::CRC16( BYTE *cmd,int nLength )
{
	int nCRCHi = 0;
	for (int i=0; i < nLength ; i++)
	{
		nCRCHi += cmd[i];
	}

	return nCRCHi & 0xFF;
}

int CDtvp200Test::Cal4ByteToInt( BYTE *byteContext,int nIndex)
{
	int nValue;

	nValue = byteContext[nIndex] & 0xFF;
	nValue |= ((byteContext[nIndex + 1] << 8) & 0xFF00);
	nValue |= ((byteContext[nIndex + 2] << 16) & 0xFF0000);
	nValue |= ((byteContext[nIndex + 3] << 24) & 0xFF000000);

	return nValue;
}

int CDtvp200Test::GetHeigthByte( BYTE byteValue )
{
	int nValue = ((byteValue & 0xF0) >> 4);
// 	int x = ((byteValue >> 4) & 0x0F);
// 	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("nValue = %d  x= %d"), nValue, x);
	return nValue;
}

int CDtvp200Test::GetLowByte( BYTE byteValue )
{
	int nValue = (byteValue & 0x0F);
	return nValue;
}

BOOL CDtvp200Test::IsTestFinish()
{
	if(m_nOrderSetting == DTVP_SET_ORDER_SETENABLE)
	{
		//设置使能之后，需要等待仪器校准，故此处固定等待30s
		if (m_nEnable[0] ==1 || m_nEnable[1] == 1)
		{
			if (m_nRunTime >= 30000)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
		
		//上送的报文中，有时候会解析到m_nPitchRtEnable == 0，所以还是采用延时处理
// 		if (m_nEnable[0] == m_nPitchRtEnable && m_nEnable[1] == m_nPositionRtEnable)
// 		{
// 			return TRUE;
// 		}
// 		else
// 			return FALSE;
	}
	else if (m_nOrderSetting == DTVP_SET_ORDER_SETANGLE)
	{
		//协议中的到达指定位置的信息没有上报，暂时用转动速度来判断是否到达指定位置。速度=0 表示到达指定位置
		//速度=0也不靠谱，稍微有抖动，速度就不等于0。
		//跟客户沟通后，此处延迟60s，认为到达指定位置。
		if (abs(m_nAngleControl[0]) > 0 && m_nPitchRtSpeed == 0)
		{
			m_nJudgeCount++;
			
			if (m_nJudgeCount < 20)
			{
				return FALSE;
			}
		}
		else
		{
			m_nJudgeCount = 0;
		}

		if (m_nRunTime >= 120000 || m_nJudgeCount >= 20)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}

// 		if (m_nSpeedControl[0] > 0 && m_nPitchRtSpeed != 0/*m_nPitchRtArrive == 0*/)//设置速度大于0 且未到达指定位置
// 		{
// 			return FALSE;
// 		}
// 		else
// 		{
// 			if (m_nSpeedControl[1] > 0 && m_nPositionRtSpeed != 0/*m_nPositionRtArrive == 0*/)//设置速度大于0 且未到达指定位置
// 			{
// 				return FALSE;
// 			}
// 			else
//				return TRUE;//设置速度大于0 且到达指定位置
//		}
	}

	return TRUE;
}






