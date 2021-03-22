#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

using namespace std;

//g++ tcp_sync_server.cpp -pthread -lboost_thread -o server

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 15));
for (;;)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      string message = "bpm:180";

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }

    catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}