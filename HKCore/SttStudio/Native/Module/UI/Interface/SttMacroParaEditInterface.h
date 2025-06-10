#pragma once

#include "../../Module/DataMngr/DataGroup.h"
#include "../../Module/DataMngr/DvmValues.h"
#include "../../Module/DataMngr/DvmDatasetGroup.h"
#include "../../SttCmd/GuideBook/SttGuideBook.h"
#include "../../SttTest/Common/tmt_result_def.h"

#define MACRO_EDIT_VIEW_TYPE_BASE   0
#define MACRO_EDIT_VIEW_TYPE_HTML   1
#define MACRO_EDIT_VIEW_TYPE_ORIGINAL   2

class CSttMacroParaEditInterface
{
public:
	CSttMacroParaEditInterface()
	{
		m_pMacroParaEditWnd = NULL;
		m_pSttItems = NULL;
	};

	virtual ~CSttMacroParaEditInterface(void){};

 	//APP ==>> HTML
	virtual void SysConfig(CDataGroup *pSysConfig) = 0;
	virtual void SysConfig(CDvmDataset *pSysConfig) = 0;
	virtual void SysConfig(const CString &strSysConfig ) = 0;
	virtual void SetDatas(CDvmDataset *pDataset) = 0;
	virtual void SetDatas(CDataGroup *pParas) = 0;
	virtual void SetDatas(const CString &strDataset) = 0;
	virtual void GetDatas(CDvmDataset *pParas) = 0;
	virtual void GetDatas(CDataGroup *pParas) = 0;
	virtual void GetDatas(CString& strParas) = 0;

	virtual void UpdateEventMsg(CEventResult *pCurrEventResult){}//���Թ��ܸ��²���
	virtual void ShowReport(CDvmValues *pValues){};
	virtual void UpdateTestResource(BOOL bCreateChMaps){}// 20220317 zhouhj
//	virtual void UpdateRtSyncTime(CDataGroup *pRtSycTime){}//20220920 zhouhj ���¶�ʱ����ʱͬ��ʱ��
	virtual void Debug(){};
	virtual BOOL IsHtmlView()	{	return FALSE;	}
	virtual long GetMacroItemsXml(const CString &strMacroItemsID, char **ppszItemsXml)	{	return 0;	}
	virtual UINT GetMacroEditViewType()	{	return MACRO_EDIT_VIEW_TYPE_BASE;	}

	//2023-2-4  lijunqing ��߳�������ʼ���򿪵��ٶȣ���ʸ��ͼ��״̬ͼ�ȵĳ�ʼ���ŵ��߳�
	virtual void InitSpyToolWidget()	{};

	//20230210 zhangyq  
	virtual void ProcessGbAfterGenTemplate(CSttGuideBook *pSttGuideBook){};  //����ģ��
	virtual CString ProcessItemID(const CString & strItemID,long nLoopIndex){ return "";};  //���ݵ�ǰ���Ե��ظ�������ţ���̬����ID

public:
	void* m_pMacroParaEditWnd;
	CExBaseObject *m_pSttItems;  //ָ���Ӧ��rootnode��CSttItems���󡣷���ɾ����Ŀ�ǲ�����ͼ�����ر�ģ����ͼ��
};

class CSttMacroParaEditMsgRcvInterface
{
public:
	CSttMacroParaEditMsgRcvInterface(){};
	virtual ~CSttMacroParaEditMsgRcvInterface(void){};

	//HTML ==>> APP
	virtual void UpdateDatas(CDvmDataset *pParas) = 0;
	virtual void OnItemsChanged(CDvmDataset *pParas) = 0;
	virtual void UI_ExecCmd(const CString &strCmd, CDvmDataset *pParas) = 0;
	virtual void UI_OK_Click(const CString &strHtmlFileName, CDvmDataset *pParas) = 0;
	virtual void UI_Cancel_Click(const CString &strHtmlFileName) = 0;

};

/*//ģ��ṹ
�����ܣ�
	HdConfig     IEC61850Config   SystemConfig    MacroTest(MacroID)

��Web����
	HdConfig     IEC61850Config   SystemConfig    MacroUI.id(Items)
*/
