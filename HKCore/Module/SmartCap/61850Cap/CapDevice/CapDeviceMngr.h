//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceMngr.h  CCapDeviceMngr

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"
#include "../../../Record/MR1200BaseApp.h"
#include "../../../MemBuffer/TCycleMemBuffer.h"

//测试仪录波报文上送的当前模拟量通道过零点绝对时间的最大数量
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
	BOOL IsFT3Rcd();//判断当前是否为FT3录波模式

	//2023.10.26 zhouhj
//	void UpdateSeletStateAllCap(BOOL bSmv92Sel, BOOL bGooseSel,BOOL bFT3_Sel);
//重载函数
public:
	void ResetTimeDataList();
	//zhouhj 2024.3.27 添加合并单元上送模拟量时间数据
	void AddMUTimeData(int nTimeDataCh,__int64 n64TimeData);

	//记录接收报文时,上送的模拟量过零点时候对应的时标
	CTCycleMemBuffer<__int64> m_oTimeDataList;
	//最低位字节对应关联软件资源序号,取值:1-48
	//倒数第2字节对应关联软件资源类型,0-电压  1-电流
	int m_nTimeDataCh;//上述上送的模拟量通道对应的电压电流类别及软件资源Index

//私有成员变量
private:
	CRecordTest *m_pRecordTest;  

//私有成员变量访问方法
public:
	CCapDeviceBase* FindCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	CCapDeviceBase* AddCapDevice(BYTE *pDstMac,BYTE *pSrcMac,UINT APPID, UINT nCMT);
	
	CCapDeviceBase* FindCapDevice(PEPCAPBUFFERITEM pItemData);
	CCapDeviceBase* FindCapDevice(UINT nAppID, 
		const CString &strDetectPkgType,long nPort);//20220609 zhouhj 参数2为探测报文类型,即底层返回的报文类型字符
	CCapDeviceBase* AddCapDevice(PEPCAPBUFFERITEM pItemData);
	CCapDeviceBase* AddCapDevice(CDataGroup *pSttIecCb);
	void InitNameAndID(CCapDeviceBase *pCapDevice);
	CCapDeviceBase* FindCapDevice(CDvmDataset *pDataset); //2022-5-26 
	CCapDeviceBase* FindCapDevice(CDataGroup *pSttIecCb);
	long GetDeviceCount(long nClassID);
	void ClearAllIecfgAttach();
	long GetSmpRate_FT3();

	//zhouhj 2023.10.30  验证FT3控制块通道关联
	BOOL ValidSelectFT3CB_PkgLenth();
	BOOL ValidSelectFT3CB_PkgLenth(long nFt3CrcType);//20240802 suyang 增加CRC类型 0-标准16字节校验，1-报文末尾校验，2-第一个数据块14字节校验

	//验证ST口模式是否正确
	BOOL ValidSTMode();

	//开始抓包，复位之前的状态  2020-06-19  lijunqing
	void Reset();  

	//定期更新装置链接状态  2020-06-27  lijunqing
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