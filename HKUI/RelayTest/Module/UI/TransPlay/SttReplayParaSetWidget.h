#ifndef SttReplayParaSetWidget_H
#define SttReplayParaSetWidget_H

#include <QWidget>
#include "ui_SttReplayParaSetWidget.h"

#include "../Module/CommonMethod/commonMethod.h"
//#include "define.h"
#include "../../../Module/DataMngr/DataGroup.h"
//#include "../Module/TestWinFrame/testwinbase.h"
#include "SttReplayWaveformEditWidget.h"


// #include "..\..\..\Module\BaseClass\ExBaseList.h"
// #include "../../Module/ReplayTest/SttModuleChComtradeBind.h"
// #include "..\..\Module\SttTest\Common\tmt_test_paras_head.h"
// #include "..\..\..\Module\Record\Comtrade\ComtradeAnalogData.h"
// #include "../../Module/ReplayTest/BigComtradeTransPlay.h"

#include "SttReplayTriggerWidget.h"
#include "SttReplayModuleChWidget.h"
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
	void InitSttReplayTriggerWidget();
	void InitSttReplayWaveEditWidget();
	void initTabPage();
	void UpdateStateView(bool bEnable);

	//刷新通道瞬时值
	void UpdateChMomentaryVal();
	void UpdateEditData();

	int GetWaveEditType(); 
	int GetInsertNormalType();

	CSttReplayTriggerWidget *m_pSttReplayTriggerWidget;
	CComtradeAnalogData* GetComtradeAnalogU(long nIndex);
	CComtradeAnalogData* GetComtradeAnalogI(long nIndex);

private:
	void InitWidget();
	long GetTotalChannelNum();

	CSttModulesComtradeBind *m_pSttModulesComtradeBind;
	SttReplayWaveformEditWidget *m_pWaveformEditWidget;
	QSttReplayDigitalModuleWidget *m_pDigitalModuleWidget;

	QList<CSttReplayModuleChWidget *> m_oSttReplayModuleChWidgetList;
	CExBaseList m_oComtradeVolChs_Ref;
	CExBaseList m_oComtradeCurChs_Ref;

	Ui::SttReplayParaSetWidget ui;
};

extern CFont *g_pSttGlobalFont;  

#endif // SttReplayParaSetWidget_H
