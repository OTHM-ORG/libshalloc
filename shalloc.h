#ifndef SHALLOC_H
#define SHALLOC_H

#include <stdio.h>

void *shalloc(size_t size);
void shafree(void *restrict mem);

void shapass(void *restrict mem);
void shapass_pt(void *restrict mem);
void fshapass_pt(void *restrict mem, FILE *stream);
void *shacatch(void);
void *shacatch_pt(void);
void *fshacatch(FILE *stream);
void *fshacatch_pt(FILE *stream);

#endif
