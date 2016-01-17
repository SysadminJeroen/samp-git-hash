#include <stdio.h>
#include <string.h>

#ifdef __unix__

#elif defined(_WIN32) || defined(WIN32)

//#define OS_Windows
#define popen _popen
#define pclose _pclose
#endif

char static str[137];

int main()
{
    if(!is_in_git_repo())
        return 0;
    strcpy(str, "#if defined _INC_GIT_HASH\n");
    strcat(str, "    #endinput\n");
    strcat(str, "#else\n");
    strcat(str, "    #define _INC_GIT_HASH\n");
    strcat(str, "#endif\n\n");
    strcat(str, "#define GitHash ");
    getGitSha(str);
    store_data("git-hash.inc", str);
    //printf("%d\n", strlen(str)); //Debug function, to count the string size if there are any changes to 'str'.
}

getGitSha(char *target)
{
    FILE *sha = popen("git rev-parse --verify HEAD -q", "r");
    char buf[40];
    while (fgets(buf, sizeof(buf), sha) != 0) {
        strcat(target, buf);
    }
    pclose(sha);
}

int is_in_git_repo()
{
    if(system("git rev-parse --verify HEAD -q"))
        return 0;
    return 1;
}

store_data(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}