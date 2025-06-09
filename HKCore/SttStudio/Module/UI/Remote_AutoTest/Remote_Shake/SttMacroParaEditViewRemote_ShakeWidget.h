#ifndef QSttMacroParaEditViewRemote_ShakeWidget_H
#define QSttMacroParaEditViewRemote_ShakeWidget_H
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "SttMacroParaEditViewRemote_ShakeTable.h"
#include "../../Controls/SttCheckableGroupBox.h"
class QSttMacroParaEditViewRemote_ShakeWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	 QSttMacroParaEditViewRemote_ShakeWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewRemote_ShakeWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_AntiShakeTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);//dingxy 20241120
	void OpenBinBoutMapXml();
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);


public:
	CDataGroup m_pShakeDataGroup;
	//CDataGroup m_oBinBoutDataGroup;
	QSttMacroParaEditViewRemote_ShakeTable *m_pShakeTable;
	QSttCheckableGroupBox *m_pGroupBox;
protected slots:
	void slot_GroupBoxtoggled(bool);

};
#endif