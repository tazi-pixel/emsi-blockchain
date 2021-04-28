#include "hblk_crypto.h"

/**
 * it sign a given set of bytes using a given EC_KEY private key
  * msglen: message length
 * sig: holds the address at which to store the signature
 * key: points to the EC_KEY structure containing the private key
 * msg: points to the msglen characters to be signed
 * Return a pointer to the signature buffer, or NULL upon failure
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen,
		 sig_t *sig)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];

	if (!key || !msg || !sig)
		return (NULL);
	if (!EC_KEY_check_key(key))
		return (NULL);
	if (!SHA256(msg, msglen, hash))
		return (NULL);
	sig->len = ECDSA_size(key);
	if (!sig->len)
		return (NULL);
	if (!ECDSA_sign(EC_CURVE, hash, SHA256_DIGEST_LENGTH, sig->sig,
			(unsigned int *)&(sig->len), (EC_KEY *)key))
		return (NULL);
	return (sig->sig);
}
