#ifndef STTMACROPARAEDITVIEWMUAUTOTEST_H
#define STTMACROPARAEDITVIEWMUAUTOTEST_H

#include "SttMacroParaEditViewMuTreeWidget.h"
#include "SttMacroParaEditViewOtherSetDlg.h"

#define	 STT_MUAUTOTEST_LINEDIT_VOL_LPTRATIO 				 _T("PTRatio1")
#define	 STT_MUAUTOTEST_LINEDIT_VOL_RPTRATIO 				 _T("PTRatio2")
#define	 STT_MUAUTOTEST_LINEDIT_CUR_LCTRATIO 				 _T("CTRatio1")
#define	 STT_MUAUTOTEST_LINEDIT_CUR_RCTRATIO 				 _T("CTRatio2")
#define	 STT_MUAUTOTEST_LINEDIT_TESTNUMBER                   _T("TestCount")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER100	     _T("Rate_100_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER002	     _T("Rate_002_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER005	     _T("Rate_005_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER010	     _T("Rate_010_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER050	     _T("Rate_050_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER080	     _T("Rate_080_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER120	     _T("Rate_120_Check")
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST_PER150	     _T("Rate_150_Check")

#define	 STT_MUAUTOTEST_TREEITEM_AUTOMATEDTEST           	 _T("AutomatedTest_Check")    		  //合并单元自动测试
#define	 STT_MUAUTOTEST_TREEITEM_ACCURACYTEST           	 _T("AccuracyTest_Check")    		  //精度测试
#define	 STT_MUAUTOTEST_TREEITEM_TIMETEST           	     _T("TimeTest_Check")    			  //时间测试
#define	 STT_MUAUTOTEST_TREEITEM_ZEROTEST           	     _T("ZeroDrift_Check")    			  //零漂测试
#define	 STT_MUAUTOTEST_TREEITEM_WAVETEST           	     _T("WaveTest_Check")                 //首周波测试
#define	 STT_MUAUTOTEST_TREEITEM_TIME_PUNACCURACY   	     _T("PunctAccur_Check")              //守时精度
#define	 STT_MUAUTOTEST_TREEITEM_TIME_TIMEACCURACY  	     _T("TimingAccur_Check")			  //对时精度


class QSttMacroParaEditViewMuAutoTest : public CSttMacroParaEditViewOriginal
{ 
	Q_OBJECT

public:
	QSttMacroParaEditViewMuAutoTest(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewMuAutoTest();

	QHBoxLayout* m_pMainVLayout;
	QVBoxLayout* m_pMUAutoParaSet;
	QVBoxLayout* m_pMuAUtoParaDisplay;
	QHBoxLayout* m_pTreeLayout;
	QHBoxLayout* m_pParaLayout;
	QHBoxLayout* m_pButtonLayout;
	QHBoxLayout* m_pParaKidLayout_1;
	QHBoxLayout* m_pParaKidLayout_2;
	QHBoxLayout* m_pParaKidLayout_3;
	QHBoxLayout* m_pParaKidLayout_4;
    QVBoxLayout* m_pParaKidLayout;
	QPushButton* m_pSelectall;
	QPushButton* m_pClear;
	QPushButton* m_pOtherparameters;
	QPushButton* m_pRefresh;
    QGroupBox* m_pParameterSet;
	QLabel* m_pPTRatio;
	QLabel* m_pCTRatio;
	QLabel* m_pNumTests;
	QLabel* m_pPTSLash;
	QLabel* m_pCTSLash;
	QFloatLineEdit* m_pVolEdit_0;
	QFloatLineEdit* m_pVolEdit_1;
	QFloatLineEdit* m_pCurEdit_0;
	QFloatLineEdit* m_pCurEdit_1;
	QLongLineEdit* m_pTestEdit;

	QSttMacroParaEditViewMuTreeWidget* m_pAotuTestTree;
	CDataGroup m_oMUAutoTestDataGroup;
	int m_nBCodeMode,m_nIecFormatMeas;

public:	

	void InitUI();
    void InitConnection();
    void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);
	void InitEditCoverage();
	void SetTreeWidgetItemValue(QExBaseTreeWidgetItem * pItem,CString strID,CDataGroup *pParas);
	void CheckChildItems(QTreeWidgetItem* item, Qt::CheckState Ischecked);
	void StartInit();
	void StopInit();
	void UpdateTreeWidgetItem(CDataGroup *pParas);
	void SetMUAutoTestWidgetFont();


    virtual CSttTestResourceBase* CreateTestResource();
	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_MUAutoTest; }
	virtual void ShowReport(CDvmValues *pValues);
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	virtual bool PrepStartTest();


public slots:

	void slot_Otherparameters();
	void slot_AllSelected();
	void slot_Clear();
	void slot_Refresh();
	void slot_TreeItemSelectionChanged(QTreeWidgetItem *pItem,int colunm);
    void slot_PTCTLineEditChanged();
	void slot_FloatLineEditChanged();
	void slot_LongLineEditChanged();
	void slot_handleItemChanged(QTreeWidgetItem* item, int column);

	
};

#endif