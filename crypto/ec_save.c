#include <stdlib.h>
#include <stdio.h>
#include "hblk_crypto.h"

/**
 * ec_save - save pub/private key pair into a file
 * @key: key pair
 * @folder: directory where to store the file
 * Return: 1 on success, 0 on failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
char path[BUFSIZ];
FILE *fp;
if (!EC_KEY_check_key(key) || !key || !folder ||
strlen(folder) + strlen(PUB_FILENAME) > BUFSIZ)
return (0);
mkdir(folder, S_IRWXU | S_IRGRP | S_IXGRP |
S_IROTH | S_IXOTH);
sprintf(path, "%s/%s", folder, PUB_FILENAME);
fp = fopen(path, "w");
if (!fp)
return (0);
if (!PEM_write_EC_PUBKEY(fp, key))
goto clean;
fclose(fp);
sprintf(path, "%s/%s", folder, PRI_FILENAME);
fp = fopen(path, "w");
if (!fp)
return (0);
if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
goto clean;
fclose(fp);
return (1);
clean:
fclose(fp);
return (0);
}
