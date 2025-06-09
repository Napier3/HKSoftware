#ifndef QSttMacroParaEditViewFreqFactorErrorWidget_H
#define QSttMacroParaEditViewFreqFactorErrorWidget_H
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

class QSttMacroParaEditViewFreqFactorErrorWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewFreqFactorErrorWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewFreqFactorErrorWidget();
	
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_FreqFactorTest; }
	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void setGroupBoxEnabled(QGroupBox *pGroupBox, bool enabled);
	void GetCheckBoxValue(CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID );
	QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	void GetGroupBoxCheckable( CDataGroup *pParas,QGroupBox * pGroupBox,CString strID);
	virtual void SetDatas(CDataGroup *pParas);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);

public:
	QLineEdit *m_pOutPutTimeEdit;
	QPushButton *m_pEstimateBtn;
	CDataGroup m_pFreqFactorDataGroup;
	QList<QSttCheckBox*> m_pAllCheckBoxList;
	QList<QGroupBox *> m_pGroupBoxList;
	CDvmValues *m_pMacroTestValues;


protected slots:
	void slot_Estimate();
	void slot_LineEditFinished();
	void slot_CheckBoxStateChanged(int);
	void slot_GroupBoxtoggled(bool);

};

class QFreqFactorErrorEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QFreqFactorErrorEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QFreqFactorErrorEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	void GetLineEditValue(QLineEdit * pLineEdit,const CString strID);
	QSttLineEdit *m_pFreqRelLineEdit;
	QSttLineEdit *m_pPFRelLineEdit;


protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_FreqRelEditFinished();
	void slot_PFRelEditFinished();
};

#endif