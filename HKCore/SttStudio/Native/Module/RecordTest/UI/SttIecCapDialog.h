#ifndef STTIECCAPDIALOG_H
#define STTIECCAPDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SttIecRecordMainWidget.h"
#include "../../UI/Controls/SttOutPutWidget.h"

class QSttIecCapDialog : public QDialog
{
	Q_OBJECT

public:
	QSttIecCapDialog(QWidget *parent);
	virtual ~QSttIecCapDialog();

	void InitUI();
	void StartDetect(bool bStartDetect);
	QSttOutPutWidget *m_pSttOutPutWidget;

private:
	QSttIecRecordMainWidget *m_pSttIecRecordMainWidget;
	QVBoxLayout *m_pMainVLayout;
	QPushButton *m_pOK_PushButton;
	QHBoxLayout *m_pOK_CancelHLayout;

public slots:
	void slot_OKClicked();
	
};

#endif // STTIECCAPDIALOG_H
