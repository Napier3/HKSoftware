// RtSingleVariable.h: interface for the CRtSingleVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSINGLEVARIABLE_H__CBFAE646_3FE6_4D5F_8803_169ED122AB89__INCLUDED_)
#define AFX_RTSINGLEVARIABLE_H__CBFAE646_3FE6_4D5F_8803_169ED122AB89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtVariable.h"

class CRtSingleVariable : public CRtVariable  
{
public:
	CRtSingleVariable();
	virtual ~CRtSingleVariable();

//����
public:
	//�ؼ���
// 	static const char *g_pszKeySingleVariable;
// 	static const char *g_pszKeyDCAC;
// 	static const char *g_pszKeyRange;
// 	static const char *g_pszKeyPhaseID;
// 	static const char *g_pszKeyTranChIndex;
// 	static const char *g_pszKeyEndFrequence;

	//��������
	CString m_strDCAC;
	CString m_strPhaseID;
	CString m_strUnit;  //��λ
	
	//������ͨ���������Ӳ���任����ͨ������λ��,������ֵ�������ƥ��
	long m_nAttachedTranChannelIndex;
//	long m_nMemBuffer;
	
	long m_nEndFreqSet;//��ֹƵ������
	BOOL m_bRangeChanged;
	
	//����У׼��λ�ö�������ͨ���ı任��ʱ�����ڵ������任��������ͨ����Ӳ��ͨ���Ĺ���
	LPVOID m_pReserved;

	long m_nRangeCoef;//ͨ�����̵���ʱ����

private:
	double m_dRange;

//����
public:
	//���صķ���
	virtual UINT GetClassID(){		return RTCLASSID_SINGLEVARIABLE;	}	
#ifdef _record_use_all_mode_
	virtual long ReadXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);	
	virtual BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif
	virtual long GetRtVariableClassID()		{	return 0;	}
	
	//����Ӧ����
// 	virtual CExBaseObject* RTClone();		
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);

	//�������Ի�ȡ��λ
	virtual CString GetUnitString();

	void SetRange(double dRange)
	{	
		if (dRange < 1.0)
		{
			dRange = 1.0;
		}

		m_dRange = dRange;
		AdjustRangeAndUint(m_dRange);
		InitRangeCoef();
	}
	double GetRange()				{	return m_dRange;	}
	double* GetRangeRef()			{	return &m_dRange;	}
	double GetRangeEx()				{	return m_dRange*m_nRangeCoef;  }
	
	CMemBuffer_Float *GetEffcAttrBuffer();
	
	void SetAttachedTranChannelIndex(long AttachedTranChannelIndex)	{	m_nAttachedTranChannelIndex = AttachedTranChannelIndex;	}
	
	BOOL IsDCVariable()		{	return (_stricmp(g_pszKeyVariableDC, m_strDCAC.GetString()) == 0);	}
	BOOL IsACVariable()		{	return (_stricmp(g_pszKeyVariableAC, m_strDCAC.GetString()) == 0);	}
	BOOL IsACDCVariable()	{	return (_stricmp(g_pszKeyVariableACDC, m_strDCAC.GetString()) == 0);	}

	//�������̺͵�λ
	void AdjustRangeAndUint(double &dRange);
	void InitRangeCoef()
	{
		if (m_dRange < 1)
		{
			m_nRangeCoef = 1000;
		}
		else
		{
			m_nRangeCoef = 1;
		}
	}

	void CreateStaticAttrs(const CString &strName);

	CRtDataAttribute* CreateAttrByID(const CString& strID,const CString& strVarName, long nIndex);
	CString CmbVariableID();
};

#endif // !defined(AFX_RTSINGLEVARIABLE_H__CBFAE646_3FE6_4D5F_8803_169ED122AB89__INCLUDED_)
