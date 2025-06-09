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
#include "../SysParasSetDlg/QFloatLineEdit.h"
#include "../CommonCtrl_QT/QNumberCheckBox.h"
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

	QPushButton *m_pClear_PushButton;//2023-12-18 suyang 清除绑定按钮

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
signals:

protected slots:
	void slot_ClearClicked();
};

#endif // STTIECGINWIDGET_H
