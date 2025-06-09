#ifndef GRADIENTPARATAB_H
#define GRADIENTPARATAB_H

#include <QWidget>
#include <QTabWidget>
#include "gradientparaset.h"
#include "../../../../../Module/OSInterface/OSInterface.h"

class GradientParaTab : public QWidget
{
	Q_OBJECT

public:
	GradientParaTab(QWidget *parent = 0);
	~GradientParaTab();

	QTabWidget* m_tabWidget;

	void initUI();
	
	QTabWidget* getTabWidget(){	return m_tabWidget; }
	GradientParaSet* getAmpParaSet();
	GradientParaSet* getFreqParaSet();

	void setData(CSttTestResourceBase *pSttTestResource,tmt_StatePara* pStatePara);
	void saveData();
	void updateGradientType(int nType);
	void InitLinearStepGradient();
private:
	QVBoxLayout* m_pVBoxLayout;

	GradientParaSet* m_AmpParaWidget;
	GradientParaSet* m_FreqParaWidget;

signals:
	void sig_TabPageChanged(int);

public slots:
	void slot_TabPageChanged(int index);
};

extern CFont *g_pSttGlobalFont;  

#endif // GRADIENTPARATAB_H
