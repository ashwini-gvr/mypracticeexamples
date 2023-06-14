#include<stdio.h>
#include<regex.h>
#include<dirent.h>
#include<string.h>
regex_t reegex;

// Variable for return type
int returnValue1;
int returnValue2;

void listFilesRecursively(char*,char*,char*);
int main(int argc,char *argv[])
{

	int i=0;

	for(i=1;i<argc;i++)
	{

		printf("\nInput[%d]=%s",i,argv[i]);
	}

	if(strcmp(argv[1],"search")==0)
	{
		// Creation of regEx
		returnValue1=regcomp( &reegex, argv[3], 0);
		if(returnValue1==0)
		{
			listFilesRecursively(argv[2],argv[3],".");
		}
		else
		{
			printf("\nInvalid Input!\n");
		}
	}
	else
	{
		printf("\nCommand not supported!\n");
		printf("\nSupported input format:Test search .file_extension filename.* \nPlease rerun!\n");
	}

	return 0;
}
void listFilesRecursively(char* extension,char* pattern,char* basepath)
{

	char path[1000];
	memset(path,0x00,sizeof(path));
	struct dirent *dp;
	DIR *dir=opendir(basepath);
	if(!dir)
	{
		return;

	}

	while((dp=readdir(dir))!=NULL)
	{

		if(strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0)
		{
			char *dot;
			//If file?
			if((dot=strrchr(dp->d_name, '.'))!=NULL)
			{

				if(strcmp(dot,extension)==0)
				{

					// Comparing pattern
					returnValue2 = regexec( &reegex, dp->d_name,
							0, NULL, 0);

					if(returnValue2==0)
						printf("\nFile matching pattern is:%s\n",dp->d_name);
				}
			}//If Directory?
			else
			{

				if(strcmp(dp->d_name,extension)==0)
				{

					// Comparing pattern
					returnValue2 = regexec( &reegex, dp->d_name,
							0, NULL, 0);

					if(returnValue2==0)
						printf("\nDirectory matching pattern is:%s\n",dp->d_name);
				}

			}
			strcpy(path,basepath);
			strcat(path,"/");
			strcat(path,dp->d_name);

			listFilesRecursively(extension,pattern,path);


		}


	}

	closedir(dir);
}

