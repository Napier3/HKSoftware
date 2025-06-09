// RtMultiVariable.h: interface for the CRtMultiVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTMULTIVARIABLE_H__1F396402_0F79_43A2_A9ED_1387995EDE53__INCLUDED_)
#define AFX_RTMULTIVARIABLE_H__1F396402_0F79_43A2_A9ED_1387995EDE53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtVariable.h"
 
//CRtMultiVariable�ļ����ǻ������Ե�
class CRtMultiVariable : public CRtVariable  
{
public:
	CRtMultiVariable();
	virtual ~CRtMultiVariable();

//����
public:	
	//�ؼ�������
// 	static const char *g_pszKeyMultiVariable;
// 	static const char *g_pszKeyDCAC;

	//��������
	CString m_strDCAC;

//����
public:
	//���صķ���
	virtual UINT GetClassID()    {    return RTCLASSID_MULTIVARIABLE;    }
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	virtual BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);	
	virtual const char* GetXmlElementKey();
#endif
	virtual long GetRtVariableClassID()		{	return 0;	}
	virtual BOOL GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer);

	//�������Ի�ȡ��λ
	virtual CString GetUnitString();

	//��������Ӧmultiariable���Ӷ���
	void AutofitCreateMultiNewChild(const CString & strMultiID, char **szAutoMultiChsName);

	//����Channel��ID��ʼ��MultiVariable������
	void UpdateStrNameByChannels();

	BOOL IsDCVariable()		{	return (_stricmp(g_pszKeyVariableDC, m_strDCAC.GetString()) == 0);	}
	BOOL IsACVariable()		{	return (_stricmp(g_pszKeyVariableAC, m_strDCAC.GetString()) == 0);	}
	BOOL IsACDCVariable()	{	return (_stricmp(g_pszKeyVariableACDC, m_strDCAC.GetString()) == 0);	}

};

#endif // !defined(AFX_RTMULTIVARIABLE_H__1F396402_0F79_43A2_A9ED_1387995EDE53__INCLUDED_)
