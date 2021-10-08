#include <SFML/Graphics.hpp>
#include "config.h"
#include <iostream>
#include "time.h"
#include <cmath>

void is_movement_down_possible();
void draw_field();
void move_down();
void move_aside(int);
bool is_movement_right_possible();
bool is_movement_left_possible();
void set_up_new_figure();
bool is_figure_collided_with_others();
bool is_here_another_figure_by_right_side();
bool is_here_another_figure_by_left_side();
void set_rotated_coords();

int main(){
    srand(time(NULL));
    //set up first block
    set_up_new_figure();


	bool check = true;


	sf::Clock clock;

    sf::Event evnt;
    while(window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //check window/keyboard events
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch(evnt.type){
            case sf::Event::Closed:
                window.close();
                break;
            }
            //move left
            if(evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::A && is_movement_left_possible()){
                    std::cout << "left\n";

                move_aside(-1);
            }
            //move right
            if(evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::D && is_movement_right_possible()){
                std::cout << "right\n";
                move_aside(1);
            }
            // move upwards

            if(evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::W){
                    set_rotated_coords();
                    for(int i = 0;i < 4;i++){
                        std::cout << "rotated: \n";
                        std::cout << rotated_coords[i][0] << " " << rotated_coords[i][1] << std::endl;
                    }
                for(int i = 0;i < 4;i++){
                    std::cout << figures[figures.size() - 1].coords[i][0] << " " << figures[figures.size() - 1].coords[i][1] << std::endl;
                }
                std::cout << std::endl;
            }
        }


        //game

        is_movement_down_possible();
        if(figures[figures.size() - 1].movement && timer > delay){

            move_down();
            timer = 0;
        }

        if(!figures[figures.size() - 1].movement){
                set_up_new_figure();
        }


        window.clear();
        draw_field();
        window.display();
    }

    return 0;
}

void draw_field(){
    for(int i = 0;i < figures.size();i++){
            for(int j = 0;j < 4;j++){
            sf::RectangleShape rect(sf::Vector2f(BLOCK, BLOCK));
            rect.setFillColor(sf::Color(figures[i].color[0], figures[i].color[1], figures[i].color[2]));
            rect.setPosition(figures[i].coords[j][0] * BLOCK, figures[i].coords[j][1] * BLOCK);
            window.draw(rect);
        }
    }
}

void set_rotated_coords(){
     Figure current_figure = figures[figures.size() - 1];
     //осевой блок фигуры
     int original_center[2];

     //осевой блок фигуры после изменения
     int rotated_center[2];

     //присваивание координат оригинальному осевому блоку
     original_center[0] = current_figure.coords[0][0];
     original_center[1] = current_figure.coords[0][1];

     //установка rotated координат
    for(int i = 0;i < 4;i++){
        rotated_coords[i][0] = current_figure.coords[i][1];
        rotated_coords[i][1] = -current_figure.coords[i][0];
    }

    //присваивание координат измененому осевому центру
    rotated_center[0] = rotated_coords[0][0];
    rotated_center[1] = rotated_coords[0][1];

    //присваивание измененных координат фигуре
    for(int i = 0;i < 4;i++){
        figures[figures.size() - 1].coords[i][0] = rotated_coords[i][0];
        figures[figures.size() - 1].coords[i][1] = rotated_coords[i][1];
    }

    //нахождение разницы по координатам между оригинальным и измененными центрами
    int gap_x = std::abs(original_center[0] - rotated_center[0]);
    int gap_y  = std::abs(original_center[1] - rotated_center[1]);

    //выравнивание фигуры с измененными координатами на исходное место
    for(int i = 0;i < 4;i++){
        figures[figures.size() - 1].coords[i][0] += gap_x;
        figures[figures.size() - 1].coords[i][1] += gap_y;
    }
}

bool is_figure_collided_with_others(){
    Figure current_figure = figures[figures.size() - 1];
    for(int i = 0;i < figures.size() - 1;i++){
        for(int j = 0;j < 4;j++){
            for(int k = 0;k < 4;k++){
                if(figures[i].coords[j][1] * BLOCK - BLOCK == current_figure.coords[k][1] * BLOCK && figures[i].coords[j][0] * BLOCK == current_figure.coords[k][0] * BLOCK){
                    return true;
                }
            }
        }
    }
    return false;
}

void is_movement_down_possible(){
    Figure current_figure = figures[figures.size() - 1];
    for(int i = 0;i < 4;i++){
        if(current_figure.coords[i][1] * BLOCK + BLOCK == HEIGHT || is_figure_collided_with_others()){
            figures[figures.size() - 1].movement = false;
        }
    }
}

void move_down(){
    for(int i = 0;i < 4;i++){
        figures[figures.size() - 1].coords[i][1]++;
    }
}

void move_aside(int dir){
    for(int i = 0;i < 4;i++){
        figures[figures.size() - 1].coords[i][0] += dir;
    }
}

bool is_here_another_figure_by_right_side(){
    Figure current_figure = figures[figures.size() - 1];
    for(int i = 0;i < figures.size() - 1;i++){
        for(int j = 0;j < 4;j++){
            for(int k = 0;k < 4;k++){
                if(current_figure.coords[k][0] * BLOCK + BLOCK == figures[i].coords[j][0] * BLOCK && current_figure.coords[k][1] * BLOCK == figures[i].coords[j][1] * BLOCK){
                        std::cout << "there is a figure by right side!!!!\n";
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_movement_right_possible(){
    Figure last_figure = figures[figures.size() - 1];
    for(int i = 0;i < 4;i++){
        if(last_figure.coords[i][0] * BLOCK + BLOCK  >= WIDTH || is_here_another_figure_by_right_side()){
            return false;
        }
    }
    return true;
}

bool is_here_another_figure_by_left_side(){
    Figure current_figure = figures[figures.size() - 1];
    for(int i = 0;i < figures.size() - 1;i++){
        for(int j = 0;j < 4;j++){
            for(int k = 0;k < 4;k++){
                if(current_figure.coords[k][0] * BLOCK - BLOCK == figures[i].coords[j][0] * BLOCK && current_figure.coords[k][1] * BLOCK == figures[i].coords[j][1] * BLOCK){
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_movement_left_possible(){

    Figure last_figure = figures[figures.size() - 1];
    for(int i = 0;i < 4;i++){
        if(last_figure.coords[i][0] * BLOCK <= 0 || is_here_another_figure_by_left_side()){
            return false;
        }
    }
    return true;
}

void set_up_new_figure(){
    srand(time(NULL));

    Figure new_figure;

    new_figure.movement = true;
    new_figure.type = 1 + rand() % 7;
    int random_color = rand() % 6;
    for(int i = 0;i < 3;i++){
        new_figure.color[i] = colors[random_color][i];
    }
    for(int i = 0;i < 8;i++){
        if(i % 2 == 0){
            new_figure.coords[i / 2][0] = start_coords[new_figure.type - 1][i];
            continue;
        }
        new_figure.coords[i / 2][1] = start_coords[new_figure.type - 1][i];
    }
    figures.push_back(new_figure);

}
