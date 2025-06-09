/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*	   2006, All Rights Reserved   					*/
/*									*/
/* MODULE NAME : Value.cpp						*/
/* PRODUCT(S)  : Generic Value class					*/
/*									*/
/* MODULE DESCRIPTION :                                                 */
/*									*/
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev      Comments                                    */
/* --------  ---  ------   -------------------------------------------  */
/* 03/12/07  DSF     02    Added ToString (ValType)			*/
/* 10/23/06  DSF     01    Created					*/
/************************************************************************/

#include "Value.h"
#include <limits.h>
#include <float.h>

namespace SISCO
{
namespace ValueNS
{

/************************************************************************/
/************************************************************************/
/*			Value class					*/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/*			constructors					*/
/************************************************************************/

Value::Value () : valueType (vtUndefined)
  {
  }
  
Value::Value (const Value& val)
  {
  
  valueType = val.GetValueType ();
  switch (valueType)
    {
    case vtUndefined:
    break;
    case vtInteger:
      v.intValue = val.v.intValue;
    break;
    case vtUnsigned:
      v.uintValue = val.v.uintValue;
    break;
    case vtFloat:
      v.floatValue = val.v.floatValue;
    break;
    case vtDouble:
      v.doubleValue = val.v.doubleValue;
    break;
    case vtBoolean:
      v.boolValue = val.v.boolValue;
    break;
    case vtDateTime:
      v.dateTimeValue = val.v.dateTimeValue;
    break;
    case vtString:
      v.stringValue = val.v.stringValue;
    break;
    case vtBitset:
      m_bitCount = val.GetBitsetSize ();
      v.bitsetValue = val.v.bitsetValue;
    break;
    case vtByteArray:
      v.byteArrayValue = val.v.byteArrayValue;
    break;
    default:
      invalid_argument ("Invalid value type");
    break;
    }
  }
  
Value::Value (const char val)
  {
  valueType = vtInteger;
  v.intValue = val;
  }
  
Value::Value (const unsigned char val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  }

Value::Value (const short val)
  {
  valueType = vtInteger;
  v.intValue = val;
  }

Value::Value (const unsigned short val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  }

Value::Value (const int val)
  {
  valueType = vtInteger;
  v.intValue = val;
  }

Value::Value (const unsigned val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  }

Value::Value (const long val)
  {
  valueType = vtInteger;
  v.intValue = val;
  }

Value::Value (const unsigned long val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  }

Value::Value (const float val)
  {
  valueType = vtFloat;
  v.floatValue = val;
  }

Value::Value (const double val)
  {
  valueType = vtDouble;
  v.doubleValue = val;
  }

Value::Value (const bool val)
  {
  valueType = vtBoolean;
  v.boolValue = val;
  }

Value::Value (const STDTIME& val)
  {
  valueType = vtDateTime;
  v.dateTimeValue = val;
  }

Value::Value (const string& val)
  {
  valueType = vtString;
  v.stringValue = val;
  }

Value::Value (const char *pString)
  {
  valueType = vtString;
  v.stringValue = (string) pString;
  }

Value::Value (const unsigned char *pString)
  {
  valueType = vtString;
  v.stringValue = (string) (char *) pString;
  }

Value::Value (const ByteArray& val)
  {
  valueType = vtByteArray;
  v.byteArrayValue = val;
  }

Value::Value (const unsigned char *pByteArray, unsigned int count)
  {
  valueType = vtByteArray;
  v.byteArrayValue.resize (count);
  memcpy (&v.byteArrayValue[0], pByteArray, count);
  }

/************************************************************************/
/*			assignment operators				*/
/************************************************************************/

Value& Value::operator= (const Value& val)
  {
  
  valueType = val.GetValueType ();
  switch (valueType)
    {
    case vtUndefined:
    break;
    case vtInteger:
      v.intValue = val.v.intValue;
    break;
    case vtUnsigned:
      v.uintValue = val.v.uintValue;
    break;
    case vtFloat:
      v.floatValue = val.v.floatValue;
    break;
    case vtDouble:
      v.doubleValue = val.v.doubleValue;
    break;
    case vtBoolean:
      v.boolValue = val.v.boolValue;
    break;
    case vtDateTime:
      v.dateTimeValue = val.v.dateTimeValue;
    break;
    case vtString:
      v.stringValue = val.v.stringValue;
    break;
    case vtBitset:
      m_bitCount = val.GetBitsetSize ();
      v.bitsetValue = val.v.bitsetValue;
    break;
    case vtByteArray:
      v.byteArrayValue = val.v.byteArrayValue;
    break;
    default:
      invalid_argument ("Invalid value type");
    break;
    }
    
  return *this;
  }
  
Value& Value::operator= (const char val)
  {
  valueType = vtInteger;
  v.intValue = val;
  return *this;
  }
  
Value& Value::operator= (const unsigned char val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  return *this;
  }
  
Value& Value::operator= (const short val)
  {
  valueType = vtInteger;
  v.intValue = val;
  return *this;
  }
  
Value& Value::operator= (const unsigned short val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  return *this;
  }
  
Value& Value::operator= (const int val)
  {
  valueType = vtInteger;
  v.intValue = val;
  return *this;
  }
  
Value& Value::operator= (const unsigned val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  return *this;
  }
  
Value& Value::operator= (const long val)
  {
  valueType = vtInteger;
  v.intValue = val;
  return *this;
  }
  
Value& Value::operator= (const unsigned long val)
  {
  valueType = vtUnsigned;
  v.uintValue = val;
  return *this;
  }
  
Value& Value::operator= (const float val)
  {
  valueType = vtFloat;
  v.floatValue = val;
  return *this;
  }
  
Value& Value::operator= (const double val)
  {
  valueType = vtDouble;
  v.doubleValue = val;
  return *this;
  }
  
Value& Value::operator= (const bool val)
  {
  valueType = vtBoolean;
  v.boolValue = val;
  return *this;
  }
  
Value& Value::operator= (const STDTIME& val)
  {
  valueType = vtDateTime;
  v.dateTimeValue = val;
  return *this;
  }
  
Value& Value::operator= (const string& val)
  {
  valueType = vtString;
  v.stringValue = val;
  return *this;
  }

Value& Value::operator= (const char *pString)
  {
  valueType = vtString;
  v.stringValue = (string) pString;
  return *this;
  }
  
Value& Value::operator= (const unsigned char *pString)
  {
  valueType = vtString;
  v.stringValue = (string) (char *) pString;
  return *this;
  }
  
Value& Value::operator= (const ByteArray& val)
  {
  valueType = vtByteArray;
  v.byteArrayValue = val;
  return *this;
  }
  
/************************************************************************/
/*			comparison operators				*/
/************************************************************************/
  
bool Value::operator== (const Value& val) const
  {
  if (valueType != val.GetValueType ())
    return false;
    
  switch (valueType)
    {
    case vtUndefined:
      return true;
    break;
    case vtInteger:
      return v.intValue == val.v.intValue;
    break;
    case vtUnsigned:
      return v.uintValue == val.v.uintValue;
    break;
    case vtFloat:
      return v.floatValue == val.v.floatValue;
    break;
    case vtDouble:
      return v.doubleValue == val.v.doubleValue;
    break;
    case vtBoolean:
      return v.boolValue == val.v.boolValue;
    break;
    case vtDateTime:
      return v.dateTimeValue == val.v.dateTimeValue;
    break;
    case vtString:
      return v.stringValue == val.v.stringValue;
    break;
    case vtBitset:
      if (m_bitCount != val.GetBitsetSize ())
        return false;
      return v.bitsetValue == val.v.bitsetValue;
    break;
    case vtByteArray:
      return v.byteArrayValue == val.v.byteArrayValue;
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
bool Value::operator== (const char val) const
  {
  if (valueType != vtInteger)
    return false;
  return v.intValue == val;
  }
  
bool Value::operator== (const unsigned char val) const
  {
  if (valueType != vtUnsigned)
    return false;
  return v.uintValue == val;
  }
  
bool Value::operator== (const short val) const
  {
  if (valueType != vtInteger)
    return false;
  return v.intValue == val;
  }
  
bool Value::operator== (const unsigned short val) const
  {
  if (valueType != vtUnsigned)
    return false;
  return v.uintValue == val;
  }
  
bool Value::operator== (const int val) const
  {
  if (valueType != vtInteger)
    return false;
  return v.intValue == val;
  }
  
bool Value::operator== (const unsigned val) const
  {
  if (valueType != vtUnsigned)
    return false;
  return v.uintValue == val;
  }
  
bool Value::operator== (const long val) const
  {
  if (valueType != vtInteger)
    return false;
  return v.intValue == val;
  }
  
bool Value::operator== (const unsigned long val) const
  {
  if (valueType != vtUnsigned)
    return false;
  return v.uintValue == val;
  }
  
bool Value::operator== (const float val) const
  {
  if (valueType != vtFloat)
    return false;
  return v.floatValue == val;
  }
  
bool Value::operator== (const double val) const
  {
  if (valueType != vtDouble)
    return false;
  return v.doubleValue == val;
  }
  
bool Value::operator== (const bool val) const
  {
  if (valueType != vtBoolean)
    return false;
  return v.boolValue == val;
  }
  
bool Value::operator== (const STDTIME& val) const
  {
  if (valueType != vtDateTime)
    return false;
  return v.dateTimeValue == val;
  }
  
bool Value::operator== (const string& val) const
  {
  if (valueType != vtString)
    return false;
  return v.stringValue == val;
  }

bool Value::operator== (const char *pString) const
  {
  if (valueType != vtString)
    return false;
  return v.stringValue == (string) pString;
  }

bool Value::operator== (const unsigned char *pString) const
  {
  if (valueType != vtString)
    return false;
  return v.stringValue == (string) (char *) pString;
  }
  
bool Value::operator== (const ByteArray& val) const
  {
  if (valueType != vtByteArray)
    return false;
  return v.byteArrayValue == val;
  }
  


/************************************************************************/
/*			SetValue					*/
/************************************************************************/

void Value::SetValue (const Value& val)
  {
  switch (val.valueType)
    {
    case vtUndefined:
    break;
    case vtInteger:
      SetValue (val.v.intValue);
    break;
    case vtUnsigned:
      SetValue (val.v.uintValue);
    break;
    case vtFloat:
      SetValue (val.v.floatValue);
    break;
    case vtDouble:
      SetValue (val.v.doubleValue);
    break;
    case vtBoolean:
      SetValue (val.v.boolValue);
    break;
    case vtDateTime:
      SetValue (val.v.dateTimeValue);
    break;
    case vtString:
      SetValue (val.v.stringValue);
    break;
    case vtBitset:
      SetValue (val.v.bitsetValue, val.GetBitsetSize ());
    break;
    case vtByteArray:
      SetValue (val.v.byteArrayValue);
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const char val)
  {
  SetValue ((const long) val);
  }
  
void Value::SetValue (const unsigned char val)
  {
  SetValue ((const unsigned long) val);
  }
  
void Value::SetValue (const short val)
  {
  SetValue ((const long) val);
  }
  
void Value::SetValue (const unsigned short val)
  {
  SetValue ((const unsigned long) val);
  }
  
void Value::SetValue (const int val)
  {
  SetValue ((const long) val);
  }
  
void Value::SetValue (const unsigned val)
  {
  SetValue ((const unsigned long) val);
  }
  
void Value::SetValue (const long val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtInteger;
      v.intValue = val;
    break;
    case vtInteger:
      v.intValue = val;
    break;
    case vtUnsigned:
      if (val < 0)
        throw out_of_range ("Illegal value");
      v.uintValue = val;
    break;
    case vtFloat:
      v.floatValue = (float) val;
    break;
    case vtDouble:
      v.doubleValue = (double) val;
    break;
    case vtBoolean:
      v.boolValue = val != 0;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      char temp[100];
      sprintf (temp, "%d", val);
      v.stringValue = temp;
      }
    break;
    case vtBitset:
      throw out_of_range ("Incompatible types");
    break;
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const unsigned long val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtUnsigned;
      v.uintValue = val;
    break;
    case vtInteger:
      if (val > (unsigned long) 0x7FFFFFFF)
        throw out_of_range ("Illegal value");
      v.intValue = (long) val;
    break;
    case vtUnsigned:
      v.uintValue = val;
    break;
    case vtFloat:
      v.floatValue = (float) val;
    break;
    case vtDouble:
      v.doubleValue = (double) val;
    break;
    case vtBoolean:
      v.boolValue = val != 0;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      char temp[100];
      sprintf (temp, "%u", val);
      v.stringValue = temp;
      }
    break;
    case vtBitset:
      throw out_of_range ("Incompatible types");
    break;
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const float val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtFloat;
      v.floatValue = val;
    break;
    case vtInteger:
      if (val > INT_MAX || val < INT_MIN)
        throw out_of_range ("Illegal value");
      v.intValue = (long) val;
    break;
    case vtUnsigned:
      if (val < 0 || val > UINT_MAX)
        throw out_of_range ("Illegal value");
      v.uintValue = (unsigned long) val;
    break;
    case vtFloat:
      v.floatValue = val;
    break;
    case vtDouble:
      v.doubleValue = (double) val;
    break;
    case vtBoolean:
      v.boolValue = val != 0;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      char temp[100];
      sprintf (temp, "%f", val);
      v.stringValue = temp;
      }
    break;
    case vtBitset:
      throw out_of_range ("Incompatible types");
    break;
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const double val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtDouble;
      v.doubleValue = val;
    break;
    case vtInteger:
      if (val > INT_MAX || val < INT_MIN)
        throw out_of_range ("Illegal value");
      v.intValue = (long) val;
    break;
    case vtUnsigned:
      if (val < 0 || val > UINT_MAX)
        throw out_of_range ("Illegal value");
      v.uintValue = (unsigned long) val;
    break;
    case vtFloat:
      if (val > FLT_MAX || val < FLT_MIN)
        throw out_of_range ("Illegal value");
      v.floatValue = (float) val;
    break;
    case vtDouble:
      v.doubleValue = val;
    break;
    case vtBoolean:
      v.boolValue = val != 0;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      char temp[100];
      sprintf (temp, "%g", val);
      v.stringValue = temp;
      }
    break;
    case vtBitset:
      throw out_of_range ("Incompatible types");
    break;
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const bool val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtBoolean;
      v.boolValue = val;
    break;
    case vtInteger:
      v.intValue = (long) val;
    break;
    case vtUnsigned:
      v.uintValue = (unsigned long) val;
    break;
    case vtFloat:
      v.floatValue = (float) val;
    break;
    case vtDouble:
      v.doubleValue = (double) val;
    break;
    case vtBoolean:
      v.boolValue = val;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      char temp[100];
      sprintf (temp, "%s", val ? "True" : "False");
      v.stringValue = temp;
      }
    break;
    case vtBitset:
      throw out_of_range ("Incompatible types");
    break;
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const STDTIME& val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtDateTime;
    case vtDateTime:
      v.dateTimeValue = val;
    break;
    case vtString:
      v.stringValue = DateTimeToString (val);
    break;
    case vtInteger:
    case vtUnsigned:
    case vtFloat:
    case vtDouble:
    case vtBoolean:
    case vtBitset:
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
void Value::SetValue (const string& val)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtString;
      v.stringValue = val;
    break;
    case vtInteger:
      v.intValue = atol (val.c_str ());
    break;
    case vtUnsigned:
      {
      long i = atol (val.c_str ());
      if (i < 0)
        throw out_of_range ("Illegal value");
      v.uintValue = (unsigned long) i;
      }
    break;
    case vtFloat:
      {
      double d = atof (val.c_str ());
      if (d > FLT_MAX || d < FLT_MIN)
        throw out_of_range ("Out of range");
      v.floatValue = (float) d;
      }
    break;
    case vtDouble:
      v.doubleValue = (double) atof (val.c_str ());
    break;
    case vtBoolean:
      if (val == "0" || val == "false" || val == "False" || val == "FALSE" || val == "f" || val == "F")
        v.boolValue = false;
      else if (val == "1" || val == "true" || val == "True" || val == "TRUE" || val == "t" || val == "T")
        v.boolValue = true;
      else
        throw out_of_range ("Illegal value");
    break;
    case vtDateTime:
      StringToDateTime (val, v.dateTimeValue);
    break;
    case vtString:
      v.stringValue = val;
    break;
    case vtBitset:
      {
      BitSet bs (val);
      m_bitCount = MAX_BITSET_SIZE;
      v.bitsetValue = bs;
      }
    break;
    case vtByteArray:
      SetValue ((const unsigned char *) val.c_str (), val.size ());
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }

void Value::SetValue (const char *pString)
  {
  SetValue ((string) pString);
  }

void Value::SetValue (const unsigned char *pString)
  {
  SetValue ((string) (char *) pString);
  }
  
void Value::SetValue (const ByteArray& val)
  {
  SetValue (&val[0], val.size ());
  }
  
void Value::SetValue (const unsigned char *pByteArray, unsigned int count)
  {
  switch (valueType)
    {
    case vtUndefined:
      valueType = vtByteArray;
      v.byteArrayValue.resize (count);
      memcpy (&v.byteArrayValue[0], pByteArray, count);
    break;
    case vtInteger:
      if (count > sizeof (long))
        throw out_of_range ("Incompatible types");
      memcpy (&v.intValue, pByteArray, count);
    break;
    case vtUnsigned:
      if (count > sizeof (unsigned long))
        throw out_of_range ("Incompatible types");
      memcpy (&v.uintValue, pByteArray, count);
    break;
    case vtFloat:
      if (count > sizeof (float))
        throw out_of_range ("Incompatible types");
      memcpy (&v.floatValue, pByteArray, count);
    break;
    case vtDouble:
      if (count > sizeof (double))
        throw out_of_range ("Incompatible types");
      memcpy (&v.doubleValue, pByteArray, count);
    break;
    case vtBoolean:
      if (count > sizeof (bool))
        throw out_of_range ("Incompatible types");
      memcpy (&v.boolValue, pByteArray, count);
    break;
    case vtDateTime:
      if (count > sizeof (STDTIME))
        throw out_of_range ("Incompatible types");
      memcpy (&v.dateTimeValue, pByteArray, count);
    break;
    case vtBitset:
      ByteArrayToBitset (pByteArray, count, v.bitsetValue);
      m_bitCount = count * 8;
    break;
    case vtString:
      v.stringValue = ByteArrayToString (pByteArray, count);
    break;
    case vtByteArray:
      v.byteArrayValue.resize (count);
      memcpy (&v.byteArrayValue[0], pByteArray, count);
    break;
    default:
      throw invalid_argument ("Invalid value type");
    break;
    }
  }
  
/************************************************************************/
/*			GetValueAs...					*/
/************************************************************************/

long Value::GetValueAsInteger () const
  {
  switch (valueType)
    {
    case vtInteger:
      return v.intValue;
    break;
    case vtUnsigned:
      if (v.uintValue > INT_MAX)
        throw out_of_range ("Illegal value");
      return (long) v.uintValue;
    break;
    case vtFloat:
      if (v.floatValue > INT_MAX || v.floatValue < INT_MIN)
        throw out_of_range ("Illegal value");
      return (long) v.floatValue;
    break;
    case vtDouble:
      if (v.doubleValue > INT_MAX || v.doubleValue < INT_MIN)
        throw out_of_range ("Illegal value");
      return (long) v.doubleValue;
    break;
    case vtBoolean:
      return (long) v.boolValue;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      return atol (v.stringValue.c_str ());
    break;
    case vtBitset:
      {
      if (m_bitCount > 32)
        throw out_of_range ("Illegal value");
      unsigned long ul = v.bitsetValue.to_ulong ();
      if (ul > INT_MAX)
        throw out_of_range ("Illegal value");
      return (long) ul;
      }
    break;
    case vtByteArray:
      if (v.byteArrayValue.size () > 4 || v.byteArrayValue.empty ())
        throw out_of_range ("Illegal value");
      return * (long *) &v.byteArrayValue[0];
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }

unsigned long Value::GetValueAsUnsigned () const
  {
  switch (valueType)
    {
    case vtInteger:
      if (v.uintValue < 0)
        throw out_of_range ("Illegal value");
      return (unsigned long) v.intValue;
    break;
    case vtUnsigned:
      return v.uintValue;
    break;
    case vtFloat:
      if (v.floatValue > UINT_MAX || v.floatValue < 0)
        throw out_of_range ("Illegal value");
      return (unsigned long) v.floatValue;
    break;
    case vtDouble:
      if (v.doubleValue > UINT_MAX || v.doubleValue < 0)
        throw out_of_range ("Illegal value");
      return (unsigned long) v.doubleValue;
    break;
    case vtBoolean:
      return (unsigned long) v.boolValue;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      long l = atol (v.stringValue.c_str ());
      if (l < 0)
        throw out_of_range ("Illegal value");
      return (unsigned long) l;
      }
    break;
    case vtBitset:
      if (m_bitCount > 32)
        throw out_of_range ("Illegal value");
      return v.bitsetValue.to_ulong ();
    break;
    case vtByteArray:
      if (v.byteArrayValue.size () > 4 || v.byteArrayValue.empty ())
        throw out_of_range ("Illegal value");
      return * (unsigned long *) &v.byteArrayValue[0];
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }
  
  
float Value::GetValueAsFloat () const
  {
  switch (valueType)
    {
    case vtInteger:
      return (float) v.intValue;
    break;
    case vtUnsigned:
      return (float) v.uintValue;
    break;
    case vtFloat:
      return v.floatValue;
    break;
    case vtDouble:
      if (v.doubleValue < FLT_MIN || v.doubleValue > FLT_MAX)
        throw out_of_range ("Illegal value");
      return (float) v.doubleValue;
    break;
    case vtBoolean:
      return (float) v.boolValue;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      double d = atof (v.stringValue.c_str ());
      if (d < FLT_MIN || d > FLT_MAX)
        throw out_of_range ("Illegal value");
      return (float) d;
      }
    break;
    case vtBitset:
      if (m_bitCount > 32)
        throw out_of_range ("Illegal value");
      return (float) v.bitsetValue.to_ulong ();
    break;
    case vtByteArray:
      if (v.byteArrayValue.size () > sizeof (float) || v.byteArrayValue.empty ())
        throw out_of_range ("Illegal value");
      return * (float *) &v.byteArrayValue[0];
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }

double Value::GetValueAsDouble () const
  {
  switch (valueType)
    {
    case vtInteger:
      return (double) v.intValue;
    break;
    case vtUnsigned:
      return (double) v.uintValue;
    break;
    case vtFloat:
      return (double) v.floatValue;
    break;
    case vtDouble:
      return v.doubleValue;
    break;
    case vtBoolean:
      return (double) v.boolValue;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      return atof (v.stringValue.c_str ());
    break;
    case vtBitset:
      if (m_bitCount > 32)
        throw out_of_range ("Illegal value");
      return (double) v.bitsetValue.to_ulong ();
    break;
    case vtByteArray:
      if (v.byteArrayValue.size () > sizeof (double) || v.byteArrayValue.empty ())
        throw out_of_range ("Illegal value");
      return * (double *) &v.byteArrayValue[0];
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }
  
  
bool Value::GetValueAsBool () const
  {
  switch (valueType)
    {
    case vtInteger:
      return v.intValue;
    break;
    case vtUnsigned:
      return v.uintValue;
    break;
    case vtFloat:
      return v.floatValue;
    break;
    case vtDouble:
      return v.doubleValue;
    break;
    case vtBoolean:
      return v.boolValue;
    break;
    case vtDateTime:
      throw out_of_range ("Incompatible types");
    break;
    case vtString:
      {
      if (v.stringValue == "0" || v.stringValue == "false" || v.stringValue == "False" || v.stringValue == "FALSE" ||
          v.stringValue == "f" || v.stringValue == "F")
        return false;
      else if (v.stringValue == "1" || v.stringValue == "true" || v.stringValue == "True" || v.stringValue == "TRUE" ||
               v.stringValue == "t" || v.stringValue == "T")
        return true;
      else
        throw out_of_range ("Illegal value");
      }
    break;
    case vtBitset:
     if (m_bitCount > 32)
        throw out_of_range ("Illegal value");
      return v.bitsetValue.to_ulong ();
    break;
    case vtByteArray:
      if (v.byteArrayValue.size () > sizeof (bool) || v.byteArrayValue.empty ())
        throw out_of_range ("Illegal value");
      return * (bool *) &v.byteArrayValue[0];
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }

STDTIME Value::GetValueAsDateTime () const
  {
  switch (valueType)
    {
    case vtInteger:
    case vtUnsigned:
    case vtFloat:
    case vtDouble:
    case vtBoolean:
    case vtBitset:
    case vtByteArray:
      throw out_of_range ("Incompatible types");
    break;
    case vtDateTime:
      return v.dateTimeValue;
    break;
    case vtString:
      {
      STDTIME dateTime;
      StringToDateTime (v.stringValue, dateTime);
      return dateTime;
      }
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }
  
string Value::GetValueAsString () const
  {
  return ToString ();
  }
  

BitSet Value::GetValueAsBitset () const
  {
  switch (valueType)
    {
    case vtInteger:
      {
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) &v.intValue, sizeof (long), bitset);
      return bitset;
      }
    break;
    case vtUnsigned:
      {
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) &v.uintValue, sizeof (unsigned long), bitset);
      return bitset;
      }
    break;
    case vtFloat:
      {
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) &v.floatValue, sizeof (float), bitset);
      return bitset;
      }
    break;
    case vtDouble:
      {
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) &v.doubleValue, sizeof (double), bitset);
      return bitset;
      }
    break;
    case vtBoolean:
      {
      BitSet bitset;
      if (v.boolValue)
        bitset.set (0);
      return bitset;
      }
    case vtDateTime:
      {
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) &v.dateTimeValue, sizeof (STDTIME), bitset);
      return bitset;
      }
    case vtString:
      {
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) v.stringValue.c_str (), v.stringValue.size (), bitset);
      return bitset;
      }
    break;
    case vtBitset:
      return v.bitsetValue;
    break;
    case vtByteArray:
      {
      if (v.byteArrayValue.size () > MAX_BITSET_SIZE / 8)
        throw out_of_range ("Incompatible types");
      
      BitSet bitset;
      ByteArrayToBitset ((unsigned char *) &v.byteArrayValue[0], v.byteArrayValue.size (), bitset);
      return bitset;
      }
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
  }

ByteArray Value::GetValueAsByteArray (unsigned index, unsigned count) const
  {
  ByteArray byteArray;
  
  switch (valueType)
    {
    case vtInteger:
      byteArray.resize (sizeof (long));
      memcpy (&byteArray[0], &v.intValue, sizeof (long));
    break;
    case vtUnsigned:
      byteArray.resize (sizeof (unsigned long));
      memcpy (&byteArray[0], &v.uintValue, sizeof (long));
    break;
    case vtFloat:
      byteArray.resize (sizeof (float));
      memcpy (&byteArray[0], &v.floatValue, sizeof (float));
    break;
    case vtDouble:
      byteArray.resize (sizeof (double));
      memcpy (&byteArray[0], &v.doubleValue, sizeof (double));
    break;
    case vtBoolean:
      byteArray.resize (sizeof (bool));
      memcpy (&byteArray[0], &v.boolValue, sizeof (bool));
    break;
    case vtDateTime:
      byteArray.resize (sizeof (STDTIME));
      memcpy (&byteArray[0], &v.dateTimeValue, sizeof (STDTIME));
    break;
    case vtString:
      byteArray.resize (v.stringValue.size ());
      if (v.stringValue.empty () == false)
        memcpy (&byteArray[0], v.stringValue.c_str (), v.stringValue.size ());
    break;
    case vtByteArray:
      if (index > v.byteArrayValue.size ())
        throw out_of_range ("Index out of range");
      if (count == -1)
        count = v.byteArrayValue.size ();
      count = min (count, v.byteArrayValue.size () - index);
      byteArray.resize (count);
      memcpy (&byteArray[0], &v.byteArrayValue[index], count);
    break;
    case vtBitset:
      {
      unsigned char temp[MAX_BITSET_SIZE / 8] = {0};
      unsigned size = m_bitCount / 8;
      for (unsigned i = 0; i < m_bitCount; ++i)
        {
        int byte = i / 8;
        if (v.bitsetValue.test (i))
          {
          unsigned char bit = 1 << (8 - (i % 8));
          temp[byte] |= bit;
          }
        }
      byteArray.resize (size);
      memcpy (&byteArray[0], temp, size);
      }
    break;
    default:
      throw out_of_range ("Incompatible types");
    break;
    }
    
  return byteArray;
  }

/************************************************************************/
/*			ToString					*/
/************************************************************************/
  
string Value::ToString () const
  {

  switch (valueType)
    {
    case vtUndefined:
      return "";
    break;
    case vtInteger:
      {
      char temp[100];
      sprintf (temp, "%d", v.intValue);
      return temp;
      }
    break;
    case vtUnsigned:
      {
      char temp[100];
      sprintf (temp, "%u", v.uintValue);
      return temp;
      }
    break;
    case vtFloat:
      {
      char temp[100];
      sprintf (temp, "%f", v.floatValue);
      return temp;
      }
    break;
    case vtDouble:
      {
      char temp[100];
      sprintf (temp, "%g", v.doubleValue);
      return temp;
      }
    break;
    case vtBoolean:
      {
      char temp[100];
      sprintf (temp, "%s", v.boolValue ? "True" : "False");
      return temp;
      }
    break;
    case vtDateTime:
      return DateTimeToString (v.dateTimeValue);
    break;
    case vtString:
      return v.stringValue;
    break;
    case vtBitset:
      return v.bitsetValue.template to_string<char, char_traits<char>, allocator<char> > ();
    break;
    case vtByteArray:
      return ByteArrayToString (v.byteArrayValue);
    break;
    default:
      throw invalid_argument ("Unknown value type");
    break;
    }
  }
  
/************************************************************************/
/*			GetValueType					*/
/************************************************************************/
  
void Value::ChangeValueType (ValType valType)
  {
  
  if (valueType == valType)
    return;

  switch (valType)
    {
    case vtUndefined:
      Clear ();
    break;
    case vtInteger:
      v.intValue = GetValueAsInteger ();
    break;
    case vtUnsigned:
      v.uintValue = GetValueAsUnsigned ();
    break;
    case vtFloat:
      v.floatValue = GetValueAsFloat ();
    break;
    case vtDouble:
      v.doubleValue = GetValueAsDouble ();
    break;
    case vtBoolean:
      v.boolValue = GetValueAsBool ();
    break;
    case vtDateTime:
      v.dateTimeValue = GetValueAsDateTime ();
    break;
    case vtString:
      v.stringValue = GetValueAsString ();
    break;
    case vtBitset:
       v.bitsetValue = GetValueAsBitset ();
    break;
    case vtByteArray:
      v.byteArrayValue = GetValueAsByteArray ();
    break;
    default:
      throw invalid_argument ("Unknown value type");
    break;
    }
    
  valueType = valType;    
  }

/************************************************************************/
/************************************************************************/
/*			Helpers						*/
/************************************************************************/
/************************************************************************/
  
string DateTimeToString (const STDTIME& dateTime)
  {
  
  STDTIME_STRING s;
  if (StdTimeToStdTimeString (&dateTime, &s) != STDTIME_OK)
    out_of_range ("Invalid time string");
    
  return s.str;
  }
  
void StringToDateTime (const string& str, STDTIME& dateTime)
  {
  
  STDTIME_STRING s = {0};
  if (str.size () > sizeof (s.str))
    out_of_range ("Invalid time string");
    
  if (StdTimeStringToStdTime (&s, &dateTime) != STDTIME_OK)
    out_of_range ("Invalid time string");
  }

string ByteArrayToString (const ByteArray& byteArray)
  {
  return ByteArrayToString (&byteArray[0], byteArray.size ());
  }
  
string ByteArrayToString (const unsigned char *pByteArray, unsigned count)
  {
  char *pTemp = new char[(count * 2) + 1];
  for (unsigned i = 0; i < count; ++i)
    {
    unsigned char hi = pByteArray[i] >> 4;
    unsigned char lo = pByteArray[i] & 0xF;
    sprintf (pTemp + 2*i, "%X", hi);
    sprintf (pTemp + (2*i+1), "%X", lo);
    }
  
  string s = string (pTemp);
  delete [] pTemp;
  return s;
  }
  
void StringToByteArray (const string& str, ByteArray& byteArray)
  {
  if ((str.size () % 2) != 0)
    throw invalid_argument ("Invalid hex string");

  byteArray.clear ();
  for (string::const_iterator it = str.begin (); it != str.end (); )
    {
    unsigned char hi;
    unsigned char lo;
    
    char c = (char) toupper (*it++);
    if (c >= '0' && c <= '9')
      hi = (c - '0') << 4;
    else if (toupper (c) >= 'A' && toupper (c) <= 'F')
      hi = ((c - 'A') + 10) << 4;
    else    
      throw invalid_argument ("Invalid hex string");
      
    c = (char) toupper (*it++);
    if (c >= '0' && c <= '9')
      lo = c - '0';
    else if (toupper (c) >= 'A' && toupper (c) <= 'F')
      lo = (c - 'A') + 10;
    else    
      throw invalid_argument ("Invalid hex string");
      
    byteArray.push_back (hi | lo);
    }
  }

string ToString (const ValType valType)
  {
  switch (valType)
    {
    case vtInteger:
      return "Integer";
    break;
    case vtUnsigned:
      return "Unsigned";
    break;
    case vtFloat:
      return "Float";
    break;
    case vtDouble:
      return "Double";
    break;
    case vtBoolean:
      return "Boolean";
    break;
    case vtDateTime:
      return "DateTime";
    break;
    case vtString:
      return "String";
    break;
    case vtBitset:
      return "Bitset";
    break;
    case vtByteArray:
      return "ByteArray";
    break;
    default:
      return "Undefined";
    break;    
    }
  }  
  

}
}
