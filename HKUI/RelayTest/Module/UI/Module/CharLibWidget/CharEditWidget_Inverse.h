#ifndef CharEditWidget_Inverse_H
#define CharEditWidget_Inverse_H

#include <QWidget>
#include "ui_CharEditWidget_Inverse.h"
#include "CharEditWidgetBase.h"
#include "../../../../../AutoTest/Module/Characteristic/CharElementInverse.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"

#include <QRadioButton>
#define CharInverse_ID_CurrentChangeStart              _T("CurrentChangeStart")//电流变化始值
#define CharInverse_ID_CurrentChangeFinal              _T("CurrentChangeFinal")//电流变化终值
#define CharInverse_ID_CurrentChangeStep              _T("CurrentChangeStep")//电流变化步长

class QCharEditWidget_Inverse : public QWidget, public QCharEditWidgetBase
{
	Q_OBJECT

public:
	QCharEditWidget_Inverse(QWidget *parent = 0);
	~QCharEditWidget_Inverse();

private:
	Ui::QCharEditWidget_Inverse ui;
	CCharElementInverse* m_pCharElementInverse;

	bool m_bCheckBox1;
	bool m_bCheckBox2;
	bool m_bCheckBox3;

	QList<QLineEdit*> m_editList;
	QList<QLabel*>    m_labelList;
	QRadioButton *m_pLowVolModeRadio;//低压模式
	QRadioButton *m_pOverVolModeRadio;//过压模式

public:
	void InitData();
	void InitGroup();
        void InitLanguage();

	void UpdateGroup();
	void InitConnect();
	void disConnectAll();
	void InitChar();
	void UpdateImage();

	void initMaxPositiveEdit(QLineEdit *lne);
	void setPara(QLineEdit *pEdit, CString &strTemp);
	void setPara(QLineEdit *pEdit, float &fTemp);
	void AddLabelToGroup(QString str,int nRow,int nCol);
	void AddEditToGroup(int nRow,int nCol);
	void ModifyCharByCheck();
	virtual void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);
	virtual void OnLeftButtonDown();
	virtual void GroupDatasToChar(CDataGroup *pDatas);
	virtual void UpdateCharacters(BOOL bCharChaged);
	bool IsCurrInverse();
	bool IsVolInverse();
	bool IsUFInverse();
	void UpdateEdit_CurrValueUserPoint();

	void SetInverseFont();

signals:
	void sig_CharChanged(CExBaseObject *,int);

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
	void slot_CurrValue_editingFinished();
	void slot_onlineEdit_Changed();

	void on_btnSelect_clicked();
	void slot_CIAddChar(CCharacteristic *pObj);
	void slot_ElementData_editFinished();

	void slot_btnUserClear(bool bState);
	void slot_btnUserAdd(bool bState);
	void slot_OnVolModeRadioChanged(bool bState);
};


#endif // CharEditWidget_Inverse_H
