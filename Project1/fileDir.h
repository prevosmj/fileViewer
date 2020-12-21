#ifndef _fileDir_h_
#define _fileDir_h_

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "Buffer.h"

const char clear_command[] = "cls"; // for Windows

class fileDir
{
public:
    void run();

private:
    void display();
    void execute_command(char command, bool& done);

    std::vector<std::string> back;
    Buffer buffer_;
    int window_height_ = 0;
    int window_width_ = 0;
    std::string error_message_;
};

#endif //_fileDir_

