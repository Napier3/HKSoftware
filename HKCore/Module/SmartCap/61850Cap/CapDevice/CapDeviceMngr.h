//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceMngr.h  CCapDeviceMngr

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"
#include "../../../Record/MR1200BaseApp.h"
#include "../../../MemBuffer/TCycleMemBuffer.h"

//������¼���������͵ĵ�ǰģ����ͨ����������ʱ����������
#define PKG_TIMEDATA_MEMBUFFER_MAX_NUM              1000


class CCapDeviceMngr : public CExBaseList
{
public:
	CCapDeviceMngr();
	virtual ~CCapDeviceMngr();

	void GetSttCapParas(CCapDeviceBase *pCapDeviceBase, CDataGroup *pSttParas, BOOL bUseSmv
		, BOOL bUseGoose,BOOL bUseFT3);
	void GetSttCapParas(CDataGroup *pSttParas, BOOL bUseSmv, BOOL bUseGoose,BOOL bUseFT3);
	void SetRecordTest(CRecordTest *p)	{	m_pRecordTest = p;	}

	void UnselectAllCap(BOOL bSmv, BOOL bGoose,BOOL bFT3);
	BOOL IsFT3Rcd();//�жϵ�ǰ�Ƿ�ΪFT3¼��ģʽ

	//2023.10.26 zhouhj
//	void UpdateSeletStateAllCap(BOOL bSmv92Sel, BOOL bGooseSel,BOOL bFT3_Sel);
//���غ���
public:
	void ResetTimeDataList();
	//zhouhj 2024.3.27 ��Ӻϲ���Ԫ����ģ����ʱ������
	void AddMUTimeData(int nTimeDataCh,__int64 n64TimeData);

	//��¼���ձ���ʱ,���͵�ģ���������ʱ���Ӧ��ʱ��
	CTCycleMemBuffer<__int64> m_oTimeDataList;
	//���λ�ֽڶ�Ӧ���������Դ���,ȡֵ:1-48
	//������2�ֽڶ�Ӧ���������Դ����,0-��ѹ  1-����
	int m_nTimeDataCh;//�������͵�ģ����ͨ����Ӧ�ĵ�ѹ������������ԴIndex

//˽�г�Ա����
private:
	CRecordTest *m_pRecordTest;  

//˽�г�Ա�������ʷ���
public:
	CCapDeviceBase* FindCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	CCapDeviceBase* AddCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	
	CCapDeviceBase* FindCapDevice(PEPCAPBUFFERITEM pItemData);
	CCapDeviceBase* FindCapDevice(UINT nAppID, 
		const CString &strDetectPkgType,long nPort);//20220609 zhouhj ����2Ϊ̽�ⱨ������,���ײ㷵�صı��������ַ�
	CCapDeviceBase* AddCapDevice(PEPCAPBUFFERITEM pItemData);
	CCapDeviceBase* AddCapDevice(CDataGroup *pSttIecCb);
	void InitNameAndID(CCapDeviceBase *pCapDevice);
	CCapDeviceBase* FindCapDevice(CDvmDataset *pDataset); //2022-5-26 
	CCapDeviceBase* FindCapDevice(CDataGroup *pSttIecCb);
	long GetDeviceCount(long nClassID);
	void ClearAllIecfgAttach();
	long GetSmpRate_FT3();

	//zhouhj 2023.10.30  ��֤FT3���ƿ�ͨ������
	BOOL ValidSelectFT3CB_PkgLenth();
	BOOL ValidSelectFT3CB_PkgLenth(long nFt3CrcType);//20240802 suyang ����CRC���� 0-��׼16�ֽ�У�飬1-����ĩβУ�飬2-��һ�����ݿ�14�ֽ�У��

	//��֤ST��ģʽ�Ƿ���ȷ
	BOOL ValidSTMode();

	//��ʼץ������λ֮ǰ��״̬  2020-06-19  lijunqing
	void Reset();  

	//���ڸ���װ������״̬  2020-06-27  lijunqing
	void UpdateDeviceLinkState();
	void SelectDevicesByLink(CExBaseList &list, UINT nClassID, BOOL bLink);

	//2022-5-3  lijunqing
	void ClearCap();
	void ClearPara();

	//2022-12-25  lijunqing
	CCapDeviceBase* GetSelectDevice();
	long GetSelectDeviceCount(UINT uClassID = 0);
};

#include "../../../OSInterface/XWndInterface.h"
extern CXWndInterface *g_theCapDeviceMngrMsgRcvWnd;