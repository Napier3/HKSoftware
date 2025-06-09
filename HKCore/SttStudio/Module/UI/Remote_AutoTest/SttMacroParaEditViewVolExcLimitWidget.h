#ifndef QSttMacroParaEditViewVolExcLimitWidget_H
#define QSttMacroParaEditViewVolExcLimitWidget_H
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "../Controls/SttCheckableGroupBox.h"


class QSttMacroParaEditViewVolExcLimitWidget: public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewVolExcLimitWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewVolExcLimitWidget();


	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_VolExcLimitTest; }
	void InitUI();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	void SaveParasXml();
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID);
	void GetGroupBoxValue(CDataGroup *pParas,QSttCheckableGroupBox * pGroupBox,const CString strID);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void setGroupBoxEnabled(QGroupBox *pGroupBox, bool enabled);
	//QSttCheckBox* FindCheckBoxByID(const QList<QSttCheckBox*>& checkBoxList, const CString& strID);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	void OpenBinBoutMapXml();
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);

protected:
	CDataGroup m_pDataGroup;
	QList<QLineEdit *> m_pAllLineEditList;
	QList<QSttCheckableGroupBox *> m_pGroupBoxList;


protected slots:
	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);

};

#endif