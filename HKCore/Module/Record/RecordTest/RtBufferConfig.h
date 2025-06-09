// RtBufferConfig.h: interface for the CRtBufferConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTBUFFERCONFIG_H__)
#define _RTBUFFERCONFIG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordTestClassDef.h"

/*�������Ҫ���ڷ�����ֻ���Ĵ�С,��MbΪ��λ
���� max-buffer�� attr-buffer�� record-buffer�� spy-buffer�� atr-time-gap��*/
class CRtBufferConfig : public CExBaseList  
{
public:
	CRtBufferConfig();
	virtual ~CRtBufferConfig();
	
//����
public:
	//�ؼ�������
	static const char* g_pszKeyRtBuffer;
	static const char* g_pszKeyMaxBuffer;
	static const char* g_pszKeySpyBuffer;
	static const char* g_pszKeyRecordBuffer;
	static const char* g_pszKeyAttrBuffer;
	static const char* g_pszKeyAttrTimeGap;
	static const char* g_pszKeyRecordGap;

private:
	//��������
	long m_nMaxBuffer;
	long m_nSpyBuffer;
	long m_nRecordBuffer;
	long m_nAttrBuffer;
	long m_nAttrTimeGap;//û���õ�
	long m_nHDBuffer;
	long m_nRecordGap;

public:	 //���صķ��� 
	virtual UINT GetClassID()          {     return RTCLASSID_MEMBUFFER;          }    //�õ���ID
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//������ڵ�
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	long GetMaxBuffer()       {     return 1048576*m_nMaxBuffer;          }
	long GetSpyBuffer()       {     return 1048576*m_nSpyBuffer;          }
	long GetRecordBuffer()    {     return 1048576*m_nRecordBuffer;       }
	long GetAttrBuffer()      {     return 1048576*m_nAttrBuffer;         }
	long GetHDBuffer()        {     return 1048576*m_nHDBuffer;           }
	long GetRecordGap()       {     return m_nRecordGap;                  }
	void SetRecordGap(long nGap)       {     m_nRecordGap = nGap;                  }
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyRtBuffer;        };

public://��д��ֵ
// 	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
// 	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
}; 

#endif // !defined(_RTBUFFERCONFIG_H__)
