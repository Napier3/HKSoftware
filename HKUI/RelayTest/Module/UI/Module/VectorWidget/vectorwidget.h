#ifndef VECTORWIDGET_H
#define VECTORWIDGET_H

#include "DiagramWidget.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include "../../QSttInfWidgetBase.h"

#define VECTOR_COMMON 0
#define VECTOR_POWERWORK 1
#define VECTOR_POWERWORK_I 2
class QVectorWidget : public QSttInfWidgetBase, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	explicit QVectorWidget(QWidget *parent=0);
	~QVectorWidget();

	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource,int VectorType);
	void setPropertyOfParaSet();

	void setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList);
	void setUIMax(float fUMax,float fIMax);
	void setUIMax();


	void updateData();
	CString getAllCurGroupStr();
	void setDCChanged(bool bDCTest);
	void setAutoChanged(bool bAutoTest);

	virtual void OnRtDataChanged();

	void TimerStart();
	void TimerStop(bool bUpdate = false);

	Diagram *m_pDiagram;
	void SetVectorMode(int nVectorType, CDataGroup *pGroup);//2023.7.28 zhangyq 设置矢量图工作模式
	void SetDatas_PowerDir(CDataGroup *pGroup); //2023.7.28 zhangyq 增加动作区域
	void SetDatas_PowerDir_I(CExBaseList *pParas); //2024.7.11 wanmj 增加功率方向国际版矢量图
public slots:
	void slot_PbnNextClicked();
	void slot_PbnPreClicked();

private:
	void initData();
	void initData(int nCurrentGroup);
	void initTableInfos();
    void initChannelData(int nStart,int nEnd,int nModuleType,int mapKey,QMap<int,QList<tmt_Channel> >& ChanelDataMap);
	LineInfo makeLineInfo(QString name,int linetype,QColor color,tmt_Channel* pChannel);
	void getGroupPosRange(int nModuleType, int nGroup,int& nStart,int& nEnd);

	virtual void timerEvent( QTimerEvent * );

	tmt_channel* m_pVOL;	
	tmt_channel* m_pCUR;	

	CExBaseList* m_pVolChList;//全部电压通道资源索引
	CExBaseList* m_pCurChList; //全部电流通道资源索引

	long m_nTimerID;
	int m_AllGroup;
	int m_NeedUGroup;
	int m_NeedIGroup;
	int m_nCurrentGroup; //当前组号

	bool m_bDCTest;
	CSttTestResourceBase *m_pVectorSttTestResource;
	int m_VectorType;

private:
	//Diagram *m_pDiagram;
	float m_fUMax,m_fIMax;

public:
	virtual void showEvent(QShowEvent *);

};

#endif // VECTORWIDGET_H
