#pragma once

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { YES, NO };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getter(void);
int nexttoken(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char out[1000];
