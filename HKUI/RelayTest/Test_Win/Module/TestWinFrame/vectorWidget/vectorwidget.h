#ifndef VECTORWIDGET_H
#define VECTORWIDGET_H

#include "DiagramWidget.h"
#include "../../CommonMethod/commonMethod.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

class VectorWidget : public Diagram, public CSttRtDataChangeEvent
{
	Q_OBJECT

public:
	VectorWidget(QWidget *parent=0);
	~VectorWidget();

	void setPropertyOfParaSet(CSttTestResourceBase *pSttTestResource,int VectorType);
	void setDispMode(int dispmode);
	void setData(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList, CSttMacroChannel* pUfCh = NULL,CSttMacroChannel* pIfCh = NULL);

	void updateData(bool bRt=false);//2024.4.15 Xuzt 新增参数表示是否为定时器调用，true则使用实时数据
	void setDCChanged(bool bDCTest);

	virtual void OnRtDataChanged();
	int m_nTimerID;

	bool m_bTimeStart;
protected:
	
	virtual void timerEvent( QTimerEvent * );

signals:
	void sig_Sequencemanutest();

public slots:
	void slot_PbnNextClicked();
	void slot_PbnPreClicked();

private:
	void initData(bool bRt=false);//2024.4.15 Xuzt 新增参数表示是否为定时器调用，true则使用实时数据
	void initData(int nCurrentGroup, bool bRt=false);//2024.4.15 Xuzt 新增参数表示是否为定时器调用，true则使用实时数据
	void initChannelData(int nStart,int nEnd,int nModuleType,int mapKey,QMap<int,QList<tmt_Channel>>& ChanelDataMap,bool bRt=false);
	LineInfo makeLineInfo(QString name,int linetype,QColor color,tmt_Channel* pChannel);
	void getGroupPosRange(int nModuleType, int nGroup,int& nStart,int& nEnd);

	tmt_channel* m_pVOL;	
	tmt_channel* m_pCUR;	

	CExBaseList* m_pVolChList;//全部电压通道资源索引
	CExBaseList* m_pCurChList; //全部电流通道资源索引
	CSttMacroChannel* m_pUfCh;//zhouyangyong 2023.12.26 新增用于故障电压、故障电流通道
	CSttMacroChannel* m_pIfCh;

// 	int m_UModuleNum;
// 	int m_IModuleNum;
// 	QList<int> m_UModultChannelNumList;
// 	QList<int> m_IModultChannelNumList;

	int m_AllGroup;
	int m_NeedUGroup;
	int m_NeedIGroup;
	int m_nCurrentGroup; //当前组号

	int m_nDispMode;	 //一次值、二次值

	bool m_bDCTest;
	CSttTestResourceBase *m_pSttTestResource;

};

#endif // VECTORWIDGET_H
