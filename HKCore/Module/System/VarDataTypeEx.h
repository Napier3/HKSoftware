// VarDataTypeEx.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VarDataTypeEx_H__)
#define AFX_VarDataTypeEx_H__

typedef struct _var_double_list_
{
    int nCount;
    double *pfBuffer;
}VAR_DOUBLE_LIST, *PVAR_DOUBLE_LIST;
typedef struct _var_float_list_
{
    int nCount;
    float *pfBuffer;
}VAR_FLOAT_LIST, *PVAR_FLOAT_LIST;
typedef struct _var_int_list_
{
    int nCount;
    int *pnBuffer;
}VAR_INT_LIST, *PVAR_INT_LIST;

void var_list_init(long nCount, VAR_DOUBLE_LIST &varList);
void var_list_init(long nCount, VAR_DOUBLE_LIST *varList);
void var_list_init(long nCount, VAR_FLOAT_LIST &varList);
void var_list_init(long nCount, VAR_FLOAT_LIST *varList);
void var_list_init(long nCount, VAR_INT_LIST &varList);
void var_list_init(long nCount, VAR_INT_LIST &varList);

void var_list_free(VAR_DOUBLE_LIST &varList);
void var_list_free(VAR_DOUBLE_LIST *varList);
void var_list_free(VAR_FLOAT_LIST &varList);
void var_list_free(VAR_FLOAT_LIST *varList);
void var_list_free(VAR_INT_LIST &varList);
void var_list_free(VAR_INT_LIST *varList);

#endif // !defined(AFX_VarDataTypeEx_H__)
