#include "stdafx.h"
#include "TcpEdgePrcdr_Auth.h"
#include "TcpEdgeServer.h"
#include "Pkg/TcpEdgeAuth_0x02.h"
#include "SM2/sm2_sign_and_verify.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
#include <QDebug>

CTcpEdgePrcdr_Auth::CTcpEdgePrcdr_Auth()
{
	nAuthCount = 0;
}

CTcpEdgePrcdr_Auth::~CTcpEdgePrcdr_Auth()
{

}

BOOL CTcpEdgePrcdr_Auth::RunStepNull()
{
	//�������ó�ʱ
	ResetTimer();
	SetProcedureState(PrcdrState_Step_1);
	m_nOverTimeLong = 30000;
	return FALSE;
}

BOOL CTcpEdgePrcdr_Auth::RunStep1()
{
	//����Ƿ�ʱ
	if (IsTimerOut(GetTickCount()))
	{
		SetResultEvent(RUNPROCEDURE_EVENT_CommOverTime);
		SetProcedureState(PrcdrState_Step_End);
		emit sig_updateViewPkg(m_strIP, "��֤���̳��ֳ�ʱ!", 0);
		return TRUE;
	}

	//�������б�,����ǰӦ���ģ�����TRUE,���򷵻�FALSE
	return ProcessRecvPkgs();
}

//����Ӧ�����߼�
BOOL CTcpEdgePrcdr_Auth::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	if(pPkgDetail->m_strCmdID == "0x01")
	{
		QString strLog = QString("ȷ�ϵ��豸ͨ��[%1]�ļ�Ȩ��֤����...").arg(pPkg->m_nPort);
		m_strDeviceID = pPkg->m_strName;
		emit sig_updateViewPkg(m_strIP, strLog, 0);
		ProcessAuth(pPkgDetail);	
	}
	else if(pPkgDetail->m_strCmdID == "0x03")
	{
		QString strLog = QString("�豸ͨ��[%1]��Ȩ��֤�ɹ�...").arg(pPkg->m_nPort);
		emit sig_updateViewPkg(m_strIP, strLog, 0);
		nAuthCount++;
		if(nAuthCount == 2)
		{
			//�����ǲ�ѯ��Ӧ,�����ù���
			emit sig_updateViewPkg(m_strIP, "�豸��Ȩ��֤�ɹ�...", 0);
			ProcessPackageFinished(pPkgDetail);
			return TRUE;
		}
	}

	pPkgDetail->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_1);

	return FALSE;
}

BOOL CTcpEdgePrcdr_Auth::RunProcedure_Auth(CPxPkgBase *pPkgDetail)
{
	//��Ȩ����ֻ��Ҫ����Prcdr,Ȼ��ȴ���λ�����ͱ��Ĺ���
	return TRUE;
}

BOOL CTcpEdgePrcdr_Auth::ProcessAuth(CPxPkgBase *pPkgDetail)
{
	//��Ȩ���̵�Ӧ��
	CTcpEdgeAuth_0x02* pTcpEdgeAuth = new CTcpEdgeAuth_0x02;
	CTcpEdgeDevice* pDevice = (CTcpEdgeDevice*)m_pTcpProtocolRef->m_pDevice;

	if(pDevice == NULL)
	{
		return FALSE;
	}

	//lmy��20230830�޸Ĳ������ͣ��ڸ���ʾ���Ĳ���ʱ������ԭ���������2�������Ĳ�̫�ԣ��ʶ��޸�
	char *pszRand2 = new char[8];
	pTcpEdgeAuth->CreateRandNum2(pszRand2);

	//�����ɵ���������浽m_pDevice->m_byteRecvR2��
	for(int i=0; i<8; i++)
	{
		pDevice->m_byteRecvR2[i] = (BYTE)pszRand2[i];
	}
	delete pszRand2;

	BYTE pPkgValue[64] = {0};
	BYTE* pPkg02 = pTcpEdgeAuth->CreateAuthPkg("����Ե���ز���ƽ̨", pDevice->m_byteRecvR1, 
		pDevice->m_byteRecvR2, pPkgValue);

	BYTE pkgHead[32] = {0};
	pkgHead[0] = pkgHead[2] = 0xEB;
	pkgHead[1] = pkgHead[3] = 0x90;

	long nLen = 145;
	pkgHead[4] = nLen >> 8;
	pkgHead[5] = nLen;
	pkgHead[6] = 0x02;
	long nSignLen = 0;

	if(pDevice->m_bSign)
	{
		pkgHead[6] |= 0x01;
		nSignLen = 64;
	}
	pkgHead[7] = 0x00;

	for (int i = 0; i< m_strDeviceID.GetLength(); i++)
	{
		pkgHead[8 + i] = m_strDeviceID.GetAt(i);
	}

	pkgHead[31] = 0x00;

	BYTE* pPkg = new BYTE[32 + 145 + nSignLen];
	for (int i = 0; i < 32; i++)
	{
		pPkg[i] = pkgHead[i];
	}
	for (int i = 0; i < 145; i++)
	{
		pPkg[i + 32] = pPkg02[i];
	}

	nLen = 32 + nLen + nSignLen;

	BYTE pPublicKey[65] = {0x04,0x9c,0x43,0xb0,0x6e,0x16,0x8e,0x5b,0xf6,0xe6,0x8e,0x4d,0xf1,0xd7,0x5b,0x54,0x30,0x6b,0xeb,0x82,0x25,0x8a,0xa1,0x4e,0xa0,0x05,0xf2,0xac,0xba,0x5a,0xbf,0xbb,0x08,0xc0,0x7b,0xba,0xbb,0x74,0x88,0x84,0x22,0xd4,0xce,0x26,0x14,0x2e,0xde,0xdd,0x78,0xba,0xa4,0xb6,0x3b,0x7f,0xa2,0x77,0x75,0xf8,0x75,0xc1,0x88,0x34,0xd9,0xb7,0xb7};
	BYTE pPrivateKey[32] = {0x29,0xe1,0x8a,0xf5,0xb3,0x3a,0x9a,0x69,0xf0,0xb8,0xdd,0x2a,0x97,0x14,0x03,0x5d,0xa5,0xdc,0x59,0xca,0x4b,0xcf,0x84,0x44,0x68,0xd5,0xe0,0x67,0x46,0x32,0x6e,0xd0};
	SM2_SIGNATURE_STRUCT sm2;
	CString strName = "1234567812345678";
	sm2_sign_data(pPkg, nLen - nSignLen - 64, (const unsigned char*)strName.GetString(), 16, pPublicKey, pPrivateKey, &sm2);
	
	memcpy(pPkg + 113, sm2.r_coordinate, 32);
	memcpy(pPkg + 145, sm2.s_coordinate, 32);

	if(pDevice->m_bSign)
	{
		tcp_edge_sm2_cal(pPkg, 177, sm2, pPkg + 177);
	}

	CTickCount32 event;
	event.DoEvents(1000);

	pDevice->Send(((CTcpEdgePkg*)pPkgDetail)->m_nPort, pPkg, m_strID, 177 + nSignLen);

	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_Auth);
	CString strPkg;
	for (int i = 0; i < 145 + 32; i++)
	{
		QString strTemp = QString("%1 ").arg(pPkg[i] & 0xff, 2, 16, QLatin1Char('0'));
		strTemp = strTemp.toUpper();
		strPkg += strTemp;
	}

	CDvmValue* pValue = m_pTcpProtocolRef->UpdateDataset(pDataset, "0x02", strPkg);
	pValue->m_dwItemData = -1;
	pValue->m_dwReserved = ((CTcpEdgePkg*)pPkgDetail)->m_nPort;
	return TRUE;

	//��¼һ����ô��֤���ȡSM2��˽Կ�͹�Կ(P12֤��)
	//1. openssl pkcs12 -nocerts -nodes -in xxx.p12 -out xxx.key
	//2. openssl ec -in xxx.key -noout -text
	//������������������������������������������������������
	//read EC key
	//Private-Key: (256 bit)
	//priv:
	//    29:e1:8a:f5:b3:3a:9a:69:f0:b8:dd:2a:97:14:03:
	//    5d:a5:dc:59:ca:4b:cf:84:44:68:d5:e0:67:46:32:
	//    6e:d0
	//pub:
	//	04:9c:43:b0:6e:16:8e:5b:f6:e6:8e:4d:f1:d7:5b:
	//	54:30:6b:eb:82:25:8a:a1:4e:a0:05:f2:ac:ba:5a:
	//  bf:bb:08:c0:7b:ba:bb:74:88:84:22:d4:ce:26:14:
	//	2e:de:dd:78:ba:a4:b6:3b:7f:a2:77:75:f8:75:c1:
	//	88:34:d9:b7:b7
	//ASN1 OID: SM2
	//������������������������������������������������������
	//
	//����SM2�ǻ���ECC���ģ�������ec��ʽ��key
	//����SM2��֤���ļ��ڲ�������openssl�°汾�Ĺ涨��openssl�����ʧ�ܱ���
	//������openssl�汾�����ϰ�1.1.1
	//
}