#pragma once

#define  DBOptrBase_Method_Insert ("InsertOptr")
#define  DBOptrBase_Method_Delete ("DeleteOptr")
#define  DBOptrBase_Method_Update ("UpdateOptr")
#define  DBOptrBase_Method_Query  ("QueryOptr")
#define	 DBOptrBase_Method_ExecSqlCmd ("ExecSqlCmd")
#define DBOptrBase_Method_CommQuery ("CommQueryOptr")
#define DBOptrBase_Method_CommDelete ("CommDeleteOptr")
#define DBOptrBase_Method_CommInsert ("CommInsertOptr")

#define QUERY_TABLE_OWN		0
#define QUERY_TABLE_EXT		1

/****************************
��չ��Ƕ���
D0����ѯ��ǰ��0=����ѯ��1=��ѯ
D1���������ȫ���ӱ�0=����ѯ��1=��ѯ
D2�������������Name���ԣ�0=������1=����
D3: �����������ͳ�����ԣ�0=������1=����
*****************************/
#define QUERY_EX_D0_CUR_TABLE 		0x1
#define QUERY_EX_D1_CHILD_TABLE	 	0x2
#define QUERY_EX_D2_RELATION_INFO	0x4
#define QUERY_EX_D3_STATISTIC_INFO	0x8