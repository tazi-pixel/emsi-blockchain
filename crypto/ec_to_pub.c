#include <stdlib.h>
#include <stdio.h>

#include "hblk_crypto.h"

/**
 * ec_to_pub - extracts public key from EC_KEY struct
 * @key: pointer to EC_KEY struct
 * @pub: address of buffer to populate with pub key
 * Return: address of populated buffer or NULL
 */

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
const EC_POINT *publicKey;
const EC_GROUP *group;
BN_CTX *ctx;
point_conversion_form_t form;
if (key == NULL)
return (NULL);
publicKey = EC_KEY_get0_public_key(key);
if (publicKey == NULL)
return (NULL);
group = EC_KEY_get0_group(key);
if (group == NULL)
return (NULL);
form = POINT_CONVERSION_UNCOMPRESSED;
ctx = BN_CTX_new();
if (!EC_POINT_point2oct(group, publicKey, form, pub,
			EC_PUB_LEN, ctx))
return (NULL);
BN_CTX_free(ctx);
return (pub);
}
