#ifndef CHAREDITWIDGET_INVERSE_ENG_H
#define CHAREDITWIDGET_INVERSE_ENG_H

#include <QWidget>
#include "../CharEditWidget_Inverse.h"
#include "CharactEditWidget_Eng.h"
namespace Ui {
class QCharEditWidget_Inverse_Eng;
}

class QCharEditWidget_Inverse_Eng : public QWidget, public QCharEditWidgetBase
{
    Q_OBJECT

public:
    explicit QCharEditWidget_Inverse_Eng(QWidget *parent = 0);
    ~QCharEditWidget_Inverse_Eng();

	CCharacteristics *m_pCharacteristics_Inner;//特性曲线编辑页面参数
private:
    Ui::QCharEditWidget_Inverse_Eng *ui;
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
	void UpDataParas();
//
	void initMaxPositiveEdit(QLineEdit *lne);
	void setPara(QLineEdit *pEdit, CString &strTemp);
	//void setPara(QLineEdit *pEdit, float &fTemp);
	void AddLabelToGroup(QString str,int nRow,int nCol);
	void AddEditToGroup(int nRow,int nCol);
	void ModifyCharByCheck();
	virtual void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);
//	virtual void OnLeftButtonDown();
	virtual void GroupDatasToChar(CDataGroup *pDatas);
	virtual void UpdateCharacters(BOOL bCharChaged);
	bool IsCurrInverse();
	bool IsVolInverse();
	bool IsUFInverse();
	//void UpdateEdit_CurrValueUserPoint();

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
//	void slot_CurrValue_editingFinished();
	void slot_onlineEdit_Changed();

	void on_btnSelect_clicked();
	void slot_CIAddChar(CCharacteristic *pObj);
	void slot_ElementData_editFinished();
//
//	void slot_btnUserClear(bool bState);
//	void slot_btnUserAdd(bool bState);
	void slot_OnVolModeRadioChanged(bool bState);
};

#endif // CHAREDITWIDGET_INVERSE_ENG_H
