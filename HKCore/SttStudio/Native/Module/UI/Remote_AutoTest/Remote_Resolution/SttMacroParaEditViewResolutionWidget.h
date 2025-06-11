#ifndef QSttMacroParaEditViewRemote_ResolutionWidget_H
#define QSttMacroParaEditViewRemote_ResolutionWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewResolutionTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewResolutionWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewResolutionWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewResolutionWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_ResolutionTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void OpenBinBoutMapXml();
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);

public:
	CDataGroup m_pResolutionDataGroup;
	QSttMacroParaEditViewResolutionTable *m_pResolutionTable;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_GroupBoxtoggled(bool);
};
#endif