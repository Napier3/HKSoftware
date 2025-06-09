#ifndef IEC92MNGR_H
#define IEC92MNGR_H

#include "QMap"
#include "QtCore"
#include "QObject"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg92InData.h"
#include "../IEC_GlobalDefine.h"

class CIEC92Mngr: public QObject
{
public:
    explicit CIEC92Mngr(QObject *parent = 0);
    ~CIEC92Mngr();

public:
    QVector<tmt_sv_92> data_92;
    QVector<tmt_sv_92> data_92Sub;
    void Init();
    int GetSmv92Sample()
    {
        return m_nSample;
    }
    int GetSmv92DelayTime(int nGroupIndex)
    {
        if(nGroupIndex < MAX_DIGITAL_GROUP_NUM)
        {
            return m_nDelayTime[nGroupIndex];
        }
        else
        {
            return 0;
        }
    }
    void Create92TmtStruct(CIecCfg92Data *pIecData);
    void Create92SubTmtStruct(CIecCfg92InData *pIecData);
    void Create92ByteArray(tmt_sv_92 &m_92Struct, QByteArray &m_ResultArray);
    void SetChanelMap(QMap<QString, int> oChanMap);
private:
    QMap<QString, int> m_ChanMapID;
    void InitChanelMap();
    int m_nSample;
    int m_nDelayTime[MAX_DIGITAL_GROUP_NUM];
};

#endif
