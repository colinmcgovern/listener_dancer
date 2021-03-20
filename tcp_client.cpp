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

	boost::asio::io_context io_context;
	tcp::resolver resolver(io_context);

	tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "15");

	tcp::socket socket(io_context);
	boost::asio::connect(socket, endpoints);

	for(;;){
		boost::array<char,128> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		// if(error == boost::asio::error::eof){
		// 	cout << 2 << endl;
		// 	break;
		// }else if(error){
		// 	cout << 3 << endl;
		// 	throw boost::system::system_error(error);
		// }

		cout.write(buf.data(), len);

		//cout << 1 << endl;
	}


}