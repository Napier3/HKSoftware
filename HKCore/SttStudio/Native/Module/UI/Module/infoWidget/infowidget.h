#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QTableWidget>
#include <QList>
#include "../../../SttTest/Common/tmt_result_def.h"
#include "../ScrollCtrl/ScrollTableWidget.h"

enum InPutDispNum{Input10 = 0,Input74};

class QInfoWidget : public QScrollTableWidget
{
	Q_OBJECT

public:
	explicit QInfoWidget(QWidget *parent = 0);
	~QInfoWidget();

	void init();
	void updateSwitchInfoTable(QList<CEventResult*> list);
	void InsertSwitchInfoTable(CEventResult* pEventResult,BOOL bUpdateStateIndex = FALSE);//对应手动时间不需要更新StateIndex，统一将其赋值为0
	
	void clear();
	void setProperty(InPutDispNum eflag);

	QString msformatTime(long us);
	CString FindBinInChange(long *pnNewArr, int size);
	void ShowBinInResultMsg(CEventResult* pEventResult);//20230904 suyang 增加在结果栏显示开入动作

private:
	InPutDispNum m_eDispFlag;
	long m_nBinIn[MAX_BINARYIN_COUNT];//20230725 wxy 存储原本的开入量
	long m_nBinInResult[MAX_BINARYIN_COUNT];//20241023  suyang 存储原本开始测试的的开入量用于更新开入变位

//2024-9-10 lijunqing 优化系统程序启动的效率
protected:
	bool m_bHasInitFinished;  //是否已经初始化完成，没有初始化，不能进行操作
	CExBaseList m_listEventResult; //没有点开界面，数据缓存与此，点开了界面，在Grid中显示

	void ShowListEventResult();
	void ShowEventResult(CEventResult* pEventResult,BOOL bUpdateStateIndex = FALSE);//对应手动时间不需要更新StateIndex，统一将其赋值为0

    virtual void showEvent(QShowEvent *event);
};

extern QFont *g_pSttGlobalFont; 

#endif // INFOWIDGET_H
