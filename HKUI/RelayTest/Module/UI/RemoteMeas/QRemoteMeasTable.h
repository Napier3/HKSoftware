#ifndef QREMOTEMEASTABLE_H
#define QREMOTEMEASTABLE_H

#include <QTableWidget>
#include <QMap>
#include <QAction>
#include <QMenu>
#include <QComboBox>
#include "../Module/SttUIDefine.h"
#include "../../../Module/SttTest/Common/tmt_manu_test.h"
#include "../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"

#define  STT_RemoteMeas_Dataset_ID     "Ain"    //遥测
#define  STT_RemoteMeas_Data_ID_Ua     "Ua"    
#define  STT_RemoteMeas_Data_ID_Ub     "Ub"  
#define  STT_RemoteMeas_Data_ID_Uc     "Uc"    
#define  STT_RemoteMeas_Data_ID_U0     "U0"    
#define  STT_RemoteMeas_Data_ID_Ia     "Ia"    
#define  STT_RemoteMeas_Data_ID_Ib     "Ib"   
#define  STT_RemoteMeas_Data_ID_Ic     "Ic"    
#define  STT_RemoteMeas_Data_ID_I0     "I0"    
#define  STT_RemoteMeas_Data_ID_Freq             "f"    
#define  STT_RemoteMeas_Data_ID_ActivePower      "p"    
#define  STT_RemoteMeas_Data_ID_ReactivePower    "q"    

class QComboBoxChannelDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	QComboBoxChannelDelegate(QObject *parent=NULL);
	~QComboBoxChannelDelegate();

	virtual  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,const QModelIndex & index) const;

private slots:
	void commitAndCloseEditor();
};

class QRemoteMeasTable : public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QRemoteMeasTable(CExBaseList *pChVList,CExBaseList *pChIList,tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR,QWidget *parent=NULL);
	virtual ~QRemoteMeasTable();

	int m_nRowHeight;
	int m_nHeaderViewHeight;

	int m_ModuleType;		//0:电压模块 1：电流模块
	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;
	float m_fAmpMax;
	float m_fAmpMin;
	CExBaseList *m_pChVDatas;
	CExBaseList *m_pChIDatas;
	QList<QColor> m_ColorList;
	bool m_bDC;

	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格

	void InitUI();
	void changeColor();
	virtual void UpdateValidTableDatas();	//量程切换时所有数据的有效性检查
	int getTableHeight();
	int getTableWidth();

	void InitTable();
	virtual void setTableData(tmt_channel *pArrUIVOL,tmt_channel *pArrUICUR);
	virtual void UpdateTable();
	QString initMaxAc(QString);
	void CalValueTable(CString strChName,long nChIndex,float fRate1,float fRate2);

	virtual void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE, long nCol = 1);
	virtual void Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseZValue(int nStart,int nEnd, long nCol = 2);
	virtual void Act_setHzEqualValue(int nStart,int nEnd,float fv, long nCol = 3);

	virtual void UpdateText(const QString &strText);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	BOOL m_bRunning;

	QComboBoxChannelDelegate *m_pComboBoxChannelDelegate;

signals:
	void sig_ChannelRemoteValueChanged(int channelNum,int valueFlag,float datavalue);
	void sig_updataParas();

private slots:
	void slot_OnCellChanged(int ,int);
	void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);

	void slot_UpdataVamp(QString strValue);
	void slot_UpdataIamp(QString strValue);
	void slot_UpdataHzamp(QString strValue);
	void slot_UpdataZX(QString strValue);//正序
	void slot_UpdataFX(QString strValue);//负序
	void slot_UpdataLX();//零序

	void slot_ActUEqualAmpClicked();
	void slot_ActIqualAmpClicked();
	void slot_ActHzEqualClicked();
	void slot_ActPhasePClicked();
	void slot_ActPhaseNClicked();
	void slot_ActPhaseZClicked();
	void slot_ComboBoxChannelChanged(QWidget* editor);
	void slot_ChannelAmpValueChanged(int nIndex,float fAmpValue);

};

#endif // QREMOTEMEASTABLE_H
