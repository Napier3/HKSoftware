#ifndef CHANNELTABLE_H
#define CHANNELTABLE_H

#include <QTableWidget>
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
#define MACROTYPE_ManualHarm        2//�ֶ�����������ʾ��г������
#define MACROTYPE_ManualSequence    3//ͨ�������ʹ��,ֻ��ʾ��ֵ����λ
#define MACROTYPE_ManualLineVol    4//ͨ���ߵ�ѹʹ��,ֻ��ʾ��ֵ����λ
#define MACROTYPE_RemoteMeas        5


//2024-5-16 wuxinyi �洢��ʱ��λƵ��ֵ
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
	virtual void setTableData(tmt_channel *pArrUI, bool bCanUpdateTable);
	void setHarmIndex(int *pnHarmIndex);//20220819 zhouhj ���������ֶ�г������
	
	float getItemValue(int row,int col);
	void setAmpMaxMinValue(float fmax,float fmin, bool bCanUpdateTable);  //2024-9-11 lijunqing �Ż�ϵͳ����������Ч��  bool bCanUpdateTable
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
//#endif

	BOOL m_bRunning;

	int m_nParaSetSecondValue;
	void setHeaderOfTable(QStringList strheader);

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
	void sig_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue);//valueFlag=��1:��ֵ 2:��λ 3:Ƶ�ʣ�

public:
	void init();
	void creatTableMenu();
	void changeTableColor();
	void changeTableColor_LineVol();
	void changeTableColor_RemoteMeas();
	virtual void UpdateValidTableDatas();	//�����л�ʱ�������ݵ���Ч�Լ��

	QString initMaxAcV(QString);
	QString initMaxAcI(QString);
	QString initMaxHz(QString);
	QString initMaxAcV_LineVol(QString str);//�ߵ�ѹ
	QString initMaxAmp_RemoteMeas(MOUDLEType moudleType,QString str,QString strCellText);//UO/I0���ƴ��� ���źţ�UO 0-7.8/3��I0 0-4

	tmt_channel *m_pArrUI;
	int m_MacroType; //0:ͨ�� 1:״̬����
	MOUDLEType m_moudleType;//0:��ѹģ�� 1������ģ��

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
	float m_fMultAmpMax[MAX_VOLTAGE_COUNT];//add wangtao 20240828 ͨ��ʵ��-���ʸ���ÿ��ͨ���Ĺ������ƶ�Ӧ��ѹ��С
	float m_fMultAmpMin[MAX_VOLTAGE_COUNT];
	float m_fEDVal;

	int m_nRowHeight;
	int m_nHeaderViewHeight;
	CExBaseList *m_pChDatas;
	int *m_pnHarmIndex;

	QTableWidgetItem *m_pCurrKeyboardItem;//������ʱʹ�õı��Ԫ��
	QMap<int,FloatTempChData*> m_oTempSaveDataMap;//���ֱ��ǰ����ʱ���浱ǰ��λƵ��ֵ


	virtual void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE, long nCol = 1);
	virtual void Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseZValue(int nStart,int nEnd, long nCol = 2);
	virtual void Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol = 3);

	bool HasHarmParaset();
	int getChIndexByChName( const CString & strChName );
	BOOL IsDevModel();

	//�Ƚ�����֮���Ƿ����10A
	BOOL CompareMoudleIAmp(float fValue,int nRow,int nFlag);//nFlag 0��ֵ1��λ
};

#endif // CHANNELTABLE_H
