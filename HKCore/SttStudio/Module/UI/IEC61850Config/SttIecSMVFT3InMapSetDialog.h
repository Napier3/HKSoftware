#ifndef QSTTIECSMVFT3INMAPSETDIALOG
#define QSTTIECSMVFT3INMAPSETDIALOG
#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include "../../../../Module/API/GlobalConfigApi.h"	
#define IECCFG_COMMON_FT3_BIT_NUM                16

class QSttIecSMVFT3InMapSetDialog : public QDialog
{
	Q_OBJECT
public:
	QSttIecSMVFT3InMapSetDialog(CString ostrMapString,QWidget *parent= NULL);
	~QSttIecSMVFT3InMapSetDialog();

	void InitUI();
	void SaveData();
	void ShowData();
	void SetIecSMVFT3InMapFont();
	void SetComboxData(QString m_strMapSplit);
	void SetComboxItem(QComboBox *m_Combox);
	
	CString m_strMapString;
	CString m_MapBitDataID[IECCFG_COMMON_FT3_BIT_NUM];	//实际存储MapBit数据存储集合
	QString m_MapSelectBitData[IECCFG_COMMON_FT3_BIT_NUM];	//MapBit对用combox实际选项数据存储集合
	int m_MapBitSelIndex[IECCFG_COMMON_FT3_BIT_NUM];	//MapBitInedx数据存储集合
	QComboBox *m_BitComBox[IECCFG_COMMON_FT3_BIT_NUM];	//combox集合，方便对单个combox进行操作
private:
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	QLabel *m_pBit0_label;
	QComboBox *m_pBit0_comboBox;
	QLabel *m_pBit1_label;
	QComboBox *m_pBit1_comboBox;
	QLabel *m_pBit2_label;
	QComboBox *m_pBit2_comboBox;
	QLabel *m_pBit3_label;
	QComboBox *m_pBit3_comboBox;
	QLabel *m_pBit4_label;
	QComboBox *m_pBit4_comboBox;
	QLabel *m_pBit5_label;
	QComboBox *m_pBit5_comboBox;
	QLabel *m_pBit6_label;
	QComboBox *m_pBit6_comboBox;
	QLabel *m_pBit7_label;
	QComboBox *m_pBit7_comboBox;
	QLabel *m_pBit8_label;
	QComboBox *m_pBit8_comboBox;
	QLabel *m_pBit9_label;
	QComboBox *m_pBit9_comboBox;
	QLabel *m_pBit10_label;
	QComboBox *m_pBit10_comboBox;
	QLabel *m_pBit11_label;
	QComboBox *m_pBit11_comboBox;
	QLabel *m_pBit12_label;
	QComboBox *m_pBit12_comboBox;
	QLabel *m_pBit13_label;
	QComboBox *m_pBit13_comboBox;
	QLabel *m_pBit14_label;
	QComboBox *m_pBit14_comboBox;
	QLabel *m_pBit15_label;
	QComboBox *m_pBit15_comboBox;

	QHBoxLayout *horizontalLayout_Btn;

	QHBoxLayout *m_pBinHBoxLayout;
	QVBoxLayout *m_pMainVLayout;
	QGridLayout *m_pBinGridLayout;

	
	public slots:
		void slot_OKClicked();
		void slot_CancelClicked();
};

extern QFont *g_pSttGlobalFont;  

#endif