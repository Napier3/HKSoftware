#ifndef _QSttReplayDigitalModuleWidget_H
#define _QSttReplayDigitalModuleWidget_H

#include <QWidget>
#include <QTabWidget>
#include <QList>
#include <QMap>

#include "SttReplayModuleChWidget.h"

class QSttReplayDigitalModuleWidget: public QWidget
{
	Q_OBJECT

public:
	QSttReplayDigitalModuleWidget(int nModuleIndex,CSttModuleComtradeBind *pChMapConfig,QWidget *parent = 0);
	~QSttReplayDigitalModuleWidget();


	virtual void startInit();
	virtual void stopInit();
// 	virtual void setData(PTMT_PARAS_HEAD pCurr);

	void CreateModules( CSttModuleComtradeBind* m_pModuleInfo, int nGroupSize );
	void CreatModuleChWidget();
	void InitDigitalModuleChList(const QStringList &oUChList,const QStringList &oIChList);
	void setEnableStateUI(bool bEnable);
	void InitDigitalWidget();

	CSttReplayModuleChWidget * GetDigitalModuleChWidget(int nIndex);
	int GetDigitalModuleChWidgetCount();
	void UpdateABChSel();
	void UpdateTwoCursorTimeValues(double dValueA,double dValueB);

	void UpdateUIMax();
	void UpdateUIMax( double fUMax,double fIMax );
	int GetIndexByID(CString ChStrID);//通过ID获取通道序号
	QWidget* GetParaSetWidget();

	void SetChSelectList(const QStringList &oUChList,const QStringList &oIChList);
	void clearTab();


private:
	void initUI();
	void initData(CSttModuleComtradeBind *pChMapConfig);
	void initSignalSlots();
	void uninitSignalSlots();
	virtual void resizeEvent(QResizeEvent* event); 


private:
	CSttModuleComtradeBind *m_pModuleInfo;
	QTabWidget *m_pTab;

	QList<CSttReplayModuleChWidget *> m_oModuleChWidgetList;
	QMap<int,CSttModuleComtradeBind *>m_oDigitaModuleMap;

	int m_nModuleIndex;//G1对应模块序号
	QWidget *m_pParentWidget;

// SIGNAL:
// 	void sig_DigitaModuleChChanged(int nModuleIndex,int nChIndex);

public slots:
	void slot_TabChanged(QWidget *pCurWidget);

	

};
#endif