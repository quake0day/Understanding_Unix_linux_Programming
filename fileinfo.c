/*=============================================================================
#     FileName: fileinfo.c
#         Desc: 
#       Author: quake0day
#        Email: quake0day@gmail.com
#     HomePage: http://www.darlingtree.com
#      Version: 0.0.1
#   LastChange: 2011-09-28 19:59:16
#      History:
=============================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int ac, char *av[])
{
    struct stat info; /* buffer for file info */

    if(ac>1)
        if(stat(av[1],&info) !=-1){
            show_stat_into(av[1],&info);
            return 0;
        }
        else
            perror(av[1]);
    return 1; /* report stat() errors */
}

show_stat_into(char *fname, struct stat *buf)
    /*
     * displays some info from stat in a name = value format
     */
{
    printf("    mode: %o\n",buf->st_mode); /*type + mode*/
    printf("    links: %d\n",buf->st_nlink); /*#links*/
    printf("    user: %d\n",buf->st_uid); /*type + mode*/
    printf("    group: %d\n",buf->st_gid); /*type + mode*/
    printf("    size: %d\n",buf->st_size); /*type + mode*/
    printf("    modetime: %d\n",buf->st_mtime); /*type + mode*/
    printf("    name: %s\n",fname); /*type + mode*/
}


