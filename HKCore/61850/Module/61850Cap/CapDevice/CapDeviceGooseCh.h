//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceGooseCh.h  CCapDeviceGooseCh

#pragma once

#include "CapDeviceChBase.h"

#include <math.h>


inline CString st_GetGooseChType(UINT nType, long nLen)
{
	switch (nType)
	{
	case 0x83://����
		return _T("����");
		break;
	case 0x84://˫��
		if (nLen == 2)
		{
			return _T("˫��");
		}
		else
		{
			return _T("Ʒ��");
		}
		break;
	case 0x85://ö��
		return _T("ö��");
		break;
	case 0x86://UINT
		return _T("UINT");
		break;
	case 0x91://ʱ��
		return _T("ʱ��");
		break;
	case 0x87://����
		return _T("����");
		break;
	default:
		return _T("����");
		break;
	}

	return _T("����");
}



class CCapDeviceGooseCh : public CCapDeviceChBase
{
public:
	CCapDeviceGooseCh();
	virtual ~CCapDeviceGooseCh();


	//UINT m_nChType;
	CString m_strChTypeName;

//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_GOOSECH;};

//˽�г�Ա����
private:
	

//˽�г�Ա�������ʷ���
public:
	void InitChTypeName()
	{
		m_strChTypeName = st_GetGooseChType(m_nChType, m_nLength);
	}

};
