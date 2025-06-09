// XmlRWKeys.h: interface for the CXmlRWKeys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XMLRWKEYS_h__)
#define _XMLRWKEYS_h__

//XML文件读写关键字定义
//格式
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

	//从XML节点中读取关键字
	long ReadFromXmlFile(const CComBSTR &strFile);
	
	//从XML节点中读取关键字
	virtual long ReadXml(MSXML::IXMLDOMNodePtr &oNode);  
	
public:
	CComBSTR m_strNameKey;
	CComBSTR m_strIDKey;

	static const CComBSTR g_strNameKeyString;
	static const CComBSTR g_strIDKeyString;
	
};


#endif //_XMLRWKEYS_h__