#pragma once

#include "GbScript_GlobalDefine.h"

/*

*/
class CGuideBook;
CGuideBook* GBS_GetGuideBook();

// ��Լ֡¼������
void GBS_RecordPackage(const  char* pszPkgID);
void GBS_UnRecordPackage(const  char* pszPkgID);
void GBS_GetPackagePcTime(const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail);

// ��ȡ��׼Դװ��GPSʱ����PCʱ���֮���Ӧ��ϵ
void GBS_GetGpsPcTimeMap(const char *pszGpsTime, const char *pszPcTime);

//��ȡ�����ʼʱ�̵ı�׼Դװ��GPSʱ��
void GBS_GetOutGpsTime(const char *pszGpsTimeID);

//����ʱ����
long GBS_CalGpsPcTimeGap(const char *pszTimeID1, const char *pszTimerID2);
long GBS_CalTimeGap(const char *pszTime1, const char *pszTimer2);
long GBS_CalTimeGapCurr(const char *pszTime);


//����һ��GPS��ʱ�����
long GBS_CreateGpsDateTime(const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs);
long GBS_CreateGpsTime(const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs);

//��ȡ��׼Դ�Ľ������
long GBS_ReadMacroTestResult();

//�������ص�����������Ŀ�Ĳ���
void GBS_DownloadMacroTestPara();

//ͨѶ��Լ����ӿں���
double GBS_PpGetDeviceAttr(const char *pszAttrID);
long GBS_PpGetDeviceAttrL(const char *pszAttrID);
const char* GBS_PpGetDeviceAttrStr(const char *pszAttrID);
void GBS_PpSetDeviceAttrL(const char *pszAttrID, long nValue);
void GBS_PpSetDeviceAttrStr(const char *pszAttrID, const char *pszValue);

long GBS_PpRptGetDevieNodeDatas(const char *pszNodePath);
long GBS_PpRptGetDeviceAttrs(void);
double GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID);
// long GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, const char *strValue);
long GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, double dValue);
long GBS_PpDeleteAllNodeData(const char *pszNodePath);

long GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID);
long GBS_PpReleaseDevice(const char *pszDeviceID);
long GBS_PpReleaseAllDevice();
// long GBS_PpRun(const char *pszDeviceID, const char *pszProcedureID, const char *pszPara);
long GBS_GetTestIndex();

long GBS_IsProtocol(const char *pszProtocol);
