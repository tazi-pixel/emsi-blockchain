#include "blockchain.h"

/**
 * blockchain_destroy - Destroys the Blockchain structure
 * @blockchain: pointer of the said block
 **/
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;
	llist_destroy(blockchain->unspent, 1, free);
	llist_destroy(blockchain->chain, 1,
		      (void (*)(llist_node_t))block_destroy);
	free(blockchain);
}
