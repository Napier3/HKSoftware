// RtAttrSpyConfig.h: interface for the CRtAttrSpyConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTATTRSPYCONFIG_H__88CD870B_D26B_49C1_B6EA_C34E6C5F0637__INCLUDED_)
#define AFX_RTATTRSPYCONFIG_H__88CD870B_D26B_49C1_B6EA_C34E6C5F0637__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MODULE/BASECLASS/ExBaseObject.h"
#include "RecordTestClassDef.h"

#define AttrType_Freq   0
#define AttrType_Effec  1
#define AttrType_Phase  2

class CRtAttrSpyConfig;

typedef struct ATTRSPY
{
	char strAttrID[50];
	char strAttrName[50];
	UINT nAttributeID;	
	long nSpyState;
	long nAttrType;//属性的类型，是频率，有效值(广义上的)还是相位(广义上的)
	BOOL IsAttrFreq()  {  return nAttrType == AttrType_Freq;  }
	BOOL IsAttrEffec() {  return nAttrType == AttrType_Effec; }
	BOOL IsAttrPhase() {  return nAttrType == AttrType_Phase; }
	CRtAttrSpyConfig *pParent;
}RTATTRSPY, *PRTATTRSPY;//描述了一个属性值

//描述了一个计算一次的属性值，监视频率需要计算一次，监视有效值和相位需要计算一次
class CRtAttrSpyConfig : public CExBaseObject  
{
public:
	long m_nSpyState;
	
	RTATTRSPY m_oAttrFreq;//频率
	RTATTRSPY m_oAttrEffec;//有效值（总有效值、基波、谐波）
	RTATTRSPY m_oAttrPhase;//相位（总相位、基波、谐波）
public:
	CRtAttrSpyConfig();
	virtual ~CRtAttrSpyConfig();

	virtual UINT GetClassID()				  {		return RTCLASSID_ATTRSPYCONFIG;   }	
	void SetAttrSpyState(long nSpyState) 	  {	    m_nSpyState = nSpyState;	 }

	//判断属性值是否为谐波
	BOOL IsAttrHarm();

	//判断属性值是否为频率
	BOOL IsAttrFrequency();

	//判断属性值是否为有效值
	BOOL IsAttrSpyEffec(CString strAttrID);

	//判断属性值是否为相位
	BOOL IsAttrSpyPhase(CString strAttrID);
};

#endif // !defined(AFX_RTATTRSPYCONFIG_H__88CD870B_D26B_49C1_B6EA_C34E6C5F0637__INCLUDED_)
