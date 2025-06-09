#pragma once

#include "GbScript_GlobalDefine.h"
#include "../../../../Module/XVM/TVMSingle.h"

/*

*/
class CGuideBook;
CGuideBook* GBS_GetGuideBook(CTScriptSingleVM *pXvm);

// ��Լ֡¼������
void GBS_RecordPackage(CTScriptSingleVM *pXvm, const  char* pszPkgID);
void GBS_UnRecordPackage(CTScriptSingleVM *pXvm, const  char* pszPkgID);
void GBS_GetPackagePcTime(CTScriptSingleVM *pXvm, const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail);

// ��ȡ��׼Դװ��GPSʱ����PCʱ���֮���Ӧ��ϵ
void GBS_GetGpsPcTimeMap(CTScriptSingleVM *pXvm, const char *pszGpsTime, const char *pszPcTime);

//��ȡ�����ʼʱ�̵ı�׼Դװ��GPSʱ��
void GBS_GetOutGpsTime(CTScriptSingleVM *pXvm, const char *pszGpsTimeID);

//����ʱ����
long GBS_CalGpsPcTimeGap(CTScriptSingleVM *pXvm, const char *pszTimeID1, const char *pszTimerID2);
long GBS_CalTimeGap(CTScriptSingleVM *pXvm, const char *pszTime1, const char *pszTimer2);
long GBS_CalTimeGapCurr(CTScriptSingleVM *pXvm, const char *pszTime);


//����һ��GPS��ʱ�����
long GBS_CreateGpsDateTime(CTScriptSingleVM *pXvm, const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs);
long GBS_CreateGpsTime(CTScriptSingleVM *pXvm, const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs);

//��ȡ��׼Դ�Ľ������
long GBS_ReadMacroTestResult(CTScriptSingleVM *pXvm);

//�������ص�����������Ŀ�Ĳ���
void GBS_DownloadMacroTestPara(CTScriptSingleVM *pXvm);

//ͨѶ��Լ����ӿں���
double GBS_PpGetDeviceAttr(CTScriptSingleVM *pXvm, const char *pszAttrID);
long GBS_PpGetDeviceAttrL(CTScriptSingleVM *pXvm, const char *pszAttrID);
const char* GBS_PpGetDeviceAttrStr(CTScriptSingleVM *pXvm, const char *pszAttrID);
void GBS_PpSetDeviceAttrL(CTScriptSingleVM *pXvm, const char *pszAttrID, long nValue);
void GBS_PpSetDeviceAttrStr(CTScriptSingleVM *pXvm, const char *pszAttrID, const char *pszValue);

long GBS_PpRptGetDevieNodeDatas(CTScriptSingleVM *pXvm, const char *pszNodePath);
long GBS_PpRptGetDeviceAttrs(CTScriptSingleVM *pXvm);//void
double GBS_PpGetDevieNodeDataAttr(CTScriptSingleVM *pXvm, const char *strDataPath, const char *strAttrID);
// long GBS_PpSetDevieNodeDataAttr(CTScriptSingleVM *pXvm, const char *strDataPath, const char *strAttrID, const char *strValue);
long GBS_PpSetDevieNodeDataAttr(CTScriptSingleVM *pXvm, const char *strDataPath, const char *strAttrID, double dValue);
long GBS_PpDeleteAllNodeData(CTScriptSingleVM *pXvm, const char *pszNodePath);

long GBS_PpCreateDevice(CTScriptSingleVM *pXvm, const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID);
long GBS_PpReleaseDevice(CTScriptSingleVM *pXvm, const char *pszDeviceID);
long GBS_PpReleaseAllDevice(CTScriptSingleVM *pXvm);
// long GBS_PpRun(CTScriptSingleVM *pXvm, const char *pszDeviceID, const char *pszProcedureID, const char *pszPara);
long GBS_GetTestIndex(CTScriptSingleVM *pXvm);

long GBS_IsProtocol(CTScriptSingleVM *pXvm, const char *pszProtocol);
