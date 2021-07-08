#include <memory>


namespace sylar
{

// 日志事件
class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();

    const char* getFile() const;
    int32_t getLine() const;
    uint32_t getElapse() const;
    uint32_t getThreadId() const;
    uint32_t getFiberId() const;
    uint64_t getTime() const;
    const std::string& getContent() const;
private:
    const char* file_ = nullptr;// 文件名
    int32_t line_ = 0;          // 行号
    uint32_t elapse_ = 0;       // 程序启动到现在的毫秒
    uint32_t threadId_ = 0;     // 线程id
    uint32_t fiberId_ = 0;       // 协程id
    uint64_t time_;             // 时间戳
    std::string content_;
};

}