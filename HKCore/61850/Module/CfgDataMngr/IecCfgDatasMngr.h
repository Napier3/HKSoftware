//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasMngr.h  CIecCfgDatasMngr

#pragma once

#include "IecCfgDataMngrGlobal.h"
#include "IecCfgSMVDatas.h"
#include "IecCfgGinDatas.h"
#include "IecCfgGoutDatas.h"
#include "IecCfgSmvInDatas.h"
#include "IecCfgSysParas.h"

#include "../../../Module/DataMngr/DvmLogicDevice.h"
// #include "IecCfgDatasAnalog.h"
// #include "IecCfgSystemConfig.h"

#define WM_SAVEAS_IecCfgFILE              (WM_USER+2117)
#define WM_VIEW_IECCFG_ONLY_USEDIN        (WM_USER+2118)
#define WM_VIEW_IECCFG_UPDATE_CHS_GRID    (WM_USER+2119)//更新通道表格显示标题(更新总列数)


class CIecCfgDatasMngr : public CExBaseList
{
public:
	CIecCfgDatasMngr();
	virtual ~CIecCfgDatasMngr();

	BOOL m_bModified;
	long m_nDeviceID;
// 	CString m_strIecCfgFile;
	CString m_strScdFile;
	CString m_strGinChMapFileName;//20220516 GOOSE订阅通道映射文件名称,山东自动测试需要每个ixml对应一个开入通道映射增加
	long m_nVertion;//zhouhj增加版本标记 缺省为0
	CString m_strDate;//zhouhj 2023.12.6 配置文件修改日期

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATASMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgDatasMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
    virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void InitAfterRead();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:
	CIecCfgGoutDatas *m_pGoutMngr;
	CIecCfgGinDatas *m_pGinMngr;
	CIecCfgDatasSMV *m_pSmvMngr;
	CIecCfgDatasSmvIn *m_pSmvInMngr;
	CIecCfgSysParas *m_pSysParasMngr;//zhouhj 20210316 增加用于单机软件的系统参数设置
// 	CIecCfgDatasAnalog *m_pAnalogMngr;

// 	CArtAmpDigdatas *m_pArtAmpDigdatas;

// 	long  m_nEnableSMV;
// 	long  m_nEnableGIN;
// 	long  m_nEnableGOUT;
// 	long  m_nEnableAnalog;
// 
// 	CIecCfgSystemConfig m_oIecCfgSystemConfig;

private:
	long ValidateEnable(long nEnable)	{	return ((nEnable > 0) ? 1 : 0);	}


//私有成员变量访问方法
public:
	void SetGinMngr(CIecCfgGinDatas *p)	{	m_pGinMngr = p;	}
	CIecCfgGinDatas* GetGinMngr();
	CIecCfgDatasSMV* GetSmvMngr();
	CIecCfgDatasSmvIn* GetSmvInMngr();
	CIecCfgGoutDatas* GetGoutMngr();
	CIecCfgSysParas* GetSysParasMngr();
 //	CIecCfgDatasSMVInput* GetSmvInputMngr();
// 	CArtAmpDigdatas* GetArtAmpDigdatas();
// 	CArtAmpDigdatas* InitArtAmpDigdatas();
//	CIecCfgSystemConfig* GetIecCfgSystemConfig()	{	return &m_oIecCfgSystemConfig;	}
	void SaveArtAmpDigdatasTemp();
	void CalArtAmpDigdatas();

	long GetCfgDatasEnableCount();
	long GetEnableSMV();
	long GetEnableGIN();
	long GetEnableGOUT();
 //	long GetEnableSMVInput();

	void SetEnableSMV(long nEnable=1);
	void SetEnableGIN(long nEnable=1);
	void SetEnableGOUT(long nEnable=1);
//	void SetEnableSMVInput(long nEnable=1);

	long GetSMVCount();
	long GetGINCount();
	long GetGOUTCount();
	long GetParasSetSel();//zhouhj 20211021获取界面参数设置选择按一次值还是二次值设置(0=二次值;1=一次值)
	long GetPrimOutput();//报文输出选择 0-二次值 1-一次值,缺省采用一次值(与系统参数中的该值定义相反)

//	long GetSMVInputCount();

	BOOL SetSMVCount(long nCount, CExBaseList &oListTemp);
	BOOL SetGINCount(long nCount, CExBaseList &oListTemp);
	BOOL SetGOUTCount(long nCount, CExBaseList &oListTemp);

	void SetFiber2IndexByFiberIndex(long nOffset);//zhouhj 20201205 用于切换Fiber2光口号到Fiber

//	BOOL SetSMVInputCount(long nCount, CExBaseList &oListTemp);

	CIecCfgDataBase* CreateNewSmvCfgData();
	CIecCfgDataBase* CreateNewSmvInCfgData();
	CIecCfgDataBase* CreateNewGinCfgData();
	CIecCfgDataBase* CreateNewGoutCfgData();

//	CIecCfgDataBase* CreateNewSmvInputCfgData();

	CIecCfgDataBase* GetSmvCfgData(long nIndex);
	CIecCfgDataBase* GetGinCfgData(long nIndex);
	CIecCfgDataBase* GetGoutCfgData(long nIndex);

	long GetSmvType();
	BOOL SetSmvType(long nSmvType);
	long GetSmvInType();
	BOOL SetSmvInType(long nSmvType);

	void InitCommon();
	void InitCfgDataMngr();
	void InitDatasMngr();
	void CreateDefaultCfgDataMngr(long nCfgDataCount=1);
	void GetIecCfgSmvDatas(CExBaseList &oList, BOOL bGetCommon=TRUE);
	void GetIecCfgSmvInDatas(CExBaseList &oList, BOOL bGetCommon=TRUE);
	void GetIecCfgGinDatas(CExBaseList &oList);
	void GetIecCfgGoutDatas(CExBaseList &oList);
// 	void GetIecCfgAnalogDatas(CExBaseList &oList);
	void GetIecCfgDatas(CExBaseList &oList, BOOL bGetCommon=TRUE);
	BOOL DeleteCfgData(CIecCfgDataBase *pCfgData);
	BOOL SetCfgDataCount(CIecCfgDatasBase *pCfgDatas, long nCount, CExBaseList &oListTemp);
	void ResetArtAmpDigdatas();

//	long GetSmvInputType();
	BOOL SetSmvInputType(long nSmvType);
	void GetIecCfgSmvInputDatas(CExBaseList &oList, BOOL bGetCommon=TRUE);

	BOOL OpenIecCfgFile(const CString &strFile);
	BOOL SetIecCfgDataString(const CString &strIecCfgData);  //2022-9-19  lijunqing
	void DelteteContrlBlocks_Unselected();//zhouhj 20210528删除未选择的控制块

	BOOL HasContrlBlock_Selected();//判断当前是否全部控制块都为空
	BOOL HasContrlBlock_Selected(bool bHasLCFiber,bool bHasSTFiber);//20240529 suyang 判断当前FT3 控制块 SV-goose控制块是否为空

	void UpdateGinChMapFile();//20220516 zhouhj 更新GOOSE订阅通道映射文件,根据当前标识的通道映射文件名称,去查找对应的文件, 并更新
	void UpdateFiberIdex2();//20220611 将光口标识1设置值,指向光口标识2

	void UpdateFT3ChsType(long nIecFormat,long nIecFormatMeas);//20240117 suyang 增加对FT3通道类型转换
	void UpdateFT3ChsTypeChanged(CIecCfgChsBase *pIecCfgChsBase,long nType);

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,CExBaseList *pGinList,CExBaseList *pGoutList,long &nSV_CBIndex,long &nGinCBIndex,long &nGoutCBIndex);//周宏军 20200616  增加AT02配置
	void SetAT02D_ChannelID(CExBaseList *pSmvInList,CExBaseList *pSmvOutList,CExBaseList *pGinList,CExBaseList *pGoutList,
		long &nSVmvIn_CBIndex,long &nSVmvOut_CBIndex,long &nGinCBIndex,long &nGoutCBIndex);//周宏军 20200616  增加AT02配置
	void AddAT02D_Dataset(CDvmLogicDevice *pLDevice,long &nSV_DatasetIndex,long &nGin_DatasetIndex,long &nGout_DatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	void AddAT02D_Dataset_SmvInGin(CDvmLogicDevice *pLDevice,long &nSmvIn_DatasetIndex,long &nGin_DatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas = FALSE);
	CIecCfgDatasMngr* GetAT02D_IecCfgDatasMngr();
	void AT02D_CopyGoutToGin(CIecCfgGoutDatas *pGoutMngr,CIecCfgGinDatas *pNewGinMngr);
	void AT02D_CopyGinToGout(CIecCfgGinDatas *pGinMngr,CIecCfgGoutDatas *pNewGoutMngr);
	void AT02D_GetAllDatasRef(CIecCfgDatasSMV *pTmpSMVDatas,CIecCfgGinDatas *pTmpGinDatas,CIecCfgGoutDatas *pTmpGoutDatas);
#endif

	CIecCfgDataBase* FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount);

#ifndef _PSX_IDE_QT_
	BOOL SaveAsIecCfgFile();
#endif
	BOOL SaveAsIecCfgFile(const CString &strFile,BOOL bIsAT02D_CFG = FALSE);
// 	void SaveTempIecCfgFile();
// 	void OpenTempIecCfgFile();
//	CString GetLastFile()	{	return m_oIecCfgSystemConfig.GetLastFile();	}

	BOOL AddCfgData(long nCfgDataClassID, const CString &strCfgDataFile);
	BOOL OverWriteCfgData(long nCfgDataClassID, long nIndex, const CString &strCfgDataFile, CIecCfgDataBase **ppCfgData);

protected:
	void CalArtAmpDigdatas(CExBaseList &oList);

	BOOL CanAddCfgData(CIecCfgDatasBase *pDatas, long nMaxCount);
	BOOL AddCfgData_Smv(long nCfgDataClassID, const CString &strCfgDataFile);
	BOOL AddCfgData_Gin(const CString &strCfgDataFile);
	BOOL AddCfgData_Gout(const CString &strCfgDataFile);
	
	void InitAfterRead2();   //2022-9-19  lijunqing
//	BOOL AddCfgData_SmvInput(long nCfgDataClassID, const CString &strCfgDataFile);
};

//zhouhj  2023.12.21 增加用于获取对应的比例
CIecCfgSmvRate* iecfg_GetSmvRate(CIecCfgDataSmvChBase* pDataSmvCh,BOOL bDCFT3);

#ifndef _PSX_IDE_QT_
void iecfg_SetModified(CExBaseObject *pObj, BOOL bModified = TRUE);
BOOL iecfg_IsModified(CExBaseObject *pObj);
#endif
