#ifndef QSttMacroParaEditViewRemote_ParaRecallWidget_H
#define QSttMacroParaEditViewRemote_ParaRecallWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewParaRecallTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewParaRecallWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewParaRecallWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewParaRecallWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_ParaRecallTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	void OpenBinBoutMapXml();
	//virtual BOOL GetDatas_Reports( CSttReport *pReport,const CString &strItemID = "");
	virtual void SetDatas(CDataGroup *pParas);

public:
	CDataGroup m_pParaRecallDataGroup;
	QSttMacroParaEditViewParaRecallTable *m_pParaRecallTable;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_GroupBoxtoggled(bool);
};
#endif