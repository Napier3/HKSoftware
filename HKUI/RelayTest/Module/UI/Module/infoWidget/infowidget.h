#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QTableWidget>
#include <QList>
#include "../../../../Module/SttTest/Common/tmt_result_def.h"
#include "../ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/OSInterface/OSInterface.h"

enum InPutDispNum{Input10 = 0,Input74};

//20240913 huangliang 记录每次开入量的状态
struct HL_Record_BinHis
{
	int iRow;	//行号
	long nBinIn[MAX_BINARYIN_COUNT];	//开入量状态
};

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

	QList<HL_Record_BinHis> mlist_Record;	//20240913 huangliang 记录各行的开入量状态
	void UpdateItemShowBinBinary();	//20240913 huangliang 更新Item数据
	void AddReordBinHis(int iRow, long *pnNewArr);

private:
	InPutDispNum m_eDispFlag;
	long m_nBinIn[MAX_BINARYIN_COUNT];//20230725 wxy 存储原本的开入量
};

extern CFont *g_pSttGlobalFont; 

#endif // INFOWIDGET_H
