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
 * \brief ��������� ������ ASN.1 ��������������.
 */

#ifndef _CPASN_H_INCLUDED
#define _CPASN_H_INCLUDED

#include<CPROCSP/../RuNetAsn/ms2ac.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ������������ ������*/
extern int CRYPT_STR_dup (LPBYTE src, DWORD len, BYTE **p, LPBYTE * pdst);
extern int CRYPT_UINT_BLOB_dup (CRYPT_UINT_BLOB * src, BYTE **p, CRYPT_UINT_BLOB ** pdst);

extern void
b_2_GostR3410_94_PublicKeyParameters(
    const ASN1OBJID * sign_param, const ASN1OBJID *dig_param, const ASN1OBJID * enc_param,
    GostR3410_94_PublicKeyParameters * dst );

/* ��������������� ������� ��� �������� ��� ��������� � BLOB ����������*/
extern void
b2e_STR (BYTE ** p, DWORD *plen, BYTE * src, DWORD len); /* BlobOpers.c */

CSP_BOOL
AlgorithmIdentifier_2_b (pCP_CALL_CTX pCallCtx, 
    AlgorithmIdentifier* src, ASN1OBJID* key_oid, ASN1OBJID* ph0UZ, ASN1OBJID* peUZ, ASN1OBJID* pPQA,
    const ASN1OBJID * OID_Cipher_Def_Def_);

/* ������� �������� ���������� ���������� �����. */
CSP_BOOL b_2_AlgorithmIdentifier( pCP_CALL_CTX pCallCtx, ASN1CTXT* pctxt, const ASN1OBJID *alg_oid, const ASN1OBJID *apq_ptr, 
    const ASN1OBJID *hash_params, const ASN1OBJID *cipher_params, AlgorithmIdentifier* pAlg );

/* ��������� ASN.1 ���������� �����. */
void set_private_key_attribute( GostPrivateKeyAttributes* pAttr,
    DWORD attr, 
    ALG_ID algid );

/* ��������� ASN.1 ���������� �����. */
CSP_BOOL get_private_key_attribute( GostPrivateKeyAttributes* pAttr,
    DWORD *attr, 
    ALG_ID *algid );

/*CSP_BOOL _bitValue - ����� �� �������� ���� ���� ���������*/
#define OSSETBITVALP( pBitStr, bitIndex, bitValue ) { \
int _bitValue = (bitValue)?1:0; \
if((_bitValue)) { \
    (pBitStr)->numbits = ((bitIndex)>=(pBitStr)->numbits)?((bitIndex+1)):((pBitStr)->numbits);\
    rtSetBit( (pBitStr)->data, (pBitStr)->numbits, (bitIndex) );\
} else if((bitIndex)==((pBitStr)->numbits-1)) {\
    rtClearBit( (pBitStr)->data, (pBitStr)->numbits, (bitIndex));\
    (pBitStr)->numbits--;\
} else if((bitIndex)<((pBitStr)->numbits-1))\
    rtClearBit( (pBitStr)->data, (pBitStr)->numbits, (bitIndex)); }


/* ���������� ������� ���� */
#define OSTESTBIT_CORRECT(bitStr,bitIndex) \
((OSTESTBIT((bitStr),(bitIndex)))?1:0)

#define OSTESTBITP_CORRECT(pBitStr,bitIndex) \
((OSTESTBITP((pBitStr),(bitIndex)))?1:0)

#ifdef __cplusplus
}
#endif

#endif /* _CPASN_H_INCLUDED */
/* end of file: $Id: cpasn.h 54220 2009-05-02 02:33:10Z lse $ */
