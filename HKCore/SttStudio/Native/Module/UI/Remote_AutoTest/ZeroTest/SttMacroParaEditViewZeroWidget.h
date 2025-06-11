#ifndef QSttMacroParaEditViewZeroWidget_H
#define QSttMacroParaEditViewZeroWidget_H

#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "../Module/UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "SttMacroParaEditViewZeroTable.h"
#include "../../Controls/SttCheckBox.h"
#include "../../Controls/SttCheckableGroupBox.h"

class QSttMacroParaEditViewZeroWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewZeroWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewZeroWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_ZeroTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas); //dingxy 20241120 setdatas
	void OpenBinBoutMapXml();
	void UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);


public:
	QPushButton *m_pEstimateBtn;
	QSttCheckableGroupBox *m_pZeroGroupBox;
	CDataGroup m_pZeroDataGroup;
	QSttMacroParaEditViewZeroTable *m_pZeroTable;


protected slots:
	void slot_Estimate();
	void slot_GroupBoxtoggled(bool);

};


class QZeroEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QZeroEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QZeroEstimateDlg();

public:
	void InitUI();
	CDataGroup* m_pParas;
	QList<QLineEdit*> m_pAllLineEditList;

	void GetLineEditValue(QLineEdit * pLineEdit,const CString strID);

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	void slot_EditFinished();
};

#endif
