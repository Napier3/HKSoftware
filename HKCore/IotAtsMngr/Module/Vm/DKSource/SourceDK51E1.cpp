#include "stdafx.h"
#include "SourceDK51E1.h"
#include "..\..\..\..\Module\System\TickCount32.h"

CSourceDK51E1::CSourceDK51E1()
{
	//�豸�������Թ̶�
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
		GetSerialAttributes();//�˴�getʵ�����ǳ�ʼ��DCB
		SetSerialAttributes(m_nBaudRate, m_nByteSize, m_nStopBits, m_nParity);
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("���������ӳɹ�!"));
		m_bIsConnected = TRUE;
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("����������ʧ��!"));
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
	//���ǰ6λ
	m_strData[0] = 0x81;
	m_strData[1] = m_nRxID;
	m_strData[2] = m_nTxID;
	m_strData[3] = 0;
	m_strData[4] = 0;
	//��ȡprocedure��Ӧ��Э���е�id,����33H
	long nData5 = 0;
	HexToLong(DKSource_Idx_To_Code(nProcedureID), nData5);
	m_strData[5] = nData5;

	//����Э���ж�Ӧ��data��Ϣ
	for (int i = 0; i < strData.GetLength(); i++)
	{
		long nTemp = 0;
		HexToLong(strData.Mid(2 * i, 2).GetString(), nTemp);
		m_strData[6 + i] = nTemp;
	}

	//���㳤��,�ߵ�λ�任
	long nLen = strData.GetLength() / 2 + 7;
	unsigned long uLen = ntohs(nLen);
	CString strLenth;
	long nLenthTemp = 0;
	strLenth.Format(_T("%.4x"), uLen);
	HexToLong(strLenth.Mid(0, 2).GetString(), nLenthTemp);
	m_strData[3] = nLenthTemp;
	HexToLong(strLenth.Mid(2).GetString(), nLenthTemp);
	m_strData[4] = nLenthTemp;;

	//�������У��
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
	//Э���жԴ�flagֻ�ᵽ�������������
	//�� Fa=Fb!=Fc ʱ��Flag=2��Fa=Fb=Fc ʱ��Flag=3
	//����ʱ Fa=Fb��Fc ��������Ϊ�� AB �಻ͬ��Ƶ�ʡ�Ҳ����ֻ���� Fa����Ĭ��Ϊ
	//����ͬƵ�����ڼ�����ǰ���豸ͨѶ����
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
	//ʹ��m_nMode,�߼���GetSysModeһ��
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
	Type �C ����У�����ͣ���P��- �й��� ��Q��- �޹�
	MPC �C ���й����ܳ�������Χ��1.0~599999999.0��4 ���ֽڵĸ���������
	MQC �C ���޹����ܳ�������Χ��1.0~599999999.0��4 ���ֽڵĸ���������
	SPC �C Դ�й����ܳ�������Χ��1.0~599999999.0��4 ���ֽڵĸ���������
	SQC �C Դ�޹����ܳ�������Χ��1.0~599999999.0��4 ���ֽڵĸ���������
	MDIV �C ��Ƶϵ������Χ��1~9999999��4 ���ֽڵ��޷����������ݣ����ֽ���ǰ
	MROU �C У��Ȧ������Χ�����ڵ��� 1��4 ���ֽڵ��޷����������ݣ����ֽ���ǰ
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
	Type�����ͣ���U��-��ѹ����I��-������
	Range ��ֱ��Դ��λ��1 ���ֽ�
	SData��ֱ��Դ��ֵ��4 ���ֽڱ�ʾ�ĸ��������ݡ�
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
	Mode��0-��׼Դ��1-��׼��2-��׼��ǯ��
	10-��׼ԴУ׼ģʽ��11-��׼��У׼ģʽ��12-ǯ�α�У׼ģʽ
	13-ֱ��ԴУ׼ģʽ��14-ֱ����У׼ģʽ
	*/
	CString strMode;
	strMode.Format(_T("%.2x"), pDKSource->m_nMode);
	return strMode;
}

CString CSourceDK51E1::SetSysPage(tagDKSource* pDKSource)
{
	/*
	1-��׼�����
	2-��λ�����
	3-ʸ����ʾ��
	4-г�����ã�
	5-ֱ��������
	6-ֱ������� 
	8-����У�飻
	9-����������
	10-��λ������
	11-ʸ����ʾ��
	12-����������
	13-��λ������
	14-ʸ����ʾ
	ע�⣺��������ʵ�ʲ��������ƹ���Ҫ����������ܽ���Ĳ��ֽ���
	*/
	CString strPage;
	strPage.Format(_T("%.2x"), pDKSource->m_nPage);
	return strPage;
}

CString CSourceDK51E1::SetDCRange(tagDKSource* pDKSource)
{
	/*
	Type�����ͣ���U��-��ѹ����I��-������
	Range ��ֱ��Դ��λ��1 ���ֽ�
	SData��ֱ��Դ��ֵ��4 ���ֽڱ�ʾ�ĸ��������ݡ�
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
	Type�����ͣ���U��-��ѹ����I��-������
	Range Ϊ 1 �ֽڵĵ�λ��
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
	Channel��ͨ��ѡ����λѡ��D0-Ua,D1-Ub,D2-Uc,D3-Ia,D4-Ib,D5-Ic ��1 ʱ��Ч
	Count��Ҫ���õ�г������(��1)��Э�鳤�� Length ������ı仯���仯��1 ���ֽ�����
	Count =0 ʱ���ָ��ͨ�������д�����г��
	Harmonic - г����������Χ�� 2 ~ 32 ��1 ���ֽ�����
	Amplitude - г�����ȣ���Χ�� 0 ~ 0.4��4 ���ֽڵĸ���������
	Angle - г����λ����Χ�� 0��~ 359.99�㣬4 ���ֽڵĸ���������
	ע�⣺Э���й涨��Э�鳤�ȳ���256���������ʵ�ʲ��Ա����в�����Ҫ��ô�࣬����
	ֻ���ù̶�����
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
	Flag Ϊ 1 �ֽڵĵ��������Ч��־λ
	Flag = 0 ��ʾ EV ֵ��Ч��
	Flag = ��P�� ��ʾ EV ֵΪ�й�����У����
	Flag = ��Q�� ��ʾ EV ֵΪ�޹�����У�����

	EV Ϊ 4 ���ֽڵĸ��������ݣ���λ��%
	ROUND Ϊ��ǰУ��Ȧ����4 ���ֽڵ��޷����������ݣ����ֽ���ǰ
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
	Type�����ͣ���U��-��ѹ����I��-���������ｫ������ѹһ��д��
	Range ����ǰֱ��Դ��λ��1 ���ֽ�
	DCData��ֱ��Դ��ֵ��4 ���ֽڱ�ʾ�ĸ���������
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
	//��ȡƵ��
	CString strF = CString_To_Float_Str(m_strBuffer.Mid(12, 8));
	//��ȡ��ѹ������λ
	long nUaRange = 0, nUbRange = 0, nUcRange = 0, nIaRange = 0, nIbRange = 0, nIcRange = 0;
	HexToLong(m_strBuffer.Mid(20, 2).GetString(), nUaRange);
	HexToLong(m_strBuffer.Mid(22, 2).GetString(), nUbRange);
	HexToLong(m_strBuffer.Mid(24, 2).GetString(), nUcRange);
	HexToLong(m_strBuffer.Mid(26, 2).GetString(), nIaRange);
	HexToLong(m_strBuffer.Mid(28, 2).GetString(), nIbRange);
	HexToLong(m_strBuffer.Mid(30, 2).GetString(), nIcRange);
	//��ȡ��ѹ������λֵ
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
	//��ȡ����ֵ
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
	//������һ���ϱ������������
	if (m_pReport)
	{
		delete m_pReport;
		m_pReport = NULL;
	}

	m_pReport = new CDataGroup;

	//��дֱ����ѹ����ֵ
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

	//��д������ѹ����ֵ
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
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("���ڷ����쳣,�����������ʧ��!"));
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