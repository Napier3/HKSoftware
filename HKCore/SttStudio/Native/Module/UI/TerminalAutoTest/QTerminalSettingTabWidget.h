#ifndef QSETTINGTABWIDGET_H
#define QSETTINGTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QDialog>

#include "Grid/QTerminalGinDataChsGrid.h"
#include "Grid/QTerminalGoutDataChsGrid.h"

#include "Grid/QTerminalGinDataGrid.h"
#include "Grid/QTerminalGoutDataGrid.h"

#define SET_TAB_TYPE_GOOSETOBIN		        0//GOOSE转开入
#define SET_TAB_TYPE_BOUTTOGOOSE	        1//开出转GOOSE


class QTerminalSettingTabWidget : public QDialog
{
	Q_OBJECT
public:
	QTerminalSettingTabWidget(QWidget *parent = 0);
	~QTerminalSettingTabWidget();

public:
	void InitUI();
	void InitConnection();
	void InitBinGooseData();
	void InitBoutGooseData();
	void SaveXmlParas();
	
public slots:
	void slot_TabPageChanged(int nIndex);
	void slot_BtnOK();
	void slot_BtnCancle();
	void UpdateGoutChans(CIecCfgChsBase *pIecCfgChs);
	void UpdateGinChans(CIecCfgChsBase *pIecCfgChs);
	void SaveGoutMapValue();
	void SaveGinMapValue();
	void SaveMapValue(CIecCfgChsBase *pIecCfgChsBase,CString str1,CString str2,CString srtSOE);

signals:
	void sig_UpdateChansdata(CIecCfgChsBase *);

public:
	QTabWidget *m_pTabWidget;

	QWidget *m_pMuGooseGinWidget;
	QWidget *m_pMuGooseGoutWidget;

	QTerminalGoutDataGrid *m_pIecCfgGoutDataGrid;
	QTerminalGinDataGrid *m_pIecCfgGinDataGrid;

	QTerminalGinDataChsGrid *m_pIecCfgGinChannelsGrid;
	QTerminalGoutDataChsGrid *m_pIecCfgGoutChannelsGrid;

	QPushButton *m_pBtnCancle;
	QPushButton *m_pBtnOK;
	QPushButton *m_pBtnOtherSet;

};

#endif