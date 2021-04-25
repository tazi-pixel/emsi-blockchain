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
emsi-blockchain/blockchain/v0.1/blockchain_serialize.c
@salimregragui
salimregragui blockchain
Latest commit d4d96d3 7 days ago
 History
 1 contributor
57 lines (53 sloc)  1.58 KB
  
#include "blockchain.h"

/**
 * blockchain_serialize - serialize a blockchain to a file
 *
 * @blockchain: pointer to the blockchain to be serialized
 * @path: path to a file in which to write the serialized blockchain
 *
 * Description: If @path points to an existing file, it will be overwritten.
 *
 * Return: If an error occurs, return -1.
 * Otherwise, return 0.
 */

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	int fd = -1;
	int index = 0;
	int32_t size = 0;
	uint8_t endianness = _get_endianness();
	block_t *block = NULL;

	if (!blockchain || !blockchain->chain || !path)
		return (-1);
	size = llist_size(blockchain->chain);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	if (write(fd, HBLK_MAGIC, HBLK_MAGIC_LEN) != HBLK_MAGIC_LEN)
		return (close(fd), -1);
	if (write(fd, HBLK_VERSION, HBLK_VERSION_LEN) != HBLK_VERSION_LEN)
		return (close(fd), -1);
	if (write(fd, &endianness, 1) != 1)
		return (close(fd), -1);
	if (write(fd, &size, 4) != 4)
		return (close(fd), -1);

	while (index < size)
	{
		block = llist_get_node_at(blockchain->chain, index++);
		if (!block)
			return (close(fd), -1);
		if (write(fd, &(block->info), sizeof(block->info)) !=
				sizeof(block->info))
			return (close(fd), -1);
		if (write(fd, &(block->data.len), 4) !=
				4)
			return (close(fd), -1);
		if (write(fd, block->data.buffer, block->data.len) !=
				block->data.len)
			return (close(fd), -1);
		if (write(fd, block->hash, SHA256_DIGEST_LENGTH) !=
				SHA256_DIGEST_LENGTH)
			return (close(fd), -1);
	}
	return (close(fd), 0);
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
