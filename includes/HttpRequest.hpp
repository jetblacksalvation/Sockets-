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
			static std::string splitBySpace = { ' ' };
			std::vector<std::string> requestSplitByNewline = {};
			//this will hold the whole request split by newlines and organized in order (first to last, aka how it just comes in normally ig)
			//this should make it easier for me to parse sepcific lines that may be differet


			//next is the char/addr that is after the next line feed, last is the char/addr that is after the line feed for the run before 
			for (
				std::vector<char>::iterator nextStep = HttpRequestRaw.begin(), last = HttpRequestRaw.begin();
				nextStep != HttpRequestRaw.end();
				last = nextStep, nextStep = std::search( nextStep, HttpRequestRaw.end(), splitBy.begin(), splitBy.end())+2
				)
			{
				std::string newEntry =  std::string(last, nextStep);
				newEntry = newEntry.substr(0, newEntry.size() - 2);//remove the \r\n aka line feed
				if (std::any_of(newEntry.begin(), newEntry.end(), [](char input) {return std::isblank(input); }))
				{
					requestSplitByNewline.push_back(newEntry);

				}
				
			}
			//time to actually parse it, starting from index 1 because i want to ignore the method, route and http version in the parser. it would make the code
			//look like shit if i wanted to make a dynamic approach for that part because its not dynamic
			// index is used to keep track of which part of the header we should process. the request method is always first, than route and finally the http version
			for (std::uint64_t readIndexFrom = 0, index = 0; readIndexFrom < requestSplitByNewline[0].size(); readIndexFrom++)
			{
				


				size_t pos = requestSplitByNewline[0].find(' ',readIndexFrom);

				//if NPOS is reached at an unexpected time an error should be raised
				if (pos == std::string::npos)
					break;

				//STAGE 1: Parse Request method
				if (index == 0)
				{
					method =  GetRequestmethodFromString(requestSplitByNewline[0].substr(readIndexFrom, pos));
					readIndexFrom = pos ;
					index = 1;
					continue;
				}
				//STAGE 2: Parse Request route!
				if (index == 1)
				{
					route = requestSplitByNewline[0].substr(readIndexFrom, pos-readIndexFrom);
					readIndexFrom = pos ;
					index = 2;

					continue;

				}
				//STAGE 3: Parse HTTP Version (TODO! because its not necissary)
				if (index == 2)
				{
					printf("Finished Parsing Request Method!");
					break;
				}


			}

		}
		std::string GetRequestRoute()
		{
			return this->route;
		}
		
		// so that when i iterate the map i can get the string easily.
		static std::string GetRequestMethodAsString(RequestMethod inputMethod)
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
		static RequestMethod GetRequestmethodFromString(std::string s)
		{
			if (s == "GET")
			{
				return RequestMethod::GET;
			}
			if (s == "POST")
			{
				return RequestMethod::POST;
			}
			if (s == "PUT")
			{
				return RequestMethod::PUT;
			}
			//throw something idk=
		}
	private:
		std::vector<char> HttpRequestRaw;
		//Request Properties
		RequestMethod method;
		std::string route;


		//static inline std::unordered_map<RequestMethod, std::string> RequestMethodStringMap;// ???? why would i need a map ????


	};

}