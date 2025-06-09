#pragma once

#include "..\..\Module\XLanguage\XLanguageMngr.h"
#include "XLanguageResourceAts.h"

class CXLanguageResourceAts_SmartTest : public CXLanguageResourceAtsBase
{
// ����
public:
	CXLanguageResourceAts_SmartTest();
	virtual ~CXLanguageResourceAts_SmartTest();
	
private:
	CXLanguage m_oXLangRsAutoTest;
	static const CString  g_strXLangRsAutoTestFile;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();

public:
	static CString g_sLangID_Login; 
	static CString g_sLangTxt_Login;
	static CString g_sLangID_AutoTestVTip;//�����Զ�����ϵͳV1.0
	static CString g_sLangTxt_AutoTestVTip;
// 	static CString g_sLangID_FileOpen; 
// 	static CString g_sLangTxt_FileOpen;
	static CString g_sLangID_FileOpenTip; 
	static CString g_sLangTxt_FileOpenTip;
	static CString g_sLangID_Quit; 
	static CString g_sLangTxt_Quit;
	static CString g_sLangID_QuitTip; 
	static CString g_sLangTxt_QuitTip;
	static CString g_sLangID_RibbonRecentDocs; 
	static CString g_sLangTxt_RibbonRecentDocs;
	static CString g_sLangID_Config; 
	static CString g_sLangTxt_Config;
	static CString g_sLangID_AutoTestOper; 
	static CString g_sLangTxt_AutoTestOper;
// 	static CString g_sLangID_UpLoad; 
// 	static CString g_sLangTxt_UpLoad;
// 	static CString g_sLangID_DownLoad; 
// 	static CString g_sLangTxt_DownLoad;
	static CString g_sLangID_NewTest; 
	static CString g_sLangTxt_NewTest;
	static CString g_sLangID_MultiDevTest; 
	static CString g_sLangTxt_MultiDevTest;
	static CString g_sLangID_SinDevMulPro; 
	static CString g_sLangTxt_SinDevMulPro;
	static CString g_sLangID_SubTempTest; 
	static CString g_sLangTxt_SubTempTest;
	static CString g_sLangID_SingleDevTest;
	static CString g_sLangTxt_SingleDevTest;
	static CString g_sLangID_Test;
	static CString g_sLangTxt_Test; 
    static CString g_sLangID_StartTest; 
	static CString g_sLangTxt_StartTest;
	static CString g_sLangID_StartReport;
	static CString g_sLangTxt_StartReport;	
	static CString g_sLangID_Stop; 
	static CString g_sLangTxt_Stop;
	static CString g_sLangID_Report; 
	static CString g_sLangTxt_Report;
	static CString g_sLangID_ShowScale; 
	static CString g_sLangTxt_ShowScale;
	static CString g_sLangID_AdReport; 
	static CString g_sLangTxt_AdReport;
	static CString g_sLangID_PrintReport; 
	static CString g_sLangTxt_PrintReport;
	static CString g_sLangID_Settings; 
	static CString g_sLangTxt_Settings;	
	static CString g_sLangID_ReConfig; 
	static CString g_sLangTxt_ReConfig;
// 	static CString g_sLangID_View; 
// 	static CString g_sLangTxt_View;	
// 	static CString g_sLangID_StatusBarTip; 
// 	static CString g_sLangTxt_StatusBarTip;
	static CString g_sLangID_OutpWind; 
	static CString g_sLangTxt_OutpWind;
	static CString g_sLangID_FileManBar; 
	static CString g_sLangTxt_FileManBar;
	static CString g_sLangID_TestInfBar; 
	static CString g_sLangTxt_TestInfBar;//����������
	static CString g_sLangID_CharCurTest; 
	static CString g_sLangTxt_CharCurTest;//�������߲���
	static CString g_sLangID_TestTaskBar;
	static CString g_sLangTxt_TestTaskBar;
	static CString g_sLangID_ShowTestInf; 
	static CString g_sLangTxt_ShowTestInf;
// 	static CString g_sLangID_AboutTip; 
	static CString g_sLangTxt_AboutTip;
	static CString g_sLangID_ToAndCom; 
	static CString g_sLangTxt_ToAndCom;
	static CString g_sLangID_SysTools; 
	static CString g_sLangTxt_SysTools;
	static CString g_sLangID_SysCom; 
	static CString g_sLangTxt_SysCom;
	static CString g_sLangID_TestFileMan; 
	static CString g_sLangTxt_TestFileMan;
	static CString g_sLangID_TestItemField; 
	static CString g_sLangTxt_TestItemField;
	static CString g_sLangID_NewTestWork; //�½���������
	static CString g_sLangTxt_NewTestWork;
	static CString g_sLangID_TestInf; 
	static CString g_sLangTxt_TestInf;
	static CString g_sLangID_TaskName; 
	static CString g_sLangTxt_TaskName;
	static CString g_sLangID_TestType; 
	static CString g_sLangTxt_TestType;
	static CString g_sLangID_ProSet; 
	static CString g_sLangTxt_ProSet;
	static CString g_sLangID_ChoProTem; //ѡ���Լģ��
	static CString g_sLangTxt_ChoProTem;
	static CString g_sLangID_PoFile; 
	static CString g_sLangTxt_PoFile;
	static CString g_sLangID_ChoTest; 
	static CString g_sLangTxt_ChoTest;
	static CString g_sLangID_SelPoFile; //ѡ�����ļ�
	static CString g_sLangTxt_SelPoFile;
	static CString g_sLangID_TitleTask; 
	static CString g_sLangTxt_TitleTask;
	static CString g_sLangID_NewBuilt; //�½�
	static CString g_sLangTxt_NewBuilt;
	static CString g_sLangID_ReportAdjSh;//���������ʾ 
	static CString g_sLangTxt_ReportAdjSh;
	static CString g_sLangID_TestChoPro;//������ѡ�񣨲�������ѡ��ı䣬�����������Զ����Գ�������Ǹı���Ч�� 
	static CString g_sLangTxt_TestChoPro;
	static CString g_sLangID_AutoTestSysSet;//�Զ�����ϵͳ���� 
	static CString g_sLangTxt_AutoTestSysSet;
	static CString g_sLangID_AlarmAutoMain;//���桪�Զ����������� 
	static CString g_sLangTxt_AlarmAutoMain;
	static CString g_sLangID_TestFileName; //�����ļ���
	static CString g_sLangTxt_TestFileName;
	static CString g_sLangID_TesTyp; //��������
	static CString g_sLangTxt_TesTyp;
	static CString g_sLangID_ProTypeCho; //��Լ����ѡ��
	static CString g_sLangTxt_ProTypeCho;
	static CString g_sLangID_TestTempFile; //����ģ���ļ�
	static CString g_sLangTxt_TestTempFile;
	static CString g_sLangID_ProTempFile; //��Լģ���ļ�
	static CString g_sLangTxt_ProTempFile;
	static CString g_sLangID_ProHighSet; //��Լ�߼�����
	static CString g_sLangTxt_ProHighSet;
	static CString g_sLangID_ProTabFile; //��Լ����ļ�
	static CString g_sLangTxt_ProTabFile;
	static CString g_sLangID_RptData; //��������
	static CString g_sLangTxt_RptData;
	static CString g_sLangID_RptData2; //��������2
	static CString g_sLangTxt_RptData2;
	static CString g_sLangID_TestTemp; //����ģ��
	static CString g_sLangTxt_TestTemp;
	static CString g_sLangID_AppTestNo; //���ֲ��Բ��ϸ���Ŀ����
	static CString g_sLangTxt_AppTestNo;
	static CString g_sLangID_CTestCNum; //�ظ�������Ŀ�ظ�����
	static CString g_sLangTxt_CTestCNum;
	static CString g_sLangID_CoeMus; //��ʾ����
	static CString g_sLangTxt_CoeMus;
	static CString g_sLangID_AlarmMode; //�澯��ʽ
	static CString g_sLangTxt_AlarmMode;
	static CString g_sLangID_ContTest; //��������
	static CString g_sLangTxt_ContTest;
	static CString g_sLangID_LongAlarm; //������
	static CString g_sLangTxt_LongAlarm;
	static CString g_sLangID_ShortAlarm; //�̾���
	static CString g_sLangTxt_ShortAlarm;
	static CString g_sLangID_CusRepeat; //�Զ�������ظ�����
	static CString g_sLangTxt_CusRepeat;
	static CString g_sLangID_ComFaReNu; //ͨѶʧ�ܺ����Դ���
	static CString g_sLangTxt_ComFaReNu;
	static CString g_sLangID_RetComS; //����ͨѶǰ��ʱ
	static CString g_sLangTxt_RetComS;
	static CString g_sLangID_TestCoDe; //������Ŀ������ɳ���
	static CString g_sLangTxt_TestCoDe;
	static CString g_sLangID_CoNuShow; //���һ����Ŀʱ������ʾ
	static CString g_sLangTxt_CoNuShow;
	static CString g_sLangID_TestCoRe; //������ɣ������Զ�����·��������ģ������á�����
	static CString g_sLangTxt_TestCoRe;
// 	static CString g_sLangID_AdjustReport; //��������������²���
// 	static CString g_sLangTxt_AdjustReport;
	static CString g_sLangID_DeNoChTe; //1.ɾ��û��ѡ����Ե���Ŀ���౨�沿��
	static CString g_sLangTxt_DeNoChTe;
	static CString g_sLangID_RepUse; //2.����û�в��ԵĲ��Ե㣬�հײ��ֱ���ʹ�á��������滻
	static CString g_sLangTxt_RepUse;
	static CString g_sLangID_AdjustSure; //�������ֲ����Իظ���ȷ��Ҫ������
	static CString g_sLangTxt_AdjustSure;
	static CString g_sLangID_StartX; //���X
	static CString g_sLangTxt_StartX;	
	static CString g_sLangID_StartY; //���Y
	static CString g_sLangTxt_StartY;	
	static CString g_sLangID_NowX; //��ǰX
	static CString g_sLangTxt_NowX;
	static CString g_sLangID_NowY; //��ǰY
	static CString g_sLangTxt_NowY;
	static CString g_sLangID_EndPointX; //�յ�X
	static CString g_sLangTxt_EndPointX;
	static CString g_sLangID_EndPointY; //�յ�Y
	static CString g_sLangTxt_EndPointY;
	static CString g_sLangID_TestConR; //������ǿ��ƽӿڳ������֣�30s������ʧ�ܣ�����ֹ���̣��������������ǽӿڳ���
	static CString g_sLangTxt_TestConR;
	static CString g_sLangID_WarningProTest; //�����⵽ϵͳ���к�ϵͳ��صĽ����������У��������ֹ���̡��ر����н���
	static CString g_sLangTxt_WarningProTest;
	static CString g_sLangID_StopProcess; //��ֹ����
	static CString g_sLangTxt_StopProcess;
	static CString g_sLangID_NeedCloPro; //��Ҫ�رյĽ���
	static CString g_sLangTxt_NeedCloPro;
	static CString g_sLangID_SouRepPath;      //Դ����·��
	static CString g_sLangTxt_SouRepPath;
	static CString g_sLangID_ExportSet;       //��������
	static CString g_sLangTxt_ExportSet;
	static CString g_sLangID_ExportPath;      //����·��
	static CString g_sLangTxt_ExportPath;
	static CString g_sLangID_ExFileName;      //�����ļ�����
	static CString g_sLangTxt_ExFileName;
	static CString g_sLangID_ChoFileModel;    //ѡ���ļ�ģ��
	static CString g_sLangTxt_ChoFileModel;
	static CString g_sLangID_RepViewRat;    //������ʾ����
	static CString g_sLangTxt_RepViewRat;
	static CString g_sLangID_RepViRaCho;    //������ʾ����ѡ��
	static CString g_sLangTxt_RepViRaCho;
	static CString g_sLangID_TestRepViRaSet;    //���鱨����ʾ��������
	static CString g_sLangTxt_TestRepViRaSet;
	static CString g_sLangID_NoChProTem;//û��ѡ���Լģ��
	static CString g_sLangTxt_NoChProTem;
	static CString g_sLangID_NoChTestTem;//û��ѡ�����ģ��
	static CString g_sLangTxt_NoChTestTem;
	static CString g_sLangID_ChTemplet;//ѡ��ģ��
	static CString g_sLangTxt_ChTemplet;
	static CString g_sLangID_ChProtocol;//ѡ���Լ
	static CString g_sLangTxt_ChProtocol;
	static CString g_sLangID_SettingsChoose;//������ѡ��
	static CString g_sLangTxt_SettingsChoose;
	static CString g_sLangID_SetMulDev;//���ö�װ��
	static CString g_sLangTxt_SetMulDev;
	static CString g_sLangID_NoChTemFile;//û��ѡ��ģ���ļ�
	static CString g_sLangTxt_NoChTemFile;
	static CString g_sLangID_RepFileNameNu;//�����ļ���Ϊ��
	static CString g_sLangTxt_RepFileNameNu;
	static CString g_sLangID_NoChTestType;//û��ѡ���������
	static CString g_sLangTxt_NoChTestType;
	static CString g_sLangID_CommSetInf;//ͨѶ������Ϣ��ȫ
	static CString g_sLangTxt_CommSetInf;
	static CString g_sLangID_TabFileNoSel;//����ļ�û��ѡ��
	static CString g_sLangTxt_TabFileNoSel;
	static CString g_sLangID_AlreadyExists;//%s �Ѿ�����
	static CString g_sLangTxt_AlreadyExists;
	static CString g_sLangID_UnquaItem;//���ϸ���Ŀ
	static CString g_sLangTxt_UnquaItem;
	static CString g_sLangID_ModelFile;//ģ���ļ�
	static CString g_sLangTxt_ModelFile;
	static CString g_sLangID_NoAddDevTestRep;//û�����װ�ò��Ա���
	static CString g_sLangTxt_NoAddDevTestRep;
	static CString g_sLangID_OlAddOnRep;//ֻ�����һ��װ�ò��Ա���
	static CString g_sLangTxt_OlAddOnRep;
	static CString g_sLangID_ProtocoTemplate;//��Լģ��
	static CString g_sLangTxt_ProtocoTemplate;
	static CString g_sLangID_ProtocoMatching;//��Լ����
	static CString g_sLangTxt_ProtocoMatching;
	static CString g_sLangID_ChRptRe;//ѡ�񱨸浼��Ŀ��Ŀ¼
	static CString g_sLangTxt_ChRptRe;
	static CString g_sLangID_AlOpen;//�Ѿ��򿪡�%s������رպ��ڴ������Ա��棡
	static CString g_sLangTxt_AlOpen;
	static CString g_sLangID_TaskTotalTime;//������ʱ��
	static CString g_sLangTxt_TaskTotalTime;
	static CString g_sLangID_RptTotalTime;//������ʱ��
	static CString g_sLangTxt_RptTotalTime;
	static CString g_sLangID_NoTitle;//�ޱ���
	static CString g_sLangTxt_NoTitle;
	static CString g_sLangID_TestingClose;//���ڲ����У����ܹر�...
	static CString g_sLangTxt_TestingClose;
	static CString g_sLangID_FileUnExistS;//�ļ�\"%s\"������
	static CString g_sLangTxt_FileUnExistS;
	static CString g_sLangID_SelOrCretFile;//�ļ��С�%s�������в��Ա����ļ�\n��ѡ����ߴ���һ���յ��ļ���
	static CString g_sLangTxt_SelOrCretFile;
	static CString g_sLangID_SelFilePath;//��ѡ�񱨸��ļ��洢��·����
	static CString g_sLangTxt_SelFilePath;
	static CString g_sLangID_DelTaskYOrN;//�Ƿ�Ҫɾ������ %s ��������
	static CString g_sLangTxt_DelTaskYOrN;
	static CString g_sLangID_SureDelAgain;//���ٴ�ȷ��ɾ��
	static CString g_sLangTxt_SureDelAgain;
	static CString g_sLangID_DelFailItem;//ɾ���������а����Ѿ����򿪵Ĺ��̣�ɾ��ʧ��
	static CString g_sLangTxt_DelFailItem;
	static CString g_sLangID_DelItemYOrN;//�Ƿ�Ҫɾ������ %s
	static CString g_sLangTxt_DelItemYOrN;
	static CString g_sLangID_DelFailure;//�ù����Ѿ����򿪣�ɾ��ʧ��
	static CString g_sLangTxt_DelFailure;
	static CString g_sLangID_StartRptYOrN;//����ʼ���桱����ֻ���Ե�ǰ�򿪵Ĳ��Ա��棬\r\n��ȷʵֻҪ���Բ��������еĵ������Ա�����\r\n\r\nѡ���ǡ����Ե�������\r\nѡ�񡰷񡱿�ʼ�������\r\nѡ��ȡ������ֹ����")
	static CString g_sLangTxt_StartRptYOrN;
	static CString g_sLangID_NewTestClear;//�½����ԣ������ǰ����������\r\n
	static CString g_sLangTxt_NewTestClear;
	static CString g_sLangID_SelYes;//ѡ���ǡ������ǰ�������ݣ��½�����\r\n
	static CString g_sLangTxt_SelYes;
	static CString g_sLangID_SelNo;//ѡ�񡰷񡱣��������ǰ�������ݣ��½�����\r\n
	static CString g_sLangTxt_SelNo;
	static CString g_sLangID_SelCancel;//ѡ��ȡ����������ʼ����
	static CString g_sLangTxt_SelCancel;
	static CString g_sLangID_WavCpntNotExist;//¼�����������
	static CString g_sLangTxt_WavCpntNotExist;
	static CString g_sLangID_UnAutoTest;//û�������Զ����ԣ��޷�ִ������
	static CString g_sLangTxt_UnAutoTest;
	static CString g_sLangID_ToolUnExitS;//���ߡ�%s����%s��������
	static CString g_sLangTxt_ToolUnExitS;
	static CString g_sLangID_TestTaskFnshS;//��������%s���������
	static CString g_sLangTxt_TestTaskFnshS;
	static CString g_sLangID_StartTestS;//��ʼ���ԡ�%s��
	static CString g_sLangTxt_StartTestS;
	static CString g_sLangID_TestTempS;//����ģ��*******%s
	static CString g_sLangTxt_TestTempS;
	static CString g_sLangID_ReportFileS;//�����ļ�*******%s
	static CString g_sLangTxt_ReportFileS;
	static CString g_sLangID_ModelFileS;//ģ���ļ�********%s
	static CString g_sLangTxt_ModelFileS;
	static CString g_sLangID_PrtcTemS;//��Լģ��********%s
	static CString g_sLangTxt_PrtcTemS;
	static CString g_sLangID_AutoTestContrl;//�Զ����Կ�������
	static CString g_sLangTxt_AutoTestContrl;
	static CString g_sLangID_SGroupS;//%s%s-��%d.%s
	static CString g_sLangTxt_SGroupS;
	static CString g_sLangID_RightBuy;//Demo�汾��ֻ��ʹ��ģ�塾Demo-PSL-641U�����빺����ʽ�汾��
	static CString g_sLangTxt_RightBuy;
	static CString g_sLangID_MainView2;//����ͼ:
	static CString g_sLangTxt_MainView2;
	static CString g_sLangID_GroupReport;//��%d����
	static CString g_sLangTxt_GroupReport;
	static CString g_sLangID_ProcessStop;//�Ͳ�����صĽ����Ѿ�����ֹ
	static CString g_sLangTxt_ProcessStop;
	static CString g_sLangID_SelObjPath;//ѡ��Ŀ��·��
	static CString g_sLangTxt_SelObjPath;
	static CString g_sLangID_FileNameIncl;//�ļ����ư����Ƿ��ַ�: %s
	static CString g_sLangTxt_FileNameIncl;
	static CString g_sLangID_ReportEptFinsh;//���浼�����
	static CString g_sLangTxt_ReportEptFinsh;
	static CString g_sLangID_ObjFileExistOvwt;//Ŀ���ļ��Ѿ�����,������?
	static CString g_sLangTxt_ObjFileExistOvwt;
	static CString g_sLangID_ReportTestTempt;//���桾%s����Ӧ�Ĳ���ģ��:��%s��
	static CString g_sLangTxt_ReportTestTempt;
	static CString g_sLangID_SureToDele;//��ȷʵҪɾ����%s����
	static CString g_sLangTxt_SureToDele;
	static CString g_sLangID_UnQualifadS;//[%s]���ϸ�
	static CString g_sLangTxt_UnQualifadS;
	static CString g_sLangID_TestOver;//********���Խ���********
	static CString g_sLangTxt_TestOver;
	static CString g_sLangID_CopyOutput;//�������
	static CString g_sLangTxt_CopyOutput;
	static CString g_sLangID_ClearOutput;//������
	static CString g_sLangTxt_ClearOutput;
// 	static CString g_sLangID_Unqualified2;//%s[���ϸ�]
// 	static CString g_sLangTxt_Unqualified2;
	static CString g_sLangID_NoAddTestRpt;//û����Ӳ��Ա���
	static CString g_sLangTxt_NoAddTestRpt;
	static CString g_sLangID_OneTestRpt;//ֻ�����һ�����Ա���
	static CString g_sLangTxt_OneTestRpt;
	static CString g_sLangID_NoSelPrtcTem;//װ�ñ����б�ڡ�%d��û��ѡ���Լģ��
	static CString g_sLangTxt_NoSelPrtcTem;
	static CString g_sLangID_NoSelFile;//װ�ñ����б�ڡ�%d��û��ѡ�����ļ�
	static CString g_sLangTxt_NoSelFile;
	static CString g_sLangID_NameSame;//װ�ñ����б�ڡ�%d����ڡ�%d�����ơ�%s����ͬ
	static CString g_sLangTxt_NameSame;
	static CString g_sLangID_PrtcSame;//װ�ñ����б�ڡ�%d����ڡ�%d����Լģ�塾%s����ͬ
	static CString g_sLangTxt_PrtcSame;
	static CString g_sLangID_IPSame;//װ�ñ����б�ڡ�%d����ڡ�%d��IP��%s����ͬ
	static CString g_sLangTxt_IPSame;
	static CString g_sLangID_ToolTip_32781;//�򿪱���
	static CString g_sLangTxt_ToolTip_32781;
	static CString g_sLangID_ToolTip_32776;//��ӱ���
	static CString g_sLangTxt_ToolTip_32776;
	static CString g_sLangID_ToolTip_32777;//ɾ������
	static CString g_sLangTxt_ToolTip_32777;
	static CString g_sLangID_ToolTip_32783;//�ָ���δ��ɵ�״̬
	static CString g_sLangTxt_ToolTip_32783;
	static CString g_sLangID_ToolTip_32778;//���Ʊ���
    static CString g_sLangTxt_ToolTip_32778;
	static CString g_sLangID_ToolTip_32779;//���Ʊ���
	static CString g_sLangTxt_ToolTip_32779;
	static CString g_sLangID_ToolTip_32784;//��ʾ�����Ӧ��ģ��
	static CString g_sLangTxt_ToolTip_32784;
	static CString g_sLangID_ToolTip_32775;//�������񱨸�
	static CString g_sLangTxt_ToolTip_32775;
	static CString g_sLangID_ToolTip_32782;//�ر�����
	static CString g_sLangTxt_ToolTip_32782;

	static CString g_sLangID_Menu_57634;
	static CString g_sLangTxt_Menu_57634;
	static CString g_sLangID_Menu_57632;
	static CString g_sLangTxt_Menu_57632;

	static CString g_sLangID_ToolTip_32789;
	static CString g_sLangTxt_ToolTip_32789;
	static CString g_sLangID_StitchRptFinish;
	static CString g_sLangTxt_StitchRptFinish;

	//2016-12-10
	static CString g_sLangID_ToolTip_2000;
	static CString g_sLangTxt_ToolTip_2000;
	static CString g_sLangID_ToolTip_32786;
	static CString g_sLangTxt_ToolTip_32786;
	static CString g_sLangID_ToolTip_32788;
	static CString g_sLangTxt_ToolTip_32788;
	static CString g_sLangID_ToolTip_2001;
	static CString g_sLangTxt_ToolTip_2001;
	static CString g_sLangID_ToolTip_32785;
	static CString g_sLangTxt_ToolTip_32785;
	static CString g_sLangID_ToolTip_351;
	static CString g_sLangTxt_ToolTip_351;
	static CString g_sLangID_ToolTip_314;
	static CString g_sLangTxt_ToolTip_314;
	static CString g_sLangID_ToolTip_320;
	static CString g_sLangTxt_ToolTip_320;
	static CString g_sLangID_ToolTip_330;
	static CString g_sLangTxt_ToolTip_330;
	static CString g_sLangID_ToolTip_358;
	static CString g_sLangTxt_ToolTip_358;
	static CString g_sLangID_ToolTip_347;
	static CString g_sLangTxt_ToolTip_347;
	static CString g_sLangID_ToolTip_310;
	static CString g_sLangTxt_ToolTip_310;
	static CString g_sLangID_ToolTip_348;
	static CString g_sLangTxt_ToolTip_348;
	static CString g_sLangID_ToolTip_349;
	static CString g_sLangTxt_ToolTip_349;
	static CString g_sLangID_ToolTip_350;
	static CString g_sLangTxt_ToolTip_350;
	static CString g_sLangID_ToolTip_357;
	static CString g_sLangTxt_ToolTip_357;
};

