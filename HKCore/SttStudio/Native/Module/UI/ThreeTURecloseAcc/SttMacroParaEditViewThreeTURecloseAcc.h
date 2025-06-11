#ifndef STTMACROPARAEDITVIEWTHREETURECLOSEACC_H
#define STTMACROPARAEDITVIEWTHREETURECLOSEACC_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "ThreeRecloseAccTable.h"

class QSttMacroParaEditViewThreeTURecloseAcc : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewThreeTURecloseAcc(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewThreeTURecloseAcc();

private:
	void InitUI();
	void InitConnect();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_ThreeTURecloseAccTest; }
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void GetLineEditValue( CDataGroup *pParas,QSttLineEdit * pLineEdit,const CString strID);


private:
	QThreeRecloseAccTable *m_pThreeRecAccTable;
	QPushButton *m_pEstimateBtn;
	QPushButton *m_pCommonParasBtn;
	
	QSttLineEdit *m_pShortCurEdit;
	QSttLineEdit *m_pShortTimeEdit;
	QSttLineEdit *m_pAccCurEdit;
	QSttLineEdit *m_pAccTimeEdit;
	QSttLineEdit *m_pFaultTimeEdit;
	QSttLineEdit *m_pFaultMarginTimeEdit;
	QLabel *m_pAccCurLabel;
	QLabel *m_pAccTimeLabel;
	
	QList<QSttLineEdit *> m_pAllLineEditList;
	CDataGroup m_pThreeTURecloseAccData;
	bool m_bAfterAccIsChecked;


	
protected slots:
	void slot_EstimateBtnClicked();
	void slot_CommonParasBtnClicked();
	void slot_lne_ShortCurChanged();
	void slot_lne_ShortTimeChanged();
	void slot_lne_AccCurChanged();
	void slot_lne_AccTimeChanged();
	void slot_lne_FaultTimeChanged();
	void slot_lne_FaultMarginTimeChanged();
	void slot_Grp_AftAccGroupEnabled(bool bChecked);
};
extern QSttMacroParaEditViewThreeTURecloseAcc* g_pThreeTURecloseAcc;
#endif