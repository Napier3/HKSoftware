// MemBufferDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFERDEF_H__)
#define _MEMBUFFERDEF_H__

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"

#define MEMCLASSID_BUFFERBASE     (CLASSID_BASECLASS+0X00100000)

#define MEMCLASSID_USHORT         (MEMCLASSID_BUFFERBASE+0X00000001)     
#define MEMCLASSID_LONG           (MEMCLASSID_BUFFERBASE+0X00000002)     
#define MEMCLASSID_FLOAT          (MEMCLASSID_BUFFERBASE+0X00000003)     
#define MEMCLASSID_DOUBLE         (MEMCLASSID_BUFFERBASE+0X00000004)     
#define MEMCLASSID_CHANNEL        (MEMCLASSID_BUFFERBASE+0X00000005)     
#define MEMCLASSID_MNGR           (MEMCLASSID_BUFFERBASE+0X00000006)     

class CMemBufferInterface : public CExBaseObject
{
public:
	virtual long GetDataLength() = 0;
	virtual long GetDataFillBeginPosition() = 0;
	virtual long GetBufferLength() = 0;
	virtual void Init() = 0;
	virtual void OffsetDataFillBeginPosition(long nLen) = 0;

	UINT m_nMemBufferTypeID;
};

//25次谐波，RTATTRIBUTECAL_MIN_BUFFER_LEN点对应的过零点次数为250次
//取较大的裕度
#define  MAX_FREQ_ZERO_POS_BUFFER  400
#define  MAX_FREQ_ZERO_POS_COUNT   50

#define MIN_CIRCLRPOINTS 10 //一个周期的最少点数
#define MEMBUFFER_LENGTH_EX 200

//参数计算过滤用
#define RT_FILTER_BUFFER_LEN   81
#define RT_FILTER_DATA_LEN_PREV 40
#define RT_FILTER_DATA_LEN_NEXT 40

//按照额定频率
#define RTATTRIBUTECAL_MIN_BUFFER_LEN       (6000+RT_FILTER_BUFFER_LEN) //20000
#define RTATTRIBUTECAL_MIN_STARTUP_BUFLEN   (18000)


#endif // !defined(_MEMBUFFERDEF_H__)
