// RtSets.h: interface for the CRtSets class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSETS_H__16F7C903_BF19_4E51_9F95_ABC4694350ED__INCLUDED_)
#define AFX_RTSETS_H__16F7C903_BF19_4E51_9F95_ABC4694350ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtSet.h"

class CRtSets : public CExBaseList  
{

public:	
	CRtSets();
	virtual ~CRtSets();
	
public:
	//�ؼ���
	static const char *g_pszKeySets;

public:
	//���صķ���
	virtual UINT GetClassID();
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
// 	virtual const char* GetXmlElementKey();
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

	//���Ա��ⲿ���õķ���
// 	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
// 	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
	BOOL JudgeStartup(long &nStartup);
	BOOL JudgeStartup(long &nStartup,double* pdAttrValue,double* pdMutationValue);
	BOOL BuildExpression();
	void IsSetsUsed();
	void ResetUse();
// 	CExBaseObject* RTClone();
	
	//�������Ͳ��Ҷ�ֵ,fdp add 2010.7.3
	CRtSet* FindSetByType(const char* strType);
	
	//����Ӧ��������ͨ����ֵ
	void CreateMultiAttrSets(const CString &strAttrID);

	//������ֵ��ֵ
	void CreateSetHighByAttrID(const CString &strAttrID);
	
	//������ֵ��ֵ
	void CreateSetLowByAttrID(const CString &strAttrID);
	
	//������ֵͻ��ֵ
	void CreateSetMutationByAttrID(const CString &strAttrID);
};

#endif // !defined(AFX_RTSETS_H__16F7C903_BF19_4E51_9F95_ABC4694350ED__INCLUDED_)
