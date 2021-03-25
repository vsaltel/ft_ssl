#include "sha256.h"
#include "ssl.h"

static void	handle_chunk(t_buffer_state *state, uint8_t *chunk,
	size_t space_in_chunk)
{
	size_t			left;
	size_t			len;
	int				i;

	if (space_in_chunk >= TOTAL_LEN_LEN)
	{
		left = space_in_chunk - TOTAL_LEN_LEN;
		len = state->total_len;
		ft_memset(chunk, 0x00, left);
		chunk += left;
		chunk[7] = (uint8_t)(len << 3);
		len >>= 5;
		i = 7;
		while (--i >= 0)
		{
			chunk[i] = (uint8_t)len;
			len >>= 8;
		}
		state->total_len_delivered = 1;
	}
	else
		ft_memset(state->chunk, 0x00, space_in_chunk);
}

static int	calc_chunk(t_buffer_state *state, uint8_t *chunk)
{
	size_t			space_in_chunk;

	if (state->total_len_delivered)
		return (0);
	if (state->len >= CHUNK_SIZE)
	{
		ft_memcpy(chunk, state->p, CHUNK_SIZE);
		state->p += CHUNK_SIZE;
		state->len -= CHUNK_SIZE;
		return (1);
	}
	ft_memcpy(chunk, state->p, state->len);
	chunk += state->len;
	space_in_chunk = CHUNK_SIZE - state->len;
	state->p += state->len;
	state->len = 0;
	if (!state->single_one_delivered)
	{
		*chunk++ = 0x80;
		space_in_chunk -= 1;
		state->single_one_delivered = 1;
	}
	handle_chunk(state, chunk, space_in_chunk);
	return (1);
}

void	sha256_handle_ah(t_buffer_state *s, int i, int j)
{
	s->s1 = right_rot(s->ah[4], 6) ^ right_rot(s->ah[4], 11)
		^ right_rot(s->ah[4], 25);
	s->ch = (s->ah[4] & s->ah[5]) ^ (~s->ah[4] & s->ah[6]);
	s->temp1 = s->ah[7] + s->s1 + s->ch + s->k[i << 4 | j] + s->w[j];
	s->s0 = right_rot(s->ah[0], 2) ^ right_rot(s->ah[0], 13)
		^ right_rot(s->ah[0], 22);
	s->maj = (s->ah[0] & s->ah[1]) ^ (s->ah[0] & s->ah[2])
		^ (s->ah[1] & s->ah[2]);
	s->temp2 = s->s0 + s->maj;
	s->ah[7] = s->ah[6];
	s->ah[6] = s->ah[5];
	s->ah[5] = s->ah[4];
	s->ah[4] = s->ah[3] + s->temp1;
	s->ah[3] = s->ah[2];
	s->ah[2] = s->ah[1];
	s->ah[1] = s->ah[0];
	s->ah[0] = s->temp1 + s->temp2;
}

void	sha256_handle_w(t_buffer_state *s, int i, int j)
{
	if (i == 0)
	{
		s->w[j] = (uint32_t)s->p[0] << 24 | (uint32_t)s->p[1] << 16
			| (uint32_t)s->p[2] << 8 | (uint32_t)s->p[3];
		s->p += 4;
	}
	else
	{
		s->s0 = right_rot(s->w[(j + 1) & 0xf], 7)
			^ right_rot(s->w[(j + 1)
				& 0xf], 18) ^ (s->w[(j + 1) & 0xf] >> 3);
		s->s1 = right_rot(s->w[(j + 14) & 0xf], 17)
			^ right_rot(s->w[(j + 14)
				& 0xf], 19) ^ (s->w[(j + 14) & 0xf] >> 10);
		s->w[j] = s->w[j] + s->s0 + s->w[(j + 9) & 0xf] + s->s1;
	}
	sha256_handle_ah(s, i, j);
}

char	*sha256(void *input, size_t len)
{
	int				i;
	int				j;
	t_buffer_state	s;

	init_buf_state(&s, input, len);
	while (calc_chunk(&s, s.chunk))
	{
		s.p = s.chunk;
		i = -1;
		while (++i < 8)
			s.ah[i] = s.h[i];
		i = -1;
		while (++i < 4)
		{
			j = -1;
			while (++j < 16)
				sha256_handle_w(&s, i, j);
		}
		i = -1;
		while (++i < 8)
			s.h[i] += s.ah[i];
	}
	return (sha256_final_hash(&s));
}
