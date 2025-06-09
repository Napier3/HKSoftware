#ifndef QScanLanTesterDlg_H
#define QScanLanTesterDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QTextEdit>
#include <QNetworkInterface>
#include "ScanLanTesterGrid.h"
#include "iptypes.h"

#include "..\..\..\..\Module\SttSocket\Multicast\SttMulticastClientSocket.h"
#include "..\..\..\..\Module\SttTestAppConfig\SttTestAppCfg.h"

#include <SetupAPI.h> 
#pragma comment(lib,"setupapi.lib") 



#include <IPHlpApi.h>
#pragma comment(lib,"IPHlpApi.lib")

#define Hd_Dev_Net_Infor_Max          100

typedef struct hd_dev_nets_info
{
public:
	SP_DEVINFO_DATA m_oDevInforData[Hd_Dev_Net_Infor_Max];
	SP_PROPCHANGE_PARAMS m_oParams[Hd_Dev_Net_Infor_Max];
	CString m_strNetName[Hd_Dev_Net_Infor_Max];
	long m_nNum;
public:
	void init()
	{
		m_nNum = 0;
		SP_DEVINFO_DATA DeviceInfoData = { sizeof(SP_DEVINFO_DATA) };
		SP_PROPCHANGE_PARAMS params = { sizeof(SP_CLASSINSTALL_HEADER) };

		for (int nIndex = 0;nIndex<Hd_Dev_Net_Infor_Max;nIndex++)
		{
			m_oDevInforData[nIndex] = DeviceInfoData;
			m_oParams[nIndex] = params;
		}
//		memset(m_oDevInforData,0,sizeof(SP_DEVINFO_DATA)*Hd_Dev_Net_Infor_Max);
	}

	hd_dev_nets_info()	{init();}
}hd_DevNetsInfo; 


class QScanLanTesterDlg : public QDialog ,public CSttMulticastMsgViewInterface,public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QScanLanTesterDlg(QWidget *parent = 0,bool bUseScanLan = true);//参数2代表使用网卡扫描功能,在脱机条件下,不需要使用,特别是部分模块使用后,在机器内使用会导致软件崩溃
	~QScanLanTesterDlg();

	void initUI();
	void ReleaseUI();

	void OnStopScan();

	virtual void OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr);
	virtual void OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver vec);
	virtual void OnStopMulticastMsg();

	BOOL Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec);
	BOOL Process_Multicast_QueryServerState_ACK(CSttPpDatasDriver vec);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	void AddRecord(const CString &description );

protected:
	void InitDatas();
	virtual void timerEvent( QTimerEvent * );
	void InitLocalAdapters();
	void FreeMulticastSocket();
	BOOL ConnectMulticastServer();

	void InitEnableNetDevices();
	void EnableNetDevices(const CString&strExcludeNet,DWORD dwEnable);
	void UpdataLocalIP_Combox(QNetworkInterface &oCurNetInterface);
	CString GetNetCardDesc();
	void ReleaseOnClose();//在关闭时进行的相关操作
	BOOL ValidCurrSelIP(const CString &strIP);

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QHBoxLayout *m_pHBoxLayout1;
	QHBoxLayout *m_pHBoxLayout2;

	QLabel *m_pNetCardSel_Label;
	QComboBox *m_pNetCardSel_ComboBox;
	QLabel *m_pLocalIP_Label;
	QComboBox *m_pLocalIP_ComboBox;
	QLineEdit *m_pLocalIP_LineEdit;

	QTextEdit *m_pLogString_TextEdit;//打印信息

	QPushButton *m_pScan_PushButton;
	QPushButton *m_pModifyTesterIP_PushButton;
	QLabel *m_pServerIP_Label;
	QLineEdit *m_pServerIP_LineEdit;
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	CScanLanTesterGrid *m_pScanLanTesterGrid;
	CExBaseList m_oGridDatas;

	CSttMulticastClientSocket *m_pSttMulticastClientSocket;
	CSttTestAppCfg m_oSttTestAppCfg;

private:
	bool m_bUseScanLan;
	int m_nTimerID;
	CString m_strSelNetDesc;
//	CString m_strNetCardID;//zhouhj 20211006记录网卡的ID标识
	BOOL m_bScan;
	CDataGroup *m_pCurSelData;

	QList<QNetworkInterface> m_oNetWorkList;
	PIP_ADAPTER_INFO m_pIpAdapterInfo;
	hd_DevNetsInfo m_oDevNetsInfo;
	HDEVINFO m_hDevInfo;
	CString m_strNetCardLocalIP;//选择网卡后,记录改网卡的第一个有效IP


public:
signals:
	void sig_TesterIP_Changed();

public slots:
	void slot_ScanClicked();
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_ModifyTesterIP_Clicked();
	void slot_changeNetCardSel(int nCurComboxIndex);
	void slot_changeLocalIPAddrSel(int nCurComboxIndex);
	void slot_ModifyTesterIP(QString &strIP,const QString &strSubNetMask);
};

#endif // QScanLanTesterDlg_H
