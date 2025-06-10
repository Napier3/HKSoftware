#pragma once

#include "../../../Module/SmartCap/61850Cap/ProtocolBase/Pcap/FrameMemBufferMngr.h"
#include "SttPcapIecDef.h"
#include "../SttTest/Common/tmt_dig_replay_test.h"
#include "../ReplayTest/ComtradeBufMngr.h"

#define _STT_PCAP_PARSE_MAX_FRAME_NUM             700000 //�������ı�����֡��

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttIecCtrlBlock
{
public:
	CSttIecCtrlBlock();
	virtual ~CSttIecCtrlBlock();

	void Init();

	long m_dwAppID;//��ǰ���ƿ�AppID
	long m_nPkgNum;//��ǰ���ƿ鱨����֡��
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
	BOOL HasPcapSendDatas();//�жϵ�ǰ�Ƿ�����ط�����
	void GenerateFibersDatas();//���ɹ����������

	//���ABBuf����
	BOOL GenerateABBuf(int nIndex);	
	//�ɻطŻ���ReplayBuf���AB����
	BOOL GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf);
	void CalOutputTime();

	PCAP_IEC_CTRLS m_oPcapCtrls_SV;
	PCAP_IEC_CTRLS m_oPcapCtrls_GOOSE;
	tmt_DigReplayParas *m_pTmtDigReplayParas;
	PCAP_IEC_FIBERS m_oPcapFibersDatas;//���й�ڵ���������
	long m_nCurDeliverFiberIndex;//��ʼ���Ժ󣬵�ǰ���ͱ��Ķ�Ӧ��PCAP_IEC_FIBER_PORT��Ӧ��Index
	long m_nCurrDeliverFiberPkgIndex;//��ʼ���Ժ󣬵�ǰ���ͱ��Ķ�Ӧ�Ĺ�ڵ�PCAP_IEC_PKG��Ӧ��Index
	BOOL m_bReadFiberDatasFinish;					//��ȫ��������ݽ���

	CFrameMemBufferMngr m_oCapBufferMngr;   //ץ�����Ļ�����
	CString m_strPcapFilePath;

	void SetPkgsPlayBackDatas(long nBeginIndex,long nAllCBEndIndex);// ���ûط�����
	void PcapIecCtrls_ToDigReplayParas();//20230825 suyang ��ѡ��ȫ�����Ļط�ʱ��Ҫ���ã���Ϊ������

	CString GetNetCardID(long nIndex);
	BOOL SimulateSendPcap(const CString &strNetCardID);

protected:
	BOOL FillPkgDatas(CComtradeDataBuffer *pABBuf,PCAP_IEC_FIBER_PORT *pFibers,long &nCurrDeliverFiberPkgIndex);
	long FillPkgData_Single(CComtradeDataBuffer *pABBuf,PCAP_IEC_PKG *pP_PCAP_IEC_PKG,long &nCurrDeliverFiberPkgIndex);
	//��ȡ��������������(��λΪ32λ,��4�ֽ�)��֡����,����2Ϊ�Ƿ��ж�Ϊ4��������
	long GetPkgDataAreaLenth32bits_SinglePkg(CFrameMemBuffer *pXSmMemBuffer,BOOL bCalFourMultiple);
	//��ȡ��������������(��λΪ32λ,��4�ֽ�),����2Ϊ��Ӹ�֡����ǰ,���������ȣ�ͬʱĬ����ҪΪ4��������
	long GetPkgDataAreaLenth_32bits(CFrameMemBuffer *pXSmMemBuffer,long nPrevPkgDataAreaLenth);
	void Create_PcapIecCtrls(CSttIecCtrlBlocks *pCtrlBlocks_SV,CSttIecCtrlBlocks *pCtrlBlocks_GS);
	void AttachAllXSmMemBuffer();
	//void PcapIecCtrls_ToDigReplayParas();
	void PcapIecCtrl_ToDigReplayParas(P_PCAP_IEC_CTRL pCtrl,TMT_DIG_REPLAY_CB *pCB);
	BOOL GetEthernetTypeAppID_ByXSmMemBuffer(CXSmMemBuffer *pCXSmMemBuffer,u_short &uAppID,u_short &uEthernetType);

	//���ɹ������,//����2Ϊ��ںŴ�0��ʼ���,���մ˷�ʽ���ɵı�����Ҫ�Ա��Ľ�����������
	void GenerateFiberDatas_NeedSort(PCAP_IEC_FIBER_PORT *pPcapIecFiber,long nFiberPortIndex,long nPkgNum);
	//���ɹ������,//����2Ϊ��ںŴ�0��ʼ���,���մ˷�ʽ���ɵı��İ���Pcap�ļ��ڵ�˳���������
	void GenerateFiberDatas_ActPkgOrder(PCAP_IEC_FIBER_PORT *pPcapIecFiber,long nFiberPortIndex,long nPkgNum);
	void AddFiberCtrlDatas(PCAP_IEC_FIBER_PORT *pPcapIecFiber,P_PCAP_IEC_CTRL pPcapIecCtrl,long nBeginFrameIndex,long nEndFrameIndex);//��ӹ�ڵ������ƿ�����
	void GenerateEqualIntervalPkgsTime();//�Զ����ɵȼ������ʱ��

};
