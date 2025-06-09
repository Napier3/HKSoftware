//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceGooseCh.h  CCapDeviceGooseCh

#pragma once

#include "CapDeviceChBase.h"
#include "../../../System/VariantData.h"
#include <math.h>


inline CString st_GetGooseChType(UINT nType, long nLen)
{
	switch (nType)
	{
	case 0x83://单点
		return _T("单点");
		break;
	case 0x84://双点
// 		if (nLen == 2)//20220623 zhouhj 根据字节长度无法判断双点、品质等信息
// 		{
// 			return _T("双点");
// 		}
// 		else if(nLen == 3)//13位固定为品质,其它为位串  20220613 zhouhj
// 		{
// 			return _T("品质");
// 		}
// 		else
		{
			return _T("位串");
		}
		break;
	case 0x85://枚举
		if (nLen == 2)
		{
			return _T("枚举");
		} 
		else
		{
			return _T("INT");
		}
		break;
	case 0x86://UINT
		return _T("UINT");
		break;
	case 0x91://时间
		return _T("时间");
		break;
	case 0x87://浮点
		return _T("浮点");
		break;
	case 0xA2://结构体  20220615 zhouhj
		return _T("结构");
		break;
	default:
		return _T("单点");
		break;
	}

	return _T("单点");
}

class CCapDeviceGooseCh : public CCapDeviceChBase
{
public:
	CCapDeviceGooseCh();
	virtual ~CCapDeviceGooseCh();


	//UINT m_nChType;
	CString m_strChTypeName;

	CVariantData m_oVar;	//Goose通道值
//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_GOOSECH;};
	virtual void InitChannel(CIecCfgDataChBase *pIecCfgDataCh);
	virtual void InitChannel(CDvmData *pChData);
	virtual void InitChannelAttrs(CDvmData *pChData);

	//20220607 更新通道类型
	virtual void UpdateChTypeAndLength(WORD wChType,WORD wLength);
	CString GetIecCfgChDataType();

//私有成员变量
private:
	
//私有成员变量访问方法
public:
	void InitChTypeName()
	{
		m_strChTypeName = st_GetGooseChType(m_nChType, m_nLength);
	}

};
