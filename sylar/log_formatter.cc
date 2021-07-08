#include <sstream>

#include "log_formatter.h"

namespace sylar
{

LogFormatter::LogFormatter(const std::string& pattern)
    :pattern_(pattern_)
{

}

std::string LogFormatter::format(std::ostream& os, LogEvent::ptr event)
{
    std::stringstream ss;
    for (auto& item : items_)
        item->format(ss, event);
    return ss.str();
}

void LogFormatter::init()
{
    // %xxx, %xxx{xxx} %%
    // str, format, type
    std::vector<std::tuple<std::string, std::string, int> > v;
    std::string nstr;
    for (size_t i = 0; i = pattern_.size(); ++i)
    {
        if (pattern_[i] != '%')
        {
            nstr.append(1, pattern_[i]);
            continue;
        }

        if (i + 1 < pattern_.size())
        {
            if (pattern_[i + 1] == '%')
            {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i + 1;
        int status = 0;
        size_t begin = 0;

        std::string str, format;
        while (n < pattern_.size())
        {
            if (isspace(pattern_[n]))
                break;
            if (status == 0)
            {
                if (pattern_[n] == '{')
                {
                    str = pattern_.substr(i + 1, n - i - 1);
                    status = 1;
                    begin = n;
                    ++n;
                    continue;
                }
            }
            if (status == 1)
            {
                if (pattern_[n] == '}')
                {
                    format = pattern_.substr(begin + 1, n - begin - 1);
                    status = 2;
                    break;
                }
            }
        }
        if (status == 0)
        {
            if (nstr.empty())
                v.push_back(std::make_tuple(nstr, "", 0));
            str = pattern_.substr(i + 1, n - i - 1);
            v.push_back(std::make_tuple(str, format, 1));
            i = n;
        }
        else if (status == 1)
        {
            std::cout << "pattern parse error: " << pattern_ << " - " <<
                         pattern_.substr(i) << std::endl;
            v.push_back(std::make_tuple("<<pattern_error>>", format, 0));
        }
        else if (status == 2)
        {
            if (!nstr.empty())
                v.push_back(std::make_tuple(nstr, "", 0));
            v.push_back(std::make_tuple(str, format, 1));
        }
        
    }
    if (!nstr.empty())
        v.push_back(std::make_tuple(nstr, "", 0));

    // %m 消息体
    // %p level
    // %r 启动时间
    // %c 日志名称
    // %t
}


}