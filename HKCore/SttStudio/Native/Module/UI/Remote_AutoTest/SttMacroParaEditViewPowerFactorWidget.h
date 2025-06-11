#ifndef QSttMacroParaEditViewPowerFactorWidget_H
#define QSttMacroParaEditViewPowerFactorWidget_H
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


class QSttMacroParaEditViewPowerFactorWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewPowerFactorWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewPowerFactorWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_PowerFactorTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	void GetCheckBoxValue(  CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID );
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void setTableWidgetEnabled( QTableWidget *pTableWidget, bool enabled );
	void UpdateCheckbox( QTableWidget *pTableWidget,int row,bool bChecked );
	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);

public:
	QLineEdit *m_pOutPutTimeEdit;
	QPushButton *m_pEstimateBtn;
	CDataGroup m_pPFDataGroup;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QTableWidget *m_pPFactorTabWidget;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_Estimate();
	void slot_LineEditFinished();
	void slot_CheckBoxStateChanged(int);
	void slot_GroupBoxtoggled(bool);
};


class QPowerFactorEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QPowerFactorEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QPowerFactorEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	QSttLineEdit *m_pPowerLineEdit;


protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_EditFinished();
};

#endif