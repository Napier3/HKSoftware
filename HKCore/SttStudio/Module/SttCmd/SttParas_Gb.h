//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
  virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

  //ReadXml
  virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys);

  //WriteXml
  virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

};
