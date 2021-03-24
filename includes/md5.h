#ifndef MD5_H
# define MD5_H

typedef struct s_hash
{
	uint32_t	w[4];
	uint32_t	k[64];
	uint32_t	r[64];
	uint32_t	tmp;
	uint8_t		*mes;
}				t_hash;

uint32_t	leftrotate(uint32_t x, uint32_t c);
char		*format_res(t_hash hash);
void		init_md5(t_hash *hash);
char		*md5(uint8_t *input, size_t input_len);

#endif
