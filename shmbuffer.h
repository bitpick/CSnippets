
#ifndef SHMBUFFER_H_
#define SHMBUFFER_H_

#include <sys/type.h>
#include <sys/mman.h>
#include <semaphore.h>

#ifndef SHM_SIZE
#define SHM_SIZE 4194304    // 4MByte, default value
                            // compile time set via -DSHM_SIZE=
#endif


struct shmringbuff {
    sem_t sem;
    int error;
    size_t size;
    size_t buffer_size;
    size_t buff_begin;
    size_t buff_end;
    size_t buff_ipos;
};


int shm_ringbuff_init(struct shmringbuff **buff, size_t size, char *mapfile, int prot, int flags);
int shm_ringbuff_destroy(struct shmringbuff **buff);
int shm_ringbuff_connect_ro(char *mapfile, struct shmringbuff **buff);
int shm_ringbuff_connect_rw(char *mapfile, struct shmringbuff **buff);
int shm_ringbuff_read(struct shmringbuff *buff, char *readbuff, size_t readbuff_size);
int shm_ringbuff_write(struct shmringbuff`*buff, char *writebuff, size_t writebuff_size);

#endif  // SHMBUFFER_H_
