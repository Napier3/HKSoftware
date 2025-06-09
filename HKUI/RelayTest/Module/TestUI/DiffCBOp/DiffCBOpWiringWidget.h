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
	void initTableData();   //把表格数值都初始化为零
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
	CExBaseList* m_pCommonParaTest;	//参照测试项
	CSttDiffCurrCalculatTool m_oDiffCBOpCalTool;
	int m_nDisType;

	QString m_strBanlanceCoefs[2];//幅值列数据
	QString m_strWiringCoefs[6];//接线系数列数据
	QString m_strAxis[6];//标幺值列数据


	int nKph;     //是否设置平衡系数
	float m_fKph;//高压侧差动平衡系数
	float m_fKpm;//中压侧差动平衡系数
	float m_fKpl;//低压侧差动平衡系数
	float m_fHvVol;
	float m_fHvCur;
	float m_fHvCT;
	float m_fMvVol;
	float m_fMvCur;
	float m_fMvCT;
	float m_fLvVol;
	float m_fLvCur;
	float m_fLvCT;
	float m_fCur;  //电流
	float m_fHvKVA;//额定容量
	int		m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流 平台模板没有，恒为0 用以计算INOM
	float	m_fIbase;	//基准电流设定值
	BOOL	m_bMinAxis;	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
	int		m_nConnectMode;	//测试绕组之间角差（钟点数）0-11 12点、1点--11点  11 即平台的变压器接线组别
	int		m_nPhase;		//故障相别	

	int m_nAdoptWind;		   //测试绕组	0-高-低  1-高-中    2-中-低    2	用以计算KPH、KPL
	int m_nPhCorrectMode;    //校正选择		0-无校正 1-△侧校正 2-Y侧校正
	int m_nIbiasCal;         //制动方程
	int m_nWindH;            //高			0-Y 1-△ 0	用以计算KPH、KPL
	int m_nWindM;			 //中			0-Y 1-△ 0	用以计算KPH、KPL
	int m_nWindL;            //低			0-Y 1-△ 1 用以计算KPL
	int m_nK1;				//K1
	int m_nK2;				//K2	
	int m_nBalanceterms;	//平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式 
	int m_nCT;				//CT极性0-两侧指向变压器 1-一侧指向变压器
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
