/**
 *
 *  作者: hm
 *
 *  说明: 主函数
 *
 */


#include "main.h"


static void Math()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::cout << "IsOdd  : " << tinyToolkit::util::Math::IsOdd(123) << std::endl;
		std::cout << "IsOdd  : " << tinyToolkit::util::Math::IsOdd(456) << std::endl;

		std::cout << "IsEven : " << tinyToolkit::util::Math::IsEven(123) << std::endl;
		std::cout << "IsEven : " << tinyToolkit::util::Math::IsEven(456) << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Time()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::cout << "Timezone        : " << tinyToolkit::util::Time::Timezone() << std::endl;
		std::cout << "Hours           : " << tinyToolkit::util::Time::Hours() << std::endl;
		std::cout << "Minutes         : " << tinyToolkit::util::Time::Minutes() << std::endl;
		std::cout << "Seconds         : " << tinyToolkit::util::Time::Seconds() << std::endl;
		std::cout << "Milliseconds    : " << tinyToolkit::util::Time::Milliseconds() << std::endl;
		std::cout << "Microseconds    : " << tinyToolkit::util::Time::Microseconds() << std::endl;
		std::cout << "Nanoseconds     : " << tinyToolkit::util::Time::Nanoseconds() << std::endl;
		std::cout << "OffsetTime      : " << tinyToolkit::util::Time::OffsetTime(10, 1, 50, 30) << std::endl;
		std::cout << "OffsetTime      : " << tinyToolkit::util::Time::OffsetTime(-2, 1, 50, 30) << std::endl;
		std::cout << "Format          : " << tinyToolkit::util::Time::Format(tinyToolkit::util::Time::Seconds(), 0) << std::endl;
		std::cout << "Format          : " << tinyToolkit::util::Time::Format(tinyToolkit::util::Time::Seconds(), 8, "%4d_%02d_%02d_%02d_%02d_%02d") << std::endl;
		std::cout << "FromString      : " << tinyToolkit::util::Time::FromString("1970-01-01 08:00:00") << std::endl;
		std::cout << "UTCTimeString   : " << tinyToolkit::util::Time::UTCTimeString() << std::endl;
		std::cout << "UTCTimeString   : " << tinyToolkit::util::Time::UTCTimeString("%4d_%02d_%02d_%02d_%02d_%02d") << std::endl;
		std::cout << "LocalTimeString : " << tinyToolkit::util::Time::LocalTimeString() << std::endl;
		std::cout << "LocalTimeString : " << tinyToolkit::util::Time::LocalTimeString("%4d_%02d_%02d_%02d_%02d_%02d") << std::endl;
		std::cout << "TimePoint       : " << tinyToolkit::util::Time::TimePoint().time_since_epoch().count() << std::endl;
		std::cout << "TimePoint       : " << tinyToolkit::util::Time::TimePoint(1234509876).time_since_epoch().count() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Latch()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		tinyToolkit::util::CountLatch latch(10);

		std::thread waitThread([&]
		{
			latch.Wait();
		});

		std::thread consumeThread_1([&]
		{
			while (latch.RemainingCount())
			{
				latch.Down();

				std::cout << "consumeThread_1 : " << latch.RemainingCount() << std::endl;

				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		});

		std::thread consumeThread_2([&]
		{
			while (latch.RemainingCount())
			{
				latch.Down();

				std::cout << "consumeThread_2 : " << latch.RemainingCount() << std::endl;

				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		});

		waitThread.join();

		consumeThread_1.join();
		consumeThread_2.join();

		std::cout << "watch done : " << latch.RemainingCount() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Regex()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::cout << "IsIP       : " << tinyToolkit::util::Regex::IsIP("192.168.2.0") << std::endl;
		std::cout << "IsIP       : " << tinyToolkit::util::Regex::IsIP("192.168.2.255") << std::endl;
		std::cout << "IsIP       : " << tinyToolkit::util::Regex::IsIP("192.168.2.256") << std::endl;

		std::cout << "IsMac      : " << tinyToolkit::util::Regex::IsMac("aa:bb:cc:dd:ee") << std::endl;
		std::cout << "IsMac      : " << tinyToolkit::util::Regex::IsMac("aa-bb-cc-dd-ee") << std::endl;
		std::cout << "IsMac      : " << tinyToolkit::util::Regex::IsMac("aa:bb:cc:dd:ee:ff") << std::endl;
		std::cout << "IsMac      : " << tinyToolkit::util::Regex::IsMac("aa-bb-cc-dd-ee-ff") << std::endl;
		std::cout << "IsMac      : " << tinyToolkit::util::Regex::IsMac("aa:bb:cc:dd:ee:ff:") << std::endl;
		std::cout << "IsMac      : " << tinyToolkit::util::Regex::IsMac("aa-bb-cc-dd-ee-ff-") << std::endl;

		std::cout << "IsIPv4     : " << tinyToolkit::util::Regex::IsIPv4("192.168.2.0") << std::endl;
		std::cout << "IsIPv4     : " << tinyToolkit::util::Regex::IsIPv4("192.168.2.255") << std::endl;
		std::cout << "IsIPv4     : " << tinyToolkit::util::Regex::IsIPv4("192.168.2.256") << std::endl;

		std::cout << "IsIPv6     : " << tinyToolkit::util::Regex::IsIPv6("2001::1319:8a2h:37") << std::endl;
		std::cout << "IsIPv6     : " << tinyToolkit::util::Regex::IsIPv6("f1ec:a63b:1db9::828") << std::endl;
		std::cout << "IsIPv6     : " << tinyToolkit::util::Regex::IsIPv6("fe80::8c3d:dee5:19b:22b7%4") << std::endl;

		std::cout << "IsMail     : " << tinyToolkit::util::Regex::IsMail("abc@xyz") << std::endl;
		std::cout << "IsMail     : " << tinyToolkit::util::Regex::IsMail("abc@xyz.com") << std::endl;
		std::cout << "IsMail     : " << tinyToolkit::util::Regex::IsMail("abc@xyz.com.cn") << std::endl;

		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019-2-28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019/2/28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019-2-29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019/2/29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020-2-28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020/2/28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020-2-29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020/2/29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019-02-28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019/02/28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019-02-29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2019/02/29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020-02-28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020/02/28") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020-02-29") << std::endl;
		std::cout << "IsDate     : " << tinyToolkit::util::Regex::IsDate("2020/02/29") << std::endl;

		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("23:59:59") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("23:59:60") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("23:60:00") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("24:00:00") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("23:59:59.000") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("23:59:60.000") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("23:60:00.000") << std::endl;
		std::cout << "IsTime     : " << tinyToolkit::util::Regex::IsTime("24:00:00.000") << std::endl;

		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2019-02-28 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2019/02/28 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2019-02-29 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2019/02/29 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2020-02-28 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2020/02/28 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2020-02-29 23:59:59") << std::endl;
		std::cout << "IsDateTime : " << tinyToolkit::util::Regex::IsDateTime("2020/02/29 23:59:59") << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Signal()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		tinyToolkit::util::Signal::RegisterIgnore();

		tinyToolkit::util::Signal::RegisterTerminate([](int signalNo){ std::cout << "Terminate : " << signalNo << std::endl; });
		tinyToolkit::util::Signal::RegisterException([](int signalNo){ std::cout << "Exception : " << signalNo << std::endl; });

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		tinyToolkit::util::Signal::Raise(SIGILL);
		tinyToolkit::util::Signal::Raise(SIGFPE);
		tinyToolkit::util::Signal::Raise(SIGABRT);
		tinyToolkit::util::Signal::Raise(SIGSEGV);

		tinyToolkit::util::Signal::Raise(SIGINT);
		tinyToolkit::util::Signal::Raise(SIGTERM);
		tinyToolkit::util::Signal::Raise(SIGBREAK);

	#else

		tinyToolkit::util::Signal::Raise(SIGHUP);
		tinyToolkit::util::Signal::Raise(SIGPIPE);
		tinyToolkit::util::Signal::Raise(SIGCHLD);

		tinyToolkit::util::Signal::Raise(SIGILL);
		tinyToolkit::util::Signal::Raise(SIGFPE);
		tinyToolkit::util::Signal::Raise(SIGABRT);
		tinyToolkit::util::Signal::Raise(SIGSEGV);

		tinyToolkit::util::Signal::Raise(SIGINT);
		tinyToolkit::util::Signal::Raise(SIGQUIT);
		tinyToolkit::util::Signal::Raise(SIGTERM);
		tinyToolkit::util::Signal::Raise(SIGTSTP);

	#endif
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void String()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::string content = tinyToolkit::util::String::Trim(" 123 456 --- abc %%% 22112121212324343 ");

		tinyToolkit::util::String::Lower(content);
		tinyToolkit::util::String::Upper(content);
		tinyToolkit::util::String::Erase(content, 'a');
		tinyToolkit::util::String::Erase(content, "123 ");
		tinyToolkit::util::String::Replace(content, "456", "ttt");
		tinyToolkit::util::String::ReplaceLoop(content, "12", "21");

		std::cout << "content       : " << content << std::endl;
		std::cout << "EndWith       : " << tinyToolkit::util::String::EndWith(content, "ttt") << std::endl;
		std::cout << "StartWith     : " << tinyToolkit::util::String::StartWith(content, "ttt") << std::endl;
		std::cout << "Join          : " << tinyToolkit::util::String::Join("123", 456, "789", 0.33) << std::endl;
		std::cout << "Format        : " << tinyToolkit::util::String::Format("char {}", 456) << std::endl;
		std::cout << "Format        : " << tinyToolkit::util::String::Format(std::string("string {}"), 789) << std::endl;
		std::cout << "FilterNote    : " << tinyToolkit::util::String::FilterNote("123 //66666") << std::endl;
		std::cout << "AsHexString   : " << tinyToolkit::util::String::AsHexString("123") << std::endl;
		std::cout << "AsHexString   : " << tinyToolkit::util::String::AsHexString(reinterpret_cast<const uint8_t *>("123")) << std::endl;
		std::cout << "AsHexString   : " << tinyToolkit::util::String::AsHexString(std::string("123")) << std::endl;
		std::cout << "FromHexString : " << tinyToolkit::util::String::FromHexString("343536") << std::endl;
		std::cout << "FromHexString : " << tinyToolkit::util::String::FromHexString(reinterpret_cast<const uint8_t *>("343536")) << std::endl;
		std::cout << "FromHexString : " << tinyToolkit::util::String::FromHexString(std::string("343536")) << std::endl;

		{
			std::cout << "---------- Json ----------" << std::endl;

			std::string json = R"({"key_1":"value_1", "key_2":"value_2"})";

			std::cout << "[ReduceJson]" << std::endl;
			std::cout << tinyToolkit::util::String::ReduceJson(json) << std::endl;

			std::cout << "[BeautifyJson]" << std::endl;
			std::cout << tinyToolkit::util::String::BeautifyJson(json) << std::endl;
		}

		{
			std::cout << "---------- Split ----------" << std::endl;

			for (auto && iter : tinyToolkit::util::String::Split(content, " "))
			{
				std::cout << iter << std::endl;
			}
		}

		tinyToolkit::util::String::Replace(content, " ", LINE_EOL);

		{
			std::cout << "---------- SplitLines ----------" << std::endl;

			for (auto && iter : tinyToolkit::util::String::SplitLines(content))
			{
				std::cout << iter << std::endl;
			}
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void System()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::cout << "ProcessorCount : " << tinyToolkit::util::System::ProcessorCount() << std::endl;
		std::cout << "UserName       : " << tinyToolkit::util::System::UserName() << std::endl;
		std::cout << "ComputerName   : " << tinyToolkit::util::System::ComputerName() << std::endl;
		std::cout << "IsBigEndian    : " << tinyToolkit::util::System::IsBigEndian() << std::endl;
		std::cout << "IsLittleEndian : " << tinyToolkit::util::System::IsLittleEndian() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Singleton()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		class A
		{
		public:
			explicit A(std::size_t number) : _number(number)
			{
				(void)_number;
			}

		private:
			std::size_t _number{ 0 };
		};

		std::thread t1([]()
		{
			std::cout << "[Thread 1] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(1)) << std::endl;
			std::cout << "[Thread 1] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(2)) << std::endl;
			std::cout << "[Thread 1] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(3)) << std::endl;
		});

		std::thread t2([]()
		{
			std::cout << "[Thread 2] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(1)) << std::endl;
			std::cout << "[Thread 2] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(2)) << std::endl;
			std::cout << "[Thread 2] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(3)) << std::endl;
		});

		std::thread t3([]()
		{
			std::cout << "[Thread 3] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(1)) << std::endl;
			std::cout << "[Thread 3] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(2)) << std::endl;
			std::cout << "[Thread 3] Singleton Address : " << std::addressof(tinyToolkit::util::Singleton<A>::Instance(3)) << std::endl;
		});

		t1.join();
		t2.join();
		t3.join();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Filesystem()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::cout << "CurrentDirectory        : " << tinyToolkit::util::Filesystem::CurrentDirectory() << std::endl;

		std::cout << "a CreateDirectory       : " << tinyToolkit::util::Filesystem::CreateDirectory("a") << std::endl;
		std::cout << "b CreateDirectory       : " << tinyToolkit::util::Filesystem::CreateDirectory("b") << std::endl;

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::cout << "a CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("a\\1\\2\\3") << std::endl;
		std::cout << "b CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("b\\4\\5\\6") << std::endl;

	#else

		std::cout << "a CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("a/1/2/3") << std::endl;
		std::cout << "b CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("b/4/5/6") << std::endl;

	#endif

		std::cout << "a IsDirectory           : " << tinyToolkit::util::Filesystem::IsDirectory("a") << std::endl;
		std::cout << "b IsDirectory           : " << tinyToolkit::util::Filesystem::IsDirectory("b") << std::endl;
		std::cout << "c IsDirectory           : " << tinyToolkit::util::Filesystem::IsDirectory("c") << std::endl;

		std::cout << "a Remove                : " << tinyToolkit::util::Filesystem::Remove("a") << std::endl;
		std::cout << "b Remove                : " << tinyToolkit::util::Filesystem::Remove("b") << std::endl;
		std::cout << "c Remove                : " << tinyToolkit::util::Filesystem::Remove("c") << std::endl;

		std::cout << "123.txt CreateFile      : " << tinyToolkit::util::Filesystem::CreateFile("123.txt") << std::endl;
		std::cout << "456.txt CreateFile      : " << tinyToolkit::util::Filesystem::CreateFile("456.txt") << std::endl;

		std::cout << "123.txt WriteFile       : " << tinyToolkit::util::Filesystem::WriteFile("123.txt", "hello") << std::endl;
		std::cout << "456.txt WriteFile       : " << tinyToolkit::util::Filesystem::WriteFile("456.txt", "world") << std::endl;

		std::cout << "123.txt Size            : " << tinyToolkit::util::Filesystem::Size("123.txt") << std::endl;
		std::cout << "456.txt Size            : " << tinyToolkit::util::Filesystem::Size("456.txt") << std::endl;
		std::cout << "789.txt Size            : " << tinyToolkit::util::Filesystem::Size("789.txt") << std::endl;

		std::cout << "123.txt Name            : " << tinyToolkit::util::Filesystem::Name("123.txt") << std::endl;
		std::cout << "456.txt Name            : " << tinyToolkit::util::Filesystem::Name("456.txt") << std::endl;
		std::cout << "789.txt Name            : " << tinyToolkit::util::Filesystem::Name("789.txt") << std::endl;

		std::cout << "123.txt Steam           : " << tinyToolkit::util::Filesystem::Steam("123.txt") << std::endl;
		std::cout << "456.txt Steam           : " << tinyToolkit::util::Filesystem::Steam("456.txt") << std::endl;
		std::cout << "789.txt Steam           : " << tinyToolkit::util::Filesystem::Steam("789.txt") << std::endl;

		std::cout << "123.txt Extension       : " << tinyToolkit::util::Filesystem::Extension("123.txt") << std::endl;
		std::cout << "456.txt Extension       : " << tinyToolkit::util::Filesystem::Extension("456.txt") << std::endl;
		std::cout << "789.txt Extension       : " << tinyToolkit::util::Filesystem::Extension("789.txt") << std::endl;

		std::cout << "123.txt Exists          : " << tinyToolkit::util::Filesystem::Exists("123.txt") << std::endl;
		std::cout << "456.txt Exists          : " << tinyToolkit::util::Filesystem::Exists("456.txt") << std::endl;
		std::cout << "789.txt Exists          : " << tinyToolkit::util::Filesystem::Exists("789.txt") << std::endl;

		std::cout << "123.txt Content         : " << tinyToolkit::util::Filesystem::Content("123.txt") << std::endl;
		std::cout << "456.txt Content         : " << tinyToolkit::util::Filesystem::Content("456.txt") << std::endl;
		std::cout << "789.txt Content         : " << tinyToolkit::util::Filesystem::Content("789.txt") << std::endl;

		std::cout << "123.txt LastTime        : " << tinyToolkit::util::Filesystem::LastTime("123.txt") << std::endl;
		std::cout << "456.txt LastTime        : " << tinyToolkit::util::Filesystem::LastTime("456.txt") << std::endl;
		std::cout << "789.txt LastTime        : " << tinyToolkit::util::Filesystem::LastTime("789.txt") << std::endl;

		std::cout << "123.txt Canonical       : " << tinyToolkit::util::Filesystem::Canonical("123.txt") << std::endl;
		std::cout << "456.txt Canonical       : " << tinyToolkit::util::Filesystem::Canonical("456.txt") << std::endl;
		std::cout << "789.txt Canonical       : " << tinyToolkit::util::Filesystem::Canonical("789.txt") << std::endl;

		std::cout << "123.txt ParentDirectory : " << tinyToolkit::util::Filesystem::ParentDirectory("123.txt") << std::endl;
		std::cout << "456.txt ParentDirectory : " << tinyToolkit::util::Filesystem::ParentDirectory("456.txt") << std::endl;
		std::cout << "789.txt ParentDirectory : " << tinyToolkit::util::Filesystem::ParentDirectory("789.txt") << std::endl;

		std::cout << "123.txt Remove          : " << tinyToolkit::util::Filesystem::Remove("123.txt") << std::endl;
		std::cout << "456.txt Remove          : " << tinyToolkit::util::Filesystem::Remove("456.txt") << std::endl;
		std::cout << "789.txt Remove          : " << tinyToolkit::util::Filesystem::Remove("789.txt") << std::endl;

		std::cout << "123.txt CreateFile      : " << tinyToolkit::util::Filesystem::CreateFile("123.txt") << std::endl;
		std::cout << "456.txt CreateFile      : " << tinyToolkit::util::Filesystem::CreateFile("456.txt") << std::endl;
		std::cout << "789.txt CreateFile      : " << tinyToolkit::util::Filesystem::CreateFile("789.txt") << std::endl;

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::cout << "a CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("a\\1\\2\\3") << std::endl;
		std::cout << "b CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("b\\4\\5\\6") << std::endl;
		std::cout << "c CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("c\\7\\8\\9") << std::endl;

	#else

		std::cout << "a CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("a/1/2/3") << std::endl;
		std::cout << "b CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("b/4/5/6") << std::endl;
		std::cout << "c CreateDirectories     : " << tinyToolkit::util::Filesystem::CreateDirectories("c/7/8/9") << std::endl;

	#endif

		std::cout << "123.txt WriteFile       : " << tinyToolkit::util::Filesystem::WriteFile("123.txt", std::string("hello") + LINE_EOL + "world") << std::endl;
		std::cout << "456.txt WriteFile       : " << tinyToolkit::util::Filesystem::WriteFile("456.txt", std::string("fucks") + LINE_EOL + "yours") << std::endl;
		std::cout << "789.txt WriteFile       : " << tinyToolkit::util::Filesystem::WriteFile("789.txt", std::string("tests") + LINE_EOL + "ticks") << std::endl;

		std::cout << "123.txt Rename          : " << tinyToolkit::util::Filesystem::Rename("123.txt", "321.txt") << std::endl;
		std::cout << "456.txt Rename          : " << tinyToolkit::util::Filesystem::Rename("456.txt", "654.txt") << std::endl;
		std::cout << "789.txt Rename          : " << tinyToolkit::util::Filesystem::Rename("789.txt", "987.txt") << std::endl;

		{
			tinyToolkit::util::Filesystem::CreateFile("321.txt");
			tinyToolkit::util::Filesystem::CreateFile("654.txt");
			tinyToolkit::util::Filesystem::CreateFile("987.txt");

			{
				std::cout << "---------- TraverseFile ----------" << std::endl;

				for (auto && file : tinyToolkit::util::Filesystem::TraverseFile("."))
				{
					std::cout << "[" << file << "]" << std::endl;
				}
			}

			tinyToolkit::util::Filesystem::Remove("321.txt");
			tinyToolkit::util::Filesystem::Remove("654.txt");
			tinyToolkit::util::Filesystem::Remove("987.txt");

			{
				std::cout << "---------- TraverseFile ----------" << std::endl;

				for (auto && file : tinyToolkit::util::Filesystem::TraverseFile("."))
				{
					std::cout << "[" << file << "]" << std::endl;
				}
			}

			tinyToolkit::util::Filesystem::CreateFile("321.txt");
			tinyToolkit::util::Filesystem::CreateFile("654.txt");
			tinyToolkit::util::Filesystem::CreateFile("987.txt");

			{
				std::cout << "---------- TraverseRegexFile ----------" << std::endl;

				for (auto && file : tinyToolkit::util::Filesystem::TraverseFile(".", std::regex(".*.txt")))
				{
					std::cout << "[" << file << "]" << std::endl;

					for (auto && line : tinyToolkit::util::Filesystem::ReadFile(file))
					{
						std::cout << line << std::endl;
					}
				}
			}

			tinyToolkit::util::Filesystem::Remove("321.txt");
			tinyToolkit::util::Filesystem::Remove("654.txt");
			tinyToolkit::util::Filesystem::Remove("987.txt");

			{
				std::cout << "---------- TraverseRegexFile ----------" << std::endl;

				for (auto && file : tinyToolkit::util::Filesystem::TraverseFile(".", std::regex(".*.txt")))
				{
					std::cout << "[" << file << "]" << std::endl;

					for (auto && line : tinyToolkit::util::Filesystem::ReadFile(file))
					{
						std::cout << line << std::endl;
					}
				}
			}
		}

		{

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			tinyToolkit::util::Filesystem::CreateDirectories("a\\1\\2\\3");
			tinyToolkit::util::Filesystem::CreateDirectories("b\\4\\5\\6");
			tinyToolkit::util::Filesystem::CreateDirectories("c\\7\\8\\9");

		#else

			tinyToolkit::util::Filesystem::CreateDirectories("a/1/2/3");
			tinyToolkit::util::Filesystem::CreateDirectories("b/4/5/6");
			tinyToolkit::util::Filesystem::CreateDirectories("c/7/8/9");

		#endif

			{
				std::cout << "---------- TraverseDirectory ----------" << std::endl;

				for (auto && directory : tinyToolkit::util::Filesystem::TraverseDirectory(".", true))
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}

			tinyToolkit::util::Filesystem::Remove("a");
			tinyToolkit::util::Filesystem::Remove("b");
			tinyToolkit::util::Filesystem::Remove("c");

			{
				std::cout << "---------- TraverseDirectory ----------" << std::endl;

				for (auto && directory : tinyToolkit::util::Filesystem::TraverseDirectory(".", true))
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			tinyToolkit::util::Filesystem::CreateDirectories("a\\1\\2\\3");
			tinyToolkit::util::Filesystem::CreateDirectories("b\\4\\5\\6");
			tinyToolkit::util::Filesystem::CreateDirectories("c\\7\\8\\9");

		#else

			tinyToolkit::util::Filesystem::CreateDirectories("a/1/2/3");
			tinyToolkit::util::Filesystem::CreateDirectories("b/4/5/6");
			tinyToolkit::util::Filesystem::CreateDirectories("c/7/8/9");

		#endif

			{
				std::cout << "---------- TraverseRegexDirectory ----------" << std::endl;

				for (auto && directory : tinyToolkit::util::Filesystem::TraverseDirectory(".", std::regex(".*[a|b|c]+"), true))
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}

			tinyToolkit::util::Filesystem::Remove("a");
			tinyToolkit::util::Filesystem::Remove("b");
			tinyToolkit::util::Filesystem::Remove("c");

			{
				std::cout << "---------- TraverseRegexDirectory ----------" << std::endl;

				for (auto && directory : tinyToolkit::util::Filesystem::TraverseDirectory(".", std::regex(".*[a|b|c]+"), true))
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}
		}
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Application()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::cout << "Path         : " << tinyToolkit::util::Application::Path() << std::endl;
		std::cout << "Name         : " << tinyToolkit::util::Application::Name() << std::endl;
		std::cout << "Exist        : " << tinyToolkit::util::Application::Exist(tinyToolkit::util::Application::Name()) << std::endl;
		std::cout << "ThreadID     : " << tinyToolkit::util::Application::ThreadID() << std::endl;
		std::cout << "ProcessID    : " << tinyToolkit::util::Application::ProcessID() << std::endl;
		std::cout << "CompileTime  : " << tinyToolkit::util::Application::CompileTime() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char const * argv[])
{
	(void)argc;
	(void)argv;

	std::cout << std::boolalpha;

	Math();
	Time();
	Latch();
	Regex();
	Signal();
	String();
	System();
	Singleton();
	Filesystem();
	Application();

	return 0;
}
