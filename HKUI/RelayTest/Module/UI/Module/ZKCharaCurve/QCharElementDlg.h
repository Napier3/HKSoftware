#ifndef QCHARELEMENTDLG_H
#define QCHARELEMENTDLG_H

#include <QDialog>
#include <QObject>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
// #include "../../Module/TestWinFrame/testwinbase.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"

//20230601 zhouhj
#define STT_CHAR_ELEMENT_TYPE_LINED                               0
#define STT_CHAR_ELEMENT_TYPE_MHO                                 1
#define STT_CHAR_ELEMENT_TYPE_LENS                                2
#define STT_CHAR_ELEMENT_TYPE_LINER                               3
#define STT_CHAR_ELEMENT_TYPE_LINE                                4
#define STT_CHAR_ELEMENT_TYPE_ARC                                 5
#define STT_CHAR_ELEMENT_TYPE_ARCP                                6


class QCharElementDlg : public QDialog
{
	Q_OBJECT

public:
	QCharElementDlg(CCharElement *pCharElement, QWidget *parent);
	~QCharElementDlg();

	void InitTopUI();
	void InitParaUI(int nType);
	void InitParaCache(CExBaseList* pParamCache);
	void UpdateParaCache();
	void InitButton();
	void SetParaData();
	void CreateNewElement();

	int GetElementType();
	void AddLabelToList(QString str,int nRow,int nCol);
	void AddEditToList(int nRow,int nCol);
	void AddrBtnImpedance(bool bIsShow);//wangtao 20240615 增加阻抗表达方式
	void SetComboIndex(int nIndex, QString strText);
	CCharElement* GetNewElement(){	return m_pNewCharElement;	}

	void SetCharElementDlgFont(); //2022-10-31 sy  设置字体
	CString GetCurrClockwiseID();
	CString GetCurrDirID();

	BOOL IsEditText();//20230814 suyang 判断edit控件数值是否为空
    
	CString GetXYByImpedance(QString strXY,QString strAmp,QString strAngle);//20240617 wangtao 根据幅值相位求xy坐标
    CString GetImpedanceByXY(QString strAmpAngle,CString strAmp,CString strAngle);//根据xy坐标求幅值相位，用于对应的界面显示
private slots:
	void slot_ElementTypeChanged(int);
	void slot_PbnOkClicked();
	void slot_PbnCancelClicked();
	void slot_ImpedanceChanged(bool);


private:
	CExBaseList* m_pParamCache;//参数缓存
	CCharElement *m_pCurCharElement;
	CCharElement *m_pNewCharElement;

private:
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;
	QComboBox *m_cmbElementType;
//	QLineEdit *m_editErrorLen;  //20241018 wanmj 特性曲线编辑窗口根据误差评估计算误差带长度，这里去掉误差带长度修改
	QLineEdit *m_editTestPoint;
	QLabel *m_labelElementType;
//	QLabel *m_labelErrorLen;
	QLabel *m_labelTestPoint;

	QLabel *m_ImpedanceLabel;
	QRadioButton *m_rBtnAmpAngle;
	QRadioButton *m_rBtnRX;

	QList<QLineEdit*> m_editList;
	QList<QComboBox*> m_cmbList;
	QList<QLabel*>    m_labelList;
	
	QStringList m_strlistEleType;
	QStringList m_strlistDir;
	QStringList m_strlistClockDir;

	QVBoxLayout *m_MainLayout;
	QGridLayout *m_TopLayout;
	QGridLayout *m_ParaLayout;
	QHBoxLayout *m_ImpedanceLayout;
	QHBoxLayout *m_BottomLayout;
	
	bool m_bIsAmpAngleChecked;
};

extern CFont *g_pSttGlobalFont;  

#endif // QCHARELEMENTDLG_H
