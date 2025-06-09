#ifndef	 QSTTANTISHAKETIMEDINEVENTGROUPGRID
#define  QSTTANTISHAKETIMEDINEVENTGROUPGRID

#include "../../../Module/UI/SttTestCntrCmdDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include <QTableWidget>

typedef struct tmt_antishake_time_result_set
{
	int m_nInterval;					//间隔
	int m_nTestObject;				//测试对象
	int m_nEventDescription;			//事件描述
	CString m_strEventTime;			//事件发生时间
};

class QSttAntiShakeTimeDinEventGroupGrid:public QTabWidget
{
	Q_OBJECT

public:
	QSttAntiShakeTimeDinEventGroupGrid(QWidget *parent = NULL);
	virtual ~QSttAntiShakeTimeDinEventGroupGrid();

	void InitUI();
	void CleanTestResultData();           //清空表格中的值。 
	void AddItem(tmt_antishake_time_result_set *pData); 

	QTableWidget *m_pTableWidget;
	QList<tmt_antishake_time_result_set *> m_oAntiShakeTimeList;
};


#endif
