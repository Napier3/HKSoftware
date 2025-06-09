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
	void initTableData();   //把表格数值都初始化为零
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
	CExBaseList* m_pCommonParaTest;	//参照测试项
	CSttDiffCurrCalculatTool m_oDiffCalTool;
	int m_nDisType;

	QString m_strBanlanceCoefs[8];//幅值列数据
	QString m_strWiringCoefs[8];//接线系数列数据
	QString m_strAxis[8];//标幺值列数据
	float m_fKph;			//高压侧差动平衡系数 1.000	用以计算KPH
	float m_fKpm;			//中压侧差动平衡系数 0.936	用以计算KPH、KPL
	float m_fKpl;			//低压侧差动平衡系数 0.637	用以计算KPL
	float m_fKjxh;//高压侧接线系数
	float m_fKjxl;//低压侧接线系数


	float m_fIe;//基准电流
	float m_fIh;
	float m_fIl;
	float m_fId;
	float m_fIr;

	int		m_nWindSide;	//测试绕组	0-高-低  1-高-中    2-中-低    2	用以计算KPH、KPL
	int		m_nWindH;		//高压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
	int		m_nWindM;		//中压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
	int		m_nWindL;		//低压侧绕组接线形式 0-Y 1-△ 1 用以计算KPL
	int		m_nPhase;		//故障相别
	BOOL	m_bMinAxis;	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
	int		m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流	平台模板没有，恒为0 用以计算INOM
	float	m_fIbase;	//基准电流设定值
	float	m_fIdiff;		//差动电流
	float	m_fIbias;		//制动电流

	long	m_nSearchMode;  //搜索模式
	int		m_nAngleMode;	//校正选择	0-无校正 1-△侧校正 2-Y侧校正
	int		m_nIbiasCal;	//制动方程
	float	m_fFactor1;		//K1				
	float	m_fFactor2;		//K2	
	int		m_nConnectMode;	//测试绕组之间角差（钟点数）
	BOOL	m_bCTStarPoint;	//CT极性0-两侧指向变压器 1-一侧指向变压器
	int		m_nJXFactor;	//平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式 
	
	float	m_fSN;				//变压器额定容量(MVA)
	float	m_fHUn;				//高压侧额定电压(kV)
	float	m_fMUn;				//中压侧额定电压(kV)
	float	m_fLUn;				//低压侧额定电压(kV)
	float	m_fCTPh;				//高压侧CT一次值(A)
	float	m_fCTSh;			//高压侧CT二次值(A)
	float	m_fCTPm;				//中压侧CT一次值(A)
	float	m_fCTSm;				//中压侧CT二次值(A)
	float	m_fCTPl;			//低压侧CT一次值(A)
	float	m_fCTSl;				//低压侧CT二次值(A)
	
};

#endif // QDIFFWIRINGWIDGET_H
