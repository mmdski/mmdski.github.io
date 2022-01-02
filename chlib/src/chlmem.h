extern void *chl_alloc (long nbytes);

extern void *chl_calloc (long count, long nbytes);

extern void chl_free (void *ptr);

#define ALLOC(nbytes) chl_alloc ((nbytes))
#define NEW(p) ((p) = ALLOC ((long) sizeof *(p)))
#define FREE(ptr) ((void) (chl_free ((ptr)), (ptr) = 0))
