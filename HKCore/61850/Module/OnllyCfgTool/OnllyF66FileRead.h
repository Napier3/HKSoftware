#pragma once
#include "onllydatadef.h"
#include "UIMarkup.h"


#define READATTRIB(Markup,name,OutValue,inValue) \
	OutValue = Markup.GetAttrib(name); \
	if(OutValue == _T("")) \
	{ \
	OutValue = inValue; \
	} \

#define GETCHILDDATA_I(name,value,dvalue) \
	GetChildData(name,strTemp,dvalue); \
	value = _ttoi(strTemp); \

#define GETCHILDDATA_L(name,value,dvalue) \
	GetChildData(name,strTemp,dvalue); \
	value = _ttol(strTemp); \

#define GETCHILDDATA_F(name,value,dvalue) \
	GetChildData(name,strTemp,dvalue); \
	value = _wtof(strTemp); \


#define GETCHILDELEMDATA(name,value,dvalue) \
	value = m_MarkUp.GetChildElemValue(name,dvalue); \


class COnllyF66FileRead
{
public:
	COnllyF66FileRead(void);
	virtual ~COnllyF66FileRead(void);

	vector<MU_SETTING> m_downmu;
	MU_GENERALSETTTING m_mugersetting;  // MUͨ������
	GSEUI m_gseui;

public:
	BOOL ReadF66File(const CString &strPath);

private:
	BOOL ReadMUMSGTestSetXML(MSGTESTSETPtr& MuPtr);
	void ReadMUChnCfgXML(vector<MU_CHNSET>& mu_chnset);
	void ReadGOOSEChnCfgXML(vector<GSECHNCFG>& gsechncfg);
	void ReadMUMSGCfgDataXml(MuCfgData *ChDataPtr);
	void ReadMU92OpData(OTHER92OP& other92op);
	void ReadMUGerSet(MU_GENERALSETTTING& mu_gset);
	void ReadMUCfgXML(vector<MU_SETTING>& mu_setting,const CString& NodeName);
	void ReadGOOSECfgXML(vector<GSECFG>& GseCfg,const CString& NodeName);
private:
	CUIMarkup m_MarkUp;
	DWORD m_nVersion;

private:
	void InitMSGTestSet(const MSGTESTSETPtr& msgtestsetptr)
	{
		msgtestsetptr->nIndex = 0;
		msgtestsetptr->bCheck = FALSE;
		msgtestsetptr->nNum = 100;
		msgtestsetptr->nTestType = 0;
		msgtestsetptr->TestBeginPt = 0;
		memset(&msgtestsetptr->TestTypeSet,0,sizeof(int)*TestType*MaxItem);

		msgtestsetptr->TestTypeSet[1][0] = 10;

		for (int i = 2; i < TestType; i++)
		{
			msgtestsetptr->TestTypeSet[i][0] = 20;
			msgtestsetptr->TestTypeSet[i][1] = 5;
		}

		msgtestsetptr->TestTypeSet[5][2] = 2;
		msgtestsetptr->TestTypeSet[6][2] = 0;
		msgtestsetptr->TestTypeSet[10][2] = 64;
		msgtestsetptr->logicCheck = 1;
		msgtestsetptr->nStartType = 0;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				msgtestsetptr->ExpPtSet[i][j] = 0;
			}
		}
	}

	void GetChildData(LPCTSTR name,CString& Outvalue,LPCTSTR inValue = _T(""))
	{
		if (m_MarkUp.FindChildElem(name))
		{
			Outvalue = m_MarkUp.GetChildData();
			if (Outvalue.IsEmpty())
			{
				Outvalue = inValue;
				return;
			}
		}

// 		CString strText;
// 		strText = name;
// 		CString strMsg;
// 		strMsg.Format(_T("���Ҳ����ڵ�[%s]"), strText);
// 		TRACE(strMsg);
	}

	void GetAttrib(LPCTSTR name,CString& Outvalue,LPCTSTR inValue = _T(""))
	{
		Outvalue = m_MarkUp.GetAttrib(name);

		if(Outvalue.IsEmpty())
		{
			Outvalue = inValue;
		}
	}
};
	


//SMV-�쳣���ݻ����ṹ�嶨��
#define MAX_CTRL_NUM	30
#define MAX_CHNSET_NUM	100
#define MAX_SMV_TESTTYPE_NUM	10


struct struct_ChTest
{
	char pszChName[4];   //Ua~Uw, Ia~Iw
	int ChValue;
};


struct struct_MsgTest_Auto
{		
	int  nTestType;			//��������
	BOOL bLimit;			//�Ƿ����ƴ���
	int  nLmNum;			//���ƴ���

	int  nCtrlSize;			//ѡ��Ŀ��ƿ���	
	int  nCtrlAry[MAX_CTRL_NUM];//���ƿ�����

	int nSetSize;			//�ɵ����
	int nSetAry[MAX_CTRL_NUM][MAX_CHNSET_NUM];//�ɵ�����

	int  nIndex;			//��λ����
	int  TestTypeSet[MAX_SMV_TESTTYPE_NUM][3];	//�������Ͳ�������

	int  nStartStyle;		//��ʼ��ʽ��0:֡����������1:Goose In����

	int	 nBeginPt;			//������ʼ֡
	int  nlogicCheck;		//bit31=1�����߼��룬bit31=0�����߼�������λ������ABCDRabcdr
};


struct struct_MsgTest_UI
{		
	int  nTestType;			// ��������
	int bLimit;			// �Ƿ����ƴ���
	int  nLmNum;			// ���ƴ���

	int  TestTypeSet[3];	// �������Ͳ�������

	int  nIndex;            // ��λ����
	int  nStartStyle;		// ��ʼ��ʽ��0:֡����������1:Goose In����
	int	 nBeginPt;			// ������ʼ֡
	int  nlogicMode;        // 0=�߼���   1=�߼���   ���״̬���ж������ַ�ʽ
	int dwBin;            // 

	int nChTestCount;
	struct struct_ChTest pChTestPara[MAX_VOLT_NUMBER + MAX_CURR_NUMBER];
};

// 
// class CDownLoadCfg : public COnllyDownCfg
// {
// public:
// 	static CDownLoadCfg *g_pDownLoadCfg;
// 	static long g_nDownLoadCfgRef;
// 	static BOOL g_bWinWorkThreadExit;
// 
// 	static CDownLoadCfg* Create();
// 	static void Release();
// 
// private:
// 	CDownLoadCfg(void);
// 	virtual ~CDownLoadCfg(void);
// 
// public:
// 	CMSGManager m_MM1; // һ�Ű�
// 	CMSGManager m_MM2; // ���Ű�
// 
// 	int m_Conn;        // ��ǰ���ӵ��ǵڼ����
// 	vector<MU_SETTING> m_downmu;
// 	MU_GENERALSETTTING m_mugersetting;  // MUͨ������
// 	GSEUI m_gseui;
// 	BOOL m_bDown;  // �����Ƿ�ɹ� 
// 	BOOL m_bDownEx;  // �Ƿ�ң�����������
// 	BOOL m_bSmvExp;  // �Ƿ��쳣����
// 
// 	BOOL m_bIsDownLoadCfgFinish;
// public:
// 
// 	static DWORD WINAPI WinWorkThread(LPVOID lpParameter);
// 
// 	// ��ȡ���ý��������ļ���ֻ����ǰЭ��
// 	void ReadXMLFile(LPCTSTR strPath);
// 	// ʹ��ǰ��ʼ��
// 	void Init();
// 	// ����
// 	BOOL DownLoadCfgFile();
// 	
// 	// �ͷ�CMSGManager
// 	void UnInitialize();
// 	
// private:
// 	BOOL SendParToMainBoard();
// 	void NextAction();
// 	BOOL ShowCheckResult(int nReturnCode,vector<int>& LanVec_re,int nType);
// 	BOOL CompareDevInfo();
// 
// public:
// 	// SMV�쳣�����쳣
// 	BOOL GetErrorString(UINT nIndex,CString& parstring);
// 	void SetErrorString(UINT nIdnex,MSGTESTSETPtr msgtestptr);
// 	void DownLoadErrorString(UINT nIndex, CString& parstring);
// 	void DownLoad(UINT nIndex);
// 
// private:
// 	void ParseString(MSGTESTSETPtr msgtestptr, CString& parstring);
// 	void FindData(CString& string,CString& parstring,int& Pos);
// 
// public:
// 	BOOL SetGSEChnValue(int nCtrlIndex,int nChnIndex,UINT iValue,BOOL bSend = FALSE);
// 	BOOL ReSetGSEChnValue(int nCtrlIndex,int nChnIndex,BOOL bSend = FALSE);
// 
// 
// 	// 2013-07-15����
// 	// ʹ�÷���
// 	// 1���ж���λ���ͺ�֧��֧���쳣ģ��
// 	// 2��SendMsgData_Convert
// 	// ���Ϲ��̶�����������ɺ����
// 	//���� SMV �쳣���ݱ���(�����ṹ��)
// 	HRESULT SendMsgData_Convert(struct_MsgTest_UI *pMsgTest,UINT16 uTotalStateNum=1, UINT16 uCurStateIndex=0);
// 	HRESULT SendMsgData(struct_MsgTest_Auto *pMsgTest,UINT16 uTotalStateNum=1, UINT16 uCurStateIndex=0);
// 	HRESULT SendMsgData_91_92(struct_MsgTest_Auto *pMsgTest,UINT16 uTotalStateNum=1,UINT16 uCurStateIndex=0);
// 	HRESULT SendMsgData_FT3(struct_MsgTest_Auto *pMsgTest,UINT16 uTotalStateNum=1,UINT16 uCurStateIndex=0);
// 
// public:
// 	//�ɵ�����ָ��, ���ݷ������������ݹ������
// // 	void SetSmvExpMgrObj(CSmvExpMgrObj *pMsgObj);
// // 	CSmvExpMgrObj *m_pSmvExpMgrObj;
// 	//�ж��Ƿ�֧�� SMV �쳣ģ��
// 	BOOL IsSupportSmvExp(); 
// 	//�ж��Ƿ��е� 2 �� 821 ��
// 	BOOL HasIO821_2(); 
// 	void InitMsgTest_CtrlAry(struct_MsgTest_Auto *pMsgTest);
// 	void ConvertData(struct_MsgTest_Auto* pMsgTest);
// 	void my_Init_MsgTest(struct_MsgTest_Auto *pMsgTest);
// private:
// 	//���ݲ�ͬ�İ汾���������Ľṹ�壬�Լ��ݾɰ汾�� IO821
// 	void ONLLYDEV_BIEX61850_Standardize(ONLLYDEV_BIEX61850 *pTemp);
// 
//  };

// 
// 
// class CPKTestDownLoadCfg : public CDownLoadCfg
// {
// public:
// 	CPKTestDownLoadCfg(void);
// 	virtual ~CPKTestDownLoadCfg(void);
// 
// private:
// 	BOOL InitMUChnFillSet(MUDOWNCFGSHAREPTR pmudowncfg,
// 		MU_SETTING& musetting,int nSampleType,int nFT3Format);
// 	BOOL InitDownGSECFG(GSEUI& gseui);
// 
// public:
// 	BOOL WriteMUCfgFile(vector<MU_SETTING>* pmusetting,MU_GENERALSETTTING& mugsetting);
// 	BOOL WriteGSEcfgFile(GSEUI& gseui);
// };
