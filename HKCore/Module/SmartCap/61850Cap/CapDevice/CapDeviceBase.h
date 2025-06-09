//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceBase.h  CCapDeviceBase

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceChBase.h"
#include "../ProtocolBase/ProtocolGlobalDef.h" 

#include "../ProtocolBase/Protocol61850Analysis.h"


#include "../../../../Module/MemBuffer/CycleMemBuffer.h"
//#include "../CapGlobalDef.h"
#include "../../../Record/RtMemBuffer/MemBuffer.h"

#include "../../../../61850/Module/CfgDataMngr/IecCfgDevice.h"

//SOE  lijunqing 2020-6-20
#include "../../../../Module/BaseClass/ExBaseCycleArray.h"
#include "../../../System/TickCount32.h"
#include "CapAnalysisConfig.h"

//�Ƿ�¼����״̬
//ץ����ʼ�󣬽���״̬���ݣ����ǲ�¼�����ݣ���ʼ¼������¼������

extern BOOL g_bSmartCap_RecordNow; 
extern BOOL _CAL_DELAY_TIME_USE_SAMPLECOUNT_;

// #include <vector>
// #include <map>
// 
// 
// typedef std::map< long, CCapDeviceChBase> CCapDeviceChMap;
// typedef std::map< long, CCapDeviceChBase>::iterator CCapDeviceChIter;


//ץ���豸������ʱ���� = ̽�⵽�Ķ���
class CCapDeviceBase : public CExBaseList
{
public:
	CCapDeviceBase();
	virtual ~CCapDeviceBase();

	virtual void GetSttCapParas(CDataGroup *pSttParas);

	BYTE m_byteSrcMac[6];
	BYTE m_byteDestMac[6];
	DWORD m_dwAppID;
	UINT m_nType;
	
	CString m_strDestAddress;
	CString m_strSrcAddress;
	
	//2022-4-13  lijunqing
	CString m_strCRC;
	CString m_strPkgDetect;
	CString m_strPkg;

	//m_oBuffer�������豸�����ƿ��һ�����ģ������ڽ����豸�Ļ�����Ϣ
	CCycleMemBuffer m_oBuffer;

	//m_pDeviceInforFrame���豸������Ϣ�ı�����ϸ��Ϣ����m_oBuffer�Ľ���
	CExBaseObject *m_pDeviceInforFrame; 

	__int64 m_n64CapDataIndex;
	long m_bSelect;

	long m_nFillBeginPos;//װ�ù���������ץ��ͨ�������ݻ�����ʼλ��
	long m_nDatasCount;  //��������
	
	CMemBuffer_Double m_oCapTimeBuffer;
// 	CCapDeviceChMap m_RecordChMap;
// 	CCapDeviceChMap m_RecordChMapRemove;
	char  m_destIn[100];
	unsigned char m_destOut[50];
	//yyj
	long m_nFiberIndex;		//�������
	long m_nMatchState;		//0-��ʼδƥ�䣻-ƥ��ɹ���-���ࣻ-ȱ��
	long m_bLinkState;       //����״̬  0=�Ͽ�   1=����

	void AttachIecCfgData(CIecCfgDataBase *pCfgDataBase);
	CIecCfgDataBase* GetIecCfgData()	{	return m_pIecCfgData; }
	CDvmDataset* GetDvmDataset()	{	return m_pRefDvmDataset; }
	void SetDvmDataset(CDvmDataset *pDvmDataset)	{	m_pRefDvmDataset = pDvmDataset; }

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas){};
	void SetChannelState(PEPCAPPARSEDATAS pParseDatas);

	EPCAPPARSEDATAS m_oPrevDatas;   // mym 2020-6-17 ���ڴ洢���ڱȽϵ�ǰһ֡�����ݣ�
	EP_ANALYSIS_RESULT m_oAnalysisResults;
	long m_nCurrErrorTypeNum;//zhouhj 2024.4.10 ��¼��ǰ�����������,���ڽ��涨ʱˢ��ʱ,����������������仯��,ʵʱͳ��

	void ep_consistence_analysis92(); // mym 2020-6-23 ��鱨��һ����
	void ep_consistence_analysisGS( );// mym 2020-6-23 ��鱨��һ����

//	long GetChIndexBySelectChIndex(long nSelectIndex);
//	long GetSelectChIndexByChIndex(long nChIndex);

	DWORD m_dwFlagSVCstc[STCAPPARSE_CONSISTENCY_COUNT];
	DWORD m_dwFlagGSCstc[STCAPPARSE_CONSISTENCY_COUNT];
	double m_dMaxTimeDiscrete ;  //SV��ɢ�ȣ�
	double m_dGOOSESyn ;           //GOOSEͬ���

	double  m_dTime1[256];//���ﶨΪ256��ͨ����mym 
	double  m_dTime2[256];

	double  m_dSOETime1;
	double  m_dSOETime2;
	double  m_dSOETime3;




	//˽�г�Ա����
protected:
	virtual CCapDeviceChBase* CreateChannel() = 0;
	CIecCfgDataBase *m_pIecCfgData;		//��Ӧ�Ŀ��ƿ�����
	CTickCount32 m_oTickCount;
	CDvmDataset *m_pRefDvmDataset; //�������豸����ģ�����ݼ�

//˽�г�Ա�������ʷ���
public:
	virtual BOOL SetChannelNum(long nChannelNum);
	BOOL Compare(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	virtual BOOL Compare(PEPCAPBUFFERITEM pItemData);
	void Iinit(PEPCAPBUFFERITEM pItemData);
	BOOL IsSameType(long nType);
	virtual void InitNameAndID(long nTypeCount);
	virtual void UpdateErrorTypeNum();//�����쳣��������

	void InitAddress();
	void InitIecfgData(CIecCfgDataBase *pIecCfgData);

	//�������ƿ���Ϣ�����ĸ�����װ����Ϣ
	void ParseDeviceInfor();

	void InitDevice(PEPCAPPARSEDATAS pDatas);

	//��ӱ������ݵ�¼��ͨ����
	void AddCapDataBuffer(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	void CapRecord(PEPCAPPARSEDATAS pDatas);  //2022-6-19  lijunqing
	void SetCapSelect(BOOL bSelect);

	virtual void Reset();  //��ʼץ������λ֮ǰ��״̬
	virtual BOOL IsDataRcvOverTime();

	//2020-6-20  lijunqing  ����ͻ����߱仯��
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0)	{};
	virtual void CreateDvmDataset(CDvmDataset *pDataset);

	//shaolei 20220427  
	virtual void UpdateDvmDeviceDatas();

	virtual void analysis92(PEPCAPPARSEDATAS pDatas);
	virtual void analysis_gs(PEPCAPPARSEDATAS pDatas);
	virtual void analysis6044(PEPCAPPARSEDATAS pDatas);

	//2022-5-3  lijunqing
	virtual void ClearCap();
	virtual void ClearAnalysisResultErrors(){};//20220614 zhouhj������Խ���еĴ���
	CString GetCtrlDesc();//��ȡ���ƿ����� 20230301 
	virtual void SetDeviceChMaps(){}//20230710 zhouhj ����ͨ��ӳ�� 
};

void cap_mac_string_to_byte(const CString &strMac, BYTE *pMAC);
CString GetMacStringFromByte(const unsigned char *pMacAddr);

//lijunqing 2020-6-20  ��ʱʹ��ȫ�ֱ�����¼SOE���棬���������Ҫ����豸����ģ�ͣ������޸�
extern CExBaseCycleArray *g_pSmartCapSoeCycleArray;
extern CExBaseCycleArray *g_pSmartCapBinCycleArray;