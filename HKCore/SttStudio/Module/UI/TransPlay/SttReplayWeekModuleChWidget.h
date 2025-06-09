#ifndef _CSttReplayWeekModuleChWidget_H_
#define _CSttReplayWeekModuleChWidget_H_

#include "SttReplayModuleChWidget.h"
#include <QWidget>

class CSttReplayWeekModuleChWidget : public CSttReplayModuleChWidget
{
	Q_OBJECT

public:
	CSttReplayWeekModuleChWidget(int nModuleIndex,CSttModuleComtradeBind *pModuleInfo,QWidget *pParent = 0);
	~CSttReplayWeekModuleChWidget();

public:
	virtual void SetChSelectList(const QStringList &oUChList,const QStringList &oIChList);
	virtual void setEnableStateUI(bool bEnable);
	virtual void UpdatePT_CT_Rates();
	virtual void initSignalSlots();
	virtual void uninitSignalSlots();

	void SetWeekEeType();//设置弱信号模块电气类型选择

	void UpdateABChSelCmbChange(int nChIndex, int nEleType);

public slots:
	virtual void slot_ChangedPT1();
	virtual void slot_ChangedPT2();
	virtual void slot_ChangedCT1();
	virtual void slot_ChangedCT2();

	void slot_WeekChSelTypeChanged(int nIndex);


private:
	// 	QWidget *m_pParentWidget;
	QStringList m_oUChList;
	QStringList m_oIChList;


};



#endif
