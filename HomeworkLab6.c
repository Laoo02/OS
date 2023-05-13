#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
// #define _POSIX_SOURCE
#include <dirent.h>
#include <fcntl.h>

int fd[2];
char buffer[1024];

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
        // reg_Menu(filename, option);
        regFile_options(filename, option);
    }
    else if (S_ISLNK(buf->st_mode) != 0)
    {
        printf("The file read is a symbolic link!\n");
        free(buf);
        // symLnk_Menu();
        symLnk_options(filename, option);
    }
    else if (S_ISDIR(buf->st_mode) != 0)
    {
        printf("The file read is a directory!\n");
        free(buf);
        // dir_Menu();
        dir_options(filename, option);
    }
    else
    {
        printf("undetected file type!\n");
        free(buf);
        exit(1);
    }
}

void fileTypeMenu(char filename[50])
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
        reg_Menu();
        // regFile_options(filename, option);
    }
    else if (S_ISLNK(buf->st_mode) != 0)
    {
        printf("The file read is a symbolic link!\n");
        free(buf);
        symLnk_Menu();
        //  symLnk_options(filename, option);
    }
    else if (S_ISDIR(buf->st_mode) != 0)
    {
        printf("The file read is a directory!\n");
        free(buf);
        dir_Menu();
        // dir_options(filename, option);
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

void reg_Menu()
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

void dir_Menu()
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

    //  printf("**child process begun**\n");

    if (opendir(filename) == NULL)
    {
        printf("Could not open the %s directory!\n", filename);
        exit(1);
    }

    char filename2[50];
    strcpy(filename2, filename);

    strcat(filename2, "_file.txt");
    int file = open(filename2, O_RDONLY | O_CREAT);

    if (file < 0)
    {
        perror("cannot open/create file!\n");
        exit(1);
    }

    printf("text file created!\n");

    if (close(file) < 0)
    {
        perror("cannot close file!\n");
        exit(1);
    }
    printf("file closed!\n");

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

    int s = strstr(filename, ".c");
    // printf("s value:%d\n", s);
    if (s)
    {
        printf("it is a C file!\n");

        close(fd[0]);
        dup2(fd[1], 1);

        // execlp("bash", "bash", "bash_proc.bash", filename, NULL);
        // perror("Cannot execute command!\n");
        // exit(1);
    }

    else if (!s)
    {
        // close(fd[0]);
        // dup2(fd[1], 1);
        printf("Not a C file!\n");
        //  execl("usr/bin/wc", "wc", "-'l", filename, NULL);
        // perror("Cannot execute command!\n");
        // exit(1);
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

    if ((dir = opendir(filename)) == NULL)
    {
        printf("Could not open the %s directory!\n", filename);
        exit(1);
    }

    struct dirent *entry;

    printf("The .c files are:");

    // char name[30];

    while ((entry = readdir(dir)) != NULL)
    {
        int p = strstr((char *)(entry->d_name), ".c");
        // free(p);

        //  printf("%s\n", entry->d_name);

        char *ext = strrchr(entry->d_name, '.');

        // if (strstr((entry->d_name), ".c") != NULL)
        if (strcmp(ext, ".c") == 0)
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
    closedir(dir);
}

int main(int argc, char *argv[])
{
    /* if (pipe(fd) == -1)
     {
         printf("cannot create pipe!\n");
         exit(1);
     }*/

    if (argc < 2)
    {
        printf("Too few arguments provided!\n");
    }

    for (int i = 1; i < argc; i++)
    {

        pid_t pid1, pid2, waitP, waitP2;
        int ch_stat, ch_stat2;
        //  char variables[10];

        pid1 = fork();

        if (pid1 < 0)
        {
            printf("error!\n");
            exit(1);
        }

        if (pid1 == 0)
        {
            printf("**child process No1 begun**\n");
            fileTypeMenu(argv[i]);
            exit(20);
        }

        pid2 = fork();

        if (pid2 < 0)
        {
            printf("error!\n");
            exit(1);
        }

        if (pid2 == 0)
        {
            printf("**child process No2 begun**\n");
            char variables[10];
            printf("enter the options to be used:\n");
            scanf("%s", variables);
            printf("**child process begun**\n");
            fileType(argv[i], variables);
            exit(20);
        }

        waitP = wait(&ch_stat);
        if (WIFEXITED(ch_stat) != 0)
        {
            printf("The process with the PID %d exited with status : %d\n", waitP, WEXITSTATUS(ch_stat));
        }
        waitP2 = wait(&ch_stat2);
        if (WIFEXITED(ch_stat2) != 0)
        {
            printf("The process with the PID %d exited with status : %d\n", waitP2, WEXITSTATUS(ch_stat));
        }

        // close(fd[1]);
        // read(fd[0], buffer, 1024);
    }
}