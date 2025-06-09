#ifndef STATEPARATAB_H
#define STATEPARATAB_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include "../Module/ChannelParaset/QBasicTestParaSet.h"
#include "../Module/ExSwitchSet/exswitchset.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
//#include "StateParaWidget.h"
#include "GooseAbnormal/GooseAbnormalParaset.h"
#include "SmvAbnormal/SmvAbnormalParaset.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
class QStateParaTab : public QWidget
{
	Q_OBJECT

public:
	QStateParaTab(BOOL *pbTmtParaChanged, QWidget *parent = 0);
	~QStateParaTab();

	void initUI();

	void AddHarmParaset();
	void RemoveHarmParaset();

	void AddExBinParaWidget();
	void RemoveExBinParaWidget();

	void AddExBoutParaWidget();
	void RemoveExBoutParaWidget();

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();
	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget();

	bool ExistHarmParaset();
	bool ExistExBinParaWidget();
	bool ExistExBoutParaWidget();
	bool ExistGooseParaWidget();
	bool ExistFT3OutParaWidget();

	void EnableBinParaWidget(bool b);
	void EnableBoutParaWidget(bool b);
	void EnableGooseParaWidget(bool b);
	void EnableFT3OutParaWidget(bool b);

	virtual void startInit();
	virtual void stopInit();
	void EnableSubParaWidget(bool bEnable);
public:
	QTabWidget* m_tabWidget;
	QBasicTestParaSet* m_pUIParaWidget;		//电压电流设置
	//QStateParaWidget* m_pStateParaWidget;	//状态参数设置
	QBasicTestParaSet* m_pHarmParaWidget;	//谐波设置
	ExSwitchSet* m_pExBinParaWidget;		//扩展开入设置
	ExSwitchSet* m_pExBoutParaWidget;		//扩展开出设置
	QGooseParaWidget* m_pGooseParaWidget;	//GOOSE数据发送
	QFT3OutParaWidget* m_pFT3OutParaWidget;
	QGooseAbnormalParaSet* m_pGooseAbnParaWidget;
	QSmvAbnormalParaset* m_pSVParaSet;		//SV异常模拟页面

signals:
	void sig_TabPageChanged(int);

public slots:
	void slot_TabPageChanged(int index);

private:
	BOOL *m_pbTmtParaChanged;
};
extern CFont *g_pSttGlobalFont;  
#endif // STATEPARATAB_H
