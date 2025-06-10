#ifndef GRADIENTCHANNELTABLE_H
#define GRADIENTCHANNELTABLE_H

#include <QTableWidget>
#include <QAction>
#include <QHeaderView>

#include "../Module/UI/Module/CommonMethod/commonMethod.h"
#include "../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/BaseClass/ExBaseList.h"
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

	void InitLinearStepGradient();//�ڽ��ݵݱ�,���Եݱ��л���,�Խṹ��������³�ʼ��

	float getItemValue(int row,int col);
	void setAmpMaxMinValue(float fmax,float fmin);
	
	void setColumnWidthByNum(int col,int width);
	void setTableFixWidgt(int width);
	int getTableHeight();
	int getTableWidth();

	void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE);
	void Act_setHzEqualValue(int nStart,int nEnd,float fv);

	virtual void UpdateText(const QString &strText);
	QTableWidgetItem *m_pCurrKeyboardItem;//������ʱʹ�õı��Ԫ��

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

	int m_ModuleType;		//0:��ѹģ�� 1������ģ��
	int m_nGradientType;	//0:�޵ݱ� 1:���Ա仯 2:���ݱ仯 
	int m_nGradientObj; 	//0:��ֵ 1:��λ 2:Ƶ��
	tmt_channel *m_pArrUI;

	QList<QColor> m_ColorList;
	
	float m_fAmpMax;
	float m_fAmpMin;

	int m_nRowHeight;
	int m_nHeaderViewHeight;
	CExBaseList *m_pChDatas;
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
};

extern QFont *g_pSttGlobalFont;  

#endif // GRADIENTCHANNELTABLE_H
