#include <boost/bind.hpp>
#include "chat.h"

Chat::Chat(io_context& io_context) : ip::udp::socket(io_context, udp::endpoint(udp::v4(), 8191))
{
	//open(ip::udp::v4());
	set_option(udp::socket::reuse_address(true));
}

Chat::~Chat()
{
}

void Chat::sendMsg(const string& content, const string& ip, unsigned short port)
{
	if (ip.empty())
	{
		set_option(socket_base::broadcast(true));
		send_to(buffer(content), udp::endpoint(address_v4::broadcast(), port));
	}
	else
	{
		send_to(buffer(content), udp::endpoint(make_address(ip), port));
	}
}

void Chat::recvMsg()
{
	async_receive_from(buffer(recvbuf), remotepoint, boost::bind(&Chat::handleReceive, this, placeholders::error, placeholders::bytes_transferred));
}

void Chat::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		cout << remotepoint.address() << ":" << remotepoint.port() << "\t";
		cout.write(recvbuf.data(), bytes_transferred) << endl;
		//cout << remotepoint.protocol() << endl;
	}
	recvMsg();
}