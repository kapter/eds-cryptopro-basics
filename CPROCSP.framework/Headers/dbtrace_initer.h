/*
 * Copyright(C) 2004 ������ ���
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
 * \version $Revision: 42695 $
 * \date $Date: 2007-10-05 09:20:31 +0400 (пт, 05 окт 2007) $
 * \author $Author: dim $
 *
 * \brief ������� � ������� ��� ���������� ������.
 */

#ifndef _DBTRACE_INITER_H_INCLUDED
#define _DBTRACE_INITER_H_INCLUDED

#include<CPROCSP/reader/dprint.h>

class DbTraceInitializer
{
    TSupportDbContext ** m_ptr_db_ctx;
  public:
    DbTraceInitializer (const TCHAR *name, TSupportDbContext *& ref_db_ctx);
    ~DbTraceInitializer (void);
  private:
    DbTraceInitializer(const DbTraceInitializer&);
    DbTraceInitializer& operator=(const DbTraceInitializer&);
};

#endif /* _DBTRACE_INITER_H_INCLUDED */
