#include "csv_exception.h"

CSV_exception::CSV_exception(int _line) {
    line = _line;
    message = to_string(line);
}

const char* CSV_exception::what() const noexcept {
    return message.c_str();
}
