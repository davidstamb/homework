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
                std::cerr << "error code: " << errno << std::endl;
                exit(-1);
        }
}

int list_content(int argc, char** argv)
{
        if (argc != 2)
        {
                std::cerr << "One path is required only!!" << std::endl;
                return -1;
        }
        const char* path_to_dir = argv[1];
        DIR* tmp_dir = opendir(path_to_dir);
        if (tmp_dir == nullptr)
        {
                std::cerr << "error when opening directory" << std::endl;
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
                                std::cerr << "something wrong when reading a directory" << std::endl;
                                return errno;
                        }
                        break;
                }
                std::cout << path_info->d_name << "\n";
        }

        std::cout << "\nlistet files at "<< path_to_dir << std::endl;
        auto err_code = closedir(tmp_dir);
        check(err_code, "error when trying to close the directory " + std::string(path_to_dir));
        return 0;
}

int main(int argc, char** argv){

        list_content(argc, argv);
       
	return 0;
}

