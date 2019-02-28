/* malloc accepts a size request without checking its plausiblity; free believes that the block it is asked to free contain a valid size field.
 * Improve these rountines so they take more pains with error checking.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NALLOC 1024
#define MAXBYTES (unsigned) 10240

typedef long Align;

union header {
	struct {
		union header *next;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;
static unsigned maxallocsize;

void *m_malloc(unsigned);
void m_free(void *);
void *m_calloc(unsigned, unsigned);
static Header * morecore(unsigned);

int main(void)
{
	int *ptr;

	ptr = (int *)m_malloc(sizeof(int));

	if (ptr == 0) {
		printf("error: Out of memory\n");
		exit(1);
	}

	*ptr = 25;
	printf("%d\n", *ptr);

	m_free(ptr);

	return 0;
}

void *m_malloc(unsigned nbytes)
{
	Header *currp, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	if (nbytes > MAXBYTES) {
		fprintf(stderr, "alloc: can't at locate more than %u bytes\n", MAXBYTES);
		return NULL;
	}

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

	if ((prevp = freep) == NULL) {
		base.s.next = freep = prevp = &base;
		base.s.size = 0;
	}

	for (currp = prevp->s.next; ; prevp = currp, currp = currp->s.next) {
		if (currp->s.size >= nunits) {
			if (currp->s.size == nunits)
				prevp->s.next = currp->s.next;
			else {
				currp->s.size -= nunits;
				currp += currp->s.size;
				currp->s.size = nunits;
			}
			freep = prevp;
			return (void *)(currp + 1);
		}
		if (currp == freep)
			if ((currp = morecore(nunits)) == NULL)
				return NULL;
	}
}

static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;

	cp = sbrk(nu * sizeof(Header));

	if (cp == (char *)-1)
		return NULL;

	up = (Header *)cp;
	maxallocsize = ((up->s.size = nu) > maxallocsize) ? up->s.size : maxallocsize;
	m_free((void *)(up + 1));

	return freep;
}

void m_free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;

	if (bp->s.size <= 0 || bp->s.size > maxallocsize) {
		fprintf(stderr, "free: can't free %u units\n", bp->s.size);
		return;
	}

	for (p = freep; !(bp > p && bp < p->s.next); p = p->s.next)
		if (p >= p->s.next && (bp > p || bp < p->s.next))
			break;

	if (bp + bp->s.size == p->s.next) {
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	}
	else
		bp->s.next = p->s.next;

	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	}
	else
		p->s.next = bp;

	freep = p;
}

void *m_calloc(unsigned n, unsigned size)
{
	unsigned i, nbytes;
	char *p, *q;

	nbytes = n * size;
	if ((p = q = m_malloc(nbytes)) != NULL)
		for (i = 0; i < nbytes; ++i)
			*p++ = 0;

	return q;
}
