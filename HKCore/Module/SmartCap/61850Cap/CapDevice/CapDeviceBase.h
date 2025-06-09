//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//是否录波的状态
//抓包开始后，解析状态数据，但是不录波数据，开始录波后，再录波数据

extern BOOL g_bSmartCap_RecordNow; 
extern BOOL _CAL_DELAY_TIME_USE_SAMPLECOUNT_;

// #include <vector>
// #include <map>
// 
// 
// typedef std::map< long, CCapDeviceChBase> CCapDeviceChMap;
// typedef std::map< long, CCapDeviceChBase>::iterator CCapDeviceChIter;


//抓包设备对象，临时对象 = 探测到的对象
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

	//m_oBuffer：保存设备（控制块的一个报文），用于解析设备的基础信息
	CCycleMemBuffer m_oBuffer;

	//m_pDeviceInforFrame：设备数据信息的报文详细信息，对m_oBuffer的解析
	CExBaseObject *m_pDeviceInforFrame; 

	__int64 m_n64CapDataIndex;
	long m_bSelect;

	long m_nFillBeginPos;//装置关联的所有抓包通道的数据缓冲起始位置
	long m_nDatasCount;  //数据数量
	
	CMemBuffer_Double m_oCapTimeBuffer;
// 	CCapDeviceChMap m_RecordChMap;
// 	CCapDeviceChMap m_RecordChMapRemove;
	char  m_destIn[100];
	unsigned char m_destOut[50];
	//yyj
	long m_nFiberIndex;		//光口索引
	long m_nMatchState;		//0-初始未匹配；-匹配成功；-多余；-缺少
	long m_bLinkState;       //链接状态  0=断开   1=链接

	void AttachIecCfgData(CIecCfgDataBase *pCfgDataBase);
	CIecCfgDataBase* GetIecCfgData()	{	return m_pIecCfgData; }
	CDvmDataset* GetDvmDataset()	{	return m_pRefDvmDataset; }
	void SetDvmDataset(CDvmDataset *pDvmDataset)	{	m_pRefDvmDataset = pDvmDataset; }

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas){};
	void SetChannelState(PEPCAPPARSEDATAS pParseDatas);

	EPCAPPARSEDATAS m_oPrevDatas;   // mym 2020-6-17 用于存储用于比较的前一帧的数据；
	EP_ANALYSIS_RESULT m_oAnalysisResults;
	long m_nCurrErrorTypeNum;//zhouhj 2024.4.10 记录当前误差类型数量,用于界面定时刷新时,发现误差类型数量变化后,实时统计

	void ep_consistence_analysis92(); // mym 2020-6-23 检查报文一致性
	void ep_consistence_analysisGS( );// mym 2020-6-23 检查报文一致性

//	long GetChIndexBySelectChIndex(long nSelectIndex);
//	long GetSelectChIndexByChIndex(long nChIndex);

	DWORD m_dwFlagSVCstc[STCAPPARSE_CONSISTENCY_COUNT];
	DWORD m_dwFlagGSCstc[STCAPPARSE_CONSISTENCY_COUNT];
	double m_dMaxTimeDiscrete ;  //SV离散度；
	double m_dGOOSESyn ;           //GOOSE同步差；

	double  m_dTime1[256];//这里定为256个通道；mym 
	double  m_dTime2[256];

	double  m_dSOETime1;
	double  m_dSOETime2;
	double  m_dSOETime3;




	//私有成员变量
protected:
	virtual CCapDeviceChBase* CreateChannel() = 0;
	CIecCfgDataBase *m_pIecCfgData;		//对应的控制块配置
	CTickCount32 m_oTickCount;
	CDvmDataset *m_pRefDvmDataset; //关联的设备数据模型数据集

//私有成员变量访问方法
public:
	virtual BOOL SetChannelNum(long nChannelNum);
	BOOL Compare(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	virtual BOOL Compare(PEPCAPBUFFERITEM pItemData);
	void Iinit(PEPCAPBUFFERITEM pItemData);
	BOOL IsSameType(long nType);
	virtual void InitNameAndID(long nTypeCount);
	virtual void UpdateErrorTypeNum();//更新异常类型数量

	void InitAddress();
	void InitIecfgData(CIecCfgDataBase *pIecCfgData);

	//解析控制块信息：报文附带的装置信息
	void ParseDeviceInfor();

	void InitDevice(PEPCAPPARSEDATAS pDatas);

	//添加报文数据到录波通道中
	void AddCapDataBuffer(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	void CapRecord(PEPCAPPARSEDATAS pDatas);  //2022-6-19  lijunqing
	void SetCapSelect(BOOL bSelect);

	virtual void Reset();  //开始抓包，复位之前的状态
	virtual BOOL IsDataRcvOverTime();

	//2020-6-20  lijunqing  分析突变或者变化量
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0)	{};
	virtual void CreateDvmDataset(CDvmDataset *pDataset);

	//shaolei 20220427  
	virtual void UpdateDvmDeviceDatas();

	virtual void analysis92(PEPCAPPARSEDATAS pDatas);
	virtual void analysis_gs(PEPCAPPARSEDATAS pDatas);
	virtual void analysis6044(PEPCAPPARSEDATAS pDatas);

	//2022-5-3  lijunqing
	virtual void ClearCap();
	virtual void ClearAnalysisResultErrors(){};//20220614 zhouhj清除测试结果中的错误
	CString GetCtrlDesc();//获取控制块描述 20230301 
	virtual void SetDeviceChMaps(){}//20230710 zhouhj 设置通道映射 
};

void cap_mac_string_to_byte(const CString &strMac, BYTE *pMAC);
CString GetMacStringFromByte(const unsigned char *pMacAddr);

//lijunqing 2020-6-20  暂时使用全局变量记录SOE缓存，后续如果需要多个设备数据模型，再做修改
extern CExBaseCycleArray *g_pSmartCapSoeCycleArray;
extern CExBaseCycleArray *g_pSmartCapBinCycleArray;