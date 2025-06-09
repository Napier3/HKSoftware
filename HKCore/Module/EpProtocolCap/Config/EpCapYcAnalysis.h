//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapYcAnalysis.h  CEpCapYcAnalysis

#pragma once

#include "MonitorCapConfigGlobal.h"


#include "EpCapYcAnalysisItem.h"

class CEpCapYcAnalysis : public CExBaseList
{
public:
	CEpCapYcAnalysis();
	virtual ~CEpCapYcAnalysis();

	long m_nProtocol;
	CString m_strDeviceModelFile;

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPYCANALYSIS;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEpCapYcAnalysisKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CEpCapYcAnalysisItem* FindByItemIndex(long nItemIndex)
	{
		CEpCapYcAnalysisItem *pNew = NULL;
		CEpCapYcAnalysisItem *pFind = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pNew = (CEpCapYcAnalysisItem *)GetNext(pos);

			if (pNew->m_nItemIndex == nItemIndex)
			{
				pFind = pNew;
				break;
			}
		}

		return pFind;
	}

	CEpCapYcAnalysisItem* AddItemIndex(long nItemIndex)
	{
		CEpCapYcAnalysisItem *pNew = FindByItemIndex(nItemIndex);
		
		if (pNew != NULL)
		{
			return pNew;
		}
		
		pNew = new CEpCapYcAnalysisItem();
		pNew->m_nItemIndex = nItemIndex;
		AddTail(pNew);
		return pNew;
	}
};

