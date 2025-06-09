#ifndef QHARMWIDGET_H
#define QHARMWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "../Module/ChannelParaSet/QParaSetBase.h"
#include "../Module/ExSwitchSet/exswitchset.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "HarmParaTable.h"
#include "HarmParaWidget.h"
//#include "OscillogramGroupWidget.h"
#include "InterharmonicsWidget.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
#include "../Controls/SettingCtrls/QSettingLineEdit.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
class QHarmWidget : public QParaSetBase
{
    Q_OBJECT
public:
    explicit QHarmWidget(QWidget *parent = 0);
	virtual ~QHarmWidget();
	void InitUI();
	void SetDatas(tmt_HarmTest *pHarmTest,CSttTestResourceBase *pSttTestResource);

	//void UpdateResult(float fActValue,  float fActTime,  float fReturnValue,  float fReturnTime);
	void UpdateTestResource();

	void IncreaseOneStepGradient();
	void DecreaseOneStepGradient();

	void AddExBinParaWidget();
	void RemoveExBinParaWidget();

	void AddExBoutParaWidget();
	void RemoveExBoutParaWidget();

	void AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas);
	void RemoveGooseParaWidget();

	void AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV);
	void RemoveFT3OutParaWidget();

	bool ExistExBinParaWidget();
	bool ExistExBoutParaWidget();
	bool ExistGooseParaWidget();
	bool ExistFT3OutParaWidget();

	void EnableBinParaWidget(bool b);
	void EnableBoutParaWidget(bool b);
	void EnableGooseParaWidget(bool b);
	void EnableFT3OutParaWidget(bool b);

	void StartInit();
	void StopInit();
	void SetEnableTable(bool  bEnable);
	void SetHarmFont();

	void UpdateVolCurTable(bool bSate);//2024-7-29 wuxinyi 更新电压电流使能状态界面改变

protected:
	void ConnectAll();
	void DisConnectAll();

public:
	tmt_HarmTest *m_pHarmTest;
	CSttTestResourceBase *m_pSttTestResource;
	bool m_bControlLock;

public:
	QVBoxLayout *m_pVBoxLayout_Main;
	QHarmParaTable *m_pParaTable;
	QHarmParaWidget *m_pParaWidget;
    //OscillogramGroupWidget *m_pOscillogramGroupWidget;
	QInterharmonicsWidget* m_pInterharmonicsWidget;

	QTabWidget *m_pTabWidget;
	QGridLayout *m_pGridLayout_Bottom;

	ExSwitchSet* m_pExBinParaWidget;		//扩展开入设置
	ExSwitchSet* m_pExBoutParaWidget;		//扩展开出设置
	QGooseParaWidget* m_pGooseParaWidget;	//GOOSE数据发送
	QFT3OutParaWidget* m_pFT3OutParaWidget;

	QPushButton *m_pbn_Lock;
	QPushButton *m_pbn_Add;
	QPushButton *m_pbn_Del;
	QPushButton *m_pbn_SetZero;//谐波清零
	QPushButton *m_pbnEstimate;//cl20230725评估  整定及结果评估
	QPushButton *m_pVolSelBtn;//电压全选/清空
	QPushButton *m_pCurrSelBtn;//电流全选/清空

	QIcon m_imgLock;
	QIcon m_imgUnlock;

	//QSttLineEdit *m_lne_BasicHarmHz;
	QSettingLineEdit *m_lne_BasicHarmHz;	//20240624 huanglinag
	//QLineEdit *m_lne_ActionTime;
	//QLineEdit *m_lne_ActionValue;

	QScrollComboBox *m_pUChannel;
	QScrollComboBox *m_pIChannel;

	QStringList m_strUChannelList;
	QStringList m_strIChannelList;

	QLabel *m_Label_UChannel;
	QLabel *m_Label_IChannel;
	QLabel *m_Label_BasicHarmHz;
	//QLabel *m_Label_ActValue;
	//QLabel *m_Label_ActTime;

	bool m_bIsChanging;
	
signals:
	void sig_SetToZero();
	void sig_LockChanged();
	void sig_AddValue(int, int,  float );
	void sig_DelValue(int, int,  float );
	void sig_SelectDataChanged(int ,int );
	void sig_WaveValueChanged(int ,int );
	void sig_ChIndexChanged(int );
//	void sig_CheckStateChanged();

	void sig_updataParas();

public slots:
	void slot_UChannelChanged(int nIndex);
	void slot_IChannelChanged(int nIndex);
	void slot_AutoStateChanged(bool bState);

	void slot_WaveValueUChanged();
	void slot_ChanelValueUChanged();
	void slot_WaveValueIChanged();
	void slot_ChanelValueIChanged();
	void slot_ChIndexChanged(int);

	void slot_lne_BasicHarmHzChanged();
	void slot_lne_BasicHarmHzClicked();
	void slot_pbn_SetZeroClicked();
	void slot_pbn_AddClicked();
	void slot_pbn_DelClicked();
	void slot_pbn_LockClicked();
	void slot_pbn_Estimate();

	void slot_VolSelBtnClicked();
	void slot_CurrSelBtnClicked();

	void slot_ResetChangeFlag(int nValue);
//	void slot_CheckStateChanged();
};

#endif // QHARMWIDGET_H
