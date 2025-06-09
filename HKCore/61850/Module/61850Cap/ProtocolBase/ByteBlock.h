#pragma once

#include "BbInffor.h"


class CByteBlock : public CExBaseList
{
public:
	CByteBlock(void);
	virtual ~CByteBlock(void);

	CBbInffor* AddBbInfor(const CString &strID, BYTE val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, short val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, WORD val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, DWORD val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, long val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, float val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, double val, long nDxBegin = -1, long nDxEnd = -1)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
		AddNewChild(pInfor);
		return pInfor;
	}
	CBbInffor* AddBbInfor(const CString &strID, const CString &val)
	{
		CBbInffor *pInfor = new CBbInffor(strID, val);
		AddNewChild(pInfor);
		return pInfor;
	}
// 	CBbInffor* AddBbInfor(const CString &strID, TIME64 val, long nDxBegin = -1, long nDxEnd = -1)
// 	{
// 		CBbInffor *pInfor = new CBbInffor(strID, val, nDxBegin, nDxEnd);
// 		AddNewChild(pInfor);
// 		return pInfor;
// 	}

//����
public:
	long  m_nIndex;   //�ֽڿ��ڹ�Լ֡������λ��
	long  m_nLength;  //�ֽڿ�ĳ���
	BOOL  m_bUseData;
	long  m_nData;
	
protected:
	
public:
	//��������
	virtual UINT GetClassID(){return STPROTOCOLCLASSID_BYTEBLOCK;};
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
	virtual void SetData(long nData, BOOL bUseData=TRUE)
	{
		m_nData = nData;
		m_bUseData = bUseData;
	}
};


class CByteBlocks : public CExBaseList
{
public:
	CByteBlocks(void);
	virtual ~CByteBlocks(void);
	//��������
	virtual UINT GetClassID(){return STPROTOCOLCLASSID_BYTEBLOCKS;};
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	//////////////////////////////////////////////////////////////////////////
	//��ӿ飬���Ϊ��������Ӷ���
	virtual CByteBlock* AddNewByteBlock(const CString &strID, long nLen, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, BYTE val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, short val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, WORD val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, long val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, long val, long nLen, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, DWORD val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, float val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, double val, long nIndex);
	virtual CByteBlock* AddByteBlockByValue(const CString &strID, const CString &val, long nLen, long nIndex);
	virtual CByteBlock* AddByteBlockByValue_MAC(const CString &strID, BYTE *val, long nIndex);

	//////////////////////////////////////////////////////////////////////////
	//��Ӽ��Ͽ�Ϊ��ǰ������Ӷ�����
	virtual CByteBlocks* AddNewByteBlocks(const CString &strID);
	virtual CByteBlock* AddNewByteBlockEx(const CString &strID, long nLen, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, BYTE val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, short val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, WORD val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, long val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, long val, long nLen, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, DWORD val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, float val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, double val, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx(const CString &strID, const CString &val, long nLen, long nIndex);
	virtual CByteBlock* AddByteBlockByValueEx_MAC(const CString &strID, BYTE *val, long nIndex);

	virtual void AppendToDetail(CExBaseList *pList);

	//////////////////////////////////////////////////////////////////////////
	//Ϊ��ǰ��m_pCurrByteBlock�����Ϣ
	CBbInffor* AddBbInfor(const CString &strID, BYTE val, long nDxBegin = -1, long nDxEnd = -1);
	CBbInffor* AddBbInfor(const CString &strID, short val, long nDxBegin = -1, long nDxEnd = -1);
	CBbInffor* AddBbInfor(const CString &strID, long val, long nDxBegin = -1, long nDxEnd = -1);
	CBbInffor* AddBbInfor(const CString &strID, float val, long nDxBegin = -1, long nDxEnd = -1);
	CBbInffor* AddBbInfor(const CString &strID, double val, long nDxBegin = -1, long nDxEnd = -1);
	CBbInffor* AddBbInfor(const CString &strID, const CString &val);

protected:
	CByteBlocks *m_pCurrByteBlocks;
	CByteBlock *m_pCurrByteBlock;

};