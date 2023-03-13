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
#include <fstream>
#include <vector>

using boost::asio::ip::tcp;

constexpr size_t image_size = 17618; // We changed the image_size to match. THe given 100x100 made it ugly.

void save_image(char* data, size_t len) // Implementation of Save_image method
{
 std::ofstream filewrite;   // Firstly, we create an object "filewrite"
                            // Which we use to write the data of the cat image to a new file called copycat
 filewrite.open("copycat.jpg"); // We open the emtpy copy cat 
 for (int i = 0; i<len; i++)    // Then we iterate through all the byte-data and write it all to new file using <<
 {
  filewrite << data[i];
 }
 filewrite.close(); // Then, when we are done, we close the object we created and all the image data has been transfered.
}                      // Important to close the object to ensure we have written everything into the new file and saved it.

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while(true)
    {
      boost::array<char, image_size> buf;
      boost::system::error_code error;

      // read until buffer is full
      boost::asio::read(socket,boost::asio::buffer(buf));

      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      save_image(buf.data(),image_size);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
