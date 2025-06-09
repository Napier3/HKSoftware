//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmLog.h  CDvmLog

#pragma once


#include "DvmDataset.h"

//////////////////////////////////////////////////////////////////////////
//CDvmLog
class CDvmLog : public CDvmDataset
{
public:
	CDvmLog();
	virtual ~CDvmLog();

	//entry_id = m_strID
	double m_dCurrTime;
	CString  m_strLogCtrl;
	CString  m_strDataset;

//���غ���
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMLOG;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmLogKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

	BOOL GetValueByID(const CString &strValueID, CString &strValue);

};
