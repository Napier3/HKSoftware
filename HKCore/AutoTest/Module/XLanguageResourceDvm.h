//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"



class CXLanguageResourceDvmBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourceDvmBase();
	virtual ~CXLanguageResourceDvmBase();
	
	void InitLangFileForDebug(const CString &strModule);
private:
	CXLanguage m_oXLangRsDvmBase; 
	static const CString  g_strXLangRsDvmBaseFile; 

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	 

	virtual void InitLangRsByFile(); 
	virtual void RegisterLanguageResource();

public:

	static CString g_sLangID_CanotCreatWnd;//δ�ܴ����������\n
	static CString g_sLangTxt_CanotCreatWnd;
    static CString g_sLangID_ConnetDev;//�����豸�ɹ�
    static CString g_sLangTxt_ConnetDev;
    static CString g_sLangID_CommunError;//ͨѶ�����г��ִ���
    static CString g_sLangTxt_CommunError;
    static CString g_sLangID_CommunTestStop;//ͨѶ�����쳣��������ֹ
    static CString g_sLangTxt_CommunTestStop;
    static CString g_sLangID_NoPrtc;//û��ע���Լ�������
    static CString g_sLangTxt_NoPrtc;
    static CString g_sLangID_CreatPrtcFail;//������ԼͨѶ�豸ʧ��
    static CString g_sLangTxt_CreatPrtcFail;
    static CString g_sLangID_FctnDevelop;//������ƿ�����
    static CString g_sLangTxt_FctnDevelop;
	static CString g_sLangID_Find;//����
	static CString g_sLangTxt_Find;
	static CString g_sLangID_Ge;//��
	static CString g_sLangTxt_Ge;
	static CString g_sLangID_MatchingTurn;//�Ӵ���������ƥ��
	static CString g_sLangTxt_MatchingTurn;
	static CString g_sLangID_Correlation;//����
	static CString g_sLangTxt_Correlation;
	static CString g_sLangID_DelCorrelation;//���ι���
	static CString g_sLangTxt_DelCorrelation;
	static CString g_sLangID_DataSel;//����ѡ��
	static CString g_sLangTxt_DataSel;

	static CString g_sLangID_DelRstNewTest;//Ҫɾ��֮ǰ�Ľ���������µĲ�����
	static CString g_sLangTxt_DelRstNewTest;
	static CString g_sLangID_DevDataTemp;//װ���豸����ģ��
	static CString g_sLangTxt_DevDataTemp;
	static CString g_sLangID_DevDataModelTest;//�豸����ģ�Ͳ���
	static CString g_sLangTxt_DevDataModelTest;
	static CString g_sLangID_DevDataModelCompara;//�豸����ģ�ͱȽ�
	static CString g_sLangTxt_DevDataModelCompara;
	static CString g_sLangID_OutputInf;//�����Ϣ
	static CString g_sLangTxt_OutputInf;
	static CString g_sLangID_CopyOutput;//�������
	static CString g_sLangTxt_CopyOutput;
	static CString g_sLangID_ClearOutput;//������
	static CString g_sLangTxt_ClearOutput;
};	