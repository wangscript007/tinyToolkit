/**
 *
 *  作者: hm
 *
 *  说明: 主函数
 *
 */


#include "main.h"


static void TaskPool()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		tinyToolkit::pool::TaskPool pool{ };

		pool.AddTask([](){ std::cout << "task1 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(1)); });
		pool.AddTask([](){ std::cout << "task2 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(2)); });
		pool.AddTask([](){ std::cout << "task3 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(3)); });
		pool.AddTask([](){ std::cout << "task4 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(4)); });
		pool.AddTask([](){ std::cout << "task5 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(5)); });
		pool.AddTask([](){ std::cout << "task6 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(6)); });
		pool.AddTask([](){ std::cout << "task7 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(7)); });
		pool.AddTask([](){ std::cout << "task8 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(8)); });
		pool.AddTask([](){ std::cout << "task9 [" << std::this_thread::get_id() << "]" << std::endl; std::this_thread::sleep_for(std::chrono::milliseconds(9)); });

		pool.Pause();

		std::this_thread::sleep_for(std::chrono::seconds(2));

		pool.Resume();

		pool.Wait();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void ObjectPool()
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
			explicit A(const char * name) : _name(name)
			{
				std::cout << "constructor : " << _name << std::endl;
			}

			~A()
			{
				std::cout << "destructor : " << _name << std::endl;
			}

			void Print()
			{
				std::cout << "Print : " << _name << std::endl;
			}

		protected:
			std::string _name;
		};

		tinyToolkit::pool::ObjectPool<A> pool{ };

		auto t1 = pool.Borrow("t1");
		auto t2 = pool.Borrow("t2");

		t1->Print();
		t2->Print();

		pool.Return(t1);
		pool.Return(t2);
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

	TaskPool();
	ObjectPool();

	return 0;
}
