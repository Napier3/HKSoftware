#ifndef STTMACROPARAEDITVIEWTERMINALAUTOTEST_H
#define STTMACROPARAEDITVIEWTERMINALAUTOTEST_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "QTerminalTreeWidget.h"
#include "QTerminalTabWidget.h"


class QSttMacroParaEditViewTerminalAutoTest : public CSttMacroParaEditViewOriginal
{ 
	Q_OBJECT

public:
	QSttMacroParaEditViewTerminalAutoTest(QWidget *parent = 0);
	 ~QSttMacroParaEditViewTerminalAutoTest();

public:
	virtual char* GetMacroID(){ return STT_ORG_MACRO_TerminalAutoTest; }
	void InitUI();
	void InitConnection();
	void UpdateGoutData();
	void UpdateGinData();
	void updateData();
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void GetDatas(CDataGroup *pParas);
	void SetTreeWidgetItemValue(QExBaseTreeWidgetItem * pItem,CString strID,CDataGroup *pParas);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void SaveXmlParas();
	virtual void ShowReport(CDvmValues *pValues);
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);
	void UpdateEventResult(CEventResult *pCurrEventResult);

	void ClearData();//chenling20240223 清空测试数据
	void UpdateMapValue(CIecCfgChsBase *pIecCfgChsBase,CString str1,CString str2,CString srtSOE);

	CString m_strInitBinIn;
	CString	m_strEndBinIn;

	QList<long>m_GooseOutIndexList;
	QList<long>m_GooseInIndexList;



signals:
	void sig_UpdateGoutData(CExBaseObject *);
	void sig_UpdateGinData(CExBaseObject *);

public:
	QTerminalTreeWidget *m_pMuTerminalTreeWidget;
	QTerminalTabWidget *m_pMuTerminalTabWidget;

	CIecCfgGinDatas *m_pIecCfgGinDatas;
	CIecCfgGoutDatas *m_pIecCfgGoutDatas;
	CIecCfgGoutChs *m_pIecCfgGoutChs;
	CIecCfgGinChs *m_pIecCfgGinChs;
	CDataGroup m_pMUAutoTestDataGroup;
	CIecCfgGoutChs *m_pGoutMapChs;
	CIecCfgGinChs *m_pGinMapChs;

public slots:
	void slot_TreeItemSelectionChanged(QTreeWidgetItem *pItem,int colunm);
};

extern QSttMacroParaEditViewTerminalAutoTest* g_TerminalAutoTest;
#endif