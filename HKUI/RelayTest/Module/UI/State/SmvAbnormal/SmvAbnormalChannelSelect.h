#ifndef CHANNELSELECT_H
#define CHANNELSELECT_H

#include <QDialog>
#include "ui_SmvAbnormalChannelSelect.h"
#include "SmvAbnormalParaset.h"

class QSmvAbnormalChannelSelect : public QDialog
{
	Q_OBJECT

public:
	QSmvAbnormalChannelSelect(tmt_StateAbnormalSMV *pAbnormalSMV,QWidget *parent = 0);
	~QSmvAbnormalChannelSelect();

signals:
	void sig_ChannelOkClicked(QList<int> &channelnum);

protected slots:
	void slot_pbn_ALlReset();
	void slot_pbn_ALlNoReset();
	void slot_pbn_OK();
	void slot_pbn_Cancle();

private:
	Ui::SmvAbnormalChannelSelect ui;
	void initConnnect();
	void initData();
        void InitLanguage();
	tmt_StateAbnormalSMV *m_pAbnormalSMV;
//	QList<int> m_channelNum;
};

#endif // CHANNELSELECT_H
