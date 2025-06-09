#pragma once
#ifdef Not_USE_IECCFGFILES
#include "../CfgDataMngr/IecCfgDatasMngr.h"
#else
#include "../IecCfgTool/IecCfgTool.h"
#endif
#include "../SCL/SclIecCfgDatas.h"

#define  IEC_CFG_SMV_TYPE_IN                                          0//20220802 zhouhj iec配置中对应的SMV接收
#define  IEC_CFG_SMV_TYPE_OUT                                         1//iec配置中对应的SMV发送



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
	void AddGinEx(CIecCfgDatasMngr *pIecfgDatasMngr,CSclIed *pCurrSelSclIed,CSclStation *pSclStation);//20221114 zhouhj 添加与当前IED有Gout连线关系的IED装置的Gout控制块到当前Cfg文件中的Gin

#ifndef Not_USE_IECCFGFILES
	void AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgFiles *pIecCfgFiles);//zhouhj 20211028 多个不同种类的控制块
	void AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgFile *pIecCfgFile);//zhouhj 20211028 多个不同种类的控制块
#endif
	long AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr,BOOL bSmvInOutMerge = TRUE);//zhouhj 20211028 多个不同种类的控制块

#ifndef Not_USE_IECCFGFILES
	void AddToIecCfg(CExBaseList &oListSclCtrls, CExBaseObject *pIecCfgFile, UINT nAddToType);
	BOOL HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgFiles *pIecCfgFiles,CExBaseList &oRepeatListRef);//zhouhj 20211103 判断当前选择的控制块中是否有重复的,如果有将重复的提取出来
	BOOL HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgFile *pIecCfgFile,CExBaseList &oRepeatListRef);//zhouhj 20211103 判断当前选择的控制块中是否有重复的,如果有将重复的提取出来
#endif

	//zhouhj 20220802 最后一个参数标识,为TRUE将Smv订阅和发布合并在SmvOut里面处理，否则分开处理
	BOOL HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oRepeatListRef,BOOL bSmvInOutMerge = TRUE);//zhouhj 20211103 判断当前选择的控制块中是否有重复的,如果有将重复的提取出来

#ifndef Not_USE_IECCFGFILES
	void DeleteAllRepeatCtrls(CIecCfgFiles *pIecCfgFiles,CExBaseList &oRepeatListRef);//zhouhj 20211103 判断当前选择的控制块中是否有重复的,如果有将重复的提取出来
	void DeleteAllRepeatCtrls(CIecCfgFile *pIecCfgFile,CExBaseList &oRepeatListRef);//zhouhj 20211103 判断当前选择的控制块中是否有重复的,如果有将重复的提取出来
#endif

	void DeleteAllRepeatCtrls(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oRepeatListRef,BOOL bSmvInOutMerge = TRUE);//zhouhj 20211103 判断当前选择的控制块中是否有重复的,如果有将重复的提取出来


	void AddToIecCfg(CSclCtrlsSmvIn  *pSclCtrlsSmvIn,CSclCtrlsGsOut  *pSclCtrlsGsOut,CSclCtrlsGsIn   *pSclCtrlsGsIn , CIecCfgDatasMngr *pIecCfgDatasMngr);
	void AddToIecCfg(CSclCtrlsSmvOut  *pSclCtrlsSmvOut,CSclCtrlsGsOut  *pSclCtrlsGsOut,CSclCtrlsGsIn   *pSclCtrlsGsIn , CIecCfgDatasMngr *pIecCfgDatasMngr);

	//20221219 zhouhj 添加单个控制块,最后一个参数为是否覆盖重复的控制块
	CIecCfgDataBase* AddCfgSmvInGin_By_SclSmvOutGout(CSclCtrlBase *pSclCtrlBase, CIecCfgDatasMngr *pIecCfgDatasMngr,BOOL bCoverRepeat = FALSE);

	void OverwriteIecCfg(CExBaseObject *pSclData, CExBaseObject *pIecCfgData);

// #ifndef Not_USE_IECCFGFILES
// 	void ValidCtrls_Repeat(CIecCfgFiles *pIecCfgFiles,CExBaseList *pListSclDatas ,UINT nClassID);//zhouhj 20211018判断链表中的控制块,是否与当前已有的控制块重复
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
	CIecCfgSmvDataBase* AddSMVInput(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn,long nGroupIndex = 1);//zhouhj 20210924 多个SMV控制块时,GroupIndex需要递增

	//ZHJ
//	CIecCfgSmvDataBase* AddSMVInputAll(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oListSclCtrls);
//	CIecCfgSmvDataBase* AddSMVInput_92All(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oListSclCtrls);

	CIecCfgSmvDataBase* AddSMVInput_91(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);
public:
	CIecCfgSmvDataBase* AddSMVInput_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSmvIn);

	//zhouhj 2023.8.19 修改为public
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
	void AddCtrlToList(CExBaseList &oRepeatListRef,CSclCtrlBase *pSclCtrl);//zhouhj 20211103 判断该控制块是否已经在链表中,如果不在,则添加到链表

};
