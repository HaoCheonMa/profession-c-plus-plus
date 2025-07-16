#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <string>
#include "tools.h"
#include <vector>
#include <cstdlib>

enum colors {
	None,
	Red,
	Green,
	Blue
};

class Shape {
public:
	std::pair<double, double> centerXY = { 0, 0 };
	short color = None;
	std::string clrName = "transparent";

	Shape(double x, double y, short clr) : centerXY{ x, y }, color(clr) {
		if (color == 0)
			clrName = "transparent";
		else if (color == 1)
			clrName = "red";
		else if (color == 2)
			clrName = "green";
		else if (color == 3)
			clrName = "blue";
		else
			clrName = "unknown";
	}
};

class Circle: public Shape {
public:
	double radius = 0;
	Circle(double x, double y, short clr, double rds) : Shape(x, y, clr),  radius(rds){}
	double square = atan(1) * 4 * radius * radius;

	std::pair<std::pair<double, double>, std::pair<double, double>> box = { {0, 0}, {0, 0} };

	std::pair<std::pair<double, double>, std::pair<double, double>> boundingBox() {
		box = { { centerXY.first - radius, centerXY.second - radius },
		{ centerXY.first + radius, centerXY.second + radius } };
		return box;
	}

	void output() {

		boundingBox();
		std::cout << std::endl;
		std::cout << "<Circle>" << std::endl;
		std::cout << "Center: (" << centerXY.first << ", " << centerXY.second << ")" << std::endl;
		std::cout << "Color : " << clrName << std::endl;
		std::cout << "Radius: " << radius << std::endl;
		std::cout << "Square: " << square << std::endl;
		std::cout << "Boundig box: (" << box.first.first << ", " << box.first.second << "), (" << box.second.first << ", " << box.second.second << ")" << std::endl;
		std::cout << std::endl;

	}

};

class Square : public Shape {
public:
	double length = 0;

	Square() = default;
	Square(double x, double y, short clr, double ln) : Shape(x, y, clr), length(ln) {}

	double square() { return length * length; }

	std::pair<std::pair<double, double>, std::pair<double, double>> box = { {0, 0}, {0, 0} };

	std::pair<std::pair<double, double>, std::pair<double, double>> boundingBox() {
		double half = length / 2.0;
		box = {
			{centerXY.first - half, centerXY.second - half},
			{centerXY.first + half, centerXY.second + half}
		};
		return box;
	}

	void output() {

		boundingBox();
		std::cout << std::endl;
		std::cout << "<Square>" << std::endl;
		std::cout << "Center: (" << centerXY.first << ", " << centerXY.second << ")" << std::endl;
		std::cout << "Color : " << clrName << std::endl;
		std::cout << "Length: " << length << std::endl;
		std::cout << "Square: " << square() << std::endl;
		std::cout << "Boundig box: (" << box.first.first << ", " << box.first.second << "), (" << box.second.first << ", " << box.second.second << ")" << std::endl;
		std::cout << std::endl;

	}

};

class Triangle : public Shape {
public:
	double length = 0;

	Triangle() = default;
	Triangle(double x, double y, short clr, double ln) : Shape(x, y, clr), length(ln) {}

	double square() {
		return length * length * std::sqrt(3) / 4;
	}

	std::pair<std::pair<double, double>, std::pair<double, double>> box = { {0, 0}, {0, 0} };

	std::pair<std::pair<double, double>, std::pair<double, double>> boundingBox() {
		double height = length * std::sqrt(3) / 2.0;
		double half = length / 2.0;
		box = {
			{centerXY.first - half, centerXY.second - height / 3.0},
			{centerXY.first + half, centerXY.second + 2.0 * height / 3.0}
		};
		return box;
	}

	void output() {

		boundingBox();
		std::cout << std::endl;
		std::cout << "<Triangle>" << std::endl;
		std::cout << "Center: (" << centerXY.first << ", " << centerXY.second << ")" << std::endl;
		std::cout << "Color : " << clrName << std::endl;
		std::cout << "Length: " << length << std::endl;
		std::cout << "Square: " << square() << std::endl;
		std::cout << "Boundig box: (" << box.first.first << ", " << box.first.second << "), (" << box.second.first << ", " << box.second.second << ")" << std::endl;
		std::cout << std::endl;

	}
};

class Rectangle : public Shape {
public:
	double width = 0;
	double height = 0;

	Rectangle() = default;
	Rectangle(double x, double y, short clr, double w, double h) : Shape(x, y, clr), width(w), height(h) {}

	double square() {
		return width * height;
	}

	std::pair<std::pair<double, double>, std::pair<double, double>> box = { {0, 0}, {0, 0} };

	std::pair<std::pair<double, double>, std::pair<double, double>> boundingBox() {
		double halfW = width / 2.0;
		double halfH = height / 2.0;
		box = {
			{centerXY.first - halfW, centerXY.second - halfH},
			{centerXY.first + halfW, centerXY.second + halfH}
		};
		return box;
	}

	void output() {

		boundingBox();
		std::cout << std::endl;
		std::cout << "<Rectangle>" << std::endl;
		std::cout << "Center: (" << centerXY.first << ", " << centerXY.second << ")" << std::endl;
		std::cout << "Color : " << clrName << std::endl;
		std::cout << "Width: " << width << std::endl;
		std::cout << "Height: " << height << std::endl;
		std::cout << "Square: " << square() << std::endl;
		std::cout << "Boundig box: (" << box.first.first << ", " << box.first.second << "), (" << box.second.first << ", " << box.second.second << ")" << std::endl;
		std::cout << std::endl;

	}
};

bool typeCheck(std::vector<std::string>& req) {
	for (int i = 1; i < req.size(); ++i)
		if (!isNumber(req[i])) {
			std::cerr << "\n**INCORRECT PARAMETERS**\n\n";
			return false;
		}

	return true;
}

int main() {

	std::cout << std::fixed << std::setprecision(2);

	std::string shp;
	std::cout << "**REQUEST FORMS**\n";
	std::cout << "<COLORS: 0 - None, 1 - Red, 2 - Green, 3 - Blue>\n";
	std::cout << "<Enter \"exit\" to stop programm>\n";
	std::cout << "1. circle x y color radius\n";
	std::cout << "2. square x y color length\n";
	std::cout << "3. triangle x y color length\n";
	std::cout << "4. rectangle x y color width height\n\n";

	Circle* circle = nullptr;
	Square* square = nullptr;
	Triangle* triangle = nullptr;
	Rectangle* rectangle = nullptr;

	bool hereCircle = false;
	bool hereSquare = false;
	bool hereTriangle = false;
	bool hereRectangle = false;

	while (true) {
		std::cout << "Enter request: ";
		getline(std::cin, shp);

		if (shp.empty()) {
			std::cerr << "\n**EMPTY REQUEST**\n\n";
			continue;
		}

		else if (shp == "exit")
			break;
		std::vector<std::string> request = parsing(shp);
		double x, y, radius, length, width, height;
		short color;

		if (request.size() != 5 && request.size() != 4) {
			std::cerr << "\n**NOT ENOUGH PARAMETERS**\n\n";
			continue;
		}

		if (request[0] == "circle") {
			
			if(!typeCheck(request))
				continue;

			x = stod(request[1]);
			y = stod(request[2]);
			color = stoi(request[3]);
			radius = stod(request[4]);
			if (radius <= 0) {
				std::cerr << "\n**INVALID PARAMETERS**\n\n";
				continue;
			}

			if (!hereCircle) {
				circle = new Circle(x, y, color, radius);
				hereCircle = true;
			}
			else {
				delete circle;
				circle = new Circle(x, y, color, radius);
			}

			circle->output();

		}

		else if (request[0] == "square") {

			if (!typeCheck(request))
				continue;

			x = stod(request[1]);
			y = stod(request[2]);
			color = stoi(request[3]);
			length = stod(request[4]);
			if (length <= 0) {
				std::cerr << "\n**INVALID PARAMETERS**\n\n";
				continue;
			}

			if (!hereSquare) {
				square = new Square(x, y, color, length);
				hereSquare = true;
			}
			else {
				delete square;
				square = new Square(x, y, color, length);
			}

			square->output();

		}

		else if (request[0] == "triangle") {

			if (!typeCheck(request))
				continue;

			x = stod(request[1]);
			y = stod(request[2]);
			color = stoi(request[3]);
			length = stod(request[4]);
			if (length <= 0) {
				std::cerr << "\n**INVALID PARAMETERS**\n\n";
				continue;
			}

			if (!hereTriangle) {
				triangle = new Triangle(x, y, color, length);
				hereSquare = true;
			}
			else {
				delete triangle;
				triangle = new Triangle(x, y, color, length);
			}

			triangle->output();

		}

		else if (request[0] == "rectangle") {

			if (!typeCheck(request))
				continue;

			x = stod(request[1]);
			y = stod(request[2]);
			color = stoi(request[3]);
			width = stod(request[4]);
			height = stod(request[5]);
			if (width <= 0 || height <= 0) {
				std::cerr << "\n**INVALID PARAMETERS**\n\n";
				continue;
			}

			if (!hereRectangle) {
				rectangle = new Rectangle(x, y, color, width, height);
				hereRectangle = true;
			}
			else {
				delete rectangle;
				rectangle = new Rectangle(x, y, color, width, height);
			}

			rectangle->output();

		}

		else {
			std::cerr << "\n**UNKNOWN SHAPE**\n\n";
			continue;
		}

	}

	std::cout << "\n<EXIT>";

	delete circle;
	delete square;
	delete triangle;
	delete rectangle;

}