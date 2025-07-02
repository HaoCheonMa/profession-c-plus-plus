#include <iostream>
#include <string>
#include <limits>
#include <cmath>

bool strToInt(const std::string& s, int& result) {
    if (s.empty())
        return false;

    size_t i = 0;
    bool negative = false;
    if (s[0] == '-') {
        negative = true;
        i = 1;
        if (s.size() == 1)
            return false;
    }
    else if (s[0] == '+') {
        i = 1;
        if (s.size() == 1)
            return false;
    }

    int val = 0;
    for (; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9')
            return false;
        int digit = s[i] - '0';
        if (val > (std::numeric_limits<int>::max() - digit) / 10)
            return false;
        val = val * 10 + digit;
    }

    result = negative ? -val : val;
    return true;
}


class Screen {
	static constexpr int width = 82;
	static constexpr int height = 52;
public:
	char pixels[height][width];
	const int getSW() { return width; }
	const int getSH() { return height; }

    bool setScreen(std::pair<int, int>& XY, int& widthW, int& heightW) {
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                pixels[i][j] = ' ';

        pixels[0][0] = '*';
        pixels[height - 1][width - 1] = '*';
        pixels[0][width - 1] = '*';
        pixels[height - 1][0] = '*';

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if ((i == 0 || i == height - 1) && j > 0 && j < width - 1)
                    pixels[i][j] = '-';
                if ((j == 0 || j == width - 1) && i > 0 && i < height - 1)
                    pixels[i][j] = '|';
            }
        }

        int startX = XY.first;
        int startY = XY.second;
        int endX = XY.first + widthW - 1;
        int endY = XY.second + heightW - 1;

        if (endX < 1 || endY < 1 || startX > width - 2 || startY > height - 2)
            return false;

        bool leftVisible = (startX >= 1 && startX <= width - 2);
        bool rightVisible = (endX >= 1 && endX <= width - 2);
        bool topVisible = (startY >= 1 && startY <= height - 2);
        bool bottomVisible = (endY >= 1 && endY <= height - 2);

        for (int i = startY; i <= endY; ++i) {
            for (int j = startX; j <= endX; ++j) {
                bool isTopEdge = (i == startY);
                bool isBottomEdge = (i == endY);
                bool isLeftEdge = (j == startX);
                bool isRightEdge = (j == endX);

                bool drawX = false;

                if (isTopEdge && topVisible && j >= 1 && j <= width - 2)
                    drawX = true;

                if (isBottomEdge && bottomVisible && j >= 1 && j <= width - 2)
                    drawX = true;

                if (isLeftEdge && leftVisible && i >= 1 && i <= height - 2)
                    drawX = true;

                if (isRightEdge && rightVisible && i >= 1 && i <= height - 2)
                    drawX = true;

                if (drawX)
                    pixels[i][j] = 'X';
                else if (i >= 1 && i <= height - 2 && j >= 1 && j <= width - 2)
                    pixels[i][j] = ' ';
            }
        }

        return true;
    }

	void drawScreen() {
		std::cout << std::endl;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j)
				std::cout << pixels[i][j];
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

class Window {
	int width = 3;
	int height = 3;
	std::pair<int, int> coordXY = { 1, 1 };

public:
	int& getWW() { return width; }
	int& getWH() { return height; }
	std::pair<int, int>& getXY() { return coordXY; }

    void move(int dx, int dy) {
        coordXY.first += dx;
        coordXY.second += dy;
    }

    bool resize(int newWidth, int newHeight) {
        if (newWidth < 1 || newHeight < 1)
            return false;
        width = newWidth;
        height = newHeight;
        return true;
    }
};

int main() {
	
	Window window;
	Screen screen;

    std::string line;
    while (true) {
        std::cout << "Enter command (move dx dy | resize w h | display | close): ";
        std::getline(std::cin, line);

        size_t pos = line.find(' ');
        std::string cmd = (pos == std::string::npos) ? line : line.substr(0, pos);

        if (cmd == "move") {
            size_t pos1 = line.find(' ', pos + 1);
            if (pos == std::string::npos || pos1 == std::string::npos) {
                std::cout << "Invalid move parameters.\n";
                continue;
            }
            std::string sdx = line.substr(pos + 1, pos1 - pos - 1);
            std::string sdy = line.substr(pos1 + 1);

            int dx, dy;
            if (!strToInt(sdx, dx) || !strToInt(sdy, dy)) {
                std::cout << "Invalid move parameters.\n";
                continue;
            }
            window.move(dx, dy);
            auto& xy = window.getXY();
            std::cout << "Window moved to (" << xy.first << ", " << xy.second << ")\n";
        }
        else if (cmd == "resize") {
            size_t pos1 = line.find(' ', pos + 1);
            if (pos == std::string::npos || pos1 == std::string::npos) {
                std::cout << "Invalid resize parameters.\n";
                continue;
            }
            std::string sw = line.substr(pos + 1, pos1 - pos - 1);
            std::string sh = line.substr(pos1 + 1);

            int w, h;
            if (!strToInt(sw, w) || !strToInt(sh, h)) {
                std::cout << "Invalid resize parameters.\n";
                continue;
            }
            if (window.resize(w, h)) {
                std::cout << "Window resized to " << w << "x" << h << "\n";
            }
            else {
                std::cout << "Invalid size. Width and height must be >= 1.\n";
            }
        }
        else if (cmd == "close") {
            std::cout << "Window closed.\n";
            break;
        }
        else if (cmd == "display") {
            screen.setScreen(window.getXY(), window.getWW(), window.getWH());
            screen.drawScreen();
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }

}