#ifndef QSttMacroParaEditViewRemote_DualPositionWidget_H
#define QSttMacroParaEditViewRemote_DualPositionWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewDualPositionTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewDualPositionWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewDualPositionWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewDualPositionWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_DualPositionTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void OpenBinBoutMapXml();

public:
	QSttCheckableGroupBox *m_pGroupBox;
	CDataGroup m_pDualPositionDataGroup;
	QSttMacroParaEditViewDualPositionTable *m_pDualPositionTable;


protected slots:
	void slot_GroupBoxtoggled(bool);
};
#endif