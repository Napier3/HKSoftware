#pragma once

#include "GbScript_GlobalDefine.h"


//////////////////////////////////////////////////////////////////////////
//��Ŀ������ز�������
//////////////////////////////////////////////////////////////////////////

//��ת����Ŀ
void GBS_GotoItem(const char* pszItemPath);
void GBS_GotoItemEx(const char* pszItemPath, long nRslt, long nAndOr);

void GBS_FireTestNextMsg();      //ֻ��������е�ͨѶ���Ŀǰֻ֧����ʾ��Ϣ
void GBS_BreakLoop(long nLevel);

//������Ϣ
void GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara);
void GBS_MtRegistPpDataMsg(const char *pszDvmDataPath);
void GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath);
void GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax);
void GBS_BreakItems(long nLevel);
void GBS_SetUploadRptFile(const char *pszFileName);

void GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam);
void GBS_MtUnRegistCmdMsg(const char *pszCmdID);

//���ݼ�����
double GBS_GetDsDataValue(const char* pszID);
double GBS_GetDsDataAttr(const char* pszID, const char *pszAttrID);
void GBS_SetDsDataValue(const char* pszID, double dVal);
const char* GBS_GetDsDataValueStr(const char* pszID);
void GBS_SetDsDataValueStr(const char* pszID, const char* pszVal);
double GBS_GetDsDataValueEx(long nDeviceIndex, const char* pszID);
void GBS_SetDsDataValueEx(long nDeviceIndex, const char* pszID, double dVal);
const char* GBS_GetDsDataValueStrEx(long nDeviceIndex, const char* pszID);
void GBS_SetDsDataValueStrEx(long nDeviceIndex, const char* pszID, const char* pszVal);
long GBS_CalAinError(const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinErrorEx(double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinErrorNom(double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr);
long GBS_CalAinStdError(double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinStdError2(const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinError2(const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr);

double GBS_CalVariation(double dValue, double dTheoreticalVal, double dBaseValue, double dRate);
long GBS_CalVariationErr(double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr);
long GBS_CalVariationErrEx(const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate);

long GBS_FlterCalErrorMax(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_FlterCalErrorMin(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);

// ��ȡ��ֵ����
// pszID�����ݵ�ID
double GBS_GetSetValue(const char* pszID);
void GBS_SetSetValue(const char* pszID, double dVal);

double GBS_GetSoftswitchValue(const char* pszID);
void GBS_SetSoftswitchValue(const char* pszID, double dVal);

// ��ȡϵͳ������������
// pszID�����ݵ�ID
double GBS_GetSysParaValue(const char* pszID);

void GBS_SetSysParaValue(const char* pszID, double dValue);

// ��ȡ���Բ�������
// pszID�����ݵ�ID
double GBS_GetTestParaValue(const char* pszID);
const char* GBS_GetTestParaStr(const char* pszID);

// ���ò��Բ�������
// pszID�����ݵ�ID
void GBS_SetTestParaValue(const char* pszID, double dValue);
void GBS_SetTestParaStr(const char* pszID, const char *pszValue);

//����������������Ŀ��Show����
//pszItemPathΪItem��·��
void GBS_SetItemShow(const char* pszItemPath, long nShow);

// ��ȡ������������Ŀ��Show����
// pszItemPathΪItem��·��
long GBS_GetItemShow(const char* pszItemPath);

// ����������������Ŀ��Enable����
// pszItemPathΪItem��·��
void GBS_SetItemEnable(const char* pszItemPath, long nEnable);

// ��ȡ������������Ŀ��Enable����
// pszItemPathΪItem��·��
long GBS_GetItemEnable(const char* pszItemPath);

//Seelct
void GBS_SetItemSelect(const char* pszItemPath, long nSelect);
long GBS_GetItemSelect(const char* pszItemPath);

// ����������������Ŀ��Name����
// pszItemPathΪItem��·��
void GBS_SetItemName(const char* pszItemPath, const char* pszName);

// ��ȡ������������Ŀ��Name����
// pszItemPathΪItem��·��
const char* GBS_GetItemName(const char* pszItemPath);

// ����������������Ŀ�Ľ���ж�
// pszItemPathΪItem��·��
void GBS_SetItemResultJudge(const char* pszItemPath, long nResult);

long GBS_GetItemResultJudge(const char* pszItemPath);


// ����������������Ŀ�����ݵ�ֵ
// pszItemPathΪItem��·��
void GBS_SetItemParaValue(const char* pszItemPath, const char* pszValID, double dValue);
void GBS_SetItemParaValueStr(const char* pszItemPath, const char* pszValID, const char *pszValue);

double GBS_GetItemParaValue(const char* pszItemPath, const char* pszValID);
const char* GBS_GetItemParaString(const char* pszItemPath, const char* pszValID);
const char* GBS_GetItemTestTime(const char* pszItemPath);
const char* GBS_GetItemTestBeginTime(const char* pszItemPath);
const char* GBS_GetItemTestEndTime(const char* pszItemPath);

//ͨѶ����Ĳ����ű�����  2019-3-19
void GBS_ClearCommCmdParas(const char* pszItemPath);
void GBS_AddCommCmdParaValue(const char* pszItemPath, const char* pszValID, double dValue);
void GBS_AddCommCmdParaValue_Long(const char* pszItemPath, const char* pszValID, long nValue);
void GBS_AddCommCmdParaValue_String(const char* pszItemPath, const char* pszValID, const char *pszValue);

//////////////////////////////////////////////////////////////////////////
//���汨�����ݴ���,����ǰ��Ŀ�ı�������
//////////////////////////////////////////////////////////////////////////
//��װ�á����ݿ�ģʽ�£���ʱ��¼��ͨ�����RptDataMap��֤���ݲ������
void GBS_AddRptMapData(const char* pszValID);

//���ñ�������
void GBS_SetItemReportValue(const char* pszItemPath, const char* pszValID, double dValue);
void GBS_SetItemReportValueString(const char* pszItemPath, const char* pszValID, const char* pszValString);

//��ȡ�������ݣ����ظ�����
double GBS_GetItemReportValue(const char* pszItemPath, const char* pszValID);
//��ȡ�������ݣ���������
long GBS_GetItemReportValueLong(const char* pszItemPath, const char* pszValID);
//��ȡ�������ݣ�����string
const char* GBS_GetItemReportValueString(const char* pszItemPath, const char* pszValID);

double GBS_GetItemReportValueEx(const char* pszItemPath, const char* pszValID, long nIndex);
long GBS_GetItemReportValueLongEx(const char* pszItemPath, const char* pszValID, long nIndex);
const char* GBS_GetItemReportValueStringEx(const char* pszItemPath, const char* pszValID, long nIndex);
long GBS_GetItemReportCount(const char* pszItemPath);
void GBS_ClearReports(const char* pszItemPath);
double GBS_CalRptValMax(const char* pszItemPath, const char* pszValID, double dDefVal);
double GBS_CalRptValMin(const char* pszItemPath, const char* pszValID, double dDefVal);
double GBS_CalRptValAvg(const char* pszItemPath, const char* pszValID, double dDefVal);

//��ȡ���������ı������ݵĸ���������������ID������ֵ
long GBS_LGetItemReportDataCount(const char* pszItemPath, const char *pszDataID, long nDataValue);

//////////////////////////////////////////////////////////////////////////
//��չ��������
//////////////////////////////////////////////////////////////////////////
//��ȡ��չ�������ݵ�CReport->m_pRptDataEx
//nIndex���������������
//pszValID�����ݵ�ֵID
double GBS_GetItemReportExValue(long nIndex, const char* pszValID);
double GBS_GetItemReportExValue_D(const char* pszDataID, const char* pszValID);
long   GBS_GetItemReportExValue_L(const char* pszDataID, const char* pszValID);
char*  GBS_GetItemReportExValue_S(const char* pszDataID, const char* pszValID);
char* GBS_GetFileInReportEx(const char *pszFilePostfix, long nFileIndex);
long GBS_GetFileNumInReportEx(const char *pszFilePostfix);

//��ñ����������ݸ���
long GBS_GetItemReportExCount();

//����ID�����Ŀ�ı�������ݸ���
long GBS_GetItemReportExDataCountByID(const char* pszDataAttrID);

//����ID�Լ�Ҫ��ȡ��ID�ĵڼ������ݷ������ڱ����ж�Ӧ��Indexֵ��nIndex��0��ʼ 
long GBS_GetItemReportDataIndexByIDIndex(const char* pszDataAttrID, long nIndex);

long GBS_CalTimeGapStr(const char* pszTime1, const char* pszTime2);
long GBS_CalTimeGapStr_us(const char* pszTime1, const char* pszTime2);
long GBS_CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID);
long GBS_CalItemReportTimeGapEx(long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2);
long GBS_CalItemReportTimeGapEx2(long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2);

//�������
void GBS_FilterInit();
long GBS_FilterReportExEqualValueL(const char* pszDataAttrID, long nAttrValue);
long GBS_FilterReportExEqualValueStr(const char* pszDataAttrID, const char* pszValue);
long GBS_FilterReportExHasValueStr(const char* pszDataAttrID, const char* pszValue);
long GBS_FilterReportExHasNoValueStr(const char* pszDataAttrID, const char* pszValue);
void GBS_FilterCombineReportEx(const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator);

long GBS_FilterRptExQuery(const char* pszQuery);
long GBS_FilterRptExGetCount();
long GBS_FilterRptExGetLong(long nIndex, const char* pszDataAttrID);
char* GBS_FilterRptExGetString(long nIndex, const char* pszDataAttrID);
double GBS_FilterRptExGetDouble(long nIndex, const char* pszDataAttrID);

long GBS_FilterRptExGetValCount(long nDataIndex);
long GBS_FilterRptExGetValLong(long nDataIndex, const char* pszValIndex);
char* GBS_FilterRptExGetValString(long nDataIndex, const char* pszValIndex);
double GBS_FilterRptExGetValDouble(long nDataIndex, const char* pszValIndex);
long GBS_FilterRptExCalValError(long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr);
long GBS_FilterRptExCalValErrorEx(const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr);

double Gbs_FilterRptExQueryUseErr(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseErrEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseAvg(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseAvgEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);
long Gbs_FilterRptExQueryClearNotUse();

//########################################################################
//���������������������������ı�������
//########################################################################
//��չ��������ΪCDvmDataset��������ΪCDvmData����
//CTag�����ʾһ�����ݵ�ֵ
//��ͨ��������ΪCValues*��������ֵΪCValue����
//���ԣ�����ͨ�������ݵĴ������չ�������ݵĴ���ʽ��һ��

//ѡ��ĳ����Ŀ
long GBS_SSelectItem(const char *pszItemPath);

//��ͨ���洦����******************************************************

//��õ�ǰѡ�����Ŀ�ı���ĸ���
long GBS_SGetItemReportCount();

//ѡ����Ŀ�ı������
long GBS_SSelectItemReport(long nReportIndex);

//�����Ŀ��ָ���ı�������ݣ�������
double GBS_SGetItemReportValue(const char* pszValID);

//�����Ŀ��ָ���ı�������ݣ�����
long GBS_SGetItemReportValueLong(const char* pszValID);

//�����Ŀ��ָ���ı�������ݣ��ַ���
const char* GBS_SGetItemReportValueString(const char* pszValID);

//�����Ŀ��ָ���ı�������ݸ���
long GBS_SGetItemReportValueCount();   

//��ȡ����ĵ�nDataIndex���ݵ�ֵ
double GBS_SGetItemReportValue2(long nDataIndex);  
long GBS_SGetItemReportValueLong2(long nDataIndex);
const char* GBS_SGetItemReportValueString2(long nDataIndex);

//��չ���洦����******************************************************

//�����Ŀ��ָ���ı�������ݸ���
long GBS_SGetItemReportExDataCount();

//�����Ŀ��ָ���ı�������ݣ�������
double GBS_SGetItemReportExDataValue(long nDataIndex, const char* pszValID);

//�����Ŀ��ָ���ı�������ݣ�����
long GBS_SGetItemReportExDataValueLong(long nDataIndex, const char* pszValID);

//�����Ŀ��ָ���ı�������ݣ�����
const char* GBS_SGetItemReportExDataValueString(long nDataIndex, const char* pszValID);
// 
// //�����Ŀ��ָ���ı�������ݣ�������
// double GBS_SFindItemReportExDataValue(const char* pszValID);
// 
// //�����Ŀ��ָ���ı�������ݣ�����
// long GBS_SFindItemReportExDataValueLong(const char* pszValID);
// 
// //�����Ŀ��ָ���ı�������ݣ�����
// const char* GBS_SFindItemReportExDataValueString(const char* pszValID);

//���ݼ��жϺ�������
//�����Ŀ��ָ���ı�������ݸ���
long GBS_RptExDsGetCount(const char* pszPath);

//�����Ŀ��ָ���ı�������ݣ�������
double GBS_RptExDsGetValueD(const char* pszPath, long nIndex);

//�����Ŀ��ָ���ı�������ݣ�����
long GBS_RptExDsGetValueL(const char* pszPath, long nIndex);

//�����Ŀ��ָ���ı�������ݣ�����
const char* GBS_RptExDsGetValueStr(const char* pszPath, long nIndex);

//������֤
void GBS_RptExDsValidClear();
void GBS_RptExDsValidAddElement(const char* pszText, long nOption, long nUnbound);
void GBS_RptExDsValidAddElementChoice(const char* pszText, long nOption, long nUnbound);
long GBS_RptExDsValid(long nValidateHead);

long GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara);
long GBS_AdjustWord(long nPopDlg);

void GBS_CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2);
void GBS_CalSoeTimeEx(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2);
void GBS_SetSoeTripDesc(const char *pszRptID, const char *pszSoeID);
long GBS_CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr);
long GBS_CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr);


//Record
long GBS_RcdSetProgID(const char* pszRcdProgID);
long GBS_RcdExit();
long GBS_RcdConfig(const char* pszPara);
long GBS_RcdSelect(const char* pszPara);
long GBS_RcdValidate(const char* pszRsltID);
long GBS_RcdCmpClear();
long GBS_RcdCmpInit(const char* pszRcdFilePathRoot, long nCreateTestTimesDir);
long GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile);
long GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir);
long GBS_RcdAnalyse(const char* pszRcdFile);
long GBS_RcdSetPath(long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir);

//�ظ��������
long GBS_GetRepeatTimes(const char* pszItemPath);
long GBS_GetRepeatSuccTimes(const char* pszItemPath);

//
void GBS_SetCmdZoneIndex(long nZoneIndex);

//��������ֵ����ʼֵ����ֵֹ
void Gbs_ValidBeginEndValRange(const char *pBeginValID, const char *pEndValID
							   , const char *pStepID, double dMinRange, double dMinStep
							   , long nMinSteps, long nMaxSteps, long nUseNeg);

//ʱ���������
void Gbs_SetTmTriggerSecond(long nSecond, long nOptr);
void Gbs_SetTmTriggerCountMinute(long nMinute);
void Gbs_EnterTmTrigger();
void Gbs_StartTimerTigger();
void Gbs_StopTimerTrigger();

//������Լ
double Gbs_ValueRevised(double dValue, long nDots);

//////////////////////////////////////////////////////////////////////////
//��־����
long Gbs_log_query_clear();
long Gbs_log_query_time(const char *pszBeginTine, const char *pszEndTime);
long Gbs_log_query_entryid(const char *pszEntryID);
long Gbs_log_query_logctrl(const char *pszLogCtrl);
long Gbs_log_query_dataset(const char *pszDataset);

long Gbs_log_query_data_clear();
long Gbs_log_query_data(const char *pszDataID);
long Gbs_log_query_data_get_count();
long Gbs_log_query_data_add_to_rpt();

long Gbs_log_query(const char *pszScript);

long Gbs_log_get_count();
const char* Gbs_log_get_attr(long nLogIndex, const char *pszAttr);
long Gbs_log_get_data_count(long nLogIndex);
const char* Gbs_log_get_data_attr(long nLogIndex, long nDataIndex, const char *pszAttr);
const char* Gbs_log_get_data_attr2(long nLogIndex, const char *pszDataID, const char *pszAttr);

//////////////////////////////////////////////////////////////////////////
//�ַ�������
long GBS_InitStrTok(const char *pszString, const char *pControl);
long GBS_StrTokCount();
const char* GBS_StrTokIndex(long nIndex);
const char* GBS_StrTokNext();

//װ�õ�ȫ�ֲ���
void GBS_SetGlobal_Str(const char *pszID, const char *pszValue);
void GBS_SetGlobal_Long(const char *pszID, long nValue);
void GBS_SetGlobal_Float(const char *pszID, float fValue);

const char* GBS_GetGlobal_Str(const char *pszID);
long GBS_GetGlobal_Long(const char *pszID);
float GBS_GetGlobal_Float(const char *pszID);
long GBS_GetGlobal_Long2(const CString &strID);

void GBS_Set_TestError(const char *pszTestError);

long GBS_BinRslt(const char *pszParaID, const char *pszRsltID);
long GBS_BinStateRslt(const char *pszParaID, const char *pszRsltID);
long GBS_BinChngCntRslt(const char *pszBinChngData, const char *pszRsltID);
/*long GBS_BinRsltEx(const char *pszParaDatas, const char *pszRsltDatas);*/

//2019-1-6:�������ݶ����Ƿ�ϸ�Ĺ���   lijq
void GBS_Set_AddDataErrorValueToRpt(long nValue);
void GBS_AddDataErrorToRpt(const char* pszDataID, long nValue);

//2019-6-5  ���Լ�¼�ļ����
const char* GBS_GetTemplateFile(long nWithPath);
const char* GBS_GetGbrptFile(long nWithPath);
void GBS_SetGbrptFileName(const char *pszFileName);

//2019-7-19     ����װ�õı�ţ���������ʱ��
void GBS_OffsetTestDataByGbrptIndex(const char *pszDestDataID);

//2020-05-22   ���ܰ汾�ȶԹ���  shaolei��
long GBS_VersionInfoCompare (const char* pszPath, const char* pszFilePath);

//2020-07-24  ����ͼ��������
void GBS_SetComtradeDrawLineMode(const char *pszMode);

