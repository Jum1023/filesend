/*
Copyright (c) 2018 by JumHorn <JumHorn@gmail.com>
Distributed under the MIT License. (See accompanying file LICENSE)
*/

#ifndef _TRANSMIT_H_
#define _TRANSMIT_H_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../macro/export.h"
using namespace boost::asio;
using namespace boost::asio::ip;

class SHAREOBJECT_EXPORT Transmit
{
public:
	Transmit(io_context& io_context);
	~Transmit();

	int sendFile(const std::string& path, const std::string& ip, unsigned short port = 8191);
	void recvFile();

	inline double getProgress() { return progress; }

private:
	void handleAccept(const boost::system::error_code& error);
	void handleRead(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handleWrite(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handleConnect(const boost::system::error_code& error);

private:
	tcp::socket sendsocket;
	tcp::socket recvsocket;

	tcp::endpoint remotepoint;
	tcp::acceptor acceptor;
	boost::array<char, 65536> recvbuf;

	std::ifstream fin;
	std::streamsize filesize;
	std::string filename;
	double progress;
};

#endif