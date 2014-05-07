#ifndef LE_NETWORK_EXCEPTIONS
#define LE_NETWORK_EXCEPTIONS

#include <stdexcept>

namespace LE {
  namespace Network {
	class SocketException: public std::runtime_error {
	  public:
		explicit SocketException(const string& error): std::runtime_error(error) {};
	};

	class TimeoutException: public std::runtime_error {
	  public:
		explicit TimeoutException(const string& error): std::runtime_error(error) {};
	};
  }
}

#endif
