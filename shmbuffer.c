

#include <sys/stat.h>
#include <fcntl.h>

#include "shmbuffer.h"


/* Link with -lrt */


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
	*buff->buff_ipos = *buff->buff_begin;

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
	// TODO: implementation
	return -1;
}


int shm_ringbuff_write(struct shmringbuff`*buff, char *writebuff, size_t writebuff_size)
{
	// TODO: implementation
	return -1;
}
