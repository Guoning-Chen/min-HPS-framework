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

std::string LogFormatter::format(std::shared_ptr<Logger>logger, 
    LogLevel::Level level, LogEvent::ptr event)
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
        std::function<FormatItem::ptr(const std::string& str)>> formatItems = {
#define CALL_CONSTRUCTOR(str, C) \
        {#str, [](const std::string& format){ \
        return FormatItem::ptr(new C(format));}}

        CALL_CONSTRUCTOR(m, MessageFormatItem),
        CALL_CONSTRUCTOR(p, LevelFormatItem),
        CALL_CONSTRUCTOR(r, ElapseFormatItem),
        CALL_CONSTRUCTOR(c, NameFormatItem),
        CALL_CONSTRUCTOR(t, ThreadIdFormatItem),
        CALL_CONSTRUCTOR(n, NewLineFormatItem),
        CALL_CONSTRUCTOR(d, DateTimeFormatItem),
        CALL_CONSTRUCTOR(f, FilenameFormatItem),
        CALL_CONSTRUCTOR(l, StringFormatItem)
#undef CALL_CONSTRUCTOR
        };
    // %m 消息体
    // %p level
    // %r 启动时间
    // %c 日志名称
    // %t 线程id
    // %n 回车换行
    // %d 时间
    // %f 文件名
    // %l 行号
    for (auto& item : items_)
    {
        if (std::get<2>(item) == 0)
        {
            const std::string& str = std::get(0)(item);
            FormatItem::ptr ptr = FormatItem::ptr(new StringFormatItem(format));
            items_.push_back(ptr);
        }
        else
        {
            const std::string& str = std::get<0>(item);
            auto it = formatItems.find(str);
            if (it == formatItems.end())
            {
                const std::string str = std::get<0>(item);
                FormatItem::ptr ptr = FormatItem::ptr(new StringFormatItem("<<error_format %" + str + ">>"))
                items_.push_back(ptr);
            }
            else
            {
                items_.push_back(it->second(std::get<1>(item)));
            }
        }

        std::cout << std::get<0>(item) << " - " << std::get<1>(item) << 
                     " - " << std::get<2>(item) << std::endl;
    }
}

LogFormatter::FormatItem::FormatItem(const std::string& format = "")
{

}


}