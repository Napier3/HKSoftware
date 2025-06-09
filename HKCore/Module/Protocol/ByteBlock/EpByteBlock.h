#pragma once

#include "..\EpGlobalDefine.h"
#include "EpBbInffor.h"


class CEpByteBlock : public CExBaseList
{
public:
	CEpByteBlock(void);
	virtual ~CEpByteBlock(void);

	CEpBbInffor* AddBbInfor(const CString &strID, BYTE &val, long nDxBegin, long nDxEnd = -1)
	{
		CEpBbInffor *pInfor = new CEpBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CEpBbInffor* AddBbInfor(const CString &strID, short &val, long nDxBegin, long nDxEnd = -1)
	{
		CEpBbInffor *pInfor = new CEpBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CEpBbInffor* AddBbInfor(const CString &strID, long &val, long nDxBegin, long nDxEnd = -1)
	{
		CEpBbInffor *pInfor = new CEpBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CEpBbInffor* AddBbInfor(const CString &strID, float &val, long nDxBegin, long nDxEnd = -1)
	{
		CEpBbInffor *pInfor = new CEpBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CEpBbInffor* AddBbInfor(const CString &strID, double &val, long nDxBegin, long nDxEnd = -1)
	{
		CEpBbInffor *pInfor = new CEpBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CEpBbInffor* AddBbInfor(const CString &strID, EPTIME64 &val, long nDxBegin, long nDxEnd = -1)
	{
		CEpBbInffor *pInfor = new CEpBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}

//����
public:
	long  m_nIndex;   //�ֽڿ��ڹ�Լ֡������λ��
	long  m_nLength;  //�ֽڿ�ĳ���
	BOOL  m_bUseData;
	long  m_nData;
	
protected:
	
public:
	//��������
	virtual UINT GetClassID(){return EPCLASSID_BYTEBLOCK;};
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual void SetData(long nData, BOOL bUseData=TRUE)
	{
		m_nData = nData;
		m_bUseData = bUseData;
	}
};
