#ifndef SttMacroParaEditViewHtml_H
#define SttMacroParaEditViewHtml_H

#include "SttWebViewBase.h"
#include "../Interface/SttMacroParaEditInterface.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#define STT_MACROPARA_HTML_NAME_SYSCONFIG                               _T("SysConfig.html")  //系统参数
#define STT_MACROPARA_HTML_NAME_POWERGEAR                               _T("PowerGear.html")   //输出功率
#define STT_MACROPARA_HTML_NAME_VERSIONINFOR                            _T("VersionInfor.html")  //版本信息
#define STT_MACROPARA_HTML_NAME_DEVCOMM                                 _T("DevComm.html")      //装置通讯

#define STT_SYSCONFIG_DATA_ID_USE_KEYBOARD                              _T("UseKeyboard")  //下发设置网页系统参数的数据,是否使用键盘(0-不使用  1-使用)

//系统参数配置：0=更新；1=创建电气量项目
#define STT_HTML_SYSCONFIG_MODE_UPDATE   0
#define STT_HTML_SYSCONFIG_MODE_NEW      1

class QSttMacroParaEditViewHtml : public QSttWebViewBase, public CSttMacroParaEditInterface
{
	Q_OBJECT

public:
    QSttMacroParaEditViewHtml(QWidget* parent = 0);
	virtual ~QSttMacroParaEditViewHtml();

	CSttTestResourceBase* CreateTestResource();
	UINT m_nSysConfig_Mode;

	virtual void OnHtmlLoadFinish(bool b);
	virtual UINT GetMacroEditViewType()	{	return MACRO_EDIT_VIEW_TYPE_HTML;	}

public:
	virtual void Debug();
	virtual void SysConfig(CDataGroup *pSysConfig);
	virtual void SysConfig(CDvmDataset *pSysConfig);
	virtual void SysConfig(const CString &strSysConfig );
	virtual void SetDatas(CDvmDataset *pDataset);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void SetDatas(const CString &strDataset);
	virtual void GetDatas(CDvmDataset *pParas);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void GetDatas(CString& strParas);
	virtual BOOL IsHtmlView()	{	return TRUE;	}
    virtual CExBaseList* GetCurrentMacroDatas(){ return NULL;};  //20240716 wanmj 单功能多点的测试功能获取当前测试项的数据

	virtual void SetSysConfig(CDataGroup *pSysParas,CSttChMaps *pChMaps);
	virtual void SetChMaps(CDataGroup *pSysParas,CSttChMaps *pChMaps);
	virtual void SetPowerGear(CDataGroup *pSysParas);
	virtual void SetVersionInfor(CDataGroup *pDeviceModel);
	virtual void SetDevComm(CDvmLogicDevice *pLdevice);

	//yzj 2022-2-20 仿照原生态功能启动网页的图表刷新
	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

public:
	CDataGroup *m_pRetParasRef;
	CSttTestResourceBase *m_pHtmlSttTestResource;//zhouhj 20220313  每个原生功能对应一个自己的软件资源
protected:
	bool m_bHasClicked_OkCancel;//20230220 zhouhj 防止重复发送通道映射等命令

public slots:
	//void populateJavaScriptWindowObject();

signals:
	//APP ==>> HTML
	void msg_Debug();
	void msg_SysConfig(QVariant object);
	void msg_SetDatas(QVariant object);
	void msg_GetDatas(QVariant object);
	void msg_SetHtml(QVariant object);

	void msg_SetSysConfig(QVariant strSysParas,QVariant strChMaps);//zhouhj 20220113 增加用于设置系统参数、通道映射、功率档位、版本信息、设备通讯
	void msg_SetChMaps(QVariant strSysParas,QVariant strChMaps);
	void msg_SetPowerGear(QVariant strSysParas);
	void msg_SetVersionInfor(QVariant strDeviceModel);
	void msg_SetDevComm(QVariant strLdevice);

public slots:
	//APP ==>> HTML
	void slot_Debug();
	void slot_SysConfig(CDataGroup *pSysConfig);
	void slot_SysConfig(const CString &strSysConfig);
	
	void slot_SetDatas(CDvmDataset *pDataset);
	void slot_SetDatas(CDataGroup *pParas);
	void slot_SetDatas(const CString &strDataset);

	void slot_GetDatas(CDvmDataset *pDataset);
	void slot_GetDatas(CDataGroup *pDataset);//zhouhj 20220113 
	void slot_SetHtml(const CString &strFile);

	//HTML ==>> APP
	void UpdateDatas(QVariant strParas);
	void OnItemsChanged(QVariant strParas);
	void UI_ExecCmd(QVariant strCmd, QVariant strParas);
	void UI_OK_Click(QVariant strHtmlFileName, QVariant strParas1, QVariant strParas2); //zhouhj 20220126 增加扩展参数
	void UI_Cancel_Click(QVariant strHtmlFileName);

};

#endif // SttMacroParaEditViewHtml_H
