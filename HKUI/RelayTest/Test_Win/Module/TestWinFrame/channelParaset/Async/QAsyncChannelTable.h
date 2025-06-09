#ifndef QASYNCCHANNELTABLE_H
#define QASYNCCHANNELTABLE_H

#include <QTableWidget>
#include <QAction>
#include <QHeaderView>
#include "../../Define.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"
#include "../../../../../Module/BaseClass/ExBaseList.h"
#include <QTableWidgetItem>
#include <QList>
#include <QHBoxLayout>
#include <QCheckBox>

#define ASYNCTABLE_AC_COL_COUNT	5
#define ASYNCTABLE_DC_COL_COUNT	3

#define ASYNCTABLE_SELECT	0
#define ASYNCTABLE_CHNAME	1
#define ASYNCTABLE_AMP		2
#define ASYNCTABLE_ANGLE	3
#define ASYNCTABLE_FREQ		4

//2024-5-16 wuxinyi 存储临时相位频率值
struct FloatAsyncTempChData 
{
	float fAngle;
	float fHz;
};

class QAsyncChannelTable : public QTableWidget
{
	Q_OBJECT

public:
	QAsyncChannelTable(MOUDLEType moudleType, tmt_async_module * pAsyncModule,int nChCount,
					int nBeginIndex= 0, bool bDc = FALSE, QWidget *parent = 0);
	~QAsyncChannelTable(void);

	virtual void initTable();
	virtual void setColumnNum(int num);
	virtual void setProperty(bool bDCTest);
	virtual void setItemValue(int row,int col,float fv);
	virtual void UpdateTable();

public:
	void init();
	void creatTableMenu();
	void changeTableColor();
	void setTableData(tmt_async_module *pModule, int nChCount, int nBeginIndex = 0);
	void setHeaderOfTable(QStringList strheader);
	float getItemValue(int row, int col);
	void setAmpMinCoe(int nMinCoe); // 设置幅值最小值系数
	void initData();
	tmt_AsyncChannel* GetChannel();
	int GetChannelNum();
	void UpdateValidTableDatas(); // 数据有效性检查
	MOUDLEType GetModuleType();
	tmt_AsyncChannel* GetChFromName(CString strChName); // 通过通道名称查找对应的通道
	tmt_AsyncChannel* GetChFromIndex(int nIndex); // 通过通道序号查找对应的通道
	int getRowIndexByChName(const CString & strChName);
	void setAmpEDValue(float fEDValue);

	void ChangeCheckEnable( bool b );
	void IsTestInProgress( bool b );//是否为测试过程中

private:
	int m_nChCount;//显示通道数量
	int m_nBeginIndex;//通道从第n个显示
	MOUDLEType m_moudleType;//0:电压模块 1：电流模块
	int m_ColumnNum;
	int m_RowNum;
	int m_tableIndex;
	bool m_bDCTest;
	bool m_bSendUpdateParas;//zhouhj 2023.8.9 是否下发更新参数
	bool m_bIsCurrentlyTesting;  // 是否正在测试过程中

	bool m_bUsekeyPressEventExec;//是否执行键盘事件转发
	tmt_async_module *m_pAsyncModule;//异步通道

	QMenu *m_MenuAmp;
	QMenu *m_MenuPhase;
	QMenu *m_MenuFre;
	QMenu *m_MenuSelect;
	QList<QColor> m_ColorList;
	QList<QCheckBox *> m_CheckBoxList;

	QAction *m_ActUAmpED; 
	QAction *m_ActUZero;
	QAction *m_ActUEqualAmp;
	QAction *m_ActIAmp1; 
	QAction *m_ActIAmp5; 
	QAction *m_ActIAmp0; 
	QAction *m_ActIqualAmp;
	QAction *m_ActIAmpED;
	QAction *m_ActSelectAll; 
	QAction *m_ActUnSelectAll;
	QAction *m_ActToggleAll; // 反选

	float m_fEDVal;
	int m_nRowHeight;
	int m_nHeaderViewHeight;

	int m_nMinCoe;//最小值幅值系数
	QMap<int,FloatAsyncTempChData*> m_oTempSaveDataMap;//点击直流前后临时保存当前相位频率值


protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

signals:
	void sig_ChannelValueChanged();
	void sig_keyPressEventExec(int nKeyValue);//用于转发键盘快捷按键


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

	void slot_ActSelAll();
	void slot_ActUnselAll();
	void slot_ActToggleAll();

	void slot_CheckStateChange(int nState);
	void slot_tableCellClicked(int row, int column);

public:
	void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE);
	void Act_setPraseZValue(int nStart,int nEnd);
	void Act_setPrasePValue(int nSwitch,int nOffset,float fv);
	void Act_setPraseNValue(int nSwitch,int nOffset,float fv);
	void Act_setHzEqualValue(int nStart,int nEnd,float fv);

// 	QString initMaxAcV(QString str, float fAmp);
// 	QString initMaxAcI(QString str, float fAmp);
	QString initMaxHz(QString str);
	CString GetChName(MOUDLEType type,int nChIndex);


	


};
#endif // QASYNCCHANNELTABLE_H