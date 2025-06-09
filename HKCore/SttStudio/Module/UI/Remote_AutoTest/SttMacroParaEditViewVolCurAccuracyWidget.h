#ifndef QSttMacroParaEditViewAccuracyWidget_H
#define QSttMacroParaEditViewAccuracyWidget_H
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


class QSttMacroParaEditViewVolCurAccuracyWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewVolCurAccuracyWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewVolCurAccuracyWidget();

	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_VolCurAccuracyTest; }
	void GetCheckBoxValue( CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID);
	void GetLineEditValue( CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);
	void GetGroupBoxCheckable( CDataGroup *pParas,QGroupBox * pGroupBox,CString strID);

	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	CString ProcessString( CString &str );
	void UpdateLineEditEnable(QSttCheckBox * pCheckBox,QLineEdit * pLineEdit);
	//void setGroupBoxEnabled(QGroupBox *pGroupBox, bool enabled);
	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	QLineEdit* FindLineEditID(const QList<QLineEdit*>& LineEditList, const CString& strID);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);


public:
	CDataGroup m_pVolCurErrorDataGroup;
	QPushButton *m_pEstimateBtn;
	QLineEdit *m_pOutPutTimeEdit;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QList<QLineEdit *> m_pAllLineEditList;
	QList<QGroupBox *> m_pGroupBoxList;
	CDvmValues *m_pMacroTestValues;

protected slots:
	void slot_Estimate();
	void slot_CheckBoxStateChanged(int);
	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);

};

class QVolCurErrorEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QVolCurErrorEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QVolCurErrorEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	QSttLineEdit *m_pVolCurErrorLineEdit;


protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_EditFinished();
};

#endif



