/* Rewrite the program cat from Chapter 7 using read , write , open and close instead of their standard library equivalents. */

#include <stdio.h>
#include <io.h>
#include <stdarg.h>
#include <fcntl.h>

void error(char *fmt, ...);
void filecopy(int , int );

int main(int argc, char *argv[])
{
	int fd;

	if (argc == 1)
		filecopy(0, 1);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY)) == -1)
				error("cat: can't open %s", *argv);
			else {
				filecopy(fd, 1);
				close(fd);
			}
		
	return 0;
}
void filecopy(int ifd, int ofd)
{
	int n;
	char buf[BUFSIZ];

	while ((n = read(ifd, buf, BUFSIZ)) > 0)
		if (write(ofd, buf, n) != n)
			error("cat: write error");
}

void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);

	exit(1);
}