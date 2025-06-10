// RtChannel.h: interface for the CRtChannel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCHANNEL_H__CCA0E872_155C_422A_9323_977083B53F46__INCLUDED_)
#define AFX_RTCHANNEL_H__CCA0E872_155C_422A_9323_977083B53F46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseObject.h"
#include "RecordTestClassDef.h"
class CRtVariable;
class CRtChannel : public CExBaseObject  
{
public:
	CRtChannel();
	virtual ~CRtChannel();
	
public:
	//���صķ���
	virtual UINT GetClassID();
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
#endif

public:
	//�ؼ���
// 	static const char *g_pszKeyChannel;
	CRtVariable* m_pAttachVariable;//ͨ��ͨ��ID������Ӧ��ͨ����ʵ�ּ�GetAttchVariableByID()
	CRtVariable* GetAttchVariableByID();

	//���ⲿ���ù�����ͨ��,fdp add 2010.7.3
	void SetAttachVariable(CRtVariable* pAttachVariable);

	//��ʼ������Ӧ��������ͨ���µ�Channal
	void InitChannal(const char *pszChName);

public:
#ifdef _record_use_all_mode_
	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif


	
};

#endif // !defined(AFX_RTCHANNEL_H__CCA0E872_155C_422A_9323_977083B53F46__INCLUDED_)
