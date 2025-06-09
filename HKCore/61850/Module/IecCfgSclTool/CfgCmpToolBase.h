#pragma once
#include "CfgSclCmpData.h"
#include "..\CfgDataMngr\IecCfgData6044.h"
#include "..\CfgDataMngr\IecCfgData91.h"
#include "..\CfgDataMngr\IecCfgData92.h"
#include "..\CfgDataMngr\IecCfgDataGin.h"
#include "..\CfgDataMngr\IecCfgDataGout.h"

#define CFGSCL_CMP_ID_MAC  _T("目标MAC地址")
#define CFGSCL_CMP_ID_SRCMAC  _T("源MAC地址")
#define CFGSCL_CMP_ID_APPID  _T("AppID")
#define CFGSCL_CMP_ID_DataSetDesc  _T("DataSetDesc")
#define CFGSCL_CMP_ID_DataSet  _T("DataSet")
#define CFGSCL_CMP_ID_LNName  _T("LNName")
#define CFGSCL_CMP_ID_LDName  _T("LDName")
#define CFGSCL_CMP_ID_goID  _T("goID")
#define CFGSCL_CMP_ID_gocbRef  _T("gocbRef")
#define CFGSCL_CMP_ID_gocbIED  _T("gocbIED")
#define CFGSCL_CMP_ID_DataType  _T("类型")
#define CFGSCL_CMP_ID_Name  _T("描述")
#define CFGSCL_CMP_ID_AppChID  _T("通道描述")
#define CFGSCL_CMP_ID_AppChType  _T("通道类型")
#define CFGSCL_CMP_ID_Version  _T("版本号")
#define CFGSCL_CMP_ID_VID  _T(" TCI VID")
#define CFGSCL_CMP_ID_Priority  _T("TCI Priority")
#define CFGSCL_CMP_ID_T0  _T("T0")
#define CFGSCL_CMP_ID_T1  _T("T1")
#define CFGSCL_CMP_ID_IED  _T("IED")
#define CFGSCL_CMP_ID_SVID  _T("SVID")
#define CFGSCL_CMP_ID_TDelay  _T("延时")
#define CFGSCL_CMP_ID_TDelay2  _T("delay2")
#define CFGSCL_CMP_ID_AddrInternal  _T("内部地址")
#define CFGSCL_CMP_ID_confRef  _T("confRef")
#define CFGSCL_CMP_ID_SmpSynch  _T("SmpSynch")
#define CFGSCL_CMP_ID_ChCount  _T("通道数目")

class CCfgCmpToolBase
{
public:
	CCfgCmpToolBase(void);
	~CCfgCmpToolBase(void);

	CCfgSclCmpData* GetCmpData1()	{	return &m_oCmpData1;	}
	CCfgSclCmpData* GetCmpData2()	{	return &m_oCmpData2;	}

	BOOL CmpCfg();
	virtual BOOL RegisterCmpData1(CIecCfgDataBase *pCfgData);
	
	BOOL m_bUseChs;
protected:
	CCfgSclCmpData m_oCmpData1;
	CCfgSclCmpData m_oCmpData2;

	void RegisterCfgData(CIecCfgGooseDataBase *pCfgData);
	void RegisterCfgData(CIecCfgDataGin *pCfgData);
	void RegisterCfgData(CIecCfgDataGout *pCfgData);

	void RegisterCfgData(CIecCfgData91 *pCfgData);
	void RegisterCfgData(CIecCfgData92 *pCfgData);
	void RegisterCfgData(CIecCfgData6044 *pCfgData);

};
