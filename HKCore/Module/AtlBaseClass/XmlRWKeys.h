// XmlRWKeys.h: interface for the CXmlRWKeys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XMLRWKEYS_h__)
#define _XMLRWKEYS_h__

//XML�ļ���д�ؼ��ֶ���
//��ʽ
/*
 * <keys name="guidebook">
 *	  <key string="name" key="nm"/>
 *    <key string="name" key="id"/>
 * </keys>
 */


class CXmlRWKeys 
{
	CXmlRWKeys()
	{
		m_strNameKey = "name";
		m_strIDKey   = "id";
	}
	virtual ~CXmlRWKeys(){}

	//��XML�ڵ��ж�ȡ�ؼ���
	long ReadFromXmlFile(const CComBSTR &strFile);
	
	//��XML�ڵ��ж�ȡ�ؼ���
	virtual long ReadXml(MSXML::IXMLDOMNodePtr &oNode);  
	
public:
	CComBSTR m_strNameKey;
	CComBSTR m_strIDKey;

	static const CComBSTR g_strNameKeyString;
	static const CComBSTR g_strIDKeyString;
	
};


#endif //_XMLRWKEYS_h__