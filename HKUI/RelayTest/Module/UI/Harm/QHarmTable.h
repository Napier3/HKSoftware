#ifndef QHARMTABLE_H
#define QHARMTABLE_H

#include <QTableWidget>
#include <QMap>
#include <QAction>
#include <QMenu>
#include "../Module/SttUIDefine.h"
#include "../../../Module/SttTest/Common/tmt_harm_test.h"
#include "../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../Module/ScrollCtrl/ScrollTableWidget.h"
#include "../Module/CommonCtrl_QT/CommonCtrlInterface.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../Controls/SettingCtrls/QSettingItem.h"

#define STT_HARM_TABLE_COL_Select            0  //第一列  选择列
#define STT_HARM_TABLE_COL_Desc              1
#define STT_HARM_TABLE_COL_Amp               2
#define STT_HARM_TABLE_COL_Phase             3
#define STT_HARM_TABLE_COL_HarmRate          4

#define STT_HARM_TABLE_ROW_DC                0  //第一行  直流输出
#define STT_HARM_TABLE_ROW_Base              1  //第二行  基波
#define STT_HARM_TABLE_ROW_Harm2             2  //第三行  2次谐波




// V500, A100
class QHarmTable : public QScrollTableWidget, public CCommonCtrlInterface
{
	Q_OBJECT

public:
	QHarmTable(QWidget *parent=NULL);
	virtual ~QHarmTable();


	tmt_Channel *m_pArrUI;//表格通道数据指针
	CSttChResource *m_pChResource;

	int m_nChIndex;

	int m_nRowHeight;
	int m_nHeaderViewHeight;

	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;

	void InitUI();
	void InitTable();
	void SetData(CSttChResource *pChResource,tmt_channel *pArrUI);

	bool addClicked(int harmNum,float fv);
	bool delClicked(int harmNum,float fv);
	void setZero(int index);

	void getSelectHarmStringList(QStringList &list);
	QStringList getSelectHarmStringList(){return m_HarmStringList;}

	//	bool SetAllSelected(bool bSel);
	bool UpdateCacuParaOneChanel(CSttChResource *pChResource,long nGroupChIndex); 

	void UpdateHeaderView();//更新通道有效值
	float UpdateCacuParaOneChanel();//计算通道有效值
	//	void setArrUIValue(bool bValue);
	void setAllAmpValue( float fAmpValue, QString strText);
	void setAllContainRateValue(float fContainRateValue, QString strText);
	void setAllPhaseValue(float fPhaseValue, QString strText);
	//void setSingleHarmValue_Add(int nIndex,  int nHarmIndex,  float fStepValue );
	//void setSingleHarmValue_Del(int nIndex,  int nHarmIndex,  float fStepValue );
	//void SetDisableRow(int nRow , bool bFlag);
	//void setAllValue_Item(float fPhaseValue, int nIndexFlag, QString strText);
	//void set_single_Value(float fValue, QString strName, int nIndexFlag );
	void SetModifyPara();
	long GetSelectCount();
	long GetHarmSelCount();//2024-9-5 wuxinyi 获取勾选的谐波次数
	void updataTableData(long  nHarmIndex = -1);

	void Disconnect();

	virtual void UpdateText(const QString &strText);
	void MenuFunc_EqualAmp(QTableWidgetItem *pItem,const QString &strValue);
	void MenuFunc_PositiveSequence(QTableWidgetItem *pItem,const QString &strValue);
	void MenuFunc_NegativeSequence(QTableWidgetItem *pItem,const QString &strValue);
	void MenuFunc_ZeroSequence(QTableWidgetItem *pItem);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	BOOL m_bRunning;

signals:
	void sig_ChanelValueChanged();
//	void sig_CheckStateChanged();
	void sig_CheckNullClicked();
	void sig_CheckAllClicekd();
	void sig_SendDataChanged();
	void sig_ChIndexChanged(int );
	void sig_WaveValueChanged();

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

private:
	//	void initTableWidget();
	void initOneCHTableData(long nGroupChIndex,long nAllChIndex);//通道1为在当前Group中的序号,参数2为在结构体中的序号,都是从0开始编号
	bool AmplitudeCellChanged( int nRow,int index );
	bool ContainRateCellChanged( int nRow,int index );
	bool PhaseCellChanged(int nRow,int index );
	void changeColor();

	bool UpdateCacuPara();


public:
	void CheckedListUnEdited(bool b);

public:
	void setSelect(int nHarmIndex,bool bSel);
	void scrollPosToItem(int nHarmIndex);

	int  m_nChangeFlag;
public:
	QStringList m_HarmStringList;

	int m_nGroupIndex;

	QTableWidgetItem *m_pCurrKeyboardItem;//弹键盘时使用的表格单元格
};

long Global_GetHarmTableMaxRowCount();

#endif // QHARMTABLE_H
