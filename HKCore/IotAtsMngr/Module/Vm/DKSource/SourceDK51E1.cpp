#include "stdafx.h"
#include "SourceDK51E1.h"
#include "..\..\..\..\Module\System\TickCount32.h"

CSourceDK51E1::CSourceDK51E1()
{
	//设备串口属性固定
	m_nBaudRate = 115200;
	m_nByteSize = 8;
	m_nStopBits = 0;
	m_nParity = 0;

	m_nRxID = 0;
	m_nTxID = 0;

	m_bIsConnected = FALSE;
	m_bIsXTimerRunning = FALSE;

	m_pReport = 0;
}

CSourceDK51E1::~CSourceDK51E1()
{
	
}

BOOL CSourceDK51E1::Connect(long nComNumber)
{
	if (m_bIsConnected)
	{
		return m_bIsConnected;
	}
	
	SetUseOverlapped(FALSE);
	if(OpenSerial(nComNumber) != -1)
	{
		//SetSerialBufferSize(1024, 1024);
		GetSerialAttributes();//此处get实际上是初始化DCB
		SetSerialAttributes(m_nBaudRate, m_nByteSize, m_nStopBits, m_nParity);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("测试仪连接成功!"));
		m_bIsConnected = TRUE;
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("测试仪连接失败!"));
		m_bIsConnected = FALSE;
	}

	return m_bIsConnected;
}

BOOL CSourceDK51E1::Disconnect()
{
	CloseSerial();
	m_bIsConnected = FALSE;
	return TRUE;
}

long CSourceDK51E1::CloseDevice()
{
	long nLen = 0;
	Generate(DKSOURCE_PROCEDURE_AC_CLOSE, _T(""), nLen);
	BYTE* strMsg = m_strData;
	long nRes = SendData(strMsg, nLen);

	CTickCount32 oTick;
	oTick.DoEvents(500);

	Generate(DKSOURCE_PROCEDURE_DC_CLOSE, _T(""), nLen);
	BYTE* strMsg2 = m_strData;
	nRes = SendData(strMsg2, nLen);

	Disconnect();
	return 0;
}

long CSourceDK51E1::CString_htonl(const CString& strNum)
{
	CString strRes = strNum;
	strRes = strRes.Mid(6, 2) + strRes.Mid(4, 2) + strRes.Mid(2, 2) + strRes.Mid(0, 2);
	long nNum = 0;
	HexToLong(strRes, nNum);
	return nNum;
}

float CSourceDK51E1::ByteArr_To_Float(const char* pByteArr)
{
	long n0 = pByteArr[0];
	long n1 = pByteArr[1];
	long n2 = pByteArr[2];
	long n3 = pByteArr[3];
	CString strData;
	strData.Format(_T("%.2x%.2x%.2x%.2x"), n0, n1, n2, n3);
	return CString_To_Float(strData);
}

float CSourceDK51E1::CString_To_Float(const CString& strNum)
{
	unsigned char temp[4] = {0};
	CString strRes = strNum, strTemp;
	for (int i = 0; i< 4; i++)
	{
		strTemp = strRes.Mid(0, 2);
		long num = 0;
		HexToLong(strTemp.GetString(), num);
		temp[i] = char(num);
		strRes = strRes.Mid(2);
	}
	float fNum = 0;
	memcpy(&fNum, temp, 4);
	return fNum;
}

CString CSourceDK51E1::CString_To_Float_Str(const CString& strNum)
{
	float fNum = CString_To_Float(strNum);
	CString strFloat;
	strFloat.Format(_T("%.4f"), fNum);
	return strFloat;
}

CString CSourceDK51E1::Float_To_CString(float fNum)
{
	unsigned char temp[4] = {0};
	memcpy(temp, &fNum, 4);
	CString strTemp, strRes;
	for (int i = 0; i< 4; i++)
	{
		strTemp.Format(_T("%.2x"), temp[i]);
		strRes += strTemp;
	}
	return strRes;
}

long CSourceDK51E1::GetXOR(BYTE* strMsg, long nLen)
{
	long nXOR = 0;
	for (int i = 1; i < nLen - 1; i++)
	{
		nXOR = nXOR ^ strMsg[i];
	}
	return nXOR;
}

void CSourceDK51E1::Generate(long nProcedureID, const CString& strData, long& nByteLen)
{
	//填充前6位
	m_strData[0] = 0x81;
	m_strData[1] = m_nRxID;
	m_strData[2] = m_nTxID;
	m_strData[3] = 0;
	m_strData[4] = 0;
	//获取procedure对应的协议中的id,例如33H
	long nData5 = 0;
	HexToLong(DKSource_Idx_To_Code(nProcedureID), nData5);
	m_strData[5] = nData5;

	//填入协议中对应的data信息
	for (int i = 0; i < strData.GetLength(); i++)
	{
		long nTemp = 0;
		HexToLong(strData.Mid(2 * i, 2).GetString(), nTemp);
		m_strData[6 + i] = nTemp;
	}

	//计算长度,高低位变换
	long nLen = strData.GetLength() / 2 + 7;
	unsigned long uLen = ntohs(nLen);
	CString strLenth;
	long nLenthTemp = 0;
	strLenth.Format(_T("%.4x"), uLen);
	HexToLong(strLenth.Mid(0, 2).GetString(), nLenthTemp);
	m_strData[3] = nLenthTemp;
	HexToLong(strLenth.Mid(2).GetString(), nLenthTemp);
	m_strData[4] = nLenthTemp;;

	//计算异或校验
	m_strData[nLen - 1] = GetXOR(m_strData, nLen);
	nByteLen = nLen;
}

CString CSourceDK51E1::SetACGear(tagDKSource* pDKSource)
{
	CString strData;
	strData.Format(_T("%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x"),
		(int)pDKSource->m_fUa, (int)pDKSource->m_fUb, (int)pDKSource->m_fUc,
		(int)pDKSource->m_fIa,(int)pDKSource->m_fIb, (int)pDKSource->m_fIc,
		(int)pDKSource->m_fIPa, (int)pDKSource->m_fIPb, (int)pDKSource->m_fIPc);
	return strData;
}

CString CSourceDK51E1::SetACRange(tagDKSource* pDKSource)
{	
	CString strData;
	strData += SetACPhase(pDKSource);
	strData += Float_To_CString(pDKSource->m_fIPa);
	strData += Float_To_CString(pDKSource->m_fIPb);
	strData += Float_To_CString(pDKSource->m_fIPc);
	return strData;
}

CString CSourceDK51E1::SetACPhase(tagDKSource* pDKSource)
{	
	CString strData;
	strData += Float_To_CString(pDKSource->m_fUa);
	strData += Float_To_CString(pDKSource->m_fUb);
	strData += Float_To_CString(pDKSource->m_fUc);
	strData += Float_To_CString(pDKSource->m_fIa);
	strData += Float_To_CString(pDKSource->m_fIb);
	strData += Float_To_CString(pDKSource->m_fIc);
	return strData;
}

CString CSourceDK51E1::SetACRate(tagDKSource* pDKSource)
{	
	CString strData;
	strData += Float_To_CString(pDKSource->m_fFa);
	strData += Float_To_CString(pDKSource->m_fFb);
	strData += Float_To_CString(pDKSource->m_fFc);
	//协议中对待flag只提到了以下两种情况
	//当 Fa=Fb!=Fc 时，Flag=2；Fa=Fb=Fc 时，Flag=3
	//设置时 Fa=Fb，Fc 可以设置为与 AB 相不同的频率。也可以只设置 Fa，则默认为
	//三相同频，用于兼容以前的设备通讯程序
	if(pDKSource->m_fFa == pDKSource->m_fFb
		&& pDKSource->m_fFa != pDKSource->m_fFc)
	{
		CString strTemp;
		strTemp.Format(_T("%.2x"), 2);
		strData += strTemp;
	}
	else if (pDKSource->m_fFa == pDKSource->m_fFb
		&& pDKSource->m_fFa == pDKSource->m_fFc)
	{
		CString strTemp;
		strTemp.Format(_T("%.2x"), 3);
		strData += strTemp;
	}
	return strData;
}

CString CSourceDK51E1::SetACPrinciple(tagDKSource* pDKSource)
{
	//使用m_nMode,逻辑与GetSysMode一致
	return SetSysMode(pDKSource);
}

CString CSourceDK51E1::SetACEnableLoop(tagDKSource* pDKSource)
{
	CString strMode, strLoop;
	strMode = SetSysMode(pDKSource);	//HarmonicMode
	strLoop.Format(_T("%.2x"), pDKSource->m_nEnable); //CloseLoop
	return strLoop + strMode;
}

CString CSourceDK51E1::SetACVerification(tagDKSource* pDKSource)
{
	/*
	Type – 电能校验类型，‘P’- 有功； ’Q’- 无功
	MPC – 表有功电能常数，范围：1.0~599999999.0，4 个字节的浮点型数据
	MQC – 表无功电能常数，范围：1.0~599999999.0，4 个字节的浮点型数据
	SPC – 源有功电能常数，范围：1.0~599999999.0，4 个字节的浮点型数据
	SQC – 源无功电能常数，范围：1.0~599999999.0，4 个字节的浮点型数据
	MDIV – 分频系数，范围：1~9999999，4 个字节的无符号整型数据，高字节在前
	MROU – 校验圈数，范围：大于等于 1，4 个字节的无符号整型数据，高字节在前
	*/
	CString strData, strType, strNum;
	strType.Format(_T("%.2x"), pDKSource->m_nType);
	strData += strType;
	strData += Float_To_CString(pDKSource->m_fMPC);
	strData += Float_To_CString(pDKSource->m_fMQC);
	strData += Float_To_CString(pDKSource->m_fSPC);
	strData += Float_To_CString(pDKSource->m_fSQC);
	strNum.Format(_T("%.8x%.8x"), ntohl(pDKSource->m_nMDIV), ntohl(pDKSource->m_nMROU));
	strData += strNum;
	return strData;
}

CString CSourceDK51E1::SetACActivePower(tagDKSource* pDKSource)
{
	CString strData, strType;
	strType.Format(_T("%.2x"), pDKSource->m_nType);
	strData += strType;
	strData += Float_To_CString(pDKSource->m_fPower);
	return strData;
}

CString CSourceDK51E1::SetACReactivePower(tagDKSource* pDKSource)
{
	return SetACActivePower(pDKSource);
}

CString CSourceDK51E1::SetDCAmp(tagDKSource* pDKSource)
{
	/*
	Type：类型，’U’-电压，’I’-电流。
	Range ：直流源档位，1 个字节
	SData：直流源幅值，4 个字节表示的浮点型数据。
	*/
	CString strType, strRange, strSData, strData;
	if (pDKSource->m_nType == 1)
	{
		strType.Format(_T("%.2x"), 'I');
	}
	else
	{
		strType.Format(_T("%.2x"), 'U');
	}

	strRange.Format(_T("%.2x"), pDKSource->m_nRange);
	strSData = Float_To_CString(pDKSource->m_fSData);
	strData = strRange + strSData + strType;
	return strData;
}

CString CSourceDK51E1::SetSysMode(tagDKSource* pDKSource)
{
	/*
	Mode：0-标准源，1-标准表，2-标准表（钳表）
	10-标准源校准模式，11-标准表校准模式，12-钳形表校准模式
	13-直流源校准模式，14-直流表校准模式
	*/
	CString strMode;
	strMode.Format(_T("%.2x"), pDKSource->m_nMode);
	return strMode;
}

CString CSourceDK51E1::SetSysPage(tagDKSource* pDKSource)
{
	/*
	1-标准输出；
	2-相位输出；
	3-矢量显示；
	4-谐波设置；
	5-直流测量；
	6-直流输出； 
	8-电能校验；
	9-参数测量；
	10-相位测量；
	11-矢量显示；
	12-参数测量；
	13-相位测量；
	14-矢量显示
	注意：该命令在实际测试中能绕过需要输入密码才能进入的部分界面
	*/
	CString strPage;
	strPage.Format(_T("%.2x"), pDKSource->m_nPage);
	return strPage;
}

CString CSourceDK51E1::SetDCRange(tagDKSource* pDKSource)
{
	/*
	Type：类型，’U’-电压，’I’-电流。
	Range ：直流源档位，1 个字节
	SData：直流源幅值，4 个字节表示的浮点型数据。
	*/
	CString strData, strSData;
	strSData = Float_To_CString(pDKSource->m_fSData);
	strData.Format(_T("%.2x%s%.2x"), pDKSource->m_nRange, strSData, pDKSource->m_nType);
	return strData;
}

CString CSourceDK51E1::SetDCMeasurementType(tagDKSource* pDKSource)
{
	CString strData;
	strData.Format(_T("%.2x"), pDKSource->m_nType);
	return strData;
}

CString CSourceDK51E1::SetDCGear(tagDKSource* pDKSource)
{
	/*
	Type：类型，’U’-电压，’I’-电流。
	Range 为 1 字节的档位字
	*/
	CString strData, strType;
	if (pDKSource->m_nType == 1)
	{
		strType.Format(_T("%.2x"), 'I');
	}
	else
	{
		strType.Format(_T("%.2x"), 'U');
	}
	strData.Format(_T("%.2x%s"), pDKSource->m_nRange, strType);
	return strData;
}

CString CSourceDK51E1::SetRemoteOutput(tagDKSource* pDKSource)
{
	CString strData, strTemp;
	strTemp.Format(_T("%.2x%.2x%.2x%.2x"), pDKSource->m_nD0, pDKSource->m_nD1,
		pDKSource->m_nD2, pDKSource->m_nD3);
	return strData;
}

CString CSourceDK51E1::SetRemoteControl(tagDKSource* pDKSource)
{
	return SetSysMode(pDKSource);
}

CString CSourceDK51E1::SetACHarmonicParam(tagDKSource* pDKSource)
{
	/*
	Channel：通道选择，由位选择，D0-Ua,D1-Ub,D2-Uc,D3-Ia,D4-Ib,D5-Ic ＝1 时有效
	Count：要设置的谐波个数(≥1)，协议长度 Length 随个数的变化而变化，1 个字节整型
	Count =0 时清空指定通道的所有次数的谐波
	Harmonic - 谐波次数，范围： 2 ~ 32 ，1 个字节整型
	Amplitude - 谐波幅度，范围： 0 ~ 0.4，4 个字节的浮点型数据
	Angle - 谐波相位，范围： 0°~ 359.99°，4 个字节的浮点型数据
	注意：协议中规定了协议长度超过256的情况，但实际测试报告中并不需要那么多，所以
	只设置固定组数
	*/
	CString strData, strChannel, strCount, strHarmonic;
	strChannel.Format(_T("%.2x"), pDKSource->m_nType);
	strCount.Format(_T("%.2x"), pDKSource->m_nCount);
	strData += strChannel + strCount;
	POS pos = pDKSource->m_pHarmonic->GetHeadPosition();
	while (pos)
	{
		CHarmonic* pHar = (CHarmonic*)pDKSource->m_pHarmonic->GetNext(pos);
		strHarmonic.Format(_T("%.2x"), pHar->m_nHarmonic);
		strData += strHarmonic + Float_To_CString(pHar->m_fAmplitude)
			+ Float_To_CString(pHar->m_fAngle);
	}
	return strData;
}

void CSourceDK51E1::GetACError(CDataGroup* pDataGroup)
{
	/*
	Flag 为 1 字节的电能误差有效标志位
	Flag = 0 表示 EV 值无效；
	Flag = ‘P’ 表示 EV 值为有功电能校验误差；
	Flag = ‘Q’ 表示 EV 值为无功电能校验误差

	EV 为 4 个字节的浮点型数据，单位：%
	ROUND 为当前校验圈数，4 个字节的无符号整数数据，高字节在前
	*/
	long nFlag = CString_To_long(m_strBuffer.Mid(12, 2));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Flag, nFlag);

	CString strEV = m_strBuffer.Mid(14, 8);
	float fEV = CString_To_Float(strEV);
	strEV.Format(_T("%f%"), fEV);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_EV, strEV);

	CString strROUND = m_strBuffer.Mid(22, 8);
	long nROUND = CString_htonl(strROUND);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_ROUND, nROUND);
}

void CSourceDK51E1::GetDCParam(CDataGroup* pDataGroup)
{
	/*
	Type：类型，’U’-电压，’I’-电流，这里将电流电压一并写入
	Range ：当前直流源档位，1 个字节
	DCData：直流源幅值，4 个字节表示的浮点型数据
	*/
	CString strDCData = m_strBuffer.Mid(14, 8);
	float fDCData = CString_To_Float(strDCData);
	strDCData.Format(_T("%.8f"), fDCData);
	long nRange = CString_To_long(m_strBuffer.Mid(12, 2));
	if(m_strBuffer.Mid(22, 2) == _T("49"))
	{
		pDataGroup->AddNewData(DKSOURCE_PARA_ID_Range, DKSource_IRange_To_DCStr(nRange));
		pDataGroup->AddNewData(DKSOURCE_PARA_ID_DC_I, strDCData);
		pDataGroup->AddNewData(DKSOURCE_PARA_ID_DC_U, _T("0.00"));
	}
	else
	{
		pDataGroup->AddNewData(DKSOURCE_PARA_ID_Range, DKSource_URange_To_DCStr(nRange));
		pDataGroup->AddNewData(DKSOURCE_PARA_ID_DC_U, strDCData);
		pDataGroup->AddNewData(DKSOURCE_PARA_ID_DC_I, _T("0.00"));
	}
}

void CSourceDK51E1::GetACParam(CDataGroup* pDataGroup)
{
	//获取频率
	CString strF = CString_To_Float_Str(m_strBuffer.Mid(12, 8));
	//获取电压电流档位
	long nUaRange = 0, nUbRange = 0, nUcRange = 0, nIaRange = 0, nIbRange = 0, nIcRange = 0;
	HexToLong(m_strBuffer.Mid(20, 2).GetString(), nUaRange);
	HexToLong(m_strBuffer.Mid(22, 2).GetString(), nUbRange);
	HexToLong(m_strBuffer.Mid(24, 2).GetString(), nUcRange);
	HexToLong(m_strBuffer.Mid(26, 2).GetString(), nIaRange);
	HexToLong(m_strBuffer.Mid(28, 2).GetString(), nIbRange);
	HexToLong(m_strBuffer.Mid(30, 2).GetString(), nIcRange);
	//获取电压电流相位值
	CString strUa = CString_To_Float_Str(m_strBuffer.Mid(32, 8));
	CString strUb = CString_To_Float_Str(m_strBuffer.Mid(40, 8));
	CString strUc = CString_To_Float_Str(m_strBuffer.Mid(48, 8));
	CString strIa = CString_To_Float_Str(m_strBuffer.Mid(56, 8));
	CString strIb = CString_To_Float_Str(m_strBuffer.Mid(64, 8));
	CString strIc = CString_To_Float_Str(m_strBuffer.Mid(72, 8));
	CString strUaPhase = CString_To_Float_Str(m_strBuffer.Mid(80, 8));
	CString strUbPhase = CString_To_Float_Str(m_strBuffer.Mid(88, 8));
	CString strUcPhase = CString_To_Float_Str(m_strBuffer.Mid(96, 8));
	CString strIaPhase = CString_To_Float_Str(m_strBuffer.Mid(104, 8));
	CString strIbPhase = CString_To_Float_Str(m_strBuffer.Mid(112, 8));
	CString strIcPhase = CString_To_Float_Str(m_strBuffer.Mid(120, 8));
	//读取功率值
	CString strPa = CString_To_Float_Str(m_strBuffer.Mid(128, 8));
	CString strPb = CString_To_Float_Str(m_strBuffer.Mid(136, 8));
	CString strPc = CString_To_Float_Str(m_strBuffer.Mid(144, 8));
	CString strP = CString_To_Float_Str(m_strBuffer.Mid(152, 8));
	CString strQa = CString_To_Float_Str(m_strBuffer.Mid(160, 8));
	CString strQb = CString_To_Float_Str(m_strBuffer.Mid(168, 8));
	CString strQc = CString_To_Float_Str(m_strBuffer.Mid(176, 8));
	CString strQ = CString_To_Float_Str(m_strBuffer.Mid(184, 8));
	CString strSa = CString_To_Float_Str(m_strBuffer.Mid(192, 8));
	CString strSb = CString_To_Float_Str(m_strBuffer.Mid(200, 8));
	CString strSc = CString_To_Float_Str(m_strBuffer.Mid(208, 8));
	CString strS = CString_To_Float_Str(m_strBuffer.Mid(216, 8));
	CString strCosFaia = CString_To_Float_Str(m_strBuffer.Mid(224, 8));
	CString strCosFaib = CString_To_Float_Str(m_strBuffer.Mid(232, 8));
	CString strCosFaic = CString_To_Float_Str(m_strBuffer.Mid(240, 8));
	CString strCosFai = CString_To_Float_Str(m_strBuffer.Mid(248, 8));
	long nPrinciple = 0, nEnable = 0, nMode = 0;
	HexToLong(m_strBuffer.Mid(256, 2).GetString(), nPrinciple);
	HexToLong(m_strBuffer.Mid(258, 2).GetString(), nEnable);
	HexToLong(m_strBuffer.Mid(260, 2).GetString(), nMode);

	pDataGroup->AddNewData(DKSOURCE_PARA_ID_F, strF);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_UaRange, DKSource_URange_To_ACStr(nUaRange));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_UbRange, DKSource_URange_To_ACStr(nUbRange));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_UcRange, DKSource_URange_To_ACStr(nUcRange));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_IaRange, DKSource_IRange_To_ACStr(nIaRange));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_IbRange, DKSource_IRange_To_ACStr(nIbRange));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_IcRange, DKSource_IRange_To_ACStr(nIcRange));
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Ua, strUa);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Ub, strUb);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Uc, strUc);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Ia, strIa);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Ib, strIb);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Ic, strIc);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_UaPhase, strUaPhase);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_UbPhase, strUbPhase);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_UcPhase, strUcPhase);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_IaPhase, strIaPhase);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_IbPhase, strIbPhase);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_IcPhase, strIcPhase);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Pa, strPa);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Pb, strPb);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Pc, strPc);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_P, strP);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Qa, strQa);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Qb, strQb);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Qc, strQc);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Q, strQ);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Sa, strSa);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Sb, strSb);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_Sc, strSc);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_S, strS);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_CosFaia, strCosFaia);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_CosFaib, strCosFaib);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_CosFaic, strCosFaic);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_CosFai, strCosFai);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_PRINCIPLE, nPrinciple);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_CloseloopEn, nEnable);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_HarmonicMode, nMode);
}

void CSourceDK51E1::GetRemoteInputState(CDataGroup* pDataGroup)
{
	long nDI0 = 0, nDI1 = 0, nDI2 = 0, nDI3 = 0;
	HexToLong(m_strBuffer.Mid(12, 2).GetString(), nDI3);
	HexToLong(m_strBuffer.Mid(14, 2).GetString(), nDI2);
	HexToLong(m_strBuffer.Mid(16, 2).GetString(), nDI1);
	HexToLong(m_strBuffer.Mid(18, 2).GetString(), nDI0);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_DI3, nDI3);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_DI2, nDI2);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_DI1, nDI1);
	pDataGroup->AddNewData(DKSOURCE_PARA_ID_DI0, nDI0);
}

void CSourceDK51E1::GetDCMeasurementParam(CDataGroup* pDataGroup)
{
	GetDCParam(pDataGroup);
}

void CSourceDK51E1::GetReport(CString& strDCReport, CString& strACReport)
{
	//存在上一次上报的数据则清空
	if (m_pReport)
	{
		delete m_pReport;
		m_pReport = NULL;
	}

	m_pReport = new CDataGroup;

	//填写直流电压电流值
	CString strDCData = strDCReport.Mid(14, 8);
	float fDCData = CString_To_Float(strDCData);
	strDCData.Format(_T("%.8f"), fDCData);
	long nRange = CString_To_long(strDCReport.Mid(12, 2));
	if(strDCReport.Mid(22, 2) == _T("49"))
	{
		m_pReport->AddNewData(DKSOURCE_PARA_ID_Range, DKSource_IRange_To_DCStr(nRange));
		m_pReport->AddNewData(DKSOURCE_PARA_ID_DC_I,strDCData);
		m_pReport->AddNewData(DKSOURCE_PARA_ID_DC_U,_T("0.00"));
	}
	else
	{
		m_pReport->AddNewData(DKSOURCE_PARA_ID_Range,  DKSource_URange_To_DCStr(nRange));
		m_pReport->AddNewData(DKSOURCE_PARA_ID_DC_U,strDCData);
		m_pReport->AddNewData(DKSOURCE_PARA_ID_DC_I,_T("0.00"));
	}

	//填写交流电压电流值
	CString strUa = CString_To_Float_Str(strACReport.Mid(32, 8));
	CString strUb = CString_To_Float_Str(strACReport.Mid(40, 8));
	CString strUc = CString_To_Float_Str(strACReport.Mid(48, 8));
	CString strIa = CString_To_Float_Str(strACReport.Mid(56, 8));
	CString strIb = CString_To_Float_Str(strACReport.Mid(64, 8));
	CString strIc = CString_To_Float_Str(strACReport.Mid(72, 8));
	m_pReport->AddNewData(DKSOURCE_PARA_ID_Ua, strUa);
	m_pReport->AddNewData(DKSOURCE_PARA_ID_Ub, strUb);
	m_pReport->AddNewData(DKSOURCE_PARA_ID_Uc, strUc);
	m_pReport->AddNewData(DKSOURCE_PARA_ID_Ia, strIa);
	m_pReport->AddNewData(DKSOURCE_PARA_ID_Ib, strIb);
	m_pReport->AddNewData(DKSOURCE_PARA_ID_Ic ,strIc);
}

BOOL CSourceDK51E1::RunProcedure(tagDKSource* pDKSource, long nParamNum)
{
	long nIdx = DKSource_Str_To_Idx(m_strCurProcedure, nParamNum);
	CString strData;

	switch(nIdx)
	{
	case DKSOURCE_PROCEDURE_AC_SETGEAR: strData = SetACGear(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETRANGE: strData = SetACRange(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETPHASE: strData = SetACPhase(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETFREQ: strData = SetACRate(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETPRINCIPLE: strData = SetACPrinciple(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_ENABLELOOP: strData = SetACEnableLoop(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETVERIFICATION: strData = SetACVerification(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETACTIVEPOWER: strData = SetACActivePower(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETREACTIVEPOWER: strData = SetACReactivePower(pDKSource); break;
	case DKSOURCE_PROCEDURE_DC_SETMEASUREMENTRANGE: strData = SetDCRange(pDKSource); break;
	case DKSOURCE_PROCEDURE_DC_SETMEASUREMENTTYPE: strData = SetDCMeasurementType(pDKSource); break;
	case DKSOURCE_PROCEDURE_DC_SETRANGE: strData = SetDCAmp(pDKSource); break;
	case DKSOURCE_PROCEDURE_DC_SETGEAR: strData = SetDCGear(pDKSource); break;
	case DKSOURCE_PROCEDURE_SYS_SETMODE: strData = SetSysMode(pDKSource); break;
	case DKSOURCE_PROCEDURE_SYS_SETPAGE: strData = SetSysPage(pDKSource); break;
	case DKSOURCE_PROCEDURE_REMOTE_SETOUTPUTSTATE: strData = SetRemoteOutput(pDKSource); break;
	case DKSOURCE_PROCEDURE_REMOTE_SETCONTROL: strData = SetRemoteControl(pDKSource); break;
	case DKSOURCE_PROCEDURE_AC_SETHARMONICPARAM: strData = SetACHarmonicParam(pDKSource); break;
	default:
		break;
	}

	long nLen = 0;
	Generate(nIdx, strData, nLen);
	BYTE* strMsg = m_strData;
	long nRes = SendData(strMsg, nLen);
	if(nRes == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("串口发送异常,测试仪命令发送失败!"));
		return FALSE;
	}
	return TRUE;
}

CDataGroup* CSourceDK51E1::ParseBuffer()
{
	CDataGroup* pDataGroup = new CDataGroup;

	switch(DKSource_Str_To_Idx(m_strCurProcedure))
	{
	case DKSOURCE_PROCEDURE_AC_GETERROR: GetACError(pDataGroup); break;
	case DKSOURCE_PROCEDURE_DC_GETPARAM: GetDCParam(pDataGroup); break;
	case DKSOURCE_PROCEDURE_AC_GETPARAM: GetACParam(pDataGroup); break;
	case DKSOURCE_PROCEDURE_DC_GETMEASUREMENTPARAM: GetDCMeasurementParam(pDataGroup); break;
	case DKSOURCE_PROCEDURE_REMOTE_GETINPUTSTATE: GetRemoteInputState(pDataGroup); break;
	default:
		break;
	}

	return pDataGroup;
}