/************************************************************************/
/* GOOSE发布页面                                                                     */
/************************************************************************/
#ifndef STTIECGOUTWIDGET_H
#define STTIECGOUTWIDGET_H

#include "SttIecConfigWidgetBase.h"
#include "SttIecConfigGlobalDef.h"
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "../Module/CommonCtrl_QT/QIecLineEdit.h"
#include "../Module/CommonCtrl_QT/QLongLineEdit.h"
#include "../Module/CommonCtrl_QT/QNumberCheckBox.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGoutDatas.h"
#include "Grid/IecCfgGoutDataGrid.h"


class QSttIecGoutWidget : public QSttIecConfigWidgetBase, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecGoutWidget(QFont oIecFont,QWidget *parent=NULL);
	~QSttIecGoutWidget();

	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void SaveData();
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGGOUTCH;   }

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
	void initConnect();
	void SetIecGoutFont();

	QLongLineEdit *m_pT1_LineEdit;
	QLongLineEdit *m_pT0_LineEdit;
	QIecLineEdit  *m_pTimeQuality_LineEdit;
	QLongLineEdit *m_pGroupDelay_LineEdit;
	QHBoxLayout   *m_pGoutFirstHLayout;
	QLabel        *m_pGroupDelay_Label;
	QLabel        *m_pT1Times_Label;
	QLabel        *m_pT0Times_Label;
	QLabel        *m_pTimeQuality_Label;

signals:

protected slots:
	void slot_lne_T1EditClicked();
	void slot_lne_T0EditClicked();
	void slot_lne_TimeQualityEditClicked();
	void slot_lne_GroupDelayEditClicked();

	void slot_lne_T1Edit_editingFinished();
	void slot_lne_T0Edit_editingFinished();
	void slot_lne_GroupDelayEdit_editingFinished();
};

extern QFont *g_pSttGlobalFont;  

#endif // STTIECGOUTWIDGET_H
