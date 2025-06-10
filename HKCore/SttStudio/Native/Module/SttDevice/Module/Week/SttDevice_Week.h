#pragma once
#include "../../../SttTest/Common/tmt_common_def.h"
#ifdef _MainBoard_PTU_

#else
    #include "../Driver466/SttDeviceComm.h"
#endif

extern int g_nWeekTap;
extern int WeekTap[4][ADJUST_MAX_CHANNEL_COUNT];

void WeekGradientPreProcess(float &fStart, float &fEnd, float &fStep, long &nStepCnt,
                            long &nSign, long GradientType, PSTT_MODULE pModule, long nChannel, long nHarmIndex);

//PN主板小信号 50K
void TransAnalogToDrv_Week_PN_Main(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

void Manual_Week_PN_Main(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
                      BOOL bIsDc, BOOL bIsModuleOutput);

void State_Week_PN_Main(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_PN_Main(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                              BOOL bIsDc, int nStatus);

//PIA48S 25K
void TransAnalogDCToDrv_Week_PIA48S(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);

long TranslateACAmp_Week_PIA48S(float fAmp, int nChannel, int nModuleIndex, int nHarm);

void TransAnalogToDrv_Week_PIA48S(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

void Manual_Week_PIA48S(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
                        BOOL bIsDc, BOOL bIsModuleOutput);

void State_Week_PIA48S(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_PIA48S(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                BOOL bIsDc, int nStatus);

//PIA12DS
void TransAnalogDCToDrv_Week_PIA12DS(float fAmp, int nChannel, int nModuleIndex, long *pDrvData);

void Manual_Week_PIA12DS(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput = FALSE);

void State_Week_PIA12DS(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_PIA12DS(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                 BOOL bIsDc, int nStatus);

int GetTapCode_PIA12DS(float *fMaxOut, BOOL bStateTest, int *nTap);

//EVTECT 同模拟量的频率计算公式 400K
void TransAnalogDCToDrv_Week_EVTECT(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);

long TranslateACAmp_Week_EVTECT(float fAmp, int nChannel, int nModuleIndex, int nHarm);

void TransAnalogToDrv_Week_EVTECT(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

void Manual_Week_EVTECT(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
                        BOOL bIsDc, BOOL bIsModuleOutput);

void State_Week_EVTECT(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_EVTECT(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                BOOL bIsDc, int nStatus);

int GetTapCode_EVTECT(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc, int *nTap);

//EVTECT_Ex1 直流增量插件
void TransAnalogDCToDrv_Week_EVTECT_Ex1(float fAmp, int nChannel, int nModuleIndex, long *pDrvData);

void Manual_Week_EVTECT_Ex1(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput);

void State_Week_EVTECT_Ex1(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void State_Gradient_Week_EVTECT_Ex1(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
                                    int nIndex);

void Gradient_NormalWeek_EVTECT_Ex1(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                    BOOL bIsDc, int nStatus);

int GetTapCode_EVTECT_Ex1(float *fMaxOut, BOOL bStateTest, int *nTap);

//DC6U10V
void TransAnalogDCToDrv_Week_DC6U10V(float fAmp, int nChannel, int nModuleIndex, long *pDrvData);

void Manual_Week_DC6U10V(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput, int nTap = 0);

void State_Week_DC6U10V(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_DC6U10V(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                 BOOL bIsDc, int nStatus);

int GetTapCode_DC6U10V(float *fMaxOut, BOOL bStateTest, int *nCalTap, int nUserSetTap);

//DC6I20mA
void TransAnalogDCToDrv_Week_DC6I20mA(float fAmp, int nChannel, int nModuleIndex, long *pDrvData);

void Manual_Week_DC6I20mA(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput, int nTap = 0);

void State_Week_DC6I20mA(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_DC6I20mA(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                  BOOL bIsDc, int nStatus);

int GetTapCode_DC6I20mA(float *fMaxOut, BOOL bStateTest, int *nCalTap, int nUserSetTap);

//PNS331 50K
void TransAnalogDCToDrv_Week_PNS331(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);

long TranslateACAmp_Week_PNS331(float fAmp, int nChannel, int nModuleIndex, int nHarm);

void TransAnalogToDrv_Week_PNS331(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

void Manual_Week_PNS331(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
                        BOOL bIsDc, BOOL bIsModuleOutput);

void State_Week_PNS331(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_PNS331(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                BOOL bIsDc, int nStatus);

void State_Week_PNS331_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

int GetTapCode_PNS331(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc, int *nTap);

//PN6U6I直流插件
void TransAnalogDCToDrv_Week_PN_DC6U6I(float fAmp, int nChannel, int nModuleIndex, long *pDrvData);

void Manual_Week_PN_DC6U6I(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput = FALSE);

void State_Week_PN_DC6U6I(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_PN_DC6U6I(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
                                   BOOL bIsDc, int nStatus);

int GetTapCode_PN_DC6U6I(float *fMaxOut, BOOL bStateTest, int *nTap);

//L336D 50K
void TransAnalogDCToDrv_Week_L336D(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);

long TranslateACAmp_Week_L336D(float fAmp, int nChannel, int nModuleIndex, int nHarm);

void TransAnalogToDrv_Week_L336D(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

void Manual_Week_L336D(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
						BOOL bIsDc, BOOL bIsModuleOutput);

void State_Week_L336D(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_L336D(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								BOOL bIsDc, int nStatus);

void State_Week_L336D_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

int GetTapCode_L336D(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc, int *nTap);

//ADMU 50K
void TransAnalogDCToDrv_Week_ADMU(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero = TRUE);

long TranslateACAmp_Week_ADMU(float fAmp, int nChannel, int nModuleIndex, int nHarm);

void TransAnalogToDrv_Week_ADMU(float fAmp, float fAng, float fFre, int nChannel, int nModuleIndex, long *pnDrvData);

void Manual_Week_ADMU(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
						BOOL bIsDc, BOOL bIsModuleOutput, int nTap = 0);

void State_Week_ADMU(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

void Gradient_NormalWeek_ADMU(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								BOOL bIsDc, int nStatus);

void State_Week_ADMU_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex);

int GetTapCode_ADMU(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc,int *nCalTap, int nUserSetTap);//零值输出，校准零漂时指定档位nUserSetTap
