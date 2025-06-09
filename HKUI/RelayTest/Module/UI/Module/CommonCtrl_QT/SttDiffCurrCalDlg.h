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
	float m_fId;//差动电流
	float m_fIr;//制动电流
	long m_nIrEquation;//制动方程
	float m_fK1;//K1
	float m_fK2;//K2
	long m_nCTPoint;//CT极性
	float m_fKph;//高压侧平衡系数
	float m_fKpl;//低压侧平衡系数

	long m_nWindH;//高压侧绕组接线型式
	long m_nWindL;//低压侧接线型式
	long m_nTransGroupMode;//绕组间角差
	long m_nJXFactor;//平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式 
	long m_nPhCorrectMode;//校正选择
	long m_nTestPhase;//测试相
	long m_nHightUsed;//低压侧应用于
	long m_nLowerUsed;//低压侧应用于

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
	void UpdateUsed_ComboBox();//更新高压\低压侧应用于下拉框内容

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局

	QGridLayout *m_pParasSet_GridLayout;
	QLabel *m_pId_Label;//差动电流
	QLabel *m_pIr_Label;//制动电流
	QLabel *m_pIrEquation_Label;//制动方程
	QLabel *m_pK1_Label;//K1
	QLabel *m_pK2_Label;//K2
	QLabel *m_pCTPoint_Label;//CT极性
	QLabel *m_pKph_Label;//高压侧平衡系数
	QLabel *m_pKpl_Label;//低压侧平衡系数

	QLabel *m_pWindH_Label;//高压侧绕组接线型式
	QLabel *m_pWindL_Label;//低压侧接线型式
	QLabel *m_pTransGroupMode_Label;//绕组间角差
	QLabel *m_pJXFactor_Label;//平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式 
	QLabel *m_pPhCorrectMode_Label;//校正选择
	QLabel *m_pTestPhase_Label;//测试相
	QLabel *m_pHightUsed_Label;//低压侧应用于
	QLabel *m_pLowerUsed_Label;//低压侧应用于

	QFloatLineEdit *m_pId_FloatLineEdit;
	QFloatLineEdit *m_pIr_FloatLineEdit;
	QScrollComboBox *m_pIrEquation_ComboBox;
	QFloatLineEdit *m_pK1_FloatLineEdit;
	QFloatLineEdit *m_pK2_FloatLineEdit;
	QScrollComboBox *m_pCTPoint_ComboBox;
	QFloatLineEdit *m_pKph_FloatLineEdit;
	QFloatLineEdit *m_pKpl_FloatLineEdit;

	QScrollComboBox *m_pWindH_ComboBox;//高压侧绕组接线型式
	QScrollComboBox *m_pWindL_ComboBox;//低压侧接线型式
	QScrollComboBox *m_pTransGroupMode_ComboBox;//绕组间角差
	QScrollComboBox *m_pJXFactor_ComboBox;//平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式 
	QScrollComboBox *m_pPhCorrectMode_ComboBox;//校正选择
	QScrollComboBox *m_pTestPhase_ComboBox;//测试相
	QScrollComboBox *m_pHightUsed_ComboBox;//高压侧应用于
	QScrollComboBox *m_pLowerUsed_ComboBox;//低压侧应用于

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
