#ifndef QSttMacroParaEditViewRemote_AccuracyWidget_H
#define QSttMacroParaEditViewRemote_AccuracyWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewRemote_AccuracyTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewRemote_AccuracyWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewRemote_AccuracyWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewRemote_AccuracyWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_AccuracyTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	void OpenBinBoutMapXml();
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
	virtual void SetDatas(CDataGroup *pParas);
public:
	CDataGroup m_pAccuracyDataGroup;
	QSttCheckableGroupBox *m_pGroupBox;
	QSttMacroParaEditViewRemote_AccuracyTable *m_pAccuracyTable;

protected slots:
	void slot_GroupBoxtoggled(bool);
};

extern QSttMacroParaEditViewRemote_AccuracyWidget* g_pAccuracyWidget;

#endif