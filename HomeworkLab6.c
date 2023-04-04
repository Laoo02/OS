#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

  //  char *file=argv[0];

    void menu(char filename[50],char option[10])
    {

        // printf("The name is:%s\n",filename);
        printf("--MENU--\n");
        printf("Options:\n");
         printf("name:n\n");
          printf("last modified:m\n");
           printf("a:access\n");
           printf("***********************************************************************\n");
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
              printf("Access rights: \n");
              printf("USER:\n");
              printf( (buf->st_mode & S_IRUSR) ? "Read:yes\n" : "Read:no\n");
              printf( (buf->st_mode & S_IWUSR) ? "Write:yes\n" : "Write:no\n");
              printf( (buf->st_mode & S_IXUSR) ? "Execution:yes\n" : "Execution:no\n");
              printf("GROUP:\n");
              printf( (buf->st_mode & S_IRGRP) ? "Read:yes\n" : "Read:no\n");
              printf( (buf->st_mode & S_IWGRP) ? "Write:yes\n" : "Write:no\n");
              printf( (buf->st_mode & S_IXGRP) ? "Execution:yes\n" : "Execution:no\n");
              printf("OTHER:");
              printf( (buf->st_mode & S_IROTH) ? "Read:yes\n" : "Read:no\n");
              printf( (buf->st_mode & S_IWOTH) ? "Write:yes\n" : "Write:no\n");
              printf( (buf->st_mode & S_IXOTH) ? "Execution:yes\n" : "Execution:no\n");
                break;

                default:
                printf("invalid input!\n");
            }   
            printf("***********************************************************************\n");
        }
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
