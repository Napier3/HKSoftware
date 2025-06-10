#ifndef GOOSEPUBWIDGET_H
#define GOOSEPUBWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include "../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"
#include "IecCfgGoutChsGrid.h"

class QGooseParaWidget;
class GoosePubWidget : public QWidget
{
	Q_OBJECT

public:
	GoosePubWidget(QGooseParaWidget *pParaWidget,QWidget *parent = 0);
	~GoosePubWidget();

	void initUI();
	void initData(CIecCfgGoutData *pCfgGoutData,bool bInitEditable=TRUE);
	void SetRunState(int nRunState);
	void EnableInverseCol(BOOL bEnable);
	void SetTestCheckBox_Visible(BOOL bVisible);//设置检修状态勾选框是否可见

	void SetGoosePubFont();

	QGooseParaWidget* m_pParent;
	CIecCfgGoutChsGrid *m_pIecCfgGoutChsGrid;
	QLabel *label_IEDName;
	QLineEdit *lne_IEDName;
	QLabel *label_APPID;
	QLineEdit *lne_APPID;
	QCheckBox *chb_Invert;
	QCheckBox *chb_Repair;

signals:
	void sig_GooseDataChanged();
	void sig_RepairDataChanged();
	void sig_GoutMapChanged();//GOOOSE开出通道映射或者数据类型改变

private slots:
	void slot_chb_InvertStateChanged(int);
	void slot_chb_RepairStateChanged(int);
	void slot_dataChanged();
	void slot_GoutMapChanged();

private:
	bool m_bAll;
	CIecCfgGoutData *m_pCfgGoutData;
};

#endif // GOOSEPUBWIDGET_H
