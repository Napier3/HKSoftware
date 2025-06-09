/************************************************************************/
/* SMV92订阅页面                                                                     */
/************************************************************************/
#ifndef STTIECSMV92INWIDGET_H
#define STTIECSMV92INWIDGET_H

#include "SttIecConfigWidgetBase.h"
#include "SttIecConfigGlobalDef.h"
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../Module/CommonCtrl_QT/QNumberCheckBox.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvInDatas.h"
#include "Grid/IecCfgSmvData92InGrid.h"

class QSttIecSMV92InWidget : public QSttIecConfigWidgetBase, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecSMV92InWidget(QFont oIecFont,QWidget *parent=NULL);
	~QSttIecSMV92InWidget();

	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void SaveData();
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92INPUTDATA;   }
protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
	void SetIecSMV92InFont();

	QFloatLineEdit *m_pSmpRateLineEdit;
	QPushButton *m_pSMV92OtherSetButton;
	QHBoxLayout *m_pSMV92FirstHLayout;
	QLabel *m_pLabel;

signals:

protected slots:
	void slot_SMV92OtherSetClicked();
	void slot_lne_SmpRateEditClicked();
	void slot_lne_SmpRateEdit_editingFinished();
};

extern CFont *g_pSttGlobalFont;  

#endif // STTIECSMV92INWIDGET_H
