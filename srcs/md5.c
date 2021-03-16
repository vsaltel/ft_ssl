#include "ssl.h"
#include "md5.h"

static void	md5_hash_word(t_hash *curr, uint32_t i, uint32_t *f, uint32_t *g)
{
	if (i < 16)
	{
		*f = (curr->w[1] & curr->w[2]) | ((~curr->w[1]) & curr->w[3]);
		*g = i;
	}
	else if (i < 32)
	{
		*f = (curr->w[3] & curr->w[1]) | ((~curr->w[3]) & curr->w[2]);
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = curr->w[1] ^ curr->w[2] ^ curr->w[3];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = curr->w[2] ^ (curr->w[1] | (~curr->w[3]));
		*g = (7 * i) % 16;
	}
}

static void	md5_exec(t_hash *hash, uint8_t *msg, int offset)
{
	t_hash		curr;
	uint32_t	*w;
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;

	w = (uint32_t *)(msg + offset);
	curr = *hash;
	i = -1;
	while (++i < 64)
	{
		md5_hash_word(&curr, i, &f, &g);
		curr.tmp = curr.w[3];
		curr.w[3] = curr.w[2];
		curr.w[2] = curr.w[1];
		curr.w[1] = curr.w[1] + leftrotate((curr.w[0] + f + hash->k[i] + w[g]),
				hash->r[i]);
		curr.w[0] = curr.tmp;
	}
	hash->w[0] += curr.w[0];
	hash->w[1] += curr.w[1];
	hash->w[2] += curr.w[2];
	hash->w[3] += curr.w[3];
}

char	*md5(uint8_t *input, size_t input_len)
{
	t_hash		hash;
	uint8_t		*msg;
	int			new_len;
	int			offset;
	uint32_t	bits_len;

	msg = NULL;
	init_md5(&hash);
	new_len = ((((input_len + 8) / 64) + 1) * 64) - 8;
	msg = malloc(new_len + 64);
	ft_bzero(msg, new_len + 64);
	ft_memcpy(msg, input, input_len);
	msg[input_len] = 128;
	bits_len = 8 * input_len;
	ft_memcpy(msg + new_len, &bits_len, 4);
	offset = 0;
	while (offset < new_len)
	{
		md5_exec(&hash, msg, offset);
		offset += (512 / 8);
	}
	free(msg);
	return (format_res(hash));
}
