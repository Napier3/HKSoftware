#ifndef GRADIENTCHANNELTABLE_H
#define GRADIENTCHANNELTABLE_H

#include <QTableWidget>
#include <QAction>
#include <QHeaderView>

#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
#include "../../../../../RelayTest/Module/SttTest/Common/tmt_common_def.h"
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
 #include "../../Module/CommonCtrl_QT/CommonCtrlInterface.h"

#define Module_U 		0
#define Module_I 		1

class GradientChannelTable : public QScrollTableWidget,public CCommonCtrlInterface
{
	Q_OBJECT

public:
	GradientChannelTable(int moudleType,int gradientType,int gradientObj,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent = 0);
	~GradientChannelTable();
	
	virtual void initTable();
	virtual void setItemValue(int row,int col,float fv);
	virtual void UpdateTable();

	void setTableData(tmt_channel *pArrUI);
	void setHeaderOfTable(QStringList strheader);
	void saveTable();

	void InitLinearStepGradient();//在阶梯递变,线性递变切换后,对结构体进行重新初始化

	float getItemValue(int row,int col);
	void setAmpMaxMinValue(float fmax,float fmin);
	
	void setColumnWidthByNum(int col,int width);
	void setTableFixWidgt(int width);
	int getTableHeight();
	int getTableWidth();

	void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE);
	void Act_setHzEqualValue(int nStart,int nEnd,float fv);

	virtual void UpdateText(const QString &strText);
	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格

//#ifndef _PSX_QT_WINDOWS_
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
//#endif

	BOOL m_bRunning;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_OnItemClicked(QTableWidgetItem *pItem);

	void slot_ActIqualAmpClicked();
	void slot_ActUEqualAmpClicked();
	void slot_ActHzEqualClicked();

	void slot_UpdataVamp(QString strValue);
	void slot_UpdataIamp(QString strValue);
	void slot_UpdataHzamp(QString strValue);

public:
	void init();
	void changeTableColor();
	void EnableGradientCol();

	QString initMaxAc(QString);
	QString initMaxHz(QString);

	int m_ModuleType;		//0:电压模块 1：电流模块
	int m_nGradientType;	//0:无递变 1:线性变化 2:阶梯变化 
	int m_nGradientObj; 	//0:幅值 1:相位 2:频率
	tmt_channel *m_pArrUI;

	QList<QColor> m_ColorList;
	
	float m_fAmpMax;
	float m_fAmpMin;

	int m_nRowHeight;
	int m_nHeaderViewHeight;
	CExBaseList *m_pChDatas;
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
};

extern CFont *g_pSttGlobalFont;  

#endif // GRADIENTCHANNELTABLE_H
