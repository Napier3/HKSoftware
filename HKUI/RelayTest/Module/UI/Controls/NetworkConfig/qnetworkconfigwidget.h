#ifndef QNETWORKConfigWIDGET_H
#define QNETWORKConfigWIDGET_H

#include "qnetworkiptable.h"
#include <QDialog>
#include <QTimerEvent>
#include <QNetworkInterface>

#include "../../../SttSocket/Multicast/SttMulticastClientSocket.h"
#include "../../../SttSocket/Multicast/SttGlobalMulticastDef.h"
#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../SttTestAppConfig/SttTestAppCfg.h"
#include "../../../API/NetworkInterface.h"

#ifdef _PSX_QT_LINUX_


#else

#include "iptypes.h"

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

#endif



namespace Ui {
class QNetworkConfigWidget;
}

class QNetworkConfigWidget : public QDialog ,public CSttMulticastMsgViewInterface,public CExBaseListGridOptrInterface
{
    Q_OBJECT

public:
    explicit QNetworkConfigWidget(QWidget *parent = 0);
    ~QNetworkConfigWidget();

	void InitUI();
	void initConnections();

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	virtual void OnMulticastReceiveMsg(BYTE *pBuf, long nLen,LPVOID fsockaddr);
	virtual void OnProcessDataMsg(BYTE nCmdType, CSttPpDatasDriver vec);
	virtual void OnStopMulticastMsg();

private:
    Ui::QNetworkConfigWidget *ui;

	QNetworkIpTable *m_pIpGrid;
	CStringArray m_astrIP,m_astrMask;
	BOOL m_bScan;
	int m_nTimerID;
	CExBaseList m_oGridDatas;
	CDataGroup *m_pCurSelData;
	CString m_strSelNetDesc;
	QList<QNetworkInterface> m_oNetWorkList;
	bool m_bUseScanLan;

#ifdef _PSX_QT_LINUX_

#else

	PIP_ADAPTER_INFO m_pIpAdapterInfo;
	hd_DevNetsInfo m_oDevNetsInfo;
	HDEVINFO m_hDevInfo;
#endif

	void FreeMulticastSocket();
	BOOL ConnectMulticastServer();
	virtual void timerEvent( QTimerEvent * );
	void InitLocalAdapters();
	BOOL HasValidIP(QList<QNetworkAddressEntry> &oIPsList);
	void QueryLinuxIP();
	BOOL IsIPExactness(CString strIP);
	void stt_find_device_info(CString strData,CString &strSN,CString &strModel);
public:

	CSttMulticastClientSocket *m_pSttMulticastClientSocket;
	CSttTestAppCfg m_oSttTestAppCfg;
	CString m_strNetCardLocalIP;//选择网卡后,记录改网卡的第一个有效IP


	BOOL Process_Multicast_QueryIP_ACK(CSttPpDatasDriver vec);
 	BOOL Process_Multicast_QueryServerState_ACK(CSttPpDatasDriver vec);
	
	void OnStopScan();
	void EnableButtons();
	void SetNetworkConfigWidgetFont();

	void UpdataLocalIP_Combox(QNetworkInterface &oCurNetInterface);
	BOOL ValidCurrSelIP(const CString &strIP);
	CString GetNetCardDesc();
	CString GetValidIP(QNetworkInterface &oCurNetInterface);

public slots:

	void slot_ScanClicked();//扫描

	void slot_changeNetCardSel(int nCurComboxIndex);//选择网卡
	void slot_changeLocalIPAddrSel(int nCurComboxIndex);//本地网卡

    void slot_btnAdd_clicked();
    void slot_btnDelete_clicked();
	void slot_btnModify_clicked();
	void slot_ModifyTesterIPAsMask(QString &strIP,const QString &strSubNetMask);//修改IP
	void slot_AddTesterIPAsMask(QString &strIP,const QString &strSubNetMask);//添加IP
	
	void slot_CancelClicked();

};
extern CFont *g_pSttGlobalFont;


#endif // QNETWORKConfigWIDGET_H
