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
扩展标记定义
D0：查询当前表，0=不查询；1=查询
D1：相关联的全部子表，0=不查询；1=查询
D2：处理相关联的Name属性：0=不处理；1=处理
D3: 处理相关联的统计属性：0=不处理，1=处理
*****************************/
#define QUERY_EX_D0_CUR_TABLE 		0x1
#define QUERY_EX_D1_CHILD_TABLE	 	0x2
#define QUERY_EX_D2_RELATION_INFO	0x4
#define QUERY_EX_D3_STATISTIC_INFO	0x8