#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include"dc.h"
#include"dp.h"

int main(int argc, char **argv)
{
	DIR *dp=NULL;
	struct dirent *dptr;
	FILE *data_file, *output_file;
	char filename[50], t[20];
	char *line, *token;
	int params[2], i, j;
	double *arr;
	struct retval r;
	
	dp = opendir("../data");	
	while((dptr=readdir(dp))!=NULL)
	{
		sprintf(filename, "../data/%s", dptr->d_name); 
		printf("%s\n", filename);
		data_file = fopen(filename, "r");
		fgets(t, sizeof(t), data_file); t[strlen(t)-1]='\0';

		token = strtok(t, ","); i=0;
		while(token)
		{
			params[i] = atoi(token);
			token=strtok(NULL, ",");
			i++;
		}
		
		// printf("\n%d, %d\n", params[0], params[1]);
		line = malloc(sizeof(char) * params[0] * 10);
		while(fgets(line, sizeof(char) * params[0] * 10, data_file))
		{
			line[strlen(line)-1]='\0';
			printf("%s\n", line);
			arr = (double*)malloc(sizeof(double)*params[0]);
			token = strtok(line, ","); i=0;
			while(token)
			{
				arr[i] = atof(token);
				token=strtok(NULL, ",");
				i++;
			}
			r = dc(arr, 0, params[0]-1);
			double a[4] = {1., 2., -3., 4.};
			r = dc(a,0,3);
			printf("%d, %d, %d\n", r.low, r.high, r.val);
			//dp(arr);
			free(line);
			free(arr);
			line=(char*)malloc(sizeof(char)*10*params[0]);
			break;
		}

		break;
	}
}
