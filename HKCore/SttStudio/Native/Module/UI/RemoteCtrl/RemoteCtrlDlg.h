#ifndef  QRemoteCtrlDlg_H
#define  QRemoteCtrlDlg_H
 
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "SttMacroParaEditViewRemoteCtrl.h"

class QRemoteCtrlDlg : public QDialog
{
	Q_OBJECT

public:
	QRemoteCtrlDlg(QSttMacroParaEditViewRemoteCtrl *pSttMacroParaEditViewRemoteCtrl,QWidget *parent = 0);
	~QRemoteCtrlDlg();

	void InitUI();
	void SetDialogFont();

	QVBoxLayout *m_pMainLayout;  
	QSttMacroParaEditViewRemoteCtrl *m_pSttMacroParaEditViewRemoteCtrl;
	QPushButton *m_pOK_PushButton; 
	QPushButton *m_pCancel_PushButton;   

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();

};

#endif 
