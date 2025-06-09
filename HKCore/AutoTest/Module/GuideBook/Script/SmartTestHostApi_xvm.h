//SmartTestHostApi.h
#ifndef _SmartTestHostApi_xvm_h__
#define _SmartTestHostApi_xvm_h__

#include "../../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../TestControlBase.h"

//GbScript_GuideBook/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ת����Ŀ
void xvm_GBS_GotoItem(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_GotoItemEx(LPVOID pXvm, const char* pszItemPath, long nRslt, long nAndOr);  //

void xvm_GBS_FireTestNextMsg(LPVOID pXvm);      //ֻ��������е�ͨѶ���Ŀǰֻ֧����ʾ��Ϣ
void xvm_GBS_BreakLoop(LPVOID pXvm, long nLevel);  //

//������Ϣ
void xvm_GBS_MtExcuteCmd(LPVOID pXvm, const char *pszCmd, const char *pCmdPara);  //
void xvm_GBS_MtRegistPpDataMsg(LPVOID pXvm, const char *pszDvmDataPath);  //
void xvm_GBS_MtUnRegistPpDataMsg(LPVOID pXvm, const char *pszDvmDataPath);  //
void xvm_GBS_MtRegistPpDataMsgRange(LPVOID pXvm, const char *pszDvmDataPath, double dMin, double dMax);  //
void xvm_GBS_BreakItems(LPVOID pXvm, long nLevel);  //
void xvm_GBS_SetUploadRptFile(LPVOID pXvm, const char *pszFileName);  //

void xvm_GBS_MtRegistCmdMsg(LPVOID pXvm, const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam);  //
void xvm_GBS_MtUnRegistCmdMsg(LPVOID pXvm, const char *pszCmdID);  //

//���ݼ�����
void xvm_GBS_GetDsDataValue(LPVOID pXvm, const char* pszID);  //
void xvm_GBS_GetDsDataAttr(LPVOID pXvm, const char* pszID, const char *pszAttrID);  //
void xvm_GBS_SetDsDataValue(LPVOID pXvm, const char* pszID, double dVal);  //
void xvm_GBS_GetDsDataValueStr(LPVOID pXvm, const char* pszID);  //
void xvm_GBS_SetDsDataValueStr(LPVOID pXvm, const char* pszID, const char* pszVal);  //
void xvm_GBS_GetDsDataValueEx(LPVOID pXvm, long nDeviceIndex, const char* pszID);  //
void xvm_GBS_SetDsDataValueEx(LPVOID pXvm, long nDeviceIndex, const char* pszID, double dVal);  //
void xvm_GBS_GetDsDataValueStrEx(LPVOID pXvm, long nDeviceIndex, const char* pszID);  //
void xvm_GBS_SetDsDataValueStrEx(LPVOID pXvm, long nDeviceIndex, const char* pszID, const char* pszVal);  //
void xvm_GBS_CalAinError(LPVOID pXvm, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_CalAinErrorEx(LPVOID pXvm, double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_CalAinErrorNom(LPVOID pXvm, double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr);  //
void xvm_GBS_CalAinStdError(LPVOID pXvm, double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_CalAinStdError2(LPVOID pXvm, const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_CalAinError2(LPVOID pXvm, const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr);  //

void xvm_GBS_CalVariation(LPVOID pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate);  //
void xvm_GBS_CalVariationErr(LPVOID pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr);  //
void xvm_GBS_CalVariationErrEx(LPVOID pXvm, const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate);  //

void xvm_GBS_FlterCalErrorMax(LPVOID pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_FlterCalErrorMin(LPVOID pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);  //

// ��ȡ��ֵ����
// pszID�����ݵ�ID
void xvm_GBS_GetSetValue(LPVOID pXvm, const char* pszID);  //
void xvm_GBS_SetSetValue(LPVOID pXvm, const char* pszID, double dVal);  //

//void xvm_GBS_GetSoftswitchValue(LPVOID pXvm, const char* pszID
// void xvm_GBS_SetSoftswitchValue(LPVOID pXvm, const char* pszID, double dVal

// ��ȡϵͳ������������
// pszID�����ݵ�ID
void xvm_GBS_GetSysParaValue(LPVOID pXvm, const char* pszID);  //

void xvm_GBS_SetSysParaValue(LPVOID pXvm, const char* pszID, double dValue);  //

// ��ȡ���Բ�������
// pszID�����ݵ�ID
void xvm_GBS_GetTestParaValue(LPVOID pXvm, const char* pszID);  //
void xvm_GBS_GetTestParaStr(LPVOID pXvm, const char* pszID);  //

// ���ò��Բ�������
// pszID�����ݵ�ID
void xvm_GBS_SetTestParaValue(LPVOID pXvm, const char* pszID, double dValue);  //
void xvm_GBS_SetTestParaStr(LPVOID pXvm, const char* pszID, const char *pszValue);  //

//����������������Ŀ��Show����
//pszItemPathΪItem��·��
void xvm_GBS_SetItemShow(LPVOID pXvm, const char* pszItemPath, long nShow);

// ��ȡ������������Ŀ��Show����
// pszItemPathΪItem��·��
void xvm_GBS_GetItemShow(LPVOID pXvm, const char* pszItemPath);

// ����������������Ŀ��Enable����
// pszItemPathΪItem��·��
void xvm_GBS_SetItemEnable(LPVOID pXvm, const char* pszItemPath, long nEnable);

// ��ȡ������������Ŀ��Enable����
// pszItemPathΪItem��·��
void xvm_GBS_GetItemEnable(LPVOID pXvm, const char* pszItemPath);


//Seelct
void xvm_GBS_SetItemSelect(LPVOID pXvm, const char* pszItemPath, long nSelect);  //
void xvm_GBS_GetItemSelect(LPVOID pXvm, const char* pszItemPath);  //

// ����������������Ŀ��Name����
// pszItemPathΪItem��·��
void xvm_GBS_SetItemName(LPVOID pXvm, const char* pszItemPath, const char* pszName);  //

// ��ȡ������������Ŀ��Name����
// pszItemPathΪItem��·��
void xvm_GBS_GetItemName(LPVOID pXvm, const char* pszItemPath);  //

// ����������������Ŀ�Ľ���ж�
// pszItemPathΪItem��·��
void xvm_GBS_SetItemResultJudge(LPVOID pXvm, const char* pszItemPath, long nResult);  //

void xvm_GBS_GetItemResultJudge(LPVOID pXvm, const char* pszItemPath);  //


// ����������������Ŀ�����ݵ�ֵ
// pszItemPathΪItem��·��
void xvm_GBS_SetItemParaValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dValue);  //
void xvm_GBS_SetItemParaValueStr(LPVOID pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue);  //

void xvm_GBS_GetItemParaValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID);  //
void xvm_GBS_GetItemParaString(LPVOID pXvm, const char* pszItemPath, const char* pszValID);  //
void xvm_GBS_GetItemTestTime(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_GetItemTestBeginTime(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_GetItemTestEndTime(LPVOID pXvm, const char* pszItemPath);  //

//ͨѶ����Ĳ����ű�����  2019-3-19
void xvm_GBS_ClearCommCmdParas(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_AddCommCmdParaValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dValue);  //
void xvm_GBS_AddCommCmdParaValue_Long(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nValue);  //
void xvm_GBS_AddCommCmdParaValue_String(LPVOID pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue);  //

//////////////////////////////////////////////////////////////////////////
//���汨�����ݴ���,����ǰ��Ŀ�ı�������
//////////////////////////////////////////////////////////////////////////
//��װ�á����ݿ�ģʽ�£���ʱ��¼��ͨ�����RptDataMap��֤���ݲ������
void xvm_GBS_AddRptMapData(LPVOID pXvm, const char* pszValID);  //

//���ñ�������
void xvm_GBS_SetItemReportValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dValue);  //
void xvm_GBS_SetItemReportValueString(LPVOID pXvm, const char* pszItemPath, const char* pszValID, const char* pszValString);  //

//��ȡ�������ݣ����ظ�����
void xvm_GBS_GetItemReportValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID);  //
//��ȡ�������ݣ���������
void xvm_GBS_GetItemReportValueLong(LPVOID pXvm, const char* pszItemPath, const char* pszValID);  //
//��ȡ�������ݣ�����string
void xvm_GBS_GetItemReportValueString(LPVOID pXvm, const char* pszItemPath, const char* pszValID);  //

void xvm_GBS_GetItemReportValueEx(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nIndex);  //
void xvm_GBS_GetItemReportValueLongEx(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nIndex);  //
void xvm_GBS_GetItemReportValueStringEx(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nIndex);  //
void xvm_GBS_GetItemReportCount(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_ClearReports(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_CalRptValMax(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dDefVal);  //
void xvm_GBS_CalRptValMin(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dDefVal);  //
void xvm_GBS_CalRptValAvg(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dDefVal);  //

//��ȡ���������ı������ݵĸ���������������ID������ֵ
void xvm_GBS_LGetItemReportDataCount(LPVOID pXvm, const char* pszItemPath, const char *pszDataID, long nDataValue);  //

//////////////////////////////////////////////////////////////////////////
//��չ��������
//////////////////////////////////////////////////////////////////////////
//��ȡ��չ�������ݵ�CReport->m_pRptDataEx
//nIndex���������������
//pszValID�����ݵ�ֵID
void xvm_GBS_GetItemReportExValue(LPVOID pXvm, long nIndex, const char* pszValID);  //
void xvm_GBS_GetItemReportExValue_D(LPVOID pXvm, const char* pszDataID, const char* pszValID);  //
void   xvm_GBS_GetItemReportExValue_L(LPVOID pXvm, const char* pszDataID, const char* pszValID);  //
void  xvm_GBS_GetItemReportExValue_S(LPVOID pXvm, const char* pszDataID, const char* pszValID);  //
void xvm_GBS_GetFileInReportEx(LPVOID pXvm, const char *pszFilePostfix, long nFileIndex);  //
void xvm_GBS_GetFileNumInReportEx(LPVOID pXvm, const char *pszFilePostfix);  //

//��ñ����������ݸ���
void xvm_GBS_GetItemReportExCount(LPVOID pXvm);

//����ID�����Ŀ�ı�������ݸ���
void xvm_GBS_GetItemReportExDataCountByID(LPVOID pXvm, const char* pszDataAttrID);  //

//����ID�Լ�Ҫ��ȡ��ID�ĵڼ������ݷ������ڱ����ж�Ӧ��Indexֵ��nIndex��0��ʼ 
void xvm_GBS_GetItemReportDataIndexByIDIndex(LPVOID pXvm, const char* pszDataAttrID, long nIndex);  //

void xvm_GBS_CalTimeGapStr(LPVOID pXvm, const char* pszTime1, const char* pszTime2);  //
void xvm_GBS_CalTimeGapStr_us(LPVOID pXvm, const char* pszTime1, const char* pszTime2);  //
void xvm_GBS_CalItemReportTimeGap(LPVOID pXvm, long nItem1Index, long nItem2Index, const char* pszValID);  //
void xvm_GBS_CalItemReportTimeGapEx(LPVOID pXvm, long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2);  //
void xvm_GBS_CalItemReportTimeGapEx2(LPVOID pXvm, long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2);  //

//�������
void xvm_GBS_FilterInit(LPVOID pXvm);
void xvm_GBS_FilterReportExEqualValueL(LPVOID pXvm, const char* pszDataAttrID, long nAttrValue);  //
void xvm_GBS_FilterReportExEqualValueStr(LPVOID pXvm, const char* pszDataAttrID, const char* pszValue);  //
void xvm_GBS_FilterReportExHasValueStr(LPVOID pXvm, const char* pszDataAttrID, const char* pszValue);  //
void xvm_GBS_FilterReportExHasNoValueStr(LPVOID pXvm, const char* pszDataAttrID, const char* pszValue);  //
void xvm_GBS_FilterCombineReportEx(LPVOID pXvm, const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator);  //

void xvm_GBS_FilterRptExQuery(LPVOID pXvm, const char* pszQuery);  //
void xvm_GBS_FilterRptExGetCount(LPVOID pXvm);
void xvm_GBS_FilterRptExGetLong(LPVOID pXvm, long nIndex, const char* pszDataAttrID);  //
void xvm_GBS_FilterRptExGetString(LPVOID pXvm, long nIndex, const char* pszDataAttrID);  //
void xvm_GBS_FilterRptExGetDouble(LPVOID pXvm, long nIndex, const char* pszDataAttrID);  //

void xvm_GBS_FilterRptExGetValCount(LPVOID pXvm, long nDataIndex);  //
void xvm_GBS_FilterRptExGetValLong(LPVOID pXvm, long nDataIndex, const char* pszValIndex);  //
void xvm_GBS_FilterRptExGetValString(LPVOID pXvm, long nDataIndex, const char* pszValIndex);  //
void xvm_GBS_FilterRptExGetValDouble(LPVOID pXvm, long nDataIndex, const char* pszValIndex);  //
void xvm_GBS_FilterRptExCalValError(LPVOID pXvm, long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_FilterRptExCalValErrorEx(LPVOID pXvm, const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr);  //

void xvm_Gbs_FilterRptExQueryUseErr(LPVOID pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);  //
void xvm_Gbs_FilterRptExQueryUseErrEx(LPVOID pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);  //
void xvm_Gbs_FilterRptExQueryUseAvg(LPVOID pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);  //
void xvm_Gbs_FilterRptExQueryUseAvgEx(LPVOID pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);  //
void xvm_Gbs_FilterRptExQueryClearNotUse(LPVOID pXvm);

//########################################################################
//���������������������������ı�������
//########################################################################
//��չ��������ΪCDvmDataset��������ΪCDvmData����
//CTag�����ʾһ�����ݵ�ֵ
//��ͨ��������ΪCValues*��������ֵΪCValue����
//���ԣ�����ͨ�������ݵĴ������չ�������ݵĴ���ʽ��һ��

//ѡ��ĳ����Ŀ
void xvm_GBS_SSelectItem(LPVOID pXvm, const char *pszItemPath);  //

//��ͨ���洦����******************************************************

//��õ�ǰѡ�����Ŀ�ı���ĸ���
void xvm_GBS_SGetItemReportCount(LPVOID pXvm);

//ѡ����Ŀ�ı������
void xvm_GBS_SSelectItemReport(LPVOID pXvm, long nReportIndex);  //

//�����Ŀ��ָ���ı�������ݣ�������
void xvm_GBS_SGetItemReportValue(LPVOID pXvm, const char* pszValID);  //

//�����Ŀ��ָ���ı�������ݣ�����
void xvm_GBS_SGetItemReportValueLong(LPVOID pXvm, const char* pszValID);  //

//�����Ŀ��ָ���ı�������ݣ��ַ���
void xvm_GBS_SGetItemReportValueString(LPVOID pXvm, const char* pszValID);  //

//�����Ŀ��ָ���ı�������ݸ���
void xvm_GBS_SGetItemReportValueCount(LPVOID pXvm);   

//��ȡ����ĵ�nDataIndex���ݵ�ֵ
void xvm_GBS_SGetItemReportValue2(LPVOID pXvm, long nDataIndex); 
void xvm_GBS_SGetItemReportValueLong2(LPVOID pXvm, long nDataIndex);  //
void xvm_GBS_SGetItemReportValueString2(LPVOID pXvm, long nDataIndex);  //

//��չ���洦����******************************************************

//�����Ŀ��ָ���ı�������ݸ���
void xvm_GBS_SGetItemReportExDataCount(LPVOID pXvm);

//�����Ŀ��ָ���ı�������ݣ�������
void xvm_GBS_SGetItemReportExDataValue(LPVOID pXvm, long nDataIndex, const char* pszValID);  //

//�����Ŀ��ָ���ı�������ݣ�����
void xvm_GBS_SGetItemReportExDataValueLong(LPVOID pXvm, long nDataIndex, const char* pszValID);  //

//�����Ŀ��ָ���ı�������ݣ�����
void xvm_GBS_SGetItemReportExDataValueString(LPVOID pXvm, long nDataIndex, const char* pszValID);  //
// 
// //�����Ŀ��ָ���ı�������ݣ�������
// double xvm_GBS_SFindItemReportExDataValue(LPVOID pXvm, const char* pszValID
// 
// //�����Ŀ��ָ���ı�������ݣ�����
// long xvm_GBS_SFindItemReportExDataValueLong(LPVOID pXvm, const char* pszValID
// 
// //�����Ŀ��ָ���ı�������ݣ�����
// const char* xvm_GBS_SFindItemReportExDataValueString(LPVOID pXvm, const char* pszValID

//���ݼ��жϺ�������
//�����Ŀ��ָ���ı�������ݸ���
void xvm_GBS_RptExDsGetCount(LPVOID pXvm, const char* pszPath);  //

//�����Ŀ��ָ���ı�������ݣ�������
void xvm_GBS_RptExDsGetValueD(LPVOID pXvm, const char* pszPath, long nIndex);  //

//�����Ŀ��ָ���ı�������ݣ�����
void xvm_GBS_RptExDsGetValueL(LPVOID pXvm, const char* pszPath, long nIndex);  //

//�����Ŀ��ָ���ı�������ݣ�����
void xvm_GBS_RptExDsGetValueStr(LPVOID pXvm, const char* pszPath, long nIndex);  //

//������֤
void xvm_GBS_RptExDsValidClear(LPVOID pXvm);
void xvm_GBS_RptExDsValidAddElement(LPVOID pXvm, const char* pszText, long nOption, long nUnbound);  //
void xvm_GBS_RptExDsValidAddElementChoice(LPVOID pXvm, const char* pszText, long nOption, long nUnbound);  //
void xvm_GBS_RptExDsValid(LPVOID pXvm, long nValidateHead);  //

void xvm_GBS_RecordCmd(LPVOID pXvm, const char *pszCmdID, const char *pszCmdPara);  //
void xvm_GBS_AdjustWord(LPVOID pXvm, long nPopDlg);  //

void xvm_GBS_CalSoeTime(LPVOID pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2);  //
void xvm_GBS_CalSoeTimeEx(LPVOID pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2);  //
void xvm_GBS_SetSoeTripDesc(LPVOID pXvm, const char *pszRptID, const char *pszSoeID);  //
void xvm_GBS_CalSoeError(LPVOID pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr);  //
void xvm_GBS_CalSoeError2(LPVOID pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr);  //


//Record
void xvm_GBS_RcdSetProgID(LPVOID pXvm, const char* pszRcdProgID);  //
void xvm_GBS_RcdExit(LPVOID pXvm);
void xvm_GBS_RcdConfig(LPVOID pXvm, const char* pszPara);  //
void xvm_GBS_RcdSelect(LPVOID pXvm, const char* pszPara);  //
void xvm_GBS_RcdValidate(LPVOID pXvm, const char* pszRsltID);  //
void xvm_GBS_RcdCmpClear(LPVOID pXvm);
void xvm_GBS_RcdCmpInit(LPVOID pXvm, const char* pszRcdFilePathRoot, long nCreateTestTimesDir);  //
void xvm_GBS_RcdCmp(LPVOID pXvm, const char* pszStdFile, const char* pszTestFile);  //
void xvm_GBS_RcdCopyFile(LPVOID pXvm, const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir);  //
void xvm_GBS_RcdAnalyse(LPVOID pXvm, const char* pszRcdFile);  //
void xvm_GBS_RcdSetPath(LPVOID pXvm, long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir);  //

//�ظ��������
void xvm_GBS_GetRepeatTimes(LPVOID pXvm, const char* pszItemPath);  //
void xvm_GBS_GetRepeatSuccTimes(LPVOID pXvm, const char* pszItemPath);  //

//
void xvm_GBS_SetCmdZoneIndex(LPVOID pXvm, long nZoneIndex);  //

//��������ֵ����ʼֵ����ֵֹ
void xvm_Gbs_ValidBeginEndValRange(LPVOID pXvm, const char *pBeginValID, const char *pEndValID, const char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg);  //

//ʱ���������
void xvm_Gbs_SetTmTriggerSecond(LPVOID pXvm, long nSecond, long nOptr);  //
void xvm_Gbs_SetTmTriggerCountMinute(LPVOID pXvm, long nMinute);  //
void xvm_Gbs_EnterTmTrigger(LPVOID pXvm);
void xvm_Gbs_StartTimerTigger(LPVOID pXvm);
void xvm_Gbs_StopTimerTrigger(LPVOID pXvm);

//������Լ
void xvm_Gbs_ValueRevised(LPVOID pXvm, double dValue, long nDots);  //

//////////////////////////////////////////////////////////////////////////
//��־����
void xvm_Gbs_log_query_clear(LPVOID pXvm);
void xvm_Gbs_log_query_time(LPVOID pXvm, const char *pszBeginTine, const char *pszEndTime);  //
void xvm_Gbs_log_query_entryid(LPVOID pXvm, const char *pszEntryID);  //
void xvm_Gbs_log_query_logctrl(LPVOID pXvm, const char *pszLogCtrl);  //
void xvm_Gbs_log_query_dataset(LPVOID pXvm, const char *pszDataset);  //

void xvm_Gbs_log_query_data_clear(LPVOID pXvm);
void xvm_Gbs_log_query_data(LPVOID pXvm, const char *pszDataID);  //
void xvm_Gbs_log_query_data_get_count(LPVOID pXvm);
void xvm_Gbs_log_query_data_add_to_rpt(LPVOID pXvm);

void xvm_Gbs_log_query(LPVOID pXvm, const char *pszScript);  //

void xvm_Gbs_log_get_count(LPVOID pXvm);
void xvm_Gbs_log_get_attr(LPVOID pXvm, long nLogIndex, const char *pszAttr);  //
void xvm_Gbs_log_get_data_count(LPVOID pXvm, long nLogIndex);  //
void xvm_Gbs_log_get_data_attr(LPVOID pXvm, long nLogIndex, long nDataIndex, const char *pszAttr);  //
void xvm_Gbs_log_get_data_attr2(LPVOID pXvm, long nLogIndex, const char *pszDataID, const char *pszAttr);  //

//////////////////////////////////////////////////////////////////////////
//�ַ�������
void xvm_GBS_InitStrTok(LPVOID pXvm, const char *pszString, const char *pControl);  //
void xvm_GBS_StrTokCount(LPVOID pXvm);
void xvm_GBS_StrTokIndex(LPVOID pXvm, long nIndex);  //
void xvm_GBS_StrTokNext(LPVOID pXvm);

//װ�õ�ȫ�ֲ���
void xvm_GBS_SetGlobal_Str(LPVOID pXvm, const char *pszID, const char *pszValue);  //
void xvm_GBS_SetGlobal_Long(LPVOID pXvm, const char *pszID, long nValue);  //
void xvm_GBS_SetGlobal_Float(LPVOID pXvm, const char *pszID, float fValue);  //

void xvm_GBS_GetGlobal_Str(LPVOID pXvm, const char *pszID);  //
void xvm_GBS_GetGlobal_Long(LPVOID pXvm, const char *pszID);  //
void xvm_GBS_GetGlobal_Float(LPVOID pXvm, const char *pszID);  //
void xvm_GBS_GetGlobal_Long2(LPVOID pXvm, const CString &strID);  //

void xvm_GBS_Set_TestError(LPVOID pXvm, const char *pszTestError);  //

void xvm_GBS_BinRslt(LPVOID pXvm, const char *pszParaID, const char *pszRsltID);  //
void xvm_GBS_BinStateRslt(LPVOID pXvm, const char *pszParaID, const char *pszRsltID);  //
void xvm_GBS_BinChngCntRslt(LPVOID pXvm, const char *pszBinChngData, const char *pszRsltID);  //
/*long xvm_GBS_BinRsltEx(LPVOID pXvm);*///const char *pszParaDatas, const char *pszRsltDatas

//2019-1-6:�������ݶ����Ƿ�ϸ�Ĺ���   lijq
void xvm_GBS_Set_AddDataErrorValueToRpt(LPVOID pXvm, long nValue);  //
void xvm_GBS_AddDataErrorToRpt(LPVOID pXvm, const char* pszDataID, long nValue);  //

//2019-6-5  ���Լ�¼�ļ����
void xvm_GBS_GetTemplateFile(LPVOID pXvm, long nWithPath);  //
void xvm_GBS_GetGbrptFile(LPVOID pXvm, long nWithPath);  //
void xvm_GBS_SetGbrptFileName(LPVOID pXvm, const char *pszFileName);  //

//2019-7-19     ����װ�õı�ţ���������ʱ��
void xvm_GBS_OffsetTestDataByGbrptIndex(LPVOID pXvm, const char *pszDestDataID);  //

//2020-05-22   ���ܰ汾�ȶԹ���  shaolei��
void xvm_GBS_VersionInfoCompare (LPVOID pXvm, const char* pszPath, const char* pszFilePath);  //

//GbScript_System/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ڵ��Լ�����Ϣ����ʾ��Ϣ
// pszMsg����Ϣ�ı�/��ϢID
void xvm_GBS_ShowMessage(LPVOID pXvm, const  char* pszMsg);  //

// ���������ļ�
// pszFile�������ļ�
// nTimes�����Ŵ���		 0<=��ʾѭ������ 	>0��ʾʵ�ʲ��ŵĴ���
void xvm_GBS_PlayMusicFile(LPVOID pXvm, const  char* pszFileName, long nTimes);  //

void xvm_GBS_GetTime(LPVOID pXvm);

void xvm_GBS_IEC(LPVOID pXvm, double dValue, double dTp, double dK, double dAlpha);  //
void xvm_GBS_IEEE(LPVOID pXvm, double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2);  //
void xvm_GBS_IAC(LPVOID pXvm, double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta);  //
void xvm_GBS_I2T(LPVOID pXvm, double dValue, double dTp, double dA);  //

void xvm_GBS_CmpDouble(LPVOID pXvm, const char *pszVal1, const char *pszVal2, const char *pszPrecision);  //
void xvm_GBS_CmpDoubleVal(LPVOID pXvm, double dVal1, double dVal2, double dPrecision);  //
void xvm_GBS_CalRelError(LPVOID pXvm, double dAbsErr, double dRefVal);  //

//�ⲿ����ӿڲ���(DLL����)
//strPara��ʽ����Variable1=value1; Variable2=value2;��
//dllReadDatas���ؽ���ĸ�ʽ��ͬ
void xvm_GBS_dllLoad(LPVOID pXvm, const char *pszDllFilePath, const char *pszDllID);  //
void xvm_GBS_dllCall(LPVOID pXvm, const char *pszDllID, const char *pszPara);  //
void xvm_GBS_dllReadDatas(LPVOID pXvm, const char *pszDllID, const char *pszPara);  //
void xvm_GBS_dllUnload(LPVOID pXvm, const char *pszDllID);  //

//EXE����
void xvm_GBS_RunExe(LPVOID pXvm, const char *pszExeFile, const char *pszPara);  //
void xvm_GBS_ExitExe(LPVOID pXvm, const char *pszExeFile);  //

void xvm_GBS_AddLocalTime(LPVOID pXvm, long nHour, long nMinute, long nSecond);  //
void xvm_GBS_SubLocalTime(LPVOID pXvm, long nHour, long nMinute, long nSecond);  //
void xvm_GBS_RandLong(LPVOID pXvm, long nMin, long nMax);  //
void xvm_GBS_RandFloat(LPVOID pXvm, float fMin, float fMax);  //
void xvm_GBS_RandDouble(LPVOID pXvm, double fMin, double fMax);  //
void xvm_GBS_RandSeed(LPVOID pXvm);

//�ļ�
void xvm_GBS_GetFileNameFromPath(LPVOID pXvm, const char *pszPath);  //
void xvm_GBS_ParseFilePostfix(LPVOID pXvm, const char* pszFileName);  //
void xvm_GBS_ParseFileName(LPVOID pXvm, const char *pszFileName);  //

void xvm_GBS_SubStrToLong(LPVOID pXvm, const char *pszString, long nBegin, long nLen);  //
void xvm_GBS_SubStrToStr(LPVOID pXvm, const char *pszString, long nBegin, long nLen);  //
void xvm_GBS_GetSecondsFromMidnight(LPVOID pXvm);

// void xvm_GBS_LogTime_PcTime(PPCTIME pTm);
// void xvm_GBS_LogTime_GpsTime(PGPSTIME pTm);

//GbScript_Engine////////////////////////////////////////////////////////////////////////////////////////////////
// ��Լ֡¼������
void xvm_GBS_RecordPackage(LPVOID pXvm, const  char* pszPkgID);  //
void xvm_GBS_UnRecordPackage(LPVOID pXvm, const  char* pszPkgID);  //
void xvm_GBS_GetPackagePcTime(LPVOID pXvm, const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail);  //

// ��ȡ��׼Դװ��GPSʱ����PCʱ���֮���Ӧ��ϵ
void xvm_GBS_GetGpsPcTimeMap(LPVOID pXvm, const char *pszGpsTime, const char *pszPcTime);  //

//��ȡ�����ʼʱ�̵ı�׼Դװ��GPSʱ��
void xvm_GBS_GetOutGpsTime(LPVOID pXvm, const char *pszGpsTimeID);  //

//����ʱ����
void xvm_GBS_CalGpsPcTimeGap(LPVOID pXvm, const char *pszTimeID1, const char *pszTimerID2);  //
void xvm_GBS_CalTimeGap(LPVOID pXvm, const char *pszTime1, const char *pszTimer2);  //
void xvm_GBS_CalTimeGapCurr(LPVOID pXvm, const char *pszTime);  //


//����һ��GPS��ʱ�����
void xvm_GBS_CreateGpsDateTime(LPVOID pXvm, const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs);  //
void xvm_GBS_CreateGpsTime(LPVOID pXvm, const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs);  //

//��ȡ��׼Դ�Ľ������
void xvm_GBS_ReadMacroTestResult(LPVOID pXvm);

//�������ص�����������Ŀ�Ĳ���
void xvm_GBS_DownloadMacroTestPara(LPVOID pXvm);

//ͨѶ��Լ����ӿں���
void xvm_GBS_PpGetDeviceAttr(LPVOID pXvm, const char *pszAttrID);  //
void xvm_GBS_PpGetDeviceAttrL(LPVOID pXvm, const char *pszAttrID);  //
void xvm_GBS_PpGetDeviceAttrStr(LPVOID pXvm, const char *pszAttrID);  //
void xvm_GBS_PpSetDeviceAttrL(LPVOID pXvm, const char *pszAttrID, long nValue);  //
void xvm_GBS_PpSetDeviceAttrStr(LPVOID pXvm, const char *pszAttrID, const char *pszValue);  //

void xvm_GBS_PpRptGetDevieNodeDatas(LPVOID pXvm, const char *pszNodePath);  //
void xvm_GBS_PpRptGetDeviceAttrs(LPVOID pXvm);  //
void xvm_GBS_PpGetDevieNodeDataAttr(LPVOID pXvm, const char *strDataPath, const char *strAttrID);  //
// long xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm, const char *strDataPath, const char *strAttrID, const char *strValue
void xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm, const char *strDataPath, const char *strAttrID, double dValue);  //
void xvm_GBS_PpDeleteAllNodeData(LPVOID pXvm, const char *pszNodePath);  //

void xvm_GBS_PpCreateDevice(LPVOID pXvm, const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID);  //
void xvm_GBS_PpReleaseDevice(LPVOID pXvm, const char *pszDeviceID);  //
void xvm_GBS_PpReleaseAllDevice(LPVOID pXvm);
// long xvm_GBS_PpRun(LPVOID pXvm, const char *pszDeviceID, const char *pszProcedureID, const char *pszPara
void xvm_GBS_GetTestIndex(LPVOID pXvm);

void xvm_GBS_IsProtocol(LPVOID pXvm, const char *pszProtocol);  //

#endif