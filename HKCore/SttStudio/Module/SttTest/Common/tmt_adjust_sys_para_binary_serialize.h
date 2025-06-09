#ifndef TMT_ADJUST_SYS_PARAMETER_BINARY_SERIALIZE_H
#define TMT_ADJUST_SYS_PARAMETER_BINARY_SERIALIZE_H

//2020-10-21  lijunqing 
#include "tmt_adjust_sys_parameter.h"


/*
�ӿ�ʹ��ʾ����

//���建����ָ��
BYTE *pszAdjSysPara = NULL;   
long nDestLen = 0;

//��ѡ�е�ģ���ڴ����ݣ����л����������У������ص�pszAdjSysPara�У�nDestLen��ʾ���ݵĳ���
stt_binary_serialize_write(g_theDeviceSystemParameter->m_oModules[0], &pszAdjSysPara, nDestLen, true);

//�Ӷ������ڴ������У���ȡģ��ϵ������
STT_MODULE oModule;
stt_binary_serialize_read(oModule, pszAdjSysPara, nDestLen, true);

//stt_binary_serialize_write���ã����ں����ж�̬���仺�����������Ҫ�����ɾ��
delete pszAdjSysPara;

*/

/*
����ѹ�����μ��� "../../RecordTest/SttRcdSocketBufferZip.h"
ѹ�����ݻ���ĸ�ʽ���£�

//zip buffer
//     4byte              4byte                   4byte                zip data length
//  EA15EA15     zip data src length     zip data length     ------------------------
����stt_rcd_zip_buf_get_len_zip����á�zip data length��
����stt_rcd_zip_buf_get_len_src����á� zip data src length��

*/

BOOL stt_binary_serialize_read(STT_MODULE &oPara, BYTE *pDestBuffer, long &nLength, bool bUseZip);
void stt_binary_serialize_write(STT_MODULE &oPara, BYTE **ppDestBuffer, long &nDestLength, bool bUseZip);

#endif // TMT_ADJUST_SYS_PARAMETER_BINARY_SERIALIZE_H

