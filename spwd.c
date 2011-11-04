/*=============================================================================
#     FileName: spwd.c
#         Desc: 
#       Author: quake0day
#        Email: quake0day@gmail.com
#     HomePage: http://www.darlingtree.com
#      Version: 0.0.1
#   LastChange: 2011-10-10 22:01:46
#      History:
=============================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);

int main()
{
    printpathto( get_inode("."));
    putchar('\n');
    return 0;
}

void printpathto(ino_t this_inode)
{
    ino_t my_inode;
    char its_name[BUFSIZ];
    if(get_inode("..") != this_inode)
    {
        chdir("..");
        inum_to_name(this_inode,its_name,BUFSIZ);
        my_inode = get_inode(".");
        printpathto(my_inode);
        printf("/%s",its_name);
    }
}

void inum_to_name(ino_t inode_to_finde, char * numebuf, int buflen)
{
    DIR *dir_ptr;
    struct dirent * direntp;
    dir_ptr = opendir(".");
    if( dir_ptr == NULL){
        perror(".");
        exit(1);
    }

    while(( direntp = readdir(dir_ptr)) != NULL)
        if(direntp->d_ino == inode_to_finde)
        {
            strncpy(numebuf, direntp->d_name, buflen);
            numebuf[buflen-1] ='\0';
            closedir(dir_ptr);
            return;
        }
    fprintf(stderr,"error looking for inum %d\n",inode_to_finde);
    exit(1);
}

ino_t get_inode(char *fname)
{
    struct stat info;
    if( stat(fname, &info) == -1){
        fprintf(stderr, "Cannnot stat");
        perror(fname);
        exit(1);
    }
    return info.st_ino;
}

