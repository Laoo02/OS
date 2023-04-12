#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

struct stat *buf;
// buf = malloc(sizeof(struct stat));

void fileType(char filename[50], char option[10])
{
    buf = malloc(sizeof(struct stat));

    if (stat(filename, buf) < 0)
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
    }
    else if (S_ISDIR(buf->st_mode) != 0)
    {
        printf("The file read is a directory!\n");
        free(buf);
        symLnk_Menu();
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

/*void dir_Options(char filename[50],char option[10])
{
    if(DIR *opendir(filename) ==NULL)
    {
        printf("Could not open the %s directory!\n",filename);
        exit(1);
    }

    struct dirent *readdir(DIR *dirp);

}*/

void regFile_options(char filename[50], char option[10])
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
