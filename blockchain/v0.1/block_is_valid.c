Skip to content
Search or jump to…

Pull requests
Issues
Marketplace
Explore
 
@tazi-pixel 
salimregragui
/
emsi-blockchain
1
01
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
emsi-blockchain/blockchain/v0.1/block_is_valid.c
@salimregragui
salimregragui blockchain
Latest commit d4d96d3 7 days ago
 History
 1 contributor
34 lines (32 sloc)  1.03 KB
  
#include "blockchain.h"

/**
 * block_is_valid - verify that a block is valid
 *
 * @block: pointer to the block to be verified
 * @prev_block: pointer to the previous block (or NULL if @block is the first)
 *
 * Return: If the block is invalid, return 1.
 * Otherwise, return 0.
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	block_t const genesis = BLOCK_GENESIS_INIT;

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
		return (memcmp(block, &genesis, sizeof(genesis)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCK_DATA_MAX_LEN)
		return (1);
	return (0);
}
© 2021 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete
