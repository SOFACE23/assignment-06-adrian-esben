//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp; // Using the tcp class and socket type.

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context; //creating an io_context object.

    tcp::resolver resolver(io_context); //Creating a resolver object with the io_context variable as an attribute
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime"); //Defining the endpoints variable  with the resolve method, with the atrributes of the server we want to access, which in this case is the "daytime" service.

    tcp::socket socket(io_context); // We create a socket to communicate with.
    boost::asio::connect(socket, endpoints); // We connect to the endpoints, which was defined above, usingthe socket we just created. 

    while(true)
    {
      boost::array<char, 128> buf; //Creating an array with the name buf size of 128 chars for our buffed message
      boost::system::error_code error; // Creating an error variable.

      size_t len = socket.read_some(boost::asio::buffer(buf), error); // Using the read method to read the buffed string from the daytime server to the buf array.

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // If some other error accures, the we throw it on the stack for the catch method to collect.
      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl; // Tells what the error e is.
  }

  return 0;
}