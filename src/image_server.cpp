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
#include <fstream>
#include <vector>

using boost::asio::ip::tcp;

std::vector<uint8_t> get_image(const char* filename) //This was stolen from the stackoverflow page from the assignment.
{
    // open the file:
    std::streampos fileSize; // Variable to hold the size of the file
    std::ifstream file(filename, std::ios::binary); // An object is created to open the file in binary

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<uint8_t> fileData(fileSize); // The important change in this, was descibing how many bytes the vector should take
    file.read((char*) &fileData[0], fileSize); // We used uint8_t as the assignment said
    
    return fileData;
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      auto message = get_image("cat.jpg"); //changed to our cat image

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}