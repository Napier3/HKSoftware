#ifndef IECCFGDATASTODRVTOOL_H
#define IECCFGDATASTODRVTOOL_H
#include"../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

class CIecCfgDatasToDrvTool
{
public:
    CIecCfgDatasToDrvTool();
    virtual~CIecCfgDatasToDrvTool();

    BOOL IecCfgDatasToDrv(CIecCfgDatasMngr *pIecCfgDatasMngr);//参数1为测试仪配置文件对应链表对象，参数2为转化为底层结构体使用的结构体对象
};

#endif // IECCFGDATASTODRVTOOL_H
