#ifndef TMT_ADJUST_SYS_PARAMETER_BINARY_SERIALIZE_H
#define TMT_ADJUST_SYS_PARAMETER_BINARY_SERIALIZE_H

//2020-10-21  lijunqing 
#include "tmt_adjust_sys_parameter.h"


/*
接口使用示例：

//定义缓冲区指针
BYTE *pszAdjSysPara = NULL;   
long nDestLen = 0;

//将选中的模块内存数据，串行化到缓冲区中，即返回到pszAdjSysPara中，nDestLen表示数据的长度
stt_binary_serialize_write(g_theDeviceSystemParameter->m_oModules[0], &pszAdjSysPara, nDestLen, true);

//从二进制内存数据中，获取模块系数数据
STT_MODULE oModule;
stt_binary_serialize_read(oModule, pszAdjSysPara, nDestLen, true);

//stt_binary_serialize_write调用，会在函数中动态分配缓冲区，因此需要在最后删除
delete pszAdjSysPara;

*/

/*
数据压缩，参见： "../../RecordTest/SttRcdSocketBufferZip.h"
压缩数据缓存的格式如下：

//zip buffer
//     4byte              4byte                   4byte                zip data length
//  EA15EA15     zip data src length     zip data length     ------------------------
函数stt_rcd_zip_buf_get_len_zip，获得“zip data length”
函数stt_rcd_zip_buf_get_len_src，获得“ zip data src length”

*/

BOOL stt_binary_serialize_read(STT_MODULE &oPara, BYTE *pDestBuffer, long &nLength, bool bUseZip);
void stt_binary_serialize_write(STT_MODULE &oPara, BYTE **ppDestBuffer, long &nDestLength, bool bUseZip);

#endif // TMT_ADJUST_SYS_PARAMETER_BINARY_SERIALIZE_H

