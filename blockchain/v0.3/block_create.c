#include "blockchain.h"

/**
 * block_create - Creates a Block structure, and initializes it
 * @prev: previous block in the blockchain
 * @data: data to store in current block
 * @data_len: length of @data
 *
 * Return: pointer to the block structure
 **/
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len)
{
	block_t *block = calloc(1, sizeof(*block));
	llist_t *transactions = llist_create(MT_SUPPORT_FALSE);

	if (!block || !transactions)
	{
		free(block);
		llist_destroy(transactions, 0, NULL);
		perror("memory allocation failed");
		return (NULL);
	}
	block->info.timestamp = time(NULL);
	memcpy(&(block->data.buffer), data, BLOCKCHAIN_DATA_MAX);
	block->data.len = data_len > BLOCKCHAIN_DATA_MAX ? BLOCKCHAIN_DATA_MAX
		: data_len;
	block->info.index = prev->info.index + 1;
	block->transactions = transactions;
	memcpy(&(block->info.prev_hash), prev->hash, SHA256_DIGEST_LENGTH);
	return (block);
}
