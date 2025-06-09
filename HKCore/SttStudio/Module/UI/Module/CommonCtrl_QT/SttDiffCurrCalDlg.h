#ifndef STTDIFFCURRCALDLG_H
#define STTDIFFCURRCALDLG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStringList>
#include "QFloatLineEdit.h"
#include "../ScrollCtrl/ScrollComboBox.h"
#include "../../../SttTestBase/SttDiffCurrCalculatTool.h"

struct Stt_DiffCurrCalParas
{
	float m_fId;//�����
	float m_fIr;//�ƶ�����
	long m_nIrEquation;//�ƶ�����
	float m_fK1;//K1
	float m_fK2;//K2
	long m_nCTPoint;//CT����
	float m_fKph;//��ѹ��ƽ��ϵ��
	float m_fKpl;//��ѹ��ƽ��ϵ��

	long m_nWindH;//��ѹ�����������ʽ
	long m_nWindL;//��ѹ�������ʽ
	long m_nTransGroupMode;//�����ǲ�
	long m_nJXFactor;//ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ 
	long m_nPhCorrectMode;//У��ѡ��
	long m_nTestPhase;//������
	long m_nHightUsed;//��ѹ��Ӧ����
	long m_nLowerUsed;//��ѹ��Ӧ����

	void Init()
	{
		m_fId = 2.0f;
		m_fIr = 1.0f;
		m_nIrEquation = 0;
		m_fK1 = 2.0f;
		m_fK2 = 1.0f;
		m_nCTPoint = 0;
		m_fKph = 1.0f;
		m_fKpl = 1.0f;
		m_nWindH = 0;
		m_nWindL = 0;
		m_nTransGroupMode = 0;
		m_nJXFactor = 0;
		m_nPhCorrectMode = 0;
		m_nTestPhase = 0;
		m_nHightUsed = 0;
		m_nLowerUsed = 1;
	}

	Stt_DiffCurrCalParas()
	{
		Init();
	}
};


class SttDiffCurrCalDlg : public QDialog
{
	Q_OBJECT

public:
	SttDiffCurrCalDlg(QWidget *parent);
	virtual ~SttDiffCurrCalDlg();
	void InitUI(Stt_DiffCurrCalParas *pDiffCurrCalParas);

	CSttDiffCurrCalculatTool m_oDiffCalTool;
	long m_nHeightUsedIndex;
	long m_nLowerUsedIndex;

private:
	void InitDatas();
	QVBoxLayout *m_pAllVLayout;//��������Ĵ�ֱ����

	QGridLayout *m_pParasSet_GridLayout;
	QLabel *m_pId_Label;//�����
	QLabel *m_pIr_Label;//�ƶ�����
	QLabel *m_pIrEquation_Label;//�ƶ�����
	QLabel *m_pK1_Label;//K1
	QLabel *m_pK2_Label;//K2
	QLabel *m_pCTPoint_Label;//CT����
	QLabel *m_pKph_Label;//��ѹ��ƽ��ϵ��
	QLabel *m_pKpl_Label;//��ѹ��ƽ��ϵ��

	QLabel *m_pWindH_Label;//��ѹ�����������ʽ
	QLabel *m_pWindL_Label;//��ѹ�������ʽ
	QLabel *m_pTransGroupMode_Label;//�����ǲ�
	QLabel *m_pJXFactor_Label;//ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ 
	QLabel *m_pPhCorrectMode_Label;//У��ѡ��
	QLabel *m_pTestPhase_Label;//������
	QLabel *m_pHightUsed_Label;//��ѹ��Ӧ����
	QLabel *m_pLowerUsed_Label;//��ѹ��Ӧ����

	QFloatLineEdit *m_pId_FloatLineEdit;
	QFloatLineEdit *m_pIr_FloatLineEdit;
	QScrollComboBox *m_pIrEquation_ComboBox;
	QFloatLineEdit *m_pK1_FloatLineEdit;
	QFloatLineEdit *m_pK2_FloatLineEdit;
	QScrollComboBox *m_pCTPoint_ComboBox;
	QFloatLineEdit *m_pKph_FloatLineEdit;
	QFloatLineEdit *m_pKpl_FloatLineEdit;

	QScrollComboBox *m_pWindH_ComboBox;//��ѹ�����������ʽ
	QScrollComboBox *m_pWindL_ComboBox;//��ѹ�������ʽ
	QScrollComboBox *m_pTransGroupMode_ComboBox;//�����ǲ�
	QScrollComboBox *m_pJXFactor_ComboBox;//ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ 
	QScrollComboBox *m_pPhCorrectMode_ComboBox;//У��ѡ��
	QScrollComboBox *m_pTestPhase_ComboBox;//������
	QScrollComboBox *m_pHightUsed_ComboBox;//��ѹ��Ӧ����
	QScrollComboBox *m_pLowerUsed_ComboBox;//��ѹ��Ӧ����

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;
	QHBoxLayout *m_pOkCancel_HBoxLayout;
	QStringList m_astrEquationList;
	QStringList m_astrCTPointList;
	QStringList m_astrWindList;
	QStringList m_astrTransGroupMode;
	QStringList m_astrPhCorrectMode;
	QStringList m_astrTestPhaseList;
	QStringList m_astrCurrentUsedList;
	QStringList m_astrJXFactorList;
	Stt_DiffCurrCalParas *m_pDiffCurrCalParas;

signals:

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_CurrGroupChanged(int nCurrIndex);
	
};

#endif // STTDIFFCURRCALDLG_H
