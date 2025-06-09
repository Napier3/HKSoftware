//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgAdvanceException.cpp  CIecCfgAdvanceException


#include "stdafx.h"
#include "IecCfgAdvanceException.h"
#include "IecCfgSmvDataBase.h"
#include "IecCfgDataSmvChBase.h"

CIecCfgAdvanceException::CIecCfgAdvanceException()
{
	//初始化属性
	m_nExceptionType = 0;
	m_nSerialNumErr = 0;
	m_nFrameLossGap = 0;
	m_nFrameLossPoints = 0;
	m_nSynGap = 0;
	m_nSynPoints = 0;
	m_nQualityGap = 0;
	m_nQualityPoints = 0;
	m_nQualityValue = 0;
	m_nSerialJmpGap = 0;
	m_nSerialJmpPoints = 0;
	m_nSerialJmpStep = 0;
	m_nFaultValGap = 0;
	m_nFaultValPoints = 0;
	m_nFaultValRate = 0;
	m_nExceptionBeginIndex = 0;
	m_nExceptionLimit = 0;
	m_nExceptionCount = 0;

	//初始化成员变量
}

CIecCfgAdvanceException::~CIecCfgAdvanceException()
{
}

long CIecCfgAdvanceException::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strExceptionTypeKey, oNode, m_nExceptionType);
	xml_GetAttibuteValue(pXmlKeys->m_strSerialNumErrKey, oNode, m_nSerialNumErr);
	xml_GetAttibuteValue(pXmlKeys->m_strFrameLossGapKey, oNode, m_nFrameLossGap);
	xml_GetAttibuteValue(pXmlKeys->m_strFrameLossPointsKey, oNode, m_nFrameLossPoints);
	xml_GetAttibuteValue(pXmlKeys->m_strSynGapKey, oNode, m_nSynGap);
	xml_GetAttibuteValue(pXmlKeys->m_strSynPointsKey, oNode, m_nSynPoints);
	xml_GetAttibuteValue(pXmlKeys->m_strQualityGapKey, oNode, m_nQualityGap);
	xml_GetAttibuteValue(pXmlKeys->m_strQualityPointsKey, oNode, m_nQualityPoints);
	xml_GetAttibuteValue(pXmlKeys->m_strQualityValueKey, oNode, m_nQualityValue);
	xml_GetAttibuteValue(pXmlKeys->m_strSerialJmpGapKey, oNode, m_nSerialJmpGap);
	xml_GetAttibuteValue(pXmlKeys->m_strSerialJmpPointsKey, oNode, m_nSerialJmpPoints);
	xml_GetAttibuteValue(pXmlKeys->m_strSerialJmpStepKey, oNode, m_nSerialJmpStep);
	xml_GetAttibuteValue(pXmlKeys->m_strFaultValGapKey, oNode, m_nFaultValGap);
	xml_GetAttibuteValue(pXmlKeys->m_strFaultValPointsKey, oNode, m_nFaultValPoints);
	xml_GetAttibuteValue(pXmlKeys->m_strFaultValRateKey, oNode, m_nFaultValRate);
	xml_GetAttibuteValue(pXmlKeys->m_strExceptionBeginIndexKey, oNode, m_nExceptionBeginIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strExceptionLimitKey, oNode, m_nExceptionLimit);
	xml_GetAttibuteValue(pXmlKeys->m_strExceptionCountKey, oNode, m_nExceptionCount);
	return 0;
}

long CIecCfgAdvanceException::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strExceptionTypeKey, oElement, m_nExceptionType);
	xml_SetAttributeValue(pXmlKeys->m_strSerialNumErrKey, oElement, m_nSerialNumErr);
	xml_SetAttributeValue(pXmlKeys->m_strFrameLossGapKey, oElement, m_nFrameLossGap);
	xml_SetAttributeValue(pXmlKeys->m_strFrameLossPointsKey, oElement, m_nFrameLossPoints);
	xml_SetAttributeValue(pXmlKeys->m_strSynGapKey, oElement, m_nSynGap);
	xml_SetAttributeValue(pXmlKeys->m_strSynPointsKey, oElement, m_nSynPoints);
	xml_SetAttributeValue(pXmlKeys->m_strQualityGapKey, oElement, m_nQualityGap);
	xml_SetAttributeValue(pXmlKeys->m_strQualityPointsKey, oElement, m_nQualityPoints);
	xml_SetAttributeValue(pXmlKeys->m_strQualityValueKey, oElement, m_nQualityValue);
	xml_SetAttributeValue(pXmlKeys->m_strSerialJmpGapKey, oElement, m_nSerialJmpGap);
	xml_SetAttributeValue(pXmlKeys->m_strSerialJmpPointsKey, oElement, m_nSerialJmpPoints);
	xml_SetAttributeValue(pXmlKeys->m_strSerialJmpStepKey, oElement, m_nSerialJmpStep);
	xml_SetAttributeValue(pXmlKeys->m_strFaultValGapKey, oElement, m_nFaultValGap);
	xml_SetAttributeValue(pXmlKeys->m_strFaultValPointsKey, oElement, m_nFaultValPoints);
	xml_SetAttributeValue(pXmlKeys->m_strFaultValRateKey, oElement, m_nFaultValRate);
	xml_SetAttributeValue(pXmlKeys->m_strExceptionBeginIndexKey, oElement, m_nExceptionBeginIndex);
	xml_SetAttributeValue(pXmlKeys->m_strExceptionLimitKey, oElement, m_nExceptionLimit);
	xml_SetAttributeValue(pXmlKeys->m_strExceptionCountKey, oElement, m_nExceptionCount);
	return 0;
}

BOOL CIecCfgAdvanceException::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgAdvanceException *p = (CIecCfgAdvanceException*)pObj;

	if(m_nExceptionType != p->m_nExceptionType)
	{
		return FALSE;
	}

	if(m_nSerialNumErr != p->m_nSerialNumErr)
	{
		return FALSE;
	}

	if(m_nFrameLossGap != p->m_nFrameLossGap)
	{
		return FALSE;
	}

	if(m_nFrameLossPoints != p->m_nFrameLossPoints)
	{
		return FALSE;
	}

	if(m_nSynGap != p->m_nSynGap)
	{
		return FALSE;
	}

	if(m_nSynPoints != p->m_nSynPoints)
	{
		return FALSE;
	}

	if(m_nQualityGap != p->m_nQualityGap)
	{
		return FALSE;
	}

	if(m_nQualityPoints != p->m_nQualityPoints)
	{
		return FALSE;
	}

	if(m_nQualityValue != p->m_nQualityValue)
	{
		return FALSE;
	}

	if(m_nSerialJmpGap != p->m_nSerialJmpGap)
	{
		return FALSE;
	}

	if(m_nSerialJmpPoints != p->m_nSerialJmpPoints)
	{
		return FALSE;
	}

	if(m_nSerialJmpStep != p->m_nSerialJmpStep)
	{
		return FALSE;
	}

	if(m_nFaultValGap != p->m_nFaultValGap)
	{
		return FALSE;
	}

	if(m_nFaultValPoints != p->m_nFaultValPoints)
	{
		return FALSE;
	}

	if(m_nFaultValRate != p->m_nFaultValRate)
	{
		return FALSE;
	}

	if(m_nExceptionBeginIndex != p->m_nExceptionBeginIndex)
	{
		return FALSE;
	}

	if(m_nExceptionLimit != p->m_nExceptionLimit)
	{
		return FALSE;
	}

	if(m_nExceptionCount != p->m_nExceptionCount)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgAdvanceException::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgAdvanceException *p = (CIecCfgAdvanceException*)pDest;

	p->m_nExceptionType = m_nExceptionType;
	p->m_nSerialNumErr = m_nSerialNumErr;
	p->m_nFrameLossGap = m_nFrameLossGap;
	p->m_nFrameLossPoints = m_nFrameLossPoints;
	p->m_nSynGap = m_nSynGap;
	p->m_nSynPoints = m_nSynPoints;
	p->m_nQualityGap = m_nQualityGap;
	p->m_nQualityPoints = m_nQualityPoints;
	p->m_nQualityValue = m_nQualityValue;
	p->m_nSerialJmpGap = m_nSerialJmpGap;
	p->m_nSerialJmpPoints = m_nSerialJmpPoints;
	p->m_nSerialJmpStep = m_nSerialJmpStep;
	p->m_nFaultValGap = m_nFaultValGap;
	p->m_nFaultValPoints = m_nFaultValPoints;
	p->m_nFaultValRate = m_nFaultValRate;
	p->m_nExceptionBeginIndex = m_nExceptionBeginIndex;
	p->m_nExceptionLimit = m_nExceptionLimit;
	p->m_nExceptionCount = m_nExceptionCount;
	return TRUE;
}

CBaseObject* CIecCfgAdvanceException::Clone()
{
	CIecCfgAdvanceException *p = new CIecCfgAdvanceException();
	Copy(p);
	return p;
}

DWORD CIecCfgAdvanceException::GetFaultType()
{
	switch (m_nExceptionType)
	{
	case CFG_EXCEPTION_XHPC://FT2	smpCount offset value (4 bytes)
		return 0x04;
	case CFG_EXCEPTION_DZCS://FT0	lost frame interval (2 bytes)
		return 0x01;
	case CFG_EXCEPTION_TBCS://FT3	synchronization frame interval (2 bytes)
		return 0x08;
	case CFG_EXCEPTION_PZCS://FT4	fault quality frame
		return 0x10;
	case CFG_EXCEPTION_XHTB://FT1	resending frame
		return 0x20;
	case CFG_EXCEPTION_CZCS://FT6	fault value frame
		return 0x40;
	case 7://FT5	fault smpCnt frame
		return 0x02;
	default:
		return 0x00;
	}

}

//FT6	FT5	FT4	FT3	FT2	FT1	FT0
DWORD CIecCfgAdvanceException::GetFaultInteval()
{
	switch (m_nExceptionType)
	{
	case CFG_EXCEPTION_XHPC://FT2	smpCount offset value (4 bytes)
		return m_nSerialNumErr;
	case CFG_EXCEPTION_DZCS://FT0	lost frame interval (2 bytes)
		return m_nFrameLossGap;
	case CFG_EXCEPTION_TBCS://FT3	synchronization frame interval (2 bytes)
		return m_nSynGap;
	case CFG_EXCEPTION_PZCS://FT4	fault quality frame
		return m_nQualityGap;
	case CFG_EXCEPTION_XHTB://FT1	resending frame
		return m_nSerialJmpGap;
	case CFG_EXCEPTION_CZCS://FT6	fault value frame
		return m_nFaultValGap;
	case 7://FT5	fault smpCnt frame
		return 0;
	default:
		return 0x00;
	}

	return 0;
}

DWORD CIecCfgAdvanceException::GetFaultCount()
{
	switch (m_nExceptionType)
	{
	case CFG_EXCEPTION_XHPC://FT2	smpCount offset value (4 bytes)
		return m_nFrameLossPoints;
	case CFG_EXCEPTION_DZCS://FT0	lost frame interval (2 bytes)
		return m_nSynPoints;
	case CFG_EXCEPTION_TBCS://FT3	synchronization frame interval (2 bytes)
		return m_nSynPoints;
	case CFG_EXCEPTION_PZCS://FT4	fault quality frame
		return m_nQualityPoints;
	case CFG_EXCEPTION_XHTB://FT1	resending frame
		return m_nSerialJmpPoints;
	case CFG_EXCEPTION_CZCS://FT6	fault value frame
		return m_nFaultValPoints;
	case 7://FT5	fault smpCnt frame
		return 0;
	default:
		return 0x00;
	}
}

DWORD CIecCfgAdvanceException::GetFaultValue()
{
	switch (m_nExceptionType)
	{
	case CFG_EXCEPTION_XHPC://FT2	smpCount offset value (4 bytes)
		return m_nSerialNumErr;
	case CFG_EXCEPTION_DZCS://FT0	lost frame interval (2 bytes)
		return 0;
	case CFG_EXCEPTION_TBCS://FT3	synchronization frame interval (2 bytes)
		return 0;
	case CFG_EXCEPTION_PZCS://FT4	fault quality frame
		return m_nQualityValue;
	case CFG_EXCEPTION_XHTB://FT1	resending frame
		return m_nSerialJmpStep;
	case CFG_EXCEPTION_CZCS://FT6	fault value frame
		return m_nFaultValRate;
	case 7://FT5	fault smpCnt frame
		return 0;
	default:
		return 0x00;
	}
}

DWORD CIecCfgAdvanceException::GetFaultChannels(BYTE *byteChs)
{
	CIecCfgSmvDataBase *pSmvDataBase = (CIecCfgSmvDataBase*)GetParent();
	CIecCfgChsBase *pChs = pSmvDataBase->m_pCfgChs;
	POS pos = pChs->GetHeadPosition();
	CIecCfgDataSmvChBase *pSmvCh = NULL;
	long nByteIndex = 0;
	long nChIndex = 0;
	long nBitIndex = 0;

	while (pos != NULL)
	{
		CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pChs->GetNext(pos);
		nByteIndex = nChIndex / 8;
		nBitIndex = nChIndex % 8;

		if (pSmvCh->m_nUseException)
		{
			byteChs[nByteIndex] |= (1 << nBitIndex);
		}

		nChIndex++;
	}

	return nChIndex;
}

