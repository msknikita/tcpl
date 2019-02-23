/* Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution speed. */

#include <io.h>
#include <stdarg.h>
#include <fcntl.h>

#define NULL     0
#define EOF      -1
#define BUFSIZ   1024
#define OPEN_MAX 20

struct flags {
	unsigned int fread : 1;
	unsigned int fwrite : 1;
	unsigned int is_unbuf : 1;
	unsigned int _feof : 1;
	unsigned int ferr : 1;
};

typedef struct iobuf {
	int cnt;
	char *ptr;
	char *base;
	struct flags flag;
	int fd;
} FILE;

FILE _iob[OPEN_MAX];


#define stdin  (&iob[0])
#define stdout (&iob[1])
#define stderr (&iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)   (((p)->flag & _EOF) !=0)
#define ferror(p) (((p)->flag & _ERR) !=0)
#define fileno(p) ((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = x : _flushbuf((x), p))

#define getchar()  getc(stdin)
#define putchar(x) putc((x), stdout)

#define MAXLINE 20

FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);

int main(int argc, char *argv[])
{
	FILE *fp;
	char line[MAXLINE], *prog = argv[0];
	char *buf = malloc(1024 * 1024);
	int c, i = 0;

	while (--argc > 0) {
		if ((fp = fopen(*++argv, "r")) == NULL)
			exit(1);
	}

	while ((c = getc(fp)) != EOF && i < 1024 * 1024 - 1)
		buf[i++] = (char)c;

	buf[i] = '\0';

	exit(0);
}

#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (fp->flag.fread == 0 && fp->flag.fwrite == 0)
			break;

	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else
		fd = open(name, O_RDONLY, 0);

	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;

	if (*mode == 'r') {
		fp->flag.fread = 1;
		fp->flag.fwrite = 0;
	}
	else {
		fp->flag.fread = 0;
		fp->flag.fwrite = 1;
	}

	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (fp->flag.fread == 0 || fp->flag._feof == 1 || fp->flag.ferr == 1)
		return EOF;

	bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;

	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag._feof = 1;
		else
			fp->flag.ferr = 1;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char)*fp->ptr++;
}
