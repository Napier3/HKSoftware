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
	//读YCTamplate文件接口
	void ReadYCTamplateXml();
	void ReadYCTamplateXml(const CString &strPath);

public:
	//读写
	virtual long XMLReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XMLWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};
