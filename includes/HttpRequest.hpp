#include "Sockets++.hpp"
#include <algorithm> // Required for std::search
#include <vector>
#include <unordered_map>
namespace SocketsPlusPlus
{
	enum class RequestMethod {
		GET,
		POST,
		PUT
	};

	class HttpRequest
	{
	public:
		HttpRequest(Socket& sockRef)
		{

			HttpRequestRaw = sockRef.RecieveAllHttp();
			parse();
		}
		void parse()
		{
			static std::vector<char> splitBy = { '\r','\n' }; //\r\n splits line


			for (
				std::vector<char>::iterator nextStep = HttpRequestRaw.begin(), last = HttpRequestRaw.begin();
				nextStep != HttpRequestRaw.end();
				last = nextStep, nextStep = std::search( nextStep, HttpRequestRaw.end(), splitBy.begin(), splitBy.end())+2
				)
			{
				std::string newEntry =  std::string(last, nextStep);
				newEntry = newEntry.substr(0, newEntry.size() - 2);

				//if not empty string start parsing the request.
				if (std::any_of(newEntry.begin(), newEntry.end(), [](char input) {return std::isblank(input); }))
				{
					size_t colonLocation = newEntry.find(':');

					if (newEntry.find(':') != std::string::npos)
					{

					}
					else {
						//idk fuck off do something else with your time
					}
				}
				
			}
			
		}
		// so that when i iterate the map i can get the string easily.
		std::string GetRequestMethodAsString(RequestMethod inputMethod)
		{
			switch (inputMethod)
			{
			case RequestMethod::GET:
				return "GET";
			case RequestMethod::POST:
				return "POST";
			case RequestMethod::PUT:
				return "PUT";
			}
		}
	private:
		std::vector<char> HttpRequestRaw;
		RequestMethod method;
		static inline std::unordered_map<RequestMethod, std::string> RequestMethodStringMap;


	};

}