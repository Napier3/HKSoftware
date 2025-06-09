#ifndef	QDIFFCBOPWIRINGWIDGET_H
#define QDIFFCBOPWIRINGWIDGET_H

#include <QWidget>
#include <QPen>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QResizeEvent>
#include <QHeaderView>
//#include "../../Module/SttTestResourceMngr/RtDataMngr/SttGlobalRtDataMngr.h"
#include "../../SttTestResourceMngr\SttTestResourceMngr.h"
#include "SttMultiMacroDiffCBOpParasDefine.h"
#include "../../SttTestBase/SttDiffCurrCalculatTool.h"




class QDiffCBOpWiringWidget : public QWidget
{
	Q_OBJECT

public:
	QDiffCBOpWiringWidget(QWidget *parent);
	~QDiffCBOpWiringWidget();

	virtual void resizeEvent(QResizeEvent*);

	void setCommonData(CExBaseList* pCommonParaTest);
	void updateTable(CString m_pszMacroID);
	void updateTableData(CString m_pszMacroID);
	void initTableData();   //�ѱ����ֵ����ʼ��Ϊ��
	void getTableRealData(CString m_pszMacroID);
	void SetValueToPage(CSttMacroTestParaData *pData);
protected:
	void paintEvent(QPaintEvent*);
	void drawBackground(QPainter *painter);
	void drawWiring(QPainter *painter);
	void drawCTPoint(QPainter *painter, QPointF pointf, QString strText, QColor color, bool bBellow = false);
	void drawLine(QPainter *painter, QPointF point1, QPointF point2, QColor color);

private:
	void initTable();
	void updateTableRowHightSize(int height);

	QTableWidget *m_TabelData;
	CExBaseList* m_pCommonParaTest;	//���ղ�����
	CSttDiffCurrCalculatTool m_oDiffCBOpCalTool;
	int m_nDisType;

	QString m_strBanlanceCoefs[2];//��ֵ������
	QString m_strWiringCoefs[6];//����ϵ��������
	QString m_strAxis[6];//����ֵ������


	int nKph;     //�Ƿ�����ƽ��ϵ��
	float m_fKph;//��ѹ��ƽ��ϵ��
	float m_fKpm;//��ѹ��ƽ��ϵ��
	float m_fKpl;//��ѹ��ƽ��ϵ��
	float m_fHvVol;
	float m_fHvCur;
	float m_fHvCT;
	float m_fMvVol;
	float m_fMvCur;
	float m_fMvCT;
	float m_fLvVol;
	float m_fLvCur;
	float m_fLvCT;
	float m_fCur;  //����
	float m_fHvKVA;//�����
	int		m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ���� ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
	float	m_fIbase;	//��׼�����趨ֵ
	BOOL	m_bMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ ƽ̨ģ��û�У���Ϊ1
	int		m_nConnectMode;	//��������֮��ǲ�ӵ�����0-11 12�㡢1��--11��  11 ��ƽ̨�ı�ѹ���������
	int		m_nPhase;		//�������	

	int m_nAdoptWind;		   //��������	0-��-��  1-��-��    2-��-��    2	���Լ���KPH��KPL
	int m_nPhCorrectMode;    //У��ѡ��		0-��У�� 1-����У�� 2-Y��У��
	int m_nIbiasCal;         //�ƶ�����
	int m_nWindH;            //��			0-Y 1-�� 0	���Լ���KPH��KPL
	int m_nWindM;			 //��			0-Y 1-�� 0	���Լ���KPH��KPL
	int m_nWindL;            //��			0-Y 1-�� 1 ���Լ���KPL
	int m_nK1;				//K1
	int m_nK2;				//K2	
	int m_nBalanceterms;	//ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ 
	int m_nCT;				//CT����0-����ָ���ѹ�� 1-һ��ָ���ѹ��
	int m_nKcal;

	enum TestWind_Type{ TestWind_HightToLow = 0, TestWind_HightToMin, TestWind_MinToLow };
	enum Connection_Type{ StarType = 0, TriangleType };
	enum TestPhasor_type{ APhase = 0, BPhase, CPhase, ABCPhase, ABPhase, BCPhase, CAPhase };
	enum Kcal_Type{ AutoCaculate = 0, ManualCaculate };
	enum Correct_Type{ NONE_TYPE = 0, Correct_Trigangel_Type, Correct_Start_Type };
	enum BaseCurrentSelect{ HighSideSecondaryCurrent = 0, SettingValue, AllSideCurrent };
	enum SettingType{ RealValue_type = 0, MarkValue_Type };
};

#endif
