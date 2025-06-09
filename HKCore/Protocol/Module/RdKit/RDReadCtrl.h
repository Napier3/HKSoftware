#pragma once
#include "RDKitLibrary.h"

#include "..\..\..\Module\DataMngr\DvmDevice.h"

extern BOOL g_bDebugMode;

// enum _tagEngineSystemDefine
// {
// 	engineConnectDeviceFailed=0,
// 	engineConnectDeviceSuccessful=1,
// 	engineCommError = 2,
// 	engineCommFinish = 3,
// 	engineCommCmdError=4,
// 	engineHeart=5,
// 	engineException=6
// } ;//_enumEngineSystemDefine;

enum _tagEngineSystemDefine
{//2020-5-21  lijunqing
	engineConnectDeviceFailed= 1, //0,
	engineConnectDeviceSuccessful=2, //1,
	engineCommError = 3, //2,
	engineCommFinish = 4, //3,
	engineCommCmdError=5, //4
	engineException=6 //5
} ;//_enumEngineSystemDefine;

struct CRd_Measure_Datas
{
public:
	void Init_RdDatas()
	{
		for (int nIndex = 0;nIndex<50;nIndex++)
		{
			m_fIaAmp[nIndex] = 0;
			m_fIaPhase[nIndex] = 0;
			m_fIaFre[nIndex] = 0;
			m_fIbAmp[nIndex] = 0;
			m_fIbPhase[nIndex] = 0;
			m_fIbFre[nIndex] = 0;
			m_fIcAmp[nIndex] = 0;
			m_fIcPhase[nIndex] = 0;
			m_fIcFre[nIndex] = 0;

			m_fUaAmp[nIndex] = 0;
			m_fUaPhase[nIndex] = 0;
			m_fUaFre[nIndex] = 0;
			m_fUbAmp[nIndex] = 0;
			m_fUbPhase[nIndex] = 0;
			m_fUbFre[nIndex] = 0;
			m_fUcAmp[nIndex] = 0;
			m_fUcPhase[nIndex] = 0;
			m_fUcFre[nIndex] = 0;
		}

		m_fUaTHD = 0;
		m_fUbTHD = 0;
		m_fUcTHD = 0;
		m_fIaTHD = 0;
		m_fIbTHD = 0;
		m_fIcTHD = 0;
	}

	CRd_Measure_Datas(){Init_RdDatas();}
	virtual ~CRd_Measure_Datas(){}

	float m_fIaAmp[50];
	float m_fIaPhase[50];
	float m_fIaFre[50];
	float m_fIbAmp[50];
	float m_fIbPhase[50];
	float m_fIbFre[50];
	float m_fIcAmp[50];
	float m_fIcPhase[50];
	float m_fIcFre[50];

	float m_fUaAmp[50];
	float m_fUaPhase[50];
	float m_fUaFre[50];
	float m_fUbAmp[50];
	float m_fUbPhase[50];
	float m_fUbFre[50];
	float m_fUcAmp[50];
	float m_fUcPhase[50];
	float m_fUcFre[50];

	float m_fUaTHD;
	float m_fUbTHD;
	float m_fUcTHD;
	float m_fIaTHD;
	float m_fIbTHD;
	float m_fIcTHD;
};

class CRDReadCtrl
{
public:
	CRDReadCtrl(void);
	virtual ~CRDReadCtrl(void);

	BOOL ConnectRDDevice();
	BOOL DisConnectRDDevice();
	BOOL Read_AllChannels();
	BOOL ReadRD_UA(BOOL bReadPhase);
	BOOL ReadRD_UB(BOOL bReadPhase);
	BOOL ReadRD_UC(BOOL bReadPhase);
	BOOL ReadRD_IA(BOOL bReadPhase);
	BOOL ReadRD_IB(BOOL bReadPhase);
	BOOL ReadRD_IC(BOOL bReadPhase);
	BOOL ReadAllPhases(uint16 nCurrOrVolt);

	BOOL ReadRD_THD();
	BOOL ReadRD_THD(uint16 nDefType,uint16 nCurrOrVolt ,float *pfValue ,float *pfAmpValue,float *pfPhaseValue,float *pfDistValue,long &nReadCount);

	void InitModel(const CString &strModelPath);
	void Update_DatasetValus();
//	void SetModelPath(const CString &strModelPath){m_strModelPath = strModelPath;}

	CDvmDevice m_oDeviceModel;
	CRd_Measure_Datas m_oRd_Datas;
	CDvmDataset *m_pCurDataSet;
	static BOOL g_bConnected;

	//外部消息定义
	unsigned long  m_hMsgWnd;
	unsigned long  m_nMsg;
	unsigned long m_hSysMsgWnd;
	unsigned long  m_nSysMsg;

protected:
	CDvmDataset *GetAinDataset();
	void Regist_AllChannels();
	void Regist_channel(const CString &strChannelDesc,float *pfChannelValue);

	CString m_strModelPath;
	RADDEVICEID m_oDeviceId;
	void StatusError();
};

inline void mms_PostDeviceSysMessage(CRDReadCtrl *pRdReadCtrl, WPARAM wParam, LPARAM lParam)
{
// 	if (pRdReadCtrl->g_bConnected)
// 	{
// 		wParam = 1;//engineConnectDeviceSuccessful;
// 		lParam = 1;//engineConnectDeviceSuccessful;
// 	}

	HWND hWnd = (HWND)pRdReadCtrl->m_hSysMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		return;
	}

	::PostMessage(hWnd, pRdReadCtrl->m_nSysMsg, wParam, lParam);
}

inline void mms_PostDeviceCommCmdMessage(CRDReadCtrl *pRdReadCtrl, WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)pRdReadCtrl->m_hMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 【%08x】 不是窗口"), pRdReadCtrl->m_hMsgWnd);//_T("发送测试完成消息 【%08x】 不是窗口")
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("发送测试完成消息 WND=【%08x】 MSG=【%08x】"), (DWORD)hWnd, pRdReadCtrl->m_nMsg);//_T("发送测试完成消息 WND=【%08x】 MSG=【%08x】")
	::PostMessage(hWnd, pRdReadCtrl->m_nMsg, wParam, lParam);
}

