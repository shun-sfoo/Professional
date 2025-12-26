#pragma once

#include <exception>
#include <format>
#include <string>
class FileError : public std::exception {
public:
  FileError(std::string filename) : m_filename(std::move(filename)) {}
  const char *what() const noexcept override { return m_message.c_str(); }
  virtual const std::string &getFileName() const noexcept { return m_filename; }

protected:
  virtual void setMessage(std::string message) {
    m_message = std::move(message);
  }

private:
  std::string m_filename;
  std::string m_message;
};

class FileOpenError : public FileError {
public:
  FileOpenError(std::string filename) : FileError{std::move(filename)} {
    setMessage(std::format("Unable to open {}.", getFileName()));
  }
};

class FileReadError : public FileError {
public:
  FileReadError(std::string filename, size_t lineNumber)
      : FileError{std::move(filename)}, m_lineNumber{lineNumber} {
    setMessage(
        std::format("Error reading {}, line {}.", getFileName(), lineNumber));
  }

  virtual size_t getLineNumber() const noexcept { return m_lineNumber; }

private:
  size_t m_lineNumber{0};
};
