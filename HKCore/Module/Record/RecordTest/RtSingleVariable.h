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

//属性
public:
	//关键字
// 	static const char *g_pszKeySingleVariable;
// 	static const char *g_pszKeyDCAC;
// 	static const char *g_pszKeyRange;
// 	static const char *g_pszKeyPhaseID;
// 	static const char *g_pszKeyTranChIndex;
// 	static const char *g_pszKeyEndFrequence;

	//自身属性
	CString m_strDCAC;
	CString m_strPhaseID;
	CString m_strUnit;  //单位
	
	//与试验通道相关联的硬件变换器的通道索引位置,方便零值和增益的匹配
	long m_nAttachedTranChannelIndex;
//	long m_nMemBuffer;
	
	long m_nEndFreqSet;//截止频率设置
	BOOL m_bRangeChanged;
	
	//用于校准，位置二有六个通道的变换器时，用于第三个变换器的试验通道和硬件通道的关联
	LPVOID m_pReserved;

	long m_nRangeCoef;//通道量程的临时增益

private:
	double m_dRange;

//方法
public:
	//重载的方法
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
	
	//自适应功能
// 	virtual CExBaseObject* RTClone();		
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);

	//根据属性获取单位
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

	//调整量程和单位
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
