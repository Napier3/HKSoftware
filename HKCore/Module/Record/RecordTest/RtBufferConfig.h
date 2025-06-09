// RtBufferConfig.h: interface for the CRtBufferConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTBUFFERCONFIG_H__)
#define _RTBUFFERCONFIG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordTestClassDef.h"

/*这个类主要用于分配各种缓存的大小,以Mb为单位
包括 max-buffer、 attr-buffer、 record-buffer、 spy-buffer、 atr-time-gap、*/
class CRtBufferConfig : public CExBaseList  
{
public:
	CRtBufferConfig();
	virtual ~CRtBufferConfig();
	
//属性
public:
	//关键字属性
	static const char* g_pszKeyRtBuffer;
	static const char* g_pszKeyMaxBuffer;
	static const char* g_pszKeySpyBuffer;
	static const char* g_pszKeyRecordBuffer;
	static const char* g_pszKeyAttrBuffer;
	static const char* g_pszKeyAttrTimeGap;
	static const char* g_pszKeyRecordGap;

private:
	//配置属性
	long m_nMaxBuffer;
	long m_nSpyBuffer;
	long m_nRecordBuffer;
	long m_nAttrBuffer;
	long m_nAttrTimeGap;//没有用到
	long m_nHDBuffer;
	long m_nRecordGap;

public:	 //重载的方法 
	virtual UINT GetClassID()          {     return RTCLASSID_MEMBUFFER;          }    //得到类ID
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//读自身节点
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	long GetMaxBuffer()       {     return 1048576*m_nMaxBuffer;          }
	long GetSpyBuffer()       {     return 1048576*m_nSpyBuffer;          }
	long GetRecordBuffer()    {     return 1048576*m_nRecordBuffer;       }
	long GetAttrBuffer()      {     return 1048576*m_nAttrBuffer;         }
	long GetHDBuffer()        {     return 1048576*m_nHDBuffer;           }
	long GetRecordGap()       {     return m_nRecordGap;                  }
	void SetRecordGap(long nGap)       {     m_nRecordGap = nGap;                  }
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyRtBuffer;        };

public://读写定值
// 	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
// 	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
}; 

#endif // !defined(_RTBUFFERCONFIG_H__)
