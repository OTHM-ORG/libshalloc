/* See LICENSE file for copyright and license details. */
#include <sys/shm.h>
#include <sys/stat.h>
#include "shalloc.h"

void *
shalloc(size_t size)
{
	int *mem;
	int id = shmget(IPC_PRIVATE, size + sizeof(id),
			IPC_CREAT | IPC_EXCL | 0666);

	if (id < 0)
		return NULL;
	*(mem = shmat(id, NULL, 0)) = id;
	return mem + 1;
}

void
shafree(void *restrict mem)
{
	mem = ((int *) mem) - 1;
	shmctl(*(int *) mem, IPC_RMID, NULL);
	shmdt(mem);
}

void
shapass(void *restrict mem)
{
	mem = ((int *) mem) - 1;
	fwrite(mem, sizeof(int), 1, stdout);
	shmdt(mem);
}

void
shapass_pt(void *restrict mem)
{
	mem = ((int *) mem) - 1;
	printf("%i\n", *(int *) mem);
	shmdt(mem);
}

void
fshapass_pt(void *restrict mem, FILE *stream)
{
	mem = ((int *) mem) - 1;
	fprintf(stream, "%i\n", *(int *) mem);
	shmdt(mem);
}

void *
shacatch(void)
{
	int id;

	fread(&id, sizeof(int), 1, stdin);
	if (id < 0)
		return NULL;
	return shmat(id, NULL, 0);
}

void *
shacatch_pt(void)
{
	int id;

	if (scanf("%i", &id) < 0 || id < 0)
		return NULL;
	return shmat(id, NULL, 0);
}

void *
fshacatch(FILE *stream)
{
	int id;

	fread(&id, sizeof(int), 1, stream);
	if (id < 0)
		return NULL;
	return shmat(id, NULL, 0);
}

void *
fshacatch_pt(FILE *stream)
{
	int id;

	if (fscanf(stream, "%i", &id) < 0 || id < 0)
		return NULL;
	return shmat(id, NULL, 0);
}
