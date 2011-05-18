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
 * \version $Revision: 54220 $
 * \date $Date: 2009-05-02 06:33:10 +0400 (сб, 02 май 2009) $
 * \author $Author: lse $
 *
 * \brief ��������� Microsoft Cryptography Service Provider.
 *
 * �������� ��������� ������� ����������������� ��������� ������ ������ CPC.
 */
#ifndef _LFMM_H_INCLUDED
#define _LFMM_H_INCLUDED

#include <wincspc.h>

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

typedef struct CPC_LFMM_CONFIG_ {
    CPC_INTERLOCKED_FUNCS   interlockedFuncs;
    LPVOID		    Buffer;
    LONG		    Size;
    CSP_BOOL		    fSMP;
    CSP_BOOL		    fStat;
    LONG 		    *PoolSizes;
    DWORD		    nPools;
    DWORD		    nCPUs;
} CPC_LFMM_CONFIG, * LPCPC_LFMM_CONFIG;

typedef DWORD CPCAPI CPCInitMemoryLF_t(
    /* [out] */ LPCPC_MEMORY_ARENA* pArena,
    /* [in] */ LPCPC_LFMM_CONFIG pCfg
);

#if !defined(CSP_LITE) || defined(LINUX) || defined(SOLARIS)
	// ��� ������������� ���������, � ��� �� � Linux � Solaris
	// ������� �������� �����.
#elif defined(FREEBSD)
    // ?????
    #define LFMM_SEPARATE_NAMESPACE_BINDING 1
#elif !defined(UNIX)
    // #include "cpdrvlib.h"
    // IOCTL_GETCPCINITMEMORYLF
    #define LFMM_SEPARATE_NAMESPACE_BINDING 1
#endif

#if !defined(LFMM_SEPARATE_NAMESPACE_BINDING)
    CPCInitMemoryLF_t CPCInitMemoryLF;
#endif

#if defined(__cplusplus)
} // extern "C"
#endif // defined(__cplusplus)

#endif /* _LFMM_H_INCLUDED */