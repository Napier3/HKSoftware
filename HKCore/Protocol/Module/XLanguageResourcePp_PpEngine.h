//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "XLanguageResourcePp.h"


class CXLanguageResourcePp_PpEngine : public CXLanguageResourcePpBase
{
public:
	CXLanguageResourcePp_PpEngine();
	virtual ~CXLanguageResourcePp_PpEngine();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsPp_PpEngine;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();
};

	
	extern CString  g_strXLangRsPp_PpEngineFile;
	extern CString g_sLangID_NotSelDev;       //û��ѡ���豸
	extern CString g_sLangTxt_NotSelDev;
	extern CString g_sLangID_PrtcProHome;      //��Լ���������ҳ
	extern CString g_sLangTxt_PrtcProHome;
	extern CString g_sLangID_DevOpera;      //�豸����
	extern CString g_sLangTxt_DevOpera;
	extern CString g_sLangID_NewAdd;          //����
	extern CString g_sLangTxt_NewAdd;
	extern CString g_sLangID_Connection;       //����
	extern CString g_sLangTxt_Connection;
	extern CString g_sLangID_DisConnection;       //�Ͽ�����
	extern CString g_sLangTxt_DisConnection;
	extern CString g_sLangID_Uninstall;       //ж��
	extern CString g_sLangTxt_Uninstall;
	extern CString g_sLangID_PointTableEdit;       //���༭
	extern CString g_sLangTxt_PointTableEdit;
	extern CString g_sLangID_CommuntSet;       //ͨѶ����
	extern CString g_sLangTxt_CommuntSet;
	extern CString g_sLangID_CommunProcess;       //ͨѶ����
	extern CString g_sLangTxt_CommunProcess;
	extern CString g_sLangID_OperationProcess;       //���й���
	extern CString g_sLangTxt_OperationProcess;
	extern CString g_sLangID_ViewOprthPrcs;       //�鿴���й���
	extern CString g_sLangTxt_ViewOprthPrcs;
	extern CString g_sLangID_StopProcess;       //��ֹ����
	extern CString g_sLangTxt_StopProcess;
	extern CString g_sLangID_ClearSOE;       //���SOE
	extern CString g_sLangTxt_ClearSOE;
	extern CString g_sLangID_ClearMessage;       //�������
	extern CString g_sLangTxt_ClearMessage;
	extern CString g_sLangID_DebugMode;       //����ģʽ
	extern CString g_sLangTxt_DebugMode;
	extern CString g_sLangID_Report;       //����
	extern CString g_sLangTxt_Report;
	extern CString g_sLangID_StartReport;       //��������
	extern CString g_sLangTxt_StartReport;
	extern CString g_sLangID_StopReport;       //ֹͣ����
	extern CString g_sLangTxt_StopReport;
	extern CString g_sLangID_DevToolBar;       //�豸������
	extern CString g_sLangTxt_DevToolBar;
	extern CString g_sLangID_DevToolBarTip;       //��ʾ�������豸������\n�л��豸������
	extern CString g_sLangTxt_DevToolBarTip;
	extern CString g_sLangID_OutputWnd;       //�������
	extern CString g_sLangTxt_OutputWnd;
	extern CString g_sLangID_OutputWndTip;       //��ʾ�������������\n�л��������
	extern CString g_sLangTxt_OutputWndTip;
	extern CString g_sLangID_MonitorBindError;       //���Ӱ󶨴���
	extern CString g_sLangTxt_MonitorBindError;
	extern CString g_sLangID_MonitorMessageInf;       //���ӱ�����Ϣ
	extern CString g_sLangTxt_MonitorMessageInf;
	extern CString g_sLangID_MonitorMessage;       //���ӱ���
	extern CString g_sLangTxt_MonitorMessage;

	extern CString g_sLangID_ClipboardData;       //���а�����
	extern CString g_sLangTxt_ClipboardData;
// 	extern CString g_sLangID_DataList;       //�����б�
// 	extern CString g_sLangTxt_DataList;
	extern CString g_sLangID_ReadClipboard;       //��ȡ���а�
	extern CString g_sLangTxt_ReadClipboard;
	extern CString g_sLangID_AddToList;       //��ӵ��б�
	extern CString g_sLangTxt_AddToList;
	extern CString g_sLangID_InsertList;       //���뵽�б�β
	extern CString g_sLangTxt_InsertList;
	extern CString g_sLangID_ClearList;       //����б�
	extern CString g_sLangTxt_ClearList;
	extern CString g_sLangID_InsertIndex;       //������ʼ������
	extern CString g_sLangTxt_InsertIndex;
	extern CString g_sLangID_PointDataPaste;       //�������ճ��
	extern CString g_sLangTxt_PointDataPaste;
	extern CString g_sLangID_NewDev;       //�½��豸
	extern CString g_sLangTxt_NewDev;
	extern CString g_sLangID_PointListFile;       //����ļ�
	extern CString g_sLangTxt_PointListFile;
	extern CString g_sLangID_ModifyClose;       //�޸Ĺر�
	extern CString g_sLangTxt_ModifyClose;

	extern CString g_sLangID_FormulaType;       //��ʽ����
	extern CString g_sLangTxt_FormulaType;
	extern CString g_sLangID_FormulaEdit;       //��ʽ�༭
	extern CString g_sLangTxt_FormulaEdit;
	extern CString g_sLangID_SelType;       //ѡ�����
	extern CString g_sLangTxt_SelType;
	extern CString g_sLangID_FormulaEditD;       //��ʽ�༭�Ի���
	extern CString g_sLangTxt_FormulaEditD;

	extern CString g_sLangID_MonitorPrtcMessage;       //���ӹ�Լ����
	extern CString g_sLangTxt_MonitorPrtcMessage;
	extern CString g_sLangID_MonitorSOE;       //����SOE
	extern CString g_sLangTxt_MonitorSOE;
	extern CString g_sLangID_Empty;       //���
	extern CString g_sLangTxt_Empty;
	extern CString g_sLangID_CommunMonitor;       //ͨѶ����
	extern CString g_sLangTxt_CommunMonitor;
	extern CString g_sLangID_SelCommunProcess;       //ѡ��ͨѶ����
	extern CString g_sLangTxt_SelCommunProcess;
	extern CString g_sLangID_SelProcessSet;       //ѡ��������ݽӿ�����
	extern CString g_sLangTxt_SelProcessSet;

	extern CString g_sLangID_Vaule;       //��ֵ
	extern CString g_sLangTxt_Vaule;
	extern CString g_sLangID_PrtcMonitor;       //��Լ����
	extern CString g_sLangTxt_PrtcMonitor;
	extern CString g_sLangID_CannotAddView;       //�޷�����λͼ: %x\n
	extern CString g_sLangTxt_CannotAddView;
	extern CString g_sLangID_NewFolder2;       //�½��ļ���...
	extern CString g_sLangTxt_NewFolder2;
	extern CString g_sLangID_AddMemberFctn;       //��ӳ�Ա����...
	extern CString g_sLangTxt_AddMemberFctn;
	extern CString g_sLangID_RptPathUnExist;       //����·����%s��������
	extern CString g_sLangTxt_RptPathUnExist;
	extern CString g_sLangID_DataPathUnExist;       //���ݼ�·����%s��������
	extern CString g_sLangTxt_DataPathUnExist;
	extern CString g_sLangID_DiffError;       //��ǰ���̡�%s���������Ĺ��̡�%s�������߲�ͬ����������
	extern CString g_sLangTxt_DiffError;
	extern CString g_sLangID_SendTestInf;       //===============���Ͳ��������Ϣ[%s] WND=��%08x�� MSG=��%08x��
	extern CString g_sLangTxt_SendTestInf;
	extern CString g_sLangID_SendSystemMsg;       //����ϵͳ��Ϣ WND=��%08x�� MSG=��%08x��(%d, %d)
	extern CString g_sLangTxt_SendSystemMsg;
	extern CString g_sLangID_ColctnClcltFmla;       //�ɼ����㹫ʽ
	extern CString g_sLangTxt_ColctnClcltFmla;
	extern CString g_sLangID_SendClcltFmla;       //���ͼ��㹫ʽ
	extern CString g_sLangTxt_SendClcltFmla;

    /*  ���¼������ƶ�������CXLanguageResourceBase��2024-1-4  shaolei
	extern CString g_sLangID_Voltage;       //��ѹ
	extern CString g_sLangTxt_Voltage;
	extern CString g_sLangID_Current;       //����
	extern CString g_sLangTxt_Current;
	extern CString g_sLangID_ActivePower;       //�й�����
	extern CString g_sLangTxt_ActivePower;
	extern CString g_sLangID_ReactivePower;       //�޹�����
	extern CString g_sLangTxt_ReactivePower;
	extern CString g_sLangID_Frequency;       //Ƶ��
	extern CString g_sLangTxt_Frequency;
	extern CString g_sLangID_PowerFactor;       //��������
	extern CString g_sLangTxt_PowerFactor;
    */

	extern CString g_sLangID_Menu_32817;      
	extern CString g_sLangTxt_Menu_32817;
	extern CString g_sLangID_Menu_32818;      
	extern CString g_sLangTxt_Menu_32818;
	extern CString g_sLangID_Menu_32819;      
	extern CString g_sLangTxt_Menu_32819;
	extern CString g_sLangID_DeviceDataView;      
	extern CString g_sLangTxt_DeviceDataView;
