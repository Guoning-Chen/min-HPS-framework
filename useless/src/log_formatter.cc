#include <sstream>
#include <iostream>
#include <functional>
#include <tuple>

#include "log_formatter.h"
#include "log_format_item.h"

namespace sylar
{

LogFormatter::LogFormatter(const std::string& pattern)
    :pattern_(pattern) { }

std::string LogFormatter::format(LoggerPtr logger, 
    LogLevel::Level level, LogEventPtr event)
{
    std::stringstream ss;
    for (auto& item : items_)
        item->format(ss, logger, level, event);
    return ss.str();
}

void LogFormatter::init()
{
    // %xxx, %xxx{xxx} %%
    // str, format, type
    std::vector<std::tuple<std::string, std::string, int> > v;
    std::string nstr;
    for (size_t i = 0; i < pattern_.size(); ++i)
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

    static std::map<std::string, 
        std::function<FormatItemPtr(const std::string& str)>> formatItems = {
#define CALL_CONSTRUCTOR(str, C) \
        {#str, [](const std::string& format){ \
        return FormatItemPtr(new C(format));}}

        CALL_CONSTRUCTOR(m, MessageFormatItem),           //m:消息
        CALL_CONSTRUCTOR(p, LevelFormatItem),             //p:日志级别
        CALL_CONSTRUCTOR(r, ElapseFormatItem),            //r:累计毫秒数
        CALL_CONSTRUCTOR(c, NameFormatItem),              //c:日志名称
        CALL_CONSTRUCTOR(t, ThreadIdFormatItem),          //t:线程id
        CALL_CONSTRUCTOR(n, NewLineFormatItem),           //n:换行
        CALL_CONSTRUCTOR(d, DateTimeFormatItem),          //d:时间
        CALL_CONSTRUCTOR(f, FilenameFormatItem),          //f:文件名
        CALL_CONSTRUCTOR(l, LineFormatItem),              //l:行号
        CALL_CONSTRUCTOR(T, TabFormatItem),               //T:Tab
        CALL_CONSTRUCTOR(F, FiberIdFormatItem),           //F:协程id
        CALL_CONSTRUCTOR(N, ThreadNameFormatItem),        //N:线程名称
#undef CALL_CONSTRUCTOR
        };
    // for (auto& item : items_)
    // {
    //     if (std::get<2>(item) == 0)
    //     {
    //         const std::string& str = std::get(0)(item);
    //         FormatItemPtr ptr = FormatItemPtr(new StringFormatItem(format));
    //         items_.push_back(ptr);
    //     }
    //     else
    //     {
    //         const std::string& str = std::get<0>(item);
    //         auto it = formatItems.find(str);
    //         if (it == formatItems.end())
    //         {
    //             const std::string str = std::get<0>(item);
    //             FormatItemPtr ptr = FormatItemPtr(new StringFormatItem("<<error_format %" + str + ">>"))
    //             items_.push_back(ptr);
    //         }
    //         else
    //         {
    //             items_.push_back(it->second(std::get<1>(item)));
    //         }
    //     }

    //     std::cout << std::get<0>(item) << " - " << std::get<1>(item) << 
    //                  " - " << std::get<2>(item) << std::endl;
    // }
}

LogFormatter::FormatItem::FormatItem(const std::string& format)
{

}

}