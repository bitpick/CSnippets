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

#include <sys/stat.h>
#include <fcntl.h>

#include "shmbuffer.h"


int shm_ringbuff_get_content_size(struct shmringbuff *buff)
{
	int content = 0;

	// no data in buffer
	if(buff->buff_rpos == buff->buff_wpos)
		return content;

	// write pointer flipped
	if(buff->buff_wpos < buff->buff_rpos)
	{
		content = buff->buff_end - buff->buff_rpos;
		content += buff->buff_wpos - buff->buff_begin;
	}
	else
	{
		content = buff->buff_wpos - buff->buff_rpos;
	}

	return content;
}


int shm_ringbuff_get_data_address(struct shmringbuff *buff)
{
	if(shmringbuff == NULL)
		return -1;

	return shmringbuff + sizeof(struct shmringbuff);
}


int shm_ringbuff_init(struct shmringbuff **buff, size_t size, char *mapfile, int prot, int flags)
{
	int fd = 0;

	fd = shm_open(mapfile, O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(fd, sizeof(struct shmringbuff) + SHM_SIZE);

	*buff = mmap(NULL, sizeof(struct shmringbuff) + SHM_SIZE, 
		PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	close(fd);

	if(*buff == MAP_FAILED)
		return -1;

	*buff->seqnum = 0;
	*buff->buffsize = SHM_SIZE;
	*buff->size = sizeof(struct shmringbuff) + SHM_SIZE;
	*buff->buff_begin = *buff + sizeof(struct shmringbuff);
	*buff->buff_end = *buff->buff_begin + SHM_SIZE;
	*buff->buff_rpos = *buff->buff_begin;
	*buff->buff_wpos = *buff->buff_begin;

	sem_init(*buff->sem, 1, 1);

	return 0;
}


int shm_ringbuff_destroy(struct shmringbuff **buff)
{
	if(*buff != NULL)
	{
		sem_wait(*buff->sem);
		sem_destroy(*buff->sem);
		return munmap(*buff, sizeof(struct shmringbuff) + SHM_SIZE);
	}
	return -1;
}


int shm_ringbuff_connect_ro(char *mapfile, struct shmringbuff **buff)
{
	int fd;
	struct stat st;

	fd = shm_open(mapfile, O_RDONLY, 0);
	fstat(fd, &st);
	*buff = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);

	return 0;
}


int shm_ringbuff_connect_rw(char *mapfile, struct shmringbuff **buff)
{
	int fd;
	struct stat st;

	fd = shm_open(mapfile, O_RDWR, 0);
	fstat(fd, &st);
	*buff = mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	return 0;
}


int shm_ringbuff_read(struct shmringbuff *buff, char *readbuff, size_t readbuff_size)
{
	return ringbuffer_read(readbuff, buff->buffer, readbuff_size);
}


int shm_ringbuff_write(struct shmringbuff`*buff, char *writebuff, size_t writebuff_size)
{
	return ringbuffer_write(buff->buffer, writebuff, writebuff_size);	
}
