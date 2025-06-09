#ifndef QWEAKSETWIDGET_H
#define QWEAKSETWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include"WeakSetGrid.h"
#include "../../../SttTest/Common/tmt_system_config.h"


class QWeakSetWidget : public QWidget
{
	Q_OBJECT

public:
	QWeakSetWidget(QWidget *parent = 0);
	~QWeakSetWidget();

	void initUI(CSttChMaps *pChMaps);
	void InitDatas();//从系统参数中初始化界面选择
	void SaveDatas();//将界面参数保存到系统参数中
	void ShowDatas()
	{
		if (m_pWeakSetGrid != NULL)
		{
			m_pWeakSetGrid->ShowDatas(m_pChMaps);
		}
	}

	void ReleaseUI();

protected:
	QVBoxLayout *m_pAll_VBoxLayout;

	CWeakSetGrid *m_pWeakSetGrid;//通道映射表格

// 	QGroupBox *m_pGroup_GroupBox[MAX_WEEK_GROUP_NUM];
// 	QHBoxLayout *m_pGroup_HBoxLayout[MAX_WEEK_GROUP_NUM];
// 	QLabel *m_pPT_Rate_Label[MAX_WEEK_GROUP_NUM];
// 	QFloatLineEdit *m_pPT_PrimValue_LineEdit[MAX_WEEK_GROUP_NUM];
// 	QLabel *m_pPT_Unit1_Label[MAX_WEEK_GROUP_NUM];
// 	QFloatLineEdit *m_pPT_SecondValue_LineEdit[MAX_WEEK_GROUP_NUM];
// 	QLabel *m_pPT_Unit2_Label[MAX_WEEK_GROUP_NUM];
// 	QLabel *m_pCT_Rate_Label[MAX_WEEK_GROUP_NUM];
// 	QFloatLineEdit *m_pCT_PrimValue_LineEdit[MAX_WEEK_GROUP_NUM];
// 	QLabel *m_pCT_Unit1_Label[MAX_WEEK_GROUP_NUM];
// 	QFloatLineEdit *m_pCT_SecondValue_LineEdit[MAX_WEEK_GROUP_NUM];
// 	QLabel *m_pCT_Unit2_Label[MAX_WEEK_GROUP_NUM];

private:
	CSttChMaps *m_pChMaps;
};

#endif // QWEAKSETWIDGET_H
