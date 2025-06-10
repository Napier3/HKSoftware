// RtSet.h: interface for the CRtSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSET_H__F9967D2E_8027_42BA_8AF1_3BBC0B0C700F__INCLUDED_)
#define AFX_RTSET_H__F9967D2E_8027_42BA_8AF1_3BBC0B0C700F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseObject.h"
#include "RtScript.h"
#include "../RecordGlobalDefine.h"

class CRtDataAttribute;
class CRtDataAttributes;
class CRtVariable;
class CMR1200BaseApp;

#define  SET_TYPE_HIGH		0
#define  SET_TYPE_LOW		1
#define  SET_TYPE_MUTATION  2
class CRtSet : public CExBaseObject  
{
public:
	CRtSet();
	virtual ~CRtSet();
public:
	//�ڵ�����
	long    m_nUse;
	CString m_strUnit;
	double  m_dValue;
	long    m_nSratupIndex;//������˳����������Ҫ������¼��ʱʹ��
	CString m_strType;

	long m_nSetType;
	//�ؼ���
	static const char *g_pszKeyUse;
	static const char *g_pszKeyUnit;
	static const char *g_pszKeyValue;
	static const char *g_pszKeySet;
	static const char *g_pszKeyType;

	static const char* g_pszKeyHigh;
	static const char* g_pszKeyLow;
	static const char* g_pszKeyMutation;
public:
	//���صķ���
	virtual UINT GetClassID();//�õ���ID
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//������ڵ�
// 	virtual const char* GetXmlElementKey();
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

	//���Ա��ⲿ���õķ���
// 	BOOL WriteSetValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
// 	BOOL ReadSetValueXml(MSXML::IXMLDOMNodePtr &oSet);
	BOOL JudgeStartup(long &nStartup);
	BOOL JudgeStartup(long &nStartup,double* pdAttrValue,double* pdMutationValue);
	void SetUse(long nUse);
	long GetUse()	{	return m_nUse;	}
	BOOL BuildExpression();
	
	//����Ӧ����
// 	virtual CExBaseObject* RTClone();
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);

	//�ļ����οؼ���صĲ���
	//virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand);
	
private:
	CRtScript m_oScript;//�ж������Ľű�����

	//void _JudgeStartUpByValue(double dValue, long &nStartup);
	void GetSetLongTypeByStringType();
};

#endif // !defined(AFX_RTSET_H__F9967D2E_8027_42BA_8AF1_3BBC0B0C700F__INCLUDED_)
