/**
 * Copyright (C) 2014 bitpick
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 **/


/* Link with -lrt */


#ifndef SHMBUFFER_H_
#define SHMBUFFER_H_

#include <sys/type.h>
#include <sys/mman.h>
#include <semaphore.h>
#include "ringbuffer.h"

#ifndef SHM_SIZE
#define SHM_SIZE 4194304    // 4MByte, default value
                            // compile time set via -DSHM_SIZE=
#endif


struct shmringbuff {
    sem_t sem;
    int error;
    ringbuffer *buffer;
};


int shm_ringbuff_init(struct shmringbuff **buff, size_t size, char *mapfile, int prot, int flags);
int shm_ringbuff_destroy(struct shmringbuff **buff);
int shm_ringbuff_connect_ro(char *mapfile, struct shmringbuff **buff);
int shm_ringbuff_connect_rw(char *mapfile, struct shmringbuff **buff);
int shm_ringbuff_read(struct shmringbuff *buff, char *readbuff, size_t readbuff_size);
int shm_ringbuff_write(struct shmringbuff`*buff, char *writebuff, size_t writebuff_size);

#endif  // SHMBUFFER_H_
