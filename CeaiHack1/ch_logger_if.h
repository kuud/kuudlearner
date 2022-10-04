#pragma once
#include <string>

enum log_level {
    info,
    debug,
    error,
    warning
};

class ch_logger_interface {
public:
   ch_logger_interface() = default;

    ch_logger_interface(std::string tag) {
        this->tag = tag;
    }

    template<typename T>
    void debug(const T& msg)
    {
        log(log_level::debug, msg);
    }

    template<typename T>
    void error(const T& msg)
    {
        log(log_level::error, msg);
    }
    
    template<typename T>
    void info(const T& msg)
    {
        log(log_level::info, msg);
    }

    template<typename T>
    void warn(const T& msg)
    {
        log(log_level::warning, msg);
    }

    virtual void log(log_level level, std::string message) = 0;
private:
    std::string tag;
};