/**
 *
 *  作者: hm
 *
 *  说明: 主函数
 *
 */


#include "main.h"


static void Any()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		tinyToolkit::container::Any any(1.01);

		std::cout << "type  : " << any.Type().name() << std::endl;
		std::cout << "value : " << any.Get<double>() << std::endl;

		any = 123;

		std::cout << "type  : " << any.Type().name() << std::endl;
		std::cout << "value : " << any.Get<int32_t>() << std::endl;

		any = "456";

		std::cout << "type  : " << any.Type().name() << std::endl;
		std::cout << "value : " << any.Get<const char * >() << std::endl;

		any.Clear();

		std::cout << "type  : " << any.Type().name() << std::endl;
		std::cout << "value : " << any.Get<const char * >() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Queue()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::string value{ };

		tinyToolkit::container::LockQueue<std::string> queue;

		queue.Push("123");
		queue.Push("456");
		queue.Push("789");

		std::cout << "***** push *****" << std::endl;
		std::cout << "size  : " << queue.Size() << std::endl;
		std::cout << "empty : " << queue.Empty() << std::endl;
		std::cout << "back  : " << queue.Back() << std::endl;
		std::cout << "front : " << queue.Front() << std::endl;

		queue.Pop();

		std::cout << "***** pop *****" << std::endl;
		std::cout << "size  : " << queue.Size() << std::endl;
		std::cout << "empty : " << queue.Empty() << std::endl;
		std::cout << "back  : " << queue.Back() << std::endl;
		std::cout << "front : " << queue.Front() << std::endl;

		queue.Pop(value);

		std::cout << "***** pop value *****" << std::endl;
		std::cout << "size  : " << queue.Size() << std::endl;
		std::cout << "empty : " << queue.Empty() << std::endl;
		std::cout << "back  : " << queue.Back() << std::endl;
		std::cout << "front : " << queue.Front() << std::endl;
		std::cout << "value : " << value << std::endl;
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

	Any();
	Queue();

	return 0;
}
