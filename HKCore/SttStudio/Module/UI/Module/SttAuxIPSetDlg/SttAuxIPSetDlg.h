#ifndef _Stt_Aux_IP_SetDlg_H_
#define _Stt_Aux_IP_SetDlg_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include "../../Controls/SttLineEdit.h"
#include "../../../SttTestAppConfig/SttTestAppCfg.h"
#include "SttAuxIPSetGrid.h"
#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../SttCmd/SttParas.h"
#include "../../../TestClient/SttMacroTestInterface.h"
#include "../../../SttSocket/TestTerminal/SttClientSocketBase.h"




#define  MaxAuxIpCount 10

class QSttAuxIPSetDlg : public QDialog,public CTestEventBaseInterface,public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttAuxIPSetDlg(QWidget *pParent = 0);
	~QSttAuxIPSetDlg();

private:
	QLabel *m_pIP_QLabel;
	QSttLineEdit *m_pIP_QLineEdit; //Ö÷IP
	QLabel *m_pAuxIP_QLabel;
	QSttLineEdit *m_pAuxIP_QLineEdit; //¸¨ÖúIP
	QPushButton *m_pbtnOK;
	QPushButton *m_pbtnCancel;
	QPushButton *m_pbtnAdd;//Ìí¼Ó
	QPushButton *m_pbtnModify;//ÐÞ¸Ä
	QPushButton *m_pbtnDel;//É¾³ý
	QSttAuxIPSetGrid *m_pSttAuxIPSetGrid;//¸¨ÖúIP
	CSttTestAppCfg m_oSttTestAppCfg;
	CDataGroup *m_pCurSelData;
	CStringArray m_astrIP;
	CStringArray m_astrMask;
	CDataGroup m_oGridDatas;
	
	CSttTestEngineClientData *m_pClientEngine;
	CSttClientSocketBase m_oClientSocket;


private:
	void initUI();
	void initSignalSlots();
	BOOL IsIPExactness(CString strIP);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	void EnableButtons();
	void FreeClientEngine();
	BOOL CreateSttSocket();
	virtual void OnRecvSysConfigData(CSttParas *pSttParas);

signals:
//	void sig_CommCfgOK(QString &strIP,long nPort);

private slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_AddClicked();
	void slot_ModifyClicked();
	void slot_DelClicked();
	void slot_AddTesterIPAsMask(QString &strIP,const QString &strSubNetMask);
	void slot_ModifyTesterIPAsMask(QString &strIP,const QString &strSubNetMask);

};


#endif