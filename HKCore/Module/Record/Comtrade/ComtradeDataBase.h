// ComtradeDataBase.h: interface for the CComtradeDataBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMTRADEDATABASE_H__029B100F_2BAD_4A23_89F5_99612E22745F__INCLUDED_)
#define AFX_COMTRADEDATABASE_H__029B100F_2BAD_4A23_89F5_99612E22745F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RecordGlobalDefine.h"
#include "../RtMemBuffer/MemBuffer.h"
#include "ComtradeFileGlobal.h"

class CComtradeDataBase  : public CExBaseObject
{
public:
	CComtradeDataBase();
	virtual ~CComtradeDataBase();

public:	
	unsigned short* m_pnAttachBuffer;
	long m_nChannelIndex;	//ͨ������ 1	
	//CString m_strName;		//ͨ������ 2
	CString m_strPhaseID;	//���	   3
	CString m_strCcbm;		//����Ԫ�� 4
	BOOL m_bUsed;

	//2020-07-26ȥ��m_strDataFile,��m_nTotalPt��ʾ�Ƿ������ݣ���Կ�����ͨ��
	long m_nTotalPoints;  //m_nTotalPt  ΪʲôҪ��m_nTotalPt�����ܺ�m_nTotalPointsͳһ�أ�
	//CString m_strDataFile;//��ͨ����Ӧ��data�ļ��е�ֵ

    virtual void GetChanInfor(CString* pstrParse,long nOffSet = 0)
    {
#ifdef _PSX_IDE_QT_
        (void)pstrParse;
        (void)nOffSet;
#endif
    }
	virtual void SaveChanInfo(CString& strInfor);	
	virtual BOOL IsAnalogData()			{	return TRUE;				}
	virtual unsigned short* GetBuffer()	{	return m_pnAttachBuffer;	}
	virtual void ClearBuffer()	;
	virtual void InitBuffer_Circle(long nDataFileType,long nTotalPoints);//zhouhj 20210918 �����ݻط�,ѭ������ʱ���г�ʼ��
	void AllocBuffer(long nTotalBufferLenth);
	void AttachBuffer(unsigned short* pBuffer);

	CMemBuffer_UShort* GetMemBuffer_UShort()	{	return &m_oMemBuffer_UShort;	}
	long GetMemBuffer_UShortNum(){return m_oMemBuffer_UShort.GetDataLength();}
    virtual double CalValue(short vValue)
    {
#ifdef _PSX_IDE_QT_
        (void)vValue;
#endif
        return 0;
    }
private:
	BOOL m_bBufferAllocOwn;
	CMemBuffer_UShort m_oMemBuffer_UShort;

public:
	//������ͨ����ʾ�����ĺ���
	virtual void GetCountBeforeBind(int*ipBind);
    virtual void GetCHIndexBeforeBind(int*ipVoltage,int*ipCurrent,BOOL bUse)
    {
#ifdef _PSX_IDE_QT_
        (void)ipVoltage;
        (void)ipCurrent;
        (void)bUse;
#endif
    };
	//���ͨ���Ĳ����������Сֵ
    virtual void GetCHSampMaxMiVal(float &fMaxVal,float &fMinVal)
    {
#ifdef _PSX_IDE_QT_
        (void)fMaxVal;
        (void)fMinVal;
#endif
    };
	//xupf
public:
	virtual UINT GetClassID() {    return GLOBALCLASSID_CCOMTRADEDATABASE;   }
	virtual BSTR GetXmlElementKey()  {      return CComtradeFileXmlRWKeys::CComtradeDataBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);

	void InitByHexDataString(const CString &strData);
	void InitByHexDataString(const char *strData);
	void InitByHexDataString(const wchar_t *strData);
	long GetHexDataString(CString &strData);
	long GetHexDataString(char *strData);

	//2024-01-09 wuxinyi �༭��������
	virtual void InsertCyclePoints(long nBeginPos, long nEndPos, long nInsertPos, int nCycleIndex, int nDataFileType);
	virtual void DeletePoints(long nBeginPos, long nEndPos, int nDataFileType);
};


//////////////////////////////////////////////////////////////////////////
//CComtradeDataBaseList
class CComtradeDataBaseList : public CExBaseList
{
public:
	CComtradeDataBaseList();
	virtual ~CComtradeDataBaseList();

public:
	virtual UINT GetClassID() {    return CMTRDCLASSID_CHANNELS;   }

};

#endif // !defined(AFX_COMTRADEDATABASE_H__029B100F_2BAD_4A23_89F5_99612E22745F__INCLUDED_)
