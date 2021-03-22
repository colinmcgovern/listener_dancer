#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

//g++ tcp_client.cpp -pthread -lboost_thread -o client

using boost::asio::ip::tcp;

using namespace std;

int main(int argc, char* argv[]){
	try{
		if(argc != 2){
			cerr << "Usage client <host>" << endl;
			return 1;
		}
	}catch(exception& e){
		cerr << e.what() << endl;
	}

	cout << "io_context" << endl; //del
	boost::asio::io_context io_context;
	cout << "resolver" << endl; //del
	tcp::resolver resolver(io_context);

	cout << "endpoints" << endl; //del
	tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "15");

	cout << "socket" << endl; //del
	tcp::socket socket(io_context);
	cout << "connect" << endl; //del
	boost::asio::connect(socket, endpoints);

	for(;;){

		cout << "loop start" << endl; //del

		// boost::array<char,128> buf;
		boost::array<int,1> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if(error == boost::asio::error::eof){
			cout << 2 << endl;
			break;
		}else if(error){
			cout << 3 << endl;
			throw boost::system::system_error(error);
		}


		cout << "!!!!!!!!!!" << endl;
		cout << buf.data() << endl;
		cout << (int*)buf.data() << endl;
		cout << (double*)buf.data() << endl;
		printf("Value:  %p\n", &buf );
		cout << "!!!!!!!!!!" << endl;

		// boost::asio::async_write(socket_, boost::asio::buffer(message_),
	 //        boost::bind(&tcp_connection::handle_write, shared_from_this(),
	 //          boost::asio::placeholders::error,
	 //          boost::asio::placeholders::bytes_transferred));

		//cout.write(buf.data(), len);

		cout << "loop end" << endl; //del
	}


}