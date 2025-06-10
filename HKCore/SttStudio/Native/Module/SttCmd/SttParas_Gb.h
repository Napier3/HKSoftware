//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.h  CSttParas

#pragma once

#include "SttParas.h"
#include "../../../AutoTest/Module/GuideBook/GuideBook.h"

class CSttParas_Gb : public CSttParas
{
public:
	CSttParas_Gb();
	virtual ~CSttParas_Gb();

	CGuideBook *m_pTestTemplate;
	CItems *m_pItems;
	CDataTypes *m_pDataTypes;

	void AttachItems(CItems *pItems, CDataTypes *pDataTypes);
protected:
	BOOL m_bItemsAttach;
	void FreeItems();

//重载函数
public:
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
  virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

  //ReadXml
  virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys);

  //WriteXml
  virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

};
