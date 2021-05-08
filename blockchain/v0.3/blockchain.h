#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "../../crypto/hblk_crypto.h"
#include "provided/endianness.h"

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<llist.h>
#include<time.h>
#include<openssl/sha.h>

#include "transaction/transaction.h"


/**
 * Constants definition
 **/
#define BLOCKCHAIN_DATA_MAX 1024
#define GENESIS_DATA        "Holberton School"
#define GENESIS_DATA_LEN    16
#define GENESIS_HASH         "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03"
#define GENESIS_TIMESTAMP   1537578000
#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.3"
#define BLOCK_GENERATION_INTERVAL 1
#define DIFFICULTY_ADJUSTMENT_INTERVAL 5
#define COINBASE_AMOUNT    50

/**
 * struct block_data_s - Block data
 *
 * @buffer: Data buffer
 * @len:    Data size (in bytes)
 */
typedef struct block_data_s
{
	/*
	 * @buffer must stay first, so we can directly use the structure as
	 * an array of char
	 */
	int8_t      buffer[BLOCKCHAIN_DATA_MAX];
	uint32_t    len;
} block_data_t;


/**
 * struct block_info_s - Block info structure
 *
 * @index:      Index of the Block in the Blockchain
 * @difficulty: Difficulty of proof of work (hash leading zero bits)
 * @timestamp:  Time the Block was created at (UNIX timestamp)
 * @nonce:      Salt value used to alter the Block hash
 * @prev_hash:  Hash of the previous Block in the Blockchain
 */
typedef struct block_info_s
{
	/*
	 * The order of the elements in this structure should remain the same.
	 * It was designed so every element of this structure is aligned and
	 * doesn't require padding from the compiler.
	 * Therefore, it is possible to use the structure as an array of char,
	 * on any architecture.
	 */
	uint32_t    index;
	uint32_t    difficulty;
	uint64_t    timestamp;
	uint64_t    nonce;
	uint8_t     prev_hash[SHA256_DIGEST_LENGTH];
} block_info_t;

/**
 * struct tx_out_s - Transaction output
 *
 * @amount: Amount received
 * @pub:    Receiver's public address
 * @hash:   Hash of @amount and @pub. Serves as output ID
 */
typedef struct tx_out_s
{
	uint32_t    amount;
	uint8_t     pub[EC_PUB_LEN];
	uint8_t     hash[SHA256_DIGEST_LENGTH];
} tx_out_t;

/**
 * struct tx_in_s - Transaction input
 *
 * Description: A transaction input always refers to a previous
 * transaction output. The only exception is for a Coinbase transaction, that
 * adds new coins to ciruclation.
 *
 * @block_hash:  Hash of the Block containing the transaction @tx_id
 * @tx_id:       ID of the transaction containing @tx_out_hash
 * @tx_out_hash: Hash of the referenced transaction output
 * @sig:         Signature. Prevents anyone from altering the content of the
 *               transaction. The transaction input is signed by the receiver
 *               of the referenced transaction output, using their private key
 */
typedef struct tx_in_s
{
	uint8_t     block_hash[SHA256_DIGEST_LENGTH];
	uint8_t     tx_id[SHA256_DIGEST_LENGTH];
	uint8_t     tx_out_hash[SHA256_DIGEST_LENGTH];
	sig_t       sig;
} tx_in_t;

/**
 * struct transaction_s - Transaction structure
 *
 * @id:      Transaction ID. A hash of all the inputs and outputs.
 *           Prevents further alteration of the transaction.
 * @inputs:  List of `tx_in_t *`. Transaction inputs
 * @outputs: List of `tx_out_t *`. Transaction outputs
 */
typedef struct transaction_s
{
	uint8_t id[SHA256_DIGEST_LENGTH];
	llist_t *inputs;
	llist_t *outputs;
} transaction_t;

/**
 * struct Visitor - visitor struct for collect sender's unspent
 * @sender_unspent: list to collect sender's unspent tx
 * @sender_pub: sender's public key
 * @total_amount: of unspent tx
 * @amount: amount to send
 */
typedef struct Visitor
{
	llist_t *sender_unspent;
	uint8_t *sender_pub;
	uint64_t total_amount;
	uint64_t amount;
} visitor_t;

/**
 * struct Validation_Visitor - visitor struct for tx validation
 * @in_amount: total txi amount
 * @out_amount: total txo amount
 * @valid: 1 if tx valid else 0
 * @all_unspent: all unspent txs
 * @tx: the tx to validate
 * @block_index: the block index cointaining tx
 */
typedef struct Validation_Visitor
{
	long in_amount;
	long out_amount;
	int valid;
	llist_t *all_unspent;
	transaction_t const *tx;
	uint32_t block_index;
} validation_vistor_t;


/**
 * struct block_s - Block structure
 *
 * @info: Block info
 * @data: Block data
 * @transactions: List of transactions
 * @hash: 256-bit digest of the Block, to ensure authenticity
 */
typedef struct block_s
{
	block_info_t    info; /* This must stay first */
	block_data_t    data; /* This must stay second */
	llist_t         *transactions;
	uint8_t         hash[SHA256_DIGEST_LENGTH];
} block_t;


/**
 * struct unspent_tx_out_s - Unspent transaction output
 *
 * Description: This structure helps identify transaction outputs that were not
 * used in any transaction input yet, making them "available".
 *
 * @block_hash: Hash of the Block containing the transaction @tx_id
 * @tx_id:      ID of the transaction containing @out
 * @out:        Copy of the referenced transaction output
 */
typedef struct unspent_tx_out_s
{
	uint8_t     block_hash[SHA256_DIGEST_LENGTH];
	uint8_t     tx_id[SHA256_DIGEST_LENGTH];
	tx_out_t    out;
} unspent_tx_out_t;


/**
 * struct blockchain_s - Blockchain structure
 *
 * @chain:   Linked list of Blocks
 * @unspent: Linked list of unspent transaction outputs
 */
typedef struct blockchain_s
{
	llist_t     *chain;
	llist_t     *unspent;
} blockchain_t;


blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev, int8_t const *data,
		      uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block,
		    uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
blockchain_t *blockchain_deserialize(char const *path);
int block_is_valid(block_t const *block, block_t const *prev_block,
		   llist_t *all_unspent);
llist_t *deserialize_blocks(int fd, uint32_t size, uint8_t endianness);

int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
			    uint32_t difficulty);
void block_mine(block_t *block);
uint32_t blockchain_difficulty(blockchain_t const *blockchain);

tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN]);
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out);
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent);
uint8_t *transaction_hash(transaction_t const *transaction,
			  uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
sig_t *tx_in_sign(tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
		  EC_KEY const *sender, llist_t *all_unspent);
transaction_t *transaction_create(EC_KEY const *sender, EC_KEY const *receiver,
				  uint32_t amount, llist_t *all_unspent);
int transaction_is_valid(transaction_t const *transaction,
			 llist_t *all_unspent);
transaction_t *coinbase_create(EC_KEY const *receiver, uint32_t block_index);
int coinbase_is_valid(transaction_t const *coinbase, uint32_t block_index);
void transaction_destroy(transaction_t *transaction);
llist_t *update_unspent(llist_t *transactions,
			uint8_t block_hash[SHA256_DIGEST_LENGTH],
			llist_t *all_unspent);

#define GENESIS_BLOCK {				\
		{ /* info */			\
			0 /* index */,		\
				0, /* difficulty */	\
				1537578000, /* timestamp */	\
				0, /* nonce */			\
				{0} /* prev_hash */		\
		},						\
		{ /* data */					\
			"Holberton School", /* buffer */	\
				16 /* len */				\
				},					\
			NULL, /* transactions */			\
				"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03" \
				}

#include "transaction/transaction.h"
#endif
