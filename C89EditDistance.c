/*
*	Student ID: 1001296598
*	Name: Joshua Tran
*	Class: cse-2320
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <glob.h>


/* Finds the minimumn between the three variables passed */
int min(int a, int b, int c)
{
	if(a <= b)
	{
		if(a <= c)
		{
			return a;
		}
	}
	if(b <= c)
	{
		return b;
	}
	return c;
}


/* Edit Distance function given from geekforgeeks adapted to C */
int editDistDP(char* str1, char* str2, int m, int n) 
{ 
	int i, j;
	int **dp = (int **)malloc( ( m * sizeof(int *) ) + 1); 
    for (i=0; i < m + 1; i++) 
         dp[i] = (int *)malloc( ( n * sizeof(int) ) + 1); 
	
	
	
    for (i=0; i<=m; i++) 
    { 
        for (j=0; j<=n; j++) 
        { 
            if (i==0) 
            {  
			    dp[i][j] = j;
			}
            else if (j==0) 
			{
			    dp[i][j] = i;
			}
            else if (str1[i-1] == str2[j-1]) 
			{
				dp[i][j] = dp[i-1][j-1]; 
			}
            else
			{
				dp[i][j] = 1 + min(dp[i][j-1],  
                                   dp[i-1][j], 
                                   dp[i-1][j-1]);
			}
                
        } 
    } 
  
    return dp[m][n]; 
}


int main(int argc, char** argv)
{
	/* vars for taking in argv */
	char* fileExtention;
	int sizeOfArgv2;
	int editDistance;

	/* taken from the glob example */
	glob_t paths;  
    int csource;
    char** p;
     

	/* vars for dealing with the edit distance */
	int editD;
	char** p2;
	int i;
	int flag;

	/* input checking */
	if(argc != 3)
	{
		printf("usage:    executableName  maxDistanceInteger  fileNameExtension\n");
		return(0);
	}

	/* storing argv variables */
	editDistance = atoi(argv[1]);
	sizeOfArgv2 = strlen(argv[2]);
	fileExtention = malloc(sizeOfArgv2 + 1); /* possible need for additional 1 */
	fileExtention = strcpy(fileExtention, "*");
	fileExtention = strcat(fileExtention, argv[2]);


    /* taken from the glob example and implemented to */
    csource = glob(fileExtention, 0, NULL, &paths);
    if (csource == 0)
    {
		i = 1;
		/* Loop for the currently looked at file name */
        for (p=paths.gl_pathv; *(p + 1) != NULL; ++p)
		{
			flag = 0;
			/* loop for everything after the above file */
			for(p2 = paths.gl_pathv + i; *(p2) != NULL; ++p2)
			{
				editD = editDistDP(*p, *(p2), strlen(*p), strlen(*p2));
				/* printing the results if it qualifies */
				if(flag == 0 && editD <= editDistance)
				{
					printf("%s\n", *p); 
					printf("    %d, %s\n", editD, *p2);
					flag++;
				}
				else if(editD <= editDistance)
				{
					printf("    %d, %s\n", editD, *p2);
				}
			}
			i++;
		}
    }

	/* memory management */
	free(fileExtention);
	globfree(&paths);  /* function that frees the memory of the matching strings */
}
