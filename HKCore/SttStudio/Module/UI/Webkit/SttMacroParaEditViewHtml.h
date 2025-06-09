#ifndef SttMacroParaEditViewHtml_H
#define SttMacroParaEditViewHtml_H

#include "SttWebViewBase.h"
#include "../Interface/SttMacroParaEditInterface.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#define STT_MACROPARA_HTML_NAME_SYSCONFIG                               _T("SysConfig.html")  //ϵͳ����
#define STT_MACROPARA_HTML_NAME_POWERGEAR                               _T("PowerGear.html")   //�������
#define STT_MACROPARA_HTML_NAME_VERSIONINFOR                            _T("VersionInfor.html")  //�汾��Ϣ
#define STT_MACROPARA_HTML_NAME_DEVCOMM                                 _T("DevComm.html")      //װ��ͨѶ

#define STT_SYSCONFIG_DATA_ID_USE_KEYBOARD                              _T("UseKeyboard")  //�·�������ҳϵͳ����������,�Ƿ�ʹ�ü���(0-��ʹ��  1-ʹ��)

//ϵͳ�������ã�0=���£�1=������������Ŀ
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

	virtual void SetSysConfig(CDataGroup *pSysParas,CSttChMaps *pChMaps);
	virtual void SetChMaps(CDataGroup *pSysParas,CSttChMaps *pChMaps);
	virtual void SetPowerGear(CDataGroup *pSysParas);
	virtual void SetVersionInfor(CDataGroup *pDeviceModel);
	virtual void SetDevComm(CDvmLogicDevice *pLdevice);

	//yzj 2022-2-20 ����ԭ��̬����������ҳ��ͼ��ˢ��
	virtual void OnViewTestLink(BOOL b);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();

	virtual void UpdatePrimParaSetUI(){}//20240918 suyang ���½���һ��ֵ/����ֵ��ʾ
	virtual BOOL IsUseSecondParaSet(){ return TRUE; }//20240918 suyang �Ƿ���ʾ����ֵ

public:
	CDataGroup *m_pRetParasRef;
	CSttTestResourceBase *m_pHtmlSttTestResource;//zhouhj 20220313  ÿ��ԭ�����ܶ�Ӧһ���Լ��������Դ
protected:
	bool m_bHasClicked_OkCancel;//20230220 zhouhj ��ֹ�ظ�����ͨ��ӳ�������

public slots:
	//void populateJavaScriptWindowObject();

signals:
	//APP ==>> HTML
	void msg_Debug();
	void msg_SysConfig(QVariant object);
	void msg_SetDatas(QVariant object);
	void msg_GetDatas(QVariant object);
	void msg_SetHtml(QVariant object);

	void msg_SetSysConfig(QVariant strSysParas,QVariant strChMaps);//zhouhj 20220113 ������������ϵͳ������ͨ��ӳ�䡢���ʵ�λ���汾��Ϣ���豸ͨѶ
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
	void UI_OK_Click(QVariant strHtmlFileName, QVariant strParas1, QVariant strParas2); //zhouhj 20220126 ������չ����
	void UI_Cancel_Click(QVariant strHtmlFileName);

};

#endif // SttMacroParaEditViewHtml_H
