#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


          void menu(char filename[50],char option[10]){
         printf("--MENU--\n");
        printf("Options:\n");
         printf("name:n\n");
          printf("last modified:m\n");
           printf("a:access\n");
           printf("***********************************************************************\n");
           options(filename,option);
    }

    void options(char filename[50],char option[10])
    {
        struct stat *buf;
        buf=malloc(sizeof(struct stat));

                if(stat(filename,buf)<0)
                {
                    printf("Error!Cannot read file permissions!\n");
                    exit(1);
                }

        for(int i=1;i<strlen(option);i++)
        {
            switch(option[i])
            {
                case 'n':
                printf("The name is:%s\n",filename);
                break;

                case 'a':
              permissions(buf->st_mode);
                break;

                case 'm':
                //last_modified(buf->st_mtime);
                printf("Last time the file was modified:%s",ctime(&buf->st_mtime));
                break;

                case 'h':
                printf("The file named %s has %d hard links",filename,buf->st_nlink);
                break;

                default:
                printf("invalid input!\n");
            }   
            printf("***********************************************************************\n");
        }
    }

    void permissions(unsigned short mode)
    {
        printf("Access rights: \n");
              printf("USER:\n");
              printf( (mode & S_IRUSR) ? "Read:yes\n" : "Read:no\n");
              printf( (mode & S_IWUSR) ? "Write:yes\n" : "Write:no\n");
              printf( (mode & S_IXUSR) ? "Execution:yes\n" : "Execution:no\n");
              printf("GROUP:\n");
              printf( (mode & S_IRGRP) ? "Read:yes\n" : "Read:no\n");
              printf( (mode & S_IWGRP) ? "Write:yes\n" : "Write:no\n");
              printf( (mode & S_IXGRP) ? "Execution:yes\n" : "Execution:no\n");
              printf("OTHER:");
              printf( (mode & S_IROTH) ? "Read:yes\n" : "Read:no\n");
              printf( (mode & S_IWOTH) ? "Write:yes\n" : "Write:no\n");
              printf( (mode & S_IXOTH) ? "Execution:yes\n" : "Execution:no\n");
    }


int main(int argc,char *argv[])
    {
        if(argc < 3 )
        {
            printf("Too few arguments provided!\n");
        }
        else
        {
            menu(argv[1],argv[2]);
        }
     
    }
