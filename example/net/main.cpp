/**
 *
 *  作者: hm
 *
 *  说明: 主函数
 *
 */


#include "main.h"


static void TCP()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{
		static uint32_t ClientSend = 0;
		static uint32_t ServerSend = 0;
		static uint32_t TotalCount = 10;

		class Client
		{
		public:
			explicit Client(net::EventLoop * eventLoop) : _client(eventLoop)
			{
				_client.SetSendCallback(OnSend);
				_client.SetErrorCallback(OnError);
				_client.SetCloseCallback(OnClose);
				_client.SetConnectCallback(OnConnect);
				_client.SetReceiveCallback(OnReceive);
			}

			void Connect(const net::Endpoint & endpoint)
			{
				_client.Connect(endpoint);
			}

		private:
			static void OnSend(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] send "
				          << session->CurrentSendBytes()
				          << " bytes message to   ["
				          << session->PeerEndpoint().AsString()
				          << "]"
				          << std::endl;
			}

			static void OnError(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] error"
				          << std::endl;
			}

			static void OnClose(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] close ["
				          << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] failed" : "] success")
				          << std::endl;
			}

			static void OnConnect(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] connect ["
				          << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] success" : "] failed")
				          << std::endl;
			}

			static void OnReceive(const std::shared_ptr<net::TCPSession> & session, net::Buffer * buffer)
			{
				auto byte = buffer->ReadableBytes();

				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] recv "
				          << byte
				          << " bytes message from ["
				          << session->PeerEndpoint().AsString()
				          << "] "
				          << buffer->ReadString(buffer->ReadableBytes())
				          << std::endl;

				if (++ClientSend == TotalCount)
				{
					session->Shutdown();
				}
				else
				{
					session->Send("Hello TCP Server", 16);
				}
			}

		private:
			net::TCPClient _client;
		};

		class Server
		{
		public:
			explicit Server(net::EventLoop * eventLoop) : _server(eventLoop)
			{
				_server.SetSendCallback(OnSend);
				_server.SetErrorCallback(OnError);
				_server.SetCloseCallback(OnClose);
				_server.SetAcceptCallback(OnAccept);
				_server.SetReceiveCallback(OnReceive);
			}

			void Listen(const net::Endpoint & endpoint)
			{
				_server.Listen(endpoint);
			}

		private:
			static void OnSend(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] send "
				          << session->CurrentSendBytes()
				          << " bytes message to   ["
				          << session->PeerEndpoint().AsString()
				          << "]"
				          << std::endl;
			}

			static void OnError(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] error"
				          << std::endl;
			}

			static void OnClose(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "[" << session->LocalEndpoint().AsString()
				          << "] close ["
				          << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] failed" : "] success")
				          << std::endl;
			}

			static void OnAccept(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] accept [" << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] success" : "] failed")
				          << std::endl;

				if (session->IsConnect())
				{
					session->Send("Hello TCP Client", 16);
				}
			}

			static void OnReceive(const std::shared_ptr<net::TCPSession> & session, net::Buffer * buffer)
			{
				auto byte = buffer->ReadableBytes();

				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] recv "
				          << byte
				          << " bytes message from ["
				          << session->PeerEndpoint().AsString()
				          << "] "
				          << buffer->ReadString(buffer->ReadableBytes())
				          << std::endl;

				if (++ServerSend == TotalCount)
				{
					session->Shutdown();
				}
				else
				{
					session->Send("Hello TCP Client", 16);
				}
			}

		private:
			net::TCPServer _server;
		};

		net::EventLoop eventLoop{ };

		Server server(&eventLoop);

		server.Listen(net::Endpoint("127.0.0.1", 10080));

		Client client(&eventLoop);

		client.Connect(net::Endpoint("127.0.0.1", 10080));

		eventLoop.Loop();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}


static void UDP()
{
	std::cout << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "Ready run function [" << CURRENT_FUNC << "]" << std::endl;
	std::cout << std::endl;

	try
	{

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

	TCP();
	UDP();

	return 0;
}
