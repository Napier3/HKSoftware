#ifndef SttIecRecordMainWidget_H
#define SttIecRecordMainWidget_H

#include <QDialog>
#include <QFont>
#include "../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "SttIecRcdFuncInterface.h"

//2022-12-02  lijunqing  
#include "../../Assist/SttAssistGlobalApi.h"

namespace Ui {
class QSttIecRecordMainWidget;
}


class QSttIecRecordMainWidget : public QDialog, 
	public CSttWndAssistInterface  //2022-12-02 lijunqing 测试助手相关的接口
{
    Q_OBJECT
public:
    explicit QSttIecRecordMainWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttIecRecordMainWidget();

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
	void SetIecCapWriteFile(bool b);
	void SetIecCapDebugHead(bool b);

	void InitIecRecordCbWidget(const CString &strFuncID,long nPkgDetectType);

	void ShowIecDetectWindow();
	void ShowIecCbWindow();
	void UpdateCapDevice(CCapDeviceBase *pCapDevice);
	void StartDetect();//开始探测 
	void UpdateIecfg();//iecfg文件修改后,更新探测内容中的配置
	void CloseIecCapDetect();//20220629 zhouhj 关闭测试功能界面时,如果底层还处于探测模式,关闭探测通道
	void ClearAll_StartDetect();//清空全部,重新开始探测
	void UpdateIecDetectType(long nPkgDetectType);

public slots:

signals:
	void sig_ShowIecDetectWindow();
	void sig_ShowIecCbWindow();

private slots:
	void on_ShowIecDetectWindow();
	void on_ShowIecCbWindow();

private:
    Ui::QSttIecRecordMainWidget *ui;

public://20231017 wxy 外部需要调m_pSttIecRecordDetectWidget，故设为公有
	QDialog *m_pSttIecRecordDetectWidget;//报文探测界面,显示探测到的全部控制块
	QDialog *m_pSttIecRecordCbWidget;//进入报文监视界面后,显示单个控制块报文的全部信息

};

extern QSttIecRecordMainWidget *g_theSttIecRecordMainWidget;

#endif // SttIecRecordMainWidget_H
