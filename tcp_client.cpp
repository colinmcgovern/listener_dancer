#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

//g++ tcp_client.cpp -pthread -lboost_thread -o client

using boost::asio::ip::tcp;

using namespace std;

// class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
// 	public: 
// 		typedef boost::shared_ptr<tcp_connection> pointer;

// 		static pointer create(boost::asio::io_context& io_context){
// 			cout << "tcp_connection::pointer()" << endl; //del
// 			return pointer(new tcp_connection(io_context));
// 		}

// 		tcp::socket& socket(){
// 			cout << "socket()" << endl; //del
// 			return socket_;
// 		}

// 		void start(){
// 			cout << "start() started" << endl; //del

// 			cout << "Sending info to " <<
// 			 socket_.remote_endpoint().address().to_string() << ":" << 
// 			 socket_.remote_endpoint().port() <<
// 			endl;

// 			client_t new_client = {
// 				socket_.remote_endpoint().address().to_string(),
// 				socket_.remote_endpoint().port() 
// 			};

// 			clients.push_back(new_client);

// 			// const size_t id = clients.size();

// 			// boost::asio::async_write(socket_, boost::asio::buffer(&id,sizeof(size_t)),
// 	  //       boost::bind(&tcp_connection::handle_write, shared_from_this(),
// 	  //         boost::asio::placeholders::error,
// 	  //         boost::asio::placeholders::bytes_transferred));

// 			string message = "bpm:180";

// 			boost::asio::async_write(socket_, boost::asio::buffer(message),
// 			boost::bind(&tcp_connection::handle_write, shared_from_this(),
// 			boost::asio::placeholders::error,
// 			boost::asio::placeholders::bytes_transferred));

			
// 			cout << "start() ended" << endl; //del
// 		}

// 	private:
// 		tcp_connection(boost::asio::io_context& io_context)
// 		: socket_(io_context)
// 		{
// 			cout << "tcp_connection()" << endl; //del
// 		}

// 		void handle_write(const boost::system::error_code& /*error*/,
// 		  size_t /*bytes_transferred*/)
// 		{
// 			cout << "handle_write()" << endl; //del
// 		}

// 		tcp::socket socket_;
// };

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

		boost::array<char,128> buf;
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
		cout << len << endl;
		cout << buf.data() << endl;
		cout << "!!!!!!!!!!" << endl;

		socket.write_some(boost::asio::buffer("ack"));

		cout << "loop end" << endl; //del
	}

}