#ifndef QSttMacroParaEditViewRemote_TimeSyncWidget_H
#define QSttMacroParaEditViewRemote_TimeSyncWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewTimeSyncTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewTimeSyncWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewTimeSyncWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewTimeSyncWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_TimeSyncTest; }
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
	CDataGroup m_pTimeSyncDataGroup;
	QSttMacroParaEditViewTimeSyncTable *m_pTimeSyncTable;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_GroupBoxtoggled(bool);
};
#endif