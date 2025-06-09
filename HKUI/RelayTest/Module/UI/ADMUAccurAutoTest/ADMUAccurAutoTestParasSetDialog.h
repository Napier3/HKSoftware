#ifndef ADMUACCURAUTOTESTPARASSETDIALOG_H
#define ADMUACCURAUTOTESTPARASSETDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include "../../../../Module/OSInterface/QT/CString_QT.h"

class QAdmuAccurAutoTestParasSetDialog : public QDialog
{
	Q_OBJECT

public:
	explicit QAdmuAccurAutoTestParasSetDialog(QWidget *parent = 0);
	virtual ~QAdmuAccurAutoTestParasSetDialog();

	void InitUI();
	void InitConnect();
	void GetLineEditValue(QLineEdit * pLineEdit,CString strID);

private:
	QPushButton *m_pOkBtn;
	QPushButton *m_pCancelBtn;
	QMap<QString, float> m_TempData;

protected slots:
	void slot_OkClicked();
	void slot_CancelClicked();
	void slot_LineEditFinished();

};
#endif
