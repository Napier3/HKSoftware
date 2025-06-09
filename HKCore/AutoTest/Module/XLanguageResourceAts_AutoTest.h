#pragma once

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLanguageResourceAts.h"

class CXLanguageResourceAts_AutoTest : public CXLanguageResourceAtsBase
{
// ����
public:
	CXLanguageResourceAts_AutoTest();
	virtual ~CXLanguageResourceAts_AutoTest();
	
private:
	CXLanguage m_oXLangRsAutoTest;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();

	//2023-3-1  lijunqing
	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsAutoTestFile;
	extern CString g_sLangID_AutoTestVTip;//�����Զ�����ϵͳV1.0
	extern CString g_sLangTxt_AutoTestVTip;
// 	extern CString g_sLangID_FileOpen; 
// 	extern CString g_sLangTxt_FileOpen;
	extern CString g_sLangID_FileOpenTip; 
	extern CString g_sLangTxt_FileOpenTip;
	extern CString g_sLangID_Quit; 
	extern CString g_sLangTxt_Quit;
	extern CString g_sLangID_QuitTip; 
	extern CString g_sLangTxt_QuitTip;
	extern CString g_sLangID_RibbonRecentDocs; 
	extern CString g_sLangTxt_RibbonRecentDocs;
	extern CString g_sLangID_Config; 
	extern CString g_sLangTxt_Config;
	extern CString g_sLangID_AutoTestOper; 
	extern CString g_sLangTxt_AutoTestOper;
// 	extern CString g_sLangID_UpLoad; 
// 	extern CString g_sLangTxt_UpLoad;
// 	extern CString g_sLangID_DownLoad; 
// 	extern CString g_sLangTxt_DownLoad;
	extern CString g_sLangID_NewTest; 
	extern CString g_sLangTxt_NewTest;
	extern CString g_sLangID_MultiDevTest; 
	extern CString g_sLangTxt_MultiDevTest;
	extern CString g_sLangID_SinDevMulPro; 
	extern CString g_sLangTxt_SinDevMulPro;
	extern CString g_sLangID_MdvMgrpTest; 
	extern CString g_sLangTxt_MdvMgrpTest;
	extern CString g_sLangID_SubTempTest; 
	extern CString g_sLangTxt_SubTempTest;
	extern CString g_sLangID_SingleDevTest;
	extern CString g_sLangTxt_SingleDevTest;
	extern CString g_sLangID_UsePowerTestTemplate;
	extern CString g_sLangTxt_UsePowerTestTemplate;
	extern CString g_sLangID_Test;
	extern CString g_sLangTxt_Test; 
    extern CString g_sLangID_StartTest; 
	extern CString g_sLangTxt_StartTest;
	extern CString g_sLangID_StartReport;
	extern CString g_sLangTxt_StartReport;	
	extern CString g_sLangID_Stop; 
	extern CString g_sLangTxt_Stop;
	extern CString g_sLangID_Report; 
	extern CString g_sLangTxt_Report;
	extern CString g_sLangID_ShowScale; 
	extern CString g_sLangTxt_ShowScale;
	extern CString g_sLangID_AdReport; 
	extern CString g_sLangTxt_AdReport;
	extern CString g_sLangID_PrintReport; 
	extern CString g_sLangTxt_PrintReport;
	extern CString g_sLangID_Settings; 
	extern CString g_sLangTxt_Settings;	
	extern CString g_sLangID_ReConfig; 
	extern CString g_sLangTxt_ReConfig;
// 	extern CString g_sLangID_View; 
// 	extern CString g_sLangTxt_View;	
// 	extern CString g_sLangID_StatusBarTip; 
// 	extern CString g_sLangTxt_StatusBarTip;
	extern CString g_sLangID_OutpWind; 
	extern CString g_sLangTxt_OutpWind;
	extern CString g_sLangID_FileManBar; 
	extern CString g_sLangTxt_FileManBar;
	extern CString g_sLangID_TestInfBar; 
	extern CString g_sLangTxt_TestInfBar;//����������
	extern CString g_sLangID_SdvMgrpReTest; 
	extern CString g_sLangTxt_SdvMgrpReTest;//����������
	extern CString g_sLangID_CharCurTest; 
	extern CString g_sLangTxt_CharCurTest;//�������߲���
	extern CString g_sLangID_TestTaskBar;
	extern CString g_sLangTxt_TestTaskBar;
	extern CString g_sLangID_ShowTestInf; 
	extern CString g_sLangTxt_ShowTestInf;
	extern CString g_sLangID_ShowTestSpyWnd; 
	extern CString g_sLangTxt_ShowTestSpyWnd;
	extern CString g_sLangID_WriteLogFile; 
	extern CString g_sLangTxt_WriteLogFile;
	extern CString g_sLangID_ViewWordRpt; 
	extern CString g_sLangTxt_ViewWordRpt;
// 	extern CString g_sLangID_AboutTip; 
	extern CString g_sLangTxt_AboutTip;
	extern CString g_sLangID_ToAndCom; 
	extern CString g_sLangTxt_ToAndCom;
	extern CString g_sLangID_SysTools; 
	extern CString g_sLangTxt_SysTools;
	extern CString g_sLangID_SysCom; 
	extern CString g_sLangTxt_SysCom;
	extern CString g_sLangID_TestFileMan; 
	extern CString g_sLangTxt_TestFileMan;
	extern CString g_sLangID_TestItemField; 
	extern CString g_sLangTxt_TestItemField;
	extern CString g_sLangID_NewTestWork; //�½���������
	extern CString g_sLangTxt_NewTestWork;
	extern CString g_sLangID_TestInf; 
	extern CString g_sLangTxt_TestInf;
	extern CString g_sLangID_TaskName; 
	extern CString g_sLangTxt_TaskName;
	extern CString g_sLangID_TestType; 
	extern CString g_sLangTxt_TestType;
	extern CString g_sLangID_ProSet; 
	extern CString g_sLangTxt_ProSet;
	extern CString g_sLangID_ChoProTem; //ѡ���Լģ��
	extern CString g_sLangTxt_ChoProTem;
	extern CString g_sLangID_PoFile; 
	extern CString g_sLangTxt_PoFile;
	extern CString g_sLangID_ChoTest; 
	extern CString g_sLangTxt_ChoTest;
	extern CString g_sLangID_SelPoFile; //ѡ�����ļ�
	extern CString g_sLangTxt_SelPoFile;
	extern CString g_sLangID_TitleTask; 
	extern CString g_sLangTxt_TitleTask;
	extern CString g_sLangID_NewBuilt; //�½�
	extern CString g_sLangTxt_NewBuilt;
	extern CString g_sLangID_ReportAdjSh;//���������ʾ 
	extern CString g_sLangTxt_ReportAdjSh;
	extern CString g_sLangID_TestChoPro;//������ѡ�񣨲�������ѡ��ı䣬�����������Զ����Գ�������Ǹı���Ч�� 
	extern CString g_sLangTxt_TestChoPro;
	extern CString g_sLangID_AutoTestSysSet;//�Զ�����ϵͳ���� 
	extern CString g_sLangTxt_AutoTestSysSet;
	extern CString g_sLangID_AlarmAutoMain;//���桪�Զ����������� 
	extern CString g_sLangTxt_AlarmAutoMain;
	extern CString g_sLangID_TestFileName; //�����ļ���
	extern CString g_sLangTxt_TestFileName;
	extern CString g_sLangID_TesTyp; //��������
	extern CString g_sLangTxt_TesTyp;
	extern CString g_sLangID_ProTypeCho; //��Լ����ѡ��
	extern CString g_sLangTxt_ProTypeCho;
	extern CString g_sLangID_TestTempFile; //����ģ���ļ�
	extern CString g_sLangTxt_TestTempFile;
	extern CString g_sLangID_ProTempFile; //��Լģ���ļ�
	extern CString g_sLangTxt_ProTempFile;
	extern CString g_sLangID_ProHighSet; //��Լ�߼�����
	extern CString g_sLangTxt_ProHighSet;
	extern CString g_sLangID_ProTabFile; //��Լ����ļ�
	extern CString g_sLangTxt_ProTabFile;
	extern CString g_sLangID_RptData; //��������
	extern CString g_sLangTxt_RptData;
	extern CString g_sLangID_RptData2; //��������2
	extern CString g_sLangTxt_RptData2;
	extern CString g_sLangID_RptLog; //��������
	extern CString g_sLangTxt_RptLog;
	extern CString g_sLangID_TestTemp; //����ģ��
	extern CString g_sLangTxt_TestTemp;
	extern CString g_sLangID_AppTestNo; //���ֲ��Բ��ϸ���Ŀ����
	extern CString g_sLangTxt_AppTestNo;
	extern CString g_sLangID_CTestCNum; //�ظ�������Ŀ�ظ�����
	extern CString g_sLangTxt_CTestCNum;
	extern CString g_sLangID_CoeMus; //��ʾ����
	extern CString g_sLangTxt_CoeMus;
	extern CString g_sLangID_AlarmMode; //�澯��ʽ
	extern CString g_sLangTxt_AlarmMode;
	extern CString g_sLangID_ContTest; //��������
	extern CString g_sLangTxt_ContTest;
	extern CString g_sLangID_LongAlarm; //������
	extern CString g_sLangTxt_LongAlarm;
	extern CString g_sLangID_ShortAlarm; //�̾���
	extern CString g_sLangTxt_ShortAlarm;
	extern CString g_sLangID_CusRepeat; //�Զ�������ظ�����
	extern CString g_sLangTxt_CusRepeat;
	extern CString g_sLangID_ComFaReNu; //ͨѶʧ�ܺ����Դ���
	extern CString g_sLangTxt_ComFaReNu;
	extern CString g_sLangID_RetComS; //����ͨѶǰ��ʱ
	extern CString g_sLangTxt_RetComS;
	extern CString g_sLangID_TestCoDe; //������Ŀ������ɳ���
	extern CString g_sLangTxt_TestCoDe;
	extern CString g_sLangID_CoNuShow; //���һ����Ŀʱ������ʾ
	extern CString g_sLangTxt_CoNuShow;
	extern CString g_sLangID_TestCoRe; //������ɣ������Զ�����·��������ģ������á�����
	extern CString g_sLangTxt_TestCoRe;
	extern CString g_sLangID_AdjustReportInfo; //��������������²���
	extern CString g_sLangTxt_AdjustReportInfo;
// 	extern CString g_sLangID_DeNoChTe; //1.ɾ��û��ѡ����Ե���Ŀ���౨�沿��
// 	extern CString g_sLangTxt_DeNoChTe;
// 	extern CString g_sLangID_RepUse; //2.����û�в��ԵĲ��Ե㣬�հײ��ֱ���ʹ�á��������滻
// 	extern CString g_sLangTxt_RepUse;
// 	extern CString g_sLangID_AdjustSure; //�������ֲ����Իظ���ȷ��Ҫ������
// 	extern CString g_sLangTxt_AdjustSure;
	extern CString g_sLangID_StartX; //���X
	extern CString g_sLangTxt_StartX;	
	extern CString g_sLangID_StartY; //���Y
	extern CString g_sLangTxt_StartY;	
	extern CString g_sLangID_NowX; //��ǰX
	extern CString g_sLangTxt_NowX;
	extern CString g_sLangID_NowY; //��ǰY
	extern CString g_sLangTxt_NowY;
	extern CString g_sLangID_EndPointX; //�յ�X
	extern CString g_sLangTxt_EndPointX;
	extern CString g_sLangID_EndPointY; //�յ�Y
	extern CString g_sLangTxt_EndPointY;
	extern CString g_sLangID_TestConR; //������ǿ��ƽӿڳ������֣�30s������ʧ�ܣ�����ֹ���̣��������������ǽӿڳ���
	extern CString g_sLangTxt_TestConR;
	extern CString g_sLangID_WarningProTest; //�����⵽ϵͳ���к�ϵͳ��صĽ����������У��������ֹ���̡��ر����н���
	extern CString g_sLangTxt_WarningProTest;
	extern CString g_sLangID_StopProcess; //��ֹ����
	extern CString g_sLangTxt_StopProcess;
	extern CString g_sLangID_NeedCloPro; //��Ҫ�رյĽ���
	extern CString g_sLangTxt_NeedCloPro;
	extern CString g_sLangID_SouRepPath;      //Դ����·��
	extern CString g_sLangTxt_SouRepPath;
	extern CString g_sLangID_ExportSet;       //��������
	extern CString g_sLangTxt_ExportSet;
	extern CString g_sLangID_ExportPath;      //����·��
	extern CString g_sLangTxt_ExportPath;
	extern CString g_sLangID_ExFileName;      //�����ļ�����
	extern CString g_sLangTxt_ExFileName;
	extern CString g_sLangID_ChoFileModel;    //ѡ���ļ�ģ��
	extern CString g_sLangTxt_ChoFileModel;
	extern CString g_sLangID_RepViewRat;    //������ʾ����
	extern CString g_sLangTxt_RepViewRat;
	extern CString g_sLangID_RepViRaCho;    //������ʾ����ѡ��
	extern CString g_sLangTxt_RepViRaCho;
	extern CString g_sLangID_TestRepViRaSet;    //���鱨����ʾ��������
	extern CString g_sLangTxt_TestRepViRaSet;
	extern CString g_sLangID_NoChProTem;//û��ѡ���Լģ��
	extern CString g_sLangTxt_NoChProTem;
	extern CString g_sLangID_NoChTestTem;//û��ѡ�����ģ��
	extern CString g_sLangTxt_NoChTestTem;
	extern CString g_sLangID_ChTemplet;//ѡ��ģ��
	extern CString g_sLangTxt_ChTemplet;
	extern CString g_sLangID_ChProtocol;//ѡ���Լ
	extern CString g_sLangTxt_ChProtocol;
	extern CString g_sLangID_SettingsChoose;//������ѡ��
	extern CString g_sLangTxt_SettingsChoose;
	extern CString g_sLangID_SetMulDev;//���ö�װ��
	extern CString g_sLangTxt_SetMulDev;
	extern CString g_sLangID_SetMulDevMgrp;//���ö�װ�ö���
	extern CString g_sLangTxt_SetMulDevMgrp;
	extern CString g_sLangID_NoChTemFile;//û��ѡ��ģ���ļ�
	extern CString g_sLangTxt_NoChTemFile;
	extern CString g_sLangID_RepFileNameNu;//�����ļ���Ϊ��
	extern CString g_sLangTxt_RepFileNameNu;
	extern CString g_sLangID_NoChTestType;//û��ѡ���������
	extern CString g_sLangTxt_NoChTestType;
	extern CString g_sLangID_CommSetInf;//ͨѶ������Ϣ��ȫ
	extern CString g_sLangTxt_CommSetInf;
	extern CString g_sLangID_TabFileNoSel;//����ļ�û��ѡ��
	extern CString g_sLangTxt_TabFileNoSel;
	extern CString g_sLangID_AlreadyExists;//%s �Ѿ�����
	extern CString g_sLangTxt_AlreadyExists;
	extern CString g_sLangID_UnquaItem;//���ϸ���Ŀ
	extern CString g_sLangTxt_UnquaItem;
// 	extern CString g_sLangID_ModelFile;//ģ���ļ�
// 	extern CString g_sLangTxt_ModelFile;
	extern CString g_sLangID_NoAddDevTestRep;//û�����װ�ò��Ա���
	extern CString g_sLangTxt_NoAddDevTestRep;
	extern CString g_sLangID_OlAddOnRep;//ֻ�����һ��װ�ò��Ա���
	extern CString g_sLangTxt_OlAddOnRep;
	extern CString g_sLangID_ProtocoTemplate;//��Լģ��
	extern CString g_sLangTxt_ProtocoTemplate;
	extern CString g_sLangID_ProtocoMatching;//��Լ����
	extern CString g_sLangTxt_ProtocoMatching;
	extern CString g_sLangID_ChRptRe;//ѡ�񱨸浼��Ŀ��Ŀ¼
	extern CString g_sLangTxt_ChRptRe;
	extern CString g_sLangID_AlOpen;//�Ѿ��򿪡�%s������رպ��ڴ������Ա��棡
	extern CString g_sLangTxt_AlOpen;
	extern CString g_sLangID_TaskTotalTime;//������ʱ��
	extern CString g_sLangTxt_TaskTotalTime;
	extern CString g_sLangID_RptTotalTime;//������ʱ��
	extern CString g_sLangTxt_RptTotalTime;
	extern CString g_sLangID_NoTitle;//�ޱ���
	extern CString g_sLangTxt_NoTitle;
	extern CString g_sLangID_TestingClose;//���ڲ����У����ܹر�...
	extern CString g_sLangTxt_TestingClose;
	extern CString g_sLangID_FileUnExistS;//�ļ�\"%s\"������
	extern CString g_sLangTxt_FileUnExistS;
	extern CString g_sLangID_SelOrCretFile;//�ļ��С�%s�������в��Ա����ļ�\n��ѡ����ߴ���һ���յ��ļ���
	extern CString g_sLangTxt_SelOrCretFile;
	extern CString g_sLangID_SelFilePath;//��ѡ�񱨸��ļ��洢��·����
	extern CString g_sLangTxt_SelFilePath;
	extern CString g_sLangID_DelTaskYOrN;//�Ƿ�Ҫɾ������ %s ��������
	extern CString g_sLangTxt_DelTaskYOrN;
	extern CString g_sLangID_SureDelAgain;//���ٴ�ȷ��ɾ��
	extern CString g_sLangTxt_SureDelAgain;
	extern CString g_sLangID_DelFailItem;//ɾ���������а����Ѿ����򿪵Ĺ��̣�ɾ��ʧ��
	extern CString g_sLangTxt_DelFailItem;
	extern CString g_sLangID_DelItemYOrN;//�Ƿ�Ҫɾ������ %s
	extern CString g_sLangTxt_DelItemYOrN;
	extern CString g_sLangID_DelFailure;//�ù����Ѿ����򿪣�ɾ��ʧ��
	extern CString g_sLangTxt_DelFailure;
	extern CString g_sLangID_StartRptYOrN;//����ʼ���桱����ֻ���Ե�ǰ�򿪵Ĳ��Ա��棬\r\n��ȷʵֻҪ���Բ��������еĵ������Ա�����\r\n\r\nѡ���ǡ����Ե�������\r\nѡ�񡰷񡱿�ʼ�������\r\nѡ��ȡ������ֹ����")
	extern CString g_sLangTxt_StartRptYOrN;
	extern CString g_sLangID_NewTestClear;//�½����ԣ������ǰ����������\r\n
	extern CString g_sLangTxt_NewTestClear;
	extern CString g_sLangID_SelYes;//ѡ���ǡ������ǰ�������ݣ��½�����\r\n
	extern CString g_sLangTxt_SelYes;
	extern CString g_sLangID_SelNo;//ѡ�񡰷񡱣��������ǰ�������ݣ��½�����\r\n
	extern CString g_sLangTxt_SelNo;
	extern CString g_sLangID_SelCancel;//ѡ��ȡ����������ʼ����
	extern CString g_sLangTxt_SelCancel;
	extern CString g_sLangID_WavCpntNotExist;//¼�����������
	extern CString g_sLangTxt_WavCpntNotExist;
	extern CString g_sLangID_UnAutoTest;//û�������Զ����ԣ��޷�ִ������
	extern CString g_sLangTxt_UnAutoTest;
	extern CString g_sLangID_ToolUnExitS;//���ߡ�%s����%s��������
	extern CString g_sLangTxt_ToolUnExitS;
	extern CString g_sLangID_TestTaskFnshS;//��������%s���������
	extern CString g_sLangTxt_TestTaskFnshS;
	extern CString g_sLangID_StartTestS;//��ʼ���ԡ�%s��
	extern CString g_sLangTxt_StartTestS;
	extern CString g_sLangID_TestTempS;//����ģ��*******%s
	extern CString g_sLangTxt_TestTempS;
	extern CString g_sLangID_ReportFileS;//�����ļ�*******%s
	extern CString g_sLangTxt_ReportFileS;
	extern CString g_sLangID_ModelFileS;//ģ���ļ�********%s
	extern CString g_sLangTxt_ModelFileS;
	extern CString g_sLangID_PrtcTemS;//��Լģ��********%s
	extern CString g_sLangTxt_PrtcTemS;
	extern CString g_sLangID_AutoTestContrl;//�Զ����Կ�������
	extern CString g_sLangTxt_AutoTestContrl;
// 	extern CString g_sLangID_SGroupS;//%s%s-��%d.%s
// 	extern CString g_sLangTxt_SGroupS;
// 	extern CString g_sLangID_SGroupFileName;//%s%s-��%d.%s
// 	extern CString g_sLangTxt_SGroupFileName;
	extern CString g_sLangID_RightBuy;//Demo�汾��ֻ��ʹ��ģ�塾Demo-PSL-641U�����빺����ʽ�汾��
	extern CString g_sLangTxt_RightBuy;
	extern CString g_sLangID_MainView2;//����ͼ:
	extern CString g_sLangTxt_MainView2;
	extern CString g_sLangID_GroupReport;//��%d����
	extern CString g_sLangTxt_GroupReport;
	extern CString g_sLangID_ProcessStop;//�Ͳ�����صĽ����Ѿ�����ֹ
	extern CString g_sLangTxt_ProcessStop;
	extern CString g_sLangID_SelObjPath;//ѡ��Ŀ��·��
	extern CString g_sLangTxt_SelObjPath;
	extern CString g_sLangID_FileNameIncl;//�ļ����ư����Ƿ��ַ�: %s
	extern CString g_sLangTxt_FileNameIncl;
	extern CString g_sLangID_ReportEptFinsh;//���浼�����
	extern CString g_sLangTxt_ReportEptFinsh;
	extern CString g_sLangID_ObjFileExistOvwt;//Ŀ���ļ��Ѿ�����,������?
	extern CString g_sLangTxt_ObjFileExistOvwt;
	extern CString g_sLangID_ReportTestTempt;//���桾%s����Ӧ�Ĳ���ģ��:��%s��
	extern CString g_sLangTxt_ReportTestTempt;
	extern CString g_sLangID_SureToDele;//��ȷʵҪɾ����%s����
	extern CString g_sLangTxt_SureToDele;
	extern CString g_sLangID_UnQualifadS;//[%s]���ϸ�
	extern CString g_sLangTxt_UnQualifadS;
	extern CString g_sLangID_TestOver;//********���Խ���********
	extern CString g_sLangTxt_TestOver;
	extern CString g_sLangID_CopyOutput;//�������
	extern CString g_sLangTxt_CopyOutput;
	extern CString g_sLangID_ClearOutput;//������
	extern CString g_sLangTxt_ClearOutput;
// 	extern CString g_sLangID_Unqualified2;//%s[���ϸ�]
// 	extern CString g_sLangTxt_Unqualified2;
	extern CString g_sLangID_NoAddTestRpt;//û����Ӳ��Ա���
	extern CString g_sLangTxt_NoAddTestRpt;
	extern CString g_sLangID_OneTestRpt;//ֻ�����һ�����Ա���
	extern CString g_sLangTxt_OneTestRpt;
	extern CString g_sLangID_NoSelPrtcTem;//װ�ñ����б�ڡ�%d��û��ѡ���Լģ��
	extern CString g_sLangTxt_NoSelPrtcTem;
	extern CString g_sLangID_NoSelFile;//װ�ñ����б�ڡ�%d��û��ѡ�����ļ�
	extern CString g_sLangTxt_NoSelFile;
	extern CString g_sLangID_NameSame;//װ�ñ����б�ڡ�%d����ڡ�%d�����ơ�%s����ͬ
	extern CString g_sLangTxt_NameSame;
	extern CString g_sLangID_PrtcSame;//װ�ñ����б�ڡ�%d����ڡ�%d����Լģ�塾%s����ͬ
	extern CString g_sLangTxt_PrtcSame;
	extern CString g_sLangID_IPSame;//װ�ñ����б�ڡ�%d����ڡ�%d��IP��%s����ͬ
	extern CString g_sLangTxt_IPSame;
	extern CString g_sLangID_ToolTip_32781;//�򿪱���
	extern CString g_sLangTxt_ToolTip_32781;
	extern CString g_sLangID_ToolTip_32776;//��ӱ���
	extern CString g_sLangTxt_ToolTip_32776;
	extern CString g_sLangID_ToolTip_32777;//ɾ������
	extern CString g_sLangTxt_ToolTip_32777;
	extern CString g_sLangID_ToolTip_32783;//�ָ���δ��ɵ�״̬
	extern CString g_sLangTxt_ToolTip_32783;
	extern CString g_sLangID_ToolTip_32778;//���Ʊ���
    extern CString g_sLangTxt_ToolTip_32778;
	extern CString g_sLangID_ToolTip_32779;//���Ʊ���
	extern CString g_sLangTxt_ToolTip_32779;
	extern CString g_sLangID_ToolTip_32784;//��ʾ�����Ӧ��ģ��
	extern CString g_sLangTxt_ToolTip_32784;
	extern CString g_sLangID_ToolTip_32775;//�������񱨸�
	extern CString g_sLangTxt_ToolTip_32775;
	extern CString g_sLangID_ToolTip_32782;//�ر�����
	extern CString g_sLangTxt_ToolTip_32782;

	extern CString g_sLangID_Menu_57634;
	extern CString g_sLangTxt_Menu_57634;
	extern CString g_sLangID_Menu_57632;
	extern CString g_sLangTxt_Menu_57632;

	extern CString g_sLangID_ToolTip_32789;
	extern CString g_sLangTxt_ToolTip_32789;
	extern CString g_sLangID_StitchRptFinish;
	extern CString g_sLangTxt_StitchRptFinish;

	//2016-12-10
	extern CString g_sLangID_ToolTip_2000;
	extern CString g_sLangTxt_ToolTip_2000;
	extern CString g_sLangID_ToolTip_32786;
	extern CString g_sLangTxt_ToolTip_32786;
	extern CString g_sLangID_ToolTip_32788;
	extern CString g_sLangTxt_ToolTip_32788;
	extern CString g_sLangID_ToolTip_2001;
	extern CString g_sLangTxt_ToolTip_2001;
	extern CString g_sLangID_ToolTip_32785;
	extern CString g_sLangTxt_ToolTip_32785;
	extern CString g_sLangID_ToolTip_351;
	extern CString g_sLangTxt_ToolTip_351;
	extern CString g_sLangID_ToolTip_314;
	extern CString g_sLangTxt_ToolTip_314;
	extern CString g_sLangID_ToolTip_320;
	extern CString g_sLangTxt_ToolTip_320;
	extern CString g_sLangID_ToolTip_330;
	extern CString g_sLangTxt_ToolTip_330;
	extern CString g_sLangID_ToolTip_358;
	extern CString g_sLangTxt_ToolTip_358;
	extern CString g_sLangID_ToolTip_347;
	extern CString g_sLangTxt_ToolTip_347;
	extern CString g_sLangID_ToolTip_310;
	extern CString g_sLangTxt_ToolTip_310;
	extern CString g_sLangID_ToolTip_348;
	extern CString g_sLangTxt_ToolTip_348;
	extern CString g_sLangID_ToolTip_349;
	extern CString g_sLangTxt_ToolTip_349;
	extern CString g_sLangID_ToolTip_350;
	extern CString g_sLangTxt_ToolTip_350;
	extern CString g_sLangID_ToolTip_357;
	extern CString g_sLangTxt_ToolTip_357;

	//shaolei 2024-3-25
	extern CString g_sLangID_GbDevice;  //=_T("sGbDevice");
	extern CString g_sLangTxt_GbDevice;  //=_T("�豸");
	extern CString g_sLangID_SysParaCfg;  //=_T("sSysParaCfg");
	extern CString g_sLangTxt_SysParaCfg;  //=_T("ϵͳ��������");
	extern CString g_sLangID_ChMapsConfig;  //= _T("sChMapsConfig");
	extern CString g_sLangTxt_ChMapsConfig;  //= _T("Ӳ��ͨ��ӳ��");
	extern CString g_sLangID_Iec61850Cfg;  //=_T("sIec61850Cfg");
	extern CString g_sLangTxt_Iec61850Cfg;  //=_T("IEC61850����");
	extern CString g_sLangID_BeforeTest;  //=_T("sBeforeTest");
	extern CString g_sLangTxt_BeforeTest;  //=_T("����ǰ׼��");
	extern CString g_sLangID_NotTest;  //=_T("sNotTest");
	extern CString g_sLangTxt_NotTest;  //=_T("δ����");
	extern CString g_sLangID_RsltEvaluation;  //=_T("sRsltEvaluation");
	extern CString g_sLangTxt_RsltEvaluation;  //=_T("�������");
	extern CString g_sLangID_TSet;  //=_T("sTSet");
	extern CString g_sLangTxt_TSet;  //=_T("����ʱ������ֵ(s)");
	extern CString g_sLangID_USet;  //=_T("sUSet");
	extern CString g_sLangTxt_USet;  //=_T("��ѹ��������ֵ(V)");
	extern CString g_sLangID_ISet;  //=_T("sISet");
	extern CString g_sLangTxt_ISet;  //=_T("������������ֵ(A)");
	extern CString g_sLangID_AngleSet;  //=_T("sAngleSet");
	extern CString g_sLangTxt_AngleSet;  //=_T("��λ��������ֵ(��)");
	extern CString g_sLangID_HzSet;  //=_T("sHzSet");
	extern CString g_sLangTxt_HzSet;  //=_T("Ƶ����������ֵ(Hz)");
	extern CString g_sLangID_ReturnCoefSet;  //=_T("sReturnCoefSet");
	extern CString g_sLangTxt_ReturnCoefSet;  //=_T("����ϵ������ֵ");
	extern CString g_sLangID_MaxAngleSet;  //=_T("sMaxAngleSet");
	extern CString g_sLangTxt_MaxAngleSet;  //=_T("�������������ֵ(��)");
	extern CString g_sLangID_AngleFSet;  //=_T("sAngleFSet");
	extern CString g_sLangTxt_AngleFSet;  //=_T("�߽��1����ֵ(��)");
	extern CString g_sLangID_AngleSSet;  //=_T("sAngleSSet");
	extern CString g_sLangTxt_AngleSSet;  //=_T("�߽��2����ֵ(��)");
	extern CString g_sLangID_T_AbsErr_Max;  //=_T("sT_AbsErr_Max");
	extern CString g_sLangTxt_T_AbsErr_Max;  //=_T("����ʱ�����������ֵ(ms)");
	extern CString g_sLangID_T_AbsErr_Min;  //=_T("sT_AbsErr_Min");
	extern CString g_sLangTxt_T_AbsErr_Min;  //=_T("����ʱ����������Сֵ(ms)");
	extern CString g_sLangID_T_RelErr_Max;  //=_T("sT_RelErr_Max");
	extern CString g_sLangTxt_T_RelErr_Max;  //=_T("����ʱ�����������ֵ(%)");
	extern CString g_sLangID_T_RelErr_Min;  //=_T("sT_RelsErr_Min");
	extern CString g_sLangTxt_T_RelErr_Min;  //=_T("����ʱ����������Сֵ(%)");
	extern CString g_sLangID_U_AbsErr_Max;  //=_T("sU_AbsErr_Max");
	extern CString g_sLangTxt_U_AbsErr_Max;  //=_T("��ѹ����ֵ����������ֵ(V)");
	extern CString g_sLangID_U_AbsErr_Min;  //=_T("sU_AbsErr_Min");
	extern CString g_sLangTxt_U_AbsErr_Min;  //=_T("��ѹ����ֵ���������Сֵ(V)");
	extern CString g_sLangID_U_RelErr_Max;  //=_T("sU_RelErr_Max");
	extern CString g_sLangTxt_U_RelErr_Max;  //=_T("��ѹ����ֵ���������ֵ(%)");
	extern CString g_sLangID_U_RelErr_Min;  //=_T("sU_RelsErr_Min");
	extern CString g_sLangTxt_U_RelErr_Min;  //=_T("��ѹ����ֵ��������Сֵ(%)");
	extern CString g_sLangID_I_AbsErr_Max;  //=_T("sI_AbsErr_Max");
	extern CString g_sLangTxt_I_AbsErr_Max;  //=_T("��������ֵ����������ֵ(A)");
	extern CString g_sLangID_I_AbsErr_Min;  //=_T("sI_AbsErr_Min");
	extern CString g_sLangTxt_I_AbsErr_Min;  //=_T("��������ֵ���������Сֵ(A)");
	extern CString g_sLangID_I_RelErr_Max;  //=_T("sI_RelErr_Max");
	extern CString g_sLangTxt_I_RelErr_Max;  //=_T("��������ֵ���������ֵ(%)");
	extern CString g_sLangID_I_RelErr_Min;  //=_T("sI_RelsErr_Min");
	extern CString g_sLangTxt_I_RelErr_Min;  //=_T("��������ֵ��������Сֵ(%)");
	extern CString g_sLangID_Angle_AbsErr_Max;  //=_T("sAngle_AbsErr_Max");
	extern CString g_sLangTxt_Angle_AbsErr_Max;  //=_T("��λ����ֵ����������ֵ(��)");
	extern CString g_sLangID_Angle_AbsErr_Min;  //=_T("sAngle_AbsErr_Min");
	extern CString g_sLangTxt_Angle_AbsErr_Min;  //=_T("��λ����ֵ���������Сֵ(��)");
	extern CString g_sLangID_Hz_AbsErr_Max;  //=_T("sHz_AbsErr_Max");
	extern CString g_sLangTxt_Hz_AbsErr_Max;  //=_T("Ƶ�ʶ���ֵ����������ֵ(Hz)");
	extern CString g_sLangID_Hz_AbsErr_Min;  //=_T("sHz_AbsErr_Min");
	extern CString g_sLangTxt_Hz_AbsErr_Min;  //=_T("Ƶ�ʶ���ֵ���������Сֵ(Hz)");
	extern CString g_sLangID_RetCoef_AbsErr_Max;  //=_T("sRetCoef_AbsErr_Max");
	extern CString g_sLangTxt_RetCoef_AbsErr_Max;  //=_T("����ϵ������������ֵ");
	extern CString g_sLangID_RetCoef_AbsErr_Min;  //=_T("sRetCoef_AbsErr_Min");
	extern CString g_sLangTxt_RetCoef_AbsErr_Min;  //=_T("����ϵ�����������Сֵ");
	extern CString g_sLangID_MaxAngle_AbsErr_Max;  //=_T("sMaxAngle_AbsErr_Max");
	extern CString g_sLangTxt_MaxAngle_AbsErr_Max;  //=_T("��������Ǿ���������ֵ(��)");
	extern CString g_sLangID_MaxAngle_AbsErr_Min;  //=_T("sMaxAngle_AbsErr_Min");
	extern CString g_sLangTxt_MaxAngle_AbsErr_Min;  //=_T("��������Ǿ��������Сֵ(��)");
	extern CString g_sLangID_AngleF_AbsErr_Max;  //=_T("sAngleF_AbsErr_Max");
	extern CString g_sLangTxt_AngleF_AbsErr_Max;  //=_T("�߽��1����������ֵ(��)");
	extern CString g_sLangID_AngleF_AbsErr_Min;  //=_T("sAngleF_AbsErr_Min");
	extern CString g_sLangTxt_AngleF_AbsErr_Min;  //=_T("�߽��1���������Сֵ(��)");
	extern CString g_sLangID_AngleS_AbsErr_Max;  //=_T("sAngleS_AbsErr_Max");
	extern CString g_sLangTxt_AngleS_AbsErr_Max;  //=_T("�߽��2����������ֵ(��)");
	extern CString g_sLangID_AngleS_AbsErr_Min;  //=_T("sAngleS_AbsErr_Min");
	extern CString g_sLangTxt_AngleS_AbsErr_Min;  //=_T("�߽��2�Ǿ��������Сֵ(��)");
	extern CString g_sLangID_T_Act;  //=_T("sT_Act");
	extern CString g_sLangTxt_T_Act;  //=_T("����ʱ��(s)");
	extern CString g_sLangID_T_ErrRel;  //=_T("sT_ErrRel");
	extern CString g_sLangTxt_T_ErrRel;  //=_T("����ʱ����������(%)");
	extern CString g_sLangID_T_ErrAbs;  //=_T("sT_ErrAbs");
	extern CString g_sLangTxt_T_ErrAbs;  //=_T("����ʱ����������(s)");
	extern CString g_sLangID_T_RelErr;  //=_T("sT_RelErr");
	extern CString g_sLangTxt_T_RelErr;  //=_T("����ʱ��������ֵ(%)");
	extern CString g_sLangID_T_AbsErr;  //=_T("sT_AbsErr");
	extern CString g_sLangTxt_T_AbsErr;  //=_T("����ʱ��������ֵ(ms)");
	extern CString g_sLangID_U_RelErr;  //=_T("sU_RelErr");
	extern CString g_sLangTxt_U_RelErr;  //=_T("��ѹ����ֵ������ֵ(%)");
	extern CString g_sLangID_U_AbsErr;  //=_T("sU_AbsErr");
	extern CString g_sLangTxt_U_AbsErr;  //=_T("��ѹ����ֵ�������ֵ(V)");
	extern CString g_sLangID_U_ErrRel;  //=_T("sU_ErrRel");
	extern CString g_sLangTxt_U_ErrRel;  //=_T("��ѹ����ֵ��������(%)");
	extern CString g_sLangID_U_ErrAbs;  //=_T("sU_ErrAbs");
	extern CString g_sLangTxt_U_ErrAbs;  //=_T("��ѹ����ֵ���������(V)");
	extern CString g_sLangID_U_Act;  //=_T("sU_Act");
	extern CString g_sLangTxt_U_Act;  //=_T("��ѹ����ֵ(V)");
	extern CString g_sLangID_I_RelErr;  //=_T("sI_RelErr");
	extern CString g_sLangTxt_I_RelErr;  //=_T("��������ֵ������ֵ(%)");
	extern CString g_sLangID_I_AbsErr;  //=_T("sI_AbsErr");
	extern CString g_sLangTxt_I_AbsErr;  //=_T("��������ֵ�������ֵ(A)");
	extern CString g_sLangID_I_ErrRel;  //=_T("sI_ErrRel");
	extern CString g_sLangTxt_I_ErrRel;  //=_T("��������ֵ��������(%)");
	extern CString g_sLangID_I_ErrAbs;  //=_T("sI_ErrAbs");
	extern CString g_sLangTxt_I_ErrAbs;  //=_T("��������ֵ���������(A)");
	extern CString g_sLangID_I_Act;  //=_T("sI_Act");
	extern CString g_sLangTxt_I_Act;  //=_T("��������ֵ(A)");
	extern CString g_sLangID_Angle_RelErr;  //=_T("sAngle_RelErr");
	extern CString g_sLangTxt_Angle_RelErr;  //=_T("��λ����ֵ������ֵ(%)");
	extern CString g_sLangID_Angle_AbsErr;  //=_T("sAngle_AbsErr");
	extern CString g_sLangTxt_Angle_AbsErr;  //=_T("��λ����ֵ�������ֵ(��)");
	extern CString g_sLangID_Angle_ErrRel;  //=_T("sAngle_ErrRel");
	extern CString g_sLangTxt_Angle_ErrRel;  //=_T("��λ����ֵ��������(%)");
	extern CString g_sLangID_Angle_ErrAbs;  //=_T("sAngle_ErrAbs");
	extern CString g_sLangTxt_Angle_ErrAbs;  //=_T("��λ����ֵ���������(��)");
	extern CString g_sLangID_Angle_Act;  //=_T("sAngle_Act");
	extern CString g_sLangTxt_Angle_Act;  //=_T("��λ����ֵ(��)");
	extern CString g_sLangID_Hz_RelErr;  //=_T("sHz_RelErr");
	extern CString g_sLangTxt_Hz_RelErr;  //=_T("Ƶ�ʶ���ֵ������ֵ(%)");
	extern CString g_sLangID_Hz_AbsErr;  //=_T("sHz_AbsErr");
	extern CString g_sLangTxt_Hz_AbsErr;  //=_T("Ƶ�ʶ���ֵ�������ֵ(Hz)");
	extern CString g_sLangID_Hz_ErrRel;  //=_T("sHz_ErrRel");
	extern CString g_sLangTxt_Hz_ErrRel;  //=_T("Ƶ�ʶ���ֵ��������(%)");
	extern CString g_sLangID_Hz_ErrAbs;  //=_T("sHz_ErrAbs");
	extern CString g_sLangTxt_Hz_ErrAbs;  //=_T("Ƶ�ʶ���ֵ���������(Hz)");
	extern CString g_sLangID_Hz_Act;  //=_T("sHz_Act");
	extern CString g_sLangTxt_Hz_Act;  //=_T("Ƶ�ʶ���ֵ(Hz)");
	extern CString g_sLangID_ReturnCoef_AbsErr;  //=_T("sReturnCoef_AbsErr");
	extern CString g_sLangTxt_ReturnCoef_AbsErr;  //=_T("����ϵ���������ֵ");
	extern CString g_sLangID_ReturnCoef_ErrAbs;  //=_T("sReturnCoef_ErrAbs");
	extern CString g_sLangTxt_ReturnCoef_ErrAbs;  //=_T("����ϵ�����������");
	extern CString g_sLangID_ReturnCoef_Act;  //=_T("sReturnCoef_Act");
	extern CString g_sLangTxt_ReturnCoef_Act;  //=_T("����ϵ��");
	extern CString g_sLangID_MaxAngle_AbsErr;  //=_T("sMaxAngle_AbsErr");
	extern CString g_sLangTxt_MaxAngle_AbsErr;  //=_T("���������ֵ�������ֵ(��)");
	extern CString g_sLangID_MaxAngle_ErrAbs;  //=_T("sMaxAngle_ErrAbs");
	extern CString g_sLangTxt_MaxAngle_ErrAbs;  //=_T("��������Ǿ��������(��)");
	extern CString g_sLangID_AngleF_AbsErr;  //=_T("sAngleF_AbsErr");
	extern CString g_sLangTxt_AngleF_AbsErr;  //=_T("�߽��1ֵ�������ֵ(��)");
	extern CString g_sLangID_AngleF_ErrAbs;  //=_T("sAngleF_ErrAbs");
	extern CString g_sLangTxt_AngleF_ErrAbs;  //=_T("�߽��1���������(��)");
	extern CString g_sLangID_AngleS_AbsErr;  //=_T("sAngleS_AbsErr");
	extern CString g_sLangTxt_AngleS_AbsErr;  //=_T("�߽��2ֵ�������ֵ(��)");
	extern CString g_sLangID_AngleS_ErrAbs;  //=_T("sAngleS_ErrAbs");
	extern CString g_sLangTxt_AngleS_ErrAbs;  //=_T("�߽��2���������(��)");
	extern CString g_sLangID_ReadAin;  //=_T("sReadAin");
	extern CString g_sLangTxt_ReadAin;  //=_T("��ң��");
	extern CString g_sLangID_WriteSetting;  //=_T("sWriteSetting");
	extern CString g_sLangTxt_WriteSetting;  //=_T("�޸Ķ�ֵ");
	extern CString g_sLangID_WriteEna;  //=_T("sWriteEna");
	extern CString g_sLangTxt_WriteEna;  //=_T("Ͷ��ѹ��");
	extern CString g_sLangID_Reset;  //=_T("sReset");
	extern CString g_sLangTxt_Reset;  //=_T("-����̬");
	extern CString g_sLangID_BeforeTestGrp;  //=_T("sBeforeTestGrp");
	extern CString g_sLangTxt_BeforeTestGrp;  //=_T("����ǰ_�����");
	extern CString g_sLangID_ImportDvm;  //=_T("sImportDvm");
	extern CString g_sLangTxt_ImportDvm;  //=_T("����ģ��");
	extern CString g_sLangID_BeforeComm;  //=_T("sBeforeComm");
	extern CString g_sLangTxt_BeforeComm;  //=_T("ͨ��ǰ׼��");
	extern CString g_sLangID_AfterComm;  //=_T("sAfterComm");
	extern CString g_sLangTxt_IAfterComm;  //=_T("ͨ�ź�ָ�");


	//add 2024-8-27
	extern CString g_sLangID_SpowerSet;  //=_T("sSpowerSet");
	extern CString g_sLangTxt_SpowerSet;  //=_T("���ڹ�����������ֵ(VA)");
	extern CString g_sLangID_Spower_RelErr;  //=_T("sSpower_ErrRel"); 
	extern CString g_sLangTxt_Spower_RelErr;  //=_T("���ڹ���������ֵ(%)");
	extern CString g_sLangID_Spower_AbsErr;  //=_T("sSpower_AbsErr");
	extern CString g_sLangTxt_Spower_AbsErr;  //=_T("���ڹ��ʾ������ֵ(VA)");
	extern CString g_sLangID_Spower_ErrRel;  //=_T("sSpower_ErrRel");
	extern CString g_sLangTxt_Spower_ErrRel;  //=_T("���ڹ�����������(%)");
	extern CString g_sLangID_Spower_ErrAbs;  //=_T("sSpower_ErrAbs");
	extern CString g_sLangTxt_Spower_ErrAbs;  //=_T("���ڹ��ʾ��������(VA)");
	extern CString g_sLangID_PpowerSet;  //=_T("sPpowerSet");
	extern CString g_sLangTxt_PpowerSet;  //=_T("�й�������������ֵ(W)");
	extern CString g_sLangID_Ppower_RelErr;  //=_T("sPpower_RelErr");
	extern CString g_sLangTxt_Ppower_RelErr;  //=_T("�й�����������ֵ(%)");
	extern CString g_sLangID_Ppower_AbsErr;  //=_T("sPpower_AbsErr");
	extern CString g_sLangTxt_Ppower_AbsErr;  //=_T("�й����ʾ������ֵ(W)");
	extern CString g_sLangID_Ppower_ErrRel;  //=_T("sPpower_ErrRel");
	extern CString g_sLangTxt_Ppower_ErrRel;  //=_T("�й�������������(%)");
	extern CString g_sLangID_Ppower_ErrAbs;  //=_T("sPpower_ErrAbs");
	extern CString g_sLangTxt_Ppower_ErrAbs;  //=_T("�й����ʾ��������(W)");
	extern CString g_sLangID_QpowerSet;  //=_T("sQpowerSet");
	extern CString g_sLangTxt_QpowerSet;  //=_T("�޹�������������ֵ(Var)");
	extern CString g_sLangID_Qpower_RelErr;  //=_T("sQpower_RelErr");
	extern CString g_sLangTxt_Qpower_RelErr;  //=_T("�޹�����������ֵ(%)");
	extern CString g_sLangID_Qpower_AbsErr;  //=_T("sQpower_AbsErr");
	extern CString g_sLangTxt_Qpower_AbsErr;  //=_T("�޹����ʾ������ֵ(Var)");
	extern CString g_sLangID_Qpower_ErrRel;  //=_T("sQpower_ErrRel");
	extern CString g_sLangTxt_Qpower_ErrRel;  //=_T("�޹�������������(%)");
	extern CString g_sLangID_Qpower_ErrAbs;  //=_T("sQpower_ErrAbs");
	extern CString g_sLangTxt_Qpower_ErrAbs;  //=_T("�޹����ʾ��������(Var)");
	extern CString g_sLangID_Spower_AbsErr_Max;  //=_T("sSpower_AbsErr_Max");
	extern CString g_sLangTxt_Spower_AbsErr_Max;  //=_T("���ڹ��ʾ���������ֵ(VA)");
	extern CString g_sLangID_Spower_RelErr_Max;  //=_T("sSpower_RelErr_Max");
	extern CString g_sLangTxt_Spower_RelErr_Max;  //=_T("���ڹ������������ֵ(%)");
	extern CString g_sLangID_Spower_AbsErr_Min;  //=_T("sSpower_AbsErr_Min");
	extern CString g_sLangTxt_Spower_AbsErr_Min;  //=_T("���ڹ��ʾ��������Сֵ(VA)");
	extern CString g_sLangID_Spower_RelErr_Min;  //=_T("sSpower_RelErr_Min");
	extern CString g_sLangTxt_Spower_RelErr_Min;  //=_T("���ڹ�����������Сֵ(%)");
	extern CString g_sLangID_Ppower_AbsErr_Max;  //=_T("sPpower_AbsErr_Max");
	extern CString g_sLangTxt_Ppower_AbsErr_Max;  //=_T("�й����ʾ���������ֵ(W)");
	extern CString g_sLangID_Ppower_RelErr_Max;  //=_T("sPpower_RelErr_Max");
	extern CString g_sLangTxt_Ppower_RelErr_Max;  //=_T("�й��������������ֵ(%)");
	extern CString g_sLangID_Ppower_AbsErr_Min;  //=_T("sPpower_AbsErr_Min");
	extern CString g_sLangTxt_Ppower_AbsErr_Min;  //=_T("�й����ʾ��������Сֵ(W)");
	extern CString g_sLangID_Ppower_RelErr_Min;  //=_T("sPpower_RelErr_Min");
	extern CString g_sLangTxt_Ppower_RelErr_Min;  //=_T("�й�������������Сֵ(%)");
	extern CString g_sLangID_Qpower_AbsErr_Max;  //=_T("sQpower_AbsErr_Max");
	extern CString g_sLangTxt_Qpower_AbsErr_Max;  //=_T("�޹����ʾ���������ֵ(Var)");
	extern CString g_sLangID_Qpower_RelErr_Max;  //=_T("sQpower_RelErr_Max");
	extern CString g_sLangTxt_Qpower_RelErr_Max;  //=_T("�޹��������������ֵ(%)");
	extern CString g_sLangID_Qpower_AbsErr_Min;  //=_T("sQpower_AbsErr_Min");
	extern CString g_sLangTxt_Qpower_AbsErr_Min;  //=_T("�޹����ʾ��������Сֵ(Var)");
	extern CString g_sLangID_Qpower_RelErr_Min;  //=_T("sQpower_RelErr_Min");
	extern CString g_sLangTxt_Qpower_RelErr_Min;  //=_T("�޹�������������Сֵ(%)");
	extern CString g_sLangID_ImpAngleSet;  //=_T("sImpAngleSet");
	extern CString g_sLangTxt_ImpAngleSet;  //=_T("�迹����������ֵ(��)");
	extern CString g_sLangID_ImpAngle_RelErr;  //=_T("sImpAngle_RelErr");
	extern CString g_sLangTxt_ImpAngle_RelErr;  //=_T("�迹�Ƕ���ֵ������ֵ(%)");
	extern CString g_sLangID_ImpAngle_AbsErr;  //=_T("sImpAngle_AbsErr");
	extern CString g_sLangTxt_ImpAngle_AbsErr;  //=_T("�迹�Ƕ���ֵ�������ֵ(��)");
	extern CString g_sLangID_ImpAngle_ErrRel;  //=_T("sImpAngle_ErrRel");
	extern CString g_sLangTxt_ImpAngle_ErrRel;  //=_T("�迹�Ƕ���ֵ��������(%)");
	extern CString g_sLangID_ImpAngle_ErrAbs;  //=_T("sImpAngle_ErrAbs");
	extern CString g_sLangTxt_ImpAngle_ErrAbs;  //=_T("�迹�Ƕ���ֵ���������(��)");
	extern CString g_sLangID_ShortZImp;  //=_T("sShortZImp");
	extern CString g_sLangTxt_ShortZImp;  //=_T("��·�迹��������ֵ(��)");
	extern CString g_sLangID_ShortZImp_RelErr;  //=_T("sShortZImp_RelErr");
	extern CString g_sLangTxt_ShortZImp_RelErr;  //=_T("��·�迹����ֵ������ֵ(%)");
	extern CString g_sLangID_ShortZImp_AbsErr;  //=_T("sShortZImp_AbsErr");
	extern CString g_sLangTxt_ShortZImp_AbsErr;  //=_T("��·�迹����ֵ�������ֵ(��)");
	extern CString g_sLangID_ShortZImp_ErrRel;  //=_T("sShortZImp_ErrRel");
	extern CString g_sLangTxt_ShortZImp_ErrRel;  //=_T("��·�迹����ֵ��������(%)");
	extern CString g_sLangID_ShortZImp_ErrAbs;  //=_T("sShortZImp_ErrAbs");
	extern CString g_sLangTxt_ShortZImp_ErrAbs;  //=_T("��·�迹����ֵ���������(��)");
	extern CString g_sLangID_ImpAngle_AbsErr_Max;  //=_T("sImpAngle_AbsErr_Max");
	extern CString g_sLangTxt_ImpAngle_AbsErr_Max;  //=_T("�迹�Ƕ���ֵ����������ֵ(��)");
	extern CString g_sLangID_ImpAngle_RelErr_Max;  //=_T("sImpAngle_RelErr_Max");
	extern CString g_sLangTxt_ImpAngle_RelErr_Max;  //=_T("�迹�Ƕ���ֵ���������ֵ(%)");
	extern CString g_sLangID_ImpAngle_AbsErr_Min;  //=_T("sImpAngle_AbsErr_Min");
	extern CString g_sLangTxt_ImpAngle_AbsErr_Min;  //=_T("�迹�Ƕ���ֵ���������Сֵ(��)");
	extern CString g_sLangID_ImpAngle_RelErr_Min;  //=_T("sImpAngle_RelErr_Min");
	extern CString g_sLangTxt_ImpAngle_RelErr_Min;  //=_T("�迹�Ƕ���ֵ��������Сֵ(%)");
	extern CString g_sLangID_ShortZImp_AbsErr_Max;  //=_T("sShortZImp_AbsErr_Max");
	extern CString g_sLangTxt_ShortZImp_AbsErr_Max;  //=_T("��·�迹����ֵ����������ֵ(A)");
	extern CString g_sLangID_ShortZImp_RelErr_Max;  //=_T("sShortZImp_RelErr_Max");
	extern CString g_sLangTxt_ShortZImp_RelErr_Max;  //=_T("��·�迹����ֵ���������ֵ(%)");
	extern CString g_sLangID_ShortZImp_AbsErr_Min;  //=_T("sShortZImp_AbsErr_Min");
	extern CString g_sLangTxt_ShortZImp_AbsErr_Min;  //=_T("��·�迹����ֵ���������Сֵ(A)");
	extern CString g_sLangID_ShortZImp_RelErr_Min;  //=_T("sShortZImp_RelErr_Min");
	extern CString g_sLangTxt_ShortZImp_RelErr_Min;  //=_T("��·�迹����ֵ��������Сֵ(%)");
	extern CString g_sLangID_Hz_RelErr_Max;  //=_T("sHz_RelErr_Max");
	extern CString g_sLangTxt_Hz_RelErr_Max;  //=_T("Ƶ�ʶ���ֵ���������ֵ(%)");
	extern CString g_sLangID_Hz_RelErr_Min;  //=_T("sHz_RelErr_Min");
	extern CString g_sLangTxt_Hz_RelErr_Min;  //=_T("Ƶ�ʶ���ֵ��������Сֵ(%)")");
	extern CString g_sLangID_T_ErrAbsPos;  //=_T("sT_ErrAbsPos");
	extern CString g_sLangTxt_T_ErrAbsPos;  //=_T("����ʱ�������������(s)");
	extern CString g_sLangID_T_ErrAbsNeg;  //=_T("sT_ErrAbsNeg");
	extern CString g_sLangTxt_T_ErrAbsNeg;  //=_T("����ʱ�为���������(s)");
