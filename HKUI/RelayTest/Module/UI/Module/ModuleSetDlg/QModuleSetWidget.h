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

#include "../../../../Module/SttTest/Common/tmt_system_config.h"

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
	void InitDatas();//从系统参数中初始化界面选择
	void SaveDatas();//将界面参数保存到系统参数中
	void SetModuleFont();

protected:
	void UpdateCurSelModuleUI();//更新当前选择的模块的界面逻辑

	QVBoxLayout *m_pModuleSet_VBoxLayout;

//	QGroupBox *m_pStdValues_GroupBox;//额定值Group
//	QGridLayout *m_pStdValues_GridLayout;

//	QLabel *m_pStdVol_Label;
//	QFloatLineEdit *m_pStdVol_LineEdit;

//	QLabel *m_pStdCur_Label;
//	QFloatLineEdit *m_pStdCur_LineEdit;

//	QLabel *m_pStdFre_Label;
//	QFloatLineEdit *m_pStdFre_LineEdit;

//	QLabel *m_pAntiShakeTime_Label;//防抖时间
//	QFloatLineEdit *m_pAntiShakeTime_LineEdit;

	QSttGroupBox *m_pCurModule_GroupBox;//电流模块设置
	QGridLayout *m_pCurModule_GridLayout;

	QLabel *m_pCurModuleSel_Label;
	QComboBox *m_pCurModuleSel_ComboBox;

	QLabel *m_pCurGear_Label;
	QComboBox *m_pCurGear_ComboBox;

	QLabel *m_pCurMaxPortVol_Label;//交流电流最大端口电压设置
	QFloatLineEdit *m_pCurMaxPortVol_LineEdit;

	QLabel *m_pLargeCurOutTerm_Label;//大电流端子输出端口
	QComboBox *m_pLargeCurOutTerm_ComboBox;

	QSttCheckBox *m_pLargeCurTerminal_CheckBox;//模拟量选择使用大电流端子输出
//	QCheckBox *m_p6ITo3I_CheckBox;//电流6I合并3I输出
//	long m_nCurModuleNum;//电流模块数量

	STT_SystemParas *m_pSysParas;

	long m_nOldModuleSelIndex;//上次选择的选择的模块Index，用于在切换模块后,保存前一次的最大电压值设置
public slots:
	void slot_changeCurModuleSel(int nCurComboxIndex);
	void slot_changeCurGear(int nCurComboxIndex);
	void slot_changeLargeCurOutTerm(int nCurComboxIndex);
	void slot_stateChangedLargeCurTerminal(int nStateIndex);
};

#endif // QMODULESETWIDGET_H
