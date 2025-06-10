#ifndef VECTORWIDGET_H
#define VECTORWIDGET_H

#include "DiagramWidget.h"
#include "../Module/SttTest/Common/tmt_common_def.h"
#include "../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include "../../QSttInfWidgetBase.h"

#define VECTOR_COMMON 0
#define VECTOR_POWERWORK 1
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
	void SetVectorMode(int nVectorType, CDataGroup *pGroup);//2023.7.28 zhangyq ����ʸ��ͼ����ģʽ
	void SetDatas_PowerDir(CDataGroup *pGroup); //2023.7.28 zhangyq ���Ӷ�������
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

	CExBaseList* m_pVolChList;//ȫ����ѹͨ����Դ����
	CExBaseList* m_pCurChList; //ȫ������ͨ����Դ����

	long m_nTimerID;
	int m_AllGroup;
	int m_NeedUGroup;
	int m_NeedIGroup;
	int m_nCurrentGroup; //��ǰ���

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
