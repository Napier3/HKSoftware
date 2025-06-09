#ifndef LINEVOLTWIDGET_H
#define LINEVOLTWIDGET_H

#include <QWidget>
#include "ui_linevoltwidget.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

class LineVoltWidget : public QWidget, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	LineVoltWidget(QWidget *parent = 0);
	~LineVoltWidget();

	BOOL m_bDC;
	tmt_channel* m_uiVOL;
	tmt_channel* m_uiCUR;

	CExBaseList* m_pVolChList;
	CExBaseList* m_pCurChList; 

	CSttTestResourceBase *m_pSttTestResource;

	QTabWidget *m_tabWidget;

	void InitUI();

	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR);
	void getGroupPosRange(int nGroup, int& nStart, int& nEnd);

	void setDCChanged(bool bDC);
	void updateData();

	void UpdateGroupText();
	QString GetULineVoltName(CSttMacroChannel*pChannelA, CSttMacroChannel*pChannelB);

	virtual void OnRtDataChanged();

public slots:
	void slot_PbnNextClicked();
	void slot_PbnPreClicked();

private:
	Ui::linevoltwidget ui;

	int m_nRowNum;
	QStringList m_headerList;

	int m_AllGroup;
	int m_nCurrentGroup; //当前组号
};

#endif // LINEVOLTWIDGET_H
