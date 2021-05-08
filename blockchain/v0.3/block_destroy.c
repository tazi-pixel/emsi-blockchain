#include "blockchain.h"

/**
 * block_destroy - Destroys the Block structure
 * @block: pointer of the said block
 **/
void block_destroy(block_t *block)
{
	if (!block)
		return;
	llist_destroy(block->transactions, 1, (node_dtor_t)transaction_destroy);
	free(block);
}
