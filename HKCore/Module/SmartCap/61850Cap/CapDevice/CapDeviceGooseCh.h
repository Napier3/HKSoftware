//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceGooseCh.h  CCapDeviceGooseCh

#pragma once

#include "CapDeviceChBase.h"
#include "../../../System/VariantData.h"
#include <math.h>


inline CString st_GetGooseChType(UINT nType, long nLen)
{
	switch (nType)
	{
	case 0x83://����
		return _T("����");
		break;
	case 0x84://˫��
// 		if (nLen == 2)//20220623 zhouhj �����ֽڳ����޷��ж�˫�㡢Ʒ�ʵ���Ϣ
// 		{
// 			return _T("˫��");
// 		}
// 		else if(nLen == 3)//13λ�̶�ΪƷ��,����Ϊλ��  20220613 zhouhj
// 		{
// 			return _T("Ʒ��");
// 		}
// 		else
		{
			return _T("λ��");
		}
		break;
	case 0x85://ö��
		if (nLen == 2)
		{
			return _T("ö��");
		} 
		else
		{
			return _T("INT");
		}
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
	case 0xA2://�ṹ��  20220615 zhouhj
		return _T("�ṹ");
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

	CVariantData m_oVar;	//Gooseͨ��ֵ
//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_GOOSECH;};
	virtual void InitChannel(CIecCfgDataChBase *pIecCfgDataCh);
	virtual void InitChannel(CDvmData *pChData);
	virtual void InitChannelAttrs(CDvmData *pChData);

	//20220607 ����ͨ������
	virtual void UpdateChTypeAndLength(WORD wChType,WORD wLength);
	CString GetIecCfgChDataType();

//˽�г�Ա����
private:
	
//˽�г�Ա�������ʷ���
public:
	void InitChTypeName()
	{
		m_strChTypeName = st_GetGooseChType(m_nChType, m_nLength);
	}

};
