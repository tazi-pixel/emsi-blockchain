#include "transaction.h"

/**
 * tx_in_create - allocates and initializes a transaction input structure
 * @unspent: address of unspent transaction output
 *           to be converted to a transaction input
 *
 * Return: pointer to created transaction input upon success, or NULL on fail
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *txIn = calloc(1, sizeof(tx_in_t));

	if (!txIn)
		return (NULL);
	memcpy(txIn->block_hash, unspent->block_hash,
	       sizeof(txIn->block_hash));
	memcpy(txIn->tx_id, unspent->tx_id, sizeof(txIn->tx_id));
	memcpy(txIn->tx_out_hash, unspent->out.hash, sizeof(txIn->tx_out_hash));
	return (txIn);
}
