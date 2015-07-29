#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    if(argc != 2)
        return 1;

    struct stat fstat;
    if(stat(argv[1],&fstat) < 0)
        return 1;

    printf("Information for %s\n",argv[1]);
    printf("---------------------------\n");
    printf("File Size: \t\t%ld bytes\n",fstat.st_size);
    printf("Number of Links: \t%lu\n",fstat.st_nlink);
    printf("File inode: \t\t%lu\n",fstat.st_ino);

    printf("Human Readable File Permissions: \t");
    printf( (S_ISDIR(fstat.st_mode)) ? "d" : "-");
    printf( (fstat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fstat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fstat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fstat.st_mode & S_ISUID) ? "s" : "");
    printf( (fstat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fstat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fstat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fstat.st_mode & S_ISGID) ? "s" : "");
    printf( (fstat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fstat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fstat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("The file %s a symbolic link\n", (S_ISLNK(fstat.st_mode)) ? "is" : "is not");

    return 0;
}
