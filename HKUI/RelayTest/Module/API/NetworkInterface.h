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

//保存主IP到文件
long stt_file_save_deviceip(const CString &strIP, const CString &strMask);
//保存辅IP到文件
long stt_file_save_subips(const CStringArray &astrIP, const CStringArray &astrMask,
						 const CStringArray &astrGW, long *pMetric, long nBeginIndex=0);
//从文件获得主IP
void stt_file_get_deviceip(CString &strIP, CString &strMask);//避免因主IP辅IP排序颠倒,导致stt_net_get_deviceip意外获得辅IP
//从文件获得辅IP
void stt_file_get_subips(CStringArray &strIP, CStringArray &strMask, CStringArray &astrGateWay,long* nMetric);

//从QT_API获得主IP
void stt_net_get_deviceip(CString &strIP, CString &strMask);
//从QT_API获得主IP和辅IP
long stt_net_get_ip(CStringArray &astrIP, CStringArray &astrMask);
//设置辅IP生效
long stt_net_set_subips(CStringArray &astrIP, CStringArray &astrMask, long nIPBeginIndex=2);
//设置网关生效
long stt_net_set_gateway(const CString &strGateWay,long nMetric);//20220526 zhoulei 增加上网优先级设置，数值越小优先级越高
long stt_net_set_gateway(const CStringArray &astrGateWay,long* nMetric);
//从路由器动态获取IP
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
