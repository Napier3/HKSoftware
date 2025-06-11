#ifndef QSttMacroParaEditViewPriorityDeliverWidget_H
#define QSttMacroParaEditViewPriorityDeliverWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewPriorityDeliverTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewPriorityDeliverWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewPriorityDeliverWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewPriorityDeliverWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_PriorityDeliveryTest; }
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
	CDataGroup m_pDeliverDataGroup;
	QSttCheckableGroupBox *m_pGroupBox;
	QSttMacroParaEditViewPriorityDeliverTable *m_pDeliverTable;

protected slots:
	void slot_GroupBoxtoggled(bool);
};
#endif