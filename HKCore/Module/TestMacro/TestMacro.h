//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacro.h  CTestMacro

#pragma once

#include "TestMacroGlobal.h"


#include "TmFaultParas.h"
#include "TmSysParas.h"
#include "TmResultParas.h"
#include "TmFaultParasEx.h"
#include "TmResultParasEx.h"

class CTestMacro : public CExBaseList
{
public:
	CTestMacro();
	virtual ~CTestMacro();


	CString  m_strVersion;
	CString  m_strType;
	CString  m_strRemark;

	CString m_strFile;   //shaolei 20210706

//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacroKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);   //shaolei 20210708
    virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

    virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CTmFaultParas *m_pFaultParas;
	CTmSysParas *m_pSysParas;
	CTmResultParas *m_pResults;
	CTmSearchResultParas *m_pSearchResults;
	CTmFaultParasEx *m_pFaultParasEx;
	CTmResultParasEx *m_pResultsEx;

	//2021-8-15  lijunqing��ע����������remark���з�������ϰ汾����
	CExBaseList m_listFaultParasGroup;
	CExBaseList m_listSysParasGroup;

	//ͳһ��DvmDataGroup  2020-10-06
	CDataGroup *m_pFaultParas_Dvm;
	CDataGroup *m_pResults_Dvm;

public:
	//2023-1-6  shaolei  ��չ���ϲ�������չ����������ֱ�����ɵ���������
	CExBaseList m_list_FaultParasEx;
	CExBaseList m_list_ResultParasEx;

//˽�г�Ա�������ʷ���
public:
	CShortDatas* GetFaultParas()	{	return m_pFaultParas;	}
	CShortDatas* GetSearchResults()	{	return m_pSearchResults;	}
	CShortDatas* GetSysParas()		{	return m_pSysParas;		}
	CShortDatas* GetResults()		{	return m_pResults;		}
	CShortData* FindDataByID(const CString &strID);
	CTmFaultParasEx* GetFaultParasEx()	{	return m_pFaultParasEx;	}
	CTmResultParasEx* GetResultsEx()		{	return m_pResultsEx;	}

	virtual void OnSetParaValue(CShortData *pPara, CExBaseList &listNew, CExBaseList &listDelete);
	virtual void OnSetParaValue(const CString &sttrIDPath, const CString &strValue, CExBaseList &listNew, CExBaseList &listDelete, CExBaseList &listChanged);

	//lijunqing 2021-8-15  
	CDataGroup* GetFaultParas_Dvm()	{	return m_pFaultParas_Dvm;	}
	CDataGroup* GetResults_Dvm()	{	return m_pResults_Dvm;	}

//////////////////////////////////////////////////////////////////////////
//�������鹦��
public:
	CExBaseList* GetFaultParasGroups()	{	return &m_listFaultParasGroup;	}
	CExBaseList* GetSysParasGroups()	{	return &m_listSysParasGroup;	}
	void InitParasGroup();
	void ResetDatas(CExBaseList &listDatas);
	void ResetDatas();

	void GetParasValues(CValues *pValues);

	//2020-10-06  lijunqing
	void GetTestMacroParas(CDataGroup *pParas, CDataGroup *pResults);
	void GetTestMacroParas_Fault(CDataGroup *pParas);
	void GetTestMacroParas_Result(CDataGroup *pResults);
	void InitParas_Dvm();
	void GetTestMacroParas_Fault_CloneEx(CDataGroup *pParas);
	void GetTestMacroParas_Result_CloneEx(CDataGroup *pResults);

	//�����ĸ��������ֱ���չ���ϲ�������չ��������������һ������
	void InitFaultParasEx();
	void InitResultParasEx();
	void InitFaultParasEx(CExBaseList &oList, long nStateCount=-1);
	void InitResultParasEx(CExBaseList &oList, long nStateCount=-1);
	long GetStateNum(const CString &strDataID);  //״̬�������⴦���Ӳ���ID�л�ȡ״̬��

	void GetParaIDPath(CString &strPath, CShortData *pPara);
	CString GetParaIDPath(CShortData *pPara);
	void GetParaNamePath(CString &strPath, CShortData *pPara);
	CString GetParaNamePath(CShortData *pPara);

private:
	CShortDatas* FindGroupByID(CExBaseList *pListGroup, const CString &strID);
	CShortDatas* AddGroupByID(CExBaseList *pListGroup, const CString &strID, POS &posFirst);
	void AddParaToGroup(CShortData *pData, CExBaseList *pListGroup, POS &posFirst);
	void AddParasToGroup(CShortDatas *pDatas, CExBaseList *pListGroup, POS &posFirst);

	void FreeParasGroup(CExBaseList *pListGroup);
	void AppendValues(CExBaseList *pList, CValues *pValues);

	//shaolei 20210706
public:
	BOOL SaveFile();   
	void SetParasToDefault(); // shaolei  2021119 �����в������û�Ĭ��ֵ
	void SetParasToDefault(CShortDatas *pDatas);

};

