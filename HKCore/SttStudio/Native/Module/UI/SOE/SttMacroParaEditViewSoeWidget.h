#ifndef QSttMacroParaEditViewSoeWidget_H
#define QSttMacroParaEditViewSoeWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include "SttMacroParaEditViewSoeTable.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/tmt_soe_test.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttCheckBox.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../../../Module/BaseClass/QT/ExBaseListComboBox.h"

class QSttMacroParaEditViewSoeWidget : public CSttMacroParaEditViewOriginal
{
    Q_OBJECT

public:
    explicit QSttMacroParaEditViewSoeWidget(QWidget *parent = 0);
    ~QSttMacroParaEditViewSoeWidget();

	void InitUI();
	void InitConnections();
	void SetFont();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_SoeTest; }
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	CSttTestResourceBase* CreateTestResource();
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnTestResults(CDataGroup *pResults);
	virtual CString GetDefaultParaFile();
	virtual PTMT_PARAS_HEAD GetTestParas() { return &m_oSoeTest;}

	virtual void UpdateDeviceModelRef();
	virtual void AddShowSoeReports(CDvmDataset *pSoeRptDataset);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);

	void InitData();
	void InitIntervalListDatas();
	void DeleteIntervalListDatas();
	void OpenXml();
	void GetSelectObject();

public:
	QSttLineEdit *m_pPulseWidth_Edit;//脉冲宽度
	QLabel *m_pPulseWidth_Label; 
	QSttLineEdit *m_pSOE_Edit;//SOE分辨率
	QLabel *m_pSOE_Label; 
	QSttLineEdit *m_pTestCount_Edit;//测试次数
	QLabel *m_pTestCount_Label;
	QSttCheckBox *m_pLoopTestCheckBox;//闭环测试
	
	QLabel* m_pInterSelect;
	CExBaseListComboBox *m_pInterSelect_ComboBox;//间隔选择下拉框
	QPushButton* m_pBtnClearEventRecords;//清空事件记录

	QSttMacroParaEditViewSoeTable *m_pSoeFirstGrid;
	QSttMacroParaEditViewSoeTable *m_pSoeSecondGrid;

	CExBaseList m_IntervalList;         //间隔选择
	tmt_SoeTest m_oSoeTest;
	tmt_SoeParas *m_pSoeParas;
	QList<CString> m_SelectTestObjetcList;


public slots:
	void slot_EditPulseWidth();
	void slot_EditSOEResolution();
	void slot_EditTestCount();
	void slot_Check_LoopTest(bool checked);
	void slot_InterSelectIndexChanged(int nIndex);
	void slot_btn_ClearClearEventRecordsClicked();

};

extern QSttMacroParaEditViewSoeWidget* g_pSoeTest;

#endif // QSttMacroParaEditViewSoeWidget_H
