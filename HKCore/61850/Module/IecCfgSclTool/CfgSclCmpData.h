#pragma once
#include "CfgSclCmpParaObjects.h"

class CCfgSclCmpData : public CExList  
{
public:
	CCfgSclCmpData(void);
	virtual ~CCfgSclCmpData(void);

	void Init()
	{
		m_pDataParas->DeleteAll();
		DeleteAll();
	}

	CCfgSclCmpParaObjects* GetDataParas()	{	return m_pDataParas;	}
	CCfgSclCmpParaObjects* CreateNewChParaObjects(const CString &strName=_T(""));
	void Compare(CCfgSclCmpData *pCmp);

protected:
	CCfgSclCmpParaObjects *m_pDataParas;  //数据本身的参数集合
		
};
