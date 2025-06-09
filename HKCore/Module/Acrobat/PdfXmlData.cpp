#include "StdAfx.h"
#include "PdfXmlData.h"


CPdfXmlData::CPdfXmlData(void)
{
	m_fHpos = -1;
	m_fVpos = -1;
	m_fWidth = -1;
	m_fHeight = -1;
	m_sfont = _T("");
	m_nCol = -1;
	m_bSetCol = false;
}

CPdfXmlData::~CPdfXmlData(void)
{
}


long CPdfXmlData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPdfParseXmlRWKeys *pXmlKeys = (CPdfParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strVposKey, oElement, m_fVpos);
	xml_SetAttributeValue(pXmlKeys->m_strVpos2Key, oElement, m_fVpos2);
	xml_SetAttributeValue(pXmlKeys->m_strHposKey, oElement, m_fHpos);
	xml_SetAttributeValue(pXmlKeys->m_strHpos2Key, oElement, m_fHpos2);
	xml_SetAttributeValue(pXmlKeys->m_strColKey, oElement, m_nCol);

	return 0;
}

long CPdfXmlData::ValCmp(CBaseObject* pRightObj)
{
	//先看纵坐标
	float fVpos = ((CPdfXmlData*)pRightObj)->m_fVpos;
	if(m_fVpos < fVpos)
		return -1;

	//再按横坐标
	float fHpos = ((CPdfXmlData*)pRightObj)->m_fHpos;
	if(m_fHpos < fHpos)
		return -1;
	return 1;
}
long CPdfXmlData::ValCmp(CBaseObject* pRightObj, DWORD dwAttrID)
{
	float fHpos = ((CPdfXmlData*)pRightObj)->m_fHpos;
	if(m_fHpos < fHpos)
		return -1;
	return 1;
}

void CPdfXmlData::AnalysisXmlData(CReadXmlData* pStringData, float fPageVpos)
{
	float fVPosData = 0;
	vector<BDAttr*>::iterator attr;
    for(attr=pStringData->m_vecAttri.begin(); attr!=pStringData->m_vecAttri.end(); attr++)
    {
		BDAttB attriB(*attr);
		CString strName(attriB.name());
		CString strValue(attriB.value());

		try
		{
			if(strName == _T("ID"))
				m_strID = strValue;
			else if(strName == _T("CONTENT"))
				m_strName = strValue;
			else if(strName == _T("HPOS"))
				m_fHpos = atof(strValue);
			else if(strName == _T("VPOS"))
				fVPosData = atof(strValue);	
			else if(strName == _T("WIDTH"))
				m_fWidth = atof(strValue);
			else if(strName == _T("HEIGHT"))
				m_fHeight = atof(strValue);
			else if(strName == _T("STYLEREFS"))
				m_sfont = strValue;
		}
		catch (...)
		{
		}
    }

	m_fVpos = fVPosData + fPageVpos;

	m_fHpos2 = m_fHpos + m_fWidth;
	m_fVpos2 = m_fVpos + m_fHeight;
}

float CPdfXmlData::CalWordWith()
{
	if(m_strName == _T(""))
		return 0;

	int iWordLen = m_strName.GetLength();
	if(iWordLen <= 0)
		return 0;

	return m_fWidth/iWordLen;
}

BOOL CPdfXmlData::Copy(CBaseObject* pDest)
{
	CPdfXmlData *pTwo = (CPdfXmlData *)pDest;

	m_strName = pTwo->m_strName;
	m_fHpos = pTwo->m_fHpos;
	m_fVpos = pTwo->m_fVpos;
	m_fWidth = pTwo->m_fWidth;
	m_fHeight = pTwo->m_fHeight;
	m_fHpos2 = pTwo->m_fHpos2;
	m_fVpos2 = pTwo->m_fVpos2;

	m_sfont = pTwo->m_sfont;
	m_nCol = pTwo->m_nCol;
	m_bSetCol = pTwo->m_bSetCol;
	return TRUE;
}

BOOL CPdfXmlData::AddColDataH(CBaseObject* pDest, const CString &strSP)
{
	CPdfXmlData *pTwo = (CPdfXmlData *)pDest;
	if(pTwo->m_strName == _T("序号"))
		return FALSE;

	if(pTwo->m_fHpos < m_fHpos)
	{
		m_strName = pTwo->m_strName + strSP + m_strName;
		m_fHpos = pTwo->m_fHpos;
		m_fWidth = m_fHpos2 - m_fHpos;
	}
	else
	{
		m_strName = m_strName + strSP + pTwo->m_strName;
		m_fHpos2 = pTwo->m_fHpos2;
		m_fWidth = m_fHpos2 - m_fHpos;
	}
	return TRUE;
}
void CPdfXmlData::AddColDataMaxH(CBaseObject* pDest, CExBaseObject *pSatrt)
{
	CPdfXmlData *pZero = (CPdfXmlData *)pSatrt;
	CPdfXmlData *pTwo = (CPdfXmlData *)pDest;
	m_strName += pTwo->m_strName;

	//取最大长度
	if(pTwo->m_fHpos < m_fHpos)
	{
		m_fHpos = pTwo->m_fHpos;
	}
	if(pTwo->m_fWidth > m_fWidth)
	{
		m_fWidth = pTwo->m_fWidth;
		m_fHpos2 = m_fHpos + m_fWidth;
	}

	//设置高度位置，非首列，其高度与前一列位置相同
	if(pZero != NULL)
	{
		m_fVpos = pZero->m_fVpos;
		m_fVpos2 = pZero->m_fVpos2;
	}
}
void CPdfXmlData::AddColDataV(CBaseObject* pDest)
{
	CPdfXmlData *pTwo = (CPdfXmlData *)pDest;

	//Vpos有交集且pTwo的Hpos在此Hpos内
	if(pTwo->m_fHpos2 < m_fHpos2 && !(m_fVpos > pTwo->m_fVpos2 || m_fVpos2 < pTwo->m_fVpos))	
	{
		int iWord = (pTwo->m_fHpos - m_fHpos) / pTwo->CalWordWith();
		CString strHead = m_strName.Left(iWord);
		CString strTail = m_strName.Right(m_strName.GetLength() - iWord);
		m_strName = strHead;
		m_strName += pTwo->m_strName;
		m_strName += strTail;		
	}
	else
	{
		m_strName += pTwo->m_strName;
	}

	m_fVpos2 = pTwo->m_fVpos2;
	m_fHeight = m_fVpos2 - m_fVpos;
}