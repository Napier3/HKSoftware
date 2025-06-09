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
	long nAttrType;//���Ե����ͣ���Ƶ�ʣ���Чֵ(�����ϵ�)������λ(�����ϵ�)
	BOOL IsAttrFreq()  {  return nAttrType == AttrType_Freq;  }
	BOOL IsAttrEffec() {  return nAttrType == AttrType_Effec; }
	BOOL IsAttrPhase() {  return nAttrType == AttrType_Phase; }
	CRtAttrSpyConfig *pParent;
}RTATTRSPY, *PRTATTRSPY;//������һ������ֵ

//������һ������һ�ε�����ֵ������Ƶ����Ҫ����һ�Σ�������Чֵ����λ��Ҫ����һ��
class CRtAttrSpyConfig : public CExBaseObject  
{
public:
	long m_nSpyState;
	
	RTATTRSPY m_oAttrFreq;//Ƶ��
	RTATTRSPY m_oAttrEffec;//��Чֵ������Чֵ��������г����
	RTATTRSPY m_oAttrPhase;//��λ������λ��������г����
public:
	CRtAttrSpyConfig();
	virtual ~CRtAttrSpyConfig();

	virtual UINT GetClassID()				  {		return RTCLASSID_ATTRSPYCONFIG;   }	
	void SetAttrSpyState(long nSpyState) 	  {	    m_nSpyState = nSpyState;	 }

	//�ж�����ֵ�Ƿ�Ϊг��
	BOOL IsAttrHarm();

	//�ж�����ֵ�Ƿ�ΪƵ��
	BOOL IsAttrFrequency();

	//�ж�����ֵ�Ƿ�Ϊ��Чֵ
	BOOL IsAttrSpyEffec(CString strAttrID);

	//�ж�����ֵ�Ƿ�Ϊ��λ
	BOOL IsAttrSpyPhase(CString strAttrID);
};

#endif // !defined(AFX_RTATTRSPYCONFIG_H__88CD870B_D26B_49C1_B6EA_C34E6C5F0637__INCLUDED_)
