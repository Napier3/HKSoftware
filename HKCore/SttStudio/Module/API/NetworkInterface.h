//NetworkInterface.h
#ifndef _NetworkInterface_H__
#define _NetworkInterface_H__

#include "../../../Module/OSInterface/OSInterface.h"
//#include "../../../Module/DataMngr/DataGroup.h"
#include "../SttGlobalDef.h"

#ifdef _PSX_OS_CENTOS_
#define  NET_DEVICENAME   "lo"
#else
#define  NET_DEVICENAME   "eth0"
#endif

//void stt_net_add_ip_para(CDataGroup *pDataGroup, const CString &strID, long nIndex, const CString &strIP, const CString &strMask);
long stt_net_set_deviceip(const CString &strIP, const CString &strMask);
long stt_net_set_subips(const CStringArray &astrIP, const CStringArray &astrMask,long nBeginIndex=0);
void stt_net_get_deviceip(CString &strIP, CString &strMask);
void stt_file_get_deviceip(CString &strIP, CString &strMask);//避免因主IP辅IP排序颠倒,导致stt_net_get_deviceip意外获得辅IP

long stt_net_get_ip(CStringArray &astrIP, CStringArray &astrMask);
void stt_net_get_ip(CString *IP);
long stt_net_set_ip(CStringArray &astrIP, CStringArray &astrMask, long nIPBeginIndex=2);
long stt_net_set_gateway(const CString &strGateWay,long nMetric);//20220526 zhoulei 增加上网优先级设置，数值越小优先级越高
long stt_net_set_gateway(const CStringArray &astrGateWay,long* nMetric);

void stt_net_dhcp();
//long stt_net_get_ip(CDataGroup *pDataGroup);
//long stt_net_set_ip(CDataGroup *pDataGroup);

extern CString g_str_Net_DeviceName;

#ifdef _PSX_IDE_QT_
#include <QStringList>
long stt_net_get_ip(QStringList &astrIP, QStringList &astrMask);
long stt_net_set_ip(QStringList &astrIP, QStringList &astrMask, long nIPBeginIndex=2);
#endif

#endif//_FILE_API_H__
