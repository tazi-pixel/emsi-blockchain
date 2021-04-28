#include "blockchain.h"

/**
 * blockchain_serialize - serializes blockchain to file
 * @blockchain: pointer to the blockchain to be serialized
 * @path: path to save file
 * Return: 0 on success else -1 on failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	int fd, i, size;
	uint8_t endianness = _get_endianness();

	if (!blockchain || !blockchain->chain || !path)
		return (-1);
	size = llist_size(blockchain->chain);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	if (write(fd, HBLK_MAGIC, strlen(HBLK_MAGIC)) != strlen(HBLK_MAGIC))
		goto fail;
	if (write(fd, HBLK_VERSION, strlen(HBLK_VERSION)) !=
	    strlen(HBLK_VERSION))
		goto fail;
	if (write(fd, &endianness, 1) != 1)
		goto fail;
	if (write(fd, &size, 4) != 4)
		goto fail;
	for (i = 0; i < size; i++)
	{
		block_t *block = llist_get_node_at(blockchain->chain, i);

		if (!block)
			goto fail;
		if (write(fd, &(block->info), sizeof(block->info)) !=
		    sizeof(block->info))
			goto fail;
		if (write(fd, &(block->data.len), 4) != 4)
			goto fail;
		if (write(fd, block->data.buffer, block->data.len) !=
		    block->data.len)
			goto fail;
		if (write(fd, block->hash, SHA256_DIGEST_LENGTH) !=
		    SHA256_DIGEST_LENGTH)
			goto fail;
	}
	return (close(fd), 0);
fail:
	close(fd);
	return (-1);
}
