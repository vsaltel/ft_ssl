#ifndef SHA256_H
# define SHA256_H

# define CHUNK_SIZE 64
# define TOTAL_LEN_LEN 8
# define HASH_BYTE_SIZE 32

# include "libft.h"
# include <stdio.h>

typedef struct s_buffer_state {
	uint32_t		k[64];
	uint32_t		h[8];
	uint8_t			chunk[64];
	size_t			len;
	size_t			total_len;
	unsigned int	single_one_delivered;
	unsigned int	total_len_delivered;

	uint32_t		ah[8];
	uint8_t			*p;
	uint8_t			*c;
	uint32_t		w[16];
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		ch;
	uint32_t		maj;
	uint32_t		temp1;
	uint32_t		temp2;
}				t_buffer_state;

char			*sha256(void *input, size_t len);
char			*sha256_final_hash(t_buffer_state *state);
void			init_buf_state(t_buffer_state *state, void *input, size_t len);
uint32_t		right_rot(uint32_t value, unsigned int count);
#endif
