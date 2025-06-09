#pragma once
#include "..\..\..\Module\BaseClass\StBaseList.h"
#include "..\..\..\Module\System\VariantDataAddress.h"

#define CFGSCL_PARA_TYPE_NONE   0
#define CFGSCL_PARA_TYPE_HEX    1

class CCfgSclCmpParaObject : public CExObject
{
public:
	CCfgSclCmpParaObject(void);
	virtual ~CCfgSclCmpParaObject(void);

	CCfgSclCmpParaObject(const CString &strName,int *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,long *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,DWORD *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,float *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,double *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,unsigned char *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,short *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,char **value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject(const CString &strName,CString *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);

	BOOL CompareID(char *pszID)				{	return (m_strID == CString(pszID));			}
	BOOL CompareID(const CString &strID)	{	return (m_strID == strID);					}
	BOOL CompareValAddr(LPVOID pValAddr)	{	return m_varValue.CompareValAddr(pValAddr);	}

	void Init()
	{
		m_bSameValue = FALSE;
		m_dwShowType = -1;
		m_pRef = NULL;
	}
public:
	CVariantDataAddress m_varValue;	//关键字的实际值
	BOOL m_bSameValue;
	DWORD m_dwShowType;
	long m_nShowLength;
	CCfgSclCmpParaObject *m_pRef;

public:
	void SetValue(const CString &strValue);
	float GetValue();
	CString GetValueString();
	CString GetVariable()	{	return m_strID;}
	CString GetName()	{	return m_strName;}
	void Compare(CCfgSclCmpParaObject *pCmp);
};
