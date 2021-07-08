#include <memory>
#include <string>
#include <vector>

#include "log_event.h"

namespace sylar
{

// 日志格式器
class LogFormatter
{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    std::string format(std::ostream& os, LogEvent::ptr event);
private:
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem() {}
        virtual std::string format(LogEvent::ptr event) = 0;
    };

    void init();
private:
    std::string pattern_;
    std::vector<FormatItem::ptr> items_;
};

}