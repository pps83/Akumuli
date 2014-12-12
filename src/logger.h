/**
 * Copyright (c) 2014 Eugene Lazin <4lazin@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <sstream>

#include <log4cxx/logger.h>

#include <boost/circular_buffer.hpp>

namespace Akumuli {

class Formatter {
public:
    enum SinkType {
        LOGGER_INFO,
        LOGGER_ERROR,
        BUFFER,
        NONE,
    };
private:
    std::stringstream str_;
    // Optional parameters
    SinkType sink_;
    log4cxx::LoggerPtr logger_;
    boost::circular_buffer<std::string> *buffer_;
public:
    Formatter();

    ~Formatter();

    void set_info_sink(log4cxx::LoggerPtr logger);
    void set_trace_sink(boost::circular_buffer<std::string> *buffer);
    void set_error_sink(log4cxx::LoggerPtr logger, boost::circular_buffer<std::string> *buffer);

    template<class T>
    Formatter& operator << (T const& value) {
        str_ << value;
        return *this;
    }
};

/** Logger class. Not thread safe.
  */
class Logger
{
    boost::circular_buffer<std::string> trace_;
    log4cxx::LoggerPtr plogger_;
public:
    Logger(const char* log_name, int depth);

    Formatter&& trace(Formatter&& fmt = Formatter());
    Formatter&& info(Formatter&& fmt = Formatter());
    Formatter&& error(Formatter&& fmt = Formatter());
};

}

