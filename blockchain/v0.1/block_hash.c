#include "blockchain.h"

/**
 * block_hash - Computes the hash of a Block
 * @block: pointer to block to hash
 * @hash_buf: buffer to store hash
 *
 * Return: pointer to @hash_buf
 */
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len = sizeof(block->info) + block->data.len;

	sha256((void *)&(block->info), len, hash_buf);
	return (hash_buf);
}
