#ifndef QSttMacroParaEditViewHarmContentWidget_H
#define QSttMacroParaEditViewHarmContentWidget_H
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



class QSttMacroParaEditViewHarmContentWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewHarmContentWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewHarmContentWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_HarmContentTest; }
	void InitUI();
	void InitTable(QTableWidget *pTabWidget);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void GetCheckBoxValue( CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID );
	void UpdateHarmCheckbox(int row,bool bChecked );
	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	void UpdateHarmCheckbox();
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
protected:
	QLineEdit *m_pOutPutTimeEdit;
	QPushButton *m_pEstimateBtn;
	CDataGroup m_pHarmDataGroup;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QTableWidget *m_pHarmTabWidget;

protected slots:
	void slot_Estimate();
	void slot_LineEditFinished();
	void slot_CheckBoxStateChanged(int);
};

class QHarmContentEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QHarmContentEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QHarmContentEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	void GetLineEditValue(QLineEdit * pLineEdit,const CString strID);
	QSttLineEdit *m_pValRelLineEdit;
	QSttLineEdit *m_pPowerRelLineEdit;

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_ValRelEditFinished();
	void slot_PowerRelEditFinished();
};


#endif