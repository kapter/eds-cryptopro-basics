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
 * \version $Revision: 24643 $
 * \date $Date: 2005-03-18 17:56:59 +0300 (пт, 18 мар 2005) $
 * \author $Author: borodin $
 *
 * \brief ��������� ������ ��������� ������.
 */

#ifndef _CRYPTMEM_H_INCLUDED
#define _CRYPTMEM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if defined( __BOUNDSCHECKER__ )
#define CPSUPAllocMemory(dwSize) HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY, dwSize)
#define CPSUPFreeMemory(pMem)    HeapFree (GetProcessHeap (), 0, pMem)
#else  /* !defined( __BOUNDSCHECKER__ ) */

LPVOID SSPAPAllocMemory (ULONG dwSize);
CSP_BOOL   SSPAPFreeMemory (VOID *pMem);

LPVOID CPSUPAllocMemory (size_t dwSize);
CSP_BOOL   CPSUPFreeMemory (VOID *pMem);

#endif /* defined( __BOUNDSCHECKER__ ) */
CSP_BOOL CPSUPInitMemory (void);
void CPSUPDoneMemory (void);

#ifdef _CP_SSP_AP_
#define AllocMemory SSPAPAllocMemory
#define FreeMemory  SSPAPFreeMemory
#else
#define AllocMemory CPSUPAllocMemory
#define FreeMemory  CPSUPFreeMemory
#endif

#define InitMemory CPSUPInitMemory
#define DoneMemory CPSUPDoneMemory

#ifdef __cplusplus
}
#endif

#endif /* _CRYPTMEM_H_INCLUDED */
/* end of file: $Id: cryptmem.h 24643 2005-03-18 14:56:59Z borodin $ */
