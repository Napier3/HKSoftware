#ifndef _VariantApi_h
#define _VariantApi_h

BOOL VariantToCString(const _variant_t &var, CString &strValue)  ;

BOOL VariantToDouble(const _variant_t &vt,double &fValue);
BOOL VariantToFloat(const _variant_t &vt,float &fValue);

BOOL VariantToLong(const _variant_t &vt,long &nValue);
BOOL VariantToDWord(const _variant_t &vt,DWORD &nValue);
BOOL VariantToInt64(const _variant_t &vt,__int64 &nValue);

BOOL VariantToSystemTime(const _variant_t &var,SYSTEMTIME &tmValue);

#endif