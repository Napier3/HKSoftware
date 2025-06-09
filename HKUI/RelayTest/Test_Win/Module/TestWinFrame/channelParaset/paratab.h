#ifndef PARATABOFSTATUS_H
#define PARATABOFSTATUS_H

#include <QWidget>
#include <QTabWidget>
#include "QParaSetBase.h"

class ParaTab : public QWidget
{
	Q_OBJECT

public:
	ParaTab(QWidget *parent = 0);
	~ParaTab();

	void initUI();
	void setEnabled();

	QTabWidget* getTabWidget(){	return m_tabWidget; }
	QParaSetBase* getActiveParaSet();
	QParaSetBase* getAnaParaSet();
	QParaSetBase* getDigParaSet();
	QParaSetBase* getLowSParaSet();

private:
	QVBoxLayout* m_pVBoxLayout;
	QTabWidget* m_tabWidget;
	QParaSetBase* m_AnaParaWidget;
	QParaSetBase* m_DigParaWidget;
	QParaSetBase* m_LowSParaWidget;

signals:
	void sig_TabPageChanged(int);

public slots:
	void slot_TabPageChanged(int index);
};

#endif // PARATABOFSTATUS_H
