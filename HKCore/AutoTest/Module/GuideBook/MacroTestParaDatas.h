#pragma once

#include "GuideBookDefine.h"
#include "MacroTestParaData.h"

class CMacroTestParaDatas : public CExBaseList
{
public:
	CMacroTestParaDatas();
	virtual ~CMacroTestParaDatas();

protected:
	

public:
	virtual UINT GetClassID()		{		return GBCLASSID_FAULTPARAS;			}

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual void InitAfterRead();

	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaKey;  }

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	CExBaseObject* FindParaById(const CString &strID);
	CExBaseObject* FindSysVarByPathID(const CString& strID);
	CExBaseObject* AddPara(const CString &strID);
	CExBaseObject* AddPara(CShortData *pData);

	//将参数对象的数据设置到IShortDatas中
	void SetToDatasValue(CTestMacro* pTestMacro, BOOL bUseDefaultVal=TRUE);
	void SetToDatasValue(CShortDatas *pDatas, BOOL bUseDefaultVal=TRUE);
	void SetToDatasValue(CShortData *pData, UINT nRootClassID=0, BOOL bUseDefaultVal=TRUE);
	void SetToDatasValue(CDataGroup *pDataGroup, UINT nRootClassID=0, BOOL bUseDefaultVal=TRUE);
	void UpdateMacroTestParaData(const CShortData  *pData, BOOL bShowLog, BOOL bUseDefaultValue);
	void UpdateMacroTestParaData(const CString &strID, const CString &strValue, BOOL bShowLog, BOOL bUseDefaultValue);
	void ResetMacroTestParaData();
	void UpdateMacroTestParaDatas();
	CExBaseObject* FindMacroTestParaData(const CShortData  *pData);
	void UpdateMacroTestParaDataUser(const CShortData  *pData);

	BOOL SetPara(const CString &strIDPath, const CString &strValue);
	BOOL GetParaValue(const CString &strID, double &dValue);

};

class CMacroTestParaDatasUser : public CMacroTestParaDatas
{
public:
	CMacroTestParaDatasUser();
	virtual ~CMacroTestParaDatasUser();

public:
	virtual UINT GetClassID()		{		return GBCLASSID_FAULTPARASUSER;							}
	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaUserKey;		}
	virtual CBaseObject* Clone();

};