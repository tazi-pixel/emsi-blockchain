#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hblk_crypto.h"

EC_KEY *ec_create()
{
EC_KEY *key = EC_KEY_new();
EC_GROUP *group;
if (key == NULL)
return (NULL);
group = EC_GROUP_new_by_curve_name(EC_CURVE);
if (group == NULL)
return (NULL);
EC_KEY_set_group(key, group);
EC_KEY_generate_key(key);
EC_GROUP_free(group);
return (key);
}
