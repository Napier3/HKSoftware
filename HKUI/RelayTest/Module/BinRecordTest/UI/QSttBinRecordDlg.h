#ifndef QSTTBINRECORDDLG_H
#define QSTTBINRECORDDLG_H

#include <QDialog>
#include "ui_QSttBinRecordDlg.h"
#include "XGlobalDataTypes_QT.h"
#include "../../AdjustTool/SttAdjDevice.h"
#include "../../Engine/SttTestEngineClientData.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceMngr.h"
#include "Grid/QSttBinRecordModuleGrid.h"
#include "Grid/QSttBinRecordChsGrid.h"
//#include "Grid/QSttBinRecordChMapGrid.h"

class QSttBinRecordDlg : public QDialog
{
	Q_OBJECT

public:
	QSttBinRecordDlg(QWidget *parent = 0);
	~QSttBinRecordDlg();

	long m_nSampleRate;
	BOOL m_bLoginRecord;//是否登录录波
	BOOL m_bRecord;//是否正在录波
	BOOL m_bAutoSaveComtradeFile;//是否自动保存录波文件
	CString m_strComtradeFoldPath;//设置的保存录波文件的文件夹路径
	CString m_strPkgZipFile;
	CString m_strPkgUnZipFile;
	CString m_strPCapFile;
	CString m_strComtradeFile;
	CDataGroup m_oBinRecordParas;//开关量录波的参数

	void InitUI();                                              //初始化界面
	void InitDatas(CSttAdjDevice *pSttAdjDevice);				//初始化数据
	void GenerateParas();										//生成开关量录波参数
	void InitBinRecord();
	void SendBinRecordCmd();
	void ExistBinRecord();

	void UpdateBinRecordCfgByCapDevices(CCapDeviceRcdCh *pBinaryCh);//把CapDevice的值更新到数据对象中
	void UpdateCapDevicesByBinRecordCfg(CCapDeviceRcdCh *pBinaryCh, CCapDeviceRecord *pCapDevBinaryModule);   //初始化数据
	
	CCapDeviceMngr *m_pCapDeviceAll;							//下发开关量录波命令
	CCapDeviceRecord* AddCapDeviceBinary(CDataGroup *pModule);	//根据单个插件创建单个CapDeviceBinary
	CCapDeviceMngr m_oCapDeviceAll;
	CDataGroup m_oBinRecordCfgDataGroup;						//开关量录波数据对象

	QSttBinRecordModuleGrid *m_pSttBinRecordModuleGrid;        //开关量录波插件表格
	QSttBinRecordChsGrid *m_pSttBinRecordChsGrid;			   //开关量录波开关量表格

public slots:
	void slot_BeginRecord();                                    //启动录波槽函数
	void slot_StartMonitor();	                                //进入监视槽函数
	void slot_Close();                                          //关闭槽函数
	void On_SmpRateChanged();									//设置采样率槽函数
	void slot_BtnAutoSaveClicked();								//是否自动保存录波文件
	void slot_Btn_SaveCfgclicked();								//保存配置
	void slot_Btn_LoadCfgClicked();								//导入配置
	void slot_BtnBinRecordSet();								//录波设置槽函数
	void slot_CheckBoxState(int nRow, int nState);
private:
	Ui::QSttBinRecordDlg ui;
};

#endif // QSTTBINRECORDDLG_H
extern QSttBinRecordDlg* g_pBinRecord;