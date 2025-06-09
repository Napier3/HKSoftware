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

/*以下三个类目前只在在线录波功能当中用到*/

//写入文件的Buffer对象
class CRtFileFormatBuffer : public CExBaseObject
{
public:
	CRtFileFormatBuffer();
	virtual ~CRtFileFormatBuffer();
	
public:
	static const char* g_pszKeyRtFileFormatBuffer;
	static const char* g_pszKeyBufferID;

	CString m_strBufferID;

public:	 //重载的方法 
	virtual UINT GetClassID()          {     return RTCLASSID_FILEFORMAT_BUFFER;          }    //得到类ID
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//读自身节点
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyRtFileFormatBuffer;        };

};

/*写文件的格式,子对象是CRtFileFormatBuffer,例如<comtrade use="1">
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

public:	 //重载的方法 
	virtual UINT GetClassID()          {     return RTCLASSID_FILEFORMAT;          }
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//读自身节点
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

#ifdef AUTO_DEBUG
	virtual long WriteXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif

// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//查询对应Buffer的顺序位置
	long GetIndexByStrBufferID(CString strBufferID);

	void SetUse(long nUse)	{	m_nUse = nUse;	}
	long GetUse()			{	return m_nUse;	}

	//自适应创建RtFileMR1200
	void AutofitCreateRtFileMR1200(CRtVariables *pVariables);
	//自适应创建RtFileRecord
	void AutofitCreateRtFileRecord(CRtVariables *pVariables);
};

//写文件的格式及Buffer的管理对象
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
	long  m_nWriteFileTimeGap;//没有用到

	CRtFileFormat *m_pRtFileComtrade;//写文件的Comtrade格式的设置,目前没有用到
	CRtFileFormat *m_pRtFileMR1200;//写入文件的属性Buffer管理对象
	CRtFileFormat *m_pRtFileRecord;//写入文件的RecordBuffer管理对象

public:	 //重载的方法 
	virtual UINT GetClassID()          {     return RTCLASSID_FILEWRITE;          }
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//读自身节点
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);	
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyFileWrite;        };

public:
	//自适应创建file-write
	void AutofitCreateFileWrite(CRtVariables *pVariables);

};

#endif // !defined(AFX_RTFILEWRITE_H__AD4A7C7F_56A2_443A_B976_8EA87951DFD8__INCLUDED_)
