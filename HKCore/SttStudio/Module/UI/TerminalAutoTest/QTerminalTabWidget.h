#ifndef QTERMINALTABWIDGET_H
#define QTERMINALTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "Grid/QTerminalGooseGrid.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgChsBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGoutChs.h"
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGinChs.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGinDatas.h"

#define MU_TAB_TYPE_GOOSETOBIN		    0//GOOSE转开入
#define MU_TAB_TYPE_BOUTTOGOOSE	        1//开出转GOOSE
#define MU_TAB_TYPE_SOE	                2//SOE测试

class QTerminalTabWidget : public QWidget
{
	Q_OBJECT
public:
	QTerminalTabWidget(QWidget *parent = 0);
	~QTerminalTabWidget();

public:
	void InitUI();
	void StartInit();
	void StopInit();

public slots:
	void InitGoutData(CExBaseObject *pData);
	void InitGinData(CExBaseObject *pData);


public:
	QTabWidget *m_pTabWidget;
	QTerminalGooseGrid *m_MuGooseBinGrid;
	QTerminalGooseGrid *m_MuBoutGooseGrid;
	
	CExBaseList m_oGooseBinList;
	CExBaseList m_oBoutGooseList;
	long m_nBoutIndex,m_nBinIndex ;

	CExBaseList m_oSOEGooseBinList;
	CExBaseList m_oSOEBoutGooseList;

	QWidget *m_MuSoeWidget;
	QTerminalGooseGrid *m_SOEGooseBinGrid;
	QTerminalGooseGrid *m_SOEBoutGooseGrid;
};


#endif

