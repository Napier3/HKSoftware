#ifndef QSttMacroParaEditViewRemoteWidget_H
#define QSttMacroParaEditViewRemoteWidget_H
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../Controls/SttCheckableGroupBox.h"

class QSttMacroParaEditViewRemoteWidget : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewRemoteWidget(QWidget *parent = 0);
	~QSttMacroParaEditViewRemoteWidget();

	virtual char* GetMacroID(){ return STT_ORG_MACRO_Remote_Test; }
	void InitUI();
	void InitTable();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateRemoteBoutData(CDataGroup *pParas);
	void SaveParasXml();
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);

	void InitData(CDataGroup *pData);
	void GetTableWidgetItemValue( QTableWidgetItem * pItem,const CString strID);
	void OpenBinBoutMapXml();

public:
	CDataGroup m_pRemoteDataGroup;
	QTableWidget *m_pRemoteTable;
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
	QSttCheckableGroupBox *m_pGroupBox;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_GroupBoxtoggled(bool);
};
#endif