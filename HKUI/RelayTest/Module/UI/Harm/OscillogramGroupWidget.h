#ifndef OSCILLOGRAMGROUPWIDGET_H
#define OSCILLOGRAMGROUPWIDGET_H

#include<QWidget>
#include<QTabWidget>
#include<QLayout>

//#include"../../Module/TestWinFrame/channelParaset/QParaSetBase.h"

#include"OscillogramWidget.h"
#define  TAB_CNT 12
class OscillogramGroupWidget :public QWidget
{
	Q_OBJECT

public:
	OscillogramGroupWidget(QWidget *parent = 0);
	~OscillogramGroupWidget();
	void initUI(CSttTestResourceBase *m_pSttTestResource);
	void UpdateUI(CSttTestResourceBase *m_pSttTestResource);

	void setArrUIVOL(tmt_channel *pArrUIVOL);
	void setArrUICUR(tmt_channel *pArrUICUR);

	void Clear();
	int GetGroupIndexFromChIndex(int nChIndex);//根据通道索引获得其组别
	void setValue();
	QOscillogramWidget *m_pOscillogramWidget[TAB_CNT];
	int m_nVolChCnt[TAB_CNT];
	int m_nCurChCnt[TAB_CNT];

	QTabWidget *m_pTabWidget;
	QGridLayout *m_pGridLayout;

	long m_nRealGroupCnt;
	long m_nGroupIndexV;
	long m_nGroupIndexI;

	tmt_channel *m_pArrUIVOL;
	tmt_channel *m_pArrUICUR;

	int m_nGroupIndex;
	int m_nVolCurIndex;
	int m_nVolCurFlag;

	CSttTestResourceBase *m_pSttTestResource;
	void setArrUIAdress();

public slots:
	void slot_ChnIndexChanged(int nIndex);
	void slot_SetToZero();
	void slot_ValueChanged(int nVolCurIndex, int nVolCurFlag);
	void slot_updateOscillogramGroup();

};

extern CFont *g_pSttGlobalFont; 

#endif