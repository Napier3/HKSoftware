#ifndef SttIecRcdFuncInterface_H
#define SttIecRcdFuncInterface_H

#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceSmvCh.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGooseCh.h"

#define IECRCD_FUNC_SttIecRcdSmvFuncs  "IecRcdSmvFuncs"
#define IECRCD_FUNC_IecRcdGooseFuncs  "IecRcdGooseFuncs"

#define	IECRCD_FUNC_Smv_ChAttr           	"Smv_ChAttr"  //ͨ����������
#define	IECRCD_FUNC_Smv_ChQualitySpy        "Smv_ChQualitySpy"  //ͨ������
#define	IECRCD_FUNC_Smv_EffecValue   	    "Smv_EffecValue"  //��Чֵ
#define	IECRCD_FUNC_Smv_Wave	            "Smv_Wave"        //���η���
#define	IECRCD_FUNC_Smv_Vector	            "Smv_Vector"      //����
#define	IECRCD_FUNC_Smv_Sequence	        "Smv_Sequence"    //�����
#define	IECRCD_FUNC_Smv_Power	            "Smv_Power"       //����
#define	IECRCD_FUNC_Smv_Harm	            "Smv_Harm"        //г��
#define	IECRCD_FUNC_Smv_Polar	            "Smv_Polar"       //����
#define	IECRCD_FUNC_Smv_PkgError	        "Smv_PkgStc"      //����ͳ��
#define	IECRCD_FUNC_Smv_AD	                "Smv_AD"          //˫AD����
#define	IECRCD_FUNC_Smv_PkgAnalyze	        "Smv_PkgAnalyze"  //���ķ���
#define	IECRCD_FUNC_Smv_MUAccuracy	        "Smv_MUAccuracy"  //MU��ȷ��
#define	IECRCD_FUNC_Smv_MUErrorStatistics	"Smv_MUErrorStatistics"  //MU���ͳ��
#define	IECRCD_FUNC_Smv_MUTimingAccur   	"Smv_MUTimingAccur"  //MUʱ�侫�Ȳ���
#define IECRCD_FUNC_Smv_MUFirstCycleTest	"Smv_MUFirstCycleTest"//���ܲ�����

#define	IECRCD_FUNC_Smv_HarmAnalyze         "Smv_HarmAnalyze" //г������chenling 2024.5.29


#define	IECRCD_FUNC_Goose_RT	            "Goose_RT"        //ʵʱֵ
#define	IECRCD_FUNC_Goose_TurnList	    "Goose_TurnList"  //��λ�б�
#define	IECRCD_FUNC_Goose_PkgStc	        "Goose_PkgStc"    //����ͳ��
#define	IECRCD_FUNC_Goose_PkgAnalyze	    "Goose_PkgAnalyze"//���ķ���
#define	IECRCD_FUNC_Goose_TurnSpy	    "Goose_TurnSpy"   //��λ����
#define	IECRCD_FUNC_Write_File	    "Write_File"   //д�ļ�


#define	IECRCD_FUNC_FT3_RT	            "FT3_RT"        //ʵʱֵ
#define IECRCD_FUNC_FT3_OriginalMsg	"FT3_OriginalMsg"	//ԭʼ����


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
	virtual void Config();//ҳ�湦������
	virtual void UpdateChName();//����ͨ������ 2023.6.25 zhouhj

	//2022-5-28  lijunqing
	//���ݼ�����DvmDataչʾ�Ŀ��ƿ�������������CapDevice����ȡDvmData
	BOOL FindDvmDataForCtrl(CCapDeviceBase *pCapDevice, const CString &strDatasetID, CDvmDataset **ppDsRet, CDvmData **ppDataRet);

	//20240710 suyang ��SCD�ļ���ͬ��IEC�������Ѿ���̽�⵽��GOOSE���ƿ���ӵ����ģ���������ӣ����������İ�ť
	BOOL IsToSubBtn();//�ж�IEC GOOSE�����������Ƿ��ѡ��Ŀ��ƿ�

};

CString stt_iec_rcd_get_ch_value_string(CDvmValue *pCh, BOOL bWithUnit,const CString &strUnit);
CString stt_iec_rcd_get_ch_value_string(CDvmValue *pCh, BOOL bWithUnit, double &dMag, double &dAng,const CString &strUnit,long nPrecision = -1);
CString stt_iec_rcd_get_double_string(double dValue,long nPrecision);

#endif // SttIecRcdFuncInterface_H
