#pragma once

#include "../../../Module/SmartCap/61850Cap/ProtocolBase/Pcap/FrameMemBufferMngr.h"
#include "SttPcapIecDef.h"
#include "../SttTest/Common/tmt_dig_replay_test.h"
#include "../ReplayTest/ComtradeBufMngr.h"

#define _STT_PCAP_PARSE_MAX_FRAME_NUM             700000 //最大解析的报文总帧数

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttIecCtrlBlock
{
public:
	CSttIecCtrlBlock();
	virtual ~CSttIecCtrlBlock();

	void Init();

	long m_dwAppID;//当前控制块AppID
	long m_nPkgNum;//当前控制块报文总帧数
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttIecCtrlBlocks : public CTLinkList<CSttIecCtrlBlock>
{
public:
	CSttIecCtrlBlocks();
	virtual ~CSttIecCtrlBlocks();
	void AddIecPkg(long dwAppID);
	CSttIecCtrlBlock* FindByAppID(long dwAppID);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class CSttPcapFileRead
{
public:
	CSttPcapFileRead(void);
	virtual ~CSttPcapFileRead(void);

	BOOL OpenPcapFile(const CString &strPcapFile);
	void FreeAll();
	BOOL HasPcapSendDatas();//判断当前是否包含回放数据
	void GenerateFibersDatas();//生成光口数据内容

	//填充ABBuf数据
	BOOL GenerateABBuf(int nIndex);	
	//由回放缓存ReplayBuf填充AB缓存
	BOOL GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf);
	void CalOutputTime();

	PCAP_IEC_CTRLS m_oPcapCtrls_SV;
	PCAP_IEC_CTRLS m_oPcapCtrls_GOOSE;
	tmt_DigReplayParas *m_pTmtDigReplayParas;
	PCAP_IEC_FIBERS m_oPcapFibersDatas;//所有光口的数据内容
	long m_nCurDeliverFiberIndex;//开始测试后，当前发送报文对应的PCAP_IEC_FIBER_PORT对应的Index
	long m_nCurrDeliverFiberPkgIndex;//开始测试后，当前发送报文对应的光口的PCAP_IEC_PKG对应的Index
	BOOL m_bReadFiberDatasFinish;					//读全部光口数据结束

	CFrameMemBufferMngr m_oCapBufferMngr;   //抓包报文缓冲区
	CString m_strPcapFilePath;

	void SetPkgsPlayBackDatas(long nBeginIndex,long nAllCBEndIndex);// 设置回放区间
	void PcapIecCtrls_ToDigReplayParas();//20230825 suyang 在选择全部报文回放时需要调用，改为公共的

	CString GetNetCardID(long nIndex);
	BOOL SimulateSendPcap(const CString &strNetCardID);

protected:
	BOOL FillPkgDatas(CComtradeDataBuffer *pABBuf,PCAP_IEC_FIBER_PORT *pFibers,long &nCurrDeliverFiberPkgIndex);
	long FillPkgData_Single(CComtradeDataBuffer *pABBuf,PCAP_IEC_PKG *pP_PCAP_IEC_PKG,long &nCurrDeliverFiberPkgIndex);
	//获取报文数据区长度(单位为32位,即4字节)单帧报文,参数2为是否判断为4的整数倍
	long GetPkgDataAreaLenth32bits_SinglePkg(CFrameMemBuffer *pXSmMemBuffer,BOOL bCalFourMultiple);
	//获取报文数据区长度(单位为32位,即4字节),参数2为添加改帧报文前,数据区长度，同时默认需要为4的整数倍
	long GetPkgDataAreaLenth_32bits(CFrameMemBuffer *pXSmMemBuffer,long nPrevPkgDataAreaLenth);
	void Create_PcapIecCtrls(CSttIecCtrlBlocks *pCtrlBlocks_SV,CSttIecCtrlBlocks *pCtrlBlocks_GS);
	void AttachAllXSmMemBuffer();
	//void PcapIecCtrls_ToDigReplayParas();
	void PcapIecCtrl_ToDigReplayParas(P_PCAP_IEC_CTRL pCtrl,TMT_DIG_REPLAY_CB *pCB);
	BOOL GetEthernetTypeAppID_ByXSmMemBuffer(CXSmMemBuffer *pCXSmMemBuffer,u_short &uAppID,u_short &uEthernetType);

	//生成光口数据,//参数2为光口号从0开始编号,按照此方式生成的报文需要对报文进行重新排序
	void GenerateFiberDatas_NeedSort(PCAP_IEC_FIBER_PORT *pPcapIecFiber,long nFiberPortIndex,long nPkgNum);
	//生成光口数据,//参数2为光口号从0开始编号,按照此方式生成的报文按照Pcap文件内的顺序进行排序
	void GenerateFiberDatas_ActPkgOrder(PCAP_IEC_FIBER_PORT *pPcapIecFiber,long nFiberPortIndex,long nPkgNum);
	void AddFiberCtrlDatas(PCAP_IEC_FIBER_PORT *pPcapIecFiber,P_PCAP_IEC_CTRL pPcapIecCtrl,long nBeginFrameIndex,long nEndFrameIndex);//添加光口单个控制块数据
	void GenerateEqualIntervalPkgsTime();//自动生成等间隔报文时间

};
