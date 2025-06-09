#ifndef CHANNELTABLE_H
#define CHANNELTABLE_H

#define _WIN32_WINNT  0x0400

#include <QTableWidget>
#include <QAction>
#include <QHeaderView>
#include "../../Define.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"
#include "../../../../../Module/BaseClass/ExBaseList.h"

#define MACROTYPE_Manual  0
#define MACROTYPE_State   1
#define MACROTYPE_Sequence 2

//2024-5-16 wuxinyi 存储临时相位频率值
struct FloatTempChData 
{
	float fAngle;
	float fHz;
};

class CHannelTable : public QTableWidget
{
	Q_OBJECT

public:
	CHannelTable(MOUDLEType moudleType,CExBaseList *pChList,tmt_channel *pArrUI,QWidget *parent = 0);
	~CHannelTable();
	
	virtual void initTable();
	virtual void setColumnNum(int num);
	virtual void setProperty(bool bDCTest);
	virtual void setItemValue(int row,int col,float fv);
	virtual void UpdateTable();

	void setMacroType(int type){ m_MacroType = type; }
	void setTableData(tmt_channel *pArrUI);
	void setHeaderOfTable(QStringList strheader);
	float getItemValue(int row,int col);
	void setAmpMaxMinValue(float fmax,float fmin);
	void setAmpEDValue(float fEDValue);
	
	void setColumnWidthByNum(int col,int width);
	void setTableFixWidgt(int width);
	int getTableHeight();
	int getTableWidth();

	bool IsBaseHarmAddValid(int row,int col,float fv);
	virtual void keyPressEvent(QKeyEvent *event);

protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_TableShowMent(QPoint pos);

	void slot_ActUAmpEDClicked();
	void slot_ActUZeroClicked();
	void slot_ActUEqualAmpClicked();

	void slot_ActIAmp1Clicked();
	void slot_ActIAmp5Clicked();
	void slot_ActIAmp0Clicked();
	void slot_ActIqualAmpClicked();
	void slot_ActIAmpEDClicked();

	void slot_ActPhasePClicked();
	void slot_ActPhaseNClicked();
	void slot_ActPhaseZClicked();
	void slot_ActHz50Clicked();
	void slot_ActHz60Clicked();
	void slot_ActHzEqualClicked();
	void slot_ActHzEqualAllClicked();//等全部频率chenling 20230526
	void slot_ActPerUAmpEDClicked();
	void slot_ActPerIAmpEDClicked();

signals:
	void sig_ChannelValueChanged(MOUDLEType moudleType,/*int moudleID,*/int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）
	void sig_keyPressEventExec(int nKeyValue);//用于转发键盘快捷按键

public:
	void init();
	void creatTableMenu();
	void changeTableColor();
	virtual void UpdateValidTableDatas();	//量程切换时所有数据的有效性检查

	QString initMaxAcV(QString);
	QString initMaxAcI(QString);
	QString initMaxHz(QString);

	int m_dispmode;
	bool m_bUsekeyPressEventExec;//是否执行键盘事件转发
	tmt_channel *m_pArrUI;
	QMap<int,FloatTempChData*> m_oTempSaveDataMap;//点击直流前后临时保存当前相位频率值

	int m_MacroType; //0:通用 1:状态序列
	MOUDLEType m_moudleType;//0:电压模块 1：电流模块
//	int m_moudleID;			//模块编号
//	int m_moudleChannelNum;	//模块通道数
	int m_ColumnNum;
//	int m_nNameNum;
	int m_tableIndex;
	bool m_bDCTest;
	bool m_bSendUpdateParas;//zhouhj 2023.8.9 是否下发更新参数

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


	//ADMU 2024.5.6
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
	float m_fEDVal;

	int m_nRowHeight;
	int m_nHeaderViewHeight;
	CExBaseList *m_pChDatas;

	void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE);
	void Act_setPrasePValue(int nSwitch,int nOffset,float fv);
	void Act_setPraseNValue(int nSwitch,int nOffset,float fv);
	void Act_setPraseZValue(int nStart,int nEnd);
	void Act_setHzEqualValue(int nStart,int nEnd,float fv);

	bool HasHarmParaset();
};

#endif // CHANNELTABLE_H
