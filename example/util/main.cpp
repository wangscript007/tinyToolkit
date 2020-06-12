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
		std::cout << "IsOdd  : " << util::Math::IsOdd(123) << std::endl;
		std::cout << "IsOdd  : " << util::Math::IsOdd(456) << std::endl;

		std::cout << "IsEven : " << util::Math::IsEven(123) << std::endl;
		std::cout << "IsEven : " << util::Math::IsEven(456) << std::endl;
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
		std::time_t time1 = 1234509876;

		struct timeval time2{ };
		struct timespec time3{ };

		time2.tv_sec = 1234567890;
		time2.tv_usec = 0;

		time3.tv_sec = 2345678901;
		time3.tv_nsec = 0;

		std::cout << "Timezone        : " << util::Time::Timezone() << std::endl;
		std::cout << "Hours           : " << util::Time::Hours() << std::endl;
		std::cout << "Minutes         : " << util::Time::Minutes() << std::endl;
		std::cout << "Seconds         : " << util::Time::Seconds() << std::endl;
		std::cout << "Milliseconds    : " << util::Time::Milliseconds() << std::endl;
		std::cout << "Microseconds    : " << util::Time::Microseconds() << std::endl;
		std::cout << "Nanoseconds     : " << util::Time::Nanoseconds() << std::endl;
		std::cout << "OffsetTime      : " << util::Time::OffsetTime(10, 1, 50, 30) << std::endl;
		std::cout << "OffsetTime      : " << util::Time::OffsetTime(-2, 1, 50, 30) << std::endl;
		std::cout << "Format          : " << util::Time::Format(util::Time::Seconds(), 0) << std::endl;
		std::cout << "Format          : " << util::Time::Format(util::Time::Seconds(), 8, "%4d_%02d_%02d_%02d_%02d_%02d") << std::endl;
		std::cout << "FromString      : " << util::Time::FromString("1970-01-01 08:00:00") << std::endl;
		std::cout << "UTCTimeString   : " << util::Time::UTCTimeString() << std::endl;
		std::cout << "UTCTimeString   : " << util::Time::UTCTimeString("%4d_%02d_%02d_%02d_%02d_%02d") << std::endl;
		std::cout << "LocalTimeString : " << util::Time::LocalTimeString() << std::endl;
		std::cout << "LocalTimeString : " << util::Time::LocalTimeString("%4d_%02d_%02d_%02d_%02d_%02d") << std::endl;
		std::cout << "TimePoint       : " << util::Time::TimePoint().time_since_epoch().count() << std::endl;
		std::cout << "TimePoint       : " << util::Time::TimePoint(time1).time_since_epoch().count() << std::endl;
		std::cout << "TimePoint       : " << util::Time::TimePoint(time2).time_since_epoch().count() << std::endl;
		std::cout << "TimePoint       : " << util::Time::TimePoint(time3).time_since_epoch().count() << std::endl;
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
		util::Signal::RegisterIgnore();

		util::Signal::RegisterTerminate([](int signalNo){ std::cout << "Terminate : " << signalNo << std::endl; });
		util::Signal::RegisterException([](int signalNo){ std::cout << "Exception : " << signalNo << std::endl; });

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		util::Signal::Raise(SIGILL);
		util::Signal::Raise(SIGFPE);
		util::Signal::Raise(SIGABRT);
		util::Signal::Raise(SIGSEGV);

		util::Signal::Raise(SIGINT);
		util::Signal::Raise(SIGTERM);
		util::Signal::Raise(SIGBREAK);

	#else

		util::Signal::Raise(SIGHUP);
		util::Signal::Raise(SIGPIPE);
		util::Signal::Raise(SIGCHLD);

		util::Signal::Raise(SIGILL);
		util::Signal::Raise(SIGFPE);
		util::Signal::Raise(SIGABRT);
		util::Signal::Raise(SIGSEGV);

		util::Signal::Raise(SIGINT);
		util::Signal::Raise(SIGQUIT);
		util::Signal::Raise(SIGTERM);
		util::Signal::Raise(SIGTSTP);

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
		std::string content = util::String::Trim(" 123 456 --- abc %%% 22112121212324343 ");

		util::String::Lower(content);
		util::String::Upper(content);
		util::String::Erase(content, 'a');
		util::String::Erase(content, "123 ");
		util::String::Replace(content, "456", "ttt");
		util::String::ReplaceLoop(content, "12", "21");

		std::cout << "content       : " << content << std::endl;
		std::cout << "EndWith       : " << util::String::EndWith(content, "ttt") << std::endl;
		std::cout << "StartWith     : " << util::String::StartWith(content, "ttt") << std::endl;
		std::cout << "Join          : " << util::String::Join("123", 456, "789", 0.33) << std::endl;
		std::cout << "Format        : " << util::String::Format("char {}", 456) << std::endl;
		std::cout << "Format        : " << util::String::Format(std::string("string {}"), 789) << std::endl;
		std::cout << "FilterNote    : " << util::String::FilterNote("123 //66666") << std::endl;
		std::cout << "AsHexString   : " << util::String::AsHexString("123") << std::endl;
		std::cout << "AsHexString   : " << util::String::AsHexString(reinterpret_cast<const uint8_t *>("123")) << std::endl;
		std::cout << "AsHexString   : " << util::String::AsHexString(std::string("123")) << std::endl;
		std::cout << "FromHexString : " << util::String::FromHexString("343536") << std::endl;
		std::cout << "FromHexString : " << util::String::FromHexString(reinterpret_cast<const uint8_t *>("343536")) << std::endl;
		std::cout << "FromHexString : " << util::String::FromHexString(std::string("343536")) << std::endl;

		{
			std::cout << "---------- Json ----------" << std::endl;

			std::string json = R"({"key_1":"value_1", "key_2":"value_2"})";

			std::cout << "[ReduceJson]" << std::endl;
			std::cout << util::String::ReduceJson(json) << std::endl;

			std::cout << "[BeautifyJson]" << std::endl;
			std::cout << util::String::BeautifyJson(json) << std::endl;
		}

		{
			std::cout << "---------- Split ----------" << std::endl;

			std::vector<std::string> result{ };

			util::String::Split(content, " ", result);

			for (auto &iter : result)
			{
				std::cout << iter << std::endl;
			}
		}

		util::String::Replace(content, " ", LINE_EOL);

		{
			std::cout << "---------- SplitLines ----------" << std::endl;

			std::vector<std::string> result{ };

			util::String::SplitLines(content, result);

			for (auto &iter : result)
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
		std::cout << "ProcessorCount : " << util::System::ProcessorCount() << std::endl;
		std::cout << "UserName       : " << util::System::UserName() << std::endl;
		std::cout << "ComputerName   : " << util::System::ComputerName() << std::endl;
		std::cout << "IsBigEndian    : " << util::System::IsBigEndian() << std::endl;
		std::cout << "IsLittleEndian : " << util::System::IsLittleEndian() << std::endl;
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
			explicit A(std::string name) : _name(std::move(name))
			{

			}

		private:
			std::string _name{ };
		};

		std::cout << "Address : " << std::addressof(util::Singleton<A>::Instance("A")) << std::endl;
		std::cout << "Address : "  << std::addressof(util::Singleton<A>::Instance("B")) << std::endl;
		std::cout << "Address : "  << std::addressof(util::Singleton<A>::Instance("C")) << std::endl;
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
		std::cout << "CurrentDirectory        : " << util::Filesystem::CurrentDirectory() << std::endl;

		std::cout << "a CreateDirectory       : " << util::Filesystem::CreateDirectory("a") << std::endl;
		std::cout << "b CreateDirectory       : " << util::Filesystem::CreateDirectory("b") << std::endl;

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::cout << "a CreateDirectories     : " << util::Filesystem::CreateDirectories("a\\1\\2\\3") << std::endl;
		std::cout << "b CreateDirectories     : " << util::Filesystem::CreateDirectories("b\\4\\5\\6") << std::endl;

	#else

		std::cout << "a CreateDirectories     : " << util::Filesystem::CreateDirectories("a/1/2/3") << std::endl;
		std::cout << "b CreateDirectories     : " << util::Filesystem::CreateDirectories("b/4/5/6") << std::endl;

	#endif

		std::cout << "a IsDirectory           : " << util::Filesystem::IsDirectory("a") << std::endl;
		std::cout << "b IsDirectory           : " << util::Filesystem::IsDirectory("b") << std::endl;
		std::cout << "c IsDirectory           : " << util::Filesystem::IsDirectory("c") << std::endl;

		std::cout << "a Remove                : " << util::Filesystem::Remove("a") << std::endl;
		std::cout << "b Remove                : " << util::Filesystem::Remove("b") << std::endl;
		std::cout << "c Remove                : " << util::Filesystem::Remove("c") << std::endl;

		std::cout << "123.txt CreateFile      : " << util::Filesystem::CreateFile("123.txt") << std::endl;
		std::cout << "456.txt CreateFile      : " << util::Filesystem::CreateFile("456.txt") << std::endl;

		std::cout << "123.txt WriteFile       : " << util::Filesystem::WriteFile("123.txt", "hello") << std::endl;
		std::cout << "456.txt WriteFile       : " << util::Filesystem::WriteFile("456.txt", "world") << std::endl;

		std::cout << "123.txt Size            : " << util::Filesystem::Size("123.txt") << std::endl;
		std::cout << "456.txt Size            : " << util::Filesystem::Size("456.txt") << std::endl;
		std::cout << "789.txt Size            : " << util::Filesystem::Size("789.txt") << std::endl;

		std::cout << "123.txt Name            : " << util::Filesystem::Name("123.txt") << std::endl;
		std::cout << "456.txt Name            : " << util::Filesystem::Name("456.txt") << std::endl;
		std::cout << "789.txt Name            : " << util::Filesystem::Name("789.txt") << std::endl;

		std::cout << "123.txt Steam           : " << util::Filesystem::Steam("123.txt") << std::endl;
		std::cout << "456.txt Steam           : " << util::Filesystem::Steam("456.txt") << std::endl;
		std::cout << "789.txt Steam           : " << util::Filesystem::Steam("789.txt") << std::endl;

		std::cout << "123.txt Extension       : " << util::Filesystem::Extension("123.txt") << std::endl;
		std::cout << "456.txt Extension       : " << util::Filesystem::Extension("456.txt") << std::endl;
		std::cout << "789.txt Extension       : " << util::Filesystem::Extension("789.txt") << std::endl;

		std::cout << "123.txt Exists          : " << util::Filesystem::Exists("123.txt") << std::endl;
		std::cout << "456.txt Exists          : " << util::Filesystem::Exists("456.txt") << std::endl;
		std::cout << "789.txt Exists          : " << util::Filesystem::Exists("789.txt") << std::endl;

		std::cout << "123.txt Content         : " << util::Filesystem::Content("123.txt") << std::endl;
		std::cout << "456.txt Content         : " << util::Filesystem::Content("456.txt") << std::endl;
		std::cout << "789.txt Content         : " << util::Filesystem::Content("789.txt") << std::endl;

		std::cout << "123.txt LastTime        : " << util::Filesystem::LastTime("123.txt") << std::endl;
		std::cout << "456.txt LastTime        : " << util::Filesystem::LastTime("456.txt") << std::endl;
		std::cout << "789.txt LastTime        : " << util::Filesystem::LastTime("789.txt") << std::endl;

		std::cout << "123.txt Canonical       : " << util::Filesystem::Canonical("123.txt") << std::endl;
		std::cout << "456.txt Canonical       : " << util::Filesystem::Canonical("456.txt") << std::endl;
		std::cout << "789.txt Canonical       : " << util::Filesystem::Canonical("789.txt") << std::endl;

		std::cout << "123.txt ParentDirectory : " << util::Filesystem::ParentDirectory("123.txt") << std::endl;
		std::cout << "456.txt ParentDirectory : " << util::Filesystem::ParentDirectory("456.txt") << std::endl;
		std::cout << "789.txt ParentDirectory : " << util::Filesystem::ParentDirectory("789.txt") << std::endl;

		std::cout << "123.txt Remove          : " << util::Filesystem::Remove("123.txt") << std::endl;
		std::cout << "456.txt Remove          : " << util::Filesystem::Remove("456.txt") << std::endl;
		std::cout << "789.txt Remove          : " << util::Filesystem::Remove("789.txt") << std::endl;

		std::cout << "123.txt CreateFile      : " << util::Filesystem::CreateFile("123.txt") << std::endl;
		std::cout << "456.txt CreateFile      : " << util::Filesystem::CreateFile("456.txt") << std::endl;
		std::cout << "789.txt CreateFile      : " << util::Filesystem::CreateFile("789.txt") << std::endl;

	#if PLATFORM_TYPE == PLATFORM_WINDOWS

		std::cout << "a CreateDirectories     : " << util::Filesystem::CreateDirectories("a\\1\\2\\3") << std::endl;
		std::cout << "b CreateDirectories     : " << util::Filesystem::CreateDirectories("b\\4\\5\\6") << std::endl;
		std::cout << "c CreateDirectories     : " << util::Filesystem::CreateDirectories("c\\7\\8\\9") << std::endl;

	#else

		std::cout << "a CreateDirectories     : " << util::Filesystem::CreateDirectories("a/1/2/3") << std::endl;
		std::cout << "b CreateDirectories     : " << util::Filesystem::CreateDirectories("b/4/5/6") << std::endl;
		std::cout << "c CreateDirectories     : " << util::Filesystem::CreateDirectories("c/7/8/9") << std::endl;

	#endif

		std::cout << "123.txt WriteFile       : " << util::Filesystem::WriteFile("123.txt", std::string("hello") + LINE_EOL + "world") << std::endl;
		std::cout << "456.txt WriteFile       : " << util::Filesystem::WriteFile("456.txt", std::string("fucks") + LINE_EOL + "yours") << std::endl;
		std::cout << "789.txt WriteFile       : " << util::Filesystem::WriteFile("789.txt", std::string("tests") + LINE_EOL + "ticks") << std::endl;

		std::cout << "123.txt Rename          : " << util::Filesystem::Rename("123.txt", "321.txt") << std::endl;
		std::cout << "456.txt Rename          : " << util::Filesystem::Rename("456.txt", "654.txt") << std::endl;
		std::cout << "789.txt Rename          : " << util::Filesystem::Rename("789.txt", "987.txt") << std::endl;

		{
			util::Filesystem::CreateFile("321.txt");
			util::Filesystem::CreateFile("654.txt");
			util::Filesystem::CreateFile("987.txt");

			{
				std::cout << "---------- TraverseFile ----------" << std::endl;

				std::vector<std::string> files{ };

				util::Filesystem::TraverseFile(".", files);

				for (auto &file : files)
				{
					std::cout << "[" << file << "]" << std::endl;
				}
			}

			util::Filesystem::Remove("321.txt");
			util::Filesystem::Remove("654.txt");
			util::Filesystem::Remove("987.txt");

			{
				std::cout << "---------- TraverseFile ----------" << std::endl;

				std::vector<std::string> files{ };

				util::Filesystem::TraverseFile(".", files);

				for (auto &file : files)
				{
					std::cout << "[" << file << "]" << std::endl;
				}
			}

			util::Filesystem::CreateFile("321.txt");
			util::Filesystem::CreateFile("654.txt");
			util::Filesystem::CreateFile("987.txt");

			{
				std::cout << "---------- TraverseRegexFile ----------" << std::endl;

				std::vector<std::string> files{ };

				util::Filesystem::TraverseFile(".", files, std::regex(".*.txt"));

				for (auto &file : files)
				{
					std::cout << "[" << file << "]" << std::endl;

					std::vector<std::string> lines{ };

					util::Filesystem::ReadFile(file, lines);

					for (auto &line : lines)
					{
						std::cout << line << std::endl;
					}
				}
			}

			util::Filesystem::Remove("321.txt");
			util::Filesystem::Remove("654.txt");
			util::Filesystem::Remove("987.txt");

			{
				std::cout << "---------- TraverseRegexFile ----------" << std::endl;

				std::vector<std::string> files{ };

				util::Filesystem::TraverseFile(".", files, std::regex(".*.txt"));

				for (auto &file : files)
				{
					std::cout << "[" << file << "]" << std::endl;

					std::vector<std::string> lines{ };

					util::Filesystem::ReadFile(file, lines);

					for (auto &line : lines)
					{
						std::cout << line << std::endl;
					}
				}
			}
		}

		{

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			util::Filesystem::CreateDirectories("a\\1\\2\\3");
			util::Filesystem::CreateDirectories("b\\4\\5\\6");
			util::Filesystem::CreateDirectories("c\\7\\8\\9");

		#else

			util::Filesystem::CreateDirectories("a/1/2/3");
			util::Filesystem::CreateDirectories("b/4/5/6");
			util::Filesystem::CreateDirectories("c/7/8/9");

		#endif

			{
				std::cout << "---------- TraverseDirectory ----------" << std::endl;

				std::vector<std::string> directories{ };

				util::Filesystem::TraverseDirectory(".", directories, true);

				for (auto &directory : directories)
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}

			util::Filesystem::Remove("a");
			util::Filesystem::Remove("b");
			util::Filesystem::Remove("c");

			{
				std::cout << "---------- TraverseDirectory ----------" << std::endl;

				std::vector<std::string> directories{ };

				util::Filesystem::TraverseDirectory(".", directories, true);

				for (auto &directory : directories)
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}

		#if PLATFORM_TYPE == PLATFORM_WINDOWS

			util::Filesystem::CreateDirectories("a\\1\\2\\3");
			util::Filesystem::CreateDirectories("b\\4\\5\\6");
			util::Filesystem::CreateDirectories("c\\7\\8\\9");

		#else

			util::Filesystem::CreateDirectories("a/1/2/3");
			util::Filesystem::CreateDirectories("b/4/5/6");
			util::Filesystem::CreateDirectories("c/7/8/9");

		#endif

			{
				std::cout << "---------- TraverseRegexDirectory ----------" << std::endl;

				std::vector<std::string> directories{ };

				util::Filesystem::TraverseDirectory(".", directories, std::regex(".*[a|b|c]+"), true);

				for (auto &directory : directories)
				{
					std::cout << "[" << directory << "]" << std::endl;
				}
			}

			util::Filesystem::Remove("a");
			util::Filesystem::Remove("b");
			util::Filesystem::Remove("c");

			{
				std::cout << "---------- TraverseRegexDirectory ----------" << std::endl;

				std::vector<std::string> directories{ };

				util::Filesystem::TraverseDirectory(".", directories, std::regex(".*[a|b|c]+"), true);

				for (auto &directory : directories)
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
		std::cout << "Path         : " << util::Application::Path() << std::endl;
		std::cout << "Name         : " << util::Application::Name() << std::endl;
		std::cout << "Exist        : " << util::Application::Exist(util::Application::Name()) << std::endl;
		std::cout << "ThreadID     : " << util::Application::ThreadID() << std::endl;
		std::cout << "ProcessID    : " << util::Application::ProcessID() << std::endl;
		std::cout << "CompileTime  : " << util::Application::CompileTime() << std::endl;
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
	Signal();
	String();
	System();
	Singleton();
	Filesystem();
	Application();

	return 0;
}
