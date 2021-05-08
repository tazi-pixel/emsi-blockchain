#include "transaction.h"

/**
 * tx_out_create - creates a new transaction output structure
 * @amount: the transaction amount
 * @pub: public key of receiver
 *
 * Return: pointer to the transaction outputon success, else NULL
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *txOut = calloc(1, sizeof(tx_out_t));

	if (!txOut)
		return (NULL);
	txOut->amount = amount;
	memcpy(txOut->pub, pub, sizeof(txOut->pub));
	if (!sha256((void *)txOut, sizeof(txOut->amount) + sizeof(txOut->pub),
		    txOut->hash))
	{
		free(txOut);
		return (NULL);
	}
	return (txOut);
}
