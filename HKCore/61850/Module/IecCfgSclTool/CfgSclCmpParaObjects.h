#pragma once
#include "CfgSclCmpParaObject.h"

class CCfgSclCmpParaObjects : public CExList  
{
public:
	CCfgSclCmpParaObjects(void);
	virtual ~CCfgSclCmpParaObjects(void);

public:
	CCfgSclCmpParaObject* RegisterPara(const CString &strName,char **value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, int *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, long *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, DWORD *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, float *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, double *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, unsigned char *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, short *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, CString *value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0);

	CCfgSclCmpParaObject* RegisterPara(const CString &strName, int &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, long &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, DWORD &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, float &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, double &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, unsigned char &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, short &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}
	CCfgSclCmpParaObject* RegisterPara(const CString &strName, CString &value,DWORD dwType=CFGSCL_PARA_TYPE_NONE, long nLength=0)
	{
		return RegisterPara(strName, &value,dwType, nLength);
	}

	void UnRegisterPara(const char *pszID);
	void UnRegisterPara(const CString &strID);
	void UnRegisterPara(LPVOID pValAddr);

	void EditParaName(const char *pszID, const char *pszName);
	void EditParaName(const CString &strID, const CString &strName);
	void EditParaName(LPVOID pValAddr, const char *pszName);

	CCfgSclCmpParaObject* FindByVariable(const CString strID);
	float GetValueByVariable(const CString &strID);

	void Compare(CCfgSclCmpParaObjects *pCmp);
	void Compare(CCfgSclCmpParaObject *pCmp);

	void GetCmpParas(CExList &olistCmp, CExList &oListEmpty);

private:
	void FindPara(const CString &strID, CCfgSclCmpParaObject **ppFind, TPOS *pPos);
	void FindPara(LPVOID pValAddr, CCfgSclCmpParaObject **ppFind, TPOS *pPos);

};
