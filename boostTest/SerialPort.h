#pragma once
#include <iostream>  
#include <boost/asio.hpp>  
#include <boost/bind.hpp> 

using namespace std;
using namespace boost::asio;

typedef string any_type;

class SerialPort
{
private:
	//Initialize port  
	bool init_port(const any_type port, const unsigned int char_size);
public:
	//Constructor  
	//Destructor  
	SerialPort(const any_type &port_name);
	~SerialPort();

	//Write some data to port  
	void write_to_serial(const any_type data);

	//Read data from port which write data just now  
	void read_from_serial();


	int read_from_serialSync(char pBuf[], size_t length)
	{
		//return boost::asio::read(*pSerialPort, boost::asio::buffer(pBuf, length), ec);
		return this->pSerialPort->read_some(boost::asio::buffer(pBuf, length), ec);
	}

	//The asyanc callback function of asyanc_read  
	void handle_read(char buf[], boost::system::error_code ec,
		std::size_t bytes_transferred);

	//To Call io_service::run function to call asyanc callback funciton  
	void call_handle();



private:
	//io_service Object  
	io_service m_ios;

	//Serial port Object  
	serial_port *pSerialPort;

	//For save com name  
	any_type m_port;

	//Serial_port function exception  
	boost::system::error_code ec;

	//boost::function<void(const char*, size_t)> callback;
};

