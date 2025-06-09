#ifndef QSttMacroParaEditViewLowCurrentWidget_H
#define QSttMacroParaEditViewLowCurrentWidget_H
#include "../Controls/SttCheckBox.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "../Controls/SttCheckableGroupBox.h"

class QSttMacroParaEditViewLowCurrentWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewLowCurrentWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewLowCurrentWidget();

	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_LowCurrentTest; }
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);

	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
public:
	CDataGroup m_pSmallBatteryDataGroup;
	QList<QLineEdit *> m_pAllLineEditList;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);
};

#endif



