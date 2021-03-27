#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <GL/glut.h>

//g++ cube_and_job_handler.cpp -pthread -lboost_thread -lglut -lGL -lGLU -o cube_and_job_handler

using boost::asio::ip::tcp;
using namespace std;
using std::vector;

once_flag flag;

float ver[8][3] = 
{
    {-1.0,-1.0,1.0},
    {-1.0,1.0,1.0},
    {1.0,1.0,1.0},
    {1.0,-1.0,1.0},
    {-1.0,-1.0,-1.0},
    {-1.0,1.0,-1.0},
    {1.0,1.0,-1.0},
    {1.0,-1.0,-1.0},
    // {-1.38,-.673,.073},
    // {-1.38,.673,.073},
    // {1.38,.673,.073},
    // {1.38,-.673,.073},
    // {-1.38,-.673,-.073},
    // {-1.38,.673,-.073},
    // {1.38,.673,-.073},
    // {1.38,-.673,-.073},    
};

GLfloat color[8][3] = 
{
    {0.0,0.0,0.0},
    {1.0,0.0,0.0},
    {1.0,1.0,0.0},
    {0.0,1.0,0.0},
    {0.0,0.0,1.0},
    {1.0,0.0,1.0},
    {1.0,1.0,1.0},
    {0.0,1.0,1.0},
};

void quad(int a,int b,int c,int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(ver[a]);

    glColor3fv(color[b]);
    glVertex3fv(ver[b]);

    glColor3fv(color[c]);
    glVertex3fv(ver[c]);

    glColor3fv(color[d]);
    glVertex3fv(ver[d]);
    glEnd();
}

void colorcube()
{
    quad(0,3,2,1);
    quad(2,3,7,6);
    quad(0,4,7,3);
    quad(1,2,6,5);
    quad(4,5,6,7);
    quad(0,1,5,4);
}

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

double last_rotation_x = 0;
double last_rotation_y = 0;
double last_rotation_z = 0;

double rotate_x = last_rotation_x;
double rotate_y = last_rotation_y; 
double rotate_z = last_rotation_z;

void specialKeys( int key, int x, int y ) 
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
}

void display()
{
    glClearColor( 0, 0, 0, 500 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 90, w / h, 0.1, 100 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt
        ( 
        0, 0, 3, 
        0, 0, 0,
        0, 1, 0
        );

    glRotatef( rotate_x, 0.0, 1.0, 0.0 );
    glRotatef( rotate_y, 1.0, 0.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, -1.0 );

    colorcube();

    glutSwapBuffers();
}

void timer(int extra)
{
    //rotate_y += 5;
    glutTimerFunc(30, timer, 0);
    glutPostRedisplay();
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
				cout << "loop start" << endl; //del

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

				cout << "!!!!!!!!!!" << endl;
				//cout << len << endl;
				// cout << buf.data() << endl;
				vector<string> values = explode(buf.data(),':');
				// for(auto v : values){
				// 	cout << v << endl;
				// }

				// last_rotation_x = stod(values[1]);
				// last_rotation_y = stod(values[2]);
				// last_rotation_z = stod(values[3]);

				// cout << "last_rotation_x " << last_rotation_x << endl; //del
				// cout << "last_rotation_y " << last_rotation_y << endl; //del
				// cout << "last_rotation_z " << last_rotation_z << endl; //del

				// rotate_x = rotate_x - last_rotation_x;
				// rotate_y = rotate_y - last_rotation_y;
				// rotate_z = rotate_z - last_rotation_z;

				// cout << "rotate_x " << rotate_x << endl; //del
				// cout << "rotate_y " << rotate_y << endl; //del
				// cout << "rotate_z " << rotate_z << endl; //del

				rotate_x = stod(values[1]);
				rotate_y = stod(values[2]);
				rotate_z = stod(values[3]);

				cout << "!!!!!!!!!!" << endl;

				//string message = "test";
				boost::asio::async_write(socket_, boost::asio::buffer(buf),
				boost::bind(&tcp_connection::handle_write, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));

				cout << "loop end" << endl; //del
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


	for(uint i=0;i<8;i++){
		ver[i][0] *= .673;
		ver[i][1] *= .073;
		ver[i][2] *= 1.38;
	}

	cout << "main() started" << endl; //del

	thread t1([&]{
		glutInit( &argc, argv );

	    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	    glutInitWindowSize( 800, 800 );
	    glutCreateWindow( "GLUT" );
	    glutDisplayFunc( display );
	    glutSpecialFunc( specialKeys );
	    glEnable( GL_DEPTH_TEST );
	    glutTimerFunc(0, timer, 0);
	    glutMainLoop();
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

	return 0;
}
