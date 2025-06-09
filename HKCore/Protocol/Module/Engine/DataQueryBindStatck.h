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
	CString m_strDataType;    //�������ͣ��ڵ������
	CString m_strValue;          //����
	CExBaseObject *m_pData;     //�������豸����ģ�͵Ľڵ㡢����
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
	CExBaseObject* Query(BOOL bQueryDataNode);  //bQueryDataNode = TRUE,��ѯ�ڵ�,������Data
	CExBaseObject* GetDataQuery();

	void LogString(const CString &strTitle);
private:
	CExBaseObject* Query(CExBaseList *pList, CDataQueryBind *pBind);
};
