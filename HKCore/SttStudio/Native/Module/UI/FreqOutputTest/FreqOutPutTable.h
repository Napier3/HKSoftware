#ifndef FreqOutPutTable_H
#define FreqOutPutTable_H

#include <QWidget>
#include "../Module/ChannelParaSet/channeltable.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../SttTest/Common/Distribution/tmt_freqoutput_test.h"
#include "../../SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../Module/ChannelParaSet/QParaSetBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"


class QFreqOutPutTable : public QChannelTable
{
	Q_OBJECT
public:
	QFreqOutPutTable(MOUDLEType moudleType, CExBaseList *pChList,
		tmt_FreqOutputChannel *pArrUI, QWidget *parent = NULL);

	virtual ~QFreqOutPutTable();
public:
	virtual void initTable();
	virtual void UpdateTable();
	virtual void Act_setUIAmpValue(QTableWidgetItem *pItem,float fVal,bool bAll=TRUE, long nCol = 1);
	virtual void Act_setPrasePValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseNValue(int nSwitch,int nOffset,float fv, long nCol = 2);
	virtual void Act_setPraseZValue(int nStart,int nEnd, long nCol = 2);
	virtual void mousePressEvent(QMouseEvent *);

private:
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
	tmt_FreqOutputChannel *m_pArrUI;

protected slots:
	virtual void slot_OnCellChanged(int row,int col);
	virtual void slot_TableShowMent(QPoint pos);
	virtual void slot_OnItemDoubleClicked(QTableWidgetItem *pItem);
};


class QFreqOutPutWidget : public QParaSetBase
{
	Q_OBJECT

public:
	QFreqOutPutWidget(QWidget *parent = 0);
	~QFreqOutPutWidget();

	virtual void setPropertyOfParaSet(plugin_type type,CSttTestResourceBase *pSttTestResource
		,tmt_FreqOutputChannel *pArrUIVOL,tmt_FreqOutputChannel *pArrUICUR,bool bDC = false);

	void setData(tmt_FreqOutputChannel *pArrUIVOL,tmt_FreqOutputChannel *pArrUICUR);
	virtual void setMaxMinAndEDVal(bool bCanUpdateTable=true);
	virtual void setIAmpMaxMinValue(bool bCanUpdateTable);
	void setUAmpMaxMinValue(bool bCanUpdateTable);
	virtual void setIAmpEDValue(float fIEDVal);
	virtual void setUAmpEDValue(float fUEDVal);
	virtual void startInit(bool bEnable=TRUE);
	virtual void stopInit(bool bEnable=TRUE);

public:
	void InitUI();
	virtual void initUI(CSttTestResourceBase *pSttTestResource);
	virtual void initData();
	virtual void Release();
	void setMacroType(int type){ m_MacroType = type;}
	tmt_FreqOutputChannel *m_pArrUIVOL;
	tmt_FreqOutputChannel *m_pArrUICUR;

	CSttTestResourceBase *m_pParaSetSttTestResource;
	plugin_type m_type;
	QList<QFreqOutPutTable *> m_ICHannelTableList;
	QList<QFreqOutPutTable *> m_UCHannelTableList;

	int m_MacroType;
	bool m_bDC;
	QGroupBox *m_pUIGroupBox;
	QScrollArea *m_pIScrollArea;
	QWidget *m_pIWidget;
	QGridLayout *m_pIGridLayout;
	QScrollArea *m_pUScrollArea;
	QWidget *m_pUWidget;
	QGridLayout *m_pUGridLayout;

public:
	void UpdateTables();
	void UpdateValidTableDatas();

signals:
	void sig_updataParas(int channelNum,int valueFlag,float datavalue);

protected slots:
	//void slot_ChannelValueChanged(MOUDLEType moudleType,int channelNum,int valueFlag,float datavalue);//valueFlag=（1:幅值 2:相位 3:频率）

};
#endif 
