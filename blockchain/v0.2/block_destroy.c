#include "blockchain.h"

/**
 * block_destroy - Destroys the Block structure
 * @block: pointer of the said block
 **/
void block_destroy(block_t *block)
{
	free(block);
}
