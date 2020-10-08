#ifndef CRYPTO_H
#define CRYPTO_H
#include <openssl/err.h>
#include <openssl/aes.h>

#include <QCryptographicHash>

#ifdef QT_DEBUG
#include <QDebug>
#endif

#define AES_KEYLENGTH 256

// TODO : finish section and switch to EVP API (openssl)

namespace mariongiciel::core {

static inline QByteArray _SALT_ = QCryptographicHash::hash(QByteArrayLiteral("_MarionGiciel_"), QCryptographicHash::Keccak_256);

static inline QByteArray _KEY_ = []()->QByteArray {
        QByteArray key256;
        for(auto &i : {0, 1, 2, 3, 4, 5, 6, 7})
        {
            Q_UNUSED(i)
            key256 = key256 + QCryptographicHash::hash(QByteArrayLiteral("_m_a_r_i_o_n_"), QCryptographicHash::Sha3_256);
        }
        return key256;
}();

// extern C

inline QByteArray encryptAES(const QByteArray &text)
{
    QByteArray inputText = text.toHex() + _SALT_.toHex();

    unsigned char aes_input[text.length()];
    unsigned char aes_key[AES_KEYLENGTH];

    memset(aes_input, 0x00, text.length());
    memset(aes_key, 0x00, AES_KEYLENGTH);

    strcpy(reinterpret_cast<char*>(aes_input),text.toStdString().c_str());
    strcpy(reinterpret_cast<char*>(aes_key), _KEY_.toStdString().c_str());

    /* init vector */
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);

    /* buffers for encryption */
    unsigned char enc_out[text.length()];
    memset(enc_out, 0x00, sizeof(enc_out));

    AES_KEY enc_key;
    AES_set_encrypt_key(aes_key, AES_KEYLENGTH, &enc_key);
    AES_cbc_encrypt(aes_input, enc_out, text.length(), &enc_key, iv, AES_ENCRYPT);

    return QByteArray(reinterpret_cast<char*>(enc_out), sizeof (enc_out));
}

inline QByteArray decryptAES(const QByteArray &text)
{
    unsigned char aes_input[text.length()];
    unsigned char aes_key[AES_KEYLENGTH];

    memset(aes_input, 0x00, text.length());
    memset(aes_key, 0x00, AES_KEYLENGTH);

    strcpy(reinterpret_cast<char*>(aes_input),text.toStdString().c_str());
    strcpy(reinterpret_cast<char*>(aes_key), _KEY_.toStdString().c_str());

    /* init vector */
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);


    /* buffers for encryption */
    unsigned char dec_out[text.length()];
    memset(dec_out, 0x00, sizeof(dec_out));

    memset(iv, 0x00, AES_BLOCK_SIZE);

    AES_KEY dec_key;
    AES_set_decrypt_key(aes_key, AES_KEYLENGTH, &dec_key);
    AES_cbc_encrypt(aes_input, dec_out, text.length(), &dec_key, iv, AES_DECRYPT);

    return QByteArray(reinterpret_cast<char*>(dec_out), sizeof (dec_out));
}

} // END NAMESPACE mariongiciel::core

#endif // CRYPTO_H



