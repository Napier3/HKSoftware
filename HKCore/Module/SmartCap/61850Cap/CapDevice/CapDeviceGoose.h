//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	
	//2022-5-31  lijunqing 每个goose设备，单独分析
	CEpGooseBinaryTurns m_oBinaryTurns;
	CWnd *m_pXWndInterface;  //绘图监视窗口指针

//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICEGOOSE;};

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceGooseCh();	}

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas);

	//2020-6-20  lijunqing  分析突变或者变化量
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	virtual BOOL IsDataRcvOverTime();

	//shaolei 20220427
	virtual void UpdateDvmDeviceDatas();
	void UpdateDvmDeviceDatasType(UINT nType, UINT nLen, CString&strValue);//20240704 suyang 增加对类型判断，更新通道数据类型


	virtual void ClearAnalysisResultErrors();

	virtual void Reset();  //开始抓包，复位之前的状态
	void AttachXWndInterface(CWnd *pWnd)	{	m_pXWndInterface = pWnd;	}
	//2023.6.2 zhouhj 根据当前探测报文信息,设置IEC配置参数信息
	void SetIecCfgGin_ByCapDevice(CIecCfgGinData* pIecCfgGinData);
	void SetIecCfgGout_ByCapDevice(CIecCfgGoutData* pIecCfgGoutData);

};

