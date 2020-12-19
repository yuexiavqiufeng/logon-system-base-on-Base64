#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#define Account_size 20

#define filename_size 20
#define Password_size 20
#define Password_base64_encode_size Password_size*4/3+3
int filename_strcat(int file_sequence, char *file_name)
{
    
	strcat(file_name, "file_");
	if(file_sequence>pow(10,filename_size-9)){
        return -1;
    }
	char strtem[10];
	sprintf(strtem, "%d", file_sequence);
	strcat(file_name, strtem);
	strcat(file_name, ".dat");

	return 0;
}

int main()
{
			
			printf("%d",
Password_base64_encode_size);
			    return 0;
}
