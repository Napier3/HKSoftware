#ifndef QSttMacroParaEditViewThreePhUnbalanceWidget_H
#define QSttMacroParaEditViewThreePhUnbalanceWidget_H
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
#include "../Controls/SttCheckableGroupBox.h"

class QSttMacroParaEditViewThreePhUnbalanceWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewThreePhUnbalanceWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewThreePhUnbalanceWidget();
	
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_ThreePhUnbalanceTest; }
	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void GetCheckBoxValue( CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID );
	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	void setTableWidgetEnabled( QTableWidget *pTableWidget, bool enabled );
	void UpdateFrequencyCheckbox(QTableWidget *pTableWidget,int row,bool bChecked);
	void UpdateCheckboxEnabled(CString strID);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
public:
	QLineEdit *m_pOutPutTimeEdit;
	QPushButton *m_pEstimateBtn;
	CDataGroup m_pThreePhDataGroup;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QTableWidget *m_pCurTabWidget;
	QSttCheckableGroupBox *m_pGroupBox;
protected slots:
	void slot_Estimate();
	void slot_LineEditFinished();
	void slot_CheckBoxStateChanged(int);
	void slot_GroupBoxtoggled(bool);
};

class QThreePhUnbalanceEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QThreePhUnbalanceEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QThreePhUnbalanceEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	void GetLineEditValue(QLineEdit * pLineEdit,const CString strID);
	QSttLineEdit *m_pPowerRelErrLineEdit;

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_EditFinished();
};

#endif