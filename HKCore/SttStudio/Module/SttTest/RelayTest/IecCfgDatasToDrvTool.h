#ifndef IECCFGDATASTODRVTOOL_H
#define IECCFGDATASTODRVTOOL_H
#include"../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

class CIecCfgDatasToDrvTool
{
public:
    CIecCfgDatasToDrvTool();
    virtual~CIecCfgDatasToDrvTool();

    BOOL IecCfgDatasToDrv(CIecCfgDatasMngr *pIecCfgDatasMngr);//����1Ϊ�����������ļ���Ӧ������󣬲���2Ϊת��Ϊ�ײ�ṹ��ʹ�õĽṹ�����
};

#endif // IECCFGDATASTODRVTOOL_H
