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
	void DisableCtrls_SysCfg();   //��ϵͳ�������ֵĿؼ�������Ϊdisable״̬

	void InitDatas();//��ϵͳ�����г�ʼ������ѡ��
	void SaveDatas();//������������浽ϵͳ������

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
	QGridLayout *m_pChMaps_GridLayout;//��������Ĳ��ֿؼ�
//	QGroupBox *m_pOutputSel_GroupBox;//�������ѡ��Group
	QHBoxLayout *m_pOutputSel_HBoxLayout;//�������ѡ�񲼾�

	QCheckBox *m_pAnalogSel_CheckBox;//ģ����ѡ��
	QCheckBox *m_pDigitalSel_CheckBox;//������ѡ��
	QCheckBox *m_pWeakSel_CheckBox;//���ź�ѡ��
	QLabel *m_pDigitalType_Label;//���ֱ�������
	QComboBox *m_pDigitalType_Combobox;//���ֱ�������ѡ��

//	QGroupBox *m_pChMapsSet_GroupBox;//ͨ��ӳ������Group
//	QHBoxLayout *m_pChMapsSet_HBoxLayout;//ͨ��ӳ�����ò���

	CChMapsGrid *m_pChMapsGrid;//ͨ��ӳ����
	CSttChMaps *m_pCurChMaps;
	STT_SystemParas *m_pCurSysParas;
};

extern QFont *g_pSttGlobalFont;  

#endif // GOOSEPUBWIDGET_H
