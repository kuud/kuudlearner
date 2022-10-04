#pragma once
#include "ch_logger_if.h"

#include "Windows.h"
#include <wincon.h>

class ch_color_logger : public ch_logger_interface {
public:
    ch_color_logger() : ch_color_logger("CHLogger") {}

    ch_color_logger(std::string tag);

    void log(log_level level, std::string message);
private:
    short colors[4];
    HANDLE console_handle;
};