// RtCfgRecordTest.h: interface for the CRtCfgRecordTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCFGRECORDTEST_H__35EAB94E_2297_4694_AE64_F25BFE9EF592__INCLUDED_)
#define AFX_RTCFGRECORDTEST_H__35EAB94E_2297_4694_AE64_F25BFE9EF592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtCfgVariables.h"
#include "RtCfgAppModels.h"
class CRtCfgRecordTests;
#define RT_CANBEUSED    0
#define RT_CANOTBEUSED  1
#define RT_DEVALOPING   2
#define RT_ENTRY        3


class CRtCfgRecordTest : public CExBaseList  
{
public:
	CRtCfgRecordTest();
	virtual ~CRtCfgRecordTest();

//����
public:
	//�ؼ�������
	static const char *g_pszKeyRecordTest;
	static const char *g_pszKeyAppModel;
	static const char *g_pszKeyTestGroup_Type;
	static const char *g_pszKeyRemark;
	static const char *g_pszKeyRtInfo;
	static const char *g_pszKeyAnalysePage;
	static const char *g_pszKeyTestType;

	//�Ӷ�������
	CRtCfgVariables *m_pVariables;    //��������
	//CExBaseList     *m_pAppModels;

	CString m_strTestGroupType;//�����������ID
	CString m_strRemark;//�����Ӳ��˵����Ϣ,�����������������е�Ӳ����������ʾ
	CString m_strRtInfo;//ѡ�е��������Ϣ����
	long    m_nStatus;//�����״̬:��������\����������\������
	CString m_strTestAnalysePage;//�����Ӧ�ķ�������Page����
	CString m_strTestType;//��������ID

//����
public:
	//���صķ���
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTEST;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual long ReadChildrenXml(MSXML::IXMLDOMNodeListPtr &oNodes);
	
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{    return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)   	{    return NULL;	}
	
public:
// 	void InitAppModel(MSXML::IXMLDOMNodePtr &oNode);//�����豸�Ӷ���
	CString GetRTStatusString();
	long GetRTStatus();
	void SetRTStatus(long nRTStatus);
	BOOL IsUniversalTest();

	BOOL IsGetTestTypeOpen()   {	return m_strTestType == g_pRtTestFileType_gopn;	}
	BOOL IsGetTestTypeShort()  {	return m_strTestType == g_pRtTestFileType_gsht;	}

public:
	//�ļ����οؼ���صĲ���
	//virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand);	
};

#endif // !defined(AFX_RTCFGRECORDTEST_H__35EAB94E_2297_4694_AE64_F25BFE9EF592__INCLUDED_)
