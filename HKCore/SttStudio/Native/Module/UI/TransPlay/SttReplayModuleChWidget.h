#ifndef _CSttReplayModuleChWidget_H_
#define _CSttReplayModuleChWidget_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QGroupBox>

#include "SttReplayAdjustComboBox.h"
#include "../../ReplayTest/BigComtradeTransPlay.h"
#include "../Module/CommonCtrl_QT/QFloatLineEdit.h"

// #include "../../Module/ReplayTest/SttModuleChComtradeBind.h"
// #include "../../Module/ReplayTest/BigComtradeTransPlay.h"
// #include "..\..\..\Module\Record\Comtrade\ComtradeAnalogData.h"
// #include "..\..\..\Module\BaseClass\ExBaseList.h"



class CSttReplayModuleChWidget : public QWidget
{
	Q_OBJECT

public:
	CSttReplayModuleChWidget(int nModuleIndex,CSttModuleComtradeBind *pModuleInfo,QWidget *pParent = 0);
	~CSttReplayModuleChWidget();

	QFloatLineEdit *m_pVolMax_Edit;
	QFloatLineEdit *m_pCurMax_Edit;
	QFloatLineEdit *m_pTimeA_Edit;
	QFloatLineEdit *m_pTimeB_Edit;
	QFloatLineEdit *m_pTimeDiff_Edit;	
	
	QFloatLineEdit *m_pPTPrim_Edit;
	QFloatLineEdit *m_pPTSecond_Edit;
	QFloatLineEdit *m_pCTPrim_Edit;
	QFloatLineEdit *m_pCTSecond_Edit;
	QList<QCheckBox *> m_ChSelList;
	QList<QScrollComboBox *> m_AChSelList;
	QList<QScrollComboBox *> m_BChSelList;

	CSttModuleComtradeBind *m_pModuleInfo;
	QList<QLineEdit *> m_KEditList;
	QList<QScrollComboBox *> m_WeekChSelTypeList;


private:
	QLabel *m_plbChanel;
	QLabel *m_plbChanelA;
	QLabel *m_plbChanelB;
	QPushButton *m_pOpenRcdFileBtn;


	QList<QLabel *> m_OptrSubLabelList;
	QList<QLabel *> m_OptrDivLabelList;
	//QList<QScrollComboBox *> m_WeekChSelTypeList;

	QLabel *m_pPTRate_Label;
	QLabel *m_pPTDivision_Label;
	QLabel *m_pCTRate_Label;
	QLabel *m_pCTDivision_Label;

	QLabel *m_pVolMax_Label;
	QLabel *m_pCurMax_Label;
	QLabel *m_pTimeA_Label;
	QLabel *m_pTimeB_Label;
	QLabel *m_pTimeDiff_Label;
	QGroupBox *m_pMaxMinGroupBox; 

	QGridLayout *m_pGridLayout_RcdChs;
	QHBoxLayout *m_pHLayout_ReplayChs;
	QHBoxLayout *m_pHLayout_PT_CT_Rate;
	QVBoxLayout *m_pVLayout_MaxMinValues;
	QGridLayout *m_pGridLayout_MaxMinValues;
	QVBoxLayout *m_pMainLayout;

	int m_nModuleIndex;

public:
	virtual void SetChSelectList(const QStringList &oUChList,const QStringList &oIChList);
	long GetChSelectIndex(const CString &strChName);
	bool IsModuleType_U(){ return m_pModuleInfo->GetCount_U() > 0;}
	bool IsModuleType_I(){ return m_pModuleInfo->GetCount_U() > 0;}
	void OnModuleChChanged(int nModuleIndex,int nChIndex);
	void UpdateEditData();
	virtual void setEnableStateUI(bool bEnable);
	virtual void UpdatePT_CT_Rates();
	void UpdateUIMax(double fUMax,double fIMax);
	void UpdateTwoCursorTimeValues(double dValueA,double dValueB);
	void SetDefaultFocusCtrl();
	void SetReplayModuleFont();

	int GetModulesComtradeBindIndex();//获取在模块插件链表中序号
	int GetRealChIndex(int nRealModuleIndex,int nChIndex);//获取通道在模块中的实际位置
	virtual QWidget * GetParaSetWidget();


	virtual void initSignalSlots();
	virtual void uninitSignalSlots();

private:
	void initUI();

signals:
	void sig_ModuleChChanged(int nModuleIndex,int nChIndex);
	void sig_ModuleChRangeChanged();

public slots:
	void slot_ChSelChanged(int nIndex);
	void slot_AChSelChanged(int nIndex);
	void slot_BChSelChanged(int nIndex);
	void slot_KChanged();
	void slot_OpenRcdFileClicked();
	void slot_SttLineEditChanged();
	void slot_FloatLineEditChanged();

	virtual void slot_ChangedPT1();
	virtual void slot_ChangedPT2();
	virtual void slot_ChangedCT1();
	virtual void slot_ChangedCT2();

private:
	QWidget *m_pParentWidget;
};



#endif