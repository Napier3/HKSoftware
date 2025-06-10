#ifndef QMODULESETWIDGET_H
#define QMODULESETWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "../CommonCtrl_QT/QFloatLineEdit.h"

#include "../Module/SttTest/Common/tmt_system_config.h"

#include "../../Controls/SttCheckBox.h"
#include "../../Controls/SttGroupBox.h"

class QModuleSetWidget : public QWidget
{
	Q_OBJECT

public:
	QModuleSetWidget(QWidget *parent = 0);
	~QModuleSetWidget();

	void initUI(STT_SystemParas *pSysParas);
	void ReleaseUI();
	void InitDatas();//��ϵͳ�����г�ʼ������ѡ��
	void SaveDatas();//������������浽ϵͳ������
	void SetModuleFont();

protected:
	void UpdateCurSelModuleUI();//���µ�ǰѡ���ģ��Ľ����߼�

	QVBoxLayout *m_pModuleSet_VBoxLayout;

//	QGroupBox *m_pStdValues_GroupBox;//�ֵGroup
//	QGridLayout *m_pStdValues_GridLayout;

//	QLabel *m_pStdVol_Label;
//	QFloatLineEdit *m_pStdVol_LineEdit;

//	QLabel *m_pStdCur_Label;
//	QFloatLineEdit *m_pStdCur_LineEdit;

//	QLabel *m_pStdFre_Label;
//	QFloatLineEdit *m_pStdFre_LineEdit;

//	QLabel *m_pAntiShakeTime_Label;//����ʱ��
//	QFloatLineEdit *m_pAntiShakeTime_LineEdit;

	QSttGroupBox *m_pCurModule_GroupBox;//����ģ������
	QGridLayout *m_pCurModule_GridLayout;

	QLabel *m_pCurModuleSel_Label;
	QComboBox *m_pCurModuleSel_ComboBox;

	QLabel *m_pCurGear_Label;
	QComboBox *m_pCurGear_ComboBox;

	QLabel *m_pCurMaxPortVol_Label;//�����������˿ڵ�ѹ����
	QFloatLineEdit *m_pCurMaxPortVol_LineEdit;

	QLabel *m_pLargeCurOutTerm_Label;//�������������˿�
	QComboBox *m_pLargeCurOutTerm_ComboBox;

	QSttCheckBox *m_pLargeCurTerminal_CheckBox;//ģ����ѡ��ʹ�ô�����������
//	QCheckBox *m_p6ITo3I_CheckBox;//����6I�ϲ�3I���
//	long m_nCurModuleNum;//����ģ������

	STT_SystemParas *m_pSysParas;

	long m_nOldModuleSelIndex;//�ϴ�ѡ���ѡ���ģ��Index���������л�ģ���,����ǰһ�ε�����ѹֵ����
public slots:
	void slot_changeCurModuleSel(int nCurComboxIndex);
	void slot_changeCurGear(int nCurComboxIndex);
	void slot_changeLargeCurOutTerm(int nCurComboxIndex);
	void slot_stateChangedLargeCurTerminal(int nStateIndex);
};

#endif // QMODULESETWIDGET_H
