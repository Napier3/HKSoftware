// IEDGSSVInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SclIecCfgDatas.h"

#include "../../Iec61850Config/XLanguageResourceIec_61850Cfg.h"
#include "../../../Module/API/GlobalConfigApi.h"
#ifdef _PSX_QT_LINUX_
#include"../../../Module/API/StringConvertApi.h"
#endif

#ifdef USE_WAITINGTIMEDLG_FOR_SCLCOMPARECHECK
#include "../../../SCLCompareCheck/Module/SclCheck/WaitingTimeDlg.h"
#endif
// BOOL g_pIedFile_Abstract=0;

//////////////////////////////////////////////////////////通道信息/////////////////////////////////////////////////////////////////////////////////////
//CSclChBase
CSclChBase::CSclChBase()
{
	m_pCfgDataRef = NULL;
}

CSclChBase::~CSclChBase()
{

}

long CSclChBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_name, oElement, fcda_name );

// 	xml_SetAttributeValue(pXmlKeys->m_strKey_inLNDesc, oElement, inLNDesc );
// 	xml_SetAttributeValue(pXmlKeys->m_strKey_inDODesc, oElement, inDODesc );
// 	xml_SetAttributeValue(pXmlKeys->m_strKey_inDADesc, oElement, inDADesc );
	return 0;
}

long CSclChBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc, oNode,  fcda_dodesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_name, oNode, fcda_name );

// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_inLNDesc, oNode, inLNDesc );
// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDODesc, oNode, inDODesc );
// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDADesc, oNode, inDADesc );
	return 0;
}


BOOL CSclChBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclChSmv *p = (CSclChSmv*)pDest;

	p->fcda_lndesc = fcda_lndesc;
	p->fcda_dodesc = fcda_dodesc;
	p->fcda_desc = fcda_desc;
	p->fcda_name = fcda_name;		

	return TRUE;
}

CString* CSclChBase::GetName()
{
	if (fcda_desc.GetLength() > 0)
	{
		return &fcda_desc;
	}

	if (fcda_dodesc.GetLength() > 0)
	{
		return &fcda_dodesc;
	}

	return &fcda_name;
}

//////////////////////////////////////////////////////////////////////////
//
CSclChSmv::CSclChSmv()
{

}

CSclChSmv::~CSclChSmv()
{

}

long CSclChSmv::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcdaName, oElement, fcda_name );

// 	xml_SetAttributeValue(pXmlKeys->m_strKey_inLNDesc, oElement, inLNDesc );
// 	xml_SetAttributeValue(pXmlKeys->m_strKey_inDODesc, oElement, inDODesc );
// 	xml_SetAttributeValue(pXmlKeys->m_strKey_inDADesc, oElement, inDADesc );

	xml_SetAttributeValue(pXmlKeys->m_strCDOTypeKey, oElement, fcda_DOType );
	xml_SetAttributeValue(pXmlKeys->m_strCDCKey, oElement, fcda_cdc );
	return 0;
}

long CSclChSmv::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclChBase::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc, oNode,  fcda_dodesc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcdaName, oNode, fcda_name );

// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_inLNDesc, oNode, inLNDesc );
// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDODesc, oNode, inDODesc );
// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDADesc, oNode, inDADesc );

	xml_GetAttibuteValue(pXmlKeys->m_strCDOTypeKey, oNode, fcda_DOType );
	xml_GetAttibuteValue(pXmlKeys->m_strCDCKey, oNode, fcda_cdc );


	return 0;
}


BOOL CSclChSmv::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclChBase::CopyOwn(pDest);

	CSclChSmv *p = (CSclChSmv*)pDest;

	// 	p->fcda_lndesc = fcda_lndesc;
	// 	p->fcda_dodesc = fcda_dodesc;
	// 	p->fcda_desc = fcda_desc;
	// 	p->fcda_name = fcda_name;		

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//CSclChSmvOut
CSclChSmvOut::CSclChSmvOut()
{

}

CSclChSmvOut::~CSclChSmvOut()
{

}

long CSclChSmvOut::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclChSmv::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcdaName, oElement, fcda_name );

	return 0;
}

long CSclChSmvOut::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclChSmv::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc, oNode,  fcda_dodesc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcdaName, oNode, fcda_name );



	return 0;
}


BOOL CSclChSmvOut::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclChSmv::CopyOwn(pDest);

	CSclChSmvOut *p = (CSclChSmvOut*)pDest;

	// 	p->fcda_lndesc = fcda_lndesc;
	// 	p->fcda_dodesc = fcda_dodesc;
	// 	p->fcda_desc = fcda_desc;
	// 	p->fcda_name = fcda_name;		

	return TRUE;
}

CBaseObject* CSclChSmvOut::Clone()
{
	CSclChGsOut *p = new CSclChGsOut();
	Copy(p);
	return p;
}


//////////////////////////////////////////////////////////////////////////

//CSclChSmvIn
CSclChSmvIn::CSclChSmvIn()
{
	inIndex = 0;
	outIndex = 0;
}

CSclChSmvIn::~CSclChSmvIn()
{

}


long CSclChSmvIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclChSmv::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_outPath, oElement,  fcda_name);
	xml_SetAttributeValue(pXmlKeys->m_strKey_inIndex, oElement,inIndex );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inLNDesc, oElement, inLNDesc );	
	xml_SetAttributeValue(pXmlKeys->m_strKey_inDODesc, oElement,  inDODesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inDADesc, oElement,inDADesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_outIndex, oElement, outIndex );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inPath, oElement, inPath );

	xml_SetAttributeValue(pXmlKeys->m_strKey_inputRef_cdc, oElement, inputRef_cdc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inputRef_type, oElement, inputRef_DOType );
	return 0;
}

long CSclChSmvIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclChSmv::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc, oNode,  fcda_dodesc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_outPath, oNode,  fcda_name);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inIndex, oNode,inIndex );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inLNDesc, oNode, inLNDesc );	
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDODesc, oNode,  inDODesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDADesc, oNode,inDADesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_outIndex, oNode, outIndex );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inPath, oNode, inPath );



	return 0;
}


BOOL CSclChSmvIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclChSmv::CopyOwn(pDest);

	CSclChSmvIn *p = (CSclChSmvIn*)pDest;

	// 	p->fcda_lndesc = fcda_lndesc;
	// 	p->fcda_dodesc = fcda_dodesc;
	// 	p->fcda_desc = fcda_desc;
	// 	p->fcda_name = fcda_name;		

	p->outIndex = outIndex;
	p->inLNDesc = inLNDesc;
	p->inDODesc = inDODesc;
	p->inDADesc = inDADesc;
	p->inIndex = inIndex;
	p->inPath = inPath;

	return TRUE;
}

CBaseObject* CSclChSmvIn::Clone()
{
	CSclChSmvIn *p = new CSclChSmvIn();
	Copy(p);
	return p;
}

CString* CSclChSmvIn::GetName()
{
	if (inDADesc.GetLength() > 0)
	{
		return &inDADesc;
	}

	if (inDODesc.GetLength() > 0)
	{
		return &inDODesc;
	}


	return CSclChSmv::GetName();
}

//////////////////////////////////////////////////////////////////////////
//
CSclChGs::CSclChGs()
{

}

CSclChGs::~CSclChGs()
{

}


long CSclChGs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_type, oElement,  fcda_type);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcdaName, oElement,  fcda_name );

	return 0;
}

long CSclChGs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclChBase::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_type, oNode,  fcda_type);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc,oNode,  fcda_dodesc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcdaName, oNode,  fcda_name );

	return 0;
}



BOOL CSclChGs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclChBase::CopyOwn(pDest);

	CSclChGs *p = (CSclChGs*)pDest;

	// 	p->fcda_lndesc = fcda_lndesc;
	// 	p->fcda_dodesc = fcda_dodesc;
	// 	p->fcda_desc = fcda_desc;
	// 	p->fcda_name = fcda_name;		
	p->fcda_type = fcda_type;		

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

//CSclChGsOut
CSclChGsOut::CSclChGsOut()
{
	m_astrGinChs.RemoveAll();
}

CSclChGsOut::~CSclChGsOut()
{
	m_oChInRefs.RemoveAll();
}

long CSclChGsOut::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclChGs::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strKey_GinPath, oElement,  m_strGinPath);

	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_type, oElement,  fcda_type);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcdaName, oElement,  fcda_name );

	return 0;
}

long CSclChGsOut::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclChGs::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strKey_GinPath, oNode,  m_strGinPath);

	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_type, oNode,  fcda_type);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc,oNode,  fcda_dodesc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcdaName, oNode,  fcda_name );



	return 0;
}



BOOL CSclChGsOut::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclChGs::CopyOwn(pDest);

	CSclChGsOut *p = (CSclChGsOut*)pDest;

	// 	p->fcda_lndesc = fcda_lndesc;
	// 	p->fcda_dodesc = fcda_dodesc;
	// 	p->fcda_desc = fcda_desc;
	// 	p->fcda_name = fcda_name;		
	// 	p->fcda_type = fcda_type;		

	return TRUE;
}

CBaseObject* CSclChGsOut::Clone()
{
	CSclChGsOut *p = new CSclChGsOut();
	Copy(p);
	return p;
}


//////////////////////////////////////////////////////////////////////////

//CSclChGsIn
CSclChGsIn::CSclChGsIn()
{
	inIndex = 0;
	outIndex = 0;
}

CSclChGsIn::~CSclChGsIn()
{

}

long CSclChGsIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSclChGs::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_type, oElement,  fcda_type);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_lndesc, oElement,  fcda_lndesc);
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_dodesc, oElement,  fcda_dodesc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_desc, oElement, fcda_desc );
	// 	xml_SetAttributeValue(pXmlKeys->m_strKey_outPath, oElement,  fcda_name);
	xml_SetAttributeValue(pXmlKeys->m_strKey_fcda_map, oElement, fcda_map );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inIndex, oElement,inIndex );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inLNDesc, oElement, inLNDesc );	
	xml_SetAttributeValue(pXmlKeys->m_strKey_inDODesc, oElement,  inDODesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inDADesc, oElement,inDADesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_outIndex, oElement, outIndex );
	xml_SetAttributeValue(pXmlKeys->m_strKey_inPath, oElement, inPath );

	xml_SetAttributeValue(pXmlKeys->m_strKey_inputRef_type, oElement, inputRef_type );

	return 0;
}

long CSclChGsIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclChGs::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_type, oNode,  fcda_type);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_lndesc, oNode,  fcda_lndesc);
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_dodesc, oNode,  fcda_dodesc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_desc, oNode, fcda_desc );
	// 	xml_GetAttibuteValue(pXmlKeys->m_strKey_outPath, oNode,  fcda_name);

	xml_GetAttibuteValue(pXmlKeys->m_strKey_fcda_map, oNode, fcda_map );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inIndex, oNode,inIndex );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inLNDesc, oNode, inLNDesc );	
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDODesc, oNode,  inDODesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inDADesc, oNode,inDADesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_outIndex, oNode, outIndex );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_inPath, oNode, inPath );

	xml_GetAttibuteValue(pXmlKeys->m_strKey_inputRef_type, oNode, inputRef_type );


	return 0;
}


BOOL CSclChGsIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclChGs::CopyOwn(pDest);

	CSclChGsIn *p = (CSclChGsIn*)pDest;

	// 	p->fcda_type = fcda_type;
	// 	p->fcda_lndesc = fcda_lndesc;
	// 	p->fcda_dodesc = fcda_dodesc;
	// 	p->fcda_desc = fcda_desc;
	// 	p->fcda_name = fcda_name;		

	p->outIndex = outIndex;

	p->fcda_map = fcda_map;
	p->inLNDesc = inLNDesc;
	p->inDODesc = inDODesc;
	p->inDADesc = inDADesc;
	p->inIndex = inIndex;
	p->inPath = inPath;

	return TRUE;
}

CBaseObject* CSclChGsIn::Clone()
{
	CSclChGsIn *p = new CSclChGsIn();
	Copy(p);
	return p;
}


////////////////////////////////////////////////////SMV、GOOSE信息//////////////////////////////////////////////////////////////////////////////
//CSclCtrlBase
CSclCtrlBase::CSclCtrlBase()
{
	m_nSelect = 0;
	m_nChnCount = 0;
	m_pCfgDataRef = NULL;
	m_bSaveCBChs = TRUE;
	m_nFiberIndex = 0;
}

CSclCtrlBase::~CSclCtrlBase()
{

}

CString CSclCtrlBase::GetIedString()
{
	CSclIed *pIed = (CSclIed*)GetAncestor(SCLIECCLASSID_IED);
	ASSERT(pIed != NULL);

	return pIed->m_strID;
}

void CSclCtrlBase::SetSaveCBChs(BOOL bSaveChs)
{
	m_bSaveCBChs = bSaveChs;
}

long CSclCtrlBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_SetAttributeValue(pXmlKeys->m_strKey_m_nSelect, oElement, m_nSelect );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_datset, oElement,m_strDataSet );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_datset_path, oElement,  m_strDataSet );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_dataset_desc, oElement, m_strDataSetDesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_apName, oElement, apName );
	xml_SetAttributeValue(pXmlKeys->m_strKey_strMac, oElement,  m_strMac );
	xml_SetAttributeValue(pXmlKeys->m_strKey_m_nChnCount, oElement,m_nChnCount);

	xml_SetAttributeValue(pXmlKeys->m_strKey_LDdesc, oElement, m_strLDdesc );
	return 0;
}

long  CSclCtrlBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	//Ctrlbase
	xml_GetAttibuteValue(pXmlKeys->m_strKey_m_nSelect, oNode, m_nSelect );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_datset, oNode,m_strDataSet );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_datset_path, oNode,  m_strDataSet );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_dataset_desc, oNode, m_strDataSetDesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_apName, oNode, apName );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_strMac, oNode,  m_strMac );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_m_nChnCount, oNode,m_nChnCount);

	xml_GetAttibuteValue(pXmlKeys->m_strKey_LDdesc, oNode,m_strLDdesc);
	return 0;
}

long CSclCtrlBase::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (!m_bSaveCBChs)
	{
		return 0;
	}

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);	
}

BOOL CSclCtrlBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

	CSclCtrlBase *p = (CSclCtrlBase*)pDest;

	p->m_nSelect = m_nSelect;
	p->ldName = ldName;
	p->lnName = lnName;
	p->m_strDataSet = m_strDataSet;
	p->m_strDataSetPath = m_strDataSetPath;
	p->m_strDataSetDesc = m_strDataSetDesc;
	p->apName = apName;
	p->m_strMac = m_strMac;
	p->m_nChnCount = m_nChnCount;

	return TRUE;
}


CSclChBase* CSclCtrlBase::FindBy_fcda_name(const CString &fcda_name)
{
	CSclChBase *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclChBase *)GetNext(pos);

		if (p->fcda_name == fcda_name)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


//////////////////////////////////////////////////////////////////////////


//CSclCtrlSmv
CSclCtrlSmv::CSclCtrlSmv()
{
	scl_svcb_smpRate = 0;
	scl_svcb_nofASDU = 0;
	scl_svcb_confRev = 0;
	m_dwAppID = 0;
	scl_smv_VLANID = 0;
	scl_smv_VLANPRI = 0;
}

CSclCtrlSmv::~CSclCtrlSmv()
{

}

long CSclCtrlSmv::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCtrlBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_svcb_smpRate, oElement, scl_svcb_smpRate );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_svcb_smvID, oElement, m_strSVID);
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_svcb_nofASDU, oElement,  scl_svcb_nofASDU);
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_svcb_confRev, oElement,scl_svcb_confRev );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_smv_APPID, oElement,  m_dwAppID );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_smv_VLANID, oElement,  scl_smv_VLANID );
//	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_smv_VLANID, oElement, scl_smv_VLANID );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_smv_VLANPRI, oElement,  scl_smv_VLANPRI );

	return 0;
}

long CSclCtrlSmv::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCtrlBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_svcb_smpRate, oNode, scl_svcb_smpRate );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_svcb_smvID, oNode, m_strSVID);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_svcb_nofASDU, oNode,  scl_svcb_nofASDU);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_svcb_confRev, oNode,scl_svcb_confRev );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_smv_APPID, oNode,  m_dwAppID );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_smv_VLANID, oNode,  scl_smv_VLANID );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_smv_VLANPRI, oNode,  scl_smv_VLANPRI );

	return 0;
}


BOOL CSclCtrlSmv::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrlBase::CopyOwn(pDest);

	CSclCtrlSmv *p = (CSclCtrlSmv*)pDest;

	p->scl_svcb_smpRate = scl_svcb_smpRate;
	p->m_strSVID = m_strSVID;
	p->scl_svcb_nofASDU = scl_svcb_nofASDU;
	p->scl_svcb_confRev = scl_svcb_confRev;
	p->m_dwAppID = m_dwAppID;
	p->scl_smv_VLANID = scl_smv_VLANID;
	p->scl_smv_VLANPRI = scl_smv_VLANPRI;

	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
//CSclCtrlSmvOut
CSclCtrlSmvOut::CSclCtrlSmvOut()
{
	m_bInitChInRefs = FALSE;
}

CSclCtrlSmvOut::~CSclCtrlSmvOut()
{

}


CExBaseObject* CSclCtrlSmvOut::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclSvOutChKey)
	{
		pNew = new CSclChSmvOut();
	}

	return pNew;
}

long CSclCtrlSmvOut::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	CSclCtrlSmv::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclCtrlSmvOut::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCtrlSmv::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}


BOOL CSclCtrlSmvOut::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrlSmv::CopyOwn(pDest);

	CSclCtrlSmvOut *p = (CSclCtrlSmvOut*)pDest;


	return TRUE;
}

CBaseObject* CSclCtrlSmvOut::Clone()
{
	CSclCtrlSmvOut *p = new CSclCtrlSmvOut();
	Copy(p);
	return p;
}

//////////////////////////////////////////////////////////////////////////
//CSclCtrlSmvIn
CSclCtrlSmvIn::CSclCtrlSmvIn()
{
	m_nChnRefCount = 0;
}

CSclCtrlSmvIn::~CSclCtrlSmvIn()
{

}

CExBaseObject* CSclCtrlSmvIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclSvInChKey)
	{
		pNew = new CSclChSmvIn();
	}

	return pNew;
}

long CSclCtrlSmvIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	CSclCtrlSmv::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKey_iedStr, oElement,  iedStr );
	xml_SetAttributeValue(pXmlKeys->m_strKey_iedExtName, oElement,  iedExtName);
	xml_SetAttributeValue(pXmlKeys->m_strKey_apName_own, oElement,  apName_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_ldName_own, oElement,  ldName_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_lnName_own, oElement,  lnName_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_datset_own, oElement,  scl_datset_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_nChnRefCount, oElement,  m_nChnRefCount);

	xml_SetAttributeValue(pXmlKeys->m_strKey_ExLDdesc, oElement,  m_strExLDdesc);
	xml_SetAttributeValue(pXmlKeys->m_strKey_ExIedDesc, oElement,  m_strExIedDesc);

	return 0;
}

long CSclCtrlSmvIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCtrlSmv::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strKey_iedStr, oNode,  iedStr );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_iedExtName, oNode,  iedExtName);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_apName_own, oNode,  apName_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_ldName_own, oNode,  ldName_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_lnName_own, oNode,  lnName_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_datset_own, oNode,  scl_datset_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_nChnRefCount, oNode,  m_nChnRefCount);

	xml_GetAttibuteValue(pXmlKeys->m_strKey_ExLDdesc, oNode,  m_strExLDdesc);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_ExIedDesc, oNode,  m_strExIedDesc);

	return 0;
}


BOOL CSclCtrlSmvIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrlSmv::CopyOwn(pDest);

	CSclCtrlSmvIn *p = (CSclCtrlSmvIn*)pDest;

	p->iedStr = iedStr;
	p->iedExtName = iedExtName;

	p->ldName_own = ldName_own;
	p->lnName_own = lnName_own;
	p->scl_datset_own = scl_datset_own;
	p->apName_own = apName_own;
	p->m_nChnRefCount = m_nChnRefCount;

	return TRUE;
}

CBaseObject* CSclCtrlSmvIn::Clone()
{
	CSclCtrlSmvIn *p = new CSclCtrlSmvIn();
	Copy(p);
	return p;
}



//////////////////////////////////////////////////////////////////////////
//CSclCtrlGs
CSclCtrlGs::CSclCtrlGs()
{
	m_dwVersion = 0;
	m_dwAppID = 0;
	m_dwVLandID = 0;
	m_dwVLandPriority = 0;
	scl_gse_MinTime = 0;
	scl_gse_MaxTime = 0;
}

CSclCtrlGs::~CSclCtrlGs()
{

}

long CSclCtrlGs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCtrlBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKey_gocbref, oElement, gocbref );
	xml_SetAttributeValue(pXmlKeys->m_strKey_gocbref_path, oElement, m_strgocbRef);
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gcb_confRev, oElement,  m_dwVersion);
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gcb_APPID, oElement,m_strGooseId );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gse_APPID, oElement,  m_dwAppID );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gse_VLANID, oElement,  m_dwVLandID );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gse_VLANPRI, oElement, m_dwVLandPriority );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gse_MinTime, oElement,  scl_gse_MinTime );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_gse_MaxTime, oElement, scl_gse_MaxTime );	

	return 0;
}

long CSclCtrlGs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCtrlBase::XmlReadOwn(oNode, pXmlRWKeys);


	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;



	//Gs
	xml_GetAttibuteValue(pXmlKeys->m_strKey_gocbref, oNode, gocbref );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_gocbref_path, oNode, m_strgocbRef);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gcb_confRev, oNode,  m_dwVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gcb_APPID, oNode,m_strGooseId );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gse_APPID, oNode,  m_dwAppID );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gse_VLANID, oNode,  m_dwVLandID );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gse_VLANPRI, oNode, m_dwVLandPriority );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gse_MinTime, oNode,  scl_gse_MinTime );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_gse_MaxTime, oNode, scl_gse_MaxTime );


	return 0;
}



BOOL CSclCtrlGs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrlBase::CopyOwn(pDest);

	CSclCtrlGs *p = (CSclCtrlGs*)pDest;

	p->gocbref = gocbref;
	p->m_strgocbRef = m_strgocbRef;
	p->m_dwVersion = m_dwVersion;
	p->m_strGooseId = m_strGooseId;
	p->m_dwAppID = m_dwAppID;
	p->m_dwVLandID = m_dwVLandID;
	p->m_dwVLandPriority = m_dwVLandPriority;
	p->scl_gse_MinTime = scl_gse_MinTime;
	p->scl_gse_MaxTime = scl_gse_MaxTime;

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//CSclCtrlGsIn
CSclCtrlGsIn::CSclCtrlGsIn()
{
	m_nChnRefCount = 0;
}

CSclCtrlGsIn::~CSclCtrlGsIn()
{

}

long CSclCtrlGsIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCtrlGs::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKey_iedStr, oElement,  m_strIedDesc );
	xml_SetAttributeValue(pXmlKeys->m_strKey_iedExtName, oElement,  m_strIedID);
	xml_SetAttributeValue(pXmlKeys->m_strKey_apName_own, oElement,  apName_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_ldName_own, oElement,  ldName_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_lnName_own, oElement,  lnName_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_scl_datset_own, oElement,  scl_datset_own );
	xml_SetAttributeValue(pXmlKeys->m_strKey_nChnRefCount, oElement,  m_nChnRefCount);

	xml_SetAttributeValue(pXmlKeys->m_strKey_ExLDdesc, oElement,  m_strExLDdesc);
	xml_SetAttributeValue(pXmlKeys->m_strKey_ExIedDesc, oElement,  m_strExIedDesc);

	return 0;
}


CExBaseObject* CSclCtrlGsIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclGsInChKey)
	{
		pNew = new CSclChGsIn();
	}

	return pNew;
}

long CSclCtrlGsIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSclCtrlGs::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	//GsIn
	xml_GetAttibuteValue(pXmlKeys->m_strKey_iedStr, oNode,  m_strIedDesc );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_iedExtName, oNode,  m_strIedID);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_apName_own, oNode,  apName_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_ldName_own, oNode,  ldName_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_lnName_own, oNode,  lnName_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_scl_datset_own, oNode,  scl_datset_own );
	xml_GetAttibuteValue(pXmlKeys->m_strKey_nChnRefCount, oNode,  m_nChnRefCount);

	xml_GetAttibuteValue(pXmlKeys->m_strKey_ExLDdesc, oNode,  m_strExLDdesc);
	xml_GetAttibuteValue(pXmlKeys->m_strKey_ExIedDesc, oNode,  m_strExIedDesc);
	return 0;
}


BOOL CSclCtrlGsIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrlGs::CopyOwn(pDest);

	CSclCtrlGsIn *p = (CSclCtrlGsIn*)pDest;

	p->m_strIedDesc = m_strIedDesc;
	p->m_strIedID = m_strIedID;
	p->m_nChnRefCount = m_nChnRefCount;

	p->ldName_own = ldName_own;
	p->lnName_own = lnName_own;
	p->scl_datset_own = scl_datset_own;
	p->apName_own = apName_own;

	return TRUE;
}

CBaseObject* CSclCtrlGsIn::Clone()
{
	CSclCtrlGsIn *p = new CSclCtrlGsIn();
	Copy(p);
	return p;
}

CSclChGsIn* CSclCtrlGsIn::FindByInPath(const CString &strPath)
{
	CSclChGsIn *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclChGsIn *)GetNext(pos);

		if (p->inPath == strPath)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
//CSclCtrlGsOut
CSclCtrlGsOut::CSclCtrlGsOut()
{
	m_bInitChInRefs = FALSE;
}

CSclCtrlGsOut::~CSclCtrlGsOut()
{

}

long CSclCtrlGsOut::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSclCtrlGs::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}


CExBaseObject* CSclCtrlGsOut::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSclGsOutChKey)
	{
		pNew = new CSclChGsOut();
	}

	return pNew;
}

long CSclCtrlGsOut::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CSclCtrlGs::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}

BOOL CSclCtrlGsOut::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrlGs::CopyOwn(pDest);

	CSclCtrlGsOut *p = (CSclCtrlGsOut*)pDest;

	return TRUE;
}

CBaseObject* CSclCtrlGsOut::Clone()
{
	CSclCtrlGsOut *p = new CSclCtrlGsOut();
	Copy(p);
	return p;
}



//////////////////////////////////////////////////////////////////////////
//CSclCtrls
CSclCtrls::CSclCtrls()
{
	m_bRead = FALSE;
}

CSclCtrls::~CSclCtrls()
{

}

BOOL CSclCtrls::IsRead()
{
	return m_bRead;
}

void CSclCtrls::SetRead()
{
	m_bRead = TRUE;
}

void CSclCtrls::SetNoRead()
{
	m_bRead = FALSE;
}

CSclCtrlBase* CSclCtrls::CreateCtrl()
{
	ASSERT( FALSE );
	return NULL;
}

BOOL CSclCtrls::IsExist(const CString &iedName, const CString &ldName, const CString &lnName, const CString &scl_datSet)
{
	CSclCtrlBase *pFind = NULL;
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);

		if ((p->ldName == ldName) && (p->lnName == lnName)  && (p->m_strDataSet == scl_datSet))
		{
			pFind = p;
			break;
		}
	}

	return (pFind != NULL);
}

void CSclCtrls::GetAllSelectedDatas(CExBaseList &oList)
{
	CSclCtrlBase *pFind = NULL;
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);

		if (p->m_nSelect != 0)
		{
			oList.AddTail(p);
		}
	}
}

long CSclCtrls::GetCurSelCB_Num()
{
	long nSelNum = 0;
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);

		if (p->m_nSelect != 0)
		{
			nSelNum++;
		}
	}

	return nSelNum;
}

void CSclCtrls::SetAllItemData(DWORD dwValue)
{
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);
		p->m_dwItemData = dwValue;
	}
}

void CSclCtrls::SetSelectAll(BOOL bSelected)
{
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);
		p->m_nSelect = bSelected;
	}
}

BOOL CSclCtrls::IsAllSelected()
{
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);

		if (p->m_nSelect == 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CSclCtrls::SetSaveCBChs(BOOL bSaveChs)
{
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);
		p->SetSaveCBChs(bSaveChs);
	}
}


BOOL CSclCtrls::SetSelectNum(long nNum)
{
	long nCurSelNum = GetCurSelCB_Num();

	if (nCurSelNum>=nNum)
	{
		return TRUE;
	}

	long nNeedCount = nNum-nCurSelNum;
	long nIndex = 0;
	CSclCtrlBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlBase *)GetNext(pos);

		if (p->m_nSelect == 0)
		{
			p->m_nSelect = 1;
			nIndex++;

			if (nIndex>=nNeedCount)
			{
				return TRUE;
			}
		}
		
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//CSclCtrlsSmvOut
CSclCtrlsSmvOut::CSclCtrlsSmvOut()
{
	m_strName = _T("SMV Outputs");
	m_strID = m_strName;
}

CSclCtrlsSmvOut::~CSclCtrlsSmvOut()
{

}

CSclCtrlSmvOut* CSclCtrlsSmvOut::FindCrl_SmvOutput(const CString &strSvID)
{
	CSclCtrlSmvOut *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlSmvOut *)GetNext(pos);

		if (p->m_strSVID == strSvID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CSclCtrlBase* CSclCtrlsSmvOut::FindSclCtrlByAppID(DWORD dwAppID)
{
	CSclCtrlSmvOut *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlSmvOut *)GetNext(pos);

		if (p->m_dwAppID == dwAppID)
		{
			return p;
		}
	}

	return NULL;
}

CSclCtrlBase* CSclCtrlsSmvOut::FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac)
{
	CSclCtrlSmvOut *p = NULL;
	POS pos = GetHeadPosition();
	DWORD nAppID = 0;
	HexToDWORD(strAppID,nAppID);

	while (pos != NULL)
	{
		p = (CSclCtrlSmvOut *)GetNext(pos);

		if (strDesMac.IsEmpty())
		{
			if ((p->m_dwAppID == nAppID))
			{
				return p;
			}
		} 
		else
		{
			if ((p->m_dwAppID == nAppID)&&(p->m_strMac == strDesMac))
			{
				return p;
			}
		}
	}

	return NULL;
}

long CSclCtrlsSmvOut::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclCtrlsSmvOut::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	SetRead();

	return 0;
}


CExBaseObject* CSclCtrlsSmvOut::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{

	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSclCtrlSvOutKey)
	{
		pNew = new CSclCtrlSmvOut();
		return pNew;
	}
	return pNew;

}


BOOL CSclCtrlsSmvOut::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrls::CopyOwn(pDest);

	CSclCtrlsSmvOut *p = (CSclCtrlsSmvOut*)pDest;

	return TRUE;
}

CBaseObject* CSclCtrlsSmvOut::Clone()
{
	CSclCtrlsSmvOut *p = new CSclCtrlsSmvOut();
	Copy(p);
	return p;
}



//////////////////////////////////////////////////////////////////////////
//CSclCtrlsSmvIn
CSclCtrlsSmvIn::CSclCtrlsSmvIn()
{
	m_strName = _T("SMV Inputs");
	m_strID = m_strName;
}

CSclCtrlsSmvIn::~CSclCtrlsSmvIn()
{

}


BOOL CSclCtrlsSmvIn::IsExist(const CString &iedName, const CString &ldName, const CString &lnName, const CString &scl_datSet)
{
	CSclCtrlSmvIn *pFind = NULL;
	CSclCtrlSmvIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlSmvIn *)GetNext(pos);

		if ((p->iedStr == iedName) && (p->ldName == ldName) && (p->lnName == lnName)  && (p->m_strDataSet == scl_datSet))
		{
			pFind = p;
			break;
		}
	}

	return (pFind != NULL);
}


long CSclCtrlsSmvIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}


CExBaseObject* CSclCtrlsSmvIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{

	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclCtrlSvInKey)
	{
		pNew = new CSclCtrlSmvIn();
		return pNew;
	}
	return pNew;

}

long CSclCtrlsSmvIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	SetRead();

	return 0;
}


BOOL CSclCtrlsSmvIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrls::CopyOwn(pDest);

	CSclCtrlsSmvIn *p = (CSclCtrlsSmvIn*)pDest;

	return TRUE;
}

CBaseObject* CSclCtrlsSmvIn::Clone()
{
	CSclCtrlsSmvIn *p = new CSclCtrlsSmvIn();
	Copy(p);
	return p;
}


void CSclCtrlsSmvIn::GetAllChs(CExBaseList &listChs)
{
	POS pos = GetHeadPosition();
	CSclCtrlSmvIn *pSclCtrlGsIn = NULL;

	while (pos != NULL)
	{
		pSclCtrlGsIn = (CSclCtrlSmvIn *)GetNext(pos);
		POS posCh = pSclCtrlGsIn->GetHeadPosition();
		CSclChSmvIn *pCh = NULL;

		while (posCh != NULL)
		{
			pCh = (CSclChSmvIn *)pSclCtrlGsIn->GetNext(posCh);
			AddCh(listChs, pCh);
		}
	}
}

CSclCtrlBase* CSclCtrlsSmvIn::FindSclCtrlByAppID(DWORD dwAppID)
{
	CSclCtrlSmvIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlSmvIn *)GetNext(pos);

		if (p->m_dwAppID == dwAppID)
		{
			return p;
		}
	}

	return NULL;
}

CSclCtrlBase* CSclCtrlsSmvIn::FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac)
{
	CSclCtrlSmvIn *p = NULL;
	POS pos = GetHeadPosition();
	DWORD nAppID = 0;
	HexToDWORD(strAppID,nAppID);

	while (pos != NULL)
	{
		p = (CSclCtrlSmvIn *)GetNext(pos);

		if (strDesMac.IsEmpty())
		{
			if ((p->m_dwAppID == nAppID))
			{
				return p;
			}
		} 
		else
		{
			if ((p->m_dwAppID == nAppID)&&(p->m_strMac == strDesMac))
			{
				return p;
			}
		}
	}

	return NULL;
}

CSclCtrlBase* CSclCtrlsSmvIn::FindSclCtrlBySvID_DesMac(const CString &strSVID,const CString &strDesMac)
{
	CSclCtrlSmvIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlSmvIn *)GetNext(pos);

		if (strDesMac.IsEmpty())
		{
			if ((p->m_strSVID == strSVID))
			{
				return p;
			}
		} 
		else
		{
			if ((p->m_strSVID == strSVID)&&(p->m_strMac == strDesMac))
			{
				return p;
			}
		}
	}

	return NULL;
}

void CSclCtrlsSmvIn::AddCh(CExBaseList &listChs, CSclChSmvIn *pCh)
{
	POS pos = listChs.GetHeadPosition();
	CSclChSmvIn *p = NULL;

	while (pos != NULL)
	{
		p = (CSclChSmvIn *)listChs.GetAt(pos);

		if (p->inIndex > pCh->inIndex)
		{
			break;
		}

		listChs.GetNext(pos);
	}

	if (pos == NULL)
	{
		listChs.AddTail(pCh);
	}
	else
	{
		listChs.InsertBefore(pos, pCh);
	}
}


//////////////////////////////////////////////////////////////////////////
//CSclCtrlsGsIn
CSclCtrlsGsIn::CSclCtrlsGsIn()
{
	m_strName = _T("GOOSE Inputs");
	m_strID = m_strName;
	/*m_pSclCtrlGsIn=NULL;*/
}

CSclCtrlsGsIn::~CSclCtrlsGsIn()
{

}


long CSclCtrlsGsIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclCtrlsGsIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	SetRead();

	return 0;
}


BOOL CSclCtrlsGsIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrls::CopyOwn(pDest);

	CSclCtrlsGsIn *p = (CSclCtrlsGsIn*)pDest;

	return TRUE;
}

CBaseObject* CSclCtrlsGsIn::Clone()
{
	CSclCtrlsGsIn *p = new CSclCtrlsGsIn();
	Copy(p);
	return p;
}

CSclCtrlGsIn* CSclCtrlsGsIn::FindByGsID(const CString &strGsID)
{
	CSclCtrlGsIn *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsIn *)GetNext(pos);

		if (p->m_strGooseId == strGsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CSclCtrlsGsIn::GetAllChs(CExBaseList &listChs)
{
	POS pos = GetHeadPosition();
	CSclCtrlGsIn *pSclCtrlGsIn = NULL;

	while (pos != NULL)
	{
		pSclCtrlGsIn = (CSclCtrlGsIn *)GetNext(pos);
		POS posCh = pSclCtrlGsIn->GetHeadPosition();
		CSclChGsIn *pCh = NULL;

		while (posCh != NULL)
		{
			pCh = (CSclChGsIn *)pSclCtrlGsIn->GetNext(posCh);
			AddCh(listChs, pCh);
		}
	}
}

CSclCtrlBase* CSclCtrlsGsIn::FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac)
{
	DWORD nAppID = 0;
	HexToDWORD(strAppID,nAppID);
	return FindSclCtrlByAppID_DesMac(nAppID,strDesMac);
}

CSclCtrlBase* CSclCtrlsGsIn::FindSclCtrlByAppID_DesMac(DWORD dwAppID,const CString &strDesMac)
{
	CSclCtrlGsIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsIn *)GetNext(pos);

		if (strDesMac.IsEmpty())
		{
			if ((p->m_dwAppID == dwAppID))
			{
				return p;
			}
		} 
		else
		{
			if ((p->m_dwAppID == dwAppID)&&(p->m_strMac == strDesMac))
			{
				return p;
			}
		}
	}

	return NULL;
}

CSclCtrlBase* CSclCtrlsGsIn::FindSclCtrlByAppID(DWORD dwAppID)
{
	CSclCtrlGsIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsIn *)GetNext(pos);

		if (p->m_dwAppID == dwAppID)
		{
			return p;
		}
	}

	return NULL;
}

void CSclCtrlsGsIn::AddCh(CExBaseList &listChs, CSclChGsIn *pCh)
{
	POS pos = listChs.GetHeadPosition();
	CSclChGsIn *p = NULL;

	while (pos != NULL)
	{
		p = (CSclChGsIn *)listChs.GetAt(pos);

		if (p->inIndex > pCh->inIndex)
		{
			break;
		}

		listChs.GetNext(pos);
	}

	if (pos == NULL)
	{
		listChs.AddTail(pCh);
	}
	else
	{
		listChs.InsertBefore(pos, pCh);
	}
}

CExBaseObject* CSclCtrlsGsIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{

	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclCtrlGsInKey)
	{
		pNew = new CSclCtrlGsIn();
		return pNew;
	}
	return pNew;

}

BOOL CSclCtrlsGsIn::IsExist(const CString &iedName, const CString &ldName, const CString &lnName, const CString &scl_datSet)
{
	CSclCtrlGsIn *pFind = NULL;
	CSclCtrlGsIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsIn *)GetNext(pos);

		if ((p->m_strIedDesc == iedName) && (p->ldName == ldName) && (p->lnName == lnName)  && (p->m_strDataSet == scl_datSet))
		{
			pFind = p;
			break;
		}
	}

	return (pFind != NULL);
}

CSclCtrlBase* CSclCtrlsGsIn::FindSclCtrlByGoID_DesMac(const CString &strGooseID,const CString &strDesMac)
{
	CSclCtrlGsIn *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsIn *)GetNext(pos);

		if (strDesMac.IsEmpty())
		{
			if ((p->m_strGooseId == strGooseID))
			{
				return p;
			}
		} 
		else
		{
			if ((p->m_strGooseId == strGooseID)&&(p->m_strMac == strDesMac))
			{
				return p;
			}
		}
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//CSclCtrlsGsOut
CSclCtrlsGsOut::CSclCtrlsGsOut()
{
	m_strName = _T("GOOSE Outputs");
	m_strID = m_strName;
}

CSclCtrlsGsOut::~CSclCtrlsGsOut()
{

}

CSclCtrlGsOut*  CSclCtrlsGsOut::FindCrl_GooseOutput(const CString &strGsID)
{
	CSclCtrlGsOut *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsOut *)GetNext(pos);

		if (p->m_strGooseId == strGsID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CSclCtrlGsOut*  CSclCtrlsGsOut::FindCrlByGooseRefPath_GooseOutput(const CString &strgocbRef)
{
	CSclCtrlGsOut *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsOut *)GetNext(pos);

		if (p->m_strgocbRef == strgocbRef)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CExBaseObject* CSclCtrlsGsOut::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{

	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCSclCtrlGsOutKey)
	{
		pNew = new CSclCtrlGsOut();
		return pNew;
	}

	return pNew;

}

long CSclCtrlsGsOut::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclCtrlsGsOut::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	SetRead();

	return 0;
}


BOOL CSclCtrlsGsOut::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSclCtrls::CopyOwn(pDest);

	CSclCtrlsGsOut *p = (CSclCtrlsGsOut*)pDest;

	return TRUE;
}

CBaseObject* CSclCtrlsGsOut::Clone()
{
	CSclCtrlsGsOut *p = new CSclCtrlsGsOut();
	Copy(p);
	return p;
}

CSclCtrlBase* CSclCtrlsGsOut::FindSclCtrlByAppID(DWORD dwAppID)
{
	CSclCtrlGsOut *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsOut *)GetNext(pos);

		if (p->m_dwAppID == dwAppID)
		{
			return p;
		}
	}

	return NULL;
}

CSclCtrlBase* CSclCtrlsGsOut::FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac)
{
	DWORD nAppID = 0;
	HexToDWORD(strAppID,nAppID);
	return FindSclCtrlByAppID_DesMac(nAppID,strDesMac);
}

CSclCtrlBase* CSclCtrlsGsOut::FindSclCtrlByAppID_DesMac(DWORD dwAppID,const CString &strDesMac)
{
	CSclCtrlGsOut *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsOut *)GetNext(pos);

		if (strDesMac.IsEmpty())
		{
			if ((p->m_dwAppID == dwAppID))
			{
				return p;
			}
		} 
		else
		{
			if ((p->m_dwAppID == dwAppID)&&(p->m_strMac == strDesMac))
			{
				return p;
			}
		}
	}

	return NULL;
}

void CSclCtrlsGsOut::AddGsOut_NoRepeat(CSclCtrlsGsOut *pSclCtrlsGsOut)
{
	CSclCtrlGsOut *p = NULL;
	POS pos = pSclCtrlsGsOut->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CSclCtrlGsOut *)pSclCtrlsGsOut->GetNext(pos);

		if (FindSclCtrlByAppID_DesMac(p->m_dwAppID,p->m_strMac) == NULL)
		{
			AddTail(p);
		}
	}

}

//////////////////////////////////处理IED信息//////////////////////////////////////////////////////////////////////////////////////////////
//CSclIed
const CString CSclIed::g_astrIedType[IedTypeIndex_MAX]     = {_T("ProtMeas"), _T("Meas"), _T("Prot"), _T("RPITMU"), _T("RPIT"), _T("MU"), _T("ScdFile"), _T("NetGate"), _T("ProtInfo"), _T("")};
const CString CSclIed::g_astrIedTypeDesc[IedTypeIndex_MAX] = {_T("保护测控装置"), _T("测控装置"), _T("保护装置"), _T("合智一体装置"), _T("智能终端"), _T("合并单元"), /*g_sLangTxt_SCDFile*/_T("SCD文件"), _T("远动测试"), _T("保信测试"), _T("其他类型装置")};


BOOL CSclIed::IsIed_RPIT_MU()
{
	if(   m_strIedTypeLabel == g_astrIedType[IedTypeIndex_RPITMU]
		||m_strIedTypeLabel == g_astrIedType[IedTypeIndex_RPIT]
		||m_strIedTypeLabel == g_astrIedType[IedTypeIndex_MU] )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSclIed::IsIed_MU()
{
	if(m_strIedTypeLabel == g_astrIedType[IedTypeIndex_MU] )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSclIed::IsIed_RPIT()
{
	if(m_strIedTypeLabel == g_astrIedType[IedTypeIndex_RPIT] )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSclIed::IsIed_Prot_Meas()
{
	if(   m_strIedTypeLabel == g_astrIedType[IedTypeIndex_ProtMeas]
	||m_strIedTypeLabel == g_astrIedType[IedTypeIndex_Prot]
	||m_strIedTypeLabel == g_astrIedType[IedTypeIndex_Meas] )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSclIed::IsIed_Prot()
{
	if(m_strIedTypeLabel == g_astrIedType[IedTypeIndex_Prot] )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CSclIed::IsIed_Meas()
{
	if(   m_strIedTypeLabel == g_astrIedType[IedTypeIndex_Meas] )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


CString CSclIed::GetIedTypeDesc(const CString &strIedType)
{
	long nIndex = 0;

	for (nIndex=0; nIndex<IedTypeIndex_Other; nIndex++)
	{
		if (g_astrIedType[nIndex] == strIedType)
		{
			return g_astrIedTypeDesc[nIndex];
		}
	}

	return g_astrIedTypeDesc[IedTypeIndex_Other];
}

BOOL CSclIed::IsProtNetGate(const CString &strType)
{
	if (g_astrIedType[IedTypeIndex_NETGAT] == strType)
	{
		return TRUE;
	}

	if (g_astrIedType[IedTypeIndex_PROTINFO] == strType)
	{
		return TRUE;
	}

	return FALSE;
}

CSclIed::CSclIed()
{
	m_pSmvOuts = NULL;
	m_pSmvins = NULL;
	m_pGsOuts = NULL;
	m_pGsIns = NULL;
	/*m_pRefIED = NULL;*/

	m_pDvmDevice =NULL;
	m_pRefItemData = NULL;
	 m_strIedType=_T("");
	 m_strModel="";
	 m_strIedTypeLabel="";


	LDTYPE_PROT=0;
	LDTYPE_MEAS=0;
	LDTYPE_CTRL=0;
	LDTYPE_RPIT=0;
	LDTYPE_MU=0;
	m_strIP="";
	m_strIP_GATEWAY="";
	m_strIP_SUBNET="";

	m_nSelected = 0;
}

CSclIed::~CSclIed()
{

}

void CSclIed::SetLDType(char* pLDType)
{
	if (pLDType==NULL)
	{
		return;
	}
	else if(strstr(pLDType,"PROT"))
	{
		LDTYPE_PROT=1;
		return;
	}
	else if(strstr(pLDType,"MEAS"))
	{
		LDTYPE_MEAS=1;
		return;
	}
	else if(strstr(pLDType,"CTRL"))
	{
		LDTYPE_CTRL=1;
		return;
	}
	else if(strstr(pLDType,"RPIT"))
	{
		LDTYPE_RPIT=1;
		return;
	}
	else if(strstr(pLDType,"MU"))
	{
		LDTYPE_MU=1;
		return ;
	}
	return ;

}


void CSclIed::SetIedType()
{
	if (LDTYPE_PROT||LDTYPE_MEAS||LDTYPE_CTRL)
	{
		if((LDTYPE_PROT&&LDTYPE_MEAS)||(LDTYPE_PROT&&LDTYPE_CTRL))
		{
			m_strIedType = g_astrIedTypeDesc[IedTypeIndex_ProtMeas];
			m_strIedTypeLabel = g_astrIedType[IedTypeIndex_ProtMeas];
			return ;
		}
		else if(LDTYPE_MEAS&&LDTYPE_CTRL)
		{
			m_strIedType=g_astrIedTypeDesc[IedTypeIndex_Meas];
			m_strIedTypeLabel = g_astrIedType[IedTypeIndex_Meas];
			return ;
		}
		else if(LDTYPE_PROT)
		{
			m_strIedType=g_astrIedTypeDesc[IedTypeIndex_Prot];
			m_strIedTypeLabel = g_astrIedType[IedTypeIndex_Prot];
			return ;
		}
	}
	else if (LDTYPE_RPIT&&LDTYPE_MU)
	{
		m_strIedType=g_astrIedTypeDesc[IedTypeIndex_RPITMU];
		m_strIedTypeLabel = g_astrIedType[IedTypeIndex_RPITMU];

		return ;		
	}
	else if (LDTYPE_RPIT)
	{
		m_strIedType=g_astrIedTypeDesc[IedTypeIndex_RPIT];
		m_strIedTypeLabel = g_astrIedType[IedTypeIndex_RPIT];
		return ;		
	}
	else if (LDTYPE_MU)
	{
		m_strIedType=g_astrIedTypeDesc[IedTypeIndex_MU];
		m_strIedTypeLabel=g_astrIedType[IedTypeIndex_MU];
		return ;		
	}
	else
	{
		m_strIedType = g_astrIedTypeDesc[IedTypeIndex_Other];	
		m_strIedTypeLabel=g_astrIedType[IedTypeIndex_Other];
	}
}

void CSclIed::SetSaveCBChs(BOOL bSaveChs)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	CSclCtrls *pSclCtrls = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() == DVMCLASSID_CDVMDEVICE)
		{
			continue;
		}

		pSclCtrls = (CSclCtrls*)pCurrObj;
		pSclCtrls->SetSaveCBChs(bSaveChs);
	}
}

void CSclIed::DeleteCtrls(CExBaseList *pCtrls)
{
	if (pCtrls->GetCount() > 0)
	{
		return;
	}

	if (m_pGsIns == pCtrls)
	{
		m_pGsIns = NULL;
	}
	else if (m_pGsOuts == pCtrls)
	{
		m_pGsOuts = NULL;
	}
	else if (m_pSmvins == pCtrls)
	{
		m_pSmvins = NULL;
	}
	else if (m_pSmvOuts == pCtrls)
	{
		m_pSmvOuts = NULL;
	}

	Delete(pCtrls);
}

CSclCtrls* CSclIed::GetFirstCtrlObj()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID ==SCLIECCLASSID_CTRLS_SMV_OUT)
		{
			return (CSclCtrls*)p;
		}
		else if (nClassID ==SCLIECCLASSID_CTRLS_SMV_IN)
		{
			return (CSclCtrls*)p;
		}
		else if (nClassID ==SCLIECCLASSID_CTRLS_GS_OUT)
		{
			return (CSclCtrls*)p;
		}
		else if (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
		{
			return (CSclCtrls*)p;
		}
	}

	return NULL;
}

CSclCtrlGsOut*  CSclIed::FindCrl_GooseOutput(const CString &strGsID)
{
	if (m_pGsOuts == NULL)
	{
		return NULL;
	}

	return m_pGsOuts->FindCrl_GooseOutput(strGsID);
}

CSclCtrlSmvOut* CSclIed::FindCrl_SmvOutput(const CString &strSvID)
{
	if (m_pSmvOuts == NULL)
	{
		return NULL;
	}

	return m_pSmvOuts->FindCrl_SmvOutput(strSvID);
}

CSclCtrlBase* CSclIed::FindCtrl_GsOutSmvOut(DWORD dwAppID,BOOL bSmv)
{
	CSclCtrls *pSclCtrls = NULL;

	if (bSmv)
	{
		pSclCtrls = GetSmvOuts();
	} 
	else
	{
		pSclCtrls = GetGsOuts();
	}

	POS pos = pSclCtrls->GetHeadPosition();
	CSclCtrlBase *pFind = NULL,*pCurSclCtrl = NULL;

	while (pos != NULL)
	{
		pCurSclCtrl = (CSclCtrlBase*)pSclCtrls->GetNext(pos);

		if (pCurSclCtrl->m_dwAppID == dwAppID)
		{
			pFind = pCurSclCtrl;
			break;
		}
	}

	return pFind;
}

void CSclIed::ClearAll()
{
	DeleteAll();
	m_pSmvOuts = NULL;
	m_pSmvins = NULL;
	m_pGsOuts = NULL;
	m_pGsIns = NULL;
	m_pDvmDevice = NULL;
}

BOOL CSclIed::IsAllCtrlsSelected()
{
	if (m_pSmvins != NULL)
	{
		if (!m_pSmvins->IsAllSelected())
		{
			return FALSE;
		}
	}

	if (m_pSmvOuts != NULL)
	{
		if (!m_pSmvOuts->IsAllSelected())
		{
			return FALSE;
		}
	}

	if (m_pGsIns != NULL)
	{
		if (!m_pGsIns->IsAllSelected())
		{
			return FALSE;
		}
	}

	if (m_pGsOuts != NULL)
	{
		if (!m_pGsOuts->IsAllSelected())
		{
			return FALSE;
		}
	}

	return TRUE;
}


CSclCtrlsSmvOut* CSclIed::GetSmvOuts()
{
	if (m_pSmvOuts == NULL)
	{
		m_pSmvOuts = new CSclCtrlsSmvOut();
		AddNewChild(m_pSmvOuts);
	}

	return m_pSmvOuts;
}

CSclCtrlsSmvIn*  CSclIed::GetSmvIns()
{
	if (m_pSmvins == NULL)
	{
		m_pSmvins = new CSclCtrlsSmvIn();
		AddNewChild(m_pSmvins);
	}

	return m_pSmvins;
}

CSclCtrlsGsOut*  CSclIed::GetGsOuts()
{
	if (m_pGsOuts == NULL)
	{
		m_pGsOuts = new CSclCtrlsGsOut();
		AddNewChild(m_pGsOuts);
	}

	return m_pGsOuts;
}

CSclCtrlsGsIn*   CSclIed::GetGsIns()
{
	if (m_pGsIns == NULL)
	{
		m_pGsIns = new CSclCtrlsGsIn();
		AddNewChild(m_pGsIns);
	}

	return m_pGsIns;
}

CDvmDevice*  CSclIed::GetDvmDevice()
{
	if (m_pDvmDevice == NULL)
	{
		m_pDvmDevice = new CDvmDevice();
		AddNewChild(m_pDvmDevice);

		m_pDvmDevice->m_strName = m_strName;
		m_pDvmDevice->m_strID   = m_strID;
	}

	return m_pDvmDevice;
}


void CSclIed::SaveIedFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();		
	strFile.AppendFormat(_T("%s.xml"), m_strID.GetString());
	SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

void CSclIed::SaveIedFile(const CString &strSavePath)
{
	CString strFile=strSavePath;
		
	strFile.AppendFormat(_T("%s.xml"), m_strID.GetString());

	SaveIedFile2(strFile);
}

void CSclIed::SaveSiedFile(const CString &strSavePath)
{
	CString strFile=strSavePath;

	strFile.AppendFormat(_T("%s.sied"), m_strID.GetString());

	SaveIedFile2(strFile);
}

void CSclIed::SaveIedFile2(const CString &strFile)
{
	if (!IsFileExist(strFile))
	{
// #ifdef _PSX_QT_LINUX_//在linux下需要进行编码转换,采用utf8编码处理,后期需要改为在pugixml保存的地方处理
// 		CString strUtf8String;
// 
// 		if (gbk_to_utf8(strFile,strUtf8String)>0)
// 		{
// 			SaveXmlFile(strUtf8String, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 		} 
// 		else
// 		{
// 			SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 		}
// 
// #else
		SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
//#endif
	}
}


long CSclIed::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIedTypeKey, oElement,m_strIedType);
	xml_SetAttributeValue(pXmlKeys->m_strIedTypeLabelKey, oElement,m_strIedTypeLabel);
	xml_SetAttributeValue(pXmlKeys->m_strIedTypeIDKey, oElement,m_strModel);
	xml_SetAttributeValue(pXmlKeys->m_strManufacturerKey, oElement,m_strManufacturer);
	xml_SetAttributeValue(pXmlKeys->m_strIedIPKey, oElement,m_strIP);
	xml_SetAttributeValue(pXmlKeys->m_strIedIPSUBNETKey, oElement,m_strIP_SUBNET);
	xml_SetAttributeValue(pXmlKeys->m_strIedIPGATEWAYKey, oElement,m_strIP_GATEWAY);

	return 0;
}

long CSclIed::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (m_pGsIns != NULL)
	{
		POS pos = m_pGsIns->GetHeadPosition();
		POS posNew = NULL;
		POS posDel = NULL;
		CSclCtrlGsIn *pSclCtrlGsIn = NULL;
		CSclCtrlGsIn *pSclCtrlGsInNew = NULL;
		for (;pos!=NULL;)
		{
			pSclCtrlGsIn = (CSclCtrlGsIn*)m_pGsIns->GetNext(pos);
			posNew = pos;
			bool bIndex = true;
			for (;posNew!=NULL;)
			{
				posDel = posNew;
				pSclCtrlGsInNew = (CSclCtrlGsIn*)m_pGsIns->GetNext(posNew);
				if ((pSclCtrlGsIn->m_strGooseId == pSclCtrlGsInNew->m_strGooseId)&&
					(pSclCtrlGsIn->m_strMac == pSclCtrlGsInNew->m_strMac)&&(pSclCtrlGsIn->m_dwAppID == pSclCtrlGsInNew->m_dwAppID))
				{
					if (bIndex)
					{
						m_pGsIns->GetNext(pos);
					}
					m_pGsIns->DeleteAt(posDel);	
				}
				bIndex =false;
			}
		}

		m_pGsIns->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}
	if (m_pGsOuts!= NULL)
	{
		m_pGsOuts->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}
	if (m_pSmvins!= NULL)
	{
		m_pSmvins->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}
	if (m_pSmvOuts!= NULL)
	{
		m_pSmvOuts->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	if (m_pDvmDevice!= NULL)
	{
		m_pDvmDevice->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

long  CSclIed::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIedTypeKey, oNode,m_strIedType);
	xml_GetAttibuteValue(pXmlKeys->m_strIedTypeLabelKey, oNode,m_strIedTypeLabel);
	xml_GetAttibuteValue(pXmlKeys->m_strIedTypeIDKey, oNode,m_strModel);
	xml_GetAttibuteValue(pXmlKeys->m_strIedIPKey, oNode,m_strIP);
	xml_GetAttibuteValue(pXmlKeys->m_strIedIPSUBNETKey, oNode,m_strIP_SUBNET);
	xml_GetAttibuteValue(pXmlKeys->m_strIedIPGATEWAYKey, oNode,m_strIP_GATEWAY);

	return 0;
}



CExBaseObject*CSclIed::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclCtrlsSvOutKey)
	{
		pNew = new CSclCtrlsSmvOut();
		m_pSmvOuts=(CSclCtrlsSmvOut*)pNew;
	}

	if (strClassID == pXmlKeys->m_strCSclCtrlsSvInKey)
	{
		pNew = new CSclCtrlsSmvIn();
		m_pSmvins=(CSclCtrlsSmvIn*)pNew;
	}
	if (strClassID == pXmlKeys->m_strCSclCtrlsGsOutKey)
	{
		pNew = new CSclCtrlsGsOut();
		m_pGsOuts=(CSclCtrlsGsOut*)pNew;
	}
	if (strClassID == pXmlKeys->m_strCSclCtrlsGsInKey)
	{
		pNew = new CSclCtrlsGsIn();
		m_pGsIns=(CSclCtrlsGsIn*)pNew;
	}
	if (strClassID == pXmlKeys->m_strCDvmDeviceKey)
	{
		pNew = new CDvmDevice();
		m_pDvmDevice=(CDvmDevice*)pNew;
	}

	return pNew;
}


CExBaseObject* CSclIed::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID ==SCLIECCLASSID_CTRLS_SMV_OUT)
	{
		pNew = new CSclCtrlsSmvOut();
	}

	if (nClassID ==SCLIECCLASSID_CTRLS_SMV_IN)
	{
		pNew = new CSclCtrlsSmvIn();
	}
	if (nClassID ==SCLIECCLASSID_CTRLS_GS_OUT)
	{
		pNew = new CSclCtrlsGsOut();
	}
	if (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
	{
		pNew = new CSclCtrlsGsIn();
	}

	return pNew;
}

void CSclIed::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID ==SCLIECCLASSID_CTRLS_SMV_OUT)
		{
			m_pSmvOuts = (CSclCtrlsSmvOut*)p;
		}
		else if (nClassID ==SCLIECCLASSID_CTRLS_SMV_IN)
		{
			m_pSmvins = (CSclCtrlsSmvIn*)p;
		}
		else if (nClassID ==SCLIECCLASSID_CTRLS_GS_OUT)
		{
			m_pGsOuts = (CSclCtrlsGsOut*)p;
		}
		else if (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
		{
			m_pGsIns = (CSclCtrlsGsIn*)p;
		}
	}

	InitDatasetPath();
}

void CSclIed::InitDatasetPath()
{
	POS pos = NULL;
	CSclCtrlSmvOut *pSmvOut;
	CSclCtrlSmvIn  *pSmvin;
	CSclCtrlGsOut  *pGsOut;
	CSclCtrlGsIn   *pGsIn;
	CString strTmp;
	long nIndex;

	if (m_pGsOuts != NULL)
	{
		pos = m_pGsOuts->GetHeadPosition();

		while(pos!=NULL)
		{
			pGsOut = (CSclCtrlGsOut*)m_pGsOuts->GetNext(pos);
			nIndex = pGsOut->m_strgocbRef.Find(_T("LLN0"));

			if (nIndex != -1)
			{
				strTmp = pGsOut->m_strgocbRef.Left(nIndex);
				pGsOut->m_strDataSetPath.Format(_T("%sLLN0$%s"), strTmp.GetString(),pGsOut->m_strDataSet.GetString() );
			}
		}
	}

	if (m_pGsIns != NULL)
	{
		pos = m_pGsIns->GetHeadPosition();

		while(pos!=NULL)
		{
			pGsIn = (CSclCtrlGsIn*)m_pGsIns->GetNext(pos);
			nIndex = pGsIn->m_strgocbRef.Find(_T("LLN0"));

			if (nIndex != -1)
			{
				strTmp = pGsIn->m_strgocbRef.Left(nIndex);
				pGsIn->m_strDataSetPath.Format(_T("%sLLN0$%s"), strTmp.GetString(),pGsIn->m_strDataSet.GetString() );
			}
		}
	}

	if (m_pSmvOuts != NULL)
	{
		pos = m_pSmvOuts->GetHeadPosition();

		while(pos!=NULL)
		{
			pSmvOut = (CSclCtrlSmvOut*)m_pSmvOuts->GetNext(pos);

			nIndex = pSmvOut->m_strID.Find(_T("LLN0"));

			if (nIndex != -1)
			{
				strTmp = pSmvOut->m_strID.Left(nIndex);
				pSmvOut->m_strDataSetPath.Format(_T("%sLLN0$%s"), strTmp.GetString(),pSmvOut->m_strDataSet.GetString() );

			}
		}
	}

	if (m_pSmvins != NULL)
	{
		pos = m_pSmvins->GetHeadPosition();

		while(pos!=NULL)
		{
			pSmvin = (CSclCtrlSmvIn*)m_pSmvins->GetNext(pos);

			nIndex = pSmvin->m_strID.Find(_T("LLN0"));

			if (nIndex != -1)
			{
				strTmp = pSmvin->m_strID.Left(nIndex);
				pSmvin->m_strDataSetPath.Format(_T("%sLLN0$%s"), strTmp.GetString(),pSmvin->m_strDataSet.GetString() );

			}
		}
	}

}

CString CSclIed::GetSCDFilePath()
{
	CSclStation *pSclStation = (CSclStation*)m_pParent;

	if (pSclStation != NULL)
	{
		return pSclStation->m_strScdFile;
	}

	return _T("");
}

BOOL CSclIed::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

	CSclIed *p = (CSclIed*)pDest;
	p->m_strIedType = m_strIedType;
	p->m_strIP = m_strIP;
	p->m_strIP_SUBNET = m_strIP_SUBNET;
	p->m_strIP_GATEWAY = m_strIP_GATEWAY;

	p->test_men = test_men;
	p->model_test = model_test;
	p->vcnln_test = vcnln_test;
	p->macro_test = macro_test;	
	p->LDTYPE_PROT = LDTYPE_PROT;
	p->LDTYPE_MEAS = LDTYPE_MEAS;
	p->LDTYPE_CTRL = LDTYPE_CTRL;
	p->LDTYPE_RPIT = LDTYPE_RPIT;
	p->LDTYPE_MU   = LDTYPE_MU;

	return TRUE;
}

CBaseObject* CSclIed::Clone()
{
	CSclIed *p = new CSclIed();
	Copy(p);
	return p;
}

//////////////////////////////////////////////////////////////////////////
//CSclStation
CSclStation::CSclStation()
{

}

CSclStation::~CSclStation()
{


}

BOOL CSclStation::OpenSclStationFile(const CString &strFile)
{
	m_strTscdFile = strFile;
	DeleteAll();
	return OpenXmlFile(strFile,CCfgDataMngrXmlRWKeys::g_pXmlKeys);	
}

BOOL CSclStation::OpenSiedFile(CSclIed *pSclIed)
{
	if (pSclIed == NULL)
	{
		return FALSE;
	}

	CString strFolderPath;
	strFolderPath = GetPathFromFilePathName(m_strTscdFile);
	strFolderPath.AppendFormat(_T("%s.sied"),pSclIed->m_strID.GetString());
	pSclIed->ClearAll();
	return pSclIed->OpenXmlFile(strFolderPath,CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

#ifdef USE_WAITINGTIMEDLG_FOR_SCLCOMPARECHECK
void CSclStation::OpenSclFileByThr(const CString &strFile)
{
	m_strTscdFile = strFile;
	CWinThread *pThread; //线程指针
	pThread = AfxBeginThread(OpenSclFileThread, this); //启动线程 
	pThread->m_bAutoDelete = TRUE;

	CWaitingTimeDlg dlg;
	dlg.m_strMsgDesc.Format("正在读取Tscd文件 , 路径:\"%s\"",strFile.GetString());
	dlg.DoModal();
}

UINT CSclStation::OpenSclFileThread(LPVOID pParam)
{
	CSclStation *pSclStation = (CSclStation *)pParam;
	pSclStation->OpenSclStationFile(pSclStation->m_strTscdFile);

	CWaitingTimeDlg::g_bOver =  true;
	return 1;
}
#endif

BOOL CSclStation::SaveIedFiles()
{
// 	g_pIedFile_Abstract=0;

	POS pos = GetHeadPosition();		
	CExBaseObject *pTemp= NULL;

	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)GetNext(pos);

		if(pTemp->GetClassID()==CFGCLASSID_CSCLBAY)
		{

		}
		else if(pTemp->GetClassID()==SCLIECCLASSID_IED)
		{
			CSclIed* pIed= (CSclIed *)pTemp;
			pIed->SaveIedFile();
		}
	}

	return 0;
}

BOOL CSclStation::SaveIedFiles(const CString &strSavePath)
{
// 	g_pIedFile_Abstract=0;

	POS pos = GetHeadPosition();		
	CExBaseObject *pTemp= NULL;

	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)GetNext(pos);

		if(pTemp->GetClassID()==CFGCLASSID_CSCLBAY)
		{

		}
		else if(pTemp->GetClassID()==SCLIECCLASSID_IED)
		{
			CSclIed* pIed= (CSclIed *)pTemp;
			pIed->SaveIedFile(strSavePath);
		}
	}

	return 0;
}

BOOL CSclStation::SaveAbstractFile()
{
// 	g_pIedFile_Abstract=1;

	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += m_strName;
	strFile = ChangeFilePostfix(strFile, STATION_FILE_POSTFIX);
	m_strTscdFile = strFile;//周宏军 20200306 将保存的 *.tscd文件路径记录下来

	SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 	g_pIedFile_Abstract=0;
	InitSvGsIns();

	return 1;
}

BOOL CSclStation::SaveAbstractFile(const CString &strSavePath)
{
// 	g_pIedFile_Abstract=1;

	CString strFile;
	strFile = strSavePath;
	strFile += m_strName;
	strFile = ChangeFilePostfix(strFile, STATION_FILE_POSTFIX);
	m_strTscdFile = strFile;//周宏军 20200306 将保存的 *.tscd文件路径记录下来

	SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 	g_pIedFile_Abstract=0;
	InitSvGsIns();

	return 1;
}

BOOL CSclStation::SaveStationFile()//保存SCD文件解析后的文件
{
// 	g_pIedFile_Abstract=0;
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += "SCLCheckStation/";
	strFile += m_strName;
	strFile = ChangeFilePostfix(strFile, STATION_FILE_POSTFIX);
	m_strTscdFile = strFile;//周宏军 20200306 将保存的 *.tscd文件路径记录下来

	return SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CSclStation::SaveSsclFiles(const CString &strSaveSsclFilePath)
{
	CString strFolderPath;
	strFolderPath = GetPathFromFilePathName(strSaveSsclFilePath);
	POS pos = GetHeadPosition();		
	CExBaseObject *pTemp= NULL;
	CSclIed* pIed = NULL;

	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)GetNext(pos);

		if(pTemp->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}
		
		pIed = (CSclIed *)pTemp;
		pIed->SaveSiedFile(strFolderPath);
	}

	SetSaveCBChs(FALSE);

// #ifdef _PSX_QT_LINUX_//在linux下需要进行编码转换,采用utf8编码处理,后期需要改为在pugixml保存的地方处理
// 	CString strUtf8String;
// 	BOOL bRet = FALSE;
// 
// 	if (gbk_to_utf8(strSaveSsclFilePath,strUtf8String)>0)
// 	{
// 		bRet = SaveXmlFile(strUtf8String, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 	} 
// 	else
// 	{
// 		bRet = SaveXmlFile(strSaveSsclFilePath, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 	}
// 	
// #else
	BOOL bRet = SaveXmlFile(strSaveSsclFilePath, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
//#endif
	SetSaveCBChs(TRUE);
	return bRet;
}

void CSclStation::SetSaveCBChs(BOOL bSaveChs)
{
	CExBaseObject *pCurrObj= NULL;
	CSclIed *pIed = NULL;
	POS pos = GetHeadPosition();
	CSclCtrlGsOut *pFind = NULL;

	while (pos != NULL)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)pCurrObj;
		pIed->SetSaveCBChs(FALSE);
	}
}

CSclIed * CSclStation::GetRefIed(const char  *strIedName)
{
	CSclIed*pIed=NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj=NULL;

	while (pos!=NULL)
	{
		pObj=GetNext(pos);

		if (pObj->GetClassID()==CFGCLASSID_CSCLBAY)
		{
		}
		else if(pObj->GetClassID()==SCLIECCLASSID_IED)
		{
			pIed= (CSclIed *)pObj;

			if( pIed->m_strID == strIedName)
			{
				return pIed;
			}
		}
	}

	return NULL;
}

CSclIed* CSclStation::GetSelectedIed()
{
	CSclIed* pIed = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (pObj->GetClassID()!= SCLIECCLASSID_IED)
		{
			continue;
		}
		else if(pObj->GetClassID()==SCLIECCLASSID_IED)
		{
			pIed = (CSclIed *)pObj;

			if( pIed->m_nSelected == 1)
			{
				return pIed;
			}
		}
	}

	return NULL;
}

long CSclStation::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclStation::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject*CSclStation::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclIedKey)
	{
		pNew = new CSclIed();
	}

	if(strClassID == pXmlKeys->m_strCSclBayKey)
	{
		pNew=new CSclBay();
	}

	return pNew;
}

CExBaseObject* CSclStation::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == SCLIECCLASSID_IED)
	{
		pNew = new CSclIed();
	}

	if(nClassID == CFGCLASSID_CSCLBAY)
	{
		pNew=new CSclBay();
	}

	return pNew;
}

CSclCtrlGsOut* CSclStation::FindGooseOutput(const CString &strIedName, const CString &strGsID)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsGsOut *pSclCtrlsGsOut = pIed->GetGsOuts();

	//FindGSSVControl(pSclCtrlsGsOut);

	CSclCtrlGsOut *pFind = (CSclCtrlGsOut*)pSclCtrlsGsOut->FindByID(strGsID);

	return pFind;
}

CSclCtrlGsOut* CSclStation::FindGooseOutput(const CString &strIedName, const CString &strGsID ,const CString &strGocbRef)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsGsOut *pSclCtrlsGsOut = pIed->GetGsOuts();

	//FindGSSVControl(pSclCtrlsGsOut);

	CSclCtrlGsOut *pFind = NULL;
	CSclCtrlGsOut *pGsOutCtrl = NULL;
	POS pos = pSclCtrlsGsOut->GetHeadPosition();

	while(pos != NULL)
	{
		pGsOutCtrl = (CSclCtrlGsOut *)pSclCtrlsGsOut->GetNext(pos);

		if((pGsOutCtrl->m_strID == strGsID)&&(pGsOutCtrl->m_strgocbRef == strGocbRef))
		{
			pFind = pGsOutCtrl;
			break;
		}
	}

	return pFind;
}

CSclCtrlSmvOut* CSclStation::FindSmvOutput(const CString &strIedName, const CString &strSmvID)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsSmvOut *pSclCtrlsSmvOut = pIed->GetSmvOuts();

	//FindGSSVControl(pSclCtrlsSmvOut);

	CSclCtrlSmvOut *pFind = (CSclCtrlSmvOut*)pSclCtrlsSmvOut->FindByID(strSmvID);

	return pFind;
}

//ZHJ
CSclCtrlSmvOut* CSclStation::FindSmvInput(CSclCtrlSmvOut *pSclCtrlSmvOut)
{
	POS posCh = NULL;
	POS posIed = GetHeadPosition();
	POS posCtrl = NULL;
	CSclChSmvOut *pSclChSmvOut = NULL;
	CSclIed *pSclIed = NULL;
	CSclCtrlsSmvIn *pSclCtrlsSmvIn = NULL;
	CSclCtrlSmvIn *pSclCtrlSmvIn = NULL;
	CSclChSmvIn *pSclChSmvIn = NULL;

	while(posIed!=NULL)
	{
		pSclIed = (CSclIed*)GetNext(posIed);

		if (pSclIed->GetClassID() == SCLIECCLASSID_IED)
		{
			pSclCtrlsSmvIn = pSclIed->GetSmvIns();
			if (pSclCtrlsSmvIn!=NULL)
			{
				posCtrl = pSclCtrlsSmvIn->GetHeadPosition();
				while(posCtrl!=NULL)
				{
					pSclCtrlSmvIn = (CSclCtrlSmvIn*)pSclCtrlsSmvIn->GetNext(posCtrl);
					if ((pSclCtrlSmvIn->m_strSVID == pSclCtrlSmvOut->m_strSVID)&&(pSclCtrlSmvIn->m_strMac == pSclCtrlSmvOut->m_strMac))
					{
						posCh = pSclCtrlSmvOut->GetHeadPosition();
						while(posCh!=NULL)
						{
							pSclChSmvOut = (CSclChSmvOut*)pSclCtrlSmvOut->GetNext(posCh);
							pSclChSmvIn = (CSclChSmvIn*)pSclCtrlSmvIn->FindByID(pSclChSmvOut->m_strID);
							if (pSclChSmvIn!=NULL)
							{
								pSclChSmvOut->m_oChInRefs.AddTail(pSclChSmvIn);
							}
						}
					}
				}
			}
		}
	}

	return pSclCtrlSmvOut;
}

//ZHJ
CSclCtrlGsOut* CSclStation::FindGsInput(CSclCtrlGsOut *pSclCtrlGsOut)
{
	POS posCh = NULL;
	POS posIed = GetHeadPosition();
	POS posCtrl = NULL;
	CSclChGsOut *pSclChGsOut = NULL;
	CSclIed *pSclIed = NULL;
	CSclCtrlsGsIn *pSclCtrlsGsIn = NULL;
	CSclCtrlGsIn *pSclCtrlGsIn = NULL;
	CSclChGsIn *pSclChGsIn = NULL;

	while(posIed!=NULL)
	{
		pSclIed = (CSclIed*)GetNext(posIed);

		if (pSclIed->GetClassID() == SCLIECCLASSID_IED)
		{
			pSclCtrlsGsIn = pSclIed->GetGsIns();
			if (pSclCtrlsGsIn!=NULL)
			{
				posCtrl = pSclCtrlsGsIn->GetHeadPosition();
				while(posCtrl!=NULL)
				{
					pSclCtrlGsIn = (CSclCtrlGsIn*)pSclCtrlsGsIn->GetNext(posCtrl);
					if ((pSclCtrlGsIn->m_strGooseId == pSclCtrlGsOut->m_strGooseId)&&(pSclCtrlGsIn->m_strMac == pSclCtrlGsOut->m_strMac))
					{
						posCh = pSclCtrlGsOut->GetHeadPosition();
						while(posCh!=NULL)
						{
							pSclChGsOut = (CSclChGsOut*)pSclCtrlGsOut->GetNext(posCh);
							pSclChGsIn = (CSclChGsIn*)pSclCtrlGsIn->FindByID(pSclChGsOut->m_strID);
							if (pSclChGsIn!=NULL)
							{
								pSclChGsOut->m_oChInRefs.AddTail(pSclChGsIn);
							}
						}
					}
				}
			}
		}
	}

	return pSclCtrlGsOut;
}

CSclCtrlGsOut*  CSclStation::FindCrl_GooseOutput(const CString &strIedName, const CString &strGsID)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsGsOut *pSclCtrlsGsOut = pIed->GetGsOuts();
	CSclCtrlGsOut *pFind = (CSclCtrlGsOut*)pSclCtrlsGsOut->FindCrl_GooseOutput(strGsID);

	return pFind;
}

//ZHJ
CSclCtrlGsOut*  CSclStation::FindCrlByGooseRefPath_GooseOutput(const CString &strIedName, const CString &strgocbRef)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsGsOut *pSclCtrlsGsOut = pIed->GetGsOuts();
	CSclCtrlGsOut *pFind = (CSclCtrlGsOut*)pSclCtrlsGsOut->FindCrlByGooseRefPath_GooseOutput(strgocbRef);

	return pFind;
}

CSclCtrlSmvOut* CSclStation::FindCrl_SmvOutput(const CString &strIedName, const CString &strSvID)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsSmvOut *pSclCtrlsSmvOut = pIed->GetSmvOuts();
	CSclCtrlSmvOut *pFind = (CSclCtrlSmvOut*)pSclCtrlsSmvOut->FindCrl_SmvOutput(strSvID);

	return pFind;
}

CSclCtrlGsOut*  CSclStation::FindCrl_GooseOutput(const CString &strGsID)
{
	CSclIed *pIed = NULL;
	POS pos = GetHeadPosition();
	CSclCtrlGsOut *pFind = NULL;

	while (pos != NULL)
	{
		pIed = (CSclIed *)GetNext(pos);

		if (pIed->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pFind = pIed->FindCrl_GooseOutput(strGsID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CSclCtrlSmvOut* CSclStation::FindCrl_SmvOutput(const CString &strSvID)
{
	CSclIed *pIed = NULL;
	POS pos = GetHeadPosition();
	CSclCtrlSmvOut *pFind = NULL;

	while (pos != NULL)
	{
		pIed = (CSclIed *)GetNext(pos);

		if (pIed->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pFind = pIed->FindCrl_SmvOutput(strSvID);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CSclCtrlBase* CSclStation::FindCtrl_GsOutSmvOut(DWORD dwAppID,BOOL bSmv)
{
	CExBaseObject *pCurObj = NULL;
	CSclIed *pIed = NULL;
	POS pos = GetHeadPosition();
	CSclCtrlBase *pFind = NULL;

	while (pos != NULL)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed*)pCurObj;
		pFind = pIed->FindCtrl_GsOutSmvOut(dwAppID,bSmv);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}


void CSclStation::FindGSSVControl(CSclCtrls *pCtrls)
{
	// 	if (pCtrls->IsRead())
	// 	{
	// 		return;
	// 	}
	// 
	// 	BOOL bGsIn = scl_IsGsIns(pCtrls);
	// 	BOOL bGsOut = scl_IsGsOuts(pCtrls);
	// 	BOOL bSmvIn = scl_IsSmvIns(pCtrls);
	// 	BOOL bSmvOut = scl_IsSmvOuts(pCtrls);
	// 
	// 	CSclIed *pIed = scl_GetIed(pCtrls);
	// 
	// 	FindGSSVControl(&m_SclInfo, pIed, bGsIn, bGsOut, bSmvIn, bSmvOut);
	// 
	// 	//获取通道
	// 	POS pos = pCtrls->GetHeadPosition();
	// 	CSclCtrlBase *pCtrl = NULL;
	// 
	// 	while (pos != NULL)
	// 	{
	// 		pCtrl = (CSclCtrlBase *)pCtrls->GetNext(pos);
	// 
	// 		if (bGsIn)
	// 		{
	// 			FindGSSVInChannelInfo(&m_SclInfo, pCtrl);
	// 		}
	// 
	// 		if (bGsOut)
	// 		{
	// 			FindGSSVOutChannelInfo(&m_SclInfo, pCtrl);
	// 		}
	// 
	// 		if (bSmvIn)
	// 		{
	// 			FindGSSVInChannelInfo(&m_SclInfo, pCtrl);
	// 		}
	// 
	// 		if (bSmvOut)
	// 		{
	// 			FindGSSVOutChannelInfo(&m_SclInfo, pCtrl);
	// 		}
	// 		pCtrl->m_nChnCount = pCtrl->GetCount();
	// 	}
	// 	pCtrls->SetRead();
	// 	//}
	// 


}

BOOL CSclStation::FindGSSVControl(CExBaseList *pList)
{
	UINT nClassID = pList->GetClassID();

	if (   (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
		|| (nClassID == SCLIECCLASSID_CTRLS_GS_OUT)
		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_OUT) )
	{
		FindGSSVControl((CSclCtrls*)pList);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSclStation::FindGSSVControl(CSclIed *pIed, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut)
{
	//FindGSSVControl(&m_SclInfo, pIed, bGsIn, bGsOut, bSmvIn, bSmvOut);
}

void CSclStation::GetAll92Ref(CSclCtrlsSmvIn *pSMV92List)
{
	POS pos_ied = GetHeadPosition();
	POS pos_smv = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pCurSmvCtrl = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsSmvIn *pCtrlsSmv = NULL;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsSmv = pIed->GetSmvIns();
		pos_smv = pCtrlsSmv->GetHeadPosition();

		while(pos_smv)
		{
			pCurSmvCtrl = pCtrlsSmv->GetNext(pos_smv);

			if (pCurSmvCtrl->GetClassID() != SCLIECCLASSID_CTRL_SMV_IN)
			{
				continue;
			}

			if (pSMV92List->FindSclCtrlByAppID(((CSclCtrlSmvIn*)pCurSmvCtrl)->m_dwAppID) != NULL)
			{
				continue;
			}

			pSMV92List->AddTail(pCurSmvCtrl);
		}
	}
}

void CSclStation::GetAll92Ref(CSclCtrlsSmvOut *pSMV92List)
{
	POS pos_ied = GetHeadPosition();
	POS pos_smv = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pCurSmvCtrl = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsSmvOut *pCtrlsSmv = NULL;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsSmv = pIed->GetSmvOuts();
		pos_smv = pCtrlsSmv->GetHeadPosition();

		while(pos_smv)
		{
			pCurSmvCtrl = pCtrlsSmv->GetNext(pos_smv);

			if (pCurSmvCtrl->GetClassID() != SCLIECCLASSID_CTRL_SMV_OUT)
			{
				continue;
			}

			if (pSMV92List->FindSclCtrlByAppID(((CSclCtrlSmvOut*)pCurSmvCtrl)->m_dwAppID) != NULL)
			{
				continue;
			}

			pSMV92List->AddTail(pCurSmvCtrl);
		}
	}
}

void CSclStation::GetAllGinRef(CSclCtrlsGsIn *pGinList)
{
	POS pos_ied = GetHeadPosition();
	POS pos_gin = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pCurGinCtrl = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsGsIn *pCtrlsGsIn = NULL;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsGsIn = pIed->GetGsIns();
		pos_gin = pCtrlsGsIn->GetHeadPosition();

		while(pos_gin)
		{
			pCurGinCtrl = pCtrlsGsIn->GetNext(pos_gin);

			if (pCurGinCtrl->GetClassID() != SCLIECCLASSID_CTRL_GS_IN)
			{
				continue;
			}

			if (pGinList->FindSclCtrlByAppID(((CSclCtrlGsIn*)pCurGinCtrl)->m_dwAppID) != NULL)
			{
				continue;
			}

			pGinList->AddTail(pCurGinCtrl);
		}
	}
}

void CSclStation::AddIedsByGinParas(CExBaseList *pIedListRef,const CString &strMac,DWORD dwAppID)
{
	POS pos_ied = GetHeadPosition();
	CExBaseObject *p = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsGsIn *pCtrlsGsIn = NULL;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsGsIn = pIed->GetGsIns();

		if (pCtrlsGsIn->FindSclCtrlByAppID_DesMac(dwAppID,strMac) != NULL)
		{
			if (pIedListRef->FindByID(pIed->m_strID) == NULL)
			{
				pIedListRef->AddTail(pIed);
			}
		}
	}
}

void CSclStation::GetAllGoutRef(CSclCtrlsGsOut *pGoutList)
{
	POS pos_ied = GetHeadPosition();
	POS pos_gout = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pCurGoutCtrl = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsGsOut *pCtrlsGsOut = NULL;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsGsOut = pIed->GetGsOuts();
		pos_gout = pCtrlsGsOut->GetHeadPosition();

		while(pos_gout)
		{
			pCurGoutCtrl = pCtrlsGsOut->GetNext(pos_gout);

			if (pCurGoutCtrl->GetClassID() != SCLIECCLASSID_CTRL_GS_OUT)
			{
				continue;
			}

			if (pGoutList->FindSclCtrlByAppID(((CSclCtrlGsOut*)pCurGoutCtrl)->m_dwAppID) != NULL)
			{
				continue;
			}

			pGoutList->AddTail(pCurGoutCtrl);
		}
	}
}

CSclChGsOut* CSclStation::FindGoutCh(const CString &strFCDA_Path)
{
	POS pos_ied = GetHeadPosition();
	POS pos_gout = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pCurGoutCtrl = NULL;
	CExBaseObject *pCurGoutCh = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsGsOut *pCtrlsGsOut = NULL;
	CSclCtrlGsOut *pCtrlGsOut = NULL;
	CSclChGsOut* pSclChGsOut = NULL;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		if (strFCDA_Path.Find(p->m_strID) != 0)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsGsOut = pIed->GetGsOuts();
		pos_gout = pCtrlsGsOut->GetHeadPosition();

		while(pos_gout)
		{
			pCurGoutCtrl = pCtrlsGsOut->GetNext(pos_gout);

			if (pCurGoutCtrl->GetClassID() != SCLIECCLASSID_CTRL_GS_OUT)
			{
				continue;
			}

			pCtrlGsOut = (CSclCtrlGsOut *)pCurGoutCtrl;
			pCurGoutCh = pCtrlGsOut->FindByID(strFCDA_Path);

			if (pCurGoutCh != NULL)
			{
				pSclChGsOut = (CSclChGsOut*)pCurGoutCh;
				return pSclChGsOut;
			}
		}
	}

	return NULL;
}

void CSclStation::InitGoutCh_VirtualTerminals()
{
	POS pos_ied = GetHeadPosition();
	POS pos_gin = NULL;
	POS pos_ch = NULL;
	CExBaseObject *p = NULL;
	CExBaseObject *pCurGinCtrl = NULL;
	CExBaseObject *pCurGinCh = NULL;
	CSclIed *pIed = NULL;
	CSclCtrlsGsIn *pCtrlsGsIn = NULL;
	CSclCtrlsGsOut *pCtrlsGsOut = NULL;
	CSclCtrlGsIn *pCtrlGsIn = NULL;
	CSclChGsIn *pSclChGsIn = NULL;
	CSclChGsOut* pSclChGsOut = NULL;
	CString strInputPath;

	while (pos_ied != NULL)
	{
		p = GetNext(pos_ied);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		pCtrlsGsIn = pIed->GetGsIns();
		pos_gin = pCtrlsGsIn->GetHeadPosition();

		while(pos_gin)
		{
			pCurGinCtrl = pCtrlsGsOut->GetNext(pos_gin);

			if (pCurGinCtrl->GetClassID() != SCLIECCLASSID_CTRL_GS_IN)
			{
				continue;
			}

			pCtrlGsIn = (CSclCtrlGsIn *)pCurGinCtrl;
			pos_ch = pCtrlGsIn->GetHeadPosition();

			while(pos_ch)
			{
				pCurGinCh = pCtrlGsIn->GetNext(pos_ch);

				if (pCurGinCh->GetClassID() != SCLIECCLASSID_CH_GS_IN)
				{
					continue;
				}

				pSclChGsIn = (CSclChGsIn *)pCurGinCh;
				strInputPath.Format(_T("%s%s"),pIed->m_strID.GetString(),pSclChGsIn->m_strName.GetString());
				pSclChGsOut = FindGoutCh(pSclChGsIn->fcda_name);

				if (pSclChGsOut != NULL)
				{
					pSclChGsOut->m_astrGinChs.Add(strInputPath);
					pSclChGsOut->m_strGinPath = strInputPath;
				}
			}
		}
	}
}

BOOL CSclStation::IsDatasReadFinish(CExBaseList *pDatas)
{
	ASSERT(FALSE);

	return TRUE;
}

void CSclStation::InitAfterRead()
{
	InitSvGsIns();
}

void CSclStation::InitSvGsIns()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CSclIed *pIed = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pIed = (CSclIed *)p;
		InitGsIns(pIed->GetGsIns());
		InitSvIns(pIed->GetSmvIns());
	}
}

void CSclStation::InitGsIns(CSclCtrlsGsIn *pSclCtrlsGsIn)
{
	POS pos = pSclCtrlsGsIn->GetHeadPosition();
	CSclCtrlGsIn *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CSclCtrlGsIn *)pSclCtrlsGsIn->GetNext(pos);
		InitGsIn(pCtrl);
	}
}

void CSclStation::InitSvIns(CSclCtrlsSmvIn *pSclCtrlsSmvIn)
{
	POS pos = pSclCtrlsSmvIn->GetHeadPosition();
	CSclCtrlSmvIn *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CSclCtrlSmvIn *)pSclCtrlsSmvIn->GetNext(pos);
		InitSvIn(pCtrl);
	}
}

void CSclStation::InitGsIn(CSclCtrlGsIn *pSclCtrlGsIn)
{
//ZHJ
//	CSclIed *pIed = scl_GetIed(pSclCtrlGsIn);
	CSclCtrlGsOut *pGsOut = NULL;
	pGsOut = FindCrlByGooseRefPath_GooseOutput(pSclCtrlGsIn->m_strIedID, pSclCtrlGsIn->m_strgocbRef);
	ASSERT (pGsOut != NULL);

	if (pGsOut == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Ctrl: [%s][%s]"), pSclCtrlGsIn->m_strIedID.GetString(), pSclCtrlGsIn->m_strID.GetString());
		return;
	}

	POS pos = pSclCtrlGsIn->GetHeadPosition();
	CSclChGsIn *pCh = NULL;
	CSclChGsOut *pChGsOut = NULL;

	while (pos != NULL)
	{
		pCh = (CSclChGsIn *)pSclCtrlGsIn->GetNext(pos);
		pChGsOut = (CSclChGsOut*)pGsOut->FindByID(pCh->m_strID);

// 		if (pChGsOut == NULL)//zhouhj 20230615 删除此打印信息,影响解析速度
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error CH: [%s][%s][%s]"), pSclCtrlGsIn->m_strIedID.GetString(), pSclCtrlGsIn->m_strID.GetString(), pCh->m_strID.GetString());
// 		}

		pCh->m_pCfgDataRef = pChGsOut;
	}
}

void CSclStation::InitSvIn(CSclCtrlSmvIn *pSclCtrlSmvIn)
{
// 	CSclIed *pIed = scl_GetIed(pSclCtrlSmvIn);
	CSclCtrlSmvOut *pSmvOut = NULL;
	pSmvOut = FindSmvOutput(pSclCtrlSmvIn->iedExtName, pSclCtrlSmvIn->m_strID);
	ASSERT (pSmvOut != NULL);

	if (pSmvOut == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error Ctrl: [%s][%s]"), pSclCtrlSmvIn->iedExtName.GetString(), pSclCtrlSmvIn->m_strID.GetString());
		return;
	}

	POS pos = pSclCtrlSmvIn->GetHeadPosition();
	CSclChSmvIn *pCh = NULL;
	CSclChSmvOut *pChOut = NULL;

	while (pos != NULL)
	{
		pCh = (CSclChSmvIn *)pSclCtrlSmvIn->GetNext(pos);
		pChOut = (CSclChSmvOut*)pSmvOut->FindByID(pCh->m_strID);

// 		if (pChOut == NULL)  //zhouhj 20230615 删除此打印信息,影响解析速度
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error CH: [%s][%s][%s]"), pSclCtrlSmvIn->iedExtName.GetString(), pSclCtrlSmvIn->m_strID.GetString(), pCh->m_strID.GetString());
// 		}

		pCh->m_pCfgDataRef = pChOut;
	}
}
//////////////////////////////////////////////////////////////////////////
//Global Functions
CSclIed* scl_GetIed(CExBaseObject *p)
{
	CSclIed *pIed = (CSclIed*)p->GetAncestor(SCLIECCLASSID_IED);

	return pIed;
}

BOOL   scl_IsGsOutCh(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CH_GS_OUT;
}

BOOL   scl_IsGsInCh(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CH_GS_IN;
}
BOOL   scl_IsSmvOutCh(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CH_SMV_OUT;
}
BOOL   scl_IsSmvInCh(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CH_SMV_IN;
}

BOOL   scl_IsGsOuts(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CTRLS_GS_OUT;
}
BOOL   scl_IsGsIns(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CTRLS_GS_IN;
}
BOOL   scl_IsSmvOuts(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CTRLS_SMV_OUT;
}
BOOL   scl_IsSmvIns(CExBaseObject *p)
{
	return p->GetClassID() == SCLIECCLASSID_CTRLS_SMV_IN;
}

void scl_SetMac(unsigned char *pDest, unsigned char *pSrc)
{
	memcpy(pDest, pSrc, 6 * sizeof(unsigned char));
}

void scl_SetMac(CString &strMacDest, unsigned char *pSrc)
{
	strMacDest.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"), *pSrc, *(pSrc+1),
		*(pSrc+2),*(pSrc+3),*(pSrc+4),*(pSrc+5));
}

///////////////////////////////////////////////处理间隔程序//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSclIedRef::CSclIedRef()
{

}

CSclIedRef::~CSclIedRef()
{
}

long CSclIedRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CSclIedRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}


BOOL CSclIedRef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclIedRef *p = (CSclIedRef*)pDest;

	return TRUE;
}

CBaseObject* CSclIedRef::Clone()
{
	CSclIedRef *p = new CSclIedRef();
	Copy(p);
	return p;
}

///////////////////////////////////////////////
CSclBayVLevel::CSclBayVLevel()
{
	//初始化属性

	//初始化成员变量
}

CSclBayVLevel::~CSclBayVLevel()
{
}

long CSclBayVLevel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclBayVLevel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}


CExBaseObject* CSclBayVLevel::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclIedRefKey)
	{
		pNew = new CSclIedRef();
	}

	return pNew;
}

CExBaseObject* CSclBayVLevel::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CSCLIEDREF)
	{
		pNew = new CSclIedRef();
	}

	return pNew;
}


BOOL CSclBayVLevel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

	CSclBayVLevel *p = (CSclBayVLevel*)pDest;

	return TRUE;
}

CBaseObject* CSclBayVLevel::Clone()
{
	CSclBayVLevel *p = new CSclBayVLevel();
	Copy(p);
	return p;
}

//////////////////////////////////////////////

CSclBay::CSclBay()
{
	//初始化属性

	//初始化成员变量
}

CSclBay::~CSclBay()
{
}

long CSclBay::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclBay::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CSclBay::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclBayVLevelKey)
	{
		pNew = new CSclBayVLevel();
	}

	return pNew;
}

CExBaseObject* CSclBay::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CSCLBAYVLEVEL)
	{
		pNew = new CSclBayVLevel();
	}

	return pNew;
}

BOOL CSclBay::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

	CSclBay *p = (CSclBay*)pDest;

	return TRUE;
}

CBaseObject* CSclBay::Clone()
{
	CSclBay *p = new CSclBay();
	Copy(p);
	return p;
}

