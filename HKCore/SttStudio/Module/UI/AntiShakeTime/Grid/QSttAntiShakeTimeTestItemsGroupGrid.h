#ifndef  QSTTANTISHAKETIMETESTITEMSGROUPGRID
#define  QSTTANTISHAKETIMETESTITEMSGROUPGRID

#include <QWidget>
#include <QTableWidget>
#include "../../../Module/UI/SttTestCntrCmdDefine.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../../Module/DataMngr/DvmValues.h"
#include "../../../UI/Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

#define STT_ANTISHAKE_TIME_SELECT				 "Select"					   //选择
#define STT_ANTISHAKE_TIME_INTERVAL_SELECT		 "IntervalSelect"              //间隔选择
#define STT_ANTISHAKE_TIME_TEST_OBJECT			 "TestObject"				   //测试对象
#define STT_ANTISHAKE_TIME_BOUT_SET              "BoutSet"					   //开出设置
#define STT_ANTISHAKE_TIME_INIT_STATE			 "InitState"                   //初始状态
#define STT_ANTISHAKE_TIME_PULSE_WIDTH			 "PulseWidth"                  //脉冲宽度
#define STT_ANTISHAKE_TIME_ESTIMATE_TIMES		 "EstimateTimes"               //预计变位次数
#define STT_ANTISHAKE_TIME_ACTUAL_TIMES			 "ActualTimes"                 //实际变位次数
#define STT_ANTISHAKE_TIME_TEST_RESUL			 "TestResult"                  //测试结果

#define QSTTTESTITEMGRIDCOL   10 

class QSttMacroParaEditViewAntiShakeTime;


class QSttAntiShakeTimeCheckBoxDelegate : public QExBaseListCheckBoxDelegate 
{

public:
	QSttAntiShakeTimeCheckBoxDelegate(QObject *parent=NULL);
	virtual ~QSttAntiShakeTimeCheckBoxDelegate();

	virtual bool editorEvent(QEvent * event,
		QAbstractItemModel * model,
		const QStyleOptionViewItem &/* option*/,
		const QModelIndex & index);

};

class QSttAntiShakeTimeTestItemsGroupGrid:public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttAntiShakeTimeTestItemsGroupGrid(QWidget *parent = NULL);
	virtual ~QSttAntiShakeTimeTestItemsGroupGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	void ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow = TRUE);
	static void EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	virtual void Show_Check(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrCheck, GRID_CELL_EDIT_FUNC pFunc/*, BOOL bEnable*/);
	void UpdateDatas( CDvmValues *pValues,CExBaseList *pResultList,CString strItemID);
	int GetGridRow(int nIndex);


	QList<QString> m_oBoutSetList;
	QList<QString> m_ObjectIdList;

protected:
	QExBaseListCheckBoxDelegate *m_pFileSelectDelegate;
	int m_nRow;

public slots:
	void slot_UpdateCheckState(CDataGroup *pIecCfgDataBase,int nRow);

signals:
	void sig_UpdateCheckState(CDataGroup *pIecCfgDataBase,int nRow);

};


#endif
