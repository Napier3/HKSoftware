#ifndef QSttMacroParaEditViewOverCurrWidget_H
#define QSttMacroParaEditViewOverCurrWidget_H

#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "../../../Module/UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "SttMacroParaEditViewOverCurrTable.h"
#include "../../Controls/SttCheckBox.h"
#include "../../Controls/SttCheckableGroupBox.h"

class QSttMacroParaEditViewOverCurrWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewOverCurrWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewOverCurrWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_OverCurrTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void SetDatas(CDataGroup *pParas);//dingxy 20241120 切换模板获取数据
	virtual void GetDatas(CDataGroup *pParas);
	void OpenBinBoutMapXml();
	void UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);


public:
	QPushButton *m_pEstimateBtn;
	//QLineEdit *m_pOutPutTimeEdit;
	QSttCheckableGroupBox *m_pOverCurrGroupBox;
	CDataGroup m_pOverCurrDataGroup;
	QSttMacroParaEditViewOverCurrTable *m_pOverCurrTable;


protected slots:
	void slot_Estimate();
	void slot_GroupBoxtoggled(bool);
	void slot_LineEditFinished();

};


class QOverCurrEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QOverCurrEstimateDlg(CDataGroup* pParas, QWidget* parent = NULL);
	virtual ~QOverCurrEstimateDlg();

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