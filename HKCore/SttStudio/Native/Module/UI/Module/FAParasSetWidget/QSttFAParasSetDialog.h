#ifndef QSttFAParasSetDialog_H
#define QSttFAParasSetDialog_H
#include <QDialog>
#include "QSttFAParasSetWidget.h"

class QSttFAParasSetDialog : public QDialog
{
	Q_OBJECT

public:
	QSttFAParasSetDialog(QWidget *parent = 0);
	~QSttFAParasSetDialog();

	void InitUI();
	BOOL OpenFAParasFile(const CString& strParasFile);

protected:
	QSttFAParasSetWidget *m_pSttFAParasSetWidget;
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;
	CDataGroup m_pFAParasData;
	CDataGroup *m_pFAParasCopyData;

signals:
	void sig_UpdatepFAParasData(CDataGroup *);

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
};

#endif 