//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapYcAnalysisItem.h  CEpCapYcAnalysisItem

#pragma once

#include "MonitorQueryConfig.h"

#define DRAWTYPE_POINT      0
#define DRAWTYPE_LINE       1
#define DRAWTYPE_STEPLINE   2

class CEpCapYcAnalysisItem : public CExBaseObject
{
public:
	CEpCapYcAnalysisItem();
	virtual ~CEpCapYcAnalysisItem();


	long  m_nItemIndex;
	long  m_nColor;
	long  m_nDrawType;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPYCANALYSISITEM;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEpCapYcAnalysisItemKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

