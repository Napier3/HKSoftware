#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include "ui_powerwidget.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

class PowerWidget : public QWidget, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	PowerWidget(QWidget *parent = 0);
	~PowerWidget();

	BOOL m_bDC;
	tmt_channel* m_uiVOL;
	tmt_channel* m_uiCUR;
	
	CExBaseList* m_pVolChList;
	CExBaseList* m_pCurChList;

	QTabWidget *m_tabWidget;

	void InitUI();
	void InitLanguage();
	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR);
	void getGroupPosRange(int nGroup, int& nStart, int& nEnd);

	void setDCChanged(bool bDC);
	void updateData();

	void UpdateGroupText();
	virtual void OnRtDataChanged();

public slots:
	void slot_PbnNextClicked();
	void slot_PbnPreClicked();

private:
	Ui::powerwidget ui;
	CSttTestResourceBase *m_pSttTestResource;

	int m_nRowNum;
	QStringList m_headerList;

	int m_AllGroup;
	int m_NeedUGroup;
	int m_NeedIGroup;
	int m_nCurrentGroup; //当前组号
};

#endif // POWERWIDGET_H
