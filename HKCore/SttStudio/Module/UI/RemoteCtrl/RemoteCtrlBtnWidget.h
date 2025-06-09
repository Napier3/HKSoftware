#ifndef REMOTECTRLBTNWIDGET_H
#define REMOTECTRLBTNWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Controls/SttLineEdit.h"

#include "../Controls/SttTabWidget.h"
#include "../../Module/SttTest/Common/tmt_manu_test.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include "RemoteCtrlTable.h"

//#define  STT_RemoteCtrl_Dataset_ID     "Ena"    //ң��

class QRemoteCtrlBtnWidget : public QWidget
{
	Q_OBJECT

public:
	QRemoteCtrlBtnWidget(QWidget *parent = 0);
	~QRemoteCtrlBtnWidget();
   
	tmt_ManualParas* m_pManualParas;
	CExBaseList m_oEnaInterDatasRef;            //�����������
	CExBaseList m_oEnaChDatasRef;            //ͨ����������
	QStringList m_listOprSeclect;           //����ѡ��

	void DeleteEnaInterDatas();//ɾ�����ң������
//	void DeleteEnaChDatas();//ɾ��ͨ��ң������

	void setData();

	void initUI();
	void initInterSelectData();
	void InitComboxData();
	void initBaseData();

	void UpdateData();
	void UpdateState();
	void UpdateOperationSelect();

	void startInit();
	void stopInit();

	void SetFont();

public:
	//QGridLayout *m_pGridLayout;
	QVBoxLayout *m_pMain_VLayout; 

	QHBoxLayout *m_pHLayout;
	QHBoxLayout *m_pBtn_HLayout;
	QVBoxLayout *m_pVLayout; 
	QWidget *m_pWidget;
	//QSttTabWidget *m_pBtnTab;


	QLabel* m_pInterSelect;
	CExBaseListComboBox *m_pInterSelect_ComboBox;//���ѡ��������
	QLabel* m_pChannelSelect;
	CExBaseListComboBox *m_pChannelSelect_ComboBox;//ͨ��ѡ��������
	QLabel* m_pDataType;
	QSttLineEdit *m_pDataType_LineEdit;

	QLabel* m_pOperationSelect;
	QScrollComboBox *m_pOperationSelect_ComboBox;
	QPushButton *m_pRemoteCtrlPre_Button;
	QPushButton *m_pRemoteCtrlExe_Button;
	QPushButton *m_pRemoteCtrlCancel_Button;
	QPushButton* m_pReadCondition;
	QSttLineEdit *m_pCondition_LineEdit;

	QRemoteCtrlTable *m_pRemoteCtrlGridFirst;
	QRemoteCtrlTable *m_pRemoteCtrlGridSecond;

	QPushButton *m_pBtnClearOperationRecords; //��ղ�����¼
	QPushButton* m_pBtnClearEventRecords;//����¼���¼

public slots:
	void slot_cmb_ChannelSelectChanged(int index);
	void slot_PushButton_ReadConditionClicked();

	void slot_btn_ClearOperationRecordsClicked();
	void slot_btn_ClearClearEventRecordsClicked();
};
extern QFont *g_pSttGlobalFont;  

#endif // REMOTECTRLBTNWIDGET_H
