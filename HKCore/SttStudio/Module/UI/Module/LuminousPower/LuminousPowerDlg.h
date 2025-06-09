#ifndef QLUMINOUSPOWERDLG_H
#define QLUMINOUSPOWERDLG_H

#include "LuminousPowerGrid.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/BaseClass/ExBaseList.h"

class QLuminousPowerDlg : public QDialog
{
	Q_OBJECT

public:
	QLuminousPowerDlg(QWidget *parent = 0);
	virtual ~QLuminousPowerDlg();

	void InitData(CDataGroup *pDataGroup);
	void InitUI();
	void InitConnection();
	void UpdateStatusPic(QLuminousPowerGrid* pGrid,CExBaseList *pList);
    void UpdateData();

	QVBoxLayout* m_pMainLayout;
	QHBoxLayout *m_pCloseLayout;
	QPushButton *m_pbtnClose;
	QLuminousPowerGrid *m_pEvenLuminousPowerGrid;//Å¼Êý
	QLuminousPowerGrid *m_pOddLuminousPowerGrid;//ÆæÊý

	CExBaseList m_oEvenLuminousPowerList;
	CExBaseList m_oOddLuminousPowerList;

	long m_nTimerID;
	CDataGroup *m_pFiberGroup;
	BOOL m_bHasClosed;

public slots:
	void slot_CloseClicked();

protected:
	virtual void timerEvent(QTimerEvent * );
};

#endif