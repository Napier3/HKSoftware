#ifndef	QDIFFWIRINGWIDGET_H
#define QDIFFWIRINGWIDGET_H

#include <QWidget>
#include <QPen>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QResizeEvent>
#include <QHeaderView>
//#include "../../Module/SttTestResourceMngr/RtDataMngr/SttGlobalRtDataMngr.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "SttMultiMacroDiffParasDefine.h"
#include "../../SttTestBase/SttDiffCurrCalculatTool.h"


enum TestWind_Type{ TestWind_HightToLow = 0, TestWind_HightToMin, TestWind_MinToLow };
enum Connection_Type{ StarType = 0, TriangleType };
enum TestPhasor_type{ APhase = 0, BPhase, CPhase, ABCPhase, ABPhase, BCPhase, CAPhase };
enum Kcal_Type{ AutoCaculate = 0, ManualCaculate };
enum Correct_Type{ NONE_TYPE = 0, Correct_Trigangel_Type, Correct_Start_Type };
enum BaseCurrentSelect{ HighSideSecondaryCurrent = 0, SettingValue, AllSideCurrent };
enum SettingType{ RealValue_type = 0, MarkValue_Type };

class QDiffWiringWidget : public QWidget
{
	Q_OBJECT

public:
	QDiffWiringWidget(QWidget *parent);
	~QDiffWiringWidget();

	virtual void resizeEvent(QResizeEvent*);

	void setCommonData(CExBaseList* pCommonParaTest);
	void updateTable(CString m_pszMacroID);
	void updateTableData(CString m_pszMacroID);
	void initTableData();   //�ѱ����ֵ����ʼ��Ϊ��
	void getTableRealData(CString m_pszMacroID);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetCurrentCal(double *dId, double fIr);
protected:
	void paintEvent(QPaintEvent*);
	void drawBackground(QPainter *painter);
	void drawWiring(QPainter *painter);
	void drawCTPoint(QPainter *painter,QPointF pointf,QString strText,QColor color,bool bBellow = false);
	void drawLine(QPainter *painter,QPointF point1,QPointF point2,QColor color);

private:
	void initTable();
	void updateTableRowHightSize(int height);

	QTableWidget *m_TabelData;
	CExBaseList* m_pCommonParaTest;	//���ղ�����
	CSttDiffCurrCalculatTool m_oDiffCalTool;
	int m_nDisType;

	QString m_strBanlanceCoefs[8];//��ֵ������
	QString m_strWiringCoefs[8];//����ϵ��������
	QString m_strAxis[8];//����ֵ������
	float m_fKph;			//��ѹ��ƽ��ϵ�� 1.000	���Լ���KPH
	float m_fKpm;			//��ѹ��ƽ��ϵ�� 0.936	���Լ���KPH��KPL
	float m_fKpl;			//��ѹ��ƽ��ϵ�� 0.637	���Լ���KPL
	float m_fKjxh;//��ѹ�����ϵ��
	float m_fKjxl;//��ѹ�����ϵ��


	float m_fIe;//��׼����
	float m_fIh;
	float m_fIl;
	float m_fId;
	float m_fIr;

	int		m_nWindSide;	//��������	0-��-��  1-��-��    2-��-��    2	���Լ���KPH��KPL
	int		m_nWindH;		//��ѹ�����������ʽ 0-Y 1-�� 0	���Լ���KPH��KPL
	int		m_nWindM;		//��ѹ�����������ʽ 0-Y 1-�� 0	���Լ���KPH��KPL
	int		m_nWindL;		//��ѹ�����������ʽ 0-Y 1-�� 1 ���Լ���KPL
	int		m_nPhase;		//�������
	BOOL	m_bMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ ƽ̨ģ��û�У���Ϊ1
	int		m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ����	ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
	float	m_fIbase;	//��׼�����趨ֵ
	float	m_fIdiff;		//�����
	float	m_fIbias;		//�ƶ�����

	long	m_nSearchMode;  //����ģʽ
	int		m_nAngleMode;	//У��ѡ��	0-��У�� 1-����У�� 2-Y��У��
	int		m_nIbiasCal;	//�ƶ�����
	float	m_fFactor1;		//K1				
	float	m_fFactor2;		//K2	
	int		m_nConnectMode;	//��������֮��ǲ�ӵ�����
	BOOL	m_bCTStarPoint;	//CT����0-����ָ���ѹ�� 1-һ��ָ���ѹ��
	int		m_nJXFactor;	//ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ 
	
	float	m_fSN;				//��ѹ�������(MVA)
	float	m_fHUn;				//��ѹ����ѹ(kV)
	float	m_fMUn;				//��ѹ����ѹ(kV)
	float	m_fLUn;				//��ѹ����ѹ(kV)
	float	m_fCTPh;				//��ѹ��CTһ��ֵ(A)
	float	m_fCTSh;			//��ѹ��CT����ֵ(A)
	float	m_fCTPm;				//��ѹ��CTһ��ֵ(A)
	float	m_fCTSm;				//��ѹ��CT����ֵ(A)
	float	m_fCTPl;			//��ѹ��CTһ��ֵ(A)
	float	m_fCTSl;				//��ѹ��CT����ֵ(A)
	
};

#endif // QDIFFWIRINGWIDGET_H
