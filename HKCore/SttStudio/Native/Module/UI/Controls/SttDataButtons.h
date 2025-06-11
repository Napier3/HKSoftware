#ifndef QSTTDATABUTTONBASES_H
#define QSTTDATABUTTONBASES_H

#include <QToolButton>
#include "SttToolButtonBase.h"
#include "../Config/Frame/SttFrame_Data.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/API/GlobalConfigApi.h"

#define STT_LIGHT_BTN_INDEX_ShutOff                        0
#define STT_LIGHT_BTN_INDEX_Run                            1
#define STT_LIGHT_BTN_INDEX_Red                            2
#define STT_LIGHT_BTN_INDEX_Yellow                         3
#define STT_LIGHT_BIN_INDEX_Black                          4



//???????????????????????????????????????
//2022-6-9  lijunqing 此部分应该放到配置文件中，动态加载
//因为不同的产品可能需要的图标是不一样的。
struct QSttButtonIconMngr
{
	QIcon  m_IconPower_1;
	QIcon  m_IconPower_2;
	QIcon  m_IconPower_3;
	QIcon  m_IconPower_4;
	QIcon  m_IconPower_5;
	QIcon  m_IconPower_0;

	QIcon  m_IconSD_1;
	QIcon  m_IconSD_2;

	QIcon  m_IconLight_Run;
	QIcon  m_IconLight_ShutOff;
	QIcon  m_IconLight_Red;
	QIcon  m_IconLight_Yellow;
	QIcon  m_IconLight_Black;

	QIcon  m_IconBin_1;
	QIcon  m_IconBin_2;
	QIcon  m_IconBin_3;
	QIcon  m_IconBin_4;

	QIcon  m_IconNetStat_1;
	QIcon  m_IconNetStat_2;

	QIcon  m_IconGps_1;
	QIcon  m_IconGps_2;

	QIcon  m_Icon4G_1;
	QIcon  m_Icon4G_2;

	QIcon  m_IconUSB_1;
	QIcon  m_IconUSB_2;

	QIcon  m_IconBlueTooth_1;
	QIcon  m_IconBlueTooth_2;

	QIcon  m_IconWifi_1;
	QIcon  m_IconWifi_2;

	void Init/*QSttButtonIcon*/()
	{
#ifdef _PSX_QT_WINDOWS_
		CString strName;
		CString strPicPath = _P_GetResourcePath();

		strName = strPicPath + "POWER-1.png";
		m_IconPower_1.addFile(strName);

		strName = strPicPath + "POWER-2.png";
		m_IconPower_2.addFile(strName);

		strName = strPicPath + "POWER-3.png";
		m_IconPower_3.addFile(strName);

		strName = strPicPath + "POWER-4.png";
		m_IconPower_4.addFile(strName);

		strName = strPicPath + "POWER-5.png";
		m_IconPower_5.addFile(strName);

		strName = strPicPath + "POWER-0.png";
		m_IconPower_0.addFile(strName);

		strName = strPicPath + "SD1.png";
		m_IconSD_1.addFile(strName);

		strName = strPicPath + "SD0.png";
		m_IconSD_2.addFile(strName);

		strName = strPicPath + "circle_green.png";
		m_IconLight_Run.addFile(strName);

		strName = strPicPath + "shutoff.png";
		m_IconLight_ShutOff.addFile(strName);

		strName = strPicPath + "circle_red.png";
		m_IconLight_Red.addFile(strName);

		strName = strPicPath + "circle_yellow.png";
		m_IconLight_Yellow.addFile(strName);

		strName = strPicPath + "circle_black.png";
		m_IconLight_Black.addFile(strName);

		strName = strPicPath + "switch_open.png";
		m_IconBin_1.addFile(strName);

		strName = strPicPath + "switch_close2.png";
		m_IconBin_2.addFile(strName);

		strName = strPicPath + "switch_close.png";
		m_IconBin_3.addFile(strName);

		strName = strPicPath + "switch_open2.png";
		m_IconBin_4.addFile(strName);

		strName = strPicPath + "circle_green.png";
		m_IconNetStat_1.addFile(strName);

		strName = strPicPath + "circle_black.png";
		m_IconNetStat_2.addFile(strName);

		strName = strPicPath + "gps0.png";
		m_IconGps_1.addFile(strName);

		strName = strPicPath + "gps1.png";
		m_IconGps_2.addFile(strName);

		strName = strPicPath + "4G0.png";
		m_Icon4G_1.addFile(strName);

		strName = strPicPath + "4G1.png";
		m_Icon4G_2.addFile(strName);

		strName = strPicPath + "usb0.png";
		m_IconUSB_1.addFile(strName);

		strName = strPicPath + "usb1.png";
		m_IconUSB_2.addFile(strName);

		strName = strPicPath + "ble0.png";
		m_IconBlueTooth_1.addFile(strName);

		strName = strPicPath + "ble1.png";
		m_IconBlueTooth_2.addFile(strName);

		strName = strPicPath + "wifi0.png";
		m_IconWifi_1.addFile(strName);

		strName = strPicPath + "wifi1.png";
		m_IconWifi_2.addFile(strName);
#else
		//CString strName;
		CString strPicPath;// = _P_GetResourcePath();

		strPicPath =  ":/power/images/POWER-1.png";
		m_IconPower_1.addFile(strPicPath);

		strPicPath =  ":/power/images/POWER-2.png";
		m_IconPower_2.addFile(strPicPath);

		strPicPath =  ":/power/images/POWER-3.png";
		m_IconPower_3.addFile(strPicPath);

		strPicPath =  ":/power/images/POWER-4.png";
		m_IconPower_4.addFile(strPicPath);

		strPicPath =  ":/power/images/POWER-5.png";
		m_IconPower_5.addFile(strPicPath);

		strPicPath =  ":/power/images/POWER-0.png";
		m_IconPower_0.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/SD1.png";
		m_IconSD_1.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/SD0.png";
		m_IconSD_2.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/circle_green.png";
		m_IconLight_Run.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/shutoff.png";
		m_IconLight_ShutOff.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/circle_red.png";
		m_IconLight_Red.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/circle_yellow.png";
		m_IconLight_Yellow.addFile(strPicPath);

		strPicPath =  ":/ctrls/images/circle_black.png";
		m_IconLight_Black.addFile(strPicPath);

		strPicPath = ":/ctrls/images/switch_open.png";
		m_IconBin_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/switch_close2.png";
		m_IconBin_2.addFile(strPicPath);

		strPicPath = ":/ctrls/images/switch_close.png";
		m_IconBin_3.addFile(strPicPath);

		strPicPath = ":/ctrls/images/switch_open2.png";
		m_IconBin_4.addFile(strPicPath);

		strPicPath = ":/ctrls/images/circle_green.png";
		m_IconNetStat_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/circle_black.png";
		m_IconNetStat_2.addFile(strPicPath);

		strPicPath = ":/ctrls/images/gps0.png";
		m_IconGps_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/gps1.png";
		m_IconGps_2.addFile(strPicPath);

		strPicPath = ":/ctrls/images/4G0.png";
		m_Icon4G_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/4G1.png";
		m_Icon4G_2.addFile(strPicPath);

		strPicPath = ":/ctrls/images/usb0.png";
		m_IconUSB_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/usb1.png";
		m_IconUSB_2.addFile(strPicPath);

		strPicPath = ":/ctrls/images/ble0.png";
		m_IconBlueTooth_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/ble1.png";
		m_IconBlueTooth_2.addFile(strPicPath);

		strPicPath = ":/ctrls/images/wifi0.png";
		m_IconWifi_1.addFile(strPicPath);

		strPicPath = ":/ctrls/images/wifi1.png";
		m_IconWifi_2.addFile(strPicPath);
#endif
	}
};

extern QSttButtonIconMngr g_oSttButtonIconMngr;

class QSttBatteryButton : public QSttToolButtonBase
{
public:
    QSttBatteryButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    virtual void SetPic(int nState);
	virtual void UpdateState(CDataGroup *pDataGroup);  //2022-6-9  lijunqing

	long m_nBatCapValue;
	long m_nPowerAC;
	CString m_strCurrStyleString;
	CString m_strBatCapString;
};

class QSttSdCardButton : public QSttToolButtonBase
{
public:
    QSttSdCardButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    virtual void SetPic(int nState);
};

class QSttLightButton : public QSttToolButtonBase
{
public:
    QSttLightButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    virtual void SetPic(int nState);
};

class QSttBinButton : public QSttToolButtonBase
{
public:
    QSttBinButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    virtual void SetPic(int nState);
};

class QSttBoutButton : public QSttToolButtonBase
{
public:
    QSttBoutButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
    virtual void SetPic(int nState);
};

class QSttNetStatButton : public QSttToolButtonBase
{
public:
	QSttNetStatButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
	virtual void SetPic(int nState);
};

class QSttGpsButton : public QSttToolButtonBase
{
public:
	QSttGpsButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
	virtual void SetPic(int nState);

	virtual void UpdateState(CDataGroup *pDataGroup);  //2022-6-9  lijunqing

};

class QStt4GButton : public QSttToolButtonBase
{
public:
	QStt4GButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
	virtual void SetPic(int nState);
};

class QSttWifiButton : public QSttToolButtonBase
{
public:
	QSttWifiButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
	virtual void SetPic(int nState);
};

class QSttUSBButton : public QSttToolButtonBase
{
public:
	QSttUSBButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
	virtual void SetPic(int nState);
};

class QSttBlueToothButton : public QSttToolButtonBase
{
public:
	QSttBlueToothButton(CExBaseObject *pCfgData,QFont font,QWidget *parent=0);
	virtual void SetPic(int nState);
	virtual void UpdateState(CDataGroup *pDataGroup);  //2022-6-10  lijunqing
};

class QSttBarDataBtnsMngr : public QList<QSttToolButtonBase *>
{
public:
	QSttBarDataBtnsMngr();
	virtual ~QSttBarDataBtnsMngr();

	void UpdataDataButtons(CDataGroup *pDatas);
	void UpdataDataButtons(CDataGroup *pDatas, const CString &strID);
	QSttToolButtonBase* FindButtonByID(const CString &strID);

	long GetBatCapValue();
	BOOL IsCharging();//判断是否正在充电
	BOOL IsLowPower();//判断是否为低电量模式
	BOOL UpdatePicSet(const CString &strID,long nValue);

private:
	QSttBatteryButton* m_pBatteryButton;
};

#endif // QSTTTOOLBUTTONBASE_H
