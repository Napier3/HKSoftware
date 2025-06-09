#ifndef SEQWIDGET_H
#define SEQWIDGET_H

#include <QWidget>
#include "ui_seqwidget.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

class SeqWidget : public QWidget, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	SeqWidget(QWidget *parent = 0);
	~SeqWidget();
	void languageProcessing();
	BOOL m_bDC;
	tmt_channel* m_uiVOL;
	tmt_channel* m_uiCUR;

	CExBaseList* m_pVolChList;//全部电压通道资源索引
	CExBaseList* m_pCurChList; //全部电流通道资源索引

	CSttTestResourceBase *m_pSttTestResource;

	QTabWidget *m_tabWidget;

	void InitUI();

	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR);
	void getGroupPosRange(int nModuleType, int nGroup, int& nStart, int& nEnd);

	void setDCChanged(bool bDC);
	void updateData();

	void UpdateGroupText();
	virtual void OnRtDataChanged();

public slots:
	void slot_PbnNextClicked();
	void slot_PbnPreClicked();

private:
 	Ui::seqwidget ui;

	int m_nRowNum;
	QStringList m_headerList;

	int m_AllGroup;
	int m_NeedUGroup;
	int m_NeedIGroup;
	int m_nCurrentGroup; //当前组号
};

#endif // SEQWIDGET_H
