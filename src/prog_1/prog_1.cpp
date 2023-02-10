#include "prog_1.h"
#include <thread>

using namespace std;

int main()
{ 
	DataHandler handler;
	try {
		while (1) {
			thread Thread1(&DataHandler::RunParser, ref(handler));
			thread Thread2(&DataHandler::RunHandler, ref(handler));
			Thread1.join();
			Thread2.join();
		}
	}
	catch(exception &ex){
		cout << ex.what() << endl;
	}
	
	return 0;
}
