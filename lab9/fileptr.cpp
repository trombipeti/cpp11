#include <cstdio>
#include <string>
#include <vector>
#include <stdexcept>

/* FILE* RAII */
class FilePtr {
    public:
        FilePtr() : fp_(nullptr), filename_("") {}
        explicit FilePtr(const char * filename, const char * mode) 
        {
            filename_ = filename;
            fp_ = fopen(filename, mode);
            if(fp_ == nullptr)
            {
                throw std::runtime_error("Could not open file");
            }
        }
        ~FilePtr() {
            close_if_open();
        }
        /* nem másolható */
        FilePtr(FilePtr const &) = delete;
        FilePtr & operator=(FilePtr const &) = delete;
        FilePtr & operator=(FilePtr && other)
        {
            if(this != &other)
            {
                close_if_open();
                fp_ = other.fp_;
                filename_ = other.filename_;
                other.fp_ = nullptr;
                other.filename_ = "";
            }
            return *this;
        }
        FilePtr(FilePtr && other)
        {
            close_if_open();
            fp_ = other.fp_;
            filename_ = other.filename_;
            other.fp_ = nullptr;
            other.filename_ = "";
        }
        operator FILE* () const {
            return fp_;
        }
    private:
        FILE *fp_;
        std::string filename_;
        void close_if_open() {
            if (fp_ != nullptr)
                fclose(fp_);
            fp_ = nullptr;
        }
};

/* ne lehessen ilyet csinálni (az operator FILE* miatt lehetne) */
void fclose(FilePtr) = delete;

FilePtr open_for_writing(char const *name) {
    return FilePtr{name, "wt"};
}


int main() {
    //     FilePtr fp{"hello.txt", "wt"};
    //     fprintf(fp, "Hello vilag\n");

    //     FilePtr fp = open_for_writing("hello.txt");
    //     fprintf(fp, "Hello vilag");

//     FilePtr fp;
//     fp = open_for_writing("hello.txt");
//     fprintf(fp, "Hello vilag");
//     fp = open_for_writing("hello2.txt");
//     fprintf(fp, "Hello vilag");

    std::vector<FilePtr> files;
    files.push_back(open_for_writing("hello.txt"));
    files.push_back(open_for_writing("hello2.txt"));
    fprintf(files[0], "hello.txt");
    fprintf(files[1], "hello2.txt");

    return 0;
}
