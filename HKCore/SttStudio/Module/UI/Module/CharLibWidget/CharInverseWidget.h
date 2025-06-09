#ifndef PARASETWIDGET_H
#define PARASETWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QSpacerItem>
#include "ui_CharInverseWidget.h"
#include "QImpCharactWidget.h"
#include "../../../../../Module/OSInterface/OSInterface.h"

#include "../../Module\TestWinFrame\PartParaWidget\ActionTimeDataWidget.h"
#include "..\..\Module\SttTest\Common\ActionTime\tmt_action_time_test.h"
#include "..\..\Module\TestWinFrame\testwinbase.h"
#include "AddMutiTestItemDig.h"
#include "AddTestDig.h"

class CharInverseWidget : public QWidget
{
	Q_OBJECT

public:
	CharInverseWidget(QWidget *parent = 0);
	~CharInverseWidget();

	virtual void setData(PTMT_PARAS_HEAD pCurr);

	void initConnect();
	void initData();
	void InitGroup();
	void UpdateGroup();
	void InitCharactWidget();

	virtual void stopInit();
	virtual void startInit();

	/*void CalFaultTime();*/

	//���� �����������
	virtual void InsertActionTime();
	void initMaxPositiveEdit(QLineEdit *lne);

	void SetFormulaPic(int nType);

	//����ۺ����еĴ����ظ�������˺���
	void setPara(QLineEdit *A, CString &strTemp);
	void setPara(QLineEdit *A, float &fTemp);
	void AddLabelToGroup(QString str,int nRow,int nCol);
	void AddEditToGroup(int nRow,int nCol);
	void ModifyCharByChenk();

	//������������ͼ
	void UpdateCharDraw();
	void CalCharXYAxis(PTMT_PARAS_HEAD pPara);
	void CalCharYAxis(PTMT_PARAS_HEAD pPara);

protected:
	virtual void resizeEvent(QResizeEvent *);

signals:
	void updateData();
	void sig_UpdataCheck(bool, bool, bool);

	void sig_PbnAddClicked();  //���
	void sig_PbnAddSerialClicked(); //�������
 	void sig_AddClicked(tmt_ActionTimeParasEx &,QList<int>);
	void sig_AddMutiClicked(tmt_ActionTimeParasEx &,QList<int>,float,float,float);
	void sig_PbnDelClicked(); //ɾ��
	void sig_PbnDelAllClicked(); //ɾ������
 	void sig_PbnClearResultClicked(); //������
 	void sig_PbnClearAllClicked();//�������

	void sig_CICharChanged();

protected slots:
	void slot_TabPageChanged(int);
	void slot_oncheckBox_Set1_toggled(bool b);
	void slot_oncheckBox_Set2_toggled(bool b);
	void slot_oncheckBox_Set3_toggled(bool b);

	void slot_onlineEdit_VSet1_editFinished();
	void slot_onlineEdit_VSet2_editFinished();
	void slot_onlineEdit_VSet3_editFinished();
	void slot_onlineEdit_TSet2_editFinished();
	void slot_onlineEdit_TSet1_editFinished();
	void slot_onlineEdit_TSet3_editFinished();

	void slot_ElementData_editFinished();

	void slot_PbnAddClicked();  //���
	void slot_AddOk(tmt_ActionTimeParasEx &,QList<int>);
	void slot_PbnAddSerialClicked(); //�������
	void slot_AddMutiOk(tmt_ActionTimeParasEx &,QList<int>,float,float,float);
	void slot_PbnDelClicked(); //ɾ��
	void slot_PbnDelAllClicked(); //ɾ��N-1
	void slot_PbnClearResultClicked(); //������
	void slot_PbnClearAllClicked();//�������

	void slot_AddCIFeature(); //����迹����ͼ
	void slot_CIAddChar(CCharacteristic *pObj);

	void slot_FaultTypeChanged();
	void slot_FaultCurChangedFinished();

	void slot_ParaAddPoint(float fx,float fy);
	void slot_ParaPointChange(float fx,float fy);
	void slot_UpdateData();
	void slot_UpdateCheck(bool bOne, bool bTwo, bool bThr );

public:
    Ui::CharInverseWidget ui;
	//ActionTime
	tmt_ActionTimeParasEx *m_pActionTimeParas;
	tmt_CurrInverseTimeTest *m_pActionTimeTest;
	CDataGroup *m_pDvmData;

	ActionTimeDataWidget *m_pActionTimeWidget;

	//������������ʱ��
	//float calCurrent(float K);
	//float getSettingTime(float fx);
	QImpCharactWidget* m_pImpCharactWidget;


private:
	//QCheckBox
	bool m_bCheckBox1;
	bool m_bCheckBox2;
	bool m_bCheckBox3;

	QWidget *tab_1;
	QVBoxLayout *m_vLayout;
	QHBoxLayout *m_hLayout;
	QHBoxLayout *m_hLayout_1;
	QVBoxLayout *m_vLayout_1;

	QPushButton *pbn_Add;		//���ʵ��
	QPushButton *pbn_AddSerial;	//���ϵ��
	QPushButton *pbn_Del;		//ɾ��ʵ��
	QPushButton *pbn_DelSerial;	//ɾ��N-1
	QPushButton *pbn_Clear;		//������
	QPushButton *pbn_ClearAll;	//�������

	//lne_name
	QLabel *label;
	QLineEdit *lne_Name;

	QList<QLineEdit*> m_editList;
	QList<QLabel*>    m_labelList;

	QPixmap bgImage;
	QLabel *m_labelbg;

// 	//Spacer
// 	QSpacerItem *m_Spacer_1;
// 	QSpacerItem *m_Spacer_2;

};

#endif // PARASETWIDGET_H
