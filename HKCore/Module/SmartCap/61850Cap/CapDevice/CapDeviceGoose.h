//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceGoose.h  CCapDeviceGoose

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"
#include "CapDeviceGooseCh.h"

class CCapDeviceGoose : public CCapDeviceBase
{
public:
	CCapDeviceGoose();
	virtual ~CCapDeviceGoose();

	long  m_dwVID;
	long  m_dwVersion;
	CString  m_strGooseId;
	CString  m_strDataSet;
	CString  m_strDataSetDesc;
	CString  m_strgocbRef;
	CString  m_strgocbIED;
	long  m_nTest;
	long  m_dwTimeAllowToAlive;
	long m_dwStNum;
	long m_dwSqNum;
	long m_dwNdsCom;
	double m_dTime;
	
	//2022-5-31  lijunqing ÿ��goose�豸����������
	CEpGooseBinaryTurns m_oBinaryTurns;
	CWnd *m_pXWndInterface;  //��ͼ���Ӵ���ָ��

//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICEGOOSE;};

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceGooseCh();	}

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas);

	//2020-6-20  lijunqing  ����ͻ����߱仯��
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	virtual BOOL IsDataRcvOverTime();

	//shaolei 20220427
	virtual void UpdateDvmDeviceDatas();
	void UpdateDvmDeviceDatasType(UINT nType, UINT nLen, CString&strValue);//20240704 suyang ���Ӷ������жϣ�����ͨ����������


	virtual void ClearAnalysisResultErrors();

	virtual void Reset();  //��ʼץ������λ֮ǰ��״̬
	void AttachXWndInterface(CWnd *pWnd)	{	m_pXWndInterface = pWnd;	}
	//2023.6.2 zhouhj ���ݵ�ǰ̽�ⱨ����Ϣ,����IEC���ò�����Ϣ
	void SetIecCfgGin_ByCapDevice(CIecCfgGinData* pIecCfgGinData);
	void SetIecCfgGout_ByCapDevice(CIecCfgGoutData* pIecCfgGoutData);

};

