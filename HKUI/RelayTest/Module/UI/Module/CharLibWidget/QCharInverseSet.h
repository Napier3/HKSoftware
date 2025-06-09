#ifndef CHARINVERSESET_H
#define CHARINVERSESET_H

#include <QWidget>
#include <QLabel>
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"

namespace Ui {
class QCharInverseSet;
}

class QCharInverseSet : public QWidget
{
	Q_OBJECT

public:
    QCharInverseSet(CCharElement *pCharElement, QWidget *parent = 0);
    ~QCharInverseSet();

    Ui::QCharInverseSet *ui;

	void InitData();
	void InitConnect();
	void InitGroup();
        void InitLanguage();
	void UpdateGroup();

	void initMaxPositiveEdit(QLineEdit *lne);
	void setPara(QLineEdit *A, CString &strTemp);
	void setPara(QLineEdit *A, float &fTemp);
	void AddLabelToGroup(QString str,int nRow,int nCol);
	void AddEditToGroup(int nRow,int nCol);
	void ModifyCharByCheck();

signals:
	void sig_CharChanged();
// 	void sig_UpdataCheck(bool, bool, bool);

protected slots:
	void slot_oncheckBox_Set1_toggled(bool b);
	void slot_oncheckBox_Set2_toggled(bool b);
	void slot_oncheckBox_Set3_toggled(bool b);

	void slot_onlineEdit_VSet1_editFinished();
	void slot_onlineEdit_VSet2_editFinished();
	void slot_onlineEdit_VSet3_editFinished();
	void slot_onlineEdit_TSet1_editFinished();
	void slot_onlineEdit_TSet2_editFinished();
	void slot_onlineEdit_TSet3_editFinished();

	void slot_ElementData_editFinished();
	void slot_PbnOkClicked();
	void slot_PbnCancelClicked();

private:
	CCharElement *m_pCurCharElement;
	CCharElementInverse *m_pCharElementInverse;

	bool m_bCheckBox1;
	bool m_bCheckBox2;
	bool m_bCheckBox3;

	QList<QLineEdit*> m_editList;
	QList<QLabel*>    m_labelList;

public:
	int m_nIsOK;

};

#endif // CHARINVERSESET_H
