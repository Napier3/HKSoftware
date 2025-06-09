#pragma once
#include "..\..\..\..\Module\BaseClass\ExBaseList.h"


class CPmcYCTemplate :public CExBaseList
{
private:
	CPmcYCTemplate(void);
	virtual ~CPmcYCTemplate(void);

public:
	static long g_nPmcYCTemplateRef;
	static CPmcYCTemplate* g_pPmcYCTemplate;
	static CPmcYCTemplate* CreatetPmcYCTemplate();
	static void Release();

public:
	//��YCTamplate�ļ��ӿ�
	void ReadYCTamplateXml();
	void ReadYCTamplateXml(const CString &strPath);

public:
	//��д
	virtual long XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};
