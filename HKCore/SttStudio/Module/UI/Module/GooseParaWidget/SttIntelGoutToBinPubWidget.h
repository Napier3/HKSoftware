#ifndef QSTTINTELGOUTTOBINPUBWIDGET_H
#define QSTTINTELGOUTTOBINPUBWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include "../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"
#include "SttIntelGoutToBinGrid.h"

class QSttIntelGoutToBinParaWidget;
class QSttIntelGoutToBinPubWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIntelGoutToBinPubWidget(QSttIntelGoutToBinParaWidget *pParaWidget,QWidget *parent = 0);
	~QSttIntelGoutToBinPubWidget();

	void initUI();
	void initData(CIecCfgGoutData *pCfgGoutData,bool bInitEditable=TRUE);
	void SetRunState(int nRunState);
	void EnableInverseCol(BOOL bEnable);
	void SetTestCheckBox_Visible(BOOL bVisible);//设置检修状态勾选框是否可见
	void GridCellResultVlaues(float ResultTimeVlaue,char RowIndex);
	void setGooseResultVlaues();
	void SetGoosePubFont();
    void startInit();

	QSttIntelGoutToBinParaWidget* m_pParent;
	CSttIntelGoutToBinGrid *m_pSttIntelGoutToBinGrid;

	QLabel *label_IEDName;
	QLineEdit *lne_IEDName;
	QLabel *label_APPID;
	QLineEdit *lne_APPID;
	QCheckBox *chb_Repair;
	QPushButton *pbn_Revert;

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();
	void sig_GoutMapChanged();//GOOOSE开出通道映射或者数据类型改变
	void sig_RevertData();
	void sig_GoutRowIndex(int nRowIndex);

private slots:
	void slot_chb_RepairStateChanged(int);
	void slot_pbn_RevertClicked();
	void slot_dataChanged();
	void slot_GoutMapChanged();
	void slot_GoutRowIndex(int nRowIndex);

private:
	bool m_bAll;
	CIecCfgGoutData *m_pCfgGoutData;
};

#endif // QSTTINTELGOUTTOBINPUBWIDGET_H
