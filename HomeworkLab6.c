#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#define _POSIX_SOURCE
#include <dirent.h>

struct stat *buf;
// buf = malloc(sizeof(struct stat));

void fileType(char filename[50], char option[10])
{
    buf = malloc(sizeof(struct stat));

    if (lstat(filename, buf) < 0)
    {
        printf("Error!Cannot read file permissions!\n");
        exit(1);
    }
    if (S_ISREG(buf->st_mode) != 0)
    {
        free(buf);
        printf("The file read is a regular file!\n");
        reg_Menu(filename, option);
        regFile_options(filename, option);
    }
    else if (S_ISLNK(buf->st_mode) != 0)
    {
        printf("The file read is a symbolic link!\n");
        free(buf);
        symLnk_Menu();
        symLnk_options(filename, option);
    }
    else if (S_ISDIR(buf->st_mode) != 0)
    {
        printf("The file read is a directory!\n");
        free(buf);
        dir_Menu();
        dir_options(filename, option);
    }
    else
    {
        printf("undetected file type!\n");
        free(buf);
        exit(1);
    }
}

void symLnk_Menu()
{
    printf("--MENU--\n");
    printf("Options:\n");
    printf("name:n\n");
    printf("last modified:m\n");
    printf("a:access\n");
    printf("l:delete symlink\n");
    printf("t:size of target file\n");
    printf("***********************************************************************\n");
}

void reg_Menu(char filename[50], char option[10])
{
    printf("--MENU--\n");
    printf("Options:\n");
    printf("name:n\n");
    printf("last modified:m\n");
    printf("a:access\n");
    printf("l:create symlink\n");
    printf("d:file size\n");
    printf("***********************************************************************\n");
}

void dir_Menu(char filename[50], char option[10])
{
    printf("--MENU--\n");
    printf("Options:\n");
    printf("name:n\n");
    printf("a:access rights\n");
    printf("d:size\n");
    printf("c:prints the number of files with the .c extension\n");
    printf("***********************************************************************\n");
}

void dir_options(char filename[50], char option[10])
{

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        printf("error!\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("child process begun\n");

        if (opendir(filename) == NULL)
        {
            printf("Could not open the %s directory!\n", filename);
            exit(1);
        }

        if (fork() == 0)
        {
            FILE *f;
            f = fopen("OS.txt", "w");
            fclose(f);
        }
        else
        {

            buf = malloc(sizeof(struct stat));

            struct dirent *readdir(DIR * dirp);

            for (int i = 1; i < strlen(option); i++)
            {
                switch (option[i])
                {
                case 'n':
                    printf("The name is:%s\n", filename);
                    break;

                case 'a':
                    permissions(buf->st_mode);
                    break;

                case 'c':
                    no_of_cFiles(filename);
                    break;

                case 'd':
                    printf("the file has the size: %lf bytes", (double)buf->st_size);
                    break;

                default:
                    printf("invalid input!\n");
                    break;
                }
                printf("***********************************************************************\n");
            }
            closedir(filename);
            free(buf);
        }
    }
}

void regFile_options(char filename[50], char option[10])
{
    char *p = strstr(filename, ".c");
    if (p && (fork() == 0))
    {
        printf("this is a child process and produces a separate output!\n");
    }
    else if (!p)
    {
        printf("Not a reg file!\n");
    }

    else
    {
        // struct stat *buf;
        buf = malloc(sizeof(struct stat));

        if (stat(filename, buf) < 0)
        {
            printf("Error!Cannot read file permissions!\n");
            exit(1);
        }

        for (int i = 1; i < strlen(option); i++)
        {
            switch (option[i])
            {
            case 'n':
                printf("The name is:%s\n", filename);
                break;

            case 'a':
                permissions(buf->st_mode);
                break;

            case 'm':
                printf("Last time the file was modified:%s", ctime(&buf->st_mtime));
                break;

            case 'h':
                printf("The file named %s has %d hard links", filename, buf->st_nlink);
                break;

            case 'l':
                create_SL(filename);
                break;

            case 'd':
                printf("the file has the size: %lf bytes", (double)buf->st_size);
                break;

            default:
                printf("invalid input!\n");
                break;
            }
            printf("***********************************************************************\n");
        }

        free(buf);
    }
}

void symLnk_options(char filename[50], char option[10])
{
    buf = malloc(sizeof(struct stat));

    if (lstat(filename, buf) < 0)
    {
        printf("Error!Cannot read file permissions!\n");
        exit(1);
    }

    for (int i = 1; i < strlen(option); i++)
    {
        switch (option[i])
        {
        case 'n':
            printf("The name is:%s\n", filename);
            break;

        case 'a':
            permissions(buf->st_mode);
            break;

        case 'm':
            printf("Last time the file was modified:%s", ctime(&buf->st_mtime));
            break;

        case 'l':
            delete_SL(filename);
            break;

        case 'd':
            printf("the file has the size: %lf bytes", (double)buf->st_size);
            break;

        case 't':

        default:
            printf("invalid input!\n");
            break;
        }
        printf("***********************************************************************\n");
    }

    free(buf);
}

void permissions(unsigned short mode)
{
    printf("Access rights: \n");
    printf("USER:\n");
    printf((mode & S_IRUSR) ? "Read:yes\n" : "Read:no\n");
    printf((mode & S_IWUSR) ? "Write:yes\n" : "Write:no\n");
    printf((mode & S_IXUSR) ? "Execution:yes\n" : "Execution:no\n");
    printf("GROUP:\n");
    printf((mode & S_IRGRP) ? "Read:yes\n" : "Read:no\n");
    printf((mode & S_IWGRP) ? "Write:yes\n" : "Write:no\n");
    printf((mode & S_IXGRP) ? "Execution:yes\n" : "Execution:no\n");
    printf("OTHER:");
    printf((mode & S_IROTH) ? "Read:yes\n" : "Read:no\n");
    printf((mode & S_IWOTH) ? "Write:yes\n" : "Write:no\n");
    printf((mode & S_IXOTH) ? "Execution:yes\n" : "Execution:no\n");
}

void create_SL(char filename[50])
{
    char SL_name[50];
    printf("Choose a softlink file name:");
    scanf("%s", &SL_name);
    printf("\n");
    printf("file name:%s\n", SL_name);
    int Sl_test = symlink(filename, SL_name);
    if (Sl_test == 0)
    {
        printf("Soft link added!");
    }
}

void delete_SL(char filename[50])
{
    if (unlink(filename) == 0)
    {
        printf("symlink successfully deleted!\n");
    }
    else
    {
        printf("cannot delete symlink!\n");
    }
}

void no_of_cFiles(char filename[50])
{
    int count = 0;
    DIR *dir;

    if (dir = opendir(filename) == NULL)
    {
        printf("Could not open the %s directory!\n", filename);
        exit(1);
    }

    struct dirent *entry;

    printf("The .c files are:");

    // char name[30];

    while ((entry = readdir(dir)) != NULL)
    {
        //  p = strstr((char *)(entry->d_name), ".c");
        // free(p);

        printf("%s\n", entry->d_name);

        if (strstr((entry->d_name), ".c") != NULL)
        {
            // strcpy(name, entry->d_name);
            printf("%s\n", entry->d_name);
            count++;
        }
    }
    printf("\n");

    if (count == 0)
    {
        printf("No .c files inside the directory!\n");
    }
    else
    {
        printf("There are %d .c files in the directory", count);
    }
    closedir(filename);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Too few arguments provided!\n");
    }
    else if (argc == 3)
    {
        fileType(argv[1], argv[2]);
    }
}
