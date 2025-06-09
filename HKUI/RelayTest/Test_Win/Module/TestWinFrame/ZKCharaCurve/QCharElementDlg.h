#ifndef QCHARELEMENTDLG_H
#define QCHARELEMENTDLG_H

#include <QObject>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../Module/TestWinFrame/testwinbase.h"

class QCharElementDlg : public QDialog
{
	Q_OBJECT

public:
	QCharElementDlg(CCharElement *pCharElement, QWidget *parent);
	~QCharElementDlg();

	void InitTopUI();
	void InitParaUI(int nType);
	void InitButton();
	void SetParaData();
	void CreateNewElement();

	int GetElementType();
	void AddLabelToList(QString str,int nRow,int nCol);
	void AddEditToList(int nRow,int nCol);
	void SetComboIndex(int nIndex, QString strText);
	CCharElement* GetNewElement(){	return m_pNewCharElement;	}

private slots:
	void slot_ElementTypeChanged(int);
	void slot_PbnOkClicked();
	void slot_PbnCancelClicked();

public:
	int m_nIsOK;

private:
	CCharElement *m_pCurCharElement;
	CCharElement *m_pNewCharElement;

private:
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;
	QComboBox *m_cmbElementType;
	QLineEdit *m_editErrorLen;
	QLineEdit *m_editTestPoint;
	QLabel *m_labelElementType;
	QLabel *m_labelErrorLen;
	QLabel *m_labelTestPoint;

	QList<QLineEdit*> m_editList;
	QList<QComboBox*> m_cmbList;
	QList<QLabel*>    m_labelList;
	
	QStringList m_strlistEleType;
	QStringList m_strlistDir;
	QStringList m_strlistClockDir;

	QVBoxLayout *m_MainLayout;
	QGridLayout *m_TopLayout;
	QGridLayout *m_ParaLayout;
	QHBoxLayout *m_BottomLayout;
	
};

#endif // QCHARELEMENTDLG_H
