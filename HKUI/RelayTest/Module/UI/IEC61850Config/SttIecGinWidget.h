/************************************************************************/
/* GOOSE订阅页面                                                                     */
/************************************************************************/
#ifndef STTIECGINWIDGET_H
#define STTIECGINWIDGET_H

#include "SttIecConfigWidgetBase.h"
#include "SttIecConfigGlobalDef.h"
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../Module/CommonCtrl_QT/QNumberCheckBox.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGinDatas.h"
#include "Grid/IecCfgGinDataGrid.h"


class QSttIecGinWidget : public QSttIecConfigWidgetBase, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecGinWidget(QFont oIecFont,QWidget *parent=NULL);
	~QSttIecGinWidget();

	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void SaveData();
	virtual void UpdateAppMaps();
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGINDATA;   }
protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
signals:

protected slots:
};

extern CFont *g_pSttGlobalFont;  

#endif // STTIECGINWIDGET_H
