//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgGlobal.h

#pragma once


#include "../TcpEdgeGlobalDef.h"

#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DvmDatasetGroup.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CPXPKGDATABASE       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CTCPEDGEPKG       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CTCPEDGEPKGDATA       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETHISDATARESP       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CPKG_GETHISDATARESP_DEVS       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CPKG_GETHISDATARESP_DEV       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CPKG_GETHISDATARESP_DEVSVCS       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CPKG_GETHISDATARESP_DEVSVC       (MngrCLASSID_EXLISTCLASS + 0X00000007)
#define MNGRCLASSID_CPKG_GETHISDATARESP_DEVSVCDLS       (MngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CPKG_GETHISDATARESP_DEVSVCDL       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETHISDATA       (MngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CPKG_GETHISDATA_DEVS       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CPKG_GETHISDATA_DEV       (MngrCLASSID_EXLISTCLASS + 0X0000000C)
#define MNGRCLASSID_CPKG_GETHISDATA_DEVSVCS       (MngrCLASSID_EXLISTCLASS + 0X0000000D)
#define MNGRCLASSID_CPKG_GETHISDATA_DEVSVC       (MngrCLASSID_EXLISTCLASS + 0X0000000E)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARACANCELRESP       (MngrCLASSID_EXLISTCLASS + 0X0000000F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARACANCEL       (MngrCLASSID_EXLISTCLASS + 0X00000010)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARAACTIVATERESP       (MngrCLASSID_EXLISTCLASS + 0X00000011)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARAACTIVATE       (MngrCLASSID_EXLISTCLASS + 0X00000012)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARASETRESP       (MngrCLASSID_EXLISTCLASS + 0X00000013)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARASET       (MngrCLASSID_EXLISTCLASS + 0X00000014)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CTRLCMDRESP       (MngrCLASSID_EXLISTCLASS + 0X00000015)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CTRLCMD       (MngrCLASSID_EXLISTCLASS + 0X00000016)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETMESSAGERESP       (MngrCLASSID_EXLISTCLASS + 0X00000017)
#define MNGRCLASSID_CPKG_GETMESSAGERESP_FILE       (MngrCLASSID_EXLISTCLASS + 0X00000018)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETMESSAGE       (MngrCLASSID_EXLISTCLASS + 0X00000019)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETTOPOFILERESP       (MngrCLASSID_EXLISTCLASS + 0X0000001A)
#define MNGRCLASSID_CPKG_GETTOPFILERESP_FILE       (MngrCLASSID_EXLISTCLASS + 0X0000001B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETTOPOFILE       (MngrCLASSID_EXLISTCLASS + 0X0000001C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARAREADRESP       (MngrCLASSID_EXLISTCLASS + 0X0000001D)
#define MNGRCLASSID_CPKG_PARAREADRESPSVCS       (MngrCLASSID_EXLISTCLASS + 0X0000001E)
#define MNGRCLASSID_CPKG_PARAREADRESPSVC       (MngrCLASSID_EXLISTCLASS + 0X0000001F)
#define MNGRCLASSID_CPKG_PARAREADRESPSVCDLS       (MngrCLASSID_EXLISTCLASS + 0X00000020)
#define MNGRCLASSID_CPKG_PARAREADRESPSVCDL       (MngrCLASSID_EXLISTCLASS + 0X00000021)
#define MNGRCLASSID_CTCPEDGEPKGDATA_PARAREAD       (MngrCLASSID_EXLISTCLASS + 0X00000022)
#define MNGRCLASSID_CPKG_PARAREADSVC       (MngrCLASSID_EXLISTCLASS + 0X00000023)
#define MNGRCLASSID_CPKG_PARAREADSVCDL       (MngrCLASSID_EXLISTCLASS + 0X00000024)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DATAREADRESP       (MngrCLASSID_EXLISTCLASS + 0X00000025)
#define MNGRCLASSID_CPKG_DATAREADRESPDEV       (MngrCLASSID_EXLISTCLASS + 0X00000026)
#define MNGRCLASSID_CPKG_DATAREADRESPDEVSVC       (MngrCLASSID_EXLISTCLASS + 0X00000027)
#define MNGRCLASSID_CPKG_DATAREADRESPDEVSVCDL       (MngrCLASSID_EXLISTCLASS + 0X00000028)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DATAREAD       (MngrCLASSID_EXLISTCLASS + 0X00000029)
#define MNGRCLASSID_CPKG_DATAREADDEV       (MngrCLASSID_EXLISTCLASS + 0X0000002A)
#define MNGRCLASSID_CPKG_DATAREADDEVSVC       (MngrCLASSID_EXLISTCLASS + 0X0000002B)
#define MNGRCLASSID_CPKG_DATAREADDEVSVCDL       (MngrCLASSID_EXLISTCLASS + 0X0000002C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DATASPONTRESP       (MngrCLASSID_EXLISTCLASS + 0X0000002D)
#define MNGRCLASSID_CPKG_DATASPONTRESPDEVS       (MngrCLASSID_EXLISTCLASS + 0X0000002E)
#define MNGRCLASSID_CPKG_DATASPONTRESPDEV       (MngrCLASSID_EXLISTCLASS + 0X0000002F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DATASPONT       (MngrCLASSID_EXLISTCLASS + 0X00000030)
#define MNGRCLASSID_CPKG_DATASPONTDEVS       (MngrCLASSID_EXLISTCLASS + 0X00000031)
#define MNGRCLASSID_CPKG_DATASPONTDEV       (MngrCLASSID_EXLISTCLASS + 0X00000032)
#define MNGRCLASSID_CPKG_DATASPONTDEVSVCS       (MngrCLASSID_EXLISTCLASS + 0X00000033)
#define MNGRCLASSID_CPKG_DATASPONTDEVSVC       (MngrCLASSID_EXLISTCLASS + 0X00000034)
#define MNGRCLASSID_CPKG_DATASPONTDEVSVCDLS       (MngrCLASSID_EXLISTCLASS + 0X00000035)
#define MNGRCLASSID_CPKG_DATASPONTDEVSVCDL       (MngrCLASSID_EXLISTCLASS + 0X00000036)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETDATASUBSRESP       (MngrCLASSID_EXLISTCLASS + 0X00000037)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBS       (MngrCLASSID_EXLISTCLASS + 0X00000038)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUB       (MngrCLASSID_EXLISTCLASS + 0X00000039)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVC       (MngrCLASSID_EXLISTCLASS + 0X0000003A)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVCDEVS       (MngrCLASSID_EXLISTCLASS + 0X0000003B)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVCDEV       (MngrCLASSID_EXLISTCLASS + 0X0000003C)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVCDLS       (MngrCLASSID_EXLISTCLASS + 0X0000003D)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVCDL       (MngrCLASSID_EXLISTCLASS + 0X0000003E)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETDATASUBS       (MngrCLASSID_EXLISTCLASS + 0X0000003F)
#define MNGRCLASSID_CPKG_GETDATASUBS_SUB       (MngrCLASSID_EXLISTCLASS + 0X00000040)
#define MNGRCLASSID_CPKG_GETDATASUBS_SUBSVC       (MngrCLASSID_EXLISTCLASS + 0X00000041)
#define MNGRCLASSID_CPKG_GETDATASUBS_SUBSVCDEVS       (MngrCLASSID_EXLISTCLASS + 0X00000042)
#define MNGRCLASSID_CPKG_GETDATASUBS_SUBSVCDEV       (MngrCLASSID_EXLISTCLASS + 0X00000043)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DATASUBSRESP       (MngrCLASSID_EXLISTCLASS + 0X00000044)
#define MNGRCLASSID_CPKG_DATASUBSRESP_SUBS       (MngrCLASSID_EXLISTCLASS + 0X00000045)
#define MNGRCLASSID_CPKG_DATASUBSRESP_SUB       (MngrCLASSID_EXLISTCLASS + 0X00000046)
#define MNGRCLASSID_CPKG_DATASUBSRESP_SUBSVC       (MngrCLASSID_EXLISTCLASS + 0X00000047)
#define MNGRCLASSID_CPKG_DATASUBSRESP_SUBSVCDEV       (MngrCLASSID_EXLISTCLASS + 0X00000048)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DATASUBS       (MngrCLASSID_EXLISTCLASS + 0X00000049)
#define MNGRCLASSID_CPKG_DATSUBS_SUBS       (MngrCLASSID_EXLISTCLASS + 0X0000004A)
#define MNGRCLASSID_CPKG_DATSUBS_SUB       (MngrCLASSID_EXLISTCLASS + 0X0000004B)
#define MNGRCLASSID_CPKG_DATASUBS_SUBSSVCS       (MngrCLASSID_EXLISTCLASS + 0X0000004C)
#define MNGRCLASSID_CPKG_DATASUBS_SUBSSVC       (MngrCLASSID_EXLISTCLASS + 0X0000004D)
#define MNGRCLASSID_CPKG_DATASUBS_SUBSSVCDEVS       (MngrCLASSID_EXLISTCLASS + 0X0000004E)
#define MNGRCLASSID_CPKG_DATASUBS_SUBSSVCDEV       (MngrCLASSID_EXLISTCLASS + 0X0000004F)
#define MNGRCLASSID_CPKG_DATASUBS_SUBSSVCDLS       (MngrCLASSID_EXLISTCLASS + 0X00000050)
#define MNGRCLASSID_CPKG_DATASUBS_SUBSSVCDL       (MngrCLASSID_EXLISTCLASS + 0X00000051)
#define MNGRCLASSID_CTCPEDGEPKGDATA_MODELDEVREADRESP       (MngrCLASSID_EXLISTCLASS + 0X00000052)
#define MNGRCLASSID_CPKG_MODELDEVREADRESP_MODS       (MngrCLASSID_EXLISTCLASS + 0X00000053)
#define MNGRCLASSID_CPKG_MODELDEVREADRESP_MOD       (MngrCLASSID_EXLISTCLASS + 0X00000054)
#define MNGRCLASSID_CPKG_MODELDEVREADRESP_MODDEVS       (MngrCLASSID_EXLISTCLASS + 0X00000055)
#define MNGRCLASSID_CPKG_MODELDEVREADRESP_MODDEV       (MngrCLASSID_EXLISTCLASS + 0X00000056)
#define MNGRCLASSID_CTCPEDGEPKGDATA_MODELDEVREAD       (MngrCLASSID_EXLISTCLASS + 0X00000057)
#define MNGRCLASSID_CPKG_MODELDEVREAD_MODS       (MngrCLASSID_EXLISTCLASS + 0X00000058)
#define MNGRCLASSID_CPKG_MODELDEVREAD_MOD       (MngrCLASSID_EXLISTCLASS + 0X00000059)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVUPDATERESP       (MngrCLASSID_EXLISTCLASS + 0X0000005A)
#define MNGRCLASSID_CPKG_DEVUPDATERESP_DEVS       (MngrCLASSID_EXLISTCLASS + 0X0000005B)
#define MNGRCLASSID_CPKG_DEVUPDATERESP_DEV       (MngrCLASSID_EXLISTCLASS + 0X0000005C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVUPDATE       (MngrCLASSID_EXLISTCLASS + 0X0000005D)
#define MNGRCLASSID_CPKG_DEVUPDATE_DEVS       (MngrCLASSID_EXLISTCLASS + 0X0000005E)
#define MNGRCLASSID_CPKG_DEVUPDATE_DEV       (MngrCLASSID_EXLISTCLASS + 0X0000005F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVADDRESP       (MngrCLASSID_EXLISTCLASS + 0X00000060)
#define MNGRCLASSID_CPKG_DEVADDRESP_DEVS       (MngrCLASSID_EXLISTCLASS + 0X00000061)
#define MNGRCLASSID_CPKG_DEVADDRESP_DEV       (MngrCLASSID_EXLISTCLASS + 0X00000062)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVADD       (MngrCLASSID_EXLISTCLASS + 0X00000063)
#define MNGRCLASSID_CPKG_DEVADD_DEVS       (MngrCLASSID_EXLISTCLASS + 0X00000064)
#define MNGRCLASSID_CPKG_DEVADD_DEV       (MngrCLASSID_EXLISTCLASS + 0X00000065)
#define MNGRCLASSID_CTCPEDGEPKGDATA_MODELCHANGERESP       (MngrCLASSID_EXLISTCLASS + 0X00000066)
#define MNGRCLASSID_CPKG_MODELCHANGERESP_MODS       (MngrCLASSID_EXLISTCLASS + 0X00000067)
#define MNGRCLASSID_CPKG_MODELCHANGERESP_MOD       (MngrCLASSID_EXLISTCLASS + 0X00000068)
#define MNGRCLASSID_CTCPEDGEPKGDATA_MODELCHANGE       (MngrCLASSID_EXLISTCLASS + 0X00000069)
#define MNGRCLASSID_CPKG_MODELCHANGE_MODS       (MngrCLASSID_EXLISTCLASS + 0X0000006A)
#define MNGRCLASSID_CPKG_MODELCHANGE_MOD       (MngrCLASSID_EXLISTCLASS + 0X0000006B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETMODELRESP       (MngrCLASSID_EXLISTCLASS + 0X0000006C)
#define MNGRCLASSID_CPKG_GETMODELRESP_MODS       (MngrCLASSID_EXLISTCLASS + 0X0000006D)
#define MNGRCLASSID_CPKG_GETMODELRESP_MOD       (MngrCLASSID_EXLISTCLASS + 0X0000006E)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETMODEL       (MngrCLASSID_EXLISTCLASS + 0X0000006F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEGETLOGREQ       (MngrCLASSID_EXLISTCLASS + 0X00000070)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPALARM       (MngrCLASSID_EXLISTCLASS + 0X00000071)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCONFIGRESP       (MngrCLASSID_EXLISTCLASS + 0X00000072)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCONFIGREQ       (MngrCLASSID_EXLISTCLASS + 0X00000073)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCONFIGREQ       (MngrCLASSID_EXLISTCLASS + 0X00000074)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPDISABLERESP       (MngrCLASSID_EXLISTCLASS + 0X00000075)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPDISABLEREQ       (MngrCLASSID_EXLISTCLASS + 0X00000076)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPENABLERESP       (MngrCLASSID_EXLISTCLASS + 0X00000077)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPENABLEREQ       (MngrCLASSID_EXLISTCLASS + 0X00000078)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPREMOVERESP       (MngrCLASSID_EXLISTCLASS + 0X00000079)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPREMOVEREQ       (MngrCLASSID_EXLISTCLASS + 0X0000007A)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSTOPRESP       (MngrCLASSID_EXLISTCLASS + 0X0000007B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSTOPREQ       (MngrCLASSID_EXLISTCLASS + 0X0000007C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSTARTRESP       (MngrCLASSID_EXLISTCLASS + 0X0000007D)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSTARTREQ       (MngrCLASSID_EXLISTCLASS + 0X0000007E)
#define MNGRCLASSID_CTCPEDGEPKGBASE       (MngrCLASSID_EXLISTCLASS + 0X0000007F)
#define MNGRCLASSID_CTCPEDGEPKGSTRING       (MngrCLASSID_EXLISTCLASS + 0X00000080)
#define MNGRCLASSID_CTCPEDGEPKGDEV       (MngrCLASSID_EXLISTCLASS + 0X00000081)
#define MNGRCLASSID_CTCPEDGEPKGCPU       (MngrCLASSID_EXLISTCLASS + 0X00000082)
#define MNGRCLASSID_CTCPEDGEPKGMEM       (MngrCLASSID_EXLISTCLASS + 0X00000083)
#define MNGRCLASSID_CTCPEDGEPKGDISK       (MngrCLASSID_EXLISTCLASS + 0X00000084)
#define MNGRCLASSID_CTCPEDGEPKGTEMPERATURE       (MngrCLASSID_EXLISTCLASS + 0X00000085)
#define MNGRCLASSID_CTCPEDGEPKGOS       (MngrCLASSID_EXLISTCLASS + 0X00000086)
//#define MNGRCLASSID_CTCPEDGEPKGMEMUSED       (MngrCLASSID_EXLISTCLASS + 0X00000087)
#define MNGRCLASSID_CTCPEDGEPKGCFGCPU       (MngrCLASSID_EXLISTCLASS + 0X00000088)
#define MNGRCLASSID_CTCPEDGEPKGCFGMEM       (MngrCLASSID_EXLISTCLASS + 0X00000089)
#define MNGRCLASSID_CTCPEDGEPKGCFGDISK       (MngrCLASSID_EXLISTCLASS + 0X0000008A)
#define MNGRCLASSID_CTCPEDGEPKGFILE       (MngrCLASSID_EXLISTCLASS + 0X0000008B)
#define MNGRCLASSID_CTCPEDGEAUTH_0X01       (MngrCLASSID_EXLISTCLASS + 0X0000008C)
#define MNGRCLASSID_CTCPEDGEAUTH_0X02       (MngrCLASSID_EXLISTCLASS + 0X0000008D)
#define MNGRCLASSID_CTCPEDGEAUTH_0X03       (MngrCLASSID_EXLISTCLASS + 0X0000008E)
#define MNGRCLASSID_CTCPEDGEPKGHEAD       (MngrCLASSID_EXLISTCLASS + 0X0000008F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_HEALTH       (MngrCLASSID_EXLISTCLASS + 0X00000090)
#define MNGRCLASSID_CTCPEDGEPKGDATA_FILEGET       (MngrCLASSID_EXLISTCLASS + 0X00000091)
#define MNGRCLASSID_CTCPEDGEPKGDATA_FILEGETRESP       (MngrCLASSID_EXLISTCLASS + 0X00000092)
#define MNGRCLASSID_CTCPEDGEPKGDATA_FILEDATATRANS       (MngrCLASSID_EXLISTCLASS + 0X00000093)
#define MNGRCLASSID_CTCPEDGEPKGDATA_FILEDATATRANSRESP       (MngrCLASSID_EXLISTCLASS + 0X00000094)
#define MNGRCLASSID_CTCPEDGEPKGDATA_FILESEND       (MngrCLASSID_EXLISTCLASS + 0X00000095)
#define MNGRCLASSID_CTCPEDGEPKGDATA_FILESENDRESP       (MngrCLASSID_EXLISTCLASS + 0X00000096)
#define MNGRCLASSID_CTCPEDGEPKGDATA_TIMESYNCREQ       (MngrCLASSID_EXLISTCLASS + 0X00000097)
#define MNGRCLASSID_CTCPEDGEPKGDATA_TIMESYNCRESP       (MngrCLASSID_EXLISTCLASS + 0X00000098)
#define MNGRCLASSID_CTCPEDGEPKGDATA_TIMEREADREQ       (MngrCLASSID_EXLISTCLASS + 0X00000099)
#define MNGRCLASSID_CTCPEDGEPKGDATA_TIMEREADRESP       (MngrCLASSID_EXLISTCLASS + 0X0000009A)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATEREQ       (MngrCLASSID_EXLISTCLASS + 0X0000009B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATERESP       (MngrCLASSID_EXLISTCLASS + 0X0000009C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATESTATUSREQ       (MngrCLASSID_EXLISTCLASS + 0X0000009D)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATESTATUSRESP       (MngrCLASSID_EXLISTCLASS + 0X0000009E)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATERESULT       (MngrCLASSID_EXLISTCLASS + 0X0000009F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECTRLREQ       (MngrCLASSID_EXLISTCLASS + 0X00000100)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECTRLRESP       (MngrCLASSID_EXLISTCLASS + 0X00000101)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFOREQ       (MngrCLASSID_EXLISTCLASS + 0X00000102)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFORESP       (MngrCLASSID_EXLISTCLASS + 0X00000103)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICESTATUSREQ       (MngrCLASSID_EXLISTCLASS + 0X00000104)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICESTATUSRESP       (MngrCLASSID_EXLISTCLASS + 0X00000105)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECONFIGREQ       (MngrCLASSID_EXLISTCLASS + 0X00000106)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECONFIGRESP       (MngrCLASSID_EXLISTCLASS + 0X00000107)
#define MNGRCLASSID_CTCPEDGEPKGDATA_SYSALARM       (MngrCLASSID_EXLISTCLASS + 0X00000108)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEGETLOGRESP       (MngrCLASSID_EXLISTCLASS + 0X00000109)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONINSTALLREQ       (MngrCLASSID_EXLISTCLASS + 0X0000010A)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONINSTALLRESP       (MngrCLASSID_EXLISTCLASS + 0X0000010B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSTATUSREQ       (MngrCLASSID_EXLISTCLASS + 0X0000010C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFORESP_LINKS       (MngrCLASSID_EXLISTCLASS + 0X0000010D)
#define MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFORESP_LINK       (MngrCLASSID_EXLISTCLASS + 0X0000010E)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSTATUSRESP       (MngrCLASSID_EXLISTCLASS + 0X0000010F)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSTARTREQ       (MngrCLASSID_EXLISTCLASS + 0X00000110)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSTARTRESP       (MngrCLASSID_EXLISTCLASS + 0X00000111)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSTOPREQ       (MngrCLASSID_EXLISTCLASS + 0X00000112)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSTOPRESP       (MngrCLASSID_EXLISTCLASS + 0X00000113)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONRESTARTREQ       (MngrCLASSID_EXLISTCLASS + 0X00000114)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONRESTARTRESP       (MngrCLASSID_EXLISTCLASS + 0X00000115)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONREMOVEREQ       (MngrCLASSID_EXLISTCLASS + 0X00000116)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONREMOVERESP       (MngrCLASSID_EXLISTCLASS + 0X00000117)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONGETCONFIGREQ       (MngrCLASSID_EXLISTCLASS + 0X00000118)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONGETCONFIGRESP       (MngrCLASSID_EXLISTCLASS + 0X00000119)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSETCONFIGREQ       (MngrCLASSID_EXLISTCLASS + 0X0000011A)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONSETCONFIGRESP       (MngrCLASSID_EXLISTCLASS + 0X0000011B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONALARM       (MngrCLASSID_EXLISTCLASS + 0X0000011C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONTGETLOGREQ       (MngrCLASSID_EXLISTCLASS + 0X0000011D)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONTGETLOGRESP       (MngrCLASSID_EXLISTCLASS + 0X0000011E)
#define MNGRCLASSID_CPKG_DEVICESTATUSRESP_LINKSTATES       (MngrCLASSID_EXLISTCLASS + 0X0000011F)
#define MNGRCLASSID_CPKG_DEVICESTATUSRESP_LINKSTATE       (MngrCLASSID_EXLISTCLASS + 0X00000120)
#define MNGRCLASSID_CPKG_CONSTATUSRESP_CONTSTATUS        (MngrCLASSID_EXLISTCLASS + 0X00000121)
#define MNGRCLASSID_CPKG_CONSTATUSRESP_CONTSTATU       (MngrCLASSID_EXLISTCLASS + 0X00000122)
#define MNGRCLASSID_CPKG_CONGETCONFIGRESP_CONTCFGS       (MngrCLASSID_EXLISTCLASS + 0X00000123)
#define MNGRCLASSID_CPKG_CONGETCONFIGRESP_CONTCFG       (MngrCLASSID_EXLISTCLASS + 0X00000124)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLREQ       (MngrCLASSID_EXLISTCLASS + 0X00000125)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLRESP       (MngrCLASSID_EXLISTCLASS + 0X00000126)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLSTATUSREQ       (MngrCLASSID_EXLISTCLASS + 0X00000127)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLSTATUSRESP       (MngrCLASSID_EXLISTCLASS + 0X00000128)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLRESULT       (MngrCLASSID_EXLISTCLASS + 0X00000129)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSTATUSREQ       (MngrCLASSID_EXLISTCLASS + 0X0000012A)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSTATUSRESP       (MngrCLASSID_EXLISTCLASS + 0X0000012B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCONFIGRESP       (MngrCLASSID_EXLISTCLASS + 0X0000012C)
#define MNGRCLASSID_CPKG_APPSTATUSRESP_APPSTATUS       (MngrCLASSID_EXLISTCLASS + 0X0000012D)
#define MNGRCLASSID_CPKG_APPSTATUSRESP_APPSTATU       (MngrCLASSID_EXLISTCLASS + 0X0000012E)
#define MNGRCLASSID_CPKG_APPSTATUSRESP_APPSTAPROCS       (MngrCLASSID_EXLISTCLASS + 0X0000012F)
#define MNGRCLASSID_CPKG_APPSTATUSRESP_APPSTAPROC       (MngrCLASSID_EXLISTCLASS + 0X00000130)
#define MNGRCLASSID_CPKG_APPGETCONFIGRESP_APPCFGS        (MngrCLASSID_EXLISTCLASS + 0X00000131)
#define MNGRCLASSID_CPKG_APPGETCONFIGRESP_APPCFG       (MngrCLASSID_EXLISTCLASS + 0X00000132)
#define MNGRCLASSID_CPKG_GETMODELRESP_MODELS       (MngrCLASSID_EXLISTCLASS + 0X00000133)
#define MNGRCLASSID_CPKG_GETMODELRESP_MODEL       (MngrCLASSID_EXLISTCLASS + 0X00000134)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPGETLOGRESP	   (MngrCLASSID_EXLISTCLASS + 0X00000135)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPGETLOGREQ	   (MngrCLASSID_EXLISTCLASS + 0X00000136)
#define MNGRCLASSID_CTCPEDGEPKGDATA_CONTGETLOGRES		(MngrCLASSID_EXLISTCLASS + 0X00000137)
#define MNGRCLASSID_CPKG_GETTOPFILERESP_FILES			(MngrCLASSID_EXLISTCLASS + 0X00000138)
#define MNGRCLASSID_CPKG_GETMESSAGERESP_FILES			(MngrCLASSID_EXLISTCLASS + 0X00000139)
#define MNGRCLASSID_CPKG_GETDATASUBSRESP_SUBSVCS		(MngrCLASSID_EXLISTCLASS + 0X00000140)
#define MNGRCLASSID_CPKG_GETDATASUBS_SUBSVCS			(MngrCLASSID_EXLISTCLASS + 0X00000141)
#define MNGRCLASSID_CPKG_GETDATASUBS_SUBS			(MngrCLASSID_EXLISTCLASS + 0X00000142)
#define MNGRCLASSID_CPKG_DATASUBSRESP_SUBSVCDEVS		(MngrCLASSID_EXLISTCLASS + 0X00000143)
#define MNGRCLASSID_CPKG_DATAREADDEVSVCS			(MngrCLASSID_EXLISTCLASS + 0X00000144)
#define MNGRCLASSID_CPKG_PARASET_PARALISTS			(MngrCLASSID_EXLISTCLASS + 0X00000145)
#define MNGRCLASSID_CPKG_PARAREADSVCS			(MngrCLASSID_EXLISTCLASS + 0X00000146)
#define MNGRCLASSID_CPKG_DATAREADDEVS			(MngrCLASSID_EXLISTCLASS + 0X00000147)

#define MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCFGFILEREQ       (MngrCLASSID_EXLISTCLASS + 0X00000148)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCFGFILERESP       (MngrCLASSID_EXLISTCLASS + 0X00000149)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCFGFILEREQ       (MngrCLASSID_EXLISTCLASS + 0X0000014A)
#define MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCFGFILERESP       (MngrCLASSID_EXLISTCLASS + 0X0000014B)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETHISEVENT       (MngrCLASSID_EXLISTCLASS + 0X0000014C)
#define MNGRCLASSID_CTCPEDGEPKGDATA_GETHISEVENTRESP       (MngrCLASSID_EXLISTCLASS + 0X0000014D)
#define MNGRCLASSID_CPKG_GETHISEVENT_DEVICES       (MngrCLASSID_EXLISTCLASS + 0X0000014E)
#define MNGRCLASSID_CPKG_GETHISEVENT_DEVICE       (MngrCLASSID_EXLISTCLASS + 0X0000014F)
#define MNGRCLASSID_CPKG_GETHISEVENTRESP_DEVICES       (MngrCLASSID_EXLISTCLASS + 0X00000150)
#define MNGRCLASSID_CPKG_GETHISEVENTRESP_DEVICE       (MngrCLASSID_EXLISTCLASS + 0X00000151)

class CTcpEdgePkgXmlRWKeys : public CXmlRWKeys
{
protected:
	CTcpEdgePkgXmlRWKeys();
	virtual ~CTcpEdgePkgXmlRWKeys();
	static long g_nMngrRef;

public:
	static CTcpEdgePkgXmlRWKeys* g_pXmlKeys;
	static CTcpEdgePkgXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCTcpEdgePkgStringKey; //
	BSTR m_strCTcpEdgePkgBaseKey; //
	BSTR m_strCTcpEdgePkgData_AppStartReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppStartRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppStopReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppStopRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppRemoveReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppRemoveRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppEnableReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppEnableRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppDisableReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppDisableRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppGetConfigReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppSetConfigReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppSetConfigRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppAlarmKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceGetLogReqKey; //Data
	BSTR m_strCTcpEdgePkgData_GetModelKey; //Data
	BSTR m_strCPkg_GetModelResp_ModKey; //
	BSTR m_strCPkg_GetModelResp_ModsKey; //Models
	BSTR m_strCTcpEdgePkgData_GetModelRespKey; //Data
	BSTR m_strCPkg_ModelChange_ModKey; //
	BSTR m_strCPkg_ModelChange_ModsKey; //Models
	BSTR m_strCTcpEdgePkgData_ModelChangeKey; //Data
	BSTR m_strCPkg_ModelChangeResp_ModKey; //
	BSTR m_strCPkg_ModelChangeResp_ModsKey; //Models
	BSTR m_strCTcpEdgePkgData_ModelChangeRespKey; //Data
	BSTR m_strCPkg_DevAdd_DevKey; //
	BSTR m_strCPkg_DevAdd_DevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_DevAddKey; //Data
	BSTR m_strCPkg_DevAddResp_DevKey; //
	BSTR m_strCPkg_DevAddResp_DevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_DevAddRespKey; //Data
	BSTR m_strCPkg_DevUpdate_DevKey; //
	BSTR m_strCPkg_DevUpdate_DevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_DevUpdateKey; //Data
	BSTR m_strCPkg_DevUpdateResp_DevKey; //
	BSTR m_strCPkg_DevUpdateResp_DevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_DevUpdateRespKey; //Data
	BSTR m_strCPkg_ModelDevRead_ModKey; //
	BSTR m_strCPkg_ModelDevRead_ModsKey; //Models
	BSTR m_strCTcpEdgePkgData_ModelDevReadKey; //Data
	BSTR m_strCPkg_ModelDevReadResp_ModDevKey; //
	BSTR m_strCPkg_ModelDevReadResp_ModDevsKey; //Devices
	BSTR m_strCPkg_ModelDevReadResp_ModKey; //
	BSTR m_strCPkg_ModelDevReadResp_ModsKey; //Models
	BSTR m_strCTcpEdgePkgData_ModelDevReadRespKey; //Data
	BSTR m_strCPkg_DataSubs_SubsSvcDLKey; //
	BSTR m_strCPkg_DataSubs_SubsSvcDLsKey; //DataList
	BSTR m_strCPkg_DataSubs_SubsSvcDevKey; //
	BSTR m_strCPkg_DataSubs_SubsSvcDevsKey; //DeviceList
	BSTR m_strCPkg_DataSubs_SubsSvcKey; //
	BSTR m_strCPkg_DataSubs_SubsSvcsKey; //Services
	BSTR m_strCPkg_DatSubs_SubKey; //
	BSTR m_strCPkg_DatSubs_SubsKey; //Subs
	BSTR m_strCTcpEdgePkgData_DataSubsKey; //Data
	BSTR m_strCPkg_DataSubsResp_SubSvcDevKey; //
	BSTR m_strCPkg_DataSubsResp_SubSvcKey; //
	BSTR m_strCPkg_DataSubsResp_SubKey; //
	BSTR m_strCPkg_DataSubsResp_SubsKey; //Subs
	BSTR m_strCTcpEdgePkgData_DataSubsRespKey; //Data
	BSTR m_strCPkg_GetDataSubs_SubSvcDevKey; //
	BSTR m_strCPkg_GetDataSubs_SubSvcDevsKey; //DeviceList
	BSTR m_strCPkg_GetDataSubs_SubSvcKey; //
	BSTR m_strCPkg_GetDataSubs_SubKey; //
	BSTR m_strCTcpEdgePkgData_GetDataSubsKey; //Data
	BSTR m_strCPkg_GetDataSubsResp_SubSvcDLKey; //
	BSTR m_strCPkg_GetDataSubsResp_SubSvcDLsKey; //DataList
	BSTR m_strCPkg_GetDataSubsResp_SubSvcDevKey; //
	BSTR m_strCPkg_GetDataSubsResp_SubSvcDevsKey; //DeviceList
	BSTR m_strCPkg_GetDataSubsResp_SubSvcKey; //
	BSTR m_strCPkg_GetDataSubsResp_SubKey; //
	BSTR m_strCPkg_GetDataSubsResp_SubsKey; //Subs
	BSTR m_strCTcpEdgePkgData_GetDataSubsRespKey; //Data
	BSTR m_strCPkg_DataSpontDevSvcDLKey; //
	BSTR m_strCPkg_DataSpontDevSvcDLsKey; //DataList
	BSTR m_strCPkg_DataSpontDevSvcKey; //
	BSTR m_strCPkg_DataSpontDevSvcsKey; //Services
	BSTR m_strCPkg_DataSpontDevKey; //
	BSTR m_strCPkg_DataSpontDevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_DataSpontKey; //Data
	BSTR m_strCPkg_DataSpontRespDevKey; //
	BSTR m_strCPkg_DataSpontRespDevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_DataSpontRespKey; //Data
	BSTR m_strCPkg_DataReadDevSvcDLKey; //
	BSTR m_strCPkg_DataReadDevSvcKey; //
	BSTR m_strCPkg_DataReadDevKey; //
	BSTR m_strCTcpEdgePkgData_DataReadKey; //Data
	BSTR m_strCPkg_DataReadRespDevSvcDLKey; //
	BSTR m_strCPkg_DataReadRespDevSvcKey; //
	BSTR m_strCPkg_DataReadRespDevKey; //
	BSTR m_strCTcpEdgePkgData_DataReadRespKey; //Data
	BSTR m_strCPkg_ParaReadSvcDLKey; //
	BSTR m_strCPkg_ParaReadSvcKey; //
	BSTR m_strCTcpEdgePkgData_ParaReadKey; //Data
	BSTR m_strCPkg_ParaReadRespSvcDLKey; //
	BSTR m_strCPkg_ParaReadRespSvcDLsKey; //DataList
	BSTR m_strCPkg_ParaReadRespSvcKey; //
	BSTR m_strCPkg_ParaReadRespSvcsKey; //Services
	BSTR m_strCTcpEdgePkgData_ParaReadRespKey; //Data
	BSTR m_strCTcpEdgePkgData_GetTopoFileKey; //Data
	BSTR m_strCPkg_GetTopFileResp_FileKey; //
	BSTR m_strCTcpEdgePkgData_GetTopoFileRespKey; //Data
	BSTR m_strCTcpEdgePkgData_GetMessageKey; //Data
	BSTR m_strCPkg_GetMessageResp_FileKey; //
	BSTR m_strCTcpEdgePkgData_GetMessageRespKey; //Data
	BSTR m_strCTcpEdgePkgData_CtrlCmdKey; //Data
	BSTR m_strCTcpEdgePkgData_CtrlCmdRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ParaSetKey; //Data
	BSTR m_strCTcpEdgePkgData_ParaSetRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ParaActivateKey; //Data
	BSTR m_strCTcpEdgePkgData_ParaActivateRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ParaCancelKey; //Data
	BSTR m_strCTcpEdgePkgData_ParaCancelRespKey; //Data
	BSTR m_strCPkg_GetHisData_DevSvcKey; //
	BSTR m_strCPkg_GetHisData_DevSvcsKey; //Services
	BSTR m_strCPkg_GetHisData_DevKey; //
	BSTR m_strCPkg_GetHisData_DevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_GetHisDataKey; //Data
	BSTR m_strCPkg_GetHisDataResp_DevSvcDLKey; //
	BSTR m_strCPkg_GetHisDataResp_DevSvcDLsKey; //DataList
	BSTR m_strCPkg_GetHisDataResp_DevSvcKey; //
	BSTR m_strCPkg_GetHisDataResp_DevSvcsKey; //Services
	BSTR m_strCPkg_GetHisDataResp_DevKey; //
	BSTR m_strCPkg_GetHisDataResp_DevsKey; //Devices
	BSTR m_strCTcpEdgePkgData_GetHisDataRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppGetLogReqKey;
	BSTR m_strCTcpEdgePkgDataKey; //Data
	BSTR m_strCTcpEdgePkgKey; //Data
	BSTR m_strCPxPkgDataBaseKey; //Data
	BSTR m_strContinueKey; //Continue
	BSTR m_strDeviceIdKey; //DeviceId
	BSTR m_strDeviceDescKey; //DeviceDesc
	BSTR m_strServiceIdKey; //ServiceId
	BSTR m_strDataReferKey; //DataRefer
	BSTR m_strValueKey; //Value
	BSTR m_strAngleKey; //Angle
	BSTR m_strTimeStampKey; //TimeStamp
	BSTR m_strQualityKey; //Quality
	BSTR m_strMaxNumberKey; //MaxNumber
	BSTR m_strIntervalKey; //Interval
	BSTR m_strEndTimeKey; //EndTime
	BSTR m_strStartTimeKey; //StartTime
	BSTR m_strStatusKey; //Status
	BSTR m_strErrorCodeKey; //ErrorCode
	BSTR m_strNoteKey; //Note
	BSTR m_strSetIdKey; //SetId
	BSTR m_strCtrlTypeKey; //CtrlType
	BSTR m_strCtrlValKey; //CtrlVal
	BSTR m_strZipTypeKey; //ZipType
	BSTR m_strFileTypeKey; //FileType
	BSTR m_strFullPathFileNameKey; //FullPathFileName
	BSTR m_strStartByteKey;
	BSTR m_strModifyTimeKey; //ModifyTime
	BSTR m_strFileCrcKey; //FileCrc
	BSTR m_strDataAllKey; //DataAll
	BSTR m_strTransCotKey; //TransCot
	BSTR m_strModelKey; //Model
	BSTR m_strSpontKey; //Spont
	BSTR m_strPeriodKey; //Period
	BSTR m_strAllDevKey; //AllDev
	BSTR m_strAllDataKey; //AllData
	BSTR m_strModelAllKey; //ModelAll
	BSTR m_strModelNameKey; //ModelName
	BSTR m_strChangeTypeKey; //ChangeType
	BSTR m_strContainerKey; //Container
	BSTR m_strAppKey; //App
	BSTR m_strEventKey; //Event
	BSTR m_strMsgKey; //Msg
	BSTR m_strCfgCpuKey; //CfgCpu
	BSTR m_strCfgMemKey; //CfgMem
	BSTR m_strCPkg_GetModelResp_ModelKey; //
	BSTR m_strCPkg_GetModelResp_ModelsKey; //Models
	BSTR m_strCPkg_AppGetConfigResp_AppCfgKey; //
	BSTR m_strCPkg_AppGetConfigResp_AppCfgsKey; //AppCfgs
	BSTR m_strCPkg_AppStatusResp_AppStaProcKey; //
	BSTR m_strCPkg_AppStatusResp_AppStaProcsKey; //Process
	BSTR m_strCPkg_AppStatusResp_AppStatuKey; //
	BSTR m_strCPkg_AppStatusResp_AppStatusKey; //AppStatus
	BSTR m_strCTcpEdgePkgData_AppGetConfigRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppStatusRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppStatusReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppInstallResultKey; //Data
	BSTR m_strCTcpEdgePkgData_AppInstallStatusRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppInstallStatusReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppGetLogRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppInstallRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppInstallReqKey; //Data
	BSTR m_strCPkg_ConGetConfigResp_ContCfgKey; //
	BSTR m_strCPkg_ConGetConfigResp_ContCfgsKey; //ContCfgs
	BSTR m_strCPkg_ConStatusResp_ContStatuKey; //
	BSTR m_strCPkg_ConStatusResp_ContStatusKey; //ContStatus
	BSTR m_strCPkg_DeviceStatusResp_LinkStateKey; //
	BSTR m_strCPkg_DeviceStatusResp_LinkStatesKey; //LinkState
	BSTR m_strCTcpEdgePkgData_ContGetLogRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ContGetLogReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConAlarmKey; //Data
	BSTR m_strCTcpEdgePkgData_ConSetConfigRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConSetConfigReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConGetConfigRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConGetConfigReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConRemoveRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConRemoveReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConRestartRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConRestartReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConStopRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConStopReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConStartRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConStartReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConStatusRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceInfoResp_LinkKey; //
	BSTR m_strCTcpEdgePkgData_DeviceInfoResp_LinksKey; //Links
	BSTR m_strCTcpEdgePkgData_ConStatusReqKey; //Data
	BSTR m_strCTcpEdgePkgData_ConInstallRespKey; //Data
	BSTR m_strCTcpEdgePkgData_ConInstallReqKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceGetLogRespKey; //Data
	BSTR m_strCTcpEdgePkgData_SysAlarmKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceConfigRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceConfigReqKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceStatusRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceStatusReqKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceInfoRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceInfoReqKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceCtrlRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceCtrlReqKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceUpdateResultKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceUpdateStatusRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceUpdateStatusReqKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceUpdateRespKey; //Data
	BSTR m_strCTcpEdgePkgData_DeviceUpdateReqKey; //Data
	BSTR m_strCTcpEdgePkgData_TimeReadRespKey; //Data
	BSTR m_strCTcpEdgePkgData_TimeReadReqKey; //Data
	BSTR m_strCTcpEdgePkgData_TimeSyncRespKey; //Data
	BSTR m_strCTcpEdgePkgData_TimeSyncReqKey; //Data
	BSTR m_strCTcpEdgePkgData_FileSendRespKey; //Data
	BSTR m_strCTcpEdgePkgData_FileSendKey; //Data
	BSTR m_strCTcpEdgePkgData_FileDataTransRespKey; //Data
	BSTR m_strCTcpEdgePkgData_FileDataTransKey; //Data
	BSTR m_strCTcpEdgePkgData_FileGetRespKey; //Data
	BSTR m_strCTcpEdgePkgData_FileGetKey; //Data
	BSTR m_strCTcpEdgePkgData_HealthKey; //Data
	BSTR m_strCTcpEdgePkgHeadKey; //Head
	BSTR m_strCTcpEdgeAuth_0x03Key; //Data
	BSTR m_strCTcpEdgeAuth_0x02Key; //Data
	BSTR m_strCTcpEdgeAuth_0x01Key; //Data
	BSTR m_strCTcpEdgePkgFileKey; //File
	BSTR m_strCTcpEdgePkgCfgDiskKey; //CfgDisk
	BSTR m_strCTcpEdgePkgCfgMemKey; //CfgMem
	BSTR m_strCTcpEdgePkgCfgCpuKey; //CfgCpu
	//BSTR m_strCTcpEdgePkgMemUsedKey; //MemUsed
	BSTR m_strCTcpEdgePkgOsKey; //Os
	BSTR m_strCTcpEdgePkgTemperatureKey; //Temperature
	BSTR m_strCTcpEdgePkgDiskKey; //Disk
	BSTR m_strCTcpEdgePkgMemKey; //Mem
	BSTR m_strCTcpEdgePkgCpuKey; //Cpu
	BSTR m_strCTcpEdgePkgDevKey; //Dev
	BSTR m_strDevTypeKey; //DevType
	BSTR m_strDevNameKey; //DevName
	BSTR m_strMfgInfoKey; //MfgInfo
	BSTR m_strHardVersionKey; //HardVersion
	BSTR m_strCpusKey; //Cpus
	BSTR m_strFrequencyKey; //Frequency
	BSTR m_strCacheKey; //Cache
	BSTR m_strArchKey; //Arch
	BSTR m_strCpuLmtKey; //CpuLmt
	BSTR m_strPhyKey; //Phy
	BSTR m_strVirtKey; //Virt
	BSTR m_strMemLmtKey; //MemLmt
	BSTR m_strDiskKey; //Disk
	BSTR m_strDiskLmtKey; //DiskLmt
	BSTR m_strTemLowKey; //TemLow
	BSTR m_strTemHighKey; //TemHigh
	BSTR m_strDistroKey; //Distro
	BSTR m_strVersionKey; //Version
	BSTR m_strKernelKey; //Kernel
	BSTR m_strSoftVersionKey; //SoftVersion
	BSTR m_strPatchVersionKey; //PatchVersion
	BSTR m_strMemoryKey; //Memory
	BSTR m_strPathKey; //Path
	BSTR m_strSizeKey; //Size
	BSTR m_strFunNameKey; //FunName
	BSTR m_strCotKey; //Cot
	BSTR m_strMidKey; //Mid
	BSTR m_strTimestampKey; //Timestamp
	BSTR m_strCmdIdKey; //CmdId
	BSTR m_strFileSizeKey; //FileSize
	BSTR m_strFileSegNoKey; //FileSegNo
	BSTR m_strContentKey; //Content
	BSTR m_strTimeKey; //Time
	BSTR m_strJobIdKey; //JobId
	BSTR m_strPolicyKey; //Policy
	BSTR m_strUpgradeTypeKey; //UpgradeType
	BSTR m_strFileKey; //File
	BSTR m_strProgressKey; //Progress
	BSTR m_strStateKey; //State
	BSTR m_strActionKey; //Action
	BSTR m_strCpuRateKey; //CpuRate
	BSTR m_strDiskUsedKey; //DiskUsed
	BSTR m_strTempValueKey; //TempValue
	BSTR m_strDevDateTimeKey; //DevDateTime
	BSTR m_strDevStDateTimeKey; //DevStDateTime
	BSTR m_strDevRunTimeKey; //DevRunTime
	BSTR m_strLongitudeKey; //Longitude
	BSTR m_strLatitudeKey; //Latitude
	BSTR m_strTypeKey; //Type
	BSTR m_strIdKey; //Id
	BSTR m_strMacKey; //Mac
	BSTR m_strNameKey; //Name
	BSTR m_strCfgDiskKey;
	BSTR m_strMemUsedKey; //MemUsed
	BSTR m_strIpKey; //Ip
	BSTR m_strCreatedKey; //Created
	BSTR m_strStartedKey; //Started
	BSTR m_strLifeTimeKey; //LifeTime
	BSTR m_strImageKey; //Image
	BSTR m_strEnableKey; //Enable
	BSTR m_strAppHashKey; //AppHash
	BSTR m_strSrvNumberKey; //SrvNumber
	BSTR m_strSrvIndexKey; //SrvIndex
	BSTR m_strSrvNameKey; //SrvName
	BSTR m_strSrvEnableKey; //SrvEnable
	BSTR m_strSrvStatusKey; //SrvStatus
	BSTR m_strCPkg_GetTopFileResp_FilesKey;
	BSTR m_strCPkg_GetMessageResp_FilesKey;
	BSTR m_strCPkg_DataReadDevSvcDLsKey;
	BSTR m_strCPkg_DataReadDevSvcsKey; //Services
	BSTR m_strCPkg_GetDataSubsResp_SubSvcsKey;
	BSTR m_strCPkg_DataSubsResp_SubSvcsKey;
	BSTR m_strCPkg_DataSubsResp_SubSvcDevsKey;
	BSTR m_strCPkg_GetDataSubs_SubSvcsKey; //Services
	BSTR m_strCPkg_GetDataSubs_SubsKey; //Subs
	BSTR m_strCPkg_ParaReadSvcsKey; //Data
	BSTR m_strCPkg_ParaSet_ParaListsKey;
	BSTR m_strCPkg_ParaSet_ParaListKey;
	BSTR m_strCPkg_DataReadDevsKey;


	BSTR m_strCPkg_GetHisEventResp_DeviceKey; //
	BSTR m_strCPkg_GetHisEventResp_DevicesKey; //Devices
	BSTR m_strCPkg_GetHisEvent_DeviceKey; //
	BSTR m_strCPkg_GetHisEvent_DevicesKey; //Devices
	BSTR m_strCTcpEdgePkgData_GetHisEventRespKey; //Data
	BSTR m_strCTcpEdgePkgData_GetHisEventKey; //Data
	BSTR m_strCTcpEdgePkgData_AppSetCfgFileRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppSetCfgFileReqKey; //Data
	BSTR m_strCTcpEdgePkgData_AppGetCfgFileRespKey; //Data
	BSTR m_strCTcpEdgePkgData_AppGetCfgFileReqKey; //Data
	BSTR m_strEventDescKey; //EventDesc
	BSTR m_strResultKey; //Result
	BSTR m_strDataDescKey; //DataDesc
	BSTR m_strDZTypeKey;
	BSTR m_strDZValKey;

public:
	static BSTR CPkg_GetHisEventResp_DeviceKey()  {   return g_pXmlKeys->m_strCPkg_GetHisEventResp_DeviceKey;  }
	static BSTR CPkg_GetHisEventResp_DevicesKey()  {   return g_pXmlKeys->m_strCPkg_GetHisEventResp_DevicesKey;  }
	static BSTR CPkg_GetHisEvent_DeviceKey()  {   return g_pXmlKeys->m_strCPkg_GetHisEvent_DeviceKey;  }
	static BSTR CPkg_GetHisEvent_DevicesKey()  {   return g_pXmlKeys->m_strCPkg_GetHisEvent_DevicesKey;  }
	static BSTR CTcpEdgePkgData_GetHisEventRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetHisEventRespKey;  }
	static BSTR CTcpEdgePkgData_GetHisEventKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetHisEventKey;  }
	static BSTR CTcpEdgePkgData_AppSetCfgFileRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppSetCfgFileRespKey;  }
	static BSTR CTcpEdgePkgData_AppSetCfgFileReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppSetCfgFileReqKey;  }
	static BSTR CTcpEdgePkgData_AppGetCfgFileRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppGetCfgFileRespKey;  }
	static BSTR CTcpEdgePkgData_AppGetCfgFileReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppGetCfgFileReqKey;  }

	static BSTR EventDescKey()  {   return g_pXmlKeys->m_strEventDescKey;  }
	static BSTR ResultKey()  {   return g_pXmlKeys->m_strResultKey;  }
	static BSTR DataDescKey()  {   return g_pXmlKeys->m_strDataDescKey;  }
	static BSTR DZTypeKey()  {   return g_pXmlKeys->m_strDZTypeKey;  }
	static BSTR DZValKey()  {   return g_pXmlKeys->m_strDZValKey;  }



	static BSTR CPkg_GetDataSubs_SubSvcsKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubs_SubSvcsKey;  }
	static BSTR CPkg_GetDataSubs_SubsKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubs_SubsKey;  }
	static BSTR CPkg_DataReadDevSvcsKey()   {  return g_pXmlKeys->m_strCPkg_DataReadDevSvcsKey;  }
	static BSTR CPkg_DataReadDevsKey()	{  return g_pXmlKeys->m_strCPkg_DataReadDevsKey;  }
	static BSTR CTcpEdgePkgStringKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgStringKey;  }
	static BSTR CTcpEdgePkgBaseKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgBaseKey;  }
	static BSTR CTcpEdgePkgData_AppStartReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppStartReqKey;  }
	static BSTR CTcpEdgePkgData_AppStartRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppStartRespKey;  }
	static BSTR CTcpEdgePkgData_AppStopReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppStopReqKey;  }
	static BSTR CTcpEdgePkgData_AppStopRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppStopRespKey;  }
	static BSTR CTcpEdgePkgData_AppRemoveReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppRemoveReqKey;  }
	static BSTR CTcpEdgePkgData_AppRemoveRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppRemoveRespKey;  }
	static BSTR CTcpEdgePkgData_AppEnableReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppEnableReqKey;  }
	static BSTR CTcpEdgePkgData_AppEnableRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppEnableRespKey;  }
	static BSTR CTcpEdgePkgData_AppDisableReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppDisableReqKey;  }
	static BSTR CTcpEdgePkgData_AppDisableRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppDisableRespKey;  }
	static BSTR CTcpEdgePkgData_AppGetConfigReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppGetConfigReqKey;  }
	static BSTR CTcpEdgePkgData_AppSetConfigReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppSetConfigReqKey;  }
	static BSTR CTcpEdgePkgData_AppSetConfigRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppSetConfigRespKey;  }
	static BSTR CTcpEdgePkgData_AppAlarmKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppAlarmKey;  }
	static BSTR CTcpEdgePkgData_DeviceGetLogReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceGetLogReqKey;  }
	static BSTR CTcpEdgePkgData_GetModelKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetModelKey;  }
	static BSTR CPkg_GetModelResp_ModKey()  {   return g_pXmlKeys->m_strCPkg_GetModelResp_ModKey;  }
	static BSTR CPkg_GetModelResp_ModsKey()  {   return g_pXmlKeys->m_strCPkg_GetModelResp_ModsKey;  }
	static BSTR CTcpEdgePkgData_GetModelRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetModelRespKey;  }
	static BSTR CPkg_ModelChange_ModKey()  {   return g_pXmlKeys->m_strCPkg_ModelChange_ModKey;  }
	static BSTR CPkg_ModelChange_ModsKey()  {   return g_pXmlKeys->m_strCPkg_ModelChange_ModsKey;  }
	static BSTR CTcpEdgePkgData_ModelChangeKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ModelChangeKey;  }
	static BSTR CPkg_ModelChangeResp_ModKey()  {   return g_pXmlKeys->m_strCPkg_ModelChangeResp_ModKey;  }
	static BSTR CPkg_ModelChangeResp_ModsKey()  {   return g_pXmlKeys->m_strCPkg_ModelChangeResp_ModsKey;  }
	static BSTR CTcpEdgePkgData_ModelChangeRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ModelChangeRespKey;  }
	static BSTR CPkg_DevAdd_DevKey()  {   return g_pXmlKeys->m_strCPkg_DevAdd_DevKey;  }
	static BSTR CPkg_DevAdd_DevsKey()  {   return g_pXmlKeys->m_strCPkg_DevAdd_DevsKey;  }
	static BSTR CTcpEdgePkgData_DevAddKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DevAddKey;  }
	static BSTR CPkg_DevAddResp_DevKey()  {   return g_pXmlKeys->m_strCPkg_DevAddResp_DevKey;  }
	static BSTR CPkg_DevAddResp_DevsKey()  {   return g_pXmlKeys->m_strCPkg_DevAddResp_DevsKey;  }
	static BSTR CTcpEdgePkgData_DevAddRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DevAddRespKey;  }
	static BSTR CPkg_DevUpdate_DevKey()  {   return g_pXmlKeys->m_strCPkg_DevUpdate_DevKey;  }
	static BSTR CPkg_DevUpdate_DevsKey()  {   return g_pXmlKeys->m_strCPkg_DevUpdate_DevsKey;  }
	static BSTR CTcpEdgePkgData_DevUpdateKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DevUpdateKey;  }
	static BSTR CPkg_DevUpdateResp_DevKey()  {   return g_pXmlKeys->m_strCPkg_DevUpdateResp_DevKey;  }
	static BSTR CPkg_DevUpdateResp_DevsKey()  {   return g_pXmlKeys->m_strCPkg_DevUpdateResp_DevsKey;  }
	static BSTR CTcpEdgePkgData_DevUpdateRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DevUpdateRespKey;  }
	static BSTR CPkg_ModelDevRead_ModKey()  {   return g_pXmlKeys->m_strCPkg_ModelDevRead_ModKey;  }
	static BSTR CPkg_ModelDevRead_ModsKey()  {   return g_pXmlKeys->m_strCPkg_ModelDevRead_ModsKey;  }
	static BSTR CTcpEdgePkgData_ModelDevReadKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ModelDevReadKey;  }
	static BSTR CPkg_ModelDevReadResp_ModDevKey()  {   return g_pXmlKeys->m_strCPkg_ModelDevReadResp_ModDevKey;  }
	static BSTR CPkg_ModelDevReadResp_ModDevsKey()  {   return g_pXmlKeys->m_strCPkg_ModelDevReadResp_ModDevsKey;  }
	static BSTR CPkg_ModelDevReadResp_ModKey()  {   return g_pXmlKeys->m_strCPkg_ModelDevReadResp_ModKey;  }
	static BSTR CPkg_ModelDevReadResp_ModsKey()  {   return g_pXmlKeys->m_strCPkg_ModelDevReadResp_ModsKey;  }
	static BSTR CTcpEdgePkgData_ModelDevReadRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ModelDevReadRespKey;  }
	static BSTR CPkg_DataSubs_SubsSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_DataSubs_SubsSvcDLKey;  }
	static BSTR CPkg_DataSubs_SubsSvcDLsKey()  {   return g_pXmlKeys->m_strCPkg_DataSubs_SubsSvcDLsKey;  }
	static BSTR CPkg_DataSubs_SubsSvcDevKey()  {   return g_pXmlKeys->m_strCPkg_DataSubs_SubsSvcDevKey;  }
	static BSTR CPkg_DataSubs_SubsSvcDevsKey()  {   return g_pXmlKeys->m_strCPkg_DataSubs_SubsSvcDevsKey;  }
	static BSTR CPkg_DataSubs_SubsSvcKey()  {   return g_pXmlKeys->m_strCPkg_DataSubs_SubsSvcKey;  }
	static BSTR CPkg_DataSubs_SubsSvcsKey()  {   return g_pXmlKeys->m_strCPkg_DataSubs_SubsSvcsKey;  }
	static BSTR CPkg_DatSubs_SubKey()  {   return g_pXmlKeys->m_strCPkg_DatSubs_SubKey;  }
	static BSTR CPkg_DatSubs_SubsKey()  {   return g_pXmlKeys->m_strCPkg_DatSubs_SubsKey;  }
	static BSTR CTcpEdgePkgData_DataSubsKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DataSubsKey;  }
	static BSTR CPkg_DataSubsResp_SubSvcDevKey()  {   return g_pXmlKeys->m_strCPkg_DataSubsResp_SubSvcDevKey;  }
	static BSTR CPkg_DataSubsResp_SubSvcKey()  {   return g_pXmlKeys->m_strCPkg_DataSubsResp_SubSvcKey;  }
	static BSTR CPkg_DataSubsResp_SubKey()  {   return g_pXmlKeys->m_strCPkg_DataSubsResp_SubKey;  }
	static BSTR CPkg_DataSubsResp_SubsKey()  {   return g_pXmlKeys->m_strCPkg_DataSubsResp_SubsKey;  }
	static BSTR CTcpEdgePkgData_DataSubsRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DataSubsRespKey;  }
	static BSTR CPkg_GetDataSubs_SubSvcDevKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubs_SubSvcDevKey;  }
	static BSTR CPkg_GetDataSubs_SubSvcDevsKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubs_SubSvcDevsKey;  }
	static BSTR CPkg_GetDataSubs_SubSvcKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubs_SubSvcKey;  }
	static BSTR CPkg_GetDataSubs_SubKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubs_SubKey;  }
	static BSTR CTcpEdgePkgData_GetDataSubsKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetDataSubsKey;  }
	static BSTR CPkg_GetDataSubsResp_SubSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubSvcDLKey;  }
	static BSTR CPkg_GetDataSubsResp_SubSvcDLsKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubSvcDLsKey;  }
	static BSTR CPkg_GetDataSubsResp_SubSvcDevKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubSvcDevKey;  }
	static BSTR CPkg_GetDataSubsResp_SubSvcDevsKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubSvcDevsKey;  }
	static BSTR CPkg_GetDataSubsResp_SubSvcKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubSvcKey;  }
	static BSTR CPkg_GetDataSubsResp_SubKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubKey;  }
	static BSTR CPkg_GetDataSubsResp_SubsKey()  {   return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubsKey;  }
	static BSTR CTcpEdgePkgData_GetDataSubsRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetDataSubsRespKey;  }
	static BSTR CPkg_DataSpontDevSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontDevSvcDLKey;  }
	static BSTR CPkg_DataSpontDevSvcDLsKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontDevSvcDLsKey;  }
	static BSTR CPkg_DataSpontDevSvcKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontDevSvcKey;  }
	static BSTR CPkg_DataSpontDevSvcsKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontDevSvcsKey;  }
	static BSTR CPkg_DataSpontDevKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontDevKey;  }
	static BSTR CPkg_DataSpontDevsKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontDevsKey;  }
	static BSTR CTcpEdgePkgData_DataSpontKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DataSpontKey;  }
	static BSTR CPkg_DataSpontRespDevKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontRespDevKey;  }
	static BSTR CPkg_DataSpontRespDevsKey()  {   return g_pXmlKeys->m_strCPkg_DataSpontRespDevsKey;  }
	static BSTR CTcpEdgePkgData_DataSpontRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DataSpontRespKey;  }
	static BSTR CPkg_DataReadDevSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_DataReadDevSvcDLKey;  }
	static BSTR CPkg_DataReadDevSvcKey()  {   return g_pXmlKeys->m_strCPkg_DataReadDevSvcKey;  }
	static BSTR CPkg_DataReadDevKey()  {   return g_pXmlKeys->m_strCPkg_DataReadDevKey;  }
	static BSTR CTcpEdgePkgData_DataReadKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DataReadKey;  }
	static BSTR CPkg_DataReadRespDevSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_DataReadRespDevSvcDLKey;  }
	static BSTR CPkg_DataReadRespDevSvcKey()  {   return g_pXmlKeys->m_strCPkg_DataReadRespDevSvcKey;  }
	static BSTR CPkg_DataReadRespDevKey()  {   return g_pXmlKeys->m_strCPkg_DataReadRespDevKey;  }
	static BSTR CTcpEdgePkgData_DataReadRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DataReadRespKey;  }
	static BSTR CPkg_ParaReadSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_ParaReadSvcDLKey;  }
	static BSTR CPkg_ParaReadSvcKey()  {   return g_pXmlKeys->m_strCPkg_ParaReadSvcKey;  }
	static BSTR CTcpEdgePkgData_ParaReadKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaReadKey;  }
	static BSTR CPkg_ParaReadRespSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_ParaReadRespSvcDLKey;  }
	static BSTR CPkg_ParaReadRespSvcDLsKey()  {   return g_pXmlKeys->m_strCPkg_ParaReadRespSvcDLsKey;  }
	static BSTR CPkg_ParaReadRespSvcKey()  {   return g_pXmlKeys->m_strCPkg_ParaReadRespSvcKey;  }
	static BSTR CPkg_ParaReadRespSvcsKey()  {   return g_pXmlKeys->m_strCPkg_ParaReadRespSvcsKey;  }
	static BSTR CTcpEdgePkgData_ParaReadRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaReadRespKey;  }
	static BSTR CTcpEdgePkgData_GetTopoFileKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetTopoFileKey;  }
	static BSTR CPkg_GetTopFileResp_FileKey()  {   return g_pXmlKeys->m_strCPkg_GetTopFileResp_FileKey;  }
	static BSTR CTcpEdgePkgData_GetTopoFileRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetTopoFileRespKey;  }
	static BSTR CTcpEdgePkgData_GetMessageKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetMessageKey;  }
	static BSTR CPkg_GetMessageResp_FileKey()  {   return g_pXmlKeys->m_strCPkg_GetMessageResp_FileKey;  }
	static BSTR CTcpEdgePkgData_GetMessageRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetMessageRespKey;  }
	static BSTR CTcpEdgePkgData_CtrlCmdKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_CtrlCmdKey;  }
	static BSTR CTcpEdgePkgData_CtrlCmdRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_CtrlCmdRespKey;  }
	static BSTR CTcpEdgePkgData_ParaSetKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaSetKey;  }
	static BSTR CTcpEdgePkgData_ParaSetRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaSetRespKey;  }
	static BSTR CTcpEdgePkgData_ParaActivateKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaActivateKey;  }
	static BSTR CTcpEdgePkgData_ParaActivateRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaActivateRespKey;  }
	static BSTR CTcpEdgePkgData_ParaCancelKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaCancelKey;  }
	static BSTR CTcpEdgePkgData_ParaCancelRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ParaCancelRespKey;  }
	static BSTR CPkg_GetHisData_DevSvcKey()  {   return g_pXmlKeys->m_strCPkg_GetHisData_DevSvcKey;  }
	static BSTR CPkg_GetHisData_DevSvcsKey()  {   return g_pXmlKeys->m_strCPkg_GetHisData_DevSvcsKey;  }
	static BSTR CPkg_ParaReadSvcsKey()			{ return g_pXmlKeys->m_strCPkg_ParaReadSvcsKey;}
	static BSTR CPkg_GetHisData_DevKey()  {   return g_pXmlKeys->m_strCPkg_GetHisData_DevKey;  }
	static BSTR CPkg_GetHisData_DevsKey()  {   return g_pXmlKeys->m_strCPkg_GetHisData_DevsKey;  }
	static BSTR CTcpEdgePkgData_GetHisDataKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetHisDataKey;  }
	static BSTR CPkg_GetHisDataResp_DevSvcDLKey()  {   return g_pXmlKeys->m_strCPkg_GetHisDataResp_DevSvcDLKey;  }
	static BSTR CPkg_GetHisDataResp_DevSvcDLsKey()  {   return g_pXmlKeys->m_strCPkg_GetHisDataResp_DevSvcDLsKey;  }
	static BSTR CPkg_GetHisDataResp_DevSvcKey()  {   return g_pXmlKeys->m_strCPkg_GetHisDataResp_DevSvcKey;  }
	static BSTR CPkg_GetHisDataResp_DevSvcsKey()  {   return g_pXmlKeys->m_strCPkg_GetHisDataResp_DevSvcsKey;  }
	static BSTR CPkg_GetHisDataResp_DevKey()  {   return g_pXmlKeys->m_strCPkg_GetHisDataResp_DevKey;  }
	static BSTR CPkg_GetHisDataResp_DevsKey()  {   return g_pXmlKeys->m_strCPkg_GetHisDataResp_DevsKey;  }
	static BSTR CTcpEdgePkgData_GetHisDataRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_GetHisDataRespKey;  }
	static BSTR CTcpEdgePkgData_AppGetLogReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppGetLogReqKey;  }
	static BSTR CTcpEdgePkgDataKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgDataKey;  }
	static BSTR CTcpEdgePkgKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgKey;  }
	static BSTR CPxPkgDataBaseKey()  {   return g_pXmlKeys->m_strCPxPkgDataBaseKey;  }
	static BSTR ContinueKey()  {   return g_pXmlKeys->m_strContinueKey;  }
	static BSTR DeviceIdKey()  {   return g_pXmlKeys->m_strDeviceIdKey;  }
	static BSTR DeviceDescKey()  {   return g_pXmlKeys->m_strDeviceDescKey;  }
	static BSTR ServiceIdKey()  {   return g_pXmlKeys->m_strServiceIdKey;  }
	static BSTR DataReferKey()  {   return g_pXmlKeys->m_strDataReferKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR AngleKey()  {   return g_pXmlKeys->m_strAngleKey;  }
	static BSTR TimeStampKey()  {   return g_pXmlKeys->m_strTimeStampKey;  }
	static BSTR QualityKey()  {   return g_pXmlKeys->m_strQualityKey;  }
	static BSTR MaxNumberKey()  {   return g_pXmlKeys->m_strMaxNumberKey;  }
	static BSTR IntervalKey()  {   return g_pXmlKeys->m_strIntervalKey;  }
	static BSTR EndTimeKey()  {   return g_pXmlKeys->m_strEndTimeKey;  }
	static BSTR StartTimeKey()  {   return g_pXmlKeys->m_strStartTimeKey;  }
	static BSTR StatusKey()  {   return g_pXmlKeys->m_strStatusKey;  }
	static BSTR ErrorCodeKey()  {   return g_pXmlKeys->m_strErrorCodeKey;  }
	static BSTR NoteKey()  {   return g_pXmlKeys->m_strNoteKey;  }
	static BSTR SetIdKey()  {   return g_pXmlKeys->m_strSetIdKey;  }
	static BSTR CtrlTypeKey()  {   return g_pXmlKeys->m_strCtrlTypeKey;  }
	static BSTR CtrlValKey()  {   return g_pXmlKeys->m_strCtrlValKey;  }
	static BSTR ZipTypeKey()  {   return g_pXmlKeys->m_strZipTypeKey;  }
	static BSTR FileTypeKey()  {   return g_pXmlKeys->m_strFileTypeKey;  }
	static BSTR FullPathFileNameKey()  {   return g_pXmlKeys->m_strFullPathFileNameKey;  }
	static BSTR StartByteKey()  {   return g_pXmlKeys->m_strStartByteKey;  }
	static BSTR ModifyTimeKey()  {   return g_pXmlKeys->m_strModifyTimeKey;  }
	static BSTR FileCrcKey()  {   return g_pXmlKeys->m_strFileCrcKey;  }
	static BSTR DataAllKey()  {   return g_pXmlKeys->m_strDataAllKey;  }
	static BSTR TransCotKey()  {   return g_pXmlKeys->m_strTransCotKey;  }
	static BSTR ModelKey()  {   return g_pXmlKeys->m_strModelKey;  }
	static BSTR SpontKey()  {   return g_pXmlKeys->m_strSpontKey;  }
	static BSTR PeriodKey()  {   return g_pXmlKeys->m_strPeriodKey;  }
	static BSTR AllDevKey()  {   return g_pXmlKeys->m_strAllDevKey;  }
	static BSTR AllDataKey()  {   return g_pXmlKeys->m_strAllDataKey;  }
	static BSTR ModelAllKey()  {   return g_pXmlKeys->m_strModelAllKey;  }
	static BSTR ModelNameKey()  {   return g_pXmlKeys->m_strModelNameKey;  }
	static BSTR ChangeTypeKey()  {   return g_pXmlKeys->m_strChangeTypeKey;  }
	static BSTR ContainerKey()  {   return g_pXmlKeys->m_strContainerKey;  }
	static BSTR AppKey()  {   return g_pXmlKeys->m_strAppKey;  }
	static BSTR EventKey()  {   return g_pXmlKeys->m_strEventKey;  }
	static BSTR MsgKey()  {   return g_pXmlKeys->m_strMsgKey;  }
	static BSTR CfgCpuKey()  {   return g_pXmlKeys->m_strCfgCpuKey;  }
	static BSTR CfgMemKey()  {   return g_pXmlKeys->m_strCfgMemKey;  }
	static BSTR CPkg_GetModelResp_ModelKey()  {   return g_pXmlKeys->m_strCPkg_GetModelResp_ModelKey;  }
	static BSTR CPkg_GetModelResp_ModelsKey()  {   return g_pXmlKeys->m_strCPkg_GetModelResp_ModelsKey;  }
	static BSTR CPkg_AppGetConfigResp_AppCfgKey()  {   return g_pXmlKeys->m_strCPkg_AppGetConfigResp_AppCfgKey;  }
	static BSTR CPkg_AppGetConfigResp_AppCfgsKey()  {   return g_pXmlKeys->m_strCPkg_AppGetConfigResp_AppCfgsKey;  }
	static BSTR CPkg_AppStatusResp_AppStaProcKey()  {   return g_pXmlKeys->m_strCPkg_AppStatusResp_AppStaProcKey;  }
	static BSTR CPkg_AppStatusResp_AppStaProcsKey()  {   return g_pXmlKeys->m_strCPkg_AppStatusResp_AppStaProcsKey;  }
	static BSTR CPkg_AppStatusResp_AppStatuKey()  {   return g_pXmlKeys->m_strCPkg_AppStatusResp_AppStatuKey;  }
	static BSTR CPkg_AppStatusResp_AppStatusKey()  {   return g_pXmlKeys->m_strCPkg_AppStatusResp_AppStatusKey;  }
	static BSTR CTcpEdgePkgData_AppGetConfigRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppGetConfigRespKey;  }
	static BSTR CTcpEdgePkgData_AppStatusRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppStatusRespKey;  }
	static BSTR CTcpEdgePkgData_AppStatusReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppStatusReqKey;  }
	static BSTR CTcpEdgePkgData_AppInstallResultKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppInstallResultKey;  }
	static BSTR CTcpEdgePkgData_AppInstallStatusRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppInstallStatusRespKey;  }
	static BSTR CTcpEdgePkgData_AppInstallStatusReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppInstallStatusReqKey;  }
	static BSTR CTcpEdgePkgData_AppGetLogRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppGetLogRespKey;  }
	static BSTR CTcpEdgePkgData_AppInstallRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppInstallRespKey;  }
	static BSTR CTcpEdgePkgData_AppInstallReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_AppInstallReqKey;  }
	static BSTR CPkg_ConGetConfigResp_ContCfgKey()  {   return g_pXmlKeys->m_strCPkg_ConGetConfigResp_ContCfgKey;  }
	static BSTR CPkg_ConGetConfigResp_ContCfgsKey()  {   return g_pXmlKeys->m_strCPkg_ConGetConfigResp_ContCfgsKey;  }
	static BSTR CPkg_ConStatusResp_ContStatuKey()  {   return g_pXmlKeys->m_strCPkg_ConStatusResp_ContStatuKey;  }
	static BSTR CPkg_ConStatusResp_ContStatusKey()  {   return g_pXmlKeys->m_strCPkg_ConStatusResp_ContStatusKey;  }
	static BSTR CPkg_DeviceStatusResp_LinkStateKey()  {   return g_pXmlKeys->m_strCPkg_DeviceStatusResp_LinkStateKey;  }
	static BSTR CPkg_DeviceStatusResp_LinkStatesKey()  {   return g_pXmlKeys->m_strCPkg_DeviceStatusResp_LinkStatesKey;  }
	static BSTR CTcpEdgePkgData_ContGetLogRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ContGetLogRespKey;  }
	static BSTR CTcpEdgePkgData_ContGetLogReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ContGetLogReqKey;  }
	static BSTR CTcpEdgePkgData_ConAlarmKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConAlarmKey;  }
	static BSTR CTcpEdgePkgData_ConSetConfigRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConSetConfigRespKey;  }
	static BSTR CTcpEdgePkgData_ConSetConfigReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConSetConfigReqKey;  }
	static BSTR CTcpEdgePkgData_ConGetConfigRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConGetConfigRespKey;  }
	static BSTR CTcpEdgePkgData_ConGetConfigReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConGetConfigReqKey;  }
	static BSTR CTcpEdgePkgData_ConRemoveRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConRemoveRespKey;  }
	static BSTR CTcpEdgePkgData_ConRemoveReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConRemoveReqKey;  }
	static BSTR CTcpEdgePkgData_ConRestartRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConRestartRespKey;  }
	static BSTR CTcpEdgePkgData_ConRestartReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConRestartReqKey;  }
	static BSTR CTcpEdgePkgData_ConStopRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConStopRespKey;  }
	static BSTR CTcpEdgePkgData_ConStopReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConStopReqKey;  }
	static BSTR CTcpEdgePkgData_ConStartRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConStartRespKey;  }
	static BSTR CTcpEdgePkgData_ConStartReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConStartReqKey;  }
	static BSTR CTcpEdgePkgData_ConStatusRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConStatusRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceInfoResp_LinkKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceInfoResp_LinkKey;  }
	static BSTR CTcpEdgePkgData_DeviceInfoResp_LinksKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceInfoResp_LinksKey;  }
	static BSTR CTcpEdgePkgData_ConStatusReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConStatusReqKey;  }
	static BSTR CTcpEdgePkgData_ConInstallRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConInstallRespKey;  }
	static BSTR CTcpEdgePkgData_ConInstallReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_ConInstallReqKey;  }
	static BSTR CTcpEdgePkgData_DeviceGetLogRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceGetLogRespKey;  }
	static BSTR CTcpEdgePkgData_SysAlarmKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_SysAlarmKey;  }
	static BSTR CTcpEdgePkgData_DeviceConfigRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceConfigRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceConfigReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceConfigReqKey;  }
	static BSTR CTcpEdgePkgData_DeviceStatusRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceStatusRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceStatusReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceStatusReqKey;  }
	static BSTR CTcpEdgePkgData_DeviceInfoRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceInfoRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceInfoReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceInfoReqKey;  }
	static BSTR CTcpEdgePkgData_DeviceCtrlRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceCtrlRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceCtrlReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceCtrlReqKey;  }
	static BSTR CTcpEdgePkgData_DeviceUpdateResultKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceUpdateResultKey;  }
	static BSTR CTcpEdgePkgData_DeviceUpdateStatusRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceUpdateStatusRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceUpdateStatusReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceUpdateStatusReqKey;  }
	static BSTR CTcpEdgePkgData_DeviceUpdateRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceUpdateRespKey;  }
	static BSTR CTcpEdgePkgData_DeviceUpdateReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_DeviceUpdateReqKey;  }
	static BSTR CTcpEdgePkgData_TimeReadRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_TimeReadRespKey;  }
	static BSTR CTcpEdgePkgData_TimeReadReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_TimeReadReqKey;  }
	static BSTR CTcpEdgePkgData_TimeSyncRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_TimeSyncRespKey;  }
	static BSTR CTcpEdgePkgData_TimeSyncReqKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_TimeSyncReqKey;  }
	static BSTR CTcpEdgePkgData_FileSendRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_FileSendRespKey;  }
	static BSTR CTcpEdgePkgData_FileSendKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_FileSendKey;  }
	static BSTR CTcpEdgePkgData_FileDataTransRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_FileDataTransRespKey;  }
	static BSTR CTcpEdgePkgData_FileDataTransKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_FileDataTransKey;  }
	static BSTR CTcpEdgePkgData_FileGetRespKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_FileGetRespKey;  }
	static BSTR CTcpEdgePkgData_FileGetKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_FileGetKey;  }
	static BSTR CTcpEdgePkgData_HealthKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgData_HealthKey;  }
	static BSTR CTcpEdgePkgHeadKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgHeadKey;  }
	static BSTR CTcpEdgeAuth_0x03Key()  {   return g_pXmlKeys->m_strCTcpEdgeAuth_0x03Key;  }
	static BSTR CTcpEdgeAuth_0x02Key()  {   return g_pXmlKeys->m_strCTcpEdgeAuth_0x02Key;  }
	static BSTR CTcpEdgeAuth_0x01Key()  {   return g_pXmlKeys->m_strCTcpEdgeAuth_0x01Key;  }
	static BSTR CTcpEdgePkgFileKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgFileKey;  }
	static BSTR CTcpEdgePkgCfgDiskKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgCfgDiskKey;  }
	static BSTR CTcpEdgePkgCfgMemKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgCfgMemKey;  }
	static BSTR CTcpEdgePkgCfgCpuKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgCfgCpuKey;  }
	//static BSTR CTcpEdgePkgMemUsedKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgMemUsedKey;  }
	static BSTR CTcpEdgePkgOsKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgOsKey;  }
	static BSTR CTcpEdgePkgTemperatureKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgTemperatureKey;  }
	static BSTR CTcpEdgePkgDiskKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgDiskKey;  }
	static BSTR CTcpEdgePkgMemKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgMemKey;  }
	static BSTR CTcpEdgePkgCpuKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgCpuKey;  }
	static BSTR CTcpEdgePkgDevKey()  {   return g_pXmlKeys->m_strCTcpEdgePkgDevKey;  }
	static BSTR DevTypeKey()  {   return g_pXmlKeys->m_strDevTypeKey;  }
	static BSTR DevNameKey()  {   return g_pXmlKeys->m_strDevNameKey;  }
	static BSTR MfgInfoKey()  {   return g_pXmlKeys->m_strMfgInfoKey;  }
	static BSTR HardVersionKey()  {   return g_pXmlKeys->m_strHardVersionKey;  }
	static BSTR CpusKey()  {   return g_pXmlKeys->m_strCpusKey;  }
	static BSTR FrequencyKey()  {   return g_pXmlKeys->m_strFrequencyKey;  }
	static BSTR CacheKey()  {   return g_pXmlKeys->m_strCacheKey;  }
	static BSTR ArchKey()  {   return g_pXmlKeys->m_strArchKey;  }
	static BSTR CpuLmtKey()  {   return g_pXmlKeys->m_strCpuLmtKey;  }
	static BSTR PhyKey()  {   return g_pXmlKeys->m_strPhyKey;  }
	static BSTR VirtKey()  {   return g_pXmlKeys->m_strVirtKey;  }
	static BSTR MemLmtKey()  {   return g_pXmlKeys->m_strMemLmtKey;  }
	static BSTR DiskKey()  {   return g_pXmlKeys->m_strDiskKey;  }
	static BSTR DiskLmtKey()  {   return g_pXmlKeys->m_strDiskLmtKey;  }
	static BSTR TemLowKey()  {   return g_pXmlKeys->m_strTemLowKey;  }
	static BSTR TemHighKey()  {   return g_pXmlKeys->m_strTemHighKey;  }
	static BSTR DistroKey()  {   return g_pXmlKeys->m_strDistroKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR KernelKey()  {   return g_pXmlKeys->m_strKernelKey;  }
	static BSTR SoftVersionKey()  {   return g_pXmlKeys->m_strSoftVersionKey;  }
	static BSTR PatchVersionKey()  {   return g_pXmlKeys->m_strPatchVersionKey;  }
	static BSTR MemoryKey()  {   return g_pXmlKeys->m_strMemoryKey;  }
	static BSTR PathKey()  {   return g_pXmlKeys->m_strPathKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR FunNameKey()  {   return g_pXmlKeys->m_strFunNameKey;  }
	static BSTR CotKey()  {   return g_pXmlKeys->m_strCotKey;  }
	static BSTR MidKey()  {   return g_pXmlKeys->m_strMidKey;  }
	static BSTR TimestampKey()  {   return g_pXmlKeys->m_strTimestampKey;  }
	static BSTR CmdIdKey()  {   return g_pXmlKeys->m_strCmdIdKey;  }
	static BSTR FileSizeKey()  {   return g_pXmlKeys->m_strFileSizeKey;  }
	static BSTR FileSegNoKey()  {   return g_pXmlKeys->m_strFileSegNoKey;  }
	static BSTR ContentKey()  {   return g_pXmlKeys->m_strContentKey;  }
	static BSTR TimeKey()  {   return g_pXmlKeys->m_strTimeKey;  }
	static BSTR JobIdKey()  {   return g_pXmlKeys->m_strJobIdKey;  }
	static BSTR PolicyKey()  {   return g_pXmlKeys->m_strPolicyKey;  }
	static BSTR UpgradeTypeKey()  {   return g_pXmlKeys->m_strUpgradeTypeKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
	static BSTR ProgressKey()  {   return g_pXmlKeys->m_strProgressKey;  }
	static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }
	static BSTR ActionKey()  {   return g_pXmlKeys->m_strActionKey;  }
	static BSTR CpuRateKey()  {   return g_pXmlKeys->m_strCpuRateKey;  }
	static BSTR DiskUsedKey()  {   return g_pXmlKeys->m_strDiskUsedKey;  }
	static BSTR TempValueKey()  {   return g_pXmlKeys->m_strTempValueKey;  }
	static BSTR DevDateTimeKey()  {   return g_pXmlKeys->m_strDevDateTimeKey;  }
	static BSTR DevStDateTimeKey()  {   return g_pXmlKeys->m_strDevStDateTimeKey;  }
	static BSTR DevRunTimeKey()  {   return g_pXmlKeys->m_strDevRunTimeKey;  }
	static BSTR LongitudeKey()  {   return g_pXmlKeys->m_strLongitudeKey;  }
	static BSTR LatitudeKey()  {   return g_pXmlKeys->m_strLatitudeKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR IdKey()  {   return g_pXmlKeys->m_strIdKey;  }
	static BSTR MacKey()  {   return g_pXmlKeys->m_strMacKey;  }
	static BSTR NameKey()  {   return g_pXmlKeys->m_strNameKey;  }
	static BSTR MemUsedKey()  {   return g_pXmlKeys->m_strMemUsedKey;  }
	static BSTR IpKey()  {   return g_pXmlKeys->m_strIpKey;  }
	static BSTR CreatedKey()  {   return g_pXmlKeys->m_strCreatedKey;  }
	static BSTR StartedKey()  {   return g_pXmlKeys->m_strStartedKey;  }
	static BSTR LifeTimeKey()  {   return g_pXmlKeys->m_strLifeTimeKey;  }
	static BSTR ImageKey()  {   return g_pXmlKeys->m_strImageKey;  }
	static BSTR EnableKey()  {   return g_pXmlKeys->m_strEnableKey;  }
	static BSTR AppHashKey()  {   return g_pXmlKeys->m_strAppHashKey;  }
	static BSTR SrvNumberKey()  {   return g_pXmlKeys->m_strSrvNumberKey;  }
	static BSTR SrvIndexKey()  {   return g_pXmlKeys->m_strSrvIndexKey;  }
	static BSTR SrvNameKey()  {   return g_pXmlKeys->m_strSrvNameKey;  }
	static BSTR SrvEnableKey()  {   return g_pXmlKeys->m_strSrvEnableKey;  }
	static BSTR SrvStatusKey()  {   return g_pXmlKeys->m_strSrvStatusKey;  }
	static BSTR CTcpEdgePkgData_ContGetLogResKey()	{	return g_pXmlKeys->m_strCTcpEdgePkgData_ContGetLogRespKey;	}
	static BSTR CPkg_ParaSet_ParaListsKey()	{	return g_pXmlKeys->m_strCPkg_ParaSet_ParaListsKey;	}
	static BSTR CPkg_GetTopFileResp_FilesKey()	{	return g_pXmlKeys->m_strCPkg_GetTopFileResp_FilesKey;	}
	static BSTR CPkg_GetMessageResp_FilesKey()	{	return g_pXmlKeys->m_strCPkg_GetMessageResp_FilesKey;	}
	static BSTR CPkg_GetDataSubsResp_SubSvcsKey()	{	return g_pXmlKeys->m_strCPkg_GetDataSubsResp_SubSvcsKey	;}
	static BSTR CPkg_DataSubsResp_SubSvcDevsKey()	{	return g_pXmlKeys->m_strCPkg_DataSubsResp_SubSvcDevsKey;	}


};



class CTcpEdgePkgConstGlobal
{
private:
	CTcpEdgePkgConstGlobal();
	virtual ~CTcpEdgePkgConstGlobal();

public:
	static CTcpEdgePkgConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CTcpEdgePkgConstGlobal *g_pGlobal;

private:
	//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

	//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
	//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

	//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
