//#include "stdafx.h"
#include "SerialPort.h"
#include <string>  
#include <vector>  


//Define Constructor function  
SerialPort::SerialPort(const any_type &port_name) :pSerialPort(NULL)
{
	pSerialPort = new serial_port(m_ios);
	if (pSerialPort) {
		init_port(port_name, 8);
	}
}

//Define destructor function  
SerialPort::~SerialPort()
{
	if (pSerialPort)
	{
		delete pSerialPort;
	}
}


//Initialize port  
bool SerialPort::init_port(const any_type port, const unsigned int char_size)
{
	//New not success  
	if (!pSerialPort) {
		return false;
	}

	//Open Serial port object  
	pSerialPort->open(port, ec);


	//Set port argument  
	pSerialPort->set_option(serial_port::baud_rate(9600), ec);
	pSerialPort->set_option(serial_port::flow_control(serial_port::flow_control::hardware), ec);
	pSerialPort->set_option(serial_port::parity(serial_port::parity::none), ec);
	pSerialPort->set_option(serial_port::stop_bits(serial_port::stop_bits::one), ec);
	pSerialPort->set_option(serial_port::character_size(char_size), ec);

	return true;
}


//Define wirte_to_serial to write data to serial  
void SerialPort::write_to_serial(const any_type data)
{
	size_t len = write(*pSerialPort, buffer(data), ec);
	cout << len << "\t" << data << "\n";
}

void SerialPort::handle_read(char buf[], boost::system::error_code ec1,
	std::size_t bytes_transferred)
{
	cout << "\nhandle_read: ";
	cout.write(buf, bytes_transferred);
}



//Read data from the serial  
void SerialPort::read_from_serial()
{
	char v[10] = { 0 };
	async_read(*pSerialPort, buffer(v), boost::bind(&SerialPort::handle_read, this, v, _1, _2));
}


//Call handle_read function when async function read complete or come out exception  
void SerialPort::call_handle()
{
	//There can use deadline_timer to cancle serial_port read data  

	//Wait for call callback function  
	m_ios.run();
}