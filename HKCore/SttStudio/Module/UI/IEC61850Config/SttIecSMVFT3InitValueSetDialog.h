#ifndef QSTTIECSMVFT3INITVALUESETDIALOG
#define QSTTIECSMVFT3INITVALUESETDIALOG

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include "../../../../Module/API/GlobalConfigApi.h"	//提供Cstring
// #include "../../../../Module/DataMngr/DataType.h"
// #include"../../../../Module/BaseClass/ExBaseOptrInterface.h"
#define IECCFG_COMMON_FT3_BIT_NUM                16

class QSttIecSMVFT3InitValueSetDialog : public QDialog
{
	Q_OBJECT
public:
	QSttIecSMVFT3InitValueSetDialog(long dwValue,QWidget *parent= NULL);
	~QSttIecSMVFT3InitValueSetDialog();
	
	
	void InitUI();
	void SetIecSMVFT3InitiaValueFont();	
	void SaveData();
	void ShowData();
	QString m_BitData[16];	//Bit获取选择数据集合
	long p_BitValue[16];	//Bit数据存储集合

	long m_dwValue;

private:
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;
	QWidget *m_pLeftWidget;
	QVBoxLayout *verticalLayout_Left;
	QHBoxLayout *horizontalLayout_Bit0;
	QLabel *m_pBit0_label;
	QComboBox *m_pBit0_comboBox;
	QHBoxLayout *horizontalLayout_Bit1;
	QLabel *m_pBit1_label;
	QComboBox *m_pBit1_comboBox;
	QHBoxLayout *horizontalLayout_Bit2;
	QLabel *m_pBit2_label;
	QComboBox *m_pBit2_comboBox;
	QHBoxLayout *horizontalLayout_Bit3;
	QLabel *m_pBit3_label;
	QComboBox *m_pBit3_comboBox;
	QHBoxLayout *horizontalLayout_Bit4;
	QLabel *m_pBit4_label;
	QComboBox *m_pBit4_comboBox;
	QHBoxLayout *horizontalLayout_Bit5;
	QLabel *m_pBit5_label;
	QComboBox *m_pBit5_comboBox;
	QHBoxLayout *horizontalLayout_Bit6;
	QLabel *m_pBit6_label;
	QComboBox *m_pBit6_comboBox;
	QHBoxLayout *horizontalLayout_Bit7;
	QLabel *m_pBit7_label;
	QComboBox *m_pBit7_comboBox;
	QWidget *m_pRightWidget;
	QVBoxLayout *verticalLayout_Right;
	QHBoxLayout *horizontalLayout_Bit8;
	QLabel *m_pBit8_label;
	QComboBox *m_pBit8_comboBox;
	QHBoxLayout *horizontalLayout_Bit9;
	QLabel *m_pBit9_label;
	QComboBox *m_pBit9_comboBox;
	QHBoxLayout *horizontalLayout_Bit10;
	QLabel *m_pBit10_label;
	QComboBox *m_pBit10_comboBox;
	QHBoxLayout *horizontalLayout_Bit11;
	QLabel *m_pBit11_label;
	QComboBox *m_pBit11_comboBox;
	QHBoxLayout *horizontalLayout_Bit12;
	QLabel *m_pBit12_label;
	QComboBox *m_pBit12_comboBox;
	QHBoxLayout *horizontalLayout_Bit13;
	QLabel *m_pBit13_label;
	QComboBox *m_pBit13_comboBox;
	QHBoxLayout *horizontalLayout_Bit14;
	QLabel *m_pBit14_label;
	QComboBox *m_pBit14_comboBox;
	QHBoxLayout *horizontalLayout_Bit15;
	QLabel *m_pBit15_label;
	QComboBox *m_pBit15_comboBox;

	QHBoxLayout *horizontalLayout_Btn;

public slots:
 		void slot_OKClicked();
		void slot_CancelClicked();
};

extern QFont *g_pSttGlobalFont;  

#endif