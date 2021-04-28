#include <stdlib.h>
#include <stdio.h>

#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
EC_KEY *key = NULL;
EC_POINT *pubKey = NULL;
EC_GROUP *group = NULL;
BN_CTX *ctx;
if (!pub)
return (NULL);
key = EC_KEY_new_by_curve_name(EC_CURVE);
if (key == NULL)
return (NULL);
group = (EC_GROUP *)EC_KEY_get0_group(key);
if (group == NULL)
{
EC_KEY_free(key);
return (NULL);
}
pubKey = EC_POINT_new(group);
ctx = BN_CTX_new();
if (!EC_POINT_oct2point(group, pubKey, pub,
			EC_PUB_LEN, ctx))
goto clean;
if (!EC_KEY_set_public_key(key, pubKey))
goto clean;
EC_POINT_free(pubKey);
BN_CTX_free(ctx);
return (key);
clean:
EC_KEY_free(key);
EC_POINT_free(pubKey);
BN_CTX_free(ctx);
return (NULL);
}
