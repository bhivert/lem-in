
#include "stream_priv.h"
#include "bitset.h"

void	ft_stream_clear(t_stream *stream)
{
	bitset_reset(&stream->state_bitset);
	bitset_set(&stream->state_bitset, SI_GOOD);
}

int		ft_stream_good(t_stream *stream)
{
	return (bitset_test(stream->state_bitset, SI_GOOD));
}

int		ft_stream_bad(t_stream *stream)
{
	return (bitset_test(stream->state_bitset, SI_BAD));
}

int		ft_stream_fail(t_stream *stream)
{
	return (bitset_test(stream->state_bitset, SI_FAIL));
}

int		ft_stream_eof(t_stream *stream)
{
	return (bitset_test(stream->state_bitset, SI_EOF));
}
