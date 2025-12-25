#include <exception> // std::exception
#include <format>
#include <fstream>
#include <iostream>
#include <print>
#include <stdexcept> // std::invalid_argument std::runtime_error
#include <string>
#include <vector>

double safeDivide(double num, double den) {
  if (den == 0) {
    throw std::invalid_argument("Divide by zero");
  }
  return num / den;
}

std::vector<int> readIntegerFile(const std::string &filename) {
  std::ifstream inputStream{filename};
  if (inputStream.fail()) {
    throw std::exception{};
    throw 5;
    throw "Unable to open file";
  }

  std::vector<int> integers;
  int temp;
  while (inputStream >> temp) {
    integers.push_back(temp);
  }

  if (!inputStream.eof()) {
    throw std::runtime_error("Error reading the file.");
  }

  return integers;
}

int main() {
  const std::string filename{"IntegerFile.txt"};
  std::vector<int> myInts;
  try {
    myInts = readIntegerFile(filename);
    std::println("{}", safeDivide(5, 2));
    std::println("{}", safeDivide(10, 0));
    std::println("{}", safeDivide(3, 3));
  } catch (const std::invalid_argument &e) {
    std::println("Caught exception: {}", e.what());
  } catch (int e) {
    std::cerr << std::format("Unable to open file {} (Error Code{})", filename,
                             e)
              << std::endl;
  } catch (const char *e) {
    std::cerr << e << std::endl;
  }
}
