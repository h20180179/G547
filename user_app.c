/* File copy example from "Design of UNIX Operating System" by Maurice J. Bach */
#include<fcntl.h>
#include <linux/random.h>

char buffer[2048];
int version =1 ;


int main(int argc,char *argv[])
{
	int myfile,pid;
	
	pid = getpid();
	printf("Process PID = %d\n", pid);
	if(argc != 2)
	{
		printf("Usage :<readfile>\n");
		printf("file value %d \n",myfile);
		exit(1);
	}

	myfile = open(argv[1], O_RDONLY);

	if(myfile == -1)
	{
		printf("cannot open source file\n");
		exit(1);
	}


	read_value(myfile);
	
	close(myfile);
	exit(0);
}

read_value(int old)
{
	
	read(old, buffer, sizeof(buffer));
	puts(buffer);
	

}
