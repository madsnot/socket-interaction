#include "prog_2.h"
#include <thread>

using namespace std;

int main()
{
	Reviewer rev;
    rev.initSocket();
	try {
		while (1) {
			rev.RunReviewer();
		}
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}

	return 0;
}