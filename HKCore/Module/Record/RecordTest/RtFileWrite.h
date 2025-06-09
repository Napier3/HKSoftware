// RtFileWrite.h: interface for the CRtFileWrite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTFILEWRITE_H__AD4A7C7F_56A2_443A_B976_8EA87951DFD8__INCLUDED_)
#define AFX_RTFILEWRITE_H__AD4A7C7F_56A2_443A_B976_8EA87951DFD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MODULE/BASECLASS/ExBaseList.h"
#include "RecordTestClassDef.h"

#define RTFILEWRITE_MODE_NONE      0
#define RTFILEWRITE_MODE_BUFFER    1
#define RTFILEWRITE_MODE_TIME      2
class CRtVariables;

/*����������Ŀǰֻ������¼�����ܵ����õ�*/

//д���ļ���Buffer����
class CRtFileFormatBuffer : public CExBaseObject
{
public:
	CRtFileFormatBuffer();
	virtual ~CRtFileFormatBuffer();
	
public:
	static const char* g_pszKeyRtFileFormatBuffer;
	static const char* g_pszKeyBufferID;

	CString m_strBufferID;

public:	 //���صķ��� 
	virtual UINT GetClassID()          {     return RTCLASSID_FILEFORMAT_BUFFER;          }    //�õ���ID
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//������ڵ�
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyRtFileFormatBuffer;        };

};

/*д�ļ��ĸ�ʽ,�Ӷ�����CRtFileFormatBuffer,����<comtrade use="1">
												<buffer buf-id="1" /> 
											   </comtrade>        */
class CRtFileFormat : public CExBaseList 
{
public:
	CRtFileFormat();
	virtual ~CRtFileFormat();

public:
	static const char* g_pszKeyRtFileFormat_Comtrade;
	static const char* g_pszKeyRtFileFormat_MR1200;
	static const char* g_pszKeyRtFileFormat_Record;
	static const char* g_pszKeyUse;

	long  m_nUse;

public:	 //���صķ��� 
	virtual UINT GetClassID()          {     return RTCLASSID_FILEFORMAT;          }
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//������ڵ�
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

#ifdef AUTO_DEBUG
	virtual long WriteXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif

// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//��ѯ��ӦBuffer��˳��λ��
	long GetIndexByStrBufferID(CString strBufferID);

	void SetUse(long nUse)	{	m_nUse = nUse;	}
	long GetUse()			{	return m_nUse;	}

	//����Ӧ����RtFileMR1200
	void AutofitCreateRtFileMR1200(CRtVariables *pVariables);
	//����Ӧ����RtFileRecord
	void AutofitCreateRtFileRecord(CRtVariables *pVariables);
};

//д�ļ��ĸ�ʽ��Buffer�Ĺ������
class CRtFileWrite : public CExBaseList
{
public:
	CRtFileWrite();
	virtual ~CRtFileWrite();

public:
	static const char* g_pszKeyFileWrite;
	static const char* g_pszKeyWriteFileMode;      //write-file-mode time/buffer/none
	static const char* g_pszKeyWriteFileTimeGap;   //write-file-time-gap
	static const char* g_pszKeyWriteFileMode_Time;
	static const char* g_pszKeyWriteFileMode_Buffer;
	static const char* g_pszKeyWriteFileMode_None;

	long  m_nWriteFileMode;
	long  m_nWriteFileTimeGap;//û���õ�

	CRtFileFormat *m_pRtFileComtrade;//д�ļ���Comtrade��ʽ������,Ŀǰû���õ�
	CRtFileFormat *m_pRtFileMR1200;//д���ļ�������Buffer�������
	CRtFileFormat *m_pRtFileRecord;//д���ļ���RecordBuffer�������

public:	 //���صķ��� 
	virtual UINT GetClassID()          {     return RTCLASSID_FILEWRITE;          }
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//������ڵ�
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);	
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyFileWrite;        };

public:
	//����Ӧ����file-write
	void AutofitCreateFileWrite(CRtVariables *pVariables);

};

#endif // !defined(AFX_RTFILEWRITE_H__AD4A7C7F_56A2_443A_B976_8EA87951DFD8__INCLUDED_)
