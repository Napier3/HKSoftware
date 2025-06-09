/*
 * File:	OCArray.h
 * Project:	Open Concepts Class Library
 * Author:	Russell Robinson
 * Date:	18 January 2000
 * Purpose:
 *		To declare OCArray - an improved CArray template class.
 */

#if !defined(AFX_OCARRAY_H__BE2C5983_CE26_11D3_BAE6_0000C0D475E2__INCLUDED_)
#define AFX_OCARRAY_H__BE2C5983_CE26_11D3_BAE6_0000C0D475E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

/*
 * Template Class:	OCArray
 * Author:			Russell Robinson
 * Purpose:
 *		To provide a generic array class like CArray without the problems.
 *		OCArray takes one parameter - TYPE.  Unlike CArray, OCArray always
 *		returns references and expects references as parameters.
 */
template <class TYPE> class OCArray : public CArray<TYPE,TYPE&>
{
public:
	/*
	 * Method:		OCArray::operator[] const
	 * Parameters:	i_index			the array index to access
	 * Returns:		const TYPE&		reference to the element at the index
	 * Author:		Russell Robinson
	 * Purpose:
	 *		To return an element of the array for const access.
	 */
	inline const TYPE&	operator[](int i_index) const
	{
		ASSERT(0 <= i_index && i_index < GetSize());
		return (GetData()[i_index]);
	};

	/*
	 * Method:		OCArray::GetAt
	 * Parameters:	i_index			the array index to access
	 * Returns:		const TYPE&		reference to the element at the index
	 * Author:		Russell Robinson
	 * Purpose:
	 *		To return an element of the array for const access.
	 */
	inline const TYPE&	GetAt(int i_index) const
	{
	    int Size = GetSize();
		ASSERT(0 <= i_index && i_index < GetSize());
		return (GetData()[i_index]);
	};
	inline TYPE&	GetAt(int i_index)
	{
		int Size = GetSize();
		ASSERT(0 <= i_index && i_index < GetSize());
		return (GetData()[i_index]);
	};
	/*
	 * Method:		OCArray::operator[]
	 * Parameters:	i_index		the array index to access
	 * Returns:		TYPE&		reference to the element at the index
	 * Author:		Russell Robinson
	 * Purpose:
	 *		To return an element of the array for possible modification.
	 *		This method is needed because the compiler loses the base class's method.
	 */
	inline TYPE&	operator[](int i_index)
	{
		ASSERT(0 <= i_index && i_index < GetSize());
		return (GetData()[i_index]);
	};
};

#endif // !defined(AFX_OCARRAY_H__BE2C5983_CE26_11D3_BAE6_0000C0D475E2__INCLUDED_)
