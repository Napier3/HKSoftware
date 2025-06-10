#ifndef QSttFAParasSetDialog_H
#define QSttFAParasSetDialog_H

#include "ui_QSttFAParasSetDialog.h"
#include <QWidget>
#include "../../../SttTest/Common/FAParasSet/tmt_fa_Paras_set.h"
#include "../../../SttTest/Common/tmt_test_paras_head.h"
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include <QMap>


namespace Ui{
	class QSttFAParasSetDialog;
}

class QSttFAParasSetDialog : public QWidget
{
	Q_OBJECT

public:
	Ui::QSttFAParasSetDialog *ui;

	QSttFAParasSetDialog(QWidget *parent = NULL);
	virtual ~QSttFAParasSetDialog();
	void InitUI();
	void SetData(tmt_FaParasSet *pFaParaSet);
	void SetFAParasFont();
	void InitConnections();
	void InitItemOutput();
	void InitItemSignal();
	QMap<int, QString> m_pOutputItem;
	QMap<int, QString> m_pSignalItem;
	void InsertItemOutput(int index, QComboBox *pCombox);
	void InsertItemSignal(int index, QComboBox *pCombox);
	void Update_Edit_Unit();

	tmt_FaParasSet *m_pFaParaSet;
	tmt_FaParasSetTest* m_oTmtFaParasSet;

public slots:
	void slot_m_editRatedVol();
	void slot_m_editResidualVol();
	void slot_m_editRatedCur();
	void slot_m_editFaultCur();
	void slot_m_editFailureCur();
	void slot_m_editErrorTime();
	void slot_m_editxTime();
	void slot_m_edityTime();
	void slot_m_editzTime();
	void slot_m_editxlTime();
	void slot_m_editsTime();

	void slot_TermVolIndexChanged(int index);
	void slot_TermCloseOutputIndexChanged(int index); 
	void slot_TermOpenOutputIndexChanged(int index); 
	void slot_TermCloseSignalIndexChanged(int index);
	void slot_TermQuantileSignalIndexChanged(int index);
};

#endif
