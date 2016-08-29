#include <stdio.h>
#include <string.h>
#include <time.h>

//#define DEBUG

#ifdef __unix__

#elif defined(_WIN32) || defined(WIN32)

#ifdef DEBUG
	#define OS_Windows
#endif
#define popen _popen
#define pclose _pclose
#endif

char static str[281];

int main()
{
    if(!IsCurrentlyInGitRepo())
        return 0;
    strcpy(str, "#if defined _INC_GIT_HASH\n");
    strcat(str, "    #endinput\n");
    strcat(str, "#else\n");
    strcat(str, "    #define _INC_GIT_HASH\n");
    strcat(str, "#endif\n\n");
	strcat(str, "/*\n");
	strcat(str, " * git-hash 1.0 (https://github.com/Jeroen52/samp-git-hash)\n");
	strcat(str, " * This file has been generated at ");
	AppendCurrentTimeToString(str);
	strcat(str, " */\n\n");
    strcat(str, "#define _INC_GIT_HASH_GIT_HASH \"");
    AppendGitShaToString(str);
	str[(strlen(str)-1)] = '\0';
	strcat(str, "\"");
    store_data("git-hash.inc", str);
	#ifdef DEBUG
		printf("%d\n", strlen(str));
		#ifdef OS_Windows
			getchar();
		#endif
	#endif
}

AppendGitShaToString(char *target)
{
    FILE *sha = popen("git rev-parse --verify HEAD -q", "r");
    char buf[40];
    while (fgets(buf, sizeof(buf), sha) != 0) {
        strcat(target, buf);
    }
    pclose(sha);
	return 1;
}

int IsCurrentlyInGitRepo()
{
    if(system("git rev-parse --verify HEAD -q"))
        return 0;
    return 1;
}

AppendCurrentTimeToString(char *target)
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strcat(str, asctime (timeinfo));
	return 1;
}

store_data(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
		return 1;
    }
	return 0;
}