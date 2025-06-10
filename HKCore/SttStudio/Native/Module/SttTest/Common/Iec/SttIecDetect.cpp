#include "SttIecDetect.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttIecDetect::m_strMacroName = "Êý×Ö±¨ÎÄÌ½²â²âÊÔ";
CString CSttIecDetect::m_strMacroID = STT_MACRO_ID_IecDetect;
CString CSttIecDetect::m_strFilePostFix = "stttst";
CString CSttIecDetect::m_strMacroVer ="1.0";

CSttIecDetect::CSttIecDetect()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttIecDetect::~CSttIecDetect()
{

}

void CSttIecDetect::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    BOOL bEnable;
	long nType = 0;
	pXmlSerialize->xml_serialize("","Enable","","long",bEnable);	

#ifdef _PSX_QT_LINUX_
	if(bEnable)
	{
		pXmlSerialize->xml_serialize("","Ft3_CRCType","","long",nType);
		CSttDeviceBase::g_pSttDeviceBase->SetFT3SubCRC(nType);
	}

	nType = 0;
	pXmlSerialize->xml_serialize("","IecType","","long",nType);
	switch(nType)
	{
	case 0://All
	case 1://SMV
	case 2://GOOSE
	case 3://FT3
		break;
	default:
		nType = 0;
	}

	CSttDeviceBase::g_pSttDeviceBase->SetIecDetect(bEnable, nType);
#endif
}
