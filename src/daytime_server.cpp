//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp; 

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0); // Making a variable of the the type time_t of the current time.
  return ctime(&now); // using ctime method to convert the now variable into a string, and then returning it.
}

int main()
{
  try
  {
    boost::asio::io_context io_context; // Using the io_context class to make a io_context variable with the core functionality needed to connect and communicate with the server.

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13)); //Creating an acceptor with the io_context, and an endpoint with the v4 protocol and port 13, whichh is commonly used for processing time.

    while (true)
    {
      tcp::socket socket(io_context); // Creating a socket with the functionality of the io_context variable.
      acceptor.accept(socket); // Accepting the socket to handle the information for the server, while it is active.

      std::string message = make_daytime_string(); // Creating the message of the current time using the make_daytime_string method.

      boost::system::error_code ignored_error; // If an error accures, we will ignore it for now.
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error); // Using the write method to write the message in the server. The error will also be posted to the stack, and will be collected by the catch method below.
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl; // Tells what the error e is.
  }

  return 0;
}
