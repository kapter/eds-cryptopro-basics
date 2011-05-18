#ifndef __BSTR_H__
#define __BSTR_H__

#ifdef UNIX
#include <wchar.h>
#include "CSP_WinDef.h"
typedef wchar_t* BSTR;

// Utility functions to work with BSTR
/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ wchar_t � BSTR
 *
 *  \param str [in] ����-��������������� ������ wchar_t
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */
BSTR SysAllocString( const wchar_t* str);

// Utility functions to work with BSTR
/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ wchar_t � BSTR
 *
 *  \param str [in] ����-��������������� ������ wchar_t ��� 0
 *  \param cch [in] ���������� �������� � ������
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */

BSTR SysAllocStringLen( const wchar_t *str, UINT cch);

/*! \ingroup EnrollAPI_support
 *  \brief ������������ BSTR ������
 *
 *  \param bStr [in] BSTR ������
 */
void SysFreeString( BSTR bStr);

/*! \ingroup EnrollAPI_support
 *  \brief ������������ BSTR ������
 *
 *  \param bStr [in] BSTR ������
    \return ����� ������
 */

UINT SysStringLen(BSTR bStr);

#else
//TODO: �������� header � BSTR
#endif
/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ � BSTR
 *
 *  \param str [in] ����-��������������� ������
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */

BSTR ConvertStringToBSTR( const char* str);

/*! \ingroup EnrollAPI_support
 *  \brief �������������� BSTR � ����-��������������� ������
 *
 *  \param bStr [in] BSTR ������
 *
 *  \return ���������� ������ ���� char *, ������ ���� 
 *	    ����������� ���������� delete[] 
 */
char* ConvertBSTRToString( BSTR bStr);



#endif

