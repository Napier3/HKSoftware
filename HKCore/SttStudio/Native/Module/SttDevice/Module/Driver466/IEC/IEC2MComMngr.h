#ifndef IEC2MCOMMNGR_H
#define IEC2MCOMMNGR_H

#include "QMap"
#include "QtCore"
#include "QObject"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg2MData.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg2MInData.h"
#include "../IEC_GlobalDefine.h"

typedef struct
{
    long m_nDataPkgCount;
    tmt_Stable2M m_oCmdPkg[MAX_2M_CMDIDX_COUNT];
    tmt_Stable2M m_oDataPkg[MAX_2M_DATAIDX_COUNT];
}tmt_Stable2MList;

class CIECStable2MComMngr:public QObject
{
public:
    explicit CIECStable2MComMngr(QObject *parent = 0);
    ~CIECStable2MComMngr();

public:
    tmt_Stable2MList m_oStable2MList[MAX_2M_MODULE_COUNT][MAX_2M_BLOCK_COUNT];//8 Ports
    tmt_Stable2MList m_oStable2MSubList[MAX_2M_MODULE_COUNT][MAX_2M_BLOCK_COUNT];

	void Init();

    void Create2MTmtStruct(CIecCfg2MData *pIecData);
    void Create2MByteArray(tmt_Stable2M otmt2M,long nPort,QByteArray &oPackage,BOOL bIsDataPkg);
    void Create2MListByteArray(tmt_Stable2MList oStable2MList,long nPort,QByteArray &oPackage);
    void AfterCreate2MTmt();

    void Create2MSubTmtStruct(CIecCfg2MInData *pIecData);
private:
    QList<tmt_Stable2M>  m_oDataPkgList;
};

extern long g_nStable2MDataPkgIdxMapPos[MAX_2M_BLOCKS_COUNT];

inline unsigned short SumCheck(unsigned char *pszdata,unsigned int datalen)
{
    unsigned int nRet = 0;
    for(int i = 0 ;i < datalen;)
    {
        nRet += pszdata[i];
        nRet += pszdata[i + 1]*256;
        i += 2;
    }
    nRet = ~nRet;

    return (unsigned short)(nRet & 0xFFFF);
}

#endif
