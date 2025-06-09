#pragma once


#include "../DataMngr/DvmLogicDevice.h"

#define STT_RcdInit_DL_RatError                 _T("$RatError")
#define STT_RcdInit_DL_AngError                 _T("$AngError")
#define STT_RcdInit_DL_CompError                _T("$CompError")

#define STT_RcdInit_DL_MaxValue                 _T("$MaxValue")
#define STT_RcdInit_DL_MinValue                 _T("$MinValue")
#define STT_RcdInit_DL_AverageValue             _T("$AverageValue")
#define STT_RcdInit_DL_TestCount                _T("$TestCount")
#define STT_RcdInit_DL_StdErrorValue            _T("$StdErrorValue")//��׼���ֵ,���Ҫ��
#define STT_RcdInit_DL_Result                   _T("$Result")
#define STT_RcdInit_DL_RltDesc                   _T("$RltDesc")//�������
#define STT_RcdInit_DL_MaxMagValue              _T("$MaxValue$mag")
#define STT_RcdInit_DL_MaxAngValue              _T("$MaxValue$ang")
#define STT_RcdInit_DL_MaxFreqValue              _T("$MaxValue$freq")
#define STT_RcdInit_DL_ErrorLimit              _T("$ErrorLimit")

void XSttRcdInitChDvmData(CDvmData *pChDvmData, long nHarm, BOOL bIecTest);

//SV����һ���Է���
void XSttRcdInitSv_PkgAnalyze(CDvmData *pSV, const CString &strID);

//SV�����쳣����
void XSttRcdInitSv_PkgError(CDvmData *pSV, const CString &strID);

//���������ļ�����ʼ�����ķ�������
void XSttRcdInitSv_FromCfgFile(CDvmData *pSV, const CString &strID, const CString &strCfgFile);

BOOL XSttRcdInitDouble_FromDataset(CDvmDataset *pDataset,const CString &strDataID,double &dValue);
BOOL XSttRcdInitDouble_FromValue(CDvmValue *pValue,const CString &strValueID,double &dValue);

extern long g_nXSttRcdInitChDvmData_Harm;
