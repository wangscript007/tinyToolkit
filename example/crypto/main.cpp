/**
 *
 *  作者: hm
 *
 *  说明: 主函数
 *
 */


#include "main.h"


static void Url()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::string encode = crypto::Url::Encode("https://www.baidu.com/?p1=123&p2=uuid");
		std::string decode = crypto::Url::Decode(encode);

		std::cout << "encode : " << encode << std::endl;
		std::cout << "decode : " << decode << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void Base64()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		std::string encode = crypto::Base64::Encode("https://www.baidu.com/?p1=123&p2=uuid");
		std::string decode = crypto::Base64::Decode(encode);

		std::cout << "encode : " << encode << std::endl;
		std::cout << "decode : " << decode << std::endl;
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

	Url();
	Base64();

	return 0;
}
