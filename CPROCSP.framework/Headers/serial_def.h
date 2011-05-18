/*
 * Copyright(C) 2000 ������ ���
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������ ���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������ ���.
 */

/*!
 * \file $RCSfile$
 * \version $Revision: 57277 $
 * \date $Date: 2009-09-25 19:37:44 +0400 (пт, 25 сен 2009) $
 * \author $Author: raa $
 *
 * \brief ��������� � ������ ��������� � ������������ ��������� ������ ��������.
 */

#ifndef _SERIAL_DEF_H_INCLUDED
#define _SERIAL_DEF_H_INCLUDED

// ������ ���� � �������������� 5��� ���� 
#define SERIAL_DATE_5BIT_DATE_LEN 13
// ������ ��� �� ����
#define SERIAL_DATE_5BIT_HASH_LEN 52
// ������ ������� ���� ���� 
#define SERIAL_DATE_5BIT_LEN (SERIAL_DATE_5BIT_DATE_LEN + SERIAL_DATE_5BIT_HASH_LEN)

// ������������ ������ ����� ��������
/* XXX test */
#ifdef LINUX 
#define SERIAL_COMPANY_MAX 20
#else
#define SERIAL_COMPANY_MAX 255
#endif

// ������ ��������� ������
#define SERIAL_PRODUCTID_DATA_LEN 17
// ������ ����������� ����� ��������� ������
#define SERIAL_PRODUCTID_CONTROL_LEN 8
// ������ ������ ��������� ������ 
#define SERIAL_PRODUCTID_LEN (SERIAL_PRODUCTID_DATA_LEN+SERIAL_PRODUCTID_CONTROL_LEN)
// ������ ��������� ������ � -
#define SERIAL_PRODUCTID_DATA_DASH_LEN 20
// ������ ����������� ����� ��������� ������ � -
#define SERIAL_PRODUCTID_CONTROL_DASH_LEN 9
// ������ ������ ��������� ������ � -
#define SERIAL_PRODUCTID_DASH_LEN (SERIAL_PRODUCTID_DATA_DASH_LEN + SERIAL_PRODUCTID_CONTROL_DASH_LEN )
// ����� ������ � ����������
#define LICENSE_FILES_MASK _TEXT("*.lic")

/* ��������, ����������� ��, �� ���� ��������������������. */
#define LIC_ALLOW_NOTHING   0
/* ���� � ��������, ����������� �����������. */
#define LIC_ALLOW_SIGN	    1<<0
/* ���� � ��������, ����������� ������������� �����. */
#define LIC_ALLOW_DH	    1<<1
/* ���� � ��������, ����������� �������������. */
#define LIC_ALLOW_ENCRYPT   1<<2
/* ���� � ��������, ����������� ��������������. */
#define LIC_ALLOW_DECRYPT   1<<3
/* ���� � ��������, ����������� ����� ��������. */
#define LIC_ALLOW_ALL	    0xffff

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SerialConfiguration_
{
    const TCHAR *PRODUCT_CODES;
    const unsigned *SECRET;
    size_t PRODUCT_LEN;
    const TCHAR *PRODUCT_ID;
    const TCHAR *PRODUCT_ID_PATH;
    const TCHAR *DATE_PATH;
    const TCHAR *LAST_SHOW_DIALOG_PATH;
#if defined _WIN32
    const TCHAR *SECRET_PATH;
#endif
} SerialConfiguration;

#ifdef __cplusplus
}
#endif


#endif /* _SERIAL_DEF_H_INCLUDED */
