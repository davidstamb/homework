#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <iostream>
#include <string>
#include <cerrno>

void check(ssize_t value,const std::string& failure_msg)
{
	if(value == -1)
	{
		std::cerr<<failure_msg<<std::endl;
		std::cerr<<"error code: "<<errno<<std::endl;
		exit(-1);
	}
}

int main(){

	const char* path_to_dir = "/home/dave/Desktop/homework5test/homework5";
	DIR* tmp_dir = opendir(path_to_dir);
	
	int input_fd = open("/home/dave/Desktop/homework5test/homework5/input", O_RDONLY);
	check(input_fd,"error when opening file");

	const int buf_size = 2048;
	char* buffer = new char[buf_size];

	ssize_t count = read(input_fd, buffer, buf_size);
	check(count,"error when reading file:"); 

	int fd = creat("output.txt", S_IWUSR | S_IREAD);
	check(fd,"error when reading file:");
	write(fd, buffer, count);

	delete[] buffer;
}
