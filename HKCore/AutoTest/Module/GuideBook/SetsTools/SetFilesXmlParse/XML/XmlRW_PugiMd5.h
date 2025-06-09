#pragma once

#ifdef XML_USE_PUGIXML

#include "../../../../../../Module/XML/XmlRW_Pugi.h"


class CXmlRWDoc_PugiMd5:public CXmlRWDoc_Pugi
{
public:
	CXmlRWDoc_PugiMd5();
	virtual ~CXmlRWDoc_PugiMd5();

	virtual BOOL xml_OpenFile(const CString &strFile);
	virtual BOOL SaveXml(const CString &strFilePath);	

public:
	static CXmlRWDocBase* CreateXmlRWDocMd5()
	{
		return new CXmlRWDoc_PugiMd5();
	}	

private:
	pugi::xml_node m_oDevice;

	void CalMd5();
	void UpdateHeader(const CString strMd5);
	CString RemoveWhitespace(const CString& input);

	void ValidateMd5();

	pugi::xml_node GetHeader();
	pugi::xml_node GetHashInfo();
	pugi::xml_node GetUpdate();
	pugi::xml_node GetevInfo();
	pugi::xml_node GetFileInfo();
	pugi::xml_node GetRemark();

	long GetSettingsCount();
	pugi::xml_node GetSettings(long nIndex);
	char* GetSettings_String(long nIndex);

	void CalSettings(pugi::xml_node ndSettings);
	void CalSettingsInfoGrp(pugi::xml_node ndInfoGrp);
	void CalSettingsInfoGrpSI(pugi::xml_node ndSI);


};

#endif XML_USE_PUGIXML
