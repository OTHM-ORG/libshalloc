/* See LICENSE file for copyright and license details. */
#include <sys/shm.h>
#include <sys/mman.h>
#include "shalloc.h"

void *
shaptrtoptr(Shaptr id)
{
	return (Shaptr *) shmat(id, NULL, 0) + 1;
}

Shaptr
ptrtoshaptr(void *p)
{
	return *((Shaptr *) p - 1);
}

void *
shalloc(size_t size)
{
	Shaptr *p;
	Shaptr id = shmget(IPC_PRIVATE, size + sizeof(id),
			   IPC_CREAT | IPC_EXCL | 0666);

	if (id < 0)
		return NULL;
	*(p = shmat(id, NULL, 0)) = id;
	return p + 1;
}

void
shafree(void *p)
{
	Shaptr *s = p;

	shmctl(*--s, IPC_RMID, NULL);
	shmdt(s);
}

Shaptr
shaflick(void *p)
{
	Shaptr *s = p;
	Shaptr id = *--s;

	shmdt(s);
	return id;
}

void
shapass(void *p)
{
	Shaptr id = shaflick(p);

	fwrite(&id, sizeof(Shaptr), 1, stdout);
}

void
fshapass(void *p, FILE *stream)
{
	Shaptr id = shaflick(p);

	fwrite(&id, sizeof(Shaptr), 1, stream);
}

void
shapass_pt(void *p)
{
	printf("%i\n", shaflick(p));
}

void
fshapass_pt(void *p, FILE *stream)
{
	fprintf(stream, "%i\n", shaflick(p));
}

void *
shacatch(void)
{
	Shaptr id;

	fread(&id, sizeof(id), 1, stdin);
	if (id < 0)
		return NULL;
	return shaptrtoptr(id);
}

void *
shacatch_pt(void)
{
	Shaptr id;

	if (scanf("%i", &id) < 0 || id < 0)
		return NULL;
	return shaptrtoptr(id);
}

void *
fshacatch(FILE *stream)
{
	Shaptr id;

	fread(&id, sizeof(id), 1, stream);
	if (id < 0)
		return NULL;
	return shaptrtoptr(id);
}

void *
fshacatch_pt(FILE *stream)
{
	Shaptr id;

	if (fscanf(stream, "%i", &id) < 0 || id < 0)
		return NULL;
	return shaptrtoptr(id);
}

void
shasetexec(void *p)
{
	struct shmid_ds shmbuff;
	Shaptr *s = p;

	shmctl(*--s, IPC_STAT, &shmbuff);
	mprotect(s, shmbuff.shm_segsz, PROT_EXEC | PROT_READ);
	/* shmbuff.shm_perm.mode = 0777; */
	/* shmctl(id, IPC_SET, &shmbuff); */
}

void
shaunsetexec(void *p)
{
	struct shmid_ds shmbuff;
	Shaptr *s = p;

	shmctl(*--s, IPC_STAT, &shmbuff);
	mprotect(s, shmbuff.shm_segsz, PROT_WRITE | PROT_READ);
}
