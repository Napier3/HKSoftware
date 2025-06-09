//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EcdmDatas.h  CEcdmDatas

#pragma once

#include "EpCapDeviceModelGlobal.h"


#include "EcdmData.h"

class CEcdmDatas : public CExBaseList
{
public:
	CEcdmDatas();
	virtual ~CEcdmDatas();
	long m_nDataType;

//���غ���
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CECDMDATAS;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEcdmDatasKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return CEcdmData::InitListCtrlColumnsFunc;	}

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CEcdmData* FindData(long nDataType,long nItemIndex);
	void InitOffset(long nYxAddr, long nYcAddr, long nYtAddr);
	CEcdmData* AddNewData(CEcdmData *pSrc, long nInsertAfter=-1);

	void GetDatas(CEcdmDatas &oDatas, long nType);
};

