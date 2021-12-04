#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <iostream>
#include <string>
#include <cerrno>

void check(ssize_t value, const std::string& failure_msg)
{
	if (value == -1)
	{
		std::cerr << failure_msg << std::endl;
		std::cerr << "\nerror code: " << errno << std::endl;
		exit(-1);
	}
}


int list_content(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "\nAt least 1 path required" << std::endl;
		return -1;
	}
	
	const char* path_to_dir = argv[1];
	DIR* tmp_dir = opendir(path_to_dir);
	
	if (tmp_dir == nullptr)
	{
		std::cerr << " error: No such file or directory : "<< path_to_dir << std::endl;
		return errno;
	}

	while (true)
	{
		const int old_err = errno;
		dirent* path_info = readdir(tmp_dir);
		
		if (path_info == nullptr)
		{
			if (errno != old_err)
			{
				std::cerr << "\nsomething wrong when reading a directory" << std::endl;
				return errno;
			}
			break;
		}
		
		std::cout<<"\n";

		std::cout <<"("<< path_info->d_name<<")"<< " -- ";
		switch (path_info->d_type)
		{
			case DT_BLK:
				std::cout << "Block Device";
				break;
			case DT_CHR:
				std::cout << "Character Device";
				break;
			case DT_DIR:
				std::cout << "Directory";
				break;
			case DT_FIFO:
				std::cout << "Named Pipe (FIFO)";
				break;
			case DT_LNK:
				std::cout << "Symbolic Link";
				break;
			case DT_REG:
				std::cout << "Regular File";
				break;
			default:
				std::cout << "Unkown file type";
				break;
		}
	}

     	std::cout << "\n\nlisted files and directories in " << path_to_dir << std::endl;

	return 0;
}

int main (int argc,char** argv){

	list_content(argc,argv);

	return 0;
}
