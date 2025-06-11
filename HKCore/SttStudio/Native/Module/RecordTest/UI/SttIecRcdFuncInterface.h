#ifndef SttIecRcdFuncInterface_H
#define SttIecRcdFuncInterface_H

#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceSmvCh.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGooseCh.h"

#define IECRCD_FUNC_SttIecRcdSmvFuncs  "IecRcdSmvFuncs"
#define IECRCD_FUNC_IecRcdGooseFuncs  "IecRcdGooseFuncs"

#define	IECRCD_FUNC_Smv_ChAttr           	"Smv_ChAttr"  //通道属性设置
#define	IECRCD_FUNC_Smv_ChQualitySpy        "Smv_ChQualitySpy"  //通道监视
#define	IECRCD_FUNC_Smv_EffecValue   	    "Smv_EffecValue"  //有效值
#define	IECRCD_FUNC_Smv_Wave	            "Smv_Wave"        //波形分析
#define	IECRCD_FUNC_Smv_Vector	            "Smv_Vector"      //向量
#define	IECRCD_FUNC_Smv_Sequence	        "Smv_Sequence"    //序分量
#define	IECRCD_FUNC_Smv_Power	            "Smv_Power"       //功率
#define	IECRCD_FUNC_Smv_Harm	            "Smv_Harm"        //谐波
#define	IECRCD_FUNC_Smv_Polar	            "Smv_Polar"       //极性
#define	IECRCD_FUNC_Smv_PkgError	        "Smv_PkgStc"      //报文统计
#define	IECRCD_FUNC_Smv_AD	                "Smv_AD"          //双AD分析
#define	IECRCD_FUNC_Smv_PkgAnalyze	        "Smv_PkgAnalyze"  //报文分析
#define	IECRCD_FUNC_Smv_MUAccuracy	        "Smv_MUAccuracy"  //MU精确度
#define	IECRCD_FUNC_Smv_MUErrorStatistics	"Smv_MUErrorStatistics"  //MU误差统计
#define	IECRCD_FUNC_Smv_MUTimingAccur   	"Smv_MUTimingAccur"  //MU时间精度测试
#define IECRCD_FUNC_Smv_MUFirstCycleTest	"Smv_MUFirstCycleTest"//首周波测试

#define	IECRCD_FUNC_Smv_HarmAnalyze         "Smv_HarmAnalyze" //谐波分析chenling 2024.5.29


#define	IECRCD_FUNC_Goose_RT	            "Goose_RT"        //实时值
#define	IECRCD_FUNC_Goose_TurnList	    "Goose_TurnList"  //变位列表
#define	IECRCD_FUNC_Goose_PkgStc	        "Goose_PkgStc"    //报文统计
#define	IECRCD_FUNC_Goose_PkgAnalyze	    "Goose_PkgAnalyze"//报文分析
#define	IECRCD_FUNC_Goose_TurnSpy	    "Goose_TurnSpy"   //变位监视
#define	IECRCD_FUNC_Write_File	    "Write_File"   //写文件


#define	IECRCD_FUNC_FT3_RT	            "FT3_RT"        //实时值
#define IECRCD_FUNC_FT3_OriginalMsg	"FT3_OriginalMsg"	//原始报文


class CSttIecRcdFuncInterface
{
public:
	CSttIecRcdFuncInterface();
	virtual ~CSttIecRcdFuncInterface();

	QWidget *m_pIecRcdFuncWidget;
	CString m_strIecRcdFuncID;
	CExBaseObject *m_pCapDevice;
	BOOL m_bMUTestMode;

public:
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release() = 0;

	virtual BOOL NeedNextAndPrev();
	virtual BOOL NeedAddToSubPub();
	virtual void NextPage();
	virtual void PrevPage();
	virtual void AddToSub();
	virtual void AddToPub();

	virtual BOOL NeedConfig();
	virtual void Config();//页面功能配置
	virtual void UpdateChName();//更新通道名称 2023.6.25 zhouhj

	//2022-5-28  lijunqing
	//数据集下以DvmData展示的控制块分析结果：根据CapDevice，获取DvmData
	BOOL FindDvmDataForCtrl(CCapDeviceBase *pCapDevice, const CString &strDatasetID, CDvmDataset **ppDsRet, CDvmData **ppDataRet);

	//20240710 suyang 在SCD文件相同，IEC配置中已经将探测到的GOOSE控制块添加到订阅，无需在添加，隐藏至订阅按钮
	BOOL IsToSubBtn();//判断IEC GOOSE订阅数据中是否存选择的控制块

};

CString stt_iec_rcd_get_ch_value_string(CDvmValue *pCh, BOOL bWithUnit,const CString &strUnit);
CString stt_iec_rcd_get_ch_value_string(CDvmValue *pCh, BOOL bWithUnit, double &dMag, double &dAng,const CString &strUnit,long nPrecision = -1);
CString stt_iec_rcd_get_double_string(double dValue,long nPrecision);

#endif // SttIecRcdFuncInterface_H
