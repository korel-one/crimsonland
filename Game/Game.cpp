#include "stdafx.h"
#include "MyFramework.h"

#include <map>

std::pair<int, int> parse(const std::string& str) {
	auto pos = str.find('x');

	return std::make_pair(std::atoi(str.substr(0, pos).c_str())
		, std::atoi(str.substr(pos + 1, str.size()).c_str()));
}

int main(int argc, char ** argv)
{
	std::map<std::string, std::pair<int, int>> width_height;
	std::map<std::string, int> vals;

	if (argc > 1) {
		for (int i = 1; i < argc; i += 2) {
			if (strncmp(argv[i] + 1, "window", strlen("window")) == 0 ||
				strncmp(argv[i] + 1, "map", strlen("map")) == 0) {
				width_height[argv[i] + 1] = parse(argv[i + 1]);
			}
			else {
				vals[argv[i] + 1] = std::atoi(argv[i + 1]);
			}
		}
	}

	MyFramework* framework = nullptr;
	if (width_height.find("window") != width_height.end()) {

		//game.exe -window 800x600 -map 1000x1000 -num_enemies 10 -num_ammo 3
		framework = new MyFramework(vals["num_enemies"] > 250 ? 250 : vals["num_enemies"]
			, vals["num_ammo"]
			, width_height["window"].first
			, width_height["window"].second);

	}
	else {
		framework = new MyFramework(20, 3, 1024, 680);
	}

	int exit;
	while (RestartGame()) {
		exit = run(framework);
	}

	return exit;
}