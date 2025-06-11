#ifndef QSttMacroParaEditViewDeadZeroDriftWidget_H
#define QSttMacroParaEditViewDeadZeroDriftWidget_H

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

class QSttMacroParaEditViewDeadZeroDriftWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewDeadZeroDriftWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewDeadZeroDriftWidget();

	void InitUI();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_DeadZeroDriftTest; }
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void SaveParasXml();
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);
	void GetGroupBoxValue(CDataGroup *pParas,QSttCheckableGroupBox * pGroupBox,const CString strID);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);

public:
	CDataGroup m_pDeadZeroDriftDataGroup;
	QList<QLineEdit *> m_pAllLineEditList;
	QList<QSttCheckableGroupBox *> m_pGroupBoxList;


protected slots:

	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);

};

#endif