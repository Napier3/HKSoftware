#ifndef QSynAddMultQuickDlg_H
#define QSynAddMultQuickDlg_H

#include <QDialog>
#include <QObject>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../UI/Controls/SttLineEdit.h"
#include "../../UI/Controls/SttCheckBox.h"

namespace Ui {
	class QSynAddMultQuickDlg;
}


class QSynAddMultQuickDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QSynAddMultQuickDlg(QWidget *parent = 0);
	
	CDataGroup *m_pDataGroup;//当前页面参数

	void SetParasFont();
	void initConnections();
	void initData();
	void InitUI();

	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);
	void SetValueToPage(CDvmData *pData);
	void GetPageToValue(CDvmData *pData);

	void CheckAllPresence();
	void CheckForPresence(CString strID);


private:
	Ui::QSynAddMultQuickDlg *ui;
	void InitLanuage();

private slots:
	float slot_lne_Changed(QLineEdit* pLineEdit);
	void slot_lneUPlus_editingFinished();
	void slot_lneUMinus_editingFinished();
	void slot_lneFPlus_editingFinished();
	void slot_lneFMinus_editingFinished();

	void slot_pbn_OKClick();
	void slot_pbn_CancelClick();
};

#endif //QSynAddMultQuickDlg_H
