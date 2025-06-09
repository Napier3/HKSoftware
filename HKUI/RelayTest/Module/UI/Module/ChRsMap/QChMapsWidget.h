#ifndef QChMapsWidget_H
#define QChMapsWidget_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

#include "ChMapsGrid.h"
#include "../../../../Module/SttCmd/SttChMaps.h"
#include "../../../../Module/SttTest/Common/tmt_system_config.h"


class QChMapsWidget : public QWidget
{
	Q_OBJECT

public:
	QChMapsWidget(QWidget *parent = 0);
	~QChMapsWidget();

	void initUI(STT_SystemParas *pSysParas,CSttChMaps *pChMaps);
	void DisableCtrls_SysCfg();   //将系统参数部分的控件，设置为disable状态

	void InitDatas();//从系统参数中初始化界面选择
	void SaveDatas();//将界面参数保存到系统参数中

	void ShowDatas(CExBaseList *pDatas)
	{
		m_pChMapsGrid->ShowDatas(pDatas);
	}

	BOOL IsDigitalSelected()
	{
		return (m_pDigitalSel_CheckBox->checkState() == Qt::Checked);
	}

	void setChMapsFont();

signals:

public slots:
	void slot_changeDigitalType(int nIndex);

protected:
	void ReleaseUI();
	QGridLayout *m_pChMaps_GridLayout;//整个界面的布局控件
//	QGroupBox *m_pOutputSel_GroupBox;//输出类型选择Group
	QHBoxLayout *m_pOutputSel_HBoxLayout;//输出类型选择布局

	QCheckBox *m_pAnalogSel_CheckBox;//模拟量选择
	QCheckBox *m_pDigitalSel_CheckBox;//数字量选择
	QCheckBox *m_pWeakSel_CheckBox;//弱信号选择
	QLabel *m_pDigitalType_Label;//数字报文类型
	QComboBox *m_pDigitalType_Combobox;//数字报文类型选择

//	QGroupBox *m_pChMapsSet_GroupBox;//通道映射设置Group
//	QHBoxLayout *m_pChMapsSet_HBoxLayout;//通道映射设置布局

	CChMapsGrid *m_pChMapsGrid;//通道映射表格
	CSttChMaps *m_pCurChMaps;
	STT_SystemParas *m_pCurSysParas;
};

extern CFont *g_pSttGlobalFont;  

#endif // GOOSEPUBWIDGET_H
