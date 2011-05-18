/* [Windows 1251]
 * [Use `iconv -f WINDOWS-1251', if needed]
 */
/*
 * Copyright(C) 2005-2011
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������-���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������-���.
 *
 * This is proprietary information of
 * Crypto-Pro company.
 *
 * Any part of this file can not be copied, 
 * corrected, translated into other languages,
 * localized or modified by any means,
 * compiled, transferred over a network from or to
 * any computer system without preliminary
 * agreement with Crypto-Pro company
 */

/*!
 * \version $Revision: 67479 $
 * \date $Date: 2011-04-14 17:24:49 +0400 (чт, 14 апр 2011) $
 * \author $Author: dedal $
 *
 * \brief ��������� �������� �� ����������
 *
 */

#ifndef _UNIXENROLL_H
#define _UNIXENROLL_H

#include <string>
#include <memory>
#include <list>
#include <vector>
#include<CPROCSP/CSP_WinCrypt.h>
#include<CPROCSP/SecureBuffer.h>
#include<CPROCSP/BSTR.h>

#if __GNUC__==2
typedef std::basic_string <wchar_t> std::wstring;
#endif

// TODO:X ���� ����������� ��������� MonoTouch � ��. �������� ����� 
// ������ �� � namespace ru::CryptoPro

#define XECR_PKCS10_V2_0     0x1
#define XECR_PKCS7           0x2
#define XECR_CMC             0x3
#define XECR_PKCS10_V1_5     0x4

// BSTR SysAllocStringLen( const wchar_t *str, unsigned int cch);

// TODO:X cpcrypt_store_handle - ��������� ���������, ��� ������� 
// ����������� � ��������� ����� UnixEnroll
struct cpcrypt_store_handle
{
    cpcrypt_store_handle(): store_(0), trust_(false) {}
    ~cpcrypt_store_handle();

    bool open(
	const std::wstring & store,
        bool issystem,
	unsigned long flags = CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG );

    bool open(
	const std::wstring & store,
	unsigned long flags = CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG | CERT_SYSTEM_STORE_CURRENT_USER);
    HANDLE store_;
    bool trust_;
private:
    // ����������� ���������
    cpcrypt_store_handle& operator=( const cpcrypt_store_handle& handle);
    cpcrypt_store_handle( const cpcrypt_store_handle& handle);
};

/*! \ingroup EnrollAPI
 *  \brief �������� �������� �� ���������� � ��������� 
 *	   ���������� ������������
 *
 *  \xmlonly <locfile><header>UnixEnroll.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 * 
 * �������� ��������� �������� ICertEnroll �� Microsoft CryptoAPI.
 */
class UnixEnroll
{
public:
    /*! \ingroup EnrollAPI
     *  \brief ��������� �������� ������������
     *
     *  \xmlonly <locfile><header>UnixEnroll.h</header><ulib>libenroll.so</ulib></locfile>\endxmlonly
     */
    class UserCallbacks
    {
    public:
	/*! 
	 *  \brief ������ �� ���������� ��������� ����������� � 
	 *         ��������� ���������� ������������
	 *
	 *  \param pbCert   [in] ��������������� ����������
	 *  \param cbCert   [in] ����� �����������
	 *
	 *  \return true - � ������ �������� �� ��������� �����������
	 *
	 *  \note ������������� �� �����������, ���� ������������ 
	 *        put_SupressAddRootUI()
	 */
	virtual bool askPermissionToAddToRootStore( 
		const BYTE* pbCert, DWORD cbCert, bool = false) const=0;

	/*! 
	 *  \brief ������������
	 */
	virtual UserCallbacks* clone() const=0;

	/*! 
	 *  \brief ����������
	 */
	virtual ~UserCallbacks() {}
    };
public:
    /*! 
     *  \brief �����������
     *
     *  \param callbacks    [in] ������� ������� � ������������
     *  \param handlePKCS7  [in] � ������ ������ �� ������������
     */
    UnixEnroll(
	const UserCallbacks& callbacks,
	bool handlePKCS7 = false);

    /*! 
     *  \fn UnixEnroll::~UnixEnroll
     *  \brief ����������
     */
    ~UnixEnroll();

    /*!
     *  \brief ���������� �������� S/MIME � ������ PKCS#10 (�� �����������)
     *
     *  \param value	[in] TRUE - ����������.
     *
     *	\return S_OK - � ������ ������ 
     */
    HRESULT put_EnableSMIMECapabilities( bool value)
    { (void)(value); return S_OK; }
    
    /*! 
     *  \brief ������������ ������������ ���� � ���������� (�� �����������)
     *
     *  \param value	[in] TRUE - ������������, FALSE - ������� �����.
     *
     *	\return S_OK - � ������ ������ 
     */
    HRESULT put_UseExistingKeySet(bool value);
    
    /*! 
     *  \brief ������ �������� ���-������� ��� PKCS#10 (�� �����������)
     *
     *  \param hashOid	[in] OID ���-�������.
     *
     *	\return S_OK - � ������ ������ 
     */
    HRESULT put_HashAlgorithm( BSTR hashOid)
    { hashAlgorithm_ = hashOid; return S_OK; }
    
    /*! 
     *  \brief ������ ��� ����������
     *
     *  ���� ��� ���������� �� ������, �� ��� ������������ ��� 
     *  ��������� GUID. 
     *
     *  \param cName	[in] ��� ����������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� ������������� UseExistingKeySet, ���������
     *  �������� ��� ����������.
     */
    HRESULT put_ContainerName( BSTR cName)
    { containerName_ = cName; return S_OK; }
    
    /*! 
     *  \brief ������ ��� CSP ��� �������� �����
     *
     *  ��� CSP ���������� �������� ��������� �����.
     *
     *  \param pType	[in] ��� CSP.
     *
     *	\return S_OK - � ������ ������ 
     */
    HRESULT put_ProviderType( DWORD pType)
    { providerType_ = pType; return S_OK; }
    
    /*! 
     *  \brief ������ ��� CSP ��� �������� �����
     *
     *  ���������� CSP � ������� �������� �������� ����.
     *
     *  \param pName	[in] ��� CSP.
     *
     *	\return S_OK - � ������ ������ 
     */
    HRESULT put_ProviderName( BSTR pName)
    { providerName_ = pName; return S_OK; }
    
    /*! 
     *  \brief ������ �������� ��������� �����
     *
     *  �� ��������� ������� ��������� ����� ��������, ��� ���
     *  ���������� ����� ������ CRYPT_EXPORTABLE. 
     *
     *  \param keyFlags	[in] ����� �������� ��������� �����.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ������ ������ ������ ������ � �������� CPGenKey() � CryptGenKey().
     */
    HRESULT put_GenKeyFlags( DWORD keyFlags)
    { keyFlags_ = keyFlags; return S_OK; }
    
    /*! 
     *  \brief ������ ��������� ������� � ����� ��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param storeFlags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    HRESULT put_RequestStoreFlags( DWORD storeFlags)
    { requestStoreFlags_ = storeFlags; return S_OK; };
    
    /*! 
     *  \brief ������ ����� �������� CSP
     *
     *  �������� �� ��������� 0.
     *
     *  \param provFlags [in] ����� �������� CSP.
     *
     *	\return S_OK - � ������ ������ 
     *  
     *  \note
     *  �������� �������������� ������ �������� CSP
     *  ������ � �������� CPAcquireContext() � CryptAcquireContext().
     */
    HRESULT put_ProviderFlags( DWORD provFlags)
    { provFlags_ |= provFlags; /* TODO:XXX ������ OR ??? */ return S_OK; }
    
    /*! 
     *  \brief ������ ��� ��������� �����
     *
     *  \param _dwKeySpec [in] ��� ��������� �����.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ������ ������������ ����:
     *	    - AT_KEYEXCHANGE - � ������������ ���������� ������ 
     *		����������, � ���;
     *	    - AT_SIGNATURE - ������ ���;
     *  
     *  \note
     *  ������ ��� �� �������� CPGenKey() � CryptGenKey().
     *
     *  \todo
     *  TODO:XXX � ������� �� ICertEnroll ��� �������� �� ��������� ???
     */
    HRESULT put_KeySpec( DWORD _dwKeySpec)
    { dwKeySpec = _dwKeySpec; return S_OK; }
    
    /*! 
     *  \brief ������ ����������� ����� AT_KEYEXCHANGE
     *
     *  \param value [in] ����������� ����� AT_KEYEXCHANGE.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� �������� ��������� ������ � ������ ���� AT_KEYEXCHANGE. ���
     *  ������ ���� AT_SIGNATURE ��� �������� ����� ���� ������������.
     *
     *  \note
     *  ���� �������� �������� FALSE (0), �� ������ �������� ��������� 
     *  �������� KeyUsage:
     *	    - CERT_DATA_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_KEY_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_DIGITAL_SIGNATURE_KEY_USAGE
     *	    - CERT_NON_REPUDIATION_KEY_USAGE
     *
     *  \note
     *  ���� �������� �������� TRUE (!=0), �� ������ �������� ��������� 
     *  �������� KeyUsage:
     *	    - CERT_DATA_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_KEY_ENCIPHERMENT_KEY_USAGE
     */
    HRESULT put_LimitExchangeKeyToEncipherment( int value)
    { limitExchangeKeyToEncipherment_ = value?true:false; return S_OK; }
    
    /*! 
     *  \brief ������ ��������� ������������� �� � ����� ��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param flags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    HRESULT put_CAStoreFlags( DWORD flags)
    { caStoreFlags_ = flags; return S_OK; }
    
    /*! 
     *  \brief ������ ��������� ������������ ������������ � ����� 
     *		��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param flags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    HRESULT put_MyStoreFlags( DWORD flags)
    { myStoreFlags_ = flags; return S_OK;  }
    
    /*! 
     *  \brief ������ ���������� ��������� �������� ������������ � 
     *		����� ��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param flags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    HRESULT put_RootStoreFlags( DWORD flags)
    { rootStoreFlags_ = flags; return S_OK;  }
    
    /*! 
     *  \brief ������ ��� ��������� ������������ ������������
     *
     *  �������� �� ��������� "My".
     *
     *  \param name [in] ��� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  �������� ��������� ��� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    HRESULT put_MyStoreName( BSTR name)
    { myStoreName_ = name; return S_OK;  }
    
    /*! 
     *  \brief ��������� �� ������� ���������������� � ��������� 
     *		�������� �� ����������
     *
     *  �������� �� ��������� true.
     *
     *  \param value [in] ��������� �� �������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� �������� ����� � ������� PKCS#10 �������� ����������������
     *  � ��������� ��������. �� ������ ��� ������ �� �������� ���� � ��.
     *  �� ��� ���, ���� �� �� ���������� ������ � �� ����� PKCS#7
     *  �����. �� ��������� PKCS#7 ������ � �������� ��������� 
     *  ������������ �����������, ���������������� ���������. ������,
     *  ��� ����� ������� ��� ������������ ����� ��������� �������� 
     *  ����� ����������������� ���������� �������� DeleteRequestCert
     *  � �������� false.
     */
    HRESULT put_DeleteRequestCert( bool value)
    { deleteRequest_ = value; return S_OK; }
    
    /*!
     *  \brief ��������� �� ������������� ���������� � �������� ���������
     *
     *  �������� �� ��������� false.
     *  \todo TODO:XXX � ������� �� ICertEnroll, � �������� ��� true ???
     *
     *  \param value [in] ��������� �� �������������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��������� ����������� � ��������� ������������� � ��� 
     *  ��������� � ��������� "My", � ��������, �������������
     *  ��� ���������� �������� ���������. ��� ������� �������� true,
     *  ���������� ������� ������ ����������� � ���������, �� �������� 
     *  �� ����� ���������� ������ ����, ���� �������� �������� �� 
     *  ������ ��������� ����������. � ���������, ���� ��� ��������
     *  true, �� �������� �������� (�����-�����, USB-�����, 
     *  USB-���� � �.�.) �� ���������, �� ������ ��������� �������� 
     *  ����� ����������������.
     * 
     *  \note
     *  ��� ����, ��� �� �� ���������� ������� ������ ����������� 
     *  ��������� ���������� �������� false.
     *
     *  \note
     *  ������������ ��������:
     *	    - acceptPKCS7()
     *
     *  \note
     *  ������ ����� �������� CPSetKeyParam() � CryptSetKeyParam().
     */
    HRESULT put_WriteCertToCSP( bool value)
    { writeToCSP_ = value; return S_OK; }
    
    /*!
     *  \brief ������ PIN (������) ����������
     *
     *  �������� �� ��������� - �� �����.
     *
     *  \param pin [in] PIN (������) ����������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ����� PIN (������) ��� �������� ������� ��� 
     *  ��������� ����������� ��� ������ � ������ CRYPT_SILENT 
     *  (��� ��� ������������� ���������� ���������� ��� ������������ 
     *  ���������� ������������ (TUI ��� GUI)).
     */
    HRESULT put_PIN( const CSecurePin& pin)
    { pin_.copy(pin); return S_OK; }
    
    /*!
     *  \brief �� ����������� ������������� ��� ��������� ���������
     *		����������� � ��������� ���������� ������������
     *
     *  �������� �� ��������� - false.
     *
     *  \param value [in] PIN (������) ����������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� ��������� �������� true, ����� 
     *  UnixEnroll::askPermissionToAddToRootStore()
     *  �� ����� ����������.
     */
    HRESULT put_SupressAddRootUI( bool value)
    { supressAddRootUi_ = value; return S_OK; }

    /*!
     *  \brief �������� ���������� � ������ �� ����������
     *
     *  \param flags [in] �������� �� ���������� ��������� (critical)
     *  \param name  [in] OID ����������
     *  \param value [in] ����������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ����� createRequest() ��������� ���������� � ������, � �����
     *  createPKCS10() ���.
     */
    HRESULT addExtensionToRequest( LONG flags, BSTR name, BSTR value) {
        std::vector<BYTE> binary;
        HRESULT hr = UnixEnroll::getMessageFromBSTR(value,binary);
        if( S_OK != hr ) {
            return hr;
        }
        
        const char *oid = ConvertBSTRToString(name);
        
        extensions_.push_back(Extension(oid, flags, binary) );

        delete[] oid;
        
        return S_OK;
    }

    /*! 
     *  \brief ���������� ��� ������ ��� ��������� ����������� � 
     *		���������
     *
     *  \param pdwStatus [out] ��� ������ ��� ��������� ����������� � 
     *				���������
     *
     *	\retval S_OK		������� (� pdwStatus ���������� ��� 
     *				������)
     *	\retval E_INVALIDARG	pdwStatus ��� �� ����� (==NULL)
     */
    HRESULT get_InstallToContainerStatus( DWORD *pdwStatus) {
        if(!pdwStatus) {
            return E_INVALIDARG;
        }
        *pdwStatus = installToContainerStatus_;
        return S_OK;
    }
    
    /*! 
     *  \brief ������� ������ PKCS#10
     *
     *  \param rdn     [in]  �������������� ��� (DN) ��������� �����
     *  \param usage   [in]  ������ OID ������������ ������������� 
     *			     ����� (Extended Key Usage (EKU))
     *  \param request [out] ������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ���������� ���������� �������� ������� addExtensionToRequest()
     *
     *	\note
     *	���������� BSTR ������ �������, ������ ���� ����������� 
     *  �������� SysFreeString()
     */
    HRESULT createPKCS10( BSTR rdn, BSTR usage, BSTR *request) {
        return createPKCSRequest(rdn, usage, request, false,false);
    }
    
    /*! \ingroup EnrollAPI
     *  \brief ������� ������ ����������
     *
     *  \param flags   [in]  ��� ������� �� ����������
     *  \param rdn     [in]  �������������� ��� (DN) ��������� �����
     *  \param usage   [in]  ������ OID ������������ ������������� 
     *			     ����� (Extended Key Usage (EKU))
     *  \param request [out] ������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  �������������� ��������� ���� �������� �� ����������:
     *	    - XECR_PKCS10_V1_5
     *	    - XECR_PKCS10_V2_0
     *
     *  \note
     *  ��������� ���������� �������� ������� addExtensionToRequest()
     *
     *	\note
     *	���������� BSTR ������ �������, ������ ���� ����������� 
     *  �������� SysFreeString()
     */
    HRESULT createRequest( LONG flags, BSTR rdn, BSTR usage, BSTR *request) {
        if( XECR_PKCS10_V2_0 == flags || XECR_PKCS10_V1_5 == flags ) {
            return createPKCSRequest(rdn, usage, request, true, false);
        } 
	else if (flags == XECR_PKCS7)
	{
            return createPKCSRequest(rdn, usage, request, true, true);
        }
	else
            return E_NOTIMPL;
    }
    
    /*! \ingroup EnrollAPI
     *  \brief ���������� PKCS#7 ����� �� ��
     *
     *  \param msg [in] PKCS#7 ���������, �������������� � BASE64, 
     *		        ������� �������� ���������� ��� ������� 
     *		        ������������ ��������������� �������
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ������� ������������, ��� ����� ��������� �������� ����������, 
     *  ��� � ���, � ����������� �� �������� ����������� ��. ����������,
     *  ����������� �� ��������� �������� ���� �� �������, ����������
     *  � ��������� MY. �������� ���������� ���������� � ���������
     *  ROOT, ��������� ����������� ������������� �� ���������� �
     *  ��������� CA. ���� � ��������� PKCS#7 ����������� �����-����
     *  �������� ����������, �� � ������������ ������������� 
     *  �������������.
     *  ������������ ����� ��������� ��������� ��������������� 
     *  ������������, ������� �� �� �������� �� ��� ��� ���� ��������.
     *  ����� ������������ � ��������� ������������ � ��������� ROOT
     *  �� �������� ������ ��� ���� ��������.
     *
     *  \note
     *  �� ��������� ������������ ���������: MY, CA, ROOT � REQUEST, 
     *  ������ ������������ ����� �������� ����� � ������� ��������� 
     *  �������:
     *	    - put_MyStoreName()
     */
    HRESULT acceptPKCS7( BSTR msg);
     /*! \ingroup EnrollAPI
     *  \brief ���������� ���������� ��� ������� ������������ PKCS#7
     *
     *  ����� installPKCS7Ex � ������� �� acceptPKCS7 �� ������������
     *  ��� ��������� ������������, ���������� �� ������� ������������.
     *  �� ������������ ������ ��� ��������� ����������� ��� �������
     *  � ����������� ��������� ������������.
     *
     *  \param msg [in] PKCS#7 ���������, �������������� � BASE64, 
     *		        ������� �������� ���������� ��� ������� 
     *
     *  \param plCertEncoded [out] ����� ������������, 
     *		        ������������� � ��������� ���������
     *
     *	\retval S_OK            �������
     *	\retval ERROR_CANCELLED �������� �������� ������������� 
     *
     *  \note
     *  ���� � ��������� PKCS#7 ����������� �����-����
     *  �������� ����������, �� � ������������ ������������� 
     *  ������������� �� ��� ���������.
     */
    HRESULT installPKCS7Ex( BSTR msg, LONG * plCertInstalled);
     /*! \ingroup EnrollAPI
     *  \brief ���������� ����������, �� ������� ����� �������� ������ � PKCS#7
     *  
     *
     *  \param pSignerCert  [in]  ���������� � ����������� 
     *	\retval S_OK            �������
     */
 
    HRESULT SetSignerCertificate(
      /* [in] */  PCCERT_CONTEXT pSignerCert
      );

private:
    static HRESULT getMessageFromBSTR( BSTR msg, std::vector<BYTE>& ret );
    HRESULT getCertificatesFromPKCS7(
	const BYTE* pbCert, DWORD cbCert,
	HCERTSTORE& hStore) const;
    HRESULT findCertificateInRequestStore(
	const BYTE* pbCert, DWORD cbCert,
	std::vector<BYTE>& foundedCert,
	cpcrypt_store_handle& store) const;
    HRESULT createCerificateContextFromRequestStore(
	const BYTE* pbCert, DWORD cbCert,
	PCCERT_CONTEXT& pCertContext,
	cpcrypt_store_handle& handle) const;
    HRESULT installCertificateToStore(
	PCCERT_CONTEXT pPrivateKeyCertContext,
	const BYTE* pbCert, DWORD cbCert);
    HRESULT processPKCS7(
	const BYTE* pbMsg, DWORD cbMsg,
	std::vector<BYTE>& certificate) const;
    HRESULT findRequestedCertificate(
	HCERTSTORE hStore,
	std::vector<BYTE>& certificate) const;
    HRESULT findIssuerOf(
	const BYTE* pbCert, DWORD cbCert,
	HCERTSTORE hStore,
	std::vector<BYTE>& issuer) const;
    bool isSelfSigned( const BYTE* pbCert, DWORD cbCert) const;
    HRESULT addCertificateToRootStore( const BYTE* pbCert, DWORD cbCert) const;
    HRESULT addCertificateToCAStore( const BYTE* pbCert, DWORD cbCert) const;
    HRESULT addCertificateToStore( const BYTE* pbCert, DWORD cbCert, cpcrypt_store_handle& store) const;
    std::string prepareKeyUsageString( const std::string& usage );
    HRESULT prepareKeyUsage(
	const std::string& usage, 
	std::vector<std::string>& usageArray);
    HRESULT createPKCSRequest( BSTR rdn, BSTR usage, BSTR *request, bool includeAddedExtensions,bool encodeToPKCS7);
    HRESULT encodeRequestToPKCS7(std::vector<BYTE>& Request); 

    HCRYPTPROV hProv;
    DWORD dwKeySpec;
    BSTR hashAlgorithm_;
    BSTR containerName_;
    DWORD providerType_;
    BSTR providerName_;
    DWORD keyFlags_;
    DWORD requestStoreFlags_;
    DWORD rootStoreFlags_;
    DWORD myStoreFlags_;
    DWORD caStoreFlags_;
    DWORD provFlags_;
    bool limitExchangeKeyToEncipherment_;
    BSTR myStoreName_;
    bool deleteRequest_;
    bool writeToCSP_;
    bool useExisting_;
    bool handlePKCS7_;
    std::auto_ptr<UserCallbacks> userCallbacks_;
    CSecurePin pin_;
    DWORD installToContainerStatus_;
    bool supressAddRootUi_;
    PCCERT_CONTEXT pSignerCertificate_;

    struct Extension {
        std::string oid;
        CSP_BOOL critical;
        std::vector<BYTE> value;

        Extension() {
        }

        Extension( 
            const char* argOid,
            LONG argCritical,
            const std::vector<BYTE>& argValue)
        : oid(argOid), critical(argCritical), value(argValue) {
        }
    };

    std::list<Extension> extensions_;
};

#endif /* _UNIXENROLL_H */
