#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;
signed main()
{
	ifstream ifs;
	ofstream ofs;

	ifs.open("Template_main.cpp", ios::in);
	ofs.open("main.cpp", ios::out);

	time_t now = time(0);
	char *now_t = ctime(&now);
	now_t[strlen(now_t) - 1] = 0;
	std::string Author = "SokuRitszZ-Andrew1729";

	// output main context
	std::string s;
	while (getline(ifs, s))
	{
		int pos = s.find("%$Time$%");
		if (pos != -1) s.replace(pos, 8, now_t);
		pos = s.find("%$Author$%");
		if (pos != -1) s.replace(pos, 10, Author);
		ofs << s << '\n';
	}

	ifs.close();
	ofs.close();
	
	return 0;
}