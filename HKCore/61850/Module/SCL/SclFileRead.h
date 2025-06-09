#if !defined(_CSclFileRead_h__)
#define _CSclFileRead_h__

#if _MSC_VER > 1000
#pragma once
extern "C"
{
#include "glbtypes.h"
#include "mvl_acse.h"
#include "mvl_defs.h"
#include "sx_arb.h"
#include "scl.h"
#include "smpval.h"
#include "mem_chk.h"
#include "slog.h"
};

#endif // _MSC_VER > 1000


#define WM_SCLFILE_READ_FINISH   (WM_USER + 1411)
#define SCLFILE_READ_SHOW      0
#define SCLFILE_READ_DELCTRLS  1
#define SCLFILE_READ_FINISH    2

#include "..\..\..\Module\BaseClass\ThreadProgressInterface.h"
#ifndef _PSX_IDE_QT_
#include "..\..\..\Module\DialogBase\DynDialogEx.h"
#include "ScdFileRWDlg.h"
#endif

#ifdef _USE_DATATYPETEMPLATES_READ_
#include "..\..\..\SCLCompareCheck\Module\SclCheckDataMngr\SclDataTemplates.h"
#endif

#include <list>

typedef struct 
{
	CString inPath;
	CString inLNDesc;
	CString inDODesc;
	CString inDADesc;
	CString outPath;

	CString inputRef_cdc;//zhow:20170802
	CString inputRef_type;//zhow:20170802

	long index;
}EXTREFINFO;

typedef struct _scl_node_path
{
	SCL_IED *scl_ied;
	SCL_AP  *scl_ap;
	SCL_LD  *scl_ld;
	SCL_LN  *scl_ln;
}SCL_NODE_PATH, *PSCL_NODE_PATH;

inline void _scl_init_node_path(SCL_NODE_PATH &scl_path, SCL_IED *scl_ied,SCL_AP  *scl_ap,SCL_LD  *scl_ld,SCL_LN  *scl_ln)
{
	scl_path.scl_ied = scl_ied;
	scl_path.scl_ap = scl_ap;
	scl_path.scl_ld = scl_ld;
	scl_path.scl_ln = scl_ln;
}

inline void scl_get_ln_name(SCL_LN  *scl_ln, ST_CHAR *lnName)
{
#ifdef SCL_USE_MMS_STRING_
	if (MAX_IDENT_LEN < (mms_str_length(&scl_ln->prefix) + mms_str_length(&scl_ln->lnClass) +mms_str_length(&scl_ln->inst)))
	{
		return;
	}

	strcpy (lnName, mms_string(&scl_ln->prefix));
	strcat (lnName, mms_string(&scl_ln->lnClass));
	strcat (lnName, mms_string(&scl_ln->inst));
#else
	strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
	strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
	strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
#endif
}

inline void scl_get_ln_name(SCL_LN  *scl_ln, CString &lnName)
{
#ifdef SCL_USE_MMS_STRING_
	lnName.Format(_T("%s%s%s"),mms_string(&scl_ln->prefix),mms_string(&scl_ln->lnClass),mms_string(&scl_ln->inst));
#else
	lnName.Format(_T("%s%s%s"),scl_ln->prefix,scl_ln->lnClass,scl_ln->inst);
#endif
}

#include "SclIecCfgDatas.h"
class CSclStation;

class CSclFileRead : public CExBaseList
{
public:
	CSclFileRead();   // 标准构造函数
	virtual ~CSclFileRead();

	SCL_IED* GetRefIED(CSclIed *pIed);
	void SetRefIED(CSclIed *pIed, SCL_IED *p_SCL_IED);

	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);

public:
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		    static UINT ReadSCLThread (LPVOID pParam );//cgl：只为检测SCD读写文件用
			BOOL 	ReadSclFile(const CString &strFile, CWnd *pOwnerWnd,  CSclStation *pSclStation);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//void ReadGSSVControl(CSclIed *pIed, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut);
	void ReadGSSVChannels(CSclCtrls *pCtrls);
	//BOOL ReadGSSVControl(CExBaseList *pList);
	BOOL IsInReadState()	{	return m_bIsInReadState;	}
	void Free_SCL_INFO();
	SCL_INFO* GetSCL_INFO(){return &m_SclInfo;}
	//CSclCtrlGsOut* FindGooseOutput(const CString &strIedName, const CString &strGsID);
	//CSclCtrlSmvOut* FindSmvOutput(const CString &strIedName, const CString &strSmvID);

protected:
	BOOL m_bSclIedSaveDvm;   //解析SCD时，是否给每个IED保存DvmDevice
	CString m_strFile;
	//文件存储结构
	SCL_INFO		m_SclInfo;
	CWnd            *m_pOwnerWnd;
	CSclStation   *m_pSclStation;
	CThreadProgressInterface *m_pThreadProgress;
	BOOL m_bIsInReadState;
#ifndef _PSX_IDE_QT_
	CScdFileRWDlg  *m_pScdFileRWDlg;
#endif
	SCL_IED *m_pRefIED;
	CWinThread *m_pReadThread;

	BOOL m_bCan_Free_SCL_INFO;


public:
	CSclStation* GetSclStation(){return m_pSclStation;}
	void MoveProgressWindow(CRect rc);
	void SetProgessInterface(CThreadProgressInterface *pInterface);
	void SetIedSaveDvm(BOOL bSave)	{	m_bSclIedSaveDvm = bSave;	}

protected:
//	BOOL m_bIsInReadState;
	bool InitListColumn(void);

	//读取文件线程
	//static UINT ReadSCLThread( LPVOID pParam );

	//读取GOOSE、SV信息
	void ReadStationInfo();
	void ReadIedInfoAndCtrls(SCL_INFO* scl_info);
	void ReadLdDataset(SCL_LN *scl_ln0, SCL_AP *scl_ap, CDvmLogicDevice *pDvmLdevice);

	void ReadLdRptCtrl(SCL_LN *scl_ln0, SCL_AP *scl_ap, CDvmLogicDevice *pDvmLdevice);//zhow
	void ReadLdLogCtrl(SCL_LN *scl_ln0, SCL_AP *scl_ap, CDvmLogicDevice *pDvmLdevice);//zhow

#ifdef _USE_DATATYPETEMPLATES_READ_
	void ReadDataTypeTemplates(SCL_INFO* scl_info);
#endif

	void ReadIedCtrls(SCL_LN *scl_ln0, SCL_AP *scl_ap, CSclIed *pIed);
	void ReadAllIedAddr();

	//dataset是否为GOOSE或SV
	bool IsDatasetInGSSV(SCL_LN *sclln, char *dataset);

	//获取dataset/fcda信息--类型和描述
	ST_RET GetFCDAInfo(SCL_INFO *sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda);


	//获取dataset/fcda节点类型
#ifdef SCL_USE_MMS_STRING_
	void GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &lntype);
	void GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &lntype,CDvmData *pDvmData);
#else
	void GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, ST_CHAR *lntype);
	void GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, ST_CHAR *lntype,CDvmData *pDvmData);
#endif

	
	//获取Inputs/ExtRef节点描述
	ST_RET GetExtRefDesc(SCL_AP *sclap, SCL_EXTREF *sclextref);

	void ReadGSSVChannelDOType(char *lnType,char *extrefdoName , SCL_EXTREF *sclextref);

	void ReadGSSVChanelDaType( SCL_EXTREF *sclextref ,char *extrefdaName);

	void ReadGSSVChanelBDA(char *extrefdoName ,SCL_DA *scl_da , SCL_EXTREF *sclextref);

	//查找节点类型
#ifdef SCL_USE_MMS_STRING_
	void FindDoType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &lntype, CString &dotype, CString &fcdadodaName);
	void FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype, CString &datype, CString &fcdadodaName);
	void FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype, CString &datype, CString &fcdadodaName,CDvmData *pDvmData);

	void FindFinalType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &datype, CString &fcdadodaName);
	void FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype);
	void FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype,CDvmData *pDvmData);
	void FindFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &datype);
#else
	void FindDoType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *lntype, char *dotype, char *fcdadodaName);
	void FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName);
	void FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName,CDvmData *pDvmData);

	void FindFinalType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype, char *fcdadodaName);
	void FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype);
	void FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype,CDvmData *pDvmData);
	void FindFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype);
#endif


//cgl
		ST_RET LogFCDAInfo(SCL_INFO *sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda, CDvmData *pDvmData);	//获取非Goose和SV节点的FCDA信息
#ifdef SCL_USE_MMS_STRING_
		void GetValueType(SCL_INFO *sclinfo,SCL_FCDA * sclfcda, CString &lntype,CString &FinalDaType);     //获取value的最终数值类型
		void FindValueDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype, CString &datype, CString &fcdadodaName,CString &FinalDaType);//重置查找节点类型
		void FindValueDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype,CString &FinalDaType);//重置查找节点类型
		void FindValueFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &datype,CString &FinalDaType);//重置查找节点类型
#else
		void GetValueType(SCL_INFO *sclinfo,SCL_FCDA * sclfcda, ST_CHAR *lntype,char *FinalDaType);     //获取value的最终数值类型
		void FindValueDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName,char *FinalDaType);//重置查找节点类型
		void FindValueDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype,char*FinalDaType);//重置查找节点类型
		void FindValueFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype,char*FinalDaType);//重置查找节点类型
#endif

		BOOL IsCreateValue(SCL_DAI *scldai);//判断是否有嵌套结构，需要创建Value


	//查找Inputs/ExtRef节点的ldName,lnName,doName
	void FindextrefName(SCL_EXTREF *sclextref, char *ldName, char *lnName, char *doName ,char *daName);

	//字符串中用'$'替换'.'
	void ReplaceDotToDollar(char *srcStr);

	//构造节点描述名dU
	void ConfigDescName(char *srcStr);
	
	//构造节点描述名desc
	void ConfigDoiName(char *srcStr);
	void ConfigDoiName(CString &srcStr);
	
	//查找$/.之前的字符串
	bool FindDelStr(char *srcStr, char *findStr);
	bool FindDelStr(CString &srcStr, CString &findStr);
	bool FindContinueDelStr(char *srcStr, char *findStr);
	//UTF8转换为多字节
	bool UTF8ToMultiByte(char *srcStr);
	bool UTF8ToMultiByte(CString &srcStr);

	void ReadGSSVControl(SCL_INFO *sclinfo, CSclIed *pIed/*CString iedName*/, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut);
	void FindGSOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
						const char *apName, const char *ldName,const char *ldDesc, const char *lnName, CSclCtrlsGsOut *pGsOuts);

	void FindSVOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
						const char *apName, const char *ldName,const char *ldDesc,const  char *lnName, CSclCtrlsSmvOut *pSmvOuts);

	void FindGSConnectAP(SCL_INFO *sclinfo, const char *iedName, const char *apName, 
						const char *ldName,const  char *gcbName, CSclCtrlGs *pGs);

	void FindSVConnectAP(SCL_INFO *sclinfo, const char *iedName, const char *apName, 
						const char *ldName, const char *svcbName, CSclCtrlSmv *pSmv);

	void FindGSSVOutChannelInfo(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase);

	void FindGSSVInChannelInfo(SCL_INFO *sclinfo, /*CString dataset,*/ CSclCtrlBase *pCtrlBase);

	void FindOutChannel(SCL_LN *sclln, char *iedName, CSclCtrlBase *pGout);

	void FindInChannel(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase, 
						std::list<EXTREFINFO> *listextref);

	bool ChangeCheckItem(int nItem);

	void FindGSSVInputs(SCL_INFO *sclinfo, SCL_LN *sclln, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path);

	void FindGSSVInControl(SCL_INFO *sclinfo, std::list<CString> *listied, 
							std::list<CString> *listextref, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path);

	void FindGSINControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
						const char *iedDesc, const char *apName,  const char *ldName,const char *ldDesc, const char *lnName, 
						std::list<CString> *listied,  std::list<CString> *listextref, CSclCtrlsGsIn *pGsIns
						, SCL_NODE_PATH &scl_path);

	void FindSVINControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
						const char *iedDesc, const char *apName, const  char *ldName,const char *ldDesc, const char *lnName, 
						std::list<CString> *listied,  std::list<CString> *listextref, CSclCtrlsSmvIn *pSmvIns
						, SCL_NODE_PATH &scl_path);

	bool IsOutGSSVHaveInGSSVChannel(SCL_LN *sclln, const char *dataset, const char *iedName, 
								std::list<CString> *listextref);

	void ChangeFCDAMap(SCL_INFO *sclinfo, CString dataset, 
					CString itemtext, CString itemPath);

	//void ChangeDataSetMap(SCL_INFO *sclinfo, CString dataset, CString itemtext);

	void GetSelectInfo(UINT iType);

	bool IsClickLControlCheckbox();

public:
	void ReadIedDetail(CSclIed *pIed);
	BOOL GetAndSaveDeviceModel(const CString &strDeviceModelPath,const CString &strIEDName);//从当前scd中查找IedName,导出对应Dev设备数据模型文件
	BOOL GetDvmFileFromSCL(const CString &strSclFile,const CString &strIedName,const CString &strSaveDvmFile);//比较当前scd与传入的路径是否一致，并从该scd中查找指定ied，导出设备数据模型
	//void ReadIedDetail_Ctrls(CSclIed *pIed, CSclCtrls *pCtrls);
	void Valid_dU_DescString(CString &strName,char *pFCDA_LdName,long nMaxLenth);
};



#endif
