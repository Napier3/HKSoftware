#ifndef CHANNELLOWSTABLE_H
#define CHANNELLOWSTABLE_H

#include "channeltable.h"


class CHannelLowSTable : public CHannelTable
{
	Q_OBJECT

public:
	CHannelLowSTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent = 0);
	~CHannelLowSTable();
	
protected slots:
	void slot_OnCellChanged(int row,int col);

signals:
	void sig_ChannelValueChanged(MOUDLEType moudleType,/*int moudleID,*/int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）

public:
	QString initMaxAcV(int row,QString str);
	QString initMaxAcI(int row,QString str);
	QString initMaxHz(QString);

	void setAmpMaxMinValueZero(float fmax,float fmin);

	int m_moudleChannelNum;
	float m_fAmpMaxZero,m_fAmpMinZero;	//零序电压/电流量程
};

#endif // CHANNELLOWSTABLE_H
