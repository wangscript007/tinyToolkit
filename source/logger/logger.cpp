/**
 *
 *  作者: hm
 *
 *  说明: 日志
 *
 */


#include "logger.h"


namespace logger
{
	/**
	 *
	 * 构造函数
	 *
	 * @param name 名称
	 *
	 */
	ILogger::ILogger(std::string name) : _name(std::move(name))
	{

	}

	/**
	 *
	 * 写入
	 *
	 * @param option 操作
	 *
	 */
	void ILogger::Write(LOG_OPTION_TYPE option)
	{
		Context context{ };

		context.name = _name;
		context.option = option;

		Write(context);
	}

	/**
	 *
	 * 写入
	 *
	 * @param priority 优先级
	 * @param content 内容
	 *
	 */
	void ILogger::Write(LOG_PRIORITY_TYPE priority, const std::string & content)
	{
		Context context{ };

		context.name = _name;
		context.option = LOG_OPTION_TYPE::WRITE;
		context.content = content;
		context.priority = priority;

		Write(context);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Debug(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::DEBUGS, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Info(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::INFO, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Notice(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::NOTICE, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Warning(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::WARNING, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Error(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::ERRORS, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Critical(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::CRITICAL, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Alert(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::ALERT, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Fatal(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::FATAL, content);
	}

	/**
	 *
	 * 写入
	 *
	 * @param content 内容
	 *
	 */
	void ILogger::Emerg(const std::string & content)
	{
		Write(LOG_PRIORITY_TYPE::EMERG, content);
	}

	/**
	 *
	 * 添加节点
	 *
	 * @param sink 节点
	 *
	 */
	void ILogger::AddSink(const std::shared_ptr<ISink> & sink)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_sinks.insert(std::make_pair(sink->Name(), sink));
	}

	/**
	 *
	 * 移除节点
	 *
	 * @param name 节点名称
	 *
	 */
	void ILogger::RemoveSink(const std::string & name)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_sinks.erase(name);
	}

	/**
	 *
	 * 移除节点
	 *
	 * @param sink 节点对象
	 *
	 */
	void ILogger::RemoveSink(const std::shared_ptr<ISink> & sink)
	{
		std::lock_guard<std::mutex> lock(_mutex);

		_sinks.erase(sink->Name());
	}

    /**
     *
     * 是否有效
     *
     * @return 是否有效
     *
     */
    bool ILogger::IsValid() const
    {
        return _isValid;
    }

	/**
	 *
	 * 名称
	 *
	 * @return 名称
	 *
	 */
	const std::string & ILogger::Name() const
	{
		return _name;
	}
}
