#ifndef SttReplayParaSetWidget_H
#define SttReplayParaSetWidget_H

#include <QWidget>
#include "ui_SttReplayParaSetWidget.h"

#include "../Module/CommonMethod/commonMethod.h"
//#include "define.h"
#include "../../Module/DataMngr/DataGroup.h"
//#include "../Module/TestWinFrame/testwinbase.h"
#include "SttReplayWaveformEditWidget.h"


// #include "..\..\..\Module\BaseClass\ExBaseList.h"
// #include "../../Module/ReplayTest/SttModuleChComtradeBind.h"
// #include "..\..\Module\SttTest\Common\tmt_test_paras_head.h"
// #include "..\..\..\Module\Record\Comtrade\ComtradeAnalogData.h"
// #include "../../Module/ReplayTest/BigComtradeTransPlay.h"

#include "SttReplayTriggerWidget.h"
#include "SttReplayModuleChWidget.h"
#include "SttReplayBoutModuleChWidget.h"
#include "SttReplayDigitalMoudleWidget.h"

#include "../Interface/SttMacroParaEditViewOriginal.h"


class CSttReplayParaSetWidget : public QWidget/*,public SttReplayParaSetWidgetInterface*/
{
	Q_OBJECT

public:
	CSttReplayParaSetWidget(CSttModulesComtradeBind *pChMapConfig,QWidget *parent = 0);
	virtual ~CSttReplayParaSetWidget();

	virtual void startInit();
	virtual void stopInit();
	virtual void setData(PTMT_PARAS_HEAD pCurr);
	void setDvm(CDataGroup *pDvmData);

	void init(CSttModulesComtradeBind *pSttModulesComtradeBind,QWidget *parent);
	void clearTable();
	void UpdateUIMax();
	void AddTabWidget(QWidget *pCurWidget,const QString &strTitle);

signals:
	

public slots:
	void slot_OpenRcdFileClicked();
	void slot_TabChanged(QWidget *pCurWidget);
	void slot_UpdateTwoCursorTimeValues(double dValueA,double dValueB);

public:
	//解析完Comtrade文件之后初始化界面显示
	void InitModuleChList();
	void InitBinaryModuleChList();
	void InitSttReplayTriggerWidget();
	void InitSttReplayWaveEditWidget();
	void initTabPage();
	void UpdateStateView(bool bEnable);

	//刷新通道瞬时值
	void UpdateChMomentaryVal();
	void UpdateEditData();

	int GetWaveEditType(); 
CSttReplayTriggerWidget *m_pSttReplayTriggerWidget;
	CComtradeAnalogData* GetComtradeAnalogU(long nIndex);
	CComtradeAnalogData* GetComtradeAnalogI(long nIndex);
	CComtradeBinaryData* GetComtradeBinary(long nIndex);


private:
	void InitWidget();
	long GetTotalChannelNum();

	CSttModulesComtradeBind *m_pSttModulesComtradeBind;
	SttReplayWaveformEditWidget *m_pWaveformEditWidget;
	QSttReplayDigitalModuleWidget *m_pDigitalModuleWidget;

	QList<CSttReplayModuleChWidget *> m_oSttReplayModuleChWidgetList;
	QList<CSttReplayBoutModuleChWidget*> m_oBinaryOutSetExList;
	CSttReplayBoutModuleChWidget* m_pBinaryOutSetWidget;
	QList<CSttReplayModuleChWidget *> m_oSttReplayWeekModuleChWidgetList;//弱信号模块

	CExBaseList m_oComtradeVolChs_Ref;
	CExBaseList m_oComtradeCurChs_Ref;
	CExBaseList m_oComtradeBinaryChs_Ref;
	QWidget *m_pPreWidget;//dingxy 20240710 焦点改变

	Ui::SttReplayParaSetWidget ui;
};

extern QFont *g_pSttGlobalFont;  

#endif // SttReplayParaSetWidget_H
