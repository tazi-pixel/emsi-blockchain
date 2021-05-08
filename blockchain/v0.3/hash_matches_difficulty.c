#include "blockchain.h"

/**
 * get_difficulty - computers number of leading bits in hash
 * @hash: hash buffer
 * Return: computed difficulty
 */
uint32_t get_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH])
{
	uint8_t *ptr = (uint8_t *)hash;
	uint32_t difficulty = 0;
	int i;

	for (; ptr < hash + SHA256_DIGEST_LENGTH; ptr++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*ptr >> i) & 1)
				return (difficulty);
			difficulty++;
		}
	}
	return (difficulty);
}

/**
 * hash_matches_difficulty -  checks whether a given hash matches
 * a given difficulty
 * @hash: the hash to check
 * @difficulty: the minimum difficulty the hash should match
 *
 * Return: 1 if the difficulty is respected, or 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			uint32_t difficulty)
{
	if (!hash)
		return (0);
	return (get_difficulty(hash) >= difficulty);
}
