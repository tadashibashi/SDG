//
// Created by Aaron Ishibashi on 4/21/22.
//
#include "AssertionException.h"
#include "SDG/FileSys/FileSys.h"

SDG::AssertionException::AssertionException(const std::string &statement, const char *file, int line, const char *func)
{
    this->message = FileSys::GetFileName(file) + ":" + std::to_string(line) + ": " + std::string(func) +
            ": \"" + statement + "\" assertion failed!";
}
