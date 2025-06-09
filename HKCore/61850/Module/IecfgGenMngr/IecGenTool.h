#pragma once

#include "IecGenRuleMngr.h"

#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include "..\..\..\Module\KeyDb\XKeyDB.h"

class CIecGenTool
{
public:
	CIecGenTool(void);
	virtual ~CIecGenTool(void);

	BOOL Generate(CIecCfgDevice *pIecfgDevice,const CString &strIecfgName);
//	BOOL GetCurDeivceGinChFileName(CString &strGinChFileName);  20220516 zhouhj 在CIecCfgDatasMngr中增加了相关成员变量,此函数不再需要

protected:
	BOOL GenerateIecfgDevice(CIecDeviceRule* pCurDeivceRule,CIecCfgDevice *pIecfgDevice);
	BOOL GenarateIecCfgDatasMngr(CIecGenCfgDataMngrRule *pIecGenCfgDataMngrRule,CIecCfgDatasMngr *pIecCfgDatasMngr);

	BOOL GenarateIecCfgDatas(CIecGenCfgDataMngrRule_Base *pGenCfgDataMngrRule_Base,CIecCfgDatasBase *pIecCfgDatasBase);
	BOOL GenarateIecCfgDatas_KeyDB(CIecGenCfgDataMngrRule_Base *pGenCfgDataMngrRule_Base,CIecCfgDatasBase *pIecCfgDatasBase);
	BOOL GenerateIecCfgDatas(CIecGenRule_CtrlBlock *pCurCtrlBlock,CIecCfgDatasBase *pIecCfgDatasBase);

	BOOL SetAllChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CIecCfgDatasBase *pIecCfgDatasBase);
	BOOL SetAllChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CIecCfgDataBase *pIecCfgDataBase);

#ifdef IECFG_USE_KEYDB
	CIecCfgDataBase* GetIecCfgDataBase(CXMatchObject *pXMatchObject,long nMatchRatio);
	BOOL SetAllChMaps_KeyDB(CIecGenRule_CtrlBlock *pCurCtrlBlock,CIecCfgDataBase *pIecCfgDataBase);
	BOOL SetChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CExBaseList *pMacthObjectRatioList,CIecCfgDataBase *pIecCfgDataBase);
	BOOL SetChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CExBaseList *pMacthObjectRatioList);
	CXMatchObjectRatio* GetMaxRatio_XMatchObject(CExBaseList *pMacthObjectRatioList);
#endif


protected:
	virtual void OpenKeyDbFile();
	CXKeyDB m_oKeyDB;
	CXMatchToolBase m_oXMatchTool;
	CIecDeviceRule *m_pCurDeivceRule;
};
