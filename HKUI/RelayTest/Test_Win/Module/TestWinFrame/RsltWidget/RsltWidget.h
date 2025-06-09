#ifndef QRSLTWIDGET_H
#define QRSLTWIDGET_H

#include <QWidget>
#include <QTabWidget>

#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>

#include "../../Module/SttTest/Common/Impedance/tmt_impedance_test.h"
#include "../../Module/SttCmd/SttCmdDefineGlobal.h"
#include "../../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

#include "RsltExprMngr.h"

#include "../SysParasSetDlg/QValueComboBox.h"
#include "../SysParasSetDlg/QFloatLineEdit.h"

#include "../../Module/SttTest/Common/tmt_test_mngr.h"

extern CTmtTestRsltExprImp g_oTmtTestRsltExprImp;
#define  JDG_COUNT 20
#define  MAX_EXPR_CNT  32
class QRsltWidget : public QWidget/*, public CExprVariableFind*/
{
	Q_OBJECT

public:
	QRsltWidget(PTMT_PARAS_HEAD pPTMT_PARAS_HEAD,   QWidget *parent = 0);
	~QRsltWidget();

public:
	void InitUI();
	void Reset();
	void SetParasHead(PTMT_PARAS_HEAD pPTMT_PARAS_HEAD);
	void SetUnit(int nIndex, QString strUnit[]);
	int    GetMaxCountExpr(CDataGroup *pList);

	void startInit();	//yyj add 
	void stopInit();	//yyj add

public:
	//当前选中的测试点
	PTMT_PARAS_HEAD  m_pTmt_Paras_Head;


	 /*
	 //显示规则：
		表达式标题      表达式下拉框      数据标题（ExprValueID在m_strRsltDataID中定义的）   数据值
		。。。。。
		其他数据m_strRsltDataID中不在m_strExprValueID的数据
	 */


	QList <QLabel*> m_listName;
	QList <QLabel*> m_listRsltName;

	QList <QComboBox*> m_listExpr;
	QList <QFloatLineEdit*> m_listRsltValue;
	
public:
	QGridLayout *m_MainLayout;

	QFloatLineEdit *m_editFaultTime;                       //
	QFloatLineEdit *m_editPreFaultTime;                 //
	QFloatLineEdit *m_editPostFaultTime;               //

	QLabel *label_FaultTime;
	QLabel *label_PreFaultTime;
	QLabel *label_PostFaultTime;
	QString m_strUnit[MAX_EXPR_CNT];
	QList < QString > m_listUnit;

	public slots:
		void slot_currentIndex(int);



};

#endif // QRSLTWIDGET_H
