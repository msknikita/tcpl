/* The standard library function calloc(n,size) returns a pointer to n objects of size size , with the storage initialized to zero. Write calloc,
 * by calling malloc or by modifying it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NALLOC 1024

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

void *m_malloc(unsigned);
void m_free(void *);
void *m_calloc(unsigned, unsigned);
static Header *morecore(unsigned);

int main(void)
{
	int *arr, n = 3, i;

	arr = (int *)m_calloc(n, sizeof(int));

	if (arr == 0) {
		printf("error: Out of memory\n");
		exit(1);
	}

	*arr = 25;
	for (i = 0; i < n; ++i)
		printf("%d\n", *arr++);

	m_free(arr);

	return 0;
}

void *m_malloc(unsigned nbytes)
{
	Header *currp, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

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
	up->s.size = nu;
	m_free((void *)(up + 1));

	return freep;
}

void m_free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;
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
