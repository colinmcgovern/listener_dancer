#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <fstream>
#include <chrono>
#include <cstdio>
#include <utility>
#include "visual.h"

using namespace std::chrono;
using namespace std;

using boost::asio::ip::tcp;
using std::vector;
using std::pair;

pair<long,double> last_rotate_x = make_pair(0,0);
pair<long,double> last_rotate_y = make_pair(0,0);
pair<long,double> last_rotate_z = make_pair(0,0);

bool turn_around_x = 0;
bool turn_around_y = 0;
bool turn_around_z = 0;

double rotate_x = 0;
double rotate_y = 0;
double rotate_z = 0;

double max_x_vel = 0;
double max_y_vel = 0;
double max_z_vel = 0;

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

visual v;

double degree_dist(double x, double y){
	double smaller, larger;
	if(x < y){
		smaller = x;
		larger = y;
	}else{
		smaller = y;
		larger = x;
	}

	if(larger-smaller>180){
		larger -= 360;
	}

	return abs(larger-smaller);
}

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
	public: 
		typedef boost::shared_ptr<tcp_connection> pointer;

		static pointer create(boost::asio::io_context& io_context){
			cout << "tcp_connection::pointer()" << endl; //del
			return pointer(new tcp_connection(io_context));
		}

		tcp::socket& socket(){
			cout << "socket()" << endl; //del
			return socket_;
		}

		void start(){
			cout << "start() started" << endl; //del

			cout << "Sending info to " <<
			 socket_.remote_endpoint().address().to_string() << ":" << 
			 socket_.remote_endpoint().port() <<
			endl;

			for(;;){

				boost::array<char,128> buf;
				boost::system::error_code error;
				
				size_t len = socket_.read_some(boost::asio::buffer(buf), error);

				if(error == boost::asio::error::eof){
					cout << 2 << endl;
					break;
				}else if(error){
					cout << 3 << endl;
					throw boost::system::system_error(error);
				}
				vector<string> values = explode(buf.data(),':');

				long curr_time = long(duration_cast< milliseconds >(
    				system_clock::now().time_since_epoch()).count());

				//cout << curr_time << " " << values[0] << " "<< values[1] << " "<< values[2] << endl; //del


				if(values[0]=="x" && values[1]==values[2] && curr_time!=last_rotate_x.first){

					double new_rotate = stod(values[1]);

					cout << abs(last_rotate_x-new_rotate) << " " << endl; //del

					if(abs(last_rotate_x-new_rotate)>=180){
						turn_around_x = !turn_around_x;
					}

					rotate_x = stod(values[1]) + turn_around_x*180;

					double x_vel = degree_dist(last_rotate_x.second,new_rotate) / double(curr_time-last_rotate_x.first);

					if(x_vel > max_x_vel && curr_time!=last_rotate_x.first){
						max_x_vel = x_vel;
					}

					last_rotate_x = make_pair(curr_time,stod(values[1]));
				}

				if(values[0]=="y" && values[1]==values[2] && curr_time!=last_rotate_y.first){

					double new_rotate = stod(values[1]);

					cout << abs(last_rotate_y-new_rotate) << " " << endl; //del

					if(abs(last_rotate_y-new_rotate)>=180){
						turn_around_y = !turn_around_y;
					}

					rotate_y = stod(values[1]) + turn_around_y*180;

					double y_vel = degree_dist(last_rotate_y.second,new_rotate) / double(curr_time-last_rotate_y.first);

					if(y_vel > max_y_vel && curr_time!=last_rotate_y.first){
						max_y_vel = y_vel;
					}

					last_rotate_y = make_pair(curr_time,stod(values[1]));
				}

				if(values[0]=="z" && values[1]==values[2] && curr_time!=last_rotate_z.first){

					double new_rotate = stod(values[1]);

					cout << abs(last_rotate_z-new_rotate) << " " << endl; //del

					if(abs(last_rotate_z-new_rotate)>=180){
						turn_around_z = !turn_around_z;
					}

					rotate_z = stod(values[1]) + turn_around_z*180;

					double z_vel = degree_dist(last_rotate_z.second,new_rotate) / double(curr_time-last_rotate_z.first);

					if(z_vel > max_z_vel && curr_time!=last_rotate_z.first){
						max_z_vel = z_vel;
					}

					last_rotate_z = make_pair(curr_time,stod(values[1]));
				}

				v.update_rotation(rotate_x,rotate_y,rotate_z);

				//del
				//cout << int(rotate_x) << " " << int(rotate_y) << " " << int(rotate_z) << endl;
				//del

				//string message = "test";
				boost::asio::async_write(socket_, boost::asio::buffer(buf),
				boost::bind(&tcp_connection::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			}

			
			cout << "start() ended" << endl; //del
		}

	private:
		tcp_connection(boost::asio::io_context& io_context)
		: socket_(io_context)
		{
			cout << "tcp_connection()" << endl; //del
		}

		void handle_write(const boost::system::error_code& /*error*/,
		  size_t /*bytes_transferred*/)
		{
			cout << "handle_write()" << endl; //del
		}

		tcp::socket socket_;
};


class tcp_server{
	public:
		tcp_server(boost::asio::io_context& io_context) : io_context_(io_context), 
		acceptor_(io_context, tcp::endpoint(tcp::v4(), 15)){
			cout << "tcp_server() started" << endl; //del
			start_accept();
			cout << "tcp_server() ended" << endl; //del
		}

	private:
		void start_accept(){

			cout << "start_accept() started" << endl; //del
			tcp_connection::pointer new_connection = tcp_connection::create(io_context_);

			acceptor_.async_accept(new_connection->socket(),
				boost::bind(&tcp_server::handle_accept, this, new_connection,
					boost::asio::placeholders::error));

			cout << "start_accept() ended" << endl; //del
		}

		void handle_accept(tcp_connection::pointer new_connection,
			const boost::system::error_code& error){

			cout << "handle_accept() started" << endl; //del

			if(!error){
				new_connection->start();
			}

			start_accept();

			cout << "handle_accept() ended" << endl; //del
		}

		boost::asio::io_context& io_context_;
		tcp::acceptor acceptor_;
};


int main( int argc, char **argv ){

	cout << "main() started" << endl; //del

	thread t1([&v]{
		v.start();
	});

	for(;;){
		
		try{
			boost::asio::io_context io_context;
			tcp_server server(io_context);
			io_context.run();
		}catch(std::exception& e){
			std::cerr << e.what() << std::endl;
		}
	}


	cout << "main() ended" << endl; //del

	t1.join();

	return 0;
}
