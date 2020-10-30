#include <stdio.h>

int main()
{
	FILE *fp = fopen("test.log", "r+");

	char buf[1024] = {0};
	int i = 5;

	while(fgets(buf, sizeof(buf), fp)){
		printf("buf=%s", buf);
		if(i != 0){
			i--;
			sleep(1);
		}
	}

	return 0;
}
