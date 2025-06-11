#ifndef QSttMacroParaEditViewInputVolWidget_H
#define QSttMacroParaEditViewInputVolWidget_H
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


class QSttMacroParaEditViewInputVolWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewInputVolWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewInputVolWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_InputVolTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	void GetCheckBoxValue( CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID );
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
	CDataGroup m_pDataGroup;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QTableWidget *m_pTabWidget;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_Estimate();
	void slot_LineEditFinished();
	void slot_CheckBoxStateChanged(int);
	void slot_GroupBoxtoggled(bool);
};


class QInputVolEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QInputVolEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QInputVolEstimateDlg();

public:
	void InitUI();
	void GetLineEditValue(QLineEdit * pLineEdit,const CString strID);

	CDataGroup* m_pParas;
	QSttLineEdit *m_pVolLineEdit;

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_EditFinished();
};

#endif