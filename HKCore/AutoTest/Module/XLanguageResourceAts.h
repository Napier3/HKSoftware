//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"


class CXLanguageResourceAtsBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourceAtsBase();
	virtual ~CXLanguageResourceAtsBase();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsAtsBase;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsAtsBaseFile;
	extern CString g_sLangID_OpenTemplate;
	extern CString g_sLangTxt_OpenTemplate;
	extern CString g_sLangID_OpenPowerTestTemplate;
	extern CString g_sLangTxt_OpenPowerTestTemplate;
	extern CString g_sLangID_OpenSubTemplate;
	extern CString g_sLangTxt_OpenSubTemplate;
	extern CString g_sLangID_OutputWnd;
	extern CString g_sLangTxt_OutputWnd;

	extern CString g_sLangID_LastOne;
	extern CString g_sLangTxt_LastOne;
// 	extern CString g_sLangID_TraProtocol;
// 	extern CString g_sLangTxt_TraProtocol;
// 	extern CString g_sLangID_61850Protocol;
// 	extern CString g_sLangTxt_61850Protocol;
	extern CString g_sLangID_Edit;
	extern CString g_sLangTxt_Edit;
// 	extern CString g_sLangID_Browse;
// 	extern CString g_sLangTxt_Browse;

	extern CString g_sLangID_SelNone;    //ȫ��ѡ
	extern CString g_sLangTxt_SelNone;
	extern CString g_sLangID_ErrorMax;
	extern CString g_sLangTxt_ErrorMax;
	extern CString g_sLangID_Standdeviation;          //��׼��
	extern CString g_sLangTxt_Standdeviation;
	extern CString g_sLangID_ExterScript;//�ⲿ�ű����ļ�
	extern CString g_sLangTxt_ExterScript;
	extern CString g_sLangID_InterScript;//ģ���ڲ��ű���
	extern CString g_sLangTxt_InterScript;

	extern CString g_sLangID_Attribute;   //����
	extern CString g_sLangTxt_Atrribute;
	extern CString g_sLangID_Times;      //����
	extern CString g_sLangTxt_Times;
	extern CString g_sLangID_DataPro;//���ݴ���
	extern CString g_sLangTxt_DataPro;

	extern CString g_sLangID_TestTemplateFile;
	extern CString g_sLangTxt_TestTemplateFile;
	extern CString g_sLangID_TestSubTemplateFile;
	extern CString g_sLangTxt_TestSubTemplateFile;
	extern CString g_sLangID_ReportTemplateFile;
	extern CString g_sLangTxt_ReportTemplateFile;
	//
	extern CString g_sLangID_ReportDefinition;
	extern CString g_sLangTxt_ReportDefinition;
	extern CString g_sLangID_TagManagement;
	extern CString g_sLangTxt_TagManagement;
	extern CString g_sLangID_TestTask; 
	extern CString g_sLangTxt_TestTask;

	extern CString g_sLangID_LetterForm;//����
	extern CString g_sLangTxt_LetterForm;
	extern CString g_sLangID_ViewDevPara;//�鿴�豸����
	extern CString g_sLangTxt_ViewDevPara;
	extern CString g_sLangID_TestInlegibleItems;//����ȫ�����ϸ���Ŀ
	extern CString g_sLangTxt_TestInlegibleItems;
	extern CString g_sLangID_TestCurrtItem;//���Ե�ǰ��Ŀ
	extern CString g_sLangTxt_TestCurrtItem;
	extern CString g_sLangID_TestCurrtItemDev;//���Ե�ǰ��Ŀ-װ�ö�������
	extern CString g_sLangTxt_TestCurrtItemDev;
	extern CString g_sLangID_TestCurrtItemStart;//�ӵ�ǰ��Ŀ��ʼ����
	extern CString g_sLangTxt_TestCurrtItemStart;
	extern CString g_sLangID_ParaMdf;//�����޸�
	extern CString g_sLangTxt_ParaMdf;
	extern CString g_sLangID_UpdataPara;//���²���
	extern CString g_sLangTxt_UpdataPara;
	extern CString g_sLangID_UpdataParaToGb;//���²���
	extern CString g_sLangTxt_UpdataParaToGb;
	extern CString g_sLangID_ViewReport;//�鿴����
	extern CString g_sLangTxt_ViewReport;
	extern CString g_sLangID_ViewRecordFile;//�鿴¼���ļ�
	extern CString g_sLangTxt_ViewRecordFile;
	extern CString g_sLangID_ViewCharCurve;//�鿴��������
	extern CString g_sLangTxt_ViewCharCurve;
	extern CString g_sLangID_ExpdNodes;//չ��ȫ���ӽڵ�
	extern CString g_sLangTxt_ExpdNodes;

	extern CString g_sLangID_ComictnComm;//ͨѶ����
	extern CString g_sLangTxt_ComictnComm;
	extern CString g_sLangID_ComictnFront;//ͨѶǰ��ʱ
	extern CString g_sLangTxt_ComictnFront;
	extern CString g_sLangID_ComictnLater;//ͨѶ����ʱ
	extern CString g_sLangTxt_ComictnLater;
	extern CString g_sLangID_ComputMode;//����ģʽ
	extern CString g_sLangTxt_ComputMode;
	extern CString g_sLangID_ComictnTime;//ͨѶ����
	extern CString g_sLangTxt_ComictnTime;
	extern CString g_sLangID_Text;         //�ı�
	extern CString g_sLangTxt_Text; 

	extern CString g_sLangID_CreatTestMngFail;//���������ǹ������ʧ��
	extern CString g_sLangTxt_CreatTestMngFail;
	extern CString g_sLangID_CreatTestAbnom;//����������ͨѶ��������쳣
	extern CString g_sLangTxt_CreatTestAbnom;
	extern CString g_sLangID_CreatTestCmtFail;//����������ͨѶ���ʧ��
	extern CString g_sLangTxt_CreatTestCmtFail;
	extern CString g_sLangID_NoPrtcCpnt;//û��ע���Լ�������
	extern CString g_sLangTxt_NoPrtcCpnt;
	extern CString g_sLangID_CreatPrtcFail;//������ԼͨѶ�豸ʧ��
	extern CString g_sLangTxt_CreatPrtcFail;
	extern CString g_sLangID_FileOpenFalseS;//���ļ�\"%s\"����
	extern CString g_sLangTxt_FileOpenFalseS;
	extern CString g_sLangID_TestFileOpenFalseS;//�������ļ�\"%s\"����
	extern CString g_sLangTxt_TestFileOpenFalseS;
	extern CString g_sLangID_CommunItemD;//ͨѶ������Ŀ������%d    ��������Ŀ������%d
	extern CString g_sLangTxt_CommunItemD;
	extern CString g_sLangID_TestStopS;//��%s������ֹͣ
	extern CString g_sLangTxt_TestStopS;
	extern CString g_sLangID_CommunIgnored;//ͨѶ�κ��Եĵ��������Թ�����Ϣ......��
	extern CString g_sLangTxt_CommunIgnored;
	extern CString g_sLangID_OnlineFail;//����ʧ��
	extern CString g_sLangTxt_OnlineFail;
	extern CString g_sLangID_TestStartInf;//------�յ����������Կ�ʼ��Ϣ��%s��
	extern CString g_sLangTxt_TestStartInf;
	extern CString g_sLangID_ParaDnldFail;//------��������ʧ��
	extern CString g_sLangTxt_ParaDnldFail;
	extern CString g_sLangID_TestUnsuptFctn;//------���������ײ㹦�ܽӿڲ�֧�ֲ��Թ���[%s]
	extern CString g_sLangTxt_TestUnsuptFctn;
	extern CString g_sLangID_TestOverTimeS;//------���������ײ���Թ���[%s]���Գ�ʱ, %d ms�����²���
	extern CString g_sLangTxt_TestOverTimeS;
	extern CString g_sLangID_CommunOverTime;//ͨѶ��ʱ��������ֹ��
	extern CString g_sLangTxt_CommunOverTime;
	extern CString g_sLangID_CommunTestStop;//ͨѶ�����г��ִ��󣬲�����ֹ
	extern CString g_sLangTxt_CommunTestStop;
	extern CString g_sLangID_ReCommunD;//ͨѶ�����г��ִ�������ͨѶ��%d�Σ���%d��
	extern CString g_sLangTxt_ReCommunD;
	extern CString g_sLangID_CommunFalse;//ͨѶ�����г��ִ���pCommCmd==NULL
	extern CString g_sLangTxt_CommunFalse;

	extern CString g_sLangID_StartCommun;//�����豸�ɹ�����ʼִ��ͨѶ����
	extern CString g_sLangTxt_StartCommun;
	extern CString g_sLangID_ContNextItem;//����������һ���豸
	extern CString g_sLangTxt_ContNextItem;
	extern CString g_sLangID_TestContS;//��%s������%s������ͨѶ�����г��ִ��󣬲��Լ���
	extern CString g_sLangTxt_TestContS;
	extern CString g_sLangID_TestStop3;//ͨѶ�����쳣��������ֹ
	extern CString g_sLangTxt_TestStop3;
	extern CString g_sLangID_NoTestItem;//û����Ҫ���Ե���Ŀ��
	extern CString g_sLangTxt_NoTestItem;
	extern CString g_sLangID_ItemTestTimeD;//------��Ŀ[%s]��%d�β��ԣ���%d��
	extern CString g_sLangTxt_ItemTestTimeD;
	extern CString g_sLangID_ItemTestTimeD2;//------��Ŀ[%s]��1�β��ԣ���1��
	extern CString g_sLangTxt_ItemTestTimeD2;
	extern CString g_sLangID_Communtioning;//ͨѶ��.......
	extern CString g_sLangTxt_Communtioning;
	extern CString g_sLangID_MdfParaData;//������ģ�巽ʽ�����ֶ��޸ı���װ�õĲ�������
	extern CString g_sLangTxt_MdfParaData;
	extern CString g_sLangID_CommunTestTimeD;//----%sͨѶ����[%s]��%d�β��ԣ���%d��
	extern CString g_sLangTxt_CommunTestTimeD;
	extern CString g_sLangID_CommunCmdS;//----%sͨѶ����[%s]
	extern CString g_sLangTxt_CommunCmdS;
	extern CString g_sLangID_CommunCmdItem;//----------%sͨѶ������Ŀ[%s]
	extern CString g_sLangTxt_CommunCmdItem;
	extern CString g_sLangID_CallRecordFail;//����¼���ļ�ʧ��
	extern CString g_sLangTxt_CallRecordFail;
	extern CString g_sLangID_ReadRecordFileS;//��ȡ¼���ļ�����%s��
	extern CString g_sLangTxt_ReadRecordFileS;
	extern CString g_sLangID_TestStop4;//    ������Ŀʱ�������󣬲���ֹͣ
	extern CString g_sLangTxt_TestStop4;
	extern CString g_sLangID_TestCotrAbnom;//------�����ǿ��Ƴ������쳣
	extern CString g_sLangTxt_TestCotrAbnom;
	extern CString g_sLangID_ItemUncmpltS;//------��������Ŀ\"%s\"��������Ŀû�����
	extern CString g_sLangTxt_ItemUncmpltS;
	extern CString g_sLangID_TestCotrAbnom2;//      �����ǿ��Ƴ������쳣
	extern CString g_sLangTxt_TestCotrAbnom2;
	extern CString g_sLangID_EltrcProjectCmplt;//     ��������Ŀ���
	extern CString g_sLangTxt_EltrcProjectCmplt;
	extern CString g_sLangID_NotCommunCmd;//ͨѶ�����г��ִ��󣬲���ͨѶ����
	extern CString g_sLangTxt_NotCommunCmd;
	extern CString g_sLangID_CommunFalse2;//ͨѶ�����г��ִ���Item==NULL
	extern CString g_sLangTxt_CommunFalse2;
	extern CString g_sLangID_TestItemFalse;//    >>>>>>>ExcuteCommCmd:������Ŀʱ��������
	extern CString g_sLangTxt_TestItemFalse;
	extern CString g_sLangID_CommunParaFalse;//    ͨѶ������Ŀ��%s������Ĳ�����%s������
	extern CString g_sLangTxt_CommunParaFalse;
	extern CString g_sLangID_ItemDataUnexistS;//��Ŀ(%s)ͨѶ�����豸����ģ��()%s������
	extern CString g_sLangTxt_ItemDataUnexistS;
	extern CString g_sLangID_ItemDataUnexist;//��Ŀ(%s)ͨѶ�����豸����ģ�Ͳ�����
	extern CString g_sLangTxt_ItemDataUnexist;
	extern CString g_sLangID_ItemDataUnexist2;//��Ŀ��%s��ͨѶ�����豸���ݼ���%s��������
	extern CString g_sLangTxt_ItemDataUnexist2;
	extern CString g_sLangID_ItemDataUnexist3;//��Ŀ��%s���豸����ģ�͡�%s��������
	extern CString g_sLangTxt_ItemDataUnexist3;
	extern CString g_sLangID_ItemDataUnexist4;//��Ŀ��%s��ͨѶ�����豸����ģ�Ͳ�����
	extern CString g_sLangTxt_ItemDataUnexist4;
	extern CString g_sLangID_SytmTestFalse;//ϵͳ���Դ���ExcuteCommCmdOnDelayBeforeFinish
	extern CString g_sLangTxt_SytmTestFalse;
	extern CString g_sLangID_TestAbnrm2;//���Է����쳣�����������ͨѶ����û�ж�Ӧ����Ŀ
	extern CString g_sLangTxt_TestAbnrm2;
	extern CString g_sLangID_TestAbnrm3;//���Է����쳣�����������ͨѶ����û�ж�Ӧ����Ŀ[TestNextSubItems]
	extern CString g_sLangTxt_TestAbnrm3;
	extern CString g_sLangID_DealCommunRst;//----����ͨѶ���%s�����
	extern CString g_sLangTxt_DealCommunRst;
	extern CString g_sLangID_CreatRptFail;//�����������ʧ��
	extern CString g_sLangTxt_CreatRptFail;
	extern CString g_sLangID_WaitRtest;//***********��׼Դ�澯���ȴ�%d���Ӻ����¿�ʼ����************
	extern CString g_sLangTxt_WaitRtest;
	extern CString g_sLangID_CommunUnExist;//ͨѶ�豸������
	extern CString g_sLangTxt_CommunUnExist;
	extern CString g_sLangID_CmdFalse;//ͨѶ�����ļ���%s������ȷ�����%s������
	extern CString g_sLangTxt_CmdFalse;
	extern CString g_sLangID_CommunEngineFalse;//    ִ��ͨѶ���̣�ͨѶ�������
	extern CString g_sLangTxt_CommunEngineFalse;
	extern CString g_sLangID_PrtcEngineFalse;//��Լ�����豸���ݶ������
	extern CString g_sLangTxt_PrtcEngineFalse;
	extern CString g_sLangID_PathData;//·����%s�����ݸ���%d
	extern CString g_sLangTxt_PathData;
	extern CString g_sLangID_PathFalse;//·������%s
	extern CString g_sLangTxt_PathFalse;
	extern CString g_sLangID_FunctionError;//MtRegistPpDataMsg�������ô���
	extern CString g_sLangTxt_FunctionError;
	extern CString g_sLangID_TestFctnNo;//���Թ������û��ʵ��GetExternMsgRcvWnd��G����etExternMsgID
	extern CString g_sLangTxt_TestFctnNo;
	extern CString g_sLangID_UnCreatFctn;//��û�д������Թ��������
	extern CString g_sLangTxt_UnCreatFctn;
	extern CString g_sLangID_CallRecordFail2;//����¼������ʧ��
	extern CString g_sLangTxt_CallRecordFail2;
	extern CString g_sLangID_CallCmdFail;//��������ʧ��
	extern CString g_sLangTxt_CallCmdFail;
	extern CString g_sLangID_ReportExpSucc;//���浼���ɹ���\r\n
	extern CString g_sLangTxt_ReportExpSucc;
	//GuideBookDefine��������Ϣ
	extern CString g_sLangID_Qualified;
	extern CString g_sLangTxt_Qualified;
	extern CString g_sLangID_Unqualified;
	extern CString g_sLangTxt_Unqualified;
	extern CString g_sLangID_ErrorID;
	extern CString g_sLangTxt_ErrorID;

	extern CString g_sLangID_CurrZoneIndex;    //��ǰ��ֵ��
	extern CString g_sLangTxt_CurrZoneIndex;
	extern CString g_sLangID_ZoneIndex;    
	extern CString g_sLangTxt_ZoneIndex;
	//
	extern CString g_sLangID_ModifyAndSave;    
	extern CString g_sLangTxt_ModifyAndSave;
	//CharTemplateSelDlg��������Ϣ
	extern CString g_sLangID_SelCharCurve;    
	extern CString g_sLangTxt_SelCharCurve;
    //TestItemViewGrid
	extern CString g_sLangID_ItemType;  //��Ŀ����  
	extern CString g_sLangTxt_ItemType;
	extern CString g_sLangID_Status;   //״̬ 
	extern CString g_sLangTxt_Status;
	extern CString g_sLangID_ItemPath;   //��Ŀ·�� 
	extern CString g_sLangTxt_ItemPath;
	extern CString g_sLangID_ReportInf;   //������Ϣ 
	extern CString g_sLangTxt_ReportInf;
	extern CString g_sLangID_RetestQualified;    //�ز�ϸ�
	extern CString g_sLangTxt_RetestQualified;
	extern CString g_sLangID_ElectrQuanPrjc;    //��������Ŀ
	extern CString g_sLangTxt_ElectrQuanPrjc;
	extern CString g_sLangID_ArtificialProject;    //�˹���Ŀ
	extern CString g_sLangTxt_ArtificialProject;



    //Safety
	extern CString g_sLangID_ErrorDll;//�����DLL���� %s::%s(\"%s\", \"%s\")
	extern CString g_sLangTxt_ErrorDll;
	extern CString g_sLangID_DllUnStopTest;//DLL����(%s::%s)�����У�������ֹ����...
	extern CString g_sLangTxt_DllUnStopTest;
    //Source\AutoTest\Module
	extern CString g_sLangID_CrtPrtlEgnFail; //������Լ����[%s]ʧ��
	extern CString g_sLangTxt_CrtPrtlEgnFail;
	extern CString g_sLangID_RlsPrtlEgnFail; //�ͷŹ�Լ����[%s]ʧ��
	extern CString g_sLangTxt_RlsPrtlEgnFail;
	extern CString g_sLangID_TestLogMngmt; //���Լ�¼�ļ�����
	extern CString g_sLangTxt_TestLogMngmt;
	extern CString g_sLangID_TestRptRecodFile; //���Ա����¼�ļ�
	extern CString g_sLangTxt_TestRptRecodFile;
	extern CString g_sLangID_TestRptFile; //���Ա����ļ�
	extern CString g_sLangTxt_TestRptFile;
	extern CString g_sLangID_TestTaskFile; //���������ļ�
	extern CString g_sLangTxt_TestTaskFile;
	extern CString g_sLangID_SngDeviceRpt; //��װ�ö�ͨ�����Ա����ļ�
	extern CString g_sLangTxt_SngDeviceRpt;
	extern CString g_sLangID_MulDeviceRpt; //��װ�ò��Ա����ļ�
	extern CString g_sLangTxt_MulDeviceRpt;
	extern CString g_sLangID_SngDeviceRpt2; //��װ�ö��Լ���Ա����ļ�
	extern CString g_sLangTxt_SngDeviceRpt2;
	extern CString g_sLangID_MdvMgrpFile; //��װ�ö��Լ���Ա����ļ�
	extern CString g_sLangTxt_MdvMgrpFile;
	extern CString g_sLangID_CreateCpntFail; //�����������ʧ��
	extern CString g_sLangTxt_CreateCpntFail;
	extern CString g_sLangID_MulDeviceRptS; //��װ�ò��Ա����ļ�(*.%s)|*.%s||
	extern CString g_sLangTxt_MulDeviceRptS;
	extern CString g_sLangID_SngDeviceRptS; //��װ�ö��Լ���Ա����ļ�(*.%s)|*.%s||
	extern CString g_sLangTxt_SngDeviceRptS;
	extern CString g_sLangID_MdvMgrpFilter; //��װ�ö��Լ���Ա����ļ�(*.%s)|*.%s||
	extern CString g_sLangTxt_MdvMgrpFilter;
	extern CString g_sLangID_FileRightError; //�ļ���%s���汾����
	extern CString g_sLangTxt_FileRightError;
	extern CString g_sLangID_DataIDUnext; //����ID(%s)������
	extern CString g_sLangTxt_DataIDUnext;
	extern CString g_sLangID_TestCpntCopy; //        [%s]:[%s]�������(���Ʊ���)
	extern CString g_sLangTxt_TestCpntCopy;
	extern CString g_sLangID_SngDevMulPrtc; //��װ�ö��Լ-·��1��%s
	extern CString g_sLangTxt_SngDevMulPrtc;
	extern CString g_sLangID_SngDevMulPrtc2; //��װ�ö��Լ-·��2��%s
	extern CString g_sLangTxt_SngDevMulPrtc2;
	extern CString g_sLangID_WaitSetting; //���ò����У��ȴ��������......
	extern CString g_sLangTxt_WaitSetting;
	extern CString g_sLangID_RecordFileRead; //��ȡ¼���ļ�ǰ��ʱ0��,��%d��
	extern CString g_sLangTxt_RecordFileRead;
	extern CString g_sLangID_RecordFileRead2; //��ȡ¼���ļ�ǰ��ʱ%d��,��%d��
	extern CString g_sLangTxt_RecordFileRead2;
	extern CString g_sLangID_ErrorMessage_a; //����Ĵ�����Ϣ...............
	extern CString g_sLangTxt_ErrorMessage_a;

    //GuideBook\Characteristic\CharMngr
	extern CString g_sLangID_ChrctCurDefn; //�������߶���
	extern CString g_sLangTxt_ChrctCurDefn;
	extern CString g_sLangID_ParaCurve; //���߲���
	extern CString g_sLangTxt_ParaCurve;
	extern CString g_sLangID_ExpressionError; //���ʽ��%s�� ����
	extern CString g_sLangTxt_ExpressionError;
	extern CString g_sLangID_ExpressionVariable; //���ʽ������%s�� ����
	extern CString g_sLangTxt_ExpressionVariable;
    //GuideBook\Characteristic\Element
	extern CString g_sLangID_Arc; //Բ����arc��
	extern CString g_sLangTxt_Arc;
	extern CString g_sLangID_Arcp; //Բ����arcp��
	extern CString g_sLangTxt_Arcp;
	extern CString g_sLangID_Lens; //͸����lens��
	extern CString g_sLangTxt_Lens;
	extern CString g_sLangID_Lined; //�߶Σ�lined��
	extern CString g_sLangTxt_Lined;
	extern CString g_sLangID_Line; //�ߣ�lined��
	extern CString g_sLangTxt_Line;
	extern CString g_sLangID_Linep; //�ߣ�linep��
	extern CString g_sLangTxt_Linep;
	extern CString g_sLangID_Liner; //���ߣ�liner��
	extern CString g_sLangTxt_Liner;
	extern CString g_sLangID_Mho; //Բ��mho��
	extern CString g_sLangTxt_Mho;
	extern CString g_sLangID_I2T; //I2T
	extern CString g_sLangTxt_I2T;
 	extern CString g_sLangID_IAC; //IAC
	extern CString g_sLangTxt_IAC;
	extern CString g_sLangID_IEC; //IEC
	extern CString g_sLangTxt_IEC;
	extern CString g_sLangID_IEEE; //IEEE
	extern CString g_sLangTxt_IEEE;
	extern CString g_sLangID_INVOWNDEF; //INVOWNDEF
	extern CString g_sLangTxt_INVOWNDEF;
    extern CString g_sLangID_Expr;//Expr
    extern CString g_sLangTxt_Expr;//���ʽ��Expr��
   //GuideBook\Characteristic\UI
	extern CString g_sLangID_CordnPtn; //����ģʽ
	extern CString g_sLangTxt_CordnPtn;
	extern CString g_sLangID_TestFctnSel; //���Թ���ѡ��
	extern CString g_sLangTxt_TestFctnSel;
	extern CString g_sLangID_Location; //λ��
	extern CString g_sLangTxt_Location;
	extern CString g_sLangID_RotationAngle; //��ת�Ƕ�
	extern CString g_sLangTxt_RotationAngle;
	extern CString g_sLangID_CustomAngle; //�Զ����߽Ƕ�
	extern CString g_sLangTxt_CustomAngle;
	extern CString g_sLangID_CoordinatesConflict; //�������ߵ�����ϵ��%s������ͼ�ι���ģ�������ϵ��%s����ͻ
	extern CString g_sLangTxt_CoordinatesConflict;
	extern CString g_sLangID_VariableID; //����ID
	extern CString g_sLangTxt_VariableID;
	extern CString g_sLangID_AssociationValue; //������ֵ
	extern CString g_sLangTxt_AssociationValue;
	extern CString g_sLangID_EdgeType; //������
	extern CString g_sLangTxt_EdgeType;
	extern CString g_sLangID_TestPoint; //�����
	extern CString g_sLangTxt_TestPoint;
	extern CString g_sLangID_ErrorBand; //����
	extern CString g_sLangTxt_ErrorBand;
	extern CString g_sLangID_EdgeDetails; //����ϸ��Ϣ
	extern CString g_sLangTxt_EdgeDetails;
	extern CString g_sLangID_CoordinateSystem; //����ϵ
	extern CString g_sLangTxt_CoordinateSystem;
    //GuideBook\Device\Device
	extern CString g_sLangID_DataMatchScript; //����ƥ��ű�
	extern CString g_sLangTxt_DataMatchScript;
	extern CString g_sLangID_Include; //����
	extern CString g_sLangTxt_Include;
	extern CString g_sLangID_CertainUninclude; //���벻����
	extern CString g_sLangTxt_CertainUninclude;
	extern CString g_sLangID_DataItfcMng; //���ݽӿڹ���
	extern CString g_sLangTxt_DataItfcMng;
	extern CString g_sLangID_DataItfc; //���ݽӿ�
	extern CString g_sLangTxt_DataItfc;
	extern CString g_sLangID_DataItfcVari; //���ݽӿڱ���
	extern CString g_sLangTxt_DataItfcVari;
	extern CString g_sLangID_DataDataUnExist; //���ݡ�%s�������ݼ���%s��������
	extern CString g_sLangTxt_DataDataUnExist;
	//GuideBook\Device
	extern CString g_sLangID_SoftStrap; //��ѹ��
	extern CString g_sLangTxt_SoftStrap;
	extern CString g_sLangID_SetValue; //����ֵ
	extern CString g_sLangTxt_SetValue;
	extern CString g_sLangID_TestPara; //���Բ���
	extern CString g_sLangTxt_TestPara;
	extern CString g_sLangID_ControlWord; //������
	extern CString g_sLangTxt_ControlWord;
	extern CString g_sLangID_OutputValue; //������
	extern CString g_sLangTxt_OutputValue;
	extern CString g_sLangID_InputValue; //������
	extern CString g_sLangTxt_InputValue;
	extern CString g_sLangID_AnalogValue; //ģ����
	extern CString g_sLangTxt_AnalogValue;
	//GuideBook\Item\CommCmd
	extern CString g_sLangID_PreDelay; //[%s]ͨѶǰ��ʱ (%s)==>>(%s)
	extern CString g_sLangTxt_PreDelay;
	extern CString g_sLangID_PostDelay; //[%s]ͨѶ����ʱ (%s)==>>(%s)
	extern CString g_sLangTxt_PostDelay;
	extern CString g_sLangID_RetryDelay; //[%s]����ǰ��ʱ (%s)==>>(%s)
	extern CString g_sLangTxt_RetryDelay;
	extern CString g_sLangID_CommunCmdUnExist; //ͨѶ��Ŀ��%s����Ӧ��ͨѶ���%s��������
	extern CString g_sLangTxt_CommunCmdUnExist;
	extern CString g_sLangID_CommunCmdTimes; //ͨѶ���������%s
	extern CString g_sLangTxt_CommunCmdTimes;
	extern CString g_sLangID_AllRecord; //ȫ�����ģ�%s
	extern CString g_sLangTxt_AllRecord;
	extern CString g_sLangID_StandardRecord; //��׼���ģ�%s
	extern CString g_sLangTxt_StandardRecord;
	extern CString g_sLangID_NoRecord; //���������û�б��ġ�%s��=��%s��
	extern CString g_sLangTxt_NoRecord;
	extern CString g_sLangID_NoDefin; //û�ж��塾%s��
	extern CString g_sLangTxt_NoDefin;
	extern CString g_sLangID_RecordTimes; //���ġ�%s����%s��ʱ��%s��-��%s��=%d ms
	extern CString g_sLangTxt_RecordTimes;
	extern CString g_sLangID_TimeDiff; //CalSoeTimeEx����%s��%s����%s��%s��ʱ��%s��-��%s��=%d ms
	extern CString g_sLangTxt_TimeDiff;
	extern CString g_sLangID_RecordResult; //������֤�Ľ����û�С�%s��
	extern CString g_sLangTxt_RecordResult;
	extern CString g_sLangID_Surplus; //���ࣺ%s
	extern CString g_sLangTxt_Surplus;
	extern CString g_sLangID_AllExpRecord; //ȫ�����ڱ��ģ�%s
	extern CString g_sLangTxt_AllExpRecord;
	extern CString g_sLangID_Lack; //ȱ�٣�%s
	extern CString g_sLangTxt_Lack;
	//GuideBook\Item\MacroTest
	extern CString g_sLangID_CreatCharPara; //�����������������ߣ�����ID��%s��������
	extern CString g_sLangTxt_CreatCharPara;
	extern CString g_sLangID_Act; //����
	extern CString g_sLangTxt_Act;
	extern CString g_sLangID_Unact; //δ����
	extern CString g_sLangTxt_Unact;
	extern CString g_sLangID_UndefinDataPara; //û�ж��塰%s�����ݱ���
	extern CString g_sLangTxt_UndefinDataPara;
	extern CString g_sLangID_ShowResult; //���ʽ��%s��������Ϊ��%s��
	extern CString g_sLangTxt_ShowResult;
	extern CString g_sLangID_ParaMdf2; //[%s]�����޸ģ� [%s] ==[%s] ->[%s]
	extern CString g_sLangTxt_ParaMdf2;
	//GuideBook\Item\Safety
	extern CString g_sLangID_LibraryFile; //���ļ������ڡ�%s��
	extern CString g_sLangTxt_LibraryFile;
	extern CString g_sLangID_FctnNotFound; //��%s��write_qrcode_file �������û�ҵ�
	extern CString g_sLangTxt_FctnNotFound;
	extern CString g_sLangID_MsgPrompt; //��Ϣ��ʾ
	extern CString g_sLangTxt_MsgPrompt;
	//GuideBook\Item
	extern CString g_sLangID_TaskGuide2; //��ҵָ��
	extern CString g_sLangTxt_TaskGuide2;
	extern CString g_sLangID_Delete2; //ɾ����%s
	extern CString g_sLangTxt_Delete2;
	extern CString g_sLangID_DelCommunPara; //ɾ��ͨѶ����Ĳ�����%s
	extern CString g_sLangTxt_DelCommunPara;
	extern CString g_sLangID_ItemRstError; //��Ŀ��%s������ű��﷨����
	extern CString g_sLangTxt_ItemRstError;
	//GuideBook\ReportMap
	extern CString g_sLangID_DataD2; //����%d��%s��
	extern CString g_sLangTxt_DataD2;
	extern CString g_sLangID_NullReport; //�հױ��沿��ʹ�á�%s���滻
	extern CString g_sLangTxt_NullReport;
	extern CString g_sLangID_AdjustReport; //������������
	extern CString g_sLangTxt_AdjustReport;
	extern CString g_sLangID_ReDTest; //�ظ���%d�β���
	extern CString g_sLangTxt_ReDTest;
	extern CString g_sLangID_AreaDefin; //������
	extern CString g_sLangTxt_AreaDefin;
	//GuideBook\Script
	extern CString g_sLangID_ScriptOverwrite; //�ű���%s���Ѿ����ڣ����������ű���һ�£��Ƿ񸲸�?
	extern CString g_sLangTxt_ScriptOverwrite;
	extern CString g_sLangID_DiffTypeData; //����[%s]���ڲ�ͬ�����������Ͷ���
	extern CString g_sLangTxt_DiffTypeData;
	extern CString g_sLangID_FileNewest; //���ýű���%s�������ڣ�����ű����ļ��Ƿ�Ϊ���°汾
	extern CString g_sLangTxt_FileNewest;
	extern CString g_sLangID_ParaError2; //ExitExe(\"%s\")��������
	extern CString g_sLangTxt_ParaError2;
	extern CString g_sLangID_NoDataReport; //û�б�������
	extern CString g_sLangTxt_NoDataReport;
	extern CString g_sLangID_ParaError3; //CalAinErr����:���������[%f]����������[%f]��С��0����������
	extern CString g_sLangTxt_ParaError3;
	extern CString g_sLangID_ParaError4; //CalAinStdError����:���������[%f]����������[%f]��С��0����������
	extern CString g_sLangTxt_ParaError4;
	extern CString g_sLangID_ParaError5; //CalVariationEror����:�����[%f]��С��0����������
	extern CString g_sLangTxt_ParaError5;
	extern CString g_sLangID_FctnVariousUnExist; //CalVariationErrorEx����:����ޱ���[%s]�����ڣ�
	extern CString g_sLangTxt_FctnVariousUnExist;
	extern CString g_sLangID_ErrFctnTest; //CalAinErr����ֻ�����ڲ�����ֵ������Ŀ
	extern CString g_sLangTxt_ErrFctnTest;
	extern CString g_sLangID_ErrFctnUnExist; //CalAinErr�������ݡ�%s��������
	extern CString g_sLangTxt_ErrFctnUnExist;
	extern CString g_sLangID_StdErrorFctnTest; //CalAinStdError����ֻ�����ڲ�����ֵ������Ŀ
	extern CString g_sLangTxt_StdErrorFctnTest;
	extern CString g_sLangID_StdErrorFctnUnExist; //CalAinStdError�������ݡ�%s��������
	extern CString g_sLangTxt_StdErrorFctnUnExist;
	extern CString g_sLangID_StdErrorFctnUnExistData; //CalAinStdError�������ݡ�%d�������ڲ���
	extern CString g_sLangTxt_StdErrorFctnUnExistData;
	extern CString g_sLangID_FlterFctnTest;         //FlterCalErrorMax����ֻ�����ڲ�����ֵ������Ŀ
	extern CString g_sLangTxt_FlterFctnTest;
	extern CString g_sLangID_FlterFctnUnExist; //FlterCalErrorMax�������ݡ�%s��������
	extern CString g_sLangTxt_FlterFctnUnExist;
	extern CString g_sLangID_FlterFctnUnExist2; //FlterCalErrorMax��������������ݡ�%s��������
	extern CString g_sLangTxt_FlterFctnUnExist2;
	extern CString g_sLangID_VariationFctnTest; //CalVariationErrorEx����ֻ�����ڲ���ֵ������Ŀ
	extern CString g_sLangTxt_VariationFctnTest;
	extern CString g_sLangID_VariationFctnItem; //CalVariationErrorEx�������ڵ���Ŀ�ĸ���Ŀ���ǵ�������Ŀ
	extern CString g_sLangTxt_VariationFctnItem;
	extern CString g_sLangID_VariationFctnUnExist; //CalVariationErrorEx�������ݡ�%s��������
	extern CString g_sLangTxt_VariationFctnUnExist;
	extern CString g_sLangID_VariationFctnUnExist2; //CalVariationErrorEx������׼ֵ��%s��������
	extern CString g_sLangTxt_VariationFctnUnExist2;
	extern CString g_sLangID_VariationFctnUnExist3; //CalVariationErrorEx�������ݡ�ʵ��ֵ����%s��������
	extern CString g_sLangTxt_VariationFctnUnExist3;
	extern CString g_sLangID_VariationFctnUnExist4; //CalVariationErrorEx�������ݡ�����ֵ����%s��������
	extern CString g_sLangTxt_VariationFctnUnExist4;
	extern CString g_sLangID_VariationFctnUnExist5; //CalVariationErrorEx���������Բ�����׼ֵ��%s��������
	extern CString g_sLangTxt_VariationFctnUnExist5;
	extern CString g_sLangID_VariationFctnUnExist6;         //CalVariationErrorEx�������ݡ������������%s��������
	extern CString g_sLangTxt_VariationFctnUnExist6;
	extern CString g_sLangID_ResultJude;//ʵ��ֵ=%.5f  ,����ֵ=%.5f  ,��׼ֵ=%.5f  ���=%.5f �����=%.5f  ����ж�=%d
	extern CString g_sLangTxt_ResultJude;
	extern CString g_sLangID_SetItemIDUnExist; //SetItemParaValue ID������,Path(%s) ID(%s) items
	extern CString g_sLangTxt_SetItemIDUnExist;
	extern CString g_sLangID_SetItemIDUnExist2; //SetReportValue ID������,Path(%s) ID(%s) items
	extern CString g_sLangTxt_SetItemIDUnExist2;
	extern CString g_sLangID_PathItem; //·����������Ŀ��Ψһ,Path(%s) select %d items
	extern CString g_sLangTxt_PathItem;
	extern CString g_sLangID_PathItem2; //·��ָ������Ŀ������,Path(%s) select %d items
	extern CString g_sLangTxt_PathItem2;
	extern CString g_sLangID_CalCall; //CalTmGapֻ����ͨѶ������Ŀ�б�����
	extern CString g_sLangTxt_CalCall;
	extern CString g_sLangID_NoDataReport2; //CalTmGap:û�б�������
	extern CString g_sLangTxt_NoDataReport2;
	extern CString g_sLangID_PathNoItem; //·��[%s]û��ѡ�����Ŀ
	extern CString g_sLangTxt_PathNoItem;
	extern CString g_sLangID_PathSelItem; //·��[%s]ѡ�����Ŀ��Ψһ
	extern CString g_sLangTxt_PathSelItem;
	extern CString g_sLangID_CannotUse; //DownMacroPara��������Ŀ\"%s\"��ʹ��
	extern CString g_sLangTxt_CannotUse;
	extern CString g_sLangID_CannotUse2; //DownMacroPara��������Ŀ\"%s\"��ʹ��(��Ŀ�ĸ��������)
	extern CString g_sLangTxt_CannotUse2;
	extern CString g_sLangID_CannotUse3; //DownMacroPara��������Ŀ\"%s\"��ʹ��(��Ŀ�ĸ�����ǵ�������Ŀ)
	extern CString g_sLangTxt_CannotUse3;
	extern CString g_sLangID_NullDataReport; //FilterCombineReportEx��������������Ϊ��
	extern CString g_sLangTxt_NullDataReport;
	extern CString g_sLangID_DataReportID; //������IDΪ\"%s\"�ı�������
	extern CString g_sLangTxt_DataReportID;
	extern CString g_sLangID_DataUnExist; //ReportEx����(Index=%d  AttrID=%s)������
	extern CString g_sLangTxt_DataUnExist;
	extern CString g_sLangID_DataUnExist2; //���ݡ�%s��������
	extern CString g_sLangTxt_DataUnExist2;
	extern CString g_sLangID_DataUnExist3; //����ֵ��%s��������
	extern CString g_sLangTxt_DataUnExist3;
	extern CString g_sLangID_DataPathUn; //����·����%s�������������ݡ�%d��������
	extern CString g_sLangTxt_DataPathUn;
	extern CString g_sLangID_FtcnCmdUse; //CalSoeTime����ֻ����ͨѶ������ʹ��
	extern CString g_sLangTxt_FtcnCmdUse;
	extern CString g_sLangID_FtcnCmdUse2; //SetCmdZoneIndex����ֻ������ͨѶ����
	extern CString g_sLangTxt_FtcnCmdUse2;
	extern CString g_sLangID_FtcnScriptCall; //����ValidBeginEndValRangeֻ����Ϊ��������Ŀ�Ľű�����
	extern CString g_sLangTxt_FtcnScriptCall;
	extern CString g_sLangID_FctnUnExist; //����ValidBeginEndValRange:[%s]������
	extern CString g_sLangTxt_FctnUnExist;
	//GuideBook\SetFileImExport
	extern CString g_sLangID_FixedValueData; //%s(%s)��ֵ������
	extern CString g_sLangTxt_FixedValueData;
	extern CString g_sLangID_Marking; //��ʾ
	extern CString g_sLangTxt_Marking;
	extern CString g_sLangID_PdfFile; //Pdf��ֵ�ļ�
	extern CString g_sLangTxt_PdfFile;
	extern CString g_sLangID_XMLFile; //XML��ֵ�ļ�
	extern CString g_sLangTxt_XMLFile;
	extern CString g_sLangID_WordFile; //Word��ֵ�ļ�
	extern CString g_sLangTxt_WordFile;
	extern CString g_sLangID_ExcelFile; //Excel��ֵ�ļ�
	extern CString g_sLangTxt_ExcelFile;
	extern CString g_sLangID_OATSFile; //OATS�Զ��嶨ֵ�ļ�
	extern CString g_sLangTxt_OATSFile;
	//GuideBook
	extern CString g_sLangID_DataTypeUnExist2; //���������ļ� [%s] ������
	extern CString g_sLangTxt_DataTypeUnExist2;
	extern CString g_sLangID_CommunSetUnExist; //ͨѶ�����ļ�\"%s\"������
	extern CString g_sLangTxt_CommunSetUnExist;
	extern CString g_sLangID_TestTypeUnExist; //�������������ļ�\"%s\"������
	extern CString g_sLangTxt_TestTypeUnExist;
	extern CString g_sLangID_CreatDomFail; //MSXML2����DOMDocumentʧ��
	extern CString g_sLangTxt_CreatDomFail;
	extern CString g_sLangID_OpenMsxmlFail; //MSXML2���ļ���%s��ʧ��
	extern CString g_sLangTxt_OpenMsxmlFail;
	extern CString g_sLangID_YearMonDay; //%Y��%m��%d��
	extern CString g_sLangTxt_YearMonDay;
	extern CString g_sLangID_UnitPara; //װ�ò���
	extern CString g_sLangTxt_UnitPara;
	extern CString g_sLangID_FixedValue; //��ֵ
	extern CString g_sLangTxt_FixedValue;
	extern CString g_sLangID_Platen; //ѹ��
	extern CString g_sLangTxt_Platen;
	extern CString g_sLangID_Telemetering; //ң��
	extern CString g_sLangTxt_Telemetering;
	extern CString g_sLangID_Telecommunicating; //ң��
	extern CString g_sLangTxt_Telecommunicating;
	extern CString g_sLangID_FaultReport; //���ϱ���
	extern CString g_sLangTxt_FaultReport;
	extern CString g_sLangID_ProtectEvent; //�����¼�
	extern CString g_sLangTxt_ProtectEvent;
	extern CString g_sLangID_FaultSignal; //�����ź�
	extern CString g_sLangTxt_FaultSignal;
	extern CString g_sLangID_AlarmSignal; //�澯�ź�
	extern CString g_sLangTxt_AlarmSignal;
	extern CString g_sLangID_SamplingValue; //����ֵ
	extern CString g_sLangTxt_SamplingValue;
	extern CString g_sLangID_Telecontrolling; //ң��
	extern CString g_sLangTxt_Telecontrolling;
	extern CString g_sLangID_Custom; //�Զ���
	extern CString g_sLangTxt_Custom;
	extern CString g_sLangID_SingDataMode; //��һ������дģʽ
	extern CString g_sLangTxt_SingDataMode;
	extern CString g_sLangID_ExcelDataMode; //�������дģʽ
	extern CString g_sLangTxt_ExcelDataMode;
	extern CString g_sLangID_ExcelDataMode2; //�������дģʽ
	extern CString g_sLangTxt_ExcelDataMode2;

	//TaskMngr
	extern CString g_sLangID_NewCreatTask; //�½�����
	extern CString g_sLangTxt_NewCreatTask;
	extern CString g_sLangID_NewProject; //�½�����
	extern CString g_sLangTxt_NewProject;
	extern CString g_sLangID_DeleteTask; //ɾ������
	extern CString g_sLangTxt_DeleteTask;
	extern CString g_sLangID_DeleteProject; //ɾ������
	extern CString g_sLangTxt_DeleteProject;
	extern CString g_sLangID_TaskArchive; //����鵵
	extern CString g_sLangTxt_TaskArchive;
	extern CString g_sLangID_ProjectArchive; //���̹鵵
	extern CString g_sLangTxt_ProjectArchive;
	extern CString g_sLangID_OpenProject; //�򿪹���
	extern CString g_sLangTxt_OpenProject;
	extern CString g_sLangID_CloseProject; //�رչ���
	extern CString g_sLangTxt_CloseProject;
	extern CString g_sLangID_TestRecordFile; //���Լ�¼�ļ�
	extern CString g_sLangTxt_TestRecordFile;
	extern CString g_sLangID_RecordFile; //��¼�ļ���С
	extern CString g_sLangTxt_RecordFile;
	extern CString g_sLangID_LastAccessedTimes; //������ʱ��
	extern CString g_sLangTxt_LastAccessedTimes;
	extern CString g_sLangID_ReportFile; //�����ļ�
	extern CString g_sLangTxt_ReportFile;
	extern CString g_sLangID_ReportFileSize; //�����ļ���С
	extern CString g_sLangTxt_ReportFileSize;
	extern CString g_sLangID_NewTask; //������
	extern CString g_sLangTxt_NewTask;
	extern CString g_sLangID_EnterTask; //�������
	extern CString g_sLangTxt_EnterTask;
	extern CString g_sLangID_NewReport; //�±���
	extern CString g_sLangTxt_NewReport;

	extern CString g_sLangID_TestComplete; //�������
	extern CString g_sLangTxt_TestComplete;
	extern CString g_sLangID_TerminationTest; //��ֹ����
	extern CString g_sLangTxt_TerminationTest;
	extern CString g_sLangID_Testing; //������
	extern CString g_sLangTxt_Testing;
	extern CString g_sLangID_UnTest; //δ����
	extern CString g_sLangTxt_UnTest;
	extern CString g_sLangID_SystemPara; //ϵͳ����
	extern CString g_sLangTxt_SystemPara;
	extern CString g_sLangID_CreatWordFail; //����Wordʧ�ܣ��������񱨸�ʧ�ܣ�
	extern CString g_sLangTxt_CreatWordFail;
	extern CString g_sLangID_TestReport; //���Ա���
	extern CString g_sLangTxt_TestReport;
	extern CString g_sLangID_Conclusion; //����
	extern CString g_sLangTxt_Conclusion;
	extern CString g_sLangID_UnqualifiedItem; //�в��ϸ���
	extern CString g_sLangTxt_UnqualifiedItem;
	extern CString g_sLangID_ViewPara; //�鿴����
	extern CString g_sLangTxt_ViewPara;
	extern CString g_sLangID_FctnGbNotFound; //����GbUICreate��ڵ�ַû���ҵ�
	extern CString g_sLangTxt_FctnGbNotFound;

	extern CString g_sLangID_DataBatch; //���ݼ���������
	extern CString g_sLangTxt_DataBatch;
	extern CString g_sLangID_Developing; //������
	extern CString g_sLangTxt_Developing;
	extern CString g_sLangID_ReportManager; //�������
	extern CString g_sLangTxt_ReportManager;
	extern CString g_sLangID_TestReady; //����׼��
	extern CString g_sLangTxt_TestReady;
	extern CString g_sLangID_TestWork; //���Թ����ָ�
	extern CString g_sLangTxt_TestWork;
	extern CString g_sLangID_CellpAdding; //��Ԫ�����
	extern CString g_sLangTxt_CellpAdding;
	extern CString g_sLangID_ColumnFillMmode; //�����ģʽ
	extern CString g_sLangTxt_ColumnFillMmode;
	extern CString g_sLangID_HnagFillMmode; //�����ģʽ
	extern CString g_sLangTxt_HnagFillMmode;
	extern CString g_sLangID_ParaVarious; //��������
	extern CString g_sLangTxt_ParaVarious;
	extern CString g_sLangID_Format; //��ʽ
	extern CString g_sLangTxt_Format;
	extern CString g_sLangID_Id; 
	extern CString g_sLangTxt_Id;
// 	extern CString g_sLangID_Variable; //����
// 	extern CString g_sLangTxt_Variable;
	extern CString g_sLangID_DataVariousDefin; //���ݽӿڱ�������
	extern CString g_sLangTxt_DataVariousDefin;
	extern CString g_sLangID_ProPaInf;    //��Ŀ��·����Ϣ
	extern CString g_sLangTxt_ProPaInf;
	extern CString g_sLangID_TestProjInf;    //������Ŀ��Ϣ
	extern CString g_sLangTxt_TestProjInf;
	extern CString g_sLangID_SetAsReport;    //��Ϊ���ձ���
	extern CString g_sLangTxt_SetAsReport;
	extern CString g_sLangID_ViewMessJud;    //�鿴�����ж�
	extern CString g_sLangTxt_ViewMessJud;
	extern CString g_sLangID_TestProTestRep;    //������Ŀʵ�鱨��
	extern CString g_sLangTxt_TestProTestRep;
	extern CString g_sLangID_InstrutionInfo;
	extern CString g_sLangTxt_InstrutionInfo;
	extern CString g_sLangID_GuideAutoWizardFile;
	extern CString g_sLangTxt_GuideAutoWizardFile;
	extern CString g_sLangID_NextStep;
	extern CString g_sLangTxt_NextStep;
	extern CString g_sLangID_ClickToNextStep;
	extern CString g_sLangTxt_ClickToNextStep;
	extern CString g_sLangID_OperCompleteToNext;
	extern CString g_sLangTxt_OperCompleteToNext;
	extern CString g_sLangID_DataSet;
	extern CString g_sLangTxt_DataSet;
	extern CString g_sLangID_TestItemNotExist;
	extern CString g_sLangTxt_TestItemNotExist;
	extern CString g_sLangID_SetItem;
	extern CString g_sLangTxt_SetItem;
	extern CString g_sLangID_DataMap;
	extern CString g_sLangTxt_DataMap;
	extern CString g_sLangID_DestRefData;
	extern CString g_sLangTxt_DestRefData;
	extern CString g_sLangID_TestItem;
	extern CString g_sLangTxt_TestItem;
	extern CString g_sLangID_NumberGroup;
	extern CString g_sLangTxt_NumberGroup;
	extern CString g_sLangID_ItemClassName;
	extern CString g_sLangTxt_ItemClassName;
	extern CString g_sLangID_ItemClassId;
	extern CString g_sLangTxt_ItemClassId;
	extern CString g_sLangID_BatchEnumGroup;
	extern CString g_sLangTxt_BatchEnumGroup;
	extern CString g_sLangID_BatchItemNoName;
	extern CString g_sLangTxt_BatchItemNoName;
	extern CString g_sLangID_BatchItemNoId;
	extern CString g_sLangTxt_BatchItemNoId;
	extern CString g_sLangID_BatchItemNoDataset;
	extern CString g_sLangTxt_BatchItemNoDataset;
	extern CString g_sLangID_DatasetNotExist;
	extern CString g_sLangTxt_DatasetNotExist;
	extern CString g_sLangID_DataMapNotOnly;
	extern CString g_sLangTxt_DataMapNotOnly;
	extern CString g_sLangID_ChannelCfg;
	extern CString g_sLangTxt_ChannelCfg;
	extern CString g_sLangID_InsertReportTem;
	extern CString g_sLangTxt_InsertReportTem;
	extern CString g_sLangID_CannotInstant;
	extern CString g_sLangTxt_CannotInstant;
	extern CString g_sLangID_InsertTestTem;
	extern CString g_sLangTxt_InsertTestTem;
	extern CString g_sLangID_CommCmdNoDataset;
	extern CString g_sLangTxt_CommCmdNoDataset;
	extern CString g_sLangID_Initial;
	extern CString g_sLangTxt_Initial;
	extern CString g_sLangID_DealSubTemTestPara;
	extern CString g_sLangTxt_DealSubTemTestPara;
	extern CString g_sLangID_OpenedWizardFile;
	extern CString g_sLangTxt_OpenedWizardFile;
	extern CString g_sLangID_SelTestSubTem;
	extern CString g_sLangTxt_SelTestSubTem;
	extern CString g_sLangID_SelSubTem;
	extern CString g_sLangTxt_SelSubTem;
	extern CString g_sLangID_SelTestSubTemInsert;
	extern CString g_sLangTxt_SelTestSubTemInsert;
	extern CString g_sLangID_SelTestSubTemInsert2;
	extern CString g_sLangTxt_SelTestSubTemInsert2;
	extern CString g_sLangID_SaveTestTem;
	extern CString g_sLangTxt_SaveTestTem;
	extern CString g_sLangID_SaveTestTemWizardOver;
	extern CString g_sLangTxt_SaveTestTemWizardOver;
	extern CString g_sLangID_SetTestTemAttr;
	extern CString g_sLangTxt_SetTestTemAttr;
	extern CString g_sLangID_SetTestTemAttr2;
	extern CString g_sLangTxt_SetTestTemAttr2;
	extern CString g_sLangID_SetSubTemInterface;
	extern CString g_sLangTxt_SetSubTemInterface;
	extern CString g_sLangID_SetDeviceDataModel;
	extern CString g_sLangTxt_SetDeviceDataModel;
	extern CString g_sLangID_SetDeviceAttr;
	extern CString g_sLangTxt_SetDeviceAttr;
	extern CString g_sLangID_SetDeviceDataType;
	extern CString g_sLangTxt_SetDeviceDataType;
	extern CString g_sLangID_SetDeviceCharCurve;
	extern CString g_sLangTxt_SetDeviceCharCurve;
	extern CString g_sLangID_SetDeviceAttr2;
	extern CString g_sLangTxt_SetDeviceAttr2;
	extern CString g_sLangID_SetDeviceDataType2;
	extern CString g_sLangTxt_SetDeviceDataType2;
	extern CString g_sLangID_SetDeviceCharCurve2;
	extern CString g_sLangTxt_SetDeviceCharCurve2;
	extern CString g_sLangID_Execute;
	extern CString g_sLangTxt_Execute;
	extern CString g_sLangID_CommCmdError;
	extern CString g_sLangTxt_CommCmdError;
	extern CString g_sLangID_DataPathNoData;
	extern CString g_sLangTxt_DataPathNoData;
	extern CString g_sLangID_IdReplace;
	extern CString g_sLangTxt_IdReplace;
	extern CString g_sLangID_NameReplaceCompleted;
	extern CString g_sLangTxt_NameReplaceCompleted;
	extern CString g_sLangID_AddObjMatchUnsucc;
	extern CString g_sLangTxt_AddObjMatchUnsucc;
	extern CString g_sLangID_ReplaceCompleted2;
	extern CString g_sLangTxt_ReplaceCompleted2;
	extern CString g_sLangID_DealCommCmd;
	extern CString g_sLangTxt_DealCommCmd;
	extern CString g_sLangID_RelNotOnly;
	extern CString g_sLangTxt_RelNotOnly;
	extern CString g_sLangID_DataInterfaceName;
	extern CString g_sLangTxt_DataInterfaceName;
	extern CString g_sLangID_DealMode;
	extern CString g_sLangTxt_DealMode;
	extern CString g_sLangID_StartValue;
	extern CString g_sLangTxt_StartValue;
	extern CString g_sLangID_StepNumber;
	extern CString g_sLangTxt_StepNumber;
	extern CString g_sLangID_SCLChannelName;
	extern CString g_sLangTxt_SCLChannelName;
	extern CString g_sLangID_DataName;
	extern CString g_sLangTxt_DataName;
	extern CString g_sLangID_ChannelIndex;
	extern CString g_sLangTxt_ChannelIndex;
	extern CString g_sLangID_DatasetTraverse;
	extern CString g_sLangTxt_DatasetTraverse;
	extern CString g_sLangID_NumberArithmetic;
	extern CString g_sLangTxt_NumberArithmetic;
	extern CString g_sLangID_InitOptimizeList;
	extern CString g_sLangTxt_InitOptimizeList;
	extern CString g_sLangID_InitPreTestList;
	extern CString g_sLangTxt_InitPreTestList;
	extern CString g_sLangID_InitTestRecoverList;
	extern CString g_sLangTxt_InitTestRecoverList;
	extern CString g_sLangID_OptimizePreTestItem;
	extern CString g_sLangTxt_OptimizePreTestItem;
	extern CString g_sLangID_OptimizeTestRecoverItem;
	extern CString g_sLangTxt_OptimizeTestRecoverItem;
	extern CString g_sLangID_OptimizeIecCfgDownload;
	extern CString g_sLangTxt_OptimizeIecCfgDownload;
	extern CString g_sLangID_OptimizeSysParaEditItem;
	extern CString g_sLangTxt_OptimizeSysParaEditItem;
	extern CString g_sLangID_ItemClassAllSubItem;
	extern CString g_sLangTxt_ItemClassAllSubItem;
	extern CString g_sLangID_ItemClassSubItem;
	extern CString g_sLangTxt_ItemClassSubItem;
	extern CString g_sLangID_SelItemClassMode;
	extern CString g_sLangTxt_SelItemClassMode;
	extern CString g_sLangID_ImportTo;
	extern CString g_sLangTxt_ImportTo;
	extern CString g_sLangID_NoDataObjDef;
	extern CString g_sLangTxt_NoDataObjDef;
	extern CString g_sLangID_FileNameWithout;
	extern CString g_sLangTxt_FileNameWithout;
	extern CString g_sLangID_FileMngr;
	extern CString g_sLangTxt_FileMngr;
	extern CString g_sLangID_Average;
	extern CString g_sLangTxt_Average;
	extern CString g_sLangID_CommCmdCheckComplete;
	extern CString g_sLangTxt_CommCmdCheckComplete;
	extern CString g_sLangID_CommCmdParaAbnormal;
	extern CString g_sLangTxt_CommCmdParaAbnormal;
	extern CString g_sLangID_DeleteInvalidPara;  
	extern CString g_sLangTxt_DeleteInvalidPara;
	extern CString g_sLangID_ElectricCheckComplete;
	extern CString g_sLangTxt_ElectricCheckComplete;
	extern CString g_sLangID_ElectricParaAbnormal;
	extern CString g_sLangTxt_ElectricParaAbnormal;
	extern CString g_sLangID_OpenWordFail;
	extern CString g_sLangTxt_OpenWordFail;
	extern CString g_sLangID_HaveMarkSureReplace;  
	extern CString g_sLangTxt_HaveMarkSureReplace;
	extern CString g_sLangID_NoWord;
	extern CString g_sLangTxt_NoWord;
	extern CString g_sLangID_OpenDocFail;
	extern CString g_sLangTxt_OpenDocFail;
	extern CString g_sLangID_BookMarkExist;
	extern CString g_sLangTxt_BookMarkExist;
	extern CString g_sLangID_InsertTitleFail;  
	extern CString g_sLangTxt_InsertTitleFail;
// 	extern CString g_sLangID_Title;
// 	extern CString g_sLangTxt_Title;
	extern CString g_sLangID_InsertFail;
	extern CString g_sLangTxt_InsertFail;
	extern CString g_sLangID_Finish;
	extern CString g_sLangTxt_Finish;
	extern CString g_sLangID_Unqualified2;
	extern CString g_sLangTxt_Unqualified2;
	extern CString g_sLangID_TestFinish;
	extern CString g_sLangTxt_TestFinish;

	extern CString g_sLangID_SelNoArea;  //_T("sSelNoArea");
	extern CString g_sLangTxt_SelNoArea;  //_T("û��ѡ��������");
	extern CString g_sLangID_SelOnlyOneRowCol;  //_T("sSelOnlyOneRowCol");
	extern CString g_sLangTxt_SelOnlyOneRowCol;  //_T("ѡ��������ֻ��һ��һ�У����߱���������������");
	extern CString g_sLangID_ColRowsNotSame;  //_T("sColRowsNotSame");
	extern CString g_sLangTxt_ColRowsNotSame;  //_T("ѡ��������ÿ�е�����������ͬ�����߱���������������");
	extern CString g_sLangID_SelNoItem;  //_T("sSelNoItem");
	extern CString g_sLangTxt_SelNoItem;  //_T("û��ѡ�������Ŀ��");
	extern CString g_sLangID_MustSelYcItem;  //_T("sMustSelYcItem");
	extern CString g_sLangTxt_MustSelYcItem;  //_T("��ѡ�����ң����Ŀ����Ŀ���࣡");
	extern CString g_sLangID_HasNoMacroTest;  //_T("sHasNoMacroTest");
	extern CString g_sLangTxt_HasNoMacroTest;  //_T("��%s����û�е��������Թ���");
	extern CString g_sLangID_HasNoYcItem;  //_T("sHasNoYcItem");
	extern CString g_sLangTxt_HasNoYcItem;  //_T("��%s����û��ң����Ե��������Թ���");
	extern CString g_sLangID_RepeatTimeNotSame;  //_T("sRepeatTimeNotSame");
	extern CString g_sLangTxt_RepeatTimeNotSame;  //_T("��%s�����ظ�����%d�롾%s�����ظ�����%d��һ��!");
	extern CString g_sLangID_MacroTestNotSame;  //_T("sMacroTestNotSame");
	extern CString g_sLangTxt_MacroTestNotSame;  //_T("��%s���롾%s���Ĳ��Թ��ܲ�һ��!");

	extern CString g_sLangID_AttrID_Value;  //_T("sAttrID_Value");
	extern CString g_sLangTxt_AttrID_Value;  //_T("��ֵ(value)");
	extern CString g_sLangID_AttrID_Name;  //_T("sAttrID_Name");
	extern CString g_sLangTxt_AttrID_Name;  //_T("����(Name)");

	extern CString g_sLangID_TestPrjNotFinish;
	extern CString g_sLangTxt_TestPrjNotFinish;

	extern CString g_sLangID_RsltExprScript;
	extern CString g_sLangTxt_RsltExprScript;

	extern CString g_sLangID_IgnoreAbnormal;  
	extern CString g_sLangTxt_IgnoreAbnormal;

	extern CString g_sLangID_SGroupS;//%s%s-��%d.%s
	extern CString g_sLangTxt_SGroupS;
	extern CString g_sLangID_SGroupFileName;//%s%s-��%d.%s
	extern CString g_sLangTxt_SGroupFileName;

// 	extern CString g_sLangID_IEC_Open;
// 	extern CString g_sLangTxt_IEC_Open;
	extern CString g_sLangID_IEC_AddSCL;
	extern CString g_sLangTxt_IEC_AddSCL;
	extern CString g_sLangID_IEC_DeleteNow;
	extern CString g_sLangTxt_IEC_DeleteNow;
	extern CString g_sLangID_IEC_Emptyout;
	extern CString g_sLangTxt_IEC_Emptyout;
 	extern CString g_sLangID_Native_FileName;
 	extern CString g_sLangTxt_Native_FileName;
// 	extern CString g_sLangID_Native_Choose;
// 	extern CString g_sLangTxt_Native_Choose;
	extern CString g_sLangID_Dates;
	extern CString g_sLangTxt_Dates;
// 	extern CString g_sLangID_Native_Form; //��ʽ
// 	extern CString g_sLangTxt_Native_Form;

	extern CString g_sLangID_FilePath;
	extern CString g_sLangTxt_FilePath;

	extern CString g_sLangTxt_FileSize;
	extern CString g_sLangID_FileSize;

	extern CString g_sLangID_currentfile;
	extern CString g_sLangTxt_currentfile;
	extern CString g_sLangID_parsefile;
	extern CString g_sLangTxt_parsefile;
	extern CString g_sLangID_confirmfiles;
	extern CString g_sLangTxt_confirmfiles;
	extern CString g_sLangID_IEDdialog;
	extern CString g_sLangTxt_IEDdialog;
	extern CString g_sLangID_sameopen;
	extern CString g_sLangTxt_sameopen;

	extern CString g_sLangID_Native_ChooseOpenFile;
	extern CString g_sLangTxt_Native_ChooseOpenFile;
	extern  CString g_sLangID_Gradient_ShowUpath;  
	extern  CString g_sLangTxt_Gradient_ShowUpath;
	extern CString g_sLangID_warning;
	extern CString g_sLangTxt_warning;


	extern CString g_sLangID_UpdataFail                 ;//= _T("sUpdataFail");
	extern CString g_sLangTxt_UpdataFail                ;//= _T("�����Ǹ���:��ѯ[ϵͳ��ʶ:%d,�汾��ʶ:%d]������Ϣʧ��!")
	extern CString g_sLangID_DownloadFile				 ;//= _T("sDownloadFile");
	extern CString g_sLangTxt_DownloadFile              ;//= _T("�����Ǹ���:��ѯ��Ϣ��ɣ���ʼ�����ļ������Ժ�...[ϵͳ��ʶ:%d,�汾��ʶ:%d]");
	extern CString g_sLangID_DownloadFail               ;//= _T("sDownloadFail");
	extern CString g_sLangTxt_DownloadFail              ;//= _T("�����Ǹ���:���ذ汾�ļ�[%s]ʧ��!");
	extern CString g_sLangID_DownloadCompress           ;//= _T("sDownloadCompress ");
	extern CString g_sLangTxt_DownloadCompress          ;//= _T("�����Ǹ���:���ذ汾�ļ�[%s]���,׼����ѹ��!");
	extern CString g_sLangID_LocalUpgrades              ;//= _T("sLocalUpgrades");
	extern CString g_sLangTxt_LocalUpgrades             ;//= _T("�����Ǹ���:�ѽ�������ƽ̨����,��ʼ��ѹ�����°������б�������!");
	extern CString g_sLangID_Reboot                     ;//= _T("sReboot");
	extern CString g_sLangTxt_Reboot                    ;//= _T("�����Ǹ���:�����ɹ���,�轫����������,���Ե�......");	
	extern CString g_sLangID_UnpackSucc                 ;//= _T("sUnpackSucc");
	extern CString g_sLangTxt_UnpackSucc                ;//= _T("�����Ǹ��£���ѹ���ظ��°���%s���ɹ�!");
	extern CString g_sLangID_UnpackFail                 ;//= _T("sUnpackFail");
	extern CString g_sLangTxt_UnpackFail                ;//= _T("�����Ǹ��£���ѹ���ظ��°���%s��ʧ��!");
	extern CString g_sLangID_Update_UpdateSuccess       ;//= _T("sUpdate_UpdateSuccess");
	extern CString g_sLangTxt_Update_UpdateSuccess      ;//= _T("���������ɹ������ֶ���������");

	extern CString g_sLangID_Escalating		             ;//= _T("sEscalating");
	extern CString g_sLangTxt_Escalating			     ;//= _T("����׼�������ļ������Ժ�...");
	extern CString g_sLangID_TesterUpdate				 ;//= _T("sTesterUpdate")
    extern CString g_sLangTxt_TesterUpdate		         ;//= _T("�����Ǹ��£��Ѹ���%.02f%%")
	extern CString g_sLangID_BackupSucc			         ;//= _T("sBackupSucc")
	extern CString g_sLangTxt_BackupSucc				 ;//=_T("�����Ǹ��£��ļ���%s�����ݳɹ�!")
	extern CString g_sLangID_BackupFail				     ;//= _T("sBackupFail")
	extern CString g_sLangTxt_BackupFail				 ;//=_T("�����Ǹ��£��ļ���%s������ʧ��!")
	extern CString g_sLangID_CopySucc				     ;//= _T("sCopySucc")
	extern CString g_sLangTxt_CopySucc				     ;//=_T("�����Ǹ��£��ļ���%s�������ɹ�!")
	extern CString g_sLangID_TesterUpdataFail			 ;//= _T("sTesterUpdataFail")
	extern CString g_sLangTxt_TesterUpdataFail			 ;//=_T("�����Ǹ��£��ļ���%s������ʧ��!")

	//yi
	extern CString g_sLangID_ExpSucc;
	extern CString g_sLangTxt_ExpSucc;
	extern CString g_sLangID_ExpFail;
	extern CString g_sLangTxt_ExpFail;
	extern CString g_sLangID_ImpSucc;
	extern CString g_sLangTxt_ImpSucc;
	extern CString g_sLangID_ImpFail;
	extern CString g_sLangTxt_ImpFail;
	extern CString g_sLangID_RemainingMemorySize;
	extern CString g_sLangTxt_RemainingMemorySize;
	extern CString g_sLangID_InsufficientSystemMemory;
	extern CString g_sLangTxt_InsufficientSystemMemory;
	extern CString g_sLangID_ExistenceSCDFiles;
	extern CString g_sLangTxt_ExistenceSCDFiles;
	extern CString g_sLangID_NoExistenceSCLFiles;
	extern CString g_sLangTxt_NoExistenceSCLFiles;
	extern CString g_sLangID_AnalysisSCLFiles;
	extern CString g_sLangTxt_AnalysisSCLFiles;
	extern CString g_sLangID_LoadSCLFiles;
	extern CString g_sLangTxt_LoadSCLFiles;
	extern CString g_sLangID_LoadSCLFilesProgressBar;
	extern CString g_sLangTxt_LoadSCLFilesProgressBar;
	extern CString 	g_sLangID_SaveSCLFiles ;
	extern CString g_sLangTxt_SaveSCLFiles;
	extern CString g_sLangID_State_No;
	extern CString g_sLangTxt_State_No;
	extern CString g_sLangID_State_Yes;
	extern CString g_sLangTxt_State_Yes;

//shaolei 2024-12-9
	extern CString g_sLangID_AutoTest_SvrName;                       //= _T("sAutoTest_SvrName")
	extern CString g_sLangTxt_AutoTest_SvrName;                      //= _T("�Զ����Է�������")
	extern CString g_sLangID_AutoTest_SvrVersion;				      //= _T("sAutoTest_SvrVersion")
	extern CString g_sLangTxt_AutoTest_SvrVersion;                   //= _T("�Զ����Է���汾")

//���ʰ���ֲ 20250207 xueyangfan
	extern CString g_sLangID_Xrio_EnterNumbers;                 //=_T("Xrio_EnterNumbers");
	extern CString g_sLangTxt_Xrio_EnterNumbers;                //=_T("������һ�����֡�");
	extern CString g_sLangID_Xrio_ValueLessThanOREqual;         //=_T("Xrio_ValueLessThanOREqual");
	extern CString g_sLangTxt_Xrio_ValueLessThanOREqual;        //=_T("ֵ���� <= ");
	extern CString g_sLangID_Xrio_ValueGreaterThanOREqual;      //=_T("Xrio_ValueGreaterThanOREqual");
	extern CString g_sLangTxt_Xrio_ValueGreaterThanOREqual;     //=_T("ֵ���� >= ");
	extern CString g_sLangID_Xrio_InvalidDoublePrecisionValue;  //= _T("Xrio_InvalidDoublePrecisionValue")
	extern CString g_sLangTxt_Xrio_InvalidDoublePrecisionValue; //= _T("��Ч��˫����ֵ��")
	extern CString g_sLangID_Xrio_InvalidIntValue;              //= _T("Xrio_InvalidIntValue")
	extern CString g_sLangTxt_Xrio_InvalidIntValue;             //= _T("��Ч������ֵ��")
	extern CString g_sLangID_Xrio_LogInfo_ParamDataType;        //= _T("Xrio_LogInfo_ParamDataType")
	extern CString g_sLangTxt_Xrio_LogInfo_ParamDataType;       //= _T("������������")
	extern CString g_sLangID_Xrio_LogInfo_NamePath;             //= _T("Xrio_LogInfo_NamePath")
	extern CString g_sLangTxt_Xrio_LogInfo_NamePath;            //= _T("����·��")
	extern CString g_sLangID_Xrio_LogInfo_IDPath;               //= _T("Xrio_LogInfo_IDPath")
	extern CString g_sLangTxt_Xrio_LogInfo_IDPath;              //= _T("ID·��")
	extern CString g_sLangID_Xrio_LogInfo_InvalidParamDataType; //= _T("Xrio_LogInfo_InvalidParamDataType")
	extern CString g_sLangTxt_Xrio_LogInfo_InvalidParamDataType;//= _T("��������Ч�������ͣ��������͸�Ϊ�ַ����ͣ�")
	extern CString g_sLangID_Xrio_LogInfo_MinGreaterThanMax;    //= _T("Xrio_LogInfo_MinGreaterThanMax")
	extern CString g_sLangTxt_Xrio_LogInfo_MinGreaterThanMax;   //= _T("��Сֵ�������ֵ��")
	extern CString g_sLangID_Xrio_InvalidEnumValue;             //= _T("Xrio_InvalidEnumValue")
	extern CString g_sLangTxt_Xrio_InvalidEnumValue;            //= _T("��Ч��ö��ֵ��")
	extern CString g_sLangID_Xrio_InvalidBinaryValue;           //= _T("Xrio_InvalidBinaryValue")
	extern CString g_sLangTxt_Xrio_InvalidBinaryValue;          //= _T("��Ч�Ķ�����ֵ��")