#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <vector>

const int BLOCK = 30;
const int WIDTH = 300;
const int HEIGHT = 600;

int field[20][10] = {0};

int colors[7][3] = {
    {255, 255, 255}, // white
    {0, 0, 255}, // blue
    {255, 0, 0}, // red
    {0, 255, 0}, // green
    {255, 255, 0}, // yellow
    {255, 104, 0}, //orange
    {128, 128, 128} // gray
};

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tetris");

int center = WIDTH / 30 / 2;

int start_coords[7][8] = {
    {center, 0, center, 1, center, 2, center - 1, 2}, // J
    {center, 0, center, 1, center, 2, center, 3}, // I
    {center, 0, center + 1, 0, center, 1, center + 1, 1}, // квадрат
    {center, 0, center, 1, center, 2, center + 1, 2}, // L
    {center - 1, 0, center, 0, center, 1, center + 1, 1}, // Z
    {center, 0, center, 1, center - 1, 1, center + 1, 1}, // _|_
    {center, 0, center, 1, center + 1, 0, center - 1, 1} // Z в другую сторону
};

struct Figure{
    int type = -1;
    bool movement = false;
    int color[3] = {-1};
    int coords[4][2];
};

int rotated_coords[4][2];

std::vector<Figure> figures;

float timer = 0;
	float delay = 0.3;

#endif // CONFIG_H_INCLUDED
