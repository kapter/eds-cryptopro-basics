/*
 * Copyright(C) 2000-2007 ������ ���
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
 * \version $Revision: 2781 $
 * \date $Date: 2010-10-27 17:36:46 +0400 (ср, 27 окт 2010) $
 * \author $Author: lse $
 *
 * \brief ������ �������, �������������� ��������� � ��. �������� ���������.
 */
#ifndef _PLATFORMSTREAM_H
#define _PLATFORMSTREAM_H

#ifdef UNIX
# ifdef CSP_LITE 
#  if !defined htonl && !defined htons
#   ifdef WORDS_BIGENDIAN
#     define htonl(a) (a)
#     define htons(a) (a)
#     define ntohl(a) (a)
#     define ntohs(a) (a)
#   else /* WORDS_BIGENDIAN */
#     define htons(x) \
     ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))
#     define htonl(x) \
     ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |               \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))
#     define ntohs(x) htons(x)
#     define ntohl(x) htonl(x)
#   endif /* WORDS_BIGENDIAN */
#  endif
# else /* CSP_LITE */
#   include <netinet/in.h>
# endif /* CSP_LITE */
#endif /* UNIX */

#ifdef __cplusplus
extern "C" {
#endif

#include<CPROCSP/BaseArithmDef_64.h>

#if !defined(__inline) && !defined(_WIN32)
#   define __inline     inline
#endif // !defined(__inline) && !defined(_WIN32)

#ifdef _WIN32
#ifdef _M_IX86
#define htons fast_htons
#define ntohs htons
#define htonl fast_htonl
#define ntohl htonl

#pragma warning(disable:4035)

__inline unsigned short
fast_htons (unsigned short hostshort)
{
unsigned short retax = hostshort;
__asm {
		ror retax, 8
	}
return retax;
}

__inline unsigned long
fast_htonl (unsigned long hostlong)
{
    unsigned long reteax=hostlong;
	__asm {
		mov eax, reteax
		bswap eax
		/*ror ax, 8
		ror eax, 16
		ror ax, 8*/
		mov reteax, eax
	}
    return reteax;
}
#pragma warning(default:4035)

#elif defined DEVL && defined _WIN64 /* ! _M_IX86 */
#define htons fast_htons
#define ntohs htons
#define htonl fast_htonl
#define ntohl htonl

__inline unsigned short
fast_htons (unsigned short hostshort)
{
    return ( hostshort << 8 ) | ( hostshort >> 8 );
}
__inline unsigned long
fast_htonl (unsigned long hostlong)
{
    return ( hostlong >> 24 ) 
	| ( ( hostlong >> 8 ) & 0xff00 )
	| ( hostlong << 8 ) & 0xff0000
	| ( hostlong << 24 );
}
#endif /* _M_IX86 */
#endif /*_WIN32*/

static __inline
DWORD
letohl_loc (const unsigned char * pcn)
{
    DWORD tc = 0;
    tc = (DWORD)(*(pcn));
    tc ^= ((DWORD)(*(pcn+1))) << 8;
    tc ^= ((DWORD)(*(pcn+2))) << 16;
    tc ^= ((DWORD)(*(pcn+3))) << 24;
    return tc;
}

static __inline
void
htolelxor (unsigned char * pcn, DWORD hostlong)
{
    *(pcn) ^= (unsigned char)(hostlong & (DWORD)0xff);
    hostlong >>= 8;
    *(pcn+1) ^= (unsigned char)(hostlong & (DWORD)0xff);
    hostlong >>= 8;
    *(pcn+2) ^= (unsigned char)(hostlong & (DWORD)0xff);
    hostlong >>= 8;
    *(pcn+3) ^= (unsigned char)(hostlong & (DWORD)0xff);
}

static __inline
void letohs_ref(void *pch, const void * pcn)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[1] = t;
#elif defined (_WIN64)  || defined (_M_ARM)
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[1] = ((BYTE *)pcn)[1];
#else
    *(WORD *)pch = *(WORD *)pcn;
#endif
}

static __inline
void htoles_ref(void * pcn, const void *pch)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[1];
    ((BYTE *)pcn)[1] = t;
#elif defined (_WIN64)  || defined (_M_ARM)
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[1] = ((BYTE *)pch)[1];
#else
    *(WORD *)pcn = *(WORD *)pch;
#endif
}

static __inline
void letohl_ref(void *pch, const void * pcn)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[3];
    ((BYTE *)pch)[3] = t;
                   t = ((BYTE *)pcn)[2];
    ((BYTE *)pch)[2] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[1] = t;
#elif defined (_WIN64) || defined (_M_ARM)
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[1] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[2] = ((BYTE *)pcn)[2];
    ((BYTE *)pch)[3] = ((BYTE *)pcn)[3];
    
#else
/*    *(DWORD *)pch = *(DWORD *)pcn; */
/* ����� ������������� ��� alignment?
 * ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
 * � ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
 */
    if(pch!=pcn)		/* made valgrind happy */
	memcpy(pch, pcn, sizeof(DWORD));
#endif
}

static __inline
void htolel_ref(void *pcn, const void *pch)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[3];
    ((BYTE *)pcn)[3] = t;
                   t = ((BYTE *)pch)[2];
    ((BYTE *)pcn)[2] = ((BYTE *)pch)[1];
    ((BYTE *)pcn)[1] = t;
#elif defined (_WIN64)  || defined (_M_ARM)
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[1] = ((BYTE *)pch)[1];
    ((BYTE *)pcn)[2] = ((BYTE *)pch)[2];
    ((BYTE *)pcn)[3] = ((BYTE *)pch)[3];
#else
/*    *(DWORD *)pcn = *(DWORD *)pch; */
/* ����� ������������� ��� alignment?
 * ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
 * � ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
 */
    memcpy(pcn, pch, sizeof(DWORD));
#endif
}

static __inline
DWORD letohl_ptr(const void * pcn)
{
    DWORD hdw;
    letohl_ref(&hdw, pcn);
    return hdw;
}

static __inline
void htolel_ptr(void *pcn, DWORD hdw)
{
    htolel_ref(pcn, &hdw);
}

static __inline
void    dw_set(void *pdwdst, DWORD dwsrc) {
    *(DWORD *)pdwdst = dwsrc;
}

static __inline
DWORD   dw_ptr(const void *pdwsrc) {
    return *(DWORD *)pdwsrc;
}

static __inline
void
htolel_XOR(unsigned char * pcn, DWORD ln)
{
#ifdef WORDS_BIGENDIAN
    htolelxor(pcn, ln);
#elif defined (_WIN64)  || defined (_M_ARM)
    {
	DWORD dwln=ln;
	((BYTE *)pcn)[0] ^= ((BYTE *)&dwln)[0];
	((BYTE *)pcn)[1] ^= ((BYTE *)&dwln)[1];
	((BYTE *)pcn)[2] ^= ((BYTE *)&dwln)[2];
	((BYTE *)pcn)[3] ^= ((BYTE *)&dwln)[3];
    }
#else
    *(DWORD *)pcn ^= ln;
#endif
}
 
/*! \defgroup grpLittlEndian2Host ������������ ��������� �������������� ������ 
 * �������������� ������ � � �� Littl� Endian ������������� ������. 
 * ����������������� �������������� ���������� ������ 
 * Littl� Endian ������������� ������. 
 */

/* Needed: dwDWBufLen * sizeof(DWORD) >= dwByteLen*/
/*! \internal 
 * \ingroup grpLittlEndian2Host
 * \brief ������� ����������� ����� � ����� �� ������ Littl� Endian. 
 * ��������� �� ��������� ����������� ���� �� �����.
 * \param pdwBuff [out] ��������� �� ������ ������. 
 * \param pcv [in] ��������� �� �����.
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 * \param dwByteLen [in] ����� ������ � ������.
 * Needed: dwDWBufLen * sizeof(DWORD) >= dwByteLen.
 */
static __inline
void
letohl_dwbuf(DWORD *pdwBuff, const void *pcv, DWORD dwDWBufLen, DWORD dwByteLen)
{
    int i=0, j
	,nRest = (int)dwByteLen % (int)sizeof(DWORD)
	,nFullDW = (int)dwByteLen / (int)sizeof(DWORD);
    const LPBYTE pcn=(LPBYTE)pcv;
    if(nFullDW) {
	for(i=0;i<nFullDW;i++) {
	    letohl_ref(pdwBuff + i, pcn + i*sizeof(DWORD));
	}
    }
    if(nRest) {
	DWORD dw = 0;
	for(j=nRest-1;j>=0;j--){
	    dw <<= 8;
	    dw ^= (DWORD)(*(pcn+ i*sizeof(DWORD)+j));
	}
        dw_set(pdwBuff + i, dw);
	i++;
    }
    if(dwDWBufLen - nFullDW) 
	for(;i<(int)dwDWBufLen;i++) dw_set(pdwBuff + i, 0);
}

/*! \internal 
 * \ingroup grpLittlEndian2Host
 * \brief ������� ����������� ����� � ����� �� ������ Littl� Endian. 
 * \param pdwBuff [out] ��������� �� ������ ������. 
 * \param pcn [in] ��������� �� �����.
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 */
static __inline
void
letohl_dwbuf3(DWORD *pdwBuff, const BYTE *pcn, DWORD dwDWBufLen)
{
    unsigned i;
    for(i=0; i<dwDWBufLen; i++) {
	letohl_ref(pdwBuff + i, pcn + i*sizeof(DWORD));
    }
}

/* Needed: dwDWBufLen * sizeof(DWORD) = dwByteFull + dwByteLen
 * ��������� �� ��������� ����������� ���� �� �����.
 * 
 * pdwBuff- ��������� �� ����������� �����.
 * pcn - ������� �������� �����.
 * dwByteFull - ����� ����������� ������.
 * dwDWBufLen - ����� ������ pdwBuff � DWORD.
 * dwByteLen - ����� ����������� ������ � ������ pcn, 
 * �.�. dwDWBufLen * sizeof(DWORD) = dwByteFull + dwByteLen.
*/
/*! \internal 
 * \ingroup grpLittlEndian2Host
 * \brief ������� ��������� �� ��������� ����������� 
 * ���� �� ����� �� ������ Littl� Endian. 
 *
 * \param pdwBuff [in] ��������� �� ������ ������. 
 * \param pcn [in] ��������� �� ������� �������� �����.
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 * \param dwByteLen [in] ����� ����������� ������ � ������ pcn.
 * Needed: dwDWBufLen * sizeof(DWORD) = dwByteFull + dwByteLen.
 * \return TRUE ��� �������� ����������, FALSE � ��������� ������.
 */
static __inline
CSP_BOOL
letohl_compldwbuf(DWORD * pdwBuff, const unsigned char * pcn
	    , DWORD dwDWBufLen, DWORD dwByteFull, DWORD dwByteLen)
{
    int i, j
    	,nCompl = (int)dwByteLen % (int)sizeof(DWORD)
	,nFullDW = (int)dwByteFull / (int)sizeof(DWORD);
    DWORD Temp = 0;
    if((dwDWBufLen*sizeof(DWORD)) != (dwByteFull+dwByteLen))
	return FALSE;
    if(nCompl) {
	for(j=nCompl-1;j>=0;j--){
	    Temp <<= 8;
	    Temp ^= (DWORD)(*(pcn +j));
	}
	Temp <<= (8*(sizeof(DWORD)-nCompl));
	pdwBuff[nFullDW] ^= Temp;   /* ?????? */
	nFullDW++;
	pcn+=nCompl;
    }
    if(nFullDW < (int)dwDWBufLen) {
	for(i=nFullDW,j=0;i<(int)dwDWBufLen;i++,j++) {
	    letohl_ref(pdwBuff + i, pcn + j*sizeof(DWORD));
	}
    }
    return TRUE;
}

#if !defined WORDS_BIGENDIAN
/*! \internal
 * \ingroup grpLittlEndian2Host
 * \brief ������� �������������  ����� � �����. 
 * \param pcn [out] ��������� �� �����.
 * \param pdwBuff [in] ��������� �� ������ ������. 
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 */
static __inline
void
htolel_dwbuf(void *pcn, const void *pdwBuff, DWORD dwDWBufLen)
{
    if(pcn!=pdwBuff)		/* made valgrind happy */
	memcpy(pcn, pdwBuff, sizeof(DWORD)*dwDWBufLen);
}

static __inline
CSP_BOOL
qwtodw_buf(uint64_t *pcq, const DWORD *pdwBuff, DWORD dwLen)
{
    if ( dwLen%2 )
	return FALSE;
    if((void*)pcq!=(void*)pdwBuff)		/* made valgrind happy */
	memcpy ( pcq, pdwBuff, sizeof(DWORD)*dwLen );
    return TRUE;
}

static __inline
void
dwtoqw_buf(DWORD* pcd, const uint64_t *pqwBuff, DWORD qwLen)
{
    if(pcd!=(void*)pqwBuff)		/* made valgrind happy */
	memcpy ( pcd, pqwBuff, sizeof(uint64_t)*qwLen );
}

static __inline
void
htoleq_qwbuf(unsigned char *pcn, const uint64_t *pqwBuff, DWORD qwBufLen)
{
    memcpy ( pcn, pqwBuff, sizeof(uint64_t)*qwBufLen);
}

static __inline
CSP_BOOL
letohq_qwbuf(uint64_t *pqwBuff, const unsigned char *pcn, DWORD dwByteLen)
{
    if ( dwByteLen%8 )
	return FALSE;
    memcpy ( pqwBuff, pcn, dwByteLen);
    return TRUE;
}
#else /*WORDS_BIGENDIAN*/
static __inline
void
htolel_dwbuf(void *pcn, const void *pdwBuff, DWORD dwDWBufLen)
{
    for(DWORD i=0; i<dwDWBufLen; i++) {
      htolel_ref((char*)pcn + i*sizeof(DWORD), (char*)pdwBuff + i*sizeof(DWORD));
    }
}

static __inline
CSP_BOOL
qwtodw_buf(uint64_t *pcq, const DWORD *pdwBuff, DWORD dwLen)
{
    if ( dwLen%2 )
	return FALSE;
    for ( ; dwLen; dwLen -= 2 ) {
	union {
	    uint64_t q;
	    DWORD d[2];
	} t;
	t.d[1] = *pdwBuff++;
	t.d[0] = *pdwBuff++;
	*pcq++ = t.q;
    }
    return TRUE;
}

static __inline
void
dwtoqw_buf(DWORD* pcd, const uint64_t *pqwBuff, DWORD qwLen)
{
    for ( ; qwLen; qwLen-- ) {
	union {
	    uint64_t q;
	    DWORD d[2];
	} t;
	t.q = *pqwBuff++;
	*pcd++ = t.d[1];
	*pcd++ = t.d[0];
    }
}

static __inline
void
htoleq_qwbuf(unsigned char *pcn, const uint64_t *pqwBuff, DWORD qwBufLen)
{
    for ( ; qwBufLen; qwBufLen-- ) {
	union {
	    uint64_t q;
	    BYTE b[8];
	} t;
	t.q = *pqwBuff++;
	*pcn++ = t.b[7];
	*pcn++ = t.b[6];
	*pcn++ = t.b[5];
	*pcn++ = t.b[4];
	*pcn++ = t.b[3];
	*pcn++ = t.b[2];
	*pcn++ = t.b[1];
	*pcn++ = t.b[0];
    }
}

static __inline
CSP_BOOL
letohq_qwbuf(uint64_t *pqwBuff, const unsigned char *pcn, DWORD dwByteLen)
{
    if ( dwByteLen%8 )
	return FALSE;
    for ( ; dwByteLen; dwByteLen-- ) {
	union {
	    uint64_t q;
	    BYTE b[8];
	} t;
	t.b[7] = *pcn++;
	t.b[6] = *pcn++;
	t.b[5] = *pcn++;
	t.b[4] = *pcn++;
	t.b[3] = *pcn++;
	t.b[2] = *pcn++;
	t.b[1] = *pcn++;
	t.b[0] = *pcn++;
	*pqwBuff++ = t.q;
    }
    return TRUE;
}
#endif /* !WORDS_BIGENDIAN */

#ifdef __cplusplus
}
#endif

#endif /* _PLATFORMSTREAM_H */
