#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../../../Module/DataMngr/DvmDevices.h"
#include "PpGlobalDefine.h"

class CDataQueryBind : public CExBaseObject
{
public:
	CDataQueryBind();
	virtual ~CDataQueryBind();

public:
	CString m_strDataType;    //数据类型，节点的类型
	CString m_strValue;          //数据
	CExBaseObject *m_pData;     //关联的设备数据模型的节点、数据
};

class CDataQueryBindStatck :	public CExBaseList
{
public:
	CDataQueryBindStatck(void);
	virtual ~CDataQueryBindStatck(void);

	CExBaseObject *m_pDevice;
	long m_nDatasetMode;

	void SetBindCount(long nNewCount);
	CDataQueryBind* SetBind(long nIndex, const CString &strDataType, const CString &strValue);
	CExBaseObject* Query(BOOL bQueryDataNode);  //bQueryDataNode = TRUE,查询节点,而不是Data
	CExBaseObject* GetDataQuery();

	void LogString(const CString &strTitle);
private:
	CExBaseObject* Query(CExBaseList *pList, CDataQueryBind *pBind);
};
