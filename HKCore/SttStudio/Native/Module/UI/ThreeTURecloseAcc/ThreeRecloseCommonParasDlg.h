#ifndef ThreeRecloseCommonParasDlg_H
#define ThreeRecloseCommonParasDlg_H
#include <QDialog>
#include <QTabWidget>
#include <QComboBox>
#include "../Controls/SttLineEdit.h"
#include "../../DataMngr/DataGroup.h"


class QThreeRecloseCommonParasDlg : public QDialog
{
	Q_OBJECT

public:
	QThreeRecloseCommonParasDlg(CDataGroup* pParas,QWidget* parent = NULL);
	~QThreeRecloseCommonParasDlg();

public:
	void InitUI();
	void GetLineEditValue(QSttLineEdit * pLineEdit,const CString strID,long nPrecssion);
	void GetComboxValue(QComboBox * pComboBox,const CString strID,bool b = false);
	void InitData();
	void InitConnections();



private:
	QTabWidget *m_pTableWidget;
	QComboBox *m_pCmbFaultTrigMode;       //故障触发方式
	QComboBox *m_pCmbPTPos;			   //TV安装位置
	QComboBox *m_pCmbCTPos;               //TA正极性
	QSttLineEdit *m_pEditLoadCur;    //负荷电流
	QSttLineEdit *m_pEditLoadAng;    //负荷角度
	QComboBox *m_pCmbSimulateBreakerDelay;//断路器模拟
	QSttLineEdit *m_pEditBrkBreakTime;    //分闸时间（s）
	QSttLineEdit *m_pEditBrkCloseTime;    //合闸时间（s）
	QComboBox *m_pCmbBinSelect;           //开入量选择
	CDataGroup* m_pParas;
	QList<QComboBox *> m_pBoutComboBoxList;
	QList<QComboBox *> m_pBinComboBoxList;



protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	
	//void slot_CmbFaultTrigMode(int nIndex);
	//void slot_CmbPTPos(int nIndex);
	//void slot_CmbCTPos(int nIndex);
	void slot_CmbSimulateBreakerDelay(int nIndex);
	void slot_CmbBinSelect(int nIndex);

	void slot_EditLoadCur();
	void slot_EditLoadAng();
	void slot_EditBrkBreakTime();
	void slot_EditCloseBreakTime();

};
#endif
