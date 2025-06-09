#pragma once
#ifdef Not_USE_IECCFGFILES
#include "../CfgDataMngr/IecCfgDatasMngr.h"
#else
#include "../IecCfgTool/IecCfgTool.h"
#endif
#include "../SCL/SclIecCfgDatas.h"

#define  IEC_CFG_SMV_TYPE_IN                                          0//20220802 zhouhj iec�����ж�Ӧ��SMV����
#define  IEC_CFG_SMV_TYPE_OUT                                         1//iec�����ж�Ӧ��SMV����



class CSclToIecCfgTool : public CExBaseList
{
public:
	CSclToIecCfgTool(void);
	~CSclToIecCfgTool(void);

	void AttacthSclFileRead(CSclStation *pSclFileRead)	{	m_pCSclFileRead = pSclFileRead;	}

protected:
	CSclStation *m_pCSclFileRead;
	
public:
	void AddToIecCfg(CSclIed *pIed, CIecCfgDatasMngr *pIecCfgDatasMngr);
	void AddGinEx(CIecCfgDatasMngr *pIecfgDatasMngr,CSclIed *pCurrSelSclIed,CSclStation *pSclStation);//20221114 zhouhj ����뵱ǰIED��Gout���߹�ϵ��IEDװ�õ�Gout���ƿ鵽��ǰCfg�ļ��е�Gin

#ifndef Not_USE_IECCFGFILES
	void AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgFiles *pIecCfgFiles);//zhouhj 20211028 �����ͬ����Ŀ��ƿ�
	void AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgFile *pIecCfgFile);//zhouhj 20211028 �����ͬ����Ŀ��ƿ�
#endif
	long AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr,BOOL bSmvInOutMerge = TRUE);//zhouhj 20211028 �����ͬ����Ŀ��ƿ�

#ifndef Not_USE_IECCFGFILES
	void AddToIecCfg(CExBaseList &oListSclCtrls, CExBaseObject *pIecCfgFile, UINT nAddToType);
	BOOL HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgFiles *pIecCfgFiles,CExBaseList &oRepeatListRef);//zhouhj 20211103 �жϵ�ǰѡ��Ŀ��ƿ����Ƿ����ظ���,����н��ظ�����ȡ����
	BOOL HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgFile *pIecCfgFile,CExBaseList &oRepeatListRef);//zhouhj 20211103 �жϵ�ǰѡ��Ŀ��ƿ����Ƿ����ظ���,����н��ظ�����ȡ����
#endif

	//zhouhj 20220802 ���һ��������ʶ,ΪTRUE��Smv���ĺͷ����ϲ���SmvOut���洦������ֿ�����
	BOOL HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oRepeatListRef,BOOL bSmvInOutMerge = TRUE);//zhouhj 20211103 �жϵ�ǰѡ��Ŀ��ƿ����Ƿ����ظ���,����н��ظ�����ȡ����

#ifndef Not_USE_IECCFGFILES
	void DeleteAllRepeatCtrls(CIecCfgFiles *pIecCfgFiles,CExBaseList &oRepeatListRef);//zhouhj 20211103 �жϵ�ǰѡ��Ŀ��ƿ����Ƿ����ظ���,����н��ظ�����ȡ����
	void DeleteAllRepeatCtrls(CIecCfgFile *pIecCfgFile,CExBaseList &oRepeatListRef);//zhouhj 20211103 �жϵ�ǰѡ��Ŀ��ƿ����Ƿ����ظ���,����н��ظ�����ȡ����
#endif

	void DeleteAllRepeatCtrls(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oRepeatListRef,BOOL bSmvInOutMerge = TRUE);//zhouhj 20211103 �жϵ�ǰѡ��Ŀ��ƿ����Ƿ����ظ���,����н��ظ�����ȡ����


	void AddToIecCfg(CSclCtrlsSmvIn  *pSclCtrlsSmvIn,CSclCtrlsGsOut  *pSclCtrlsGsOut,CSclCtrlsGsIn   *pSclCtrlsGsIn , CIecCfgDatasMngr *pIecCfgDatasMngr);
	void AddToIecCfg(CSclCtrlsSmvOut  *pSclCtrlsSmvOut,CSclCtrlsGsOut  *pSclCtrlsGsOut,CSclCtrlsGsIn   *pSclCtrlsGsIn , CIecCfgDatasMngr *pIecCfgDatasMngr);

	//20221219 zhouhj ��ӵ������ƿ�,���һ������Ϊ�Ƿ񸲸��ظ��Ŀ��ƿ�
	CIecCfgDataBase* AddCfgSmvInGin_By_SclSmvOutGout(CSclCtrlBase *pSclCtrlBase, CIecCfgDatasMngr *pIecCfgDatasMngr,BOOL bCoverRepeat = FALSE);

	void OverwriteIecCfg(CExBaseObject *pSclData, CExBaseObject *pIecCfgData);

// #ifndef Not_USE_IECCFGFILES
// 	void ValidCtrls_Repeat(CIecCfgFiles *pIecCfgFiles,CExBaseList *pListSclDatas ,UINT nClassID);//zhouhj 20211018�ж������еĿ��ƿ�,�Ƿ��뵱ǰ���еĿ��ƿ��ظ�
// #endif
// 	void ValidCtrls_Repeat(CExBaseList *pListSclDatas,CIecCfgDatasBase* pIecCfgDatas);
	
protected:
#ifndef Not_USE_IECCFGFILES
	void AddToIecCfg(CExBaseList &oListSclCtrls, CIecCfgFiles *pIecCfgFiles, UINT nAddToType);
	void AddToIecCfg(CExBaseList &oListSclCtrls, CIecCfgFile  *pIecCfgFile,  UINT nAddToType);
#endif
	void AddToIecCfg(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pDatasMngr,  UINT nAddToType);
	
	void AddToIecCfg_SMV(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr);
	void AddToIecCfg_SmvIn(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr);

	void AddToIecCfg_Gin(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr);
	void AddToIecCfg_Gout(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr);

protected:
	void InitCfgGin_By_SclGin(CIecCfgGinData *pCfgData, CSclCtrlGsIn *pGsIn);
	void InitCfgGin_By_SclGout(CIecCfgGinData *pCfgData, CSclCtrlGsOut *pGsOut);
	void InitCfgGout_By_SclGin(CIecCfgGoutData *pCfgData, CSclCtrlGsIn *pGsIn);
	void InitCfgGout_By_SclGout(CIecCfgGoutData *pCfgData, CSclCtrlGsOut *pGsOut);

	void AddCfgGin_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsIn *pGsIns);
	void AddCfgGin_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsOut *pGsOuts);
	void AddCfgGout_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsIn *pGsIns);
	void AddCfgGout_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsOut *pGsOuts);

	CIecCfgGooseDataBase* AddCfgGin_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlGsIn *pGsIn);
public:
	CIecCfgGooseDataBase* AddCfgGin_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlGsOut *pGsOut,BOOL bCoverRepeat = FALSE);
	CIecCfgGooseDataBase* AddCfgGout_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlGsIn *pGsIn);
protected:
	CIecCfgGooseDataBase* AddCfgGout_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlGsOut *pGsOut);

	void InitCfgSmv_By_SclSMVInput_91(CIecCfg91Data *pCfgData, CSclCtrlSmvIn *pSmvIn);
	void InitCfgSmv_By_SclSMVInput_92(CIecCfg92Data *pCfgData, CSclCtrlSmvIn *pSmvIn);
	void InitCfgSmvIn_By_SclSMVInput_92(CIecCfg92InData *pCfgData, CSclCtrlSmvIn *pSmvIn);

	//ZHJ
	void InitCfgSmv_By_SclSMVInput_92(CIecCfg92InData *pCfgDataIn, CExBaseList &oListSclCtrls);
	void InitCfgSmv_SclSMVInput_92_Str(CIecCfg92InData *pCfgDataIn, CSclCtrlSmvIn *pSclSmvIn);

	void InitCfgSmv_By_SclSMVInput_60448(CIecCfg6044Data *pCfgData, CSclCtrlSmvIn *pSmvIn);
	void InitCfgSmv_By_SclSMVOutput_91(CIecCfg91Data *pCfgData, CSclCtrlSmvOut *pSmvOut);
	void InitCfgSmv_By_SclSMVOutput_92(CIecCfg92Data *pCfgData, CSclCtrlSmvOut *pSmvOut);

	//ZHJ
	void InitCfgSmv_By_SclSMVOutput_92(CIecCfg92InData *pCfgDataIn, CSclCtrlSmvOut *pSmvOut);
	void InitCfgSmvIn_By_SclSMVOutput_92(CIecCfg92InData *pCfgDataIn, CSclCtrlSmvOut *pSmvOut);

	void InitCfgSmv_By_SclSMVOutput_60448(CIecCfg6044Data *pCfgData, CSclCtrlSmvOut *pSmvOut);

	void AddSMVInput(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsSmvIn *pSmvIns);
	CIecCfgSmvDataBase* AddSMVInput(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn,long nGroupIndex = 1);//zhouhj 20210924 ���SMV���ƿ�ʱ,GroupIndex��Ҫ����

	//ZHJ
//	CIecCfgSmvDataBase* AddSMVInputAll(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oListSclCtrls);
//	CIecCfgSmvDataBase* AddSMVInput_92All(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oListSclCtrls);

	CIecCfgSmvDataBase* AddSMVInput_91(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);
public:
	CIecCfgSmvDataBase* AddSMVInput_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);

	//zhouhj 2023.8.19 �޸�Ϊpublic
	CIecCfgSmvDataBase* AddSmvCfg_By_SclSmvOut(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut,long nCfgInOutType
		,long nGroupIndex = 1,BOOL bCoverRepeat = FALSE);
	CIecCfgSmvDataBase* AddSmvCfg_By_SclSmvIn(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn,long nCfgInOutType,long nGroupIndex = 1);
protected:
	CIecCfgSmvDataBase* AddSMVInput_60448(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);

	void AddSMVOutput(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsSmvOut *pSmvOuts);
	CIecCfgSmvDataBase* AddSMVOutput(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut,long nGroupIndex = 1);
	CIecCfgSmvDataBase* AddSMVOutput_91(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut);
	CIecCfgSmvDataBase* AddSMVOutput_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut);
	CIecCfgSmvDataBase* AddSMVOutput_60448(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut);


	CIecCfgSmvDataBase* AddCfgSmvIn_By_SclSmvOut_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut,BOOL bCoverRepeat = FALSE);
	CIecCfgSmvDataBase* AddCfgSmvOut_By_SclSmvOut_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSmvOut);
	CIecCfgSmvDataBase* AddCfgSmvIn_By_SclSmvIn_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);
	CIecCfgSmvDataBase* AddCfgSmvOut_By_SclSmvIn_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);

	virtual BOOL IsQCh(const CString &strText);
	virtual BOOL IsQCh(CSclChSmvOut *pSclSmvOut);
	virtual BOOL IsQCh(CSclChSmvIn *pSclCh);

	long GetChSize(CSclCtrlSmvIn *pSclSmvIn);
	long GetChSize(CSclCtrlSmvOut *pSclSmvOut);
	void AddCtrlToList(CExBaseList &oRepeatListRef,CSclCtrlBase *pSclCtrl);//zhouhj 20211103 �жϸÿ��ƿ��Ƿ��Ѿ���������,�������,����ӵ�����

};
