#ifndef _IOT_CMM_ERROR_DEFINES_H__
#define _IOT_CMM_ERROR_DEFINES_H__

//��ͨѶ�˿�ʧ��
#define COMMERROR_OPEN_DEVICE_FAILD		0X00000001

//��ȡ����ʧ��
#define COMMERROR_READ_DATA_FAILED		0X00000002

//��������ʧ��
#define COMMERROR_WRITE_DATA_FAILD		0X00000004

//�����쳣
#define COMMERROR_DATA_EXCEPTION		0X00000008

//����ʧ��
#define COMMERROR_CONNECT_FAILED			0X00000010

//�������ͺŲ�֧�ֵ�ǰѡ��Ĳ��Թ���
#define COMMERROR_MACRO_NOT_SUPPORT	0X00000020

//ͨѶ������
#define COMMERROR_IN_CMM_CONFIGING 	    0X00000040

//��ѹ����Խ��
#define COMMERROR_UI_LIMIT 	    0X00000080

//�豸���ڲ���   //2014-12-29  lijq
#define COMMERROR_DEVICE_INTESTTING 	    0X00000100

//�����Ĵ���
#define COMMERROR_OTHER		 	       0X08000000


//ͨѶ��غ�������ֵ�Ĵ�����
inline bool COMM_Error(DWORD nResult)
{
	return ((nResult & 0xF0000000) > 0);
}

inline DWORD COMM_GetError(DWORD nResult)
{
	return (nResult & 0x0FFFFFFF);
}

inline DWORD COMM_SetError(DWORD nData)
{
	return (nData | 0xF0000000);
}

#endif//_IOT_CMM_ERROR_DEFINES_H__
