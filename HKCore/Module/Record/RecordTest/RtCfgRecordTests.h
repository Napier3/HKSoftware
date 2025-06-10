// RtCfgRecordTests.h: interface for the CRtCfgRecordTests class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCFGRECORDTESTS_H__1638E34E_91C4_4880_A4E0_A80A78DFB2F0__INCLUDED_)
#define AFX_RTCFGRECORDTESTS_H__1638E34E_91C4_4880_A4E0_A80A78DFB2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"

#include "RtCfgRecordTest.h"
#include "RtCfgAppModels.h"
//#include "../HDManager/HDMrDevice.h"

//####################CRtType#############################

class CRtType : public CExBaseList  
{
public:
	CRtType();
	virtual ~CRtType();
	
	//����
public:
	//�ؼ�������
	static const char *g_pszKeyType;
	
	//����
public:
	//���صķ���
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTESTTYPE;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	
	//û���õ�
	//CRtType* Clone();
};

//####################CRtTypes#############################
/*�������͹������,����ÿ����������,�������Ͱ���:���������顢��·�����顢�������顢ͨ������
*/
class CRtTypes : public CExBaseList  
{
private:
	CRtTypes();
	virtual ~CRtTypes();
	
	//����
public:
	//�ؼ�������
	static const char *g_pszKeyTypes;
	static const char *g_pszKeyGenerTransformer;
	static const char *g_pszKeyCircuitGroup;
	static const char *g_pszKeyOther;
	static const char *g_pszKeyUniversal;
public:
	static CRtTypes* g_pRtTypes;
	static long  m_nRtTypesRefCount;
	
	static CRtTypes* CreateRtTypes();
	void Release();
	
	//����
public:
	//���صķ���
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTESTTYPES;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
// 	
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()						{     return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)		{     return NULL;	}
// 	
// 	//��������û���õ�
// 	CRtType* Clone(const CString &strID);
};


/*ʵ�����鹦�ܵ����ã�����Ӳ��ƥ�����飬��������������Ҫ�����黷��(���豸�ͺš�ͨ����Ϣ)����������
*/
class CRtCfgRecordTests : public CExBaseList  
{
private:
	CRtCfgRecordTests();
	virtual ~CRtCfgRecordTests();

public:

	static CRtCfgRecordTests *g_pRtCfgRecordTests;
	static long  m_nRtCfgRecordTestsRefCount;
	static CRtCfgRecordTests* CrteateRtCfgRecordTests();
	void Release();
	
//����
public:
	//�ؼ�������
	static const char *g_pszKeyRecordTests;
	static const char *g_pszConfigFile;

	//CRtCfgAppModels *m_pAppModels;//�豸�ͺŹ������
	CRtTypes *m_pRtTypes;//�������������
	CString m_strCurrRTtestInfo;
	CRtCfgRecordTest *m_pActiveRecordTest;//��ǰ��������Ķ���ָ�룬�����������������������
//����
public:
	//���صķ���
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTESTS;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
// 	virtual long ReadChildrenXml(MSXML::IXMLDOMNodeListPtr &oNodes);
// 	
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()						{     return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)		{     return NULL;	}
	
	//������ط���
	//��ȡ���������ļ�
	BOOL ReadRtConfigFile(const CString &strFile);
	BOOL ReadRtConfigFile();

	//ƥ��Ӳ��
// 	BOOL MatchTranslator(CHDMrDevice * pHDMrDevice);

	//��ǰѡ��������Ϣ�Ĳ���
	void SetCurrTestInfo(CString strTestInfo) {	  m_strCurrRTtestInfo = strTestInfo;	}
	CString GetCurrTestInfo()				  {   return m_strCurrRTtestInfo;	}

	//������������Ͳ������ڵ��������ָ�룬�Դ���Ӧ�ķ�������
	CRtCfgRecordTest *FindByTestType(const CString &strTestType);
	
public:	
	//�ļ����οؼ���صĲ���
//	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand);
	
private:
	//�����������ͣ������������Ͱ������������顢��·������ȣ�������Щ���ཫÿ������������з���	
	void AdjustTestByType();
	
	//����ͨ�����飬����ʾ��������¼��
	void AdjustUniversalTest();

	//����������������̣����������򣬱���ƥ��Ӳ��
	void SortTranRangeFromSmallToLarge(double *dRange, CExBaseList &oTranChannelList);//����SortTransChannelRange
	void SortTransChannelRange(double *dRange, int Count);//����Sort()
	void Sort(double *dRange,int left,int right);//�����㷨

	//ƥ��Ӳ��
	BOOL IsMatchFinish(long nMatchCount, CExBaseList &oChannelList);
	long MatchChannelRange(CExBaseList &oChannelList, double *dRange, long nTransUorICount);
};

inline CRtCfgRecordTests* GetCfgRecordTests()
{
	return CRtCfgRecordTests::g_pRtCfgRecordTests;
}



#endif // !defined(AFX_RTCFGRECORDTESTS_H__1638E34E_91C4_4880_A4E0_A80A78DFB2F0__INCLUDED_)
