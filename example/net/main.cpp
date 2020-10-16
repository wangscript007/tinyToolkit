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
		static int32_t totalCount = 10;

		class Client
		{
		public:
			explicit Client(net::EventLoop * eventLoop) : _client(eventLoop)
			{
				_client.SetSendCallback(std::bind(&Client::OnSend, this, std::placeholders::_1));
				_client.SetErrorCallback(std::bind(&Client::OnError, this, std::placeholders::_1));
				_client.SetCloseCallback(std::bind(&Client::OnClose, this, std::placeholders::_1));
				_client.SetConnectCallback(std::bind(&Client::OnConnect, this, std::placeholders::_1));
				_client.SetReceiveCallback(std::bind(&Client::OnReceive, this, std::placeholders::_1, std::placeholders::_2));
			}

			void Connect(const net::Endpoint & endpoint)
			{
				_client.Connect(endpoint);
			}

		private:
			void OnSend(const std::shared_ptr<net::TCPSession> & session)
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

			void OnError(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] error"
				          << std::endl;
			}

			void OnClose(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] close ["
				          << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] failed" : "] success")
				          << std::endl;
			}

			void OnConnect(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] connect ["
				          << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] success" : "] failed")
				          << std::endl;
			}

			void OnReceive(const std::shared_ptr<net::TCPSession> & session, net::Buffer * buffer)
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

				if (++_count == totalCount)
				{
					session->Shutdown();
				}
				else
				{
					session->Send("Hello TCP Server", 16);
				}
			}

		private:
			int32_t _count{ 0 };

			net::TCPClient _client;
		};

		class Server
		{
		public:
			explicit Server(net::EventLoop * eventLoop) : _server(eventLoop)
			{
				_server.SetSendCallback(std::bind(&Server::OnSend, this, std::placeholders::_1));
				_server.SetErrorCallback(std::bind(&Server::OnError, this, std::placeholders::_1));
				_server.SetCloseCallback(std::bind(&Server::OnClose, this, std::placeholders::_1));
				_server.SetAcceptCallback(std::bind(&Server::OnAccept, this, std::placeholders::_1));
				_server.SetReceiveCallback(std::bind(&Server::OnReceive, this, std::placeholders::_1, std::placeholders::_2));
			}

			void Listen(const net::Endpoint & endpoint)
			{
				_server.Listen(endpoint);
			}

		private:
			void OnSend(const std::shared_ptr<net::TCPSession> & session)
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

			void OnError(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "["
				          << session->LocalEndpoint().AsString()
				          << "] error"
				          << std::endl;
			}

			void OnClose(const std::shared_ptr<net::TCPSession> & session)
			{
				std::cout << "[" << session->LocalEndpoint().AsString()
				          << "] close ["
				          << session->PeerEndpoint().AsString()
				          << (session->IsConnect() ? "] failed" : "] success")
				          << std::endl;
			}

			void OnAccept(const std::shared_ptr<net::TCPSession> & session)
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

			void OnReceive(const std::shared_ptr<net::TCPSession> & session, net::Buffer * buffer)
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

				if (++_count == totalCount)
				{
					session->Shutdown();
				}
				else
				{
					session->Send("Hello TCP Client", 16);
				}
			}

		private:
			int32_t _count{ 0 };

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
