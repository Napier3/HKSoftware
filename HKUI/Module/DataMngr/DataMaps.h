//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DataMaps.h  CDataMaps

#pragma once

#include "DataMngrGlobal.h"
#include "XDataMap.h"


class CDataMaps : public CExBaseList
{
public:
	CDataMaps();
	virtual ~CDataMaps();


	CString  m_strDataType;
//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATAMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
        virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)
        {
#ifdef _PSX_IDE_QT_
            (void)pXmlRWKeys;
#endif
            return CDataMngrXmlRWKeys::CDataMapsKey();
        }

//˽�г�Ա����
private:
	

//˽�г�Ա�������ʷ���
public:
	CXDataMap *AddAddressChild(CVariantDataAddress oVarDataAddr);
	CXDataMap *FindAddressChild(CVariantDataAddress oVarDataAddr, bool bDel = false);

	void AddAddressChild(const CString &strFormat, CString &strAttrVal);
	void AddAddressChild(const CString &strFormat, short &nAttrVal);
	void AddAddressChild(const CString &strFormat, long &nAttrVal);
	void AddAddressChild(const CString &strFormat, int &nAttrVal);
	void AddAddressChild(const CString &strFormat, unsigned int &unAttrVal);
	void AddAddressChild(const CString &strFormat, double &dAttrVal);
	void AddAddressChild(const CString &strFormat, float &fAttrVal);
	void AddAddressChild(const CString &strFormat, char *strAttrVal);
	void AddAddressChild(const CString &strFormat, bool &bAttrVal);	//20241022 huangliang ���bool����

	CString GetAddressFormat(CString &strAttrVal);
	CString GetAddressFormat(short &nAttrVal);
	CString GetAddressFormat(long &nAttrVal);
	CString GetAddressFormat(int &nAttrVal);
	CString GetAddressFormat(unsigned int &unAttrVal);
	CString GetAddressFormat(double &dAttrVal);
	CString GetAddressFormat(float &fAttrVal);
	CString GetAddressFormat(char *strAttrVal);
	CString GetAddressFormat(bool &bAttrVal);	//20241022 huangliang ���bool����
};

