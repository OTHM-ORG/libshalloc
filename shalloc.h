#ifndef SHALLOC_H
#define SHALLOC_H

#include <stdio.h>

typedef int Shaptr;

void *shaptrtoptr(Shaptr id);
Shaptr ptrtoshaptr(void *p);

void *shalloc(size_t size);
void shafree(void *p);

Shaptr shaflick(void *p);
void shapass(void *p);
void fshapass(void *p, FILE *stream);
void shapass_pt(void *p);
void fshapass_pt(void *p, FILE *stream);

void *shacatch(void);
void *shacatch_pt(void);
void *fshacatch(FILE *stream);
void *fshacatch_pt(FILE *stream);

void shasetexec(void *p);
void shaunsetexec(void *p);

#endif
