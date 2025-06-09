//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DmDataTemplateGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"

#define DMDTCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define DMDTCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define DMDTCLASSID_CDMDTNODEDATA       (DMDTCLASSID_BASECLASS + 0X00000000)
#define DMDTCLASSID_CDMDTNODEDATAS       (DMDTCLASSID_EXLISTCLASS + 0X00000001)
#define DMDTCLASSID_CDMDATATEMPLATE       (DMDTCLASSID_EXLISTCLASS + 0X00000002)

class CDmDataTemplateXmlRWKeys : public CXmlRWKeys
{
protected:
	CDmDataTemplateXmlRWKeys();
	virtual ~CDmDataTemplateXmlRWKeys();
	static long g_nDMDTRef;

public:
	static CDmDataTemplateXmlRWKeys* g_pXmlKeys;
	static CDmDataTemplateXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCDmDataTemplateKey; //dm-template
	BSTR m_strCDmdtNodeDatasKey; //node-datas
	BSTR m_strCDmdtNodeDataKey; //data
	BSTR m_strIndexKey; //index
	BSTR m_strUnitKey; //Unit

public:
	static BSTR CDmDataTemplateKey()  {   return g_pXmlKeys->m_strCDmDataTemplateKey;  }
	static BSTR CDmdtNodeDatasKey()  {   return g_pXmlKeys->m_strCDmdtNodeDatasKey;  }
	static BSTR CDmdtNodeDataKey()  {   return g_pXmlKeys->m_strCDmdtNodeDataKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
};



class CDmDataTemplateConstGlobal
{
private:
	CDmDataTemplateConstGlobal();
	virtual ~CDmDataTemplateConstGlobal();

public:
	static CDmDataTemplateConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CDmDataTemplateConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
