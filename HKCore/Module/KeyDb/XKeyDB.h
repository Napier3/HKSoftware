//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XKeyDB.h  CXKeyDB

#pragma once

#include "KeyDbGlobal.h"


#include "XKeyBase.h"
#include "XMultiKeyBase.h"

class CXKeyDB : public CExBaseList
{
public:
	CXKeyDB();
	virtual ~CXKeyDB();

	//2022-5-10  lijunqing
	static void SetRemoveSubKeys(bool b);

	CString m_strXKeyDbFile;
	//shaolei 20220517
	long m_nMinRate;  //ƥ�����ֵ����Сƥ���

	CXKeyMngr* GetXKeyMngr()	{	return m_pXKeyMngr;	}
	CXKeyMaps* GetXKeyMaps()	{	return m_pXKeyMaps;	}

//���غ���
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXKEYDB;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXKeyDBKey();     }
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

	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
//˽�г�Ա����
private:
	DWORD *m_pdwKeyRefBuffer;
	long  m_nKeyRefCount;
	
	void InitKeyRefBuffer(CExBaseList *pList, CExBaseList *pListDst);
	void FreeKeyRefBuffer();

	CXKeyMngr *m_pXKeyMngr;
	CXKeyMaps *m_pXKeyMaps;

	long UpdateXKeyMngrByMap();
	long UpdateXKeyMngrByMap(CXMultiKeyBase *pXMultiKey);
	void InitMultiKeyArray();
	void InitMultiKeyArray(CXKeyBase *pKey);

//˽�г�Ա�������ʷ���
public:
	void OpenKeyDbFile(const CString &strFileName, BOOL bCommon);
	void OpenKeyDbFile(const CString &strFileName, const CString &strPath);
	void OpenKeyDbFile(const CString &strFilePath);
	void InsertKeyDbFile(const CString &strFilePath);
	void SaveKeyDbFile(const CString &strFile);

	void InitKeyRefBuffer();
	DWORD* GetKeyRefBuffer()		{	return m_pdwKeyRefBuffer;	}
	long   GetKeyRefBufferCount()	{	return m_nKeyRefCount;		}

	//void QueryKeys(const CString &strText, CExBaseList *pListKeys, BOOL bRemoveSub=TRUE);
	void QueryKeys(const CString &strText, CXKeyMatchRefList *pListKeys, BOOL bRemoveSub=TRUE);
	void FilterAndQueryKeys(const CString &strText, BOOL bRemoveSub=TRUE);
	CExBaseObject* FindByKeyName(const CString &strKeyName);
	CXKeyMatchRef* CreateXKeyMatchRef(const CString &strKey, long nArrayIndex);
	BOOL CreateXKeyMatchRef(const CString &strKey, long nArrayIndex, CXKeyMatchRef &oKeyMatchRef);

	//2023-2-6  lijunqing  ����strKey��Ӧ��CXKeyMatchRef
	CXKeyMatchRef* CreateXKeyMatchRef(const CString &strKey);

	void SetIdSameAsName();

private:
	BOOL  IsKeyExist(CExBaseObject *pKey, CExBaseList &oListTemp);
//	void RemoveSubKeys(CExBaseList &oListKeys);
//	void RemoveSubKeys(CXKeyMatchRefList &oListKeys,CString strText);
	void SetIdSameAsName(CExBaseList *pList);
};

CExBaseObject* XKey_GetXKey(CExBaseObject *pKey);

