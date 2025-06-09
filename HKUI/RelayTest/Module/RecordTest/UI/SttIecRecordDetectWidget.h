#ifndef SttIecRecordDetectWidget_H
#define SttIecRecordDetectWidget_H

#include <QDialog>
#include <QFont>
#include "SttIecCbGrid.h"
#include "../../../../Module/OSInterface/XWndInterface.h"
#include "../../../Module/UI/Controls/SttCheckBox.h"
//2022-12-02  lijunqing  
#include "../../Assist/SttAssistGlobalApi.h"
#include "SttIecRecordWriteFileWidget.h"

//定义报文探测类型
#define STT_IEC_DETECT_TYPE_61850                      0
#define STT_IEC_DETECT_TYPE_61850_92                   1
#define STT_IEC_DETECT_TYPE_61850_GS                   2
#define STT_IEC_DETECT_TYPE_60044                      3

namespace Ui {
class QSttIecRecordDetectWidget;
}

class QSttIecRecordDetectWidget : public QDialog, public CXWndInterface, public CExBaseListGridOptrInterface,
	public CSttWndAssistInterface  //2022-12-02 lijunqing 测试助手相关的接口
{
    Q_OBJECT

public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
	virtual unsigned int XSetTimer(unsigned int nIDEvent, unsigned int nElapse, void* pFunc);
	virtual BOOL XKillTimer(unsigned int nIDEvent);
	virtual void XPostMessage(unsigned int nMsgID, unsigned long wParam=0, unsigned long  lParam=0);
	BOOL IsCapDeviceMngrDevice(CCapDeviceBase *pCapDeviceBase);//增加判断确认  zhouhj 2024.4.26

//CSttWndAssistInterface
public:
	//查找窗口，保留用 找到返回窗口,      否则返回NULL
	//具体对象必须重载此函数，因为如果直接返回窗口指针，然后强制转换为CSttWndAssistInterface，会出错
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//功能执行接口
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

public:
    explicit QSttIecRecordDetectWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttIecRecordDetectWidget();
	void SetIecCapWriteFile(bool b);

	void ConnectAll();
	void DisConnectAll();

	CSttIecCbGrid *m_pGridIecCb;
	BOOL m_bViewSmv;
	BOOL m_bViewGoose;
	BOOL m_bViewFT3;
	BOOL m_bIsFromIecfgFile;
	bool m_bIecCapWriteFile;
	bool m_bIsClearCBs;//zhouhj  20220902  增加防止连续多次点击清除按钮
	long m_nIecType; //20240906 wuxinyi 增加报文探测时IEC类型，用于传给底层SV--1 GOOSE---2  FT3---3  全部(SV+GOOSE)---0(参考330)
	BOOL m_bStartDetect;//20241022 wuxinyi 增加是否在探测过程(参考330)

public:
//	void InitSttIecRecord();
//	void FreeeSttIecRecord();
	void UpdateCbGrid();
	void UpdateDetectWidget();//更新表格及界面按钮
	void StartDetect();//开始探测
	void ImportIecfg();
	void UpdateIecfg();
	void CloseIecCapDetect();//20220629 zhouhj 关闭测试功能界面时,如果底层还处于探测模式,关闭探测通道
	
	void SetIecRecordFont();//2022-10-17

	BOOL AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase);//20221218 zhouhj 查找SCD,根据SCD文件中对应的AppID更新当前控制块内容
	//关联FT3控制块相关通道映射内容
	BOOL AttachDeviceFT3ChMaps(CCapDeviceBase *pCapDeviceBase);
	void ClearAll_StartDetect();//清空全部,重新开始探测

	//zhouhj 2023.12.4更新报文探测类别
	void UpdateDetectType(long nPkgDetectType);

public slots:

signals:
	void sig_AddNewDevice(CCapDeviceBase *pCapDevice);

private slots:
    void on_m_btnDetect_clicked();
	void on_m_btnClear_clicked();
	void on_m_btnBeginRecord_clicked();//进入监视
    void slot_chkUseSmvClicked();
	void slot_chkUseGooseClicked();
    void slot_chkUseFT3Clicked();
	void on_AddNewDevice(CCapDeviceBase *pCapDevice);

    void on_m_chkSmvFirstIsTime_clicked();
    void on_m_btnDetectStop_clicked();

    void on_m_btnImportIecfg_clicked();

	void slot_ck_WaveRecordStateChanged(int	nIndex);

//	void on_m_chkWaveRecord_clicked(int bState);

private:
    Ui::QSttIecRecordDetectWidget *ui;
	QSttCheckBox *m_chkWaveRecord;//录波
	QSttIecRecordWriteFileWidget *m_pRecordWriteFileWiget;
	
};

extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;

#endif // SttIecRecordDetectWidget_H
