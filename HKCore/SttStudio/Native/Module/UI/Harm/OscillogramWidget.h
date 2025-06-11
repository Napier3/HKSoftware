#ifndef OSCILLOGRAMWIDGET_H
#define OSCILLOGRAMWIDGET_H

#include <QWidget>
#include"PlotOscillogram.h"
#include"../../../Module/SttTest/Common/tmt_harm_test.h"
#include <QResizeEvent>
#include <QRadioButton>
//#include <QCheckBox>
#include "../Module/UI/Controls/SttCheckBox.h"
#include <QLabel>
#include "../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"

class QOscillogramWidget : public QWidget
{
	Q_OBJECT
public:
	explicit QOscillogramWidget(QWidget *parent = 0);
	virtual ~QOscillogramWidget();

	//void InitUI();
	void updateWidget();
	void resizeEvent(QResizeEvent * resizeEvent);

	void exportOscillogram();
	QTabWidget *m_pTabWidget;
	QList<PlotOscillogram*> getPlotList(){return m_PlotList;}
	void setArrUIVOL(tmt_channel *pArrUIVOL);
	void setArrUICUR(tmt_channel *pArrUICUR);
	void setSttTestResource(CSttTestResourceBase *pSttTestResource);

	void getSttChGroupResource_Vol();
	void getSttChGroupResource_Cur();
	int  getSttChGroupResource_VolCnt();
	int  getSttChGroupResource_CurCnt();
	int  getSttChGroupResource_Vol_ChCnt();
	int  getSttChGroupResource_Cur_ChCnt();

	void InitArrUIValue();
	void InitArrUIContent();//dingxy 20240411 初始化基波含有率
	void HarmSetZero();
	void setArrUIAddress();
	void selectDataChanged();
	int m_nGroupIndex;

	public slots:
		void slot_UpdateOscillogramV(bool);
		void slot_UpdateOscillogramI(bool);
public:
	int m_nParaSetSecondValue;				//0:显示一次值 1:显示二次值
	void SetParaSetSecondValue(int nParaSetSecondValue);

private:
	void clearPlot();
	void generateOneChData(tmt_channel *pCh, QVector<double>&vector );
	float getVMax(int index);
	float getIMax(int index);

	int m_Hz;

	QList<PlotOscillogram*>m_PlotList;
	QList<QSttCheckBox *>m_CheckBoxList;//
	tmt_channel *m_pArrUIVol;
	tmt_channel *m_pArrUICur;
	CSttTestResourceBase *m_pSttTestResource;
	CSttChGroupResource m_oGroupResourceRef_Vol;
	CSttChGroupResource m_oGroupResourceRef_Cur;
	QList<QVector<double> > m_WaveDataList_Vol;
	QList<QVector<double> > m_WaveDataList_Cur;
	QList<QSttCheckBox *>m_CheckBoxList_Vol;//
	QList<QSttCheckBox *>m_CheckBoxList_Cur;//
	QList<QVector<double> >m_WaveDataList_VolTemp;
	QList<QVector<double> >m_WaveDataList_CurTemp;
	QList<QLabel *> m_listLableVol;
	QList<QLabel *> m_listLableCur;
	int m_nVolFlag;
	int m_nCurFlag;
        QList<PlotOscillogram*> m_PlotList_Volt;//增加是为了在修改一次值/二次值时更新界面电压单位 20240830 suyang

//2024-9-16 lijunqing 优化系统程序启动的效率
protected:
	bool m_bHasInitFinished;  //是否已经初始化完成，没有初始化，不能进行操作
	virtual void showEvent(QShowEvent *event);
	
	void InitOscillogramWidget();
};

extern QFont *g_pSttGlobalFont; 

#endif