#ifndef QSttMacroParaEditViewPowerAccuracyWidget_H
#define QSttMacroParaEditViewARPowerErrorWidget_H
#include "../Controls/SttCheckBox.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHeaderView>

class QSttMacroParaEditViewPowerAccuracyWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewPowerAccuracyWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewPowerAccuracyWidget();
	
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_PowerAccuracyTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void GetCheckBoxValue(CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID);
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);
	CString ProcessString( CString &str );
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void InitTable(QTableWidget *pTabWidget);
	void UpdateCheckbox(QTableWidget *pTableWidget,int row,bool bChecked);
	void UpdateCheckboxEnabled(CString strID);
	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	QLineEdit* FindLineEditID(const QList<QLineEdit*>& LineEditList, const CString& strID);
	virtual void SetDatas(CDataGroup *pParas);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void UpdateReportFile(long nPhaseNumber);

public:
	QLineEdit *m_pOutPutTimeEdit;
	QPushButton *m_pEstimateBtn;
	CDataGroup m_pARPowerErrorDataGroup;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QList<QLineEdit *> m_pAllLineEditList;
	QTableWidget *m_pTabWidget;
	CDvmValues *m_pMacroTestValues;

protected slots:
	void slot_Estimate();
	void slot_LineEditFinished();
	void slot_CheckBoxStateChanged(int);
};

class QARPowerErrorEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QARPowerErrorEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QARPowerErrorEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	QSttLineEdit *m_pPowerErrorLineEdit;

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_EditFinished();
};

#endif