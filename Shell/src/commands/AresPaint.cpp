#include "AresPaint.h"
using namespace AresConsole;
#include<SDL2/SDL.h>

AresPaint::AresPaint(char* loc, AresLog*& l)
{
	this->log = l;
	this->location = std::string(loc);
}

AresPaint::~AresPaint()
{

}

bool AresPaint::is_cmd(char* input)
{
	std::regex input_match("(paint)", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(std::string(input), input_match))
	{
		return true;
	}
	return false;
}


bool AresPaint::execute(char*)
{
	bool windowOpen = true;
	std::vector<std::pair<int, int>> points_list;
	std::vector < std::pair< std::pair<int, int>, std::pair<int, int>>> lines_list;

	int r = 255, g = 255, b = 255;
	std::thread([&] {
		SDL_Renderer* render;
		SDL_Window* window;
		SDL_Event sdlevent;

		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(200, 200, NULL, &window, &render);
		SDL_SetWindowTitle(window, "Paint");

		while (windowOpen)
		{
			while (SDL_PollEvent(&sdlevent))
			{
				switch (sdlevent.type)
				{
				case SDL_QUIT:
					windowOpen = false;
					break;
				}
			}

			SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(render);

			SDL_SetRenderDrawColor(render, r, g, b, SDL_ALPHA_OPAQUE);

			for (std::pair<int, int> point : points_list)
			{	
				SDL_RenderDrawPoint(render, point.first, point.second);
			}

			for (std::pair< std::pair<int, int>, std::pair<int, int>> line : lines_list)
			{
				SDL_RenderDrawLine(render, line.first.first, line.first.second, line.second.first, line.second.second);
			}

			SDL_RenderPresent(render);
		}
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(window);
		SDL_Quit();
		}).detach();

		while (windowOpen)
		{
			log->print("(paint)>", L_NONE, ' ');
			std::string line;
			std::getline(std::cin, line);
			if (!windowOpen)
			{
				return true;
			}

			if (line == "exit")
			{
				windowOpen = false;
				break;
			}
			else
			{
				if (line == "point")
				{
					std::pair<int, int> pos;

					log->print("point-x>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					pos.first = std::atoi(line.c_str());

					log->print("point-y>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					pos.second = std::atoi(line.c_str());

					points_list.push_back(pos);
				}
				else if (line == "color")
				{
					log->print("color-red>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					r = std::atoi(line.c_str());

					log->print("color-green>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					g = std::atoi(line.c_str());

					log->print("color-blue>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					b = std::atoi(line.c_str());
				}
				else if (line == "line")
				{
					std::pair<int, int>  p1;
					std::pair<int, int> p2;

					log->print("point-x>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					p1.first = std::atoi(line.c_str());

					log->print("point-y>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					p1.second = std::atoi(line.c_str());

					log->print("point-x>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					p2.first = std::atoi(line.c_str());

					log->print("point-y>", L_NONE, ' ');
					std::getline(std::cin, line);
					if (!windowOpen)
					{
						return true;
					}
					p2.second = std::atoi(line.c_str());

					std::pair< std::pair<int, int>, std::pair<int, int>> line = { p1,p2 };
					lines_list.push_back(line);
				}
			}
		}
		return true;
}