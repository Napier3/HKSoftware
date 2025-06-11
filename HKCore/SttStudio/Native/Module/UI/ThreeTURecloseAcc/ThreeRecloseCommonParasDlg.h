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
	QComboBox *m_pCmbFaultTrigMode;       //���ϴ�����ʽ
	QComboBox *m_pCmbPTPos;			   //TV��װλ��
	QComboBox *m_pCmbCTPos;               //TA������
	QSttLineEdit *m_pEditLoadCur;    //���ɵ���
	QSttLineEdit *m_pEditLoadAng;    //���ɽǶ�
	QComboBox *m_pCmbSimulateBreakerDelay;//��·��ģ��
	QSttLineEdit *m_pEditBrkBreakTime;    //��բʱ�䣨s��
	QSttLineEdit *m_pEditBrkCloseTime;    //��բʱ�䣨s��
	QComboBox *m_pCmbBinSelect;           //������ѡ��
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
