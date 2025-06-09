/************************************************************************/
/* SMV92页面                                                                     */
/************************************************************************/
#ifndef STTIECSMV92WIDGET_H
#define STTIECSMV92WIDGET_H

#include "SttIecConfigWidgetBase.h"
#include "SttIecConfigGlobalDef.h"
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"
#include "../Module/CommonCtrl_QT/QNumberCheckBox.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"
#include "Grid/IecCfgSmvData92Grid.h"

#define STT_IEC_SMV92_ASDU_MAX_NUM                    9

class QSttIecSMV92Widget : public QSttIecConfigWidgetBase, public CIecConfigInterface
{
	Q_OBJECT

public:
	QSttIecSMV92Widget(QFont oIecFont,QWidget *parent=NULL);
	~QSttIecSMV92Widget();

	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void SaveData();

	void GetOptSelectState(int &nSelDataset,int &nSelSecurity,int &nSelSmpRate,int &nSelRefrTm);
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG92DATA;   }
protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	virtual void InitUI();

	void CreateToolbar();
	void SetIecSMV92Font();

	QFloatLineEdit *m_pSmpRateLineEdit;
	QComboBox *m_pASDUComboBox;
	QNumberCheckBox *m_pDataSetCheckBox;
	QNumberCheckBox *m_pSecurityCheckBox;
	QNumberCheckBox *m_pSmpRateCheckBox;
	QNumberCheckBox *m_pRefrTmCheckBox;
	QPushButton *m_pSMV92OtherSetButton;
	QHBoxLayout *m_pSMV92FirstHLayout;
	QLabel *m_pLabel;
	QLabel *m_Asdu_Label;

signals:

protected slots:
	void slot_SMV92OtherSetClicked();
	void slot_lne_SmpRateEditClicked();
	void slot_lne_SmpRateEdit_editingFinished();
};

extern QFont *g_pSttGlobalFont;  

#endif // GSEPubDIALOG_H
