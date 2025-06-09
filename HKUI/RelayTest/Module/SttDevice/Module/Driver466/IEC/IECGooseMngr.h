#ifndef IECGOOSEMNGR_H
#define IECGOOSEMNGR_H

#include "QMap"
#include "QtCore"
#include "QObject"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfgGooseDataBase.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfgGoutData.h"
#include "../IEC_GlobalDefine.h"
#include "../../Module/SttDevice/SttDeviceStatus.h"

class CIECGooseMngr:public QObject
{
public:
	explicit CIECGooseMngr(QObject *parent = 0);
	~CIECGooseMngr();

public:
	QVector<tmt_goose> data_gseout;
	int m_nT[4];

	void Init();
	void CreateGooseTmtStruct(CIecCfgGooseDataBase *pIecData);
	void CreateGooseByteArray(QByteArray& oAr, tmt_goose &t_GOOSE);

	BOOL CreateGooseOut_DataSetList(QByteArray& oAr, ChanelInfo &chan,char timequality);
	void GetGooseIn_DataPosAndValue(CIecCfgGooseDataBase *gsein_data,int nIndex,unsigned long& nlastByte,
									unsigned long& nTrueValue,unsigned long& nFalseValue);
    void UpdateGooseTmtDataSetList(tmt_goose &otmt_goose);
private:
	void InitChan(ChanelInfo &chaninfo,CIecCfgGoutCh *ch);
	void EncoDerGooseDataAtom(QByteArray& oAr, CIecCfgGoutCh *ch);
	void ProcessGooseDataSetList(QByteArray& oAr);
};

#endif
