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

	//插入 试验参数界面
	virtual void InsertActionTime();
	void initMaxPositiveEdit(QLineEdit *lne);

	void SetFormulaPic(int nType);

	//避免槽函数中的大量重复，定义此函数
	void setPara(QLineEdit *A, CString &strTemp);
	void setPara(QLineEdit *A, float &fTemp);
	void AddLabelToGroup(QString str,int nRow,int nCol);
	void AddEditToGroup(int nRow,int nCol);
	void ModifyCharByChenk();

	//绘制特性曲线图
	void UpdateCharDraw();
	void CalCharXYAxis(PTMT_PARAS_HEAD pPara);
	void CalCharYAxis(PTMT_PARAS_HEAD pPara);

protected:
	virtual void resizeEvent(QResizeEvent *);

signals:
	void updateData();
	void sig_UpdataCheck(bool, bool, bool);

	void sig_PbnAddClicked();  //添加
	void sig_PbnAddSerialClicked(); //添加序列
 	void sig_AddClicked(tmt_ActionTimeParasEx &,QList<int>);
	void sig_AddMutiClicked(tmt_ActionTimeParasEx &,QList<int>,float,float,float);
	void sig_PbnDelClicked(); //删除
	void sig_PbnDelAllClicked(); //删除所有
 	void sig_PbnClearResultClicked(); //清除结果
 	void sig_PbnClearAllClicked();//清除所有

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

	void slot_PbnAddClicked();  //添加
	void slot_AddOk(tmt_ActionTimeParasEx &,QList<int>);
	void slot_PbnAddSerialClicked(); //添加序列
	void slot_AddMutiOk(tmt_ActionTimeParasEx &,QList<int>,float,float,float);
	void slot_PbnDelClicked(); //删除
	void slot_PbnDelAllClicked(); //删除N-1
	void slot_PbnClearResultClicked(); //清除结果
	void slot_PbnClearAllClicked();//清除所有

	void slot_AddCIFeature(); //添加阻抗特性图
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

	//计算整定动作时间
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

	QPushButton *pbn_Add;		//添加实验
	QPushButton *pbn_AddSerial;	//添加系列
	QPushButton *pbn_Del;		//删除实验
	QPushButton *pbn_DelSerial;	//删除N-1
	QPushButton *pbn_Clear;		//清除结果
	QPushButton *pbn_ClearAll;	//清除所有

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
