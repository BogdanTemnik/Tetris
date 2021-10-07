#include <SFML/Graphics.hpp>
#include "config.h"
#include <iostream>
#include "time.h"

void is_movement_down_possible();
void draw_field();
void move_down();
void move_aside(int);
bool is_movement_right_possible();
bool is_movement_left_possible();
void set_up_new_figure();
bool is_movement_aside_possible();

int main(){
    srand(time(NULL));
    set_up_new_figure();

    float timer = 0;
	float delay = 0.3;


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

void is_movement_down_possible(){
    Figure last_figure = figures[figures.size() - 1];
    for(int i = 0;i < figures.size() - 1;i++){
            for(int j = 0;j < 4;j++){
                for(int k = 0;k < 4;k++){
                    if(figures[i].coords[j][1] == last_figure.coords[k][1] || last_figure.coords[j][1] * BLOCK  + BLOCK== HEIGHT){
                        figures[figures.size() - 1].movement = false;
                    }
                }
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


bool is_movement_right_possible(){
    Figure last_figure = figures[figures.size() - 1];
    for(int i = 0;i < 4;i++){
            std::cout << last_figure.coords[i][0] * BLOCK << std::endl;
        if(last_figure.coords[i][0] * BLOCK + BLOCK  >= WIDTH && last_figure.movement){
            return false;
        }
    }
    return true;
}

bool is_movement_left_possible(){

    Figure last_figure = figures[figures.size() - 1];
    for(int i = 0;i < 4;i++){
            std::cout << last_figure.coords[i][0] * BLOCK << std::endl;
        if(last_figure.coords[i][0] * BLOCK <= 0 && last_figure.movement){
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
