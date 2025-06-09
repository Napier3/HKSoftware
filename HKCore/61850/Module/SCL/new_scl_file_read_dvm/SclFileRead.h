#if !defined(AFX_IEDGSSVInfo_H__567421CC_D0D1_48D1_A333_31199FAFFDBB__INCLUDED_)
#define AFX_IEDGSSVInfo_H__567421CC_D0D1_48D1_A333_31199FAFFDBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_SCLFILE_READ_FINISH   (WM_USER + 1411)
#define SCLFILE_READ_SHOW      0
#define SCLFILE_READ_DELCTRLS  1
#define SCLFILE_READ_FINISH    2

#include "..\..\..\Module\BaseClass\ThreadProgressInterface.h"

#include <list>

typedef struct 
{
	CString inPath;
	CString inLNDesc;
	CString inDODesc;
	CString inDADesc;
	CString outPath;

}EXTREFINFO;



#include "SclIecCfgDatas.h"

class CSclFileRead : public CExBaseList
{
public:
	CSclFileRead();   // ��׼���캯��
	virtual ~CSclFileRead();

	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);

public:
	BOOL ReadSclFile(const CString &strFile, CWnd *pOwnerWnd, CThreadProgressInterface *pThreadProgress);
	void FindGSSVControl(CSclIed *pIed, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut);
	void FindGSSVControl(CSclCtrls *pCtrls);
	BOOL FindGSSVControl(CExBaseList *pList);
	BOOL IsInReadState()	{	return m_bIsInReadState;	}

	CSclCtrlGsOut* FindGooseOutput(const CString &strIedName, const CString &strGsID);
	CSclCtrlSmvOut* FindSmvOutput(const CString &strIedName, const CString &strSmvID);

protected:
	CString m_strFile;
	//�ļ��洢�ṹ
	SCL_INFO		m_SclInfo;
	CWnd            *m_pOwnerWnd;

	CThreadProgressInterface *m_pThreadProgress;
protected:
	BOOL m_bIsInReadState;
	bool InitListColumn(void);

	//��ȡ�ļ��߳�
	static UINT ReadSCLThread( LPVOID pParam );

	//��ȡGOOSE��SV��Ϣ
	void ReadGSSVInfo(SCL_INFO* scl_info);

	//dataset�Ƿ�ΪGOOSE��SV
	bool IsDatasetInGSSV(SCL_LN *sclln, char *dataset);

	//��ȡdataset/fcda��Ϣ--���ͺ�����
	ST_RET GetFCDAInfo(SCL_INFO *sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda);
	ST_RET LogFCDAInfo(SCL_INFO *sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda, CDvmData *pDvmData);

	//��ȡdataset/fcda�ڵ�����
	void GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, ST_CHAR *lntype);
	
	//��ȡInputs/ExtRef�ڵ�����
	ST_RET GetExtRefDesc(SCL_AP *sclap, SCL_EXTREF *sclextref);

	//���ҽڵ�����
	void FindDoType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *lntype, char *dotype, char *fcdadodaName);
	void FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName);
	void FindFinalType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype, char *fcdadodaName);

	void FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype);
	void FindFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype);

	//����Inputs/ExtRef�ڵ��ldName,lnName,doName
	void FindextrefName(SCL_EXTREF *sclextref, char *ldName, char *lnName, char *doName);

	//�ַ�������'$'�滻'.'
	void ReplaceDotToDollar(char *srcStr);

	//����ڵ�������dU
	void ConfigDescName(char *srcStr);
	
	//����ڵ�������desc
	void ConfigDoiName(char *srcStr);
	
	//����$/.֮ǰ���ַ���
	bool FindDelStr(char *srcStr, char *findStr);
	
	//UTF8ת��Ϊ���ֽ�
	bool UTF8ToMultiByte(char *srcStr);

	void FindGSSVControl(SCL_INFO *sclinfo, CSclIed *pIed/*CString iedName*/, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut);
	void FindGSOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
						char *apName, char *ldName, char *lnName, CSclCtrlsGsOut *pGsOuts);

	void FindSVOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
						char *apName, char *ldName, char *lnName, CSclCtrlsSmvOut *pSmvOuts);

	void FindGSConnectAP(SCL_INFO *sclinfo, char *iedName, char *apName, 
						char *ldName, char *gcbName, CSclCtrlGs *pGs);

	void FindSVConnectAP(SCL_INFO *sclinfo, char *iedName, char *apName, 
						char *ldName, char *svcbName, CSclCtrlSmv *pSmv);

	void FindGSSVOutChannelInfo(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase);

	void FindGSSVInChannelInfo(SCL_INFO *sclinfo, /*CString dataset,*/ CSclCtrlBase *pCtrlBase);

	void FindOutChannel(SCL_LN *sclln, char *iedName, CSclCtrlBase *pGout);

	void FindInChannel(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase, 
						std::list<EXTREFINFO> *listextref);

	bool ChangeCheckItem(int nItem);

	void FindGSSVInputs(SCL_INFO *sclinfo, SCL_LN *sclln, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path);

	void FindGSSVInControl(SCL_INFO *sclinfo, std::list<CString> *listied, 
							std::list<CString> *listextref, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path);

	void FindGSINControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
						char *iedDesc, char *apName,  char *ldName, char *lnName, 
						std::list<CString> *listied,  std::list<CString> *listextref, CSclCtrlsGsIn *pGsIns
						, SCL_NODE_PATH &scl_path);

	void FindSVINControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
						char *iedDesc, char *apName,  char *ldName, char *lnName, 
						std::list<CString> *listied,  std::list<CString> *listextref, CSclCtrlsSmvIn *pSmvIns
						, SCL_NODE_PATH &scl_path);

	bool IsOutGSSVHaveInGSSVChannel(SCL_LN *sclln, char *dataset, char *iedName, 
								std::list<CString> *listextref);

	void ChangeFCDAMap(SCL_INFO *sclinfo, CString dataset, 
					CString itemtext, CString itemPath);

	//void ChangeDataSetMap(SCL_INFO *sclinfo, CString dataset, CString itemtext);

	void GetSelectInfo(UINT iType);

	void FindAndInsertItem(SCL_INFO *sclinfo, 
							MSXML2::IXMLDOMDocumentPtr gssvDoc, 
							MSXML2::IXMLDOMNodePtr iedNode, 
							int hItem, 
							int iIndex,
							bool bGOOSE);

	void FindAndInsertControl(SCL_INFO *sclinfo, 
							SCL_LN *sclln, 
							CString dataset, 
							MSXML2::IXMLDOMDocumentPtr gssvDoc, 
							MSXML2::IXMLDOMNodePtr dsNode,
							bool bGOOSE);

	void FindAndInsertConnectAP(SCL_INFO *sclinfo,
							CString cdName, 
							MSXML2::IXMLDOMDocumentPtr gssvDoc, 
							MSXML2::IXMLDOMNodePtr dsNode,
							bool bGOOSE);

	void FindAndInsertChannel(SCL_LN *sclln, 
							CString dataset,
							MSXML2::IXMLDOMDocumentPtr gssvDoc, 
							MSXML2::IXMLDOMNodePtr paraNode,
							bool bGOOSE);

	bool IsClickLControlCheckbox();

	void ReadIed(CSclIed *pIed);
	void ReadIed_Ctrls(CSclIed *pIed, CSclCtrls *pCtrls);

protected:
	BOOL IsValueKey(const char *pszKey);
};

#endif
