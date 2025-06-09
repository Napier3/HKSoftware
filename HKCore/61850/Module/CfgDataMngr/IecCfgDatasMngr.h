//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
#define WM_VIEW_IECCFG_UPDATE_CHS_GRID    (WM_USER+2119)//����ͨ�������ʾ����(����������)


class CIecCfgDatasMngr : public CExBaseList
{
public:
	CIecCfgDatasMngr();
	virtual ~CIecCfgDatasMngr();

	BOOL m_bModified;
	long m_nDeviceID;
// 	CString m_strIecCfgFile;
	CString m_strScdFile;
	CString m_strGinChMapFileName;//20220516 GOOSE����ͨ��ӳ���ļ�����,ɽ���Զ�������Ҫÿ��ixml��Ӧһ������ͨ��ӳ������
	long m_nVertion;//zhouhj���Ӱ汾��� ȱʡΪ0
	CString m_strDate;//zhouhj 2023.12.6 �����ļ��޸�����

//���غ���
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

//˽�г�Ա����
private:
	CIecCfgGoutDatas *m_pGoutMngr;
	CIecCfgGinDatas *m_pGinMngr;
	CIecCfgDatasSMV *m_pSmvMngr;
	CIecCfgDatasSmvIn *m_pSmvInMngr;
	CIecCfgSysParas *m_pSysParasMngr;//zhouhj 20210316 �������ڵ��������ϵͳ��������
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


//˽�г�Ա�������ʷ���
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
	long GetParasSetSel();//zhouhj 20211021��ȡ�����������ѡ��һ��ֵ���Ƕ���ֵ����(0=����ֵ;1=һ��ֵ)
	long GetPrimOutput();//�������ѡ�� 0-����ֵ 1-һ��ֵ,ȱʡ����һ��ֵ(��ϵͳ�����еĸ�ֵ�����෴)

//	long GetSMVInputCount();

	BOOL SetSMVCount(long nCount, CExBaseList &oListTemp);
	BOOL SetGINCount(long nCount, CExBaseList &oListTemp);
	BOOL SetGOUTCount(long nCount, CExBaseList &oListTemp);

	void SetFiber2IndexByFiberIndex(long nOffset);//zhouhj 20201205 �����л�Fiber2��ںŵ�Fiber

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
	void DelteteContrlBlocks_Unselected();//zhouhj 20210528ɾ��δѡ��Ŀ��ƿ�

	BOOL HasContrlBlock_Selected();//�жϵ�ǰ�Ƿ�ȫ�����ƿ鶼Ϊ��
	BOOL HasContrlBlock_Selected(bool bHasLCFiber,bool bHasSTFiber);//20240529 suyang �жϵ�ǰFT3 ���ƿ� SV-goose���ƿ��Ƿ�Ϊ��

	void UpdateGinChMapFile();//20220516 zhouhj ����GOOSE����ͨ��ӳ���ļ�,���ݵ�ǰ��ʶ��ͨ��ӳ���ļ�����,ȥ���Ҷ�Ӧ���ļ�, ������
	void UpdateFiberIdex2();//20220611 ����ڱ�ʶ1����ֵ,ָ���ڱ�ʶ2

	void UpdateFT3ChsType(long nIecFormat,long nIecFormatMeas);//20240117 suyang ���Ӷ�FT3ͨ������ת��
	void UpdateFT3ChsTypeChanged(CIecCfgChsBase *pIecCfgChsBase,long nType);

#ifdef _USE_IN_AT02D_MODE_
	virtual void SetAT02D_ChannelID(CExBaseList *pSVList,CExBaseList *pGinList,CExBaseList *pGoutList,long &nSV_CBIndex,long &nGinCBIndex,long &nGoutCBIndex);//�ܺ�� 20200616  ����AT02����
	void SetAT02D_ChannelID(CExBaseList *pSmvInList,CExBaseList *pSmvOutList,CExBaseList *pGinList,CExBaseList *pGoutList,
		long &nSVmvIn_CBIndex,long &nSVmvOut_CBIndex,long &nGinCBIndex,long &nGoutCBIndex);//�ܺ�� 20200616  ����AT02����
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

//zhouhj  2023.12.21 �������ڻ�ȡ��Ӧ�ı���
CIecCfgSmvRate* iecfg_GetSmvRate(CIecCfgDataSmvChBase* pDataSmvCh,BOOL bDCFT3);

#ifndef _PSX_IDE_QT_
void iecfg_SetModified(CExBaseObject *pObj, BOOL bModified = TRUE);
BOOL iecfg_IsModified(CExBaseObject *pObj);
#endif
