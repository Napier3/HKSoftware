//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacrosFile.h  CTestMacrosFile

#pragma once

#include "TestMacroGlobal.h"
#include "TestMacroConfig.h"
#include "../DataMngr/DataType.h"

class CTestMacrosFile : public CExBaseList
{
public:
	CTestMacrosFile();
	virtual ~CTestMacrosFile();

protected:
	//LIJQ 2020-02-14 : ��׼�����Թ���id���ᵼ��֮ǰ��ģ���޷�ʹ�ã�����m_strOldID���ڼ���֮ǰ��ģ��
	CString m_strOldID; 

	CString  m_strFile;
	CString  m_strCmmFile;
	CString  m_strTestTypeFile;
	CString  m_strDataTypeFile;
	CString  m_strDvmFile;
	CString  m_strExpandConfigFile;

	CString  m_strActiveMacroTest;
	CString  m_strRecordProgID;
	CString  m_strDllCallFile;
	CTestMacroConfig *m_pActiveMacroTest;

public:
	//2020-01-26  
	long m_nEnable;

//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROSFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacrosFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void GetAllIecConfigFileType(CDataType *pDataType);
	CString GetActiveMacroID(const CString &strType);
	CTestMacroConfigs* FindTestMacroConfigs(const CString &strType);

public:
	CString  File(BOOL bAddPath);
	CString  CmmFile(BOOL bAddPath);
	CString  TestTypeFile(BOOL bAddPath);
	CString  DataTypeFile(BOOL bAddPath);
	CString  DvmFile(BOOL bAddPath);
	CString  ExpandConfigFile(BOOL bAddPath);
	CString  DllCallFile(BOOL bAddPath);

	CString  ActiveMacroTestID()	{	return m_strActiveMacroTest;	}
	void  ActiveMacroTestID(const CString &strData)	{	m_strActiveMacroTest = strData;	}
	CString  RecordProgID()	{	return m_strRecordProgID;	}
	CTestMacroConfig* ActiveMacroTest()	{	return m_pActiveMacroTest;	}

	CString GetTestMacroCfgFile(const CString &strFileName);

	CString    OldID()	{	return m_strOldID;	}
	CString*  P_OldID()	{	return &m_strOldID;	}
	CString*  P_File()	{	return &m_strFile;	}
	CString*  P_CmmFile()	{	return &m_strCmmFile;	}
	CString*  P_TestTypeFile()	{	return &m_strTestTypeFile;	}
	CString*  P_DataTypeFile()	{	return &m_strDataTypeFile;	}
	CString*  P_DvmFile()	{	return &m_strDvmFile;	}
	CString*  P_ExpandConfigFile()	{	return &m_strExpandConfigFile;	}
	CString* P_DllCallFile()	{	return &m_strDllCallFile;	}
	CString*  P_ActiveMacroTestID()	{	return &m_strActiveMacroTest;	}
	CString*  P_RecordProgID()	{	return &m_strRecordProgID;	}

	void CreateMacroFileFolder();
	void DeleteMacroFiles();
private:
	CString GetFileWithPath(const CString &strFile);
};

BOOL TM_IsTestMacroFile(const CString &strFile);
CString TM_GetFileWithPath(const CString &strMacroFileID, const CString &strFileName);
