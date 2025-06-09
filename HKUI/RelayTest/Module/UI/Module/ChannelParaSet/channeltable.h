#ifndef CHANNELTABLE_H
#define CHANNELTABLE_H

#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QHeaderView>

#include "../../Module/SttTestSysGlobalPara.h"
#include "../CommonMethod/CommonMethod.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../ScrollCtrl/ScrollTableWidget.h"
#include "../CommonCtrl_QT/CommonCtrlInterface.h"

#define MACROTYPE_Manual            0
#define MACROTYPE_State             1
#define MACROTYPE_ManualHarm        2//手动试验里面显示的谐波界面
#define MACROTYPE_ManualSequence    3//通用序分量使用,只显示幅值、相位
#define MACROTYPE_ManualLineVol    4//通用线电压使用,只显示幅值、相位
#define MACROTYPE_RemoteMeas        5
#define MACROTYPE_ManualPower        6//通用实验-功率,只显示幅值、相位


//2024-5-16 wuxinyi 存储临时相位频率值
struct FloatTempChData 
{
	float fAngle;
	float fHz;
};

class QChannelTable : public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QChannelTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent = 0);
	virtual ~QChannelTable();
	
	virtual void initTable();
	virtual void setProperty(bool bDC);
	virtual void setItemValue(int row,int col,float fv);
	virtual void UpdateTable();

	void setMacroType(int type){ m_MacroType = type; }
	virtual void setTableData(tmt_channel *pArrUI);
	void setHarmIndex(int *pnHarmIndex);//20220819 zhouhj 增加用于手动谐波界面
	
	float getItemValue(int row,int col);
	void setAmpMaxMinValue(float fmax,float fmin);
	void setMultAmpMaxMinValue(float fmax[], float fmin[]);
	void setAmpEDValue(float fEDValue);
	
	void setColumnWidthByNum(int col,int width);
	void setTableFixWidgt(int width);
	int getTableHeight();
	int getTableWidth();

	bool IsBaseHarmAddValid(int row,int col,float fv);
	virtual void UpdateText(const QString &strText);

//#ifndef _PSX_QT_WINDOWS_
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	BOOL IsAttachSettingItem(QTableWidgetItem *pObject);
//#endif

	BOOL m_bRunning;

protected:
	int GetHarmIndex();

protected slots:
	virtual void slot_OnCellChanged(int row,int col);
	virtual void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);
	virtual void slot_TableShowMent(QPoint pos);

	void slot_ActUAmpEDClicked();
	void slot_ActPerUAmpEDClicked();
	void slot_ActUZeroClicked();
	void slot_ActUEqualAmpClicked();

	void slot_ActIAmp1Clicked();
	void slot_ActIAmp5Clicked();
	void slot_ActIAmp0Clicked();
	void slot_ActIqualAmpClicked();
	void slot_ActIAmpEDClicked();
	void slot_ActPerIAmpEDClicked();

	void slot_ActPhasePClicked();
	void slot_ActPhaseNClicked();
	void slot_ActPhaseZClicked();
	void slot_ActHz50Clicked();
	void slot_ActHz60Clicked();
	void slot_ActHzEqualClicked();

	void slot_UpdataVamp(QString strValue);
	void slot_UpdataIamp(QString strValue);
	void slot_UpdataHzamp(QString strValue);
	void slot_UpdataZX(QString strValue);
	void slot_UpdataFX(QString strValue);
	void slot_UpdataLX();

signals:
	void sig_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）

public:
	void init();
	void creatTableMenu();
	void changeTableColor();
	void changeTableColor_LineVol();
	void changeTableColor_RemoteMeas();
	virtual void UpdateValidTableDatas();	//量程切换时所有数据的有效性检查

	QString initMaxAcV(QString);
	QString initMaxAcI(QString);
	QString initMaxHz(QString);
	QString initMaxAcV_LineVol(QString str);//线电压
	QString initMaxAmp_RemoteMeas(MOUDLEType moudleType,QString str,QString strCellText);//UO/I0限制处理 弱信号，UO 0-7.8/3，I0 0-4

	tmt_channel *m_pArrUI;
	int m_MacroType; //0:通用 1:状态序列
	MOUDLEType m_moudleType;//0:电压模块 1：电流模块

	int m_tableIndex;
	bool m_bDC;

	QMenu *m_MenuAmp;
	QMenu *m_MenuPhase;
	QMenu *m_MenuFre;
	QList<QColor> m_ColorList;
	
	QAction *m_ActUAmpED; 
	QAction *m_ActUZero;
	QAction *m_ActUEqualAmp;
	QAction *m_ActIAmp1; 
	QAction *m_ActIAmp5; 
	QAction *m_ActIAmp0; 
	QAction *m_ActIqualAmp;
	QAction *m_ActIAmpED;

	//ADMU
	QAction* m_pActUAmpED2; 
	QAction* m_pActUAmpED5;
	QAction* m_pActUAmpED20;
	QAction* m_pActUAmpED120;
	QAction* m_pActUAmpED190;
	QAction* m_pActIAmpED1;
	QAction* m_pActIAmpED5;
	QAction* m_pActIAmpED20;
	QAction* m_pActIAmpED100;
	QAction* m_pActIAmpED120;


	float m_fAmpMax;
	float m_fAmpMin;
	float m_fMultAmpMax[MAX_VOLTAGE_COUNT];//add wangtao 20240828 通用实验-功率根据每个通道的功率限制对应电压大小
	float m_fMultAmpMin[MAX_VOLTAGE_COUNT];
	float m_fEDVal;

	int m_nRowHeight;
	int m_nHeaderViewHeight;
	CExBaseList *m_pChDatas;
	int *m_pnHarmIndex;

	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格
	QMap<int,FloatTempChData*> m_oTempSaveDataMap;//点击直流前后临时保存当前相位频率值


	virtual void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE, long nCol = 1);
	virtual void Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseZValue(int nStart,int nEnd, long nCol = 2);
	virtual void Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol = 3);

	bool HasHarmParaset();
	int getChIndexByChName( const CString & strChName );
};

#endif // CHANNELTABLE_H
