// VarDataTypeEx.cpp
//
//////////////////////////////////////////////////////////////////////

#include "VarDataTypeEx.h"
#include <string.h>

void var_list_init(long nCount, VAR_DOUBLE_LIST &varList)
{
    if (nCount == varList.nCount)
    {
        return;
    }

    var_list_free(varList);

    varList.nCount = nCount;

    if (nCount == 0)
    {
        return;
    }

    varList.pfBuffer = new double [nCount];
    memset(varList.pfBuffer, 0, nCount * sizeof(double));
}

void var_list_init(long nCount, VAR_DOUBLE_LIST *varList)
{
    var_list_init(nCount, *varList);
}

void var_list_init(long nCount, VAR_FLOAT_LIST &varList)
{
    if (nCount == varList.nCount)
    {
        return;
    }

    var_list_free(varList);

    if (nCount == 0)
    {
        return;
    }

    varList.nCount = nCount;
    varList.pfBuffer = new float [nCount];
    memset(varList.pfBuffer, 0, nCount * sizeof(float));
}

void var_list_init(long nCount, VAR_FLOAT_LIST *varList)
{
     var_list_init(nCount, *varList);
}

void var_list_init(long nCount, VAR_INT_LIST &varList)
{
    if (nCount == varList.nCount)
    {
        return;
    }

    var_list_free(varList);

    if (nCount == 0)
    {
        return;
    }

    varList.nCount = nCount;
    varList.pnBuffer = new int [nCount];
    memset(varList.pnBuffer, 0, nCount * sizeof(int));
}

void var_list_init(long nCount, VAR_INT_LIST *varList)
{
     var_list_init(nCount, *varList);
}

void var_list_free(VAR_DOUBLE_LIST &varList)
{
    if (varList.pfBuffer != 0)
    {
        delete varList.pfBuffer;
    }
    varList.pfBuffer = 0;
    varList.nCount = 0;
}

void var_list_free(VAR_DOUBLE_LIST *varList)
{
    var_list_free(*varList);
}

void var_list_free(VAR_FLOAT_LIST &varList)
{
    if (varList.pfBuffer != 0)
    {
        delete varList.pfBuffer;
        varList.pfBuffer = 0;
    }
    varList.nCount = 0;
}

void var_list_free(VAR_FLOAT_LIST *varList)
{
    var_list_free(*varList);
}

void var_list_free(VAR_INT_LIST &varList)
{
    if (varList.pnBuffer != 0)
    {
        delete varList.pnBuffer;
        varList.pnBuffer = 0;
    }
    varList.nCount = 0;
}

void var_list_free(VAR_INT_LIST *varList)
{
    var_list_free(*varList);
}

