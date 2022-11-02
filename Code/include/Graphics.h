#define GRAPHICAL_USE 1

#ifdef GRAPHICAL_USE

#include "SFML/Graphics.hpp"
#include "memory"
#include "vector"
#include "Structdorobo.h"

#ifndef GRAPHICS_INCLUDE_H
#define GRAPHICS_INCLUDE_H

#define GAME_WIDTH 150
#define GAME_HEIGHT 130
#define AREA_SIZE_H 70.0f
#define AREA_SIZE_W 15.0f

#define RENDER_COEFICIENT 8

class Graphics {
    public:
        Graphics(std::shared_ptr<Object<void*>> ball) {
            window = std::make_unique<sf::RenderWindow>(sf::VideoMode(GAME_WIDTH * RENDER_COEFICIENT, GAME_HEIGHT * RENDER_COEFICIENT), "VSSS");
            window->setFramerateLimit(60);
            this->ball = ball;
        };
        ~Graphics();
        void render() {
            window->clear();
            sf::Event event;
            while(window->pollEvent(event)) {
                if(event.type == sf::Event::Closed) window->close();
            }
            drawMap();
            sf::CircleShape ballRepresentation(3 * RENDER_COEFICIENT);
            ballRepresentation.setPosition(sf::Vector2f(ball->pos.x * RENDER_COEFICIENT, ball->pos.y * RENDER_COEFICIENT));
            ballRepresentation.setFillColor(sf::Color(255,127,80));
            for(Object<Robot>* _robot : robots) {
                sf::RectangleShape shape(sf::Vector2f(10 * RENDER_COEFICIENT, 10 * RENDER_COEFICIENT));
                shape.setPosition(sf::Vector2f(_robot->pos.x * RENDER_COEFICIENT, _robot->pos.y * RENDER_COEFICIENT));
                shape.setFillColor(sf::Color(238,130,238));
                window->draw(shape);
            }
            window->draw(ballRepresentation);
            window->display();
        }
        void trackRobot(Object<Robot>* robot) {
            robots.push_back(robot);
        }

        void drawMap() {
            sf::RectangleShape centralLine(sf::Vector2f(1.0f, GAME_HEIGHT * RENDER_COEFICIENT));
            centralLine.setOutlineColor(sf::Color::White);
            centralLine.setPosition(sf::Vector2f(GAME_WIDTH * RENDER_COEFICIENT / 2, 0));
            sf::RectangleShape area1(sf::Vector2f(AREA_SIZE_W * RENDER_COEFICIENT, AREA_SIZE_H * RENDER_COEFICIENT));
            area1.setOutlineColor(sf::Color::White);
            area1.setPosition(sf::Vector2f(0, GAME_HEIGHT * RENDER_COEFICIENT / 2 - (RENDER_COEFICIENT * (AREA_SIZE_H / 2))));
            area1.setFillColor(sf::Color::Black);
            area1.setOutlineThickness(1.0f);
            sf::RectangleShape area2(sf::Vector2f(AREA_SIZE_W * RENDER_COEFICIENT, AREA_SIZE_H * RENDER_COEFICIENT));
            area2.setOutlineColor(sf::Color::White);
            area2.setPosition(sf::Vector2f(GAME_WIDTH * RENDER_COEFICIENT - AREA_SIZE_W * RENDER_COEFICIENT, 
            GAME_HEIGHT * RENDER_COEFICIENT / 2 - (RENDER_COEFICIENT * (AREA_SIZE_H / 2))));
            area2.setFillColor(sf::Color::Black);
            area2.setOutlineThickness(1.0f);
            sf::CircleShape centralCircle(20 * RENDER_COEFICIENT);
            centralCircle.setPosition(sf::Vector2f(GAME_WIDTH * RENDER_COEFICIENT / 2 - (20 * RENDER_COEFICIENT), GAME_HEIGHT * RENDER_COEFICIENT / 2 - (20 * RENDER_COEFICIENT)));
            centralCircle.setOutlineColor(sf::Color::White);
            centralCircle.setFillColor(sf::Color::Black);
            centralCircle.setOutlineThickness(2.0f);
            window->draw(centralCircle);
            window->draw(centralLine);
            window->draw(area1);
            window->draw(area2);
        }
    private:
        std::unique_ptr<sf::RenderWindow> window;
        std::vector<Object<Robot>*> robots;
        std::shared_ptr<Object<void*>> ball;
};

#endif

#endif