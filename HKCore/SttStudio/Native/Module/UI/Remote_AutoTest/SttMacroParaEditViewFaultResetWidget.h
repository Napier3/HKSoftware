#ifndef QSttMacroParaEditViewFaultResetWidget_H
#define QSttMacroParaEditViewFaultResetWidget_H
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QGridLayout>
#include "../Controls/SttCheckableGroupBox.h"


class QSttMacroParaEditViewFaultResetWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewFaultResetWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewFaultResetWidget();

	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_FaultResetTest; }
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);

	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2);

public:
	CDataGroup m_pFaultResetDataGroup;
	QList<QLineEdit *> m_pAllLineEditList;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);

};

#endif



