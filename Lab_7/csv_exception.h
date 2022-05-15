#ifndef CSV_EXCEPTION_H
#define CSV_EXCEPTION_H

#include <string>

using namespace std;

class CSV_exception : public exception {
    int line;
    string message;
public:
    CSV_exception(int _line);

    const char* what() const noexcept override;
};

#endif // CSV_EXCEPTION_H
