#define GRAPHICAL_USE 1

#ifdef GRAPHICAL_USE

#ifdef _WIN32
    #include "SFML/include/SFML/Graphics.hpp"
#else
    #include "SFML/Graphics.hpp"
#endif

#include "memory"
#include "vector"
#include "Structdorobo.h"
#include "string"
#include "chrono"
#include "math.h"

#ifndef GRAPHICS_INCLUDE_H
#define GRAPHICS_INCLUDE_H

#define GAME_WIDTH 150
#define GAME_HEIGHT 130
#define AREA_SIZE_H 70.0f
#define AREA_SIZE_W 15.0f

#define RENDER_COEFICIENT 6

class Graphics {
    public:
        Graphics(std::shared_ptr<Object<void*>> ball) {
            window = std::make_unique<sf::RenderWindow>(sf::VideoMode(GAME_WIDTH * RENDER_COEFICIENT, GAME_HEIGHT * RENDER_COEFICIENT), "VSSS");
            window->setFramerateLimit(60);
            this->ball = ball;
        };
        ~Graphics();
        void render() {
            event_code = ' ';
            window->clear();
            sf::Event event;
            while(window->pollEvent(event)) {
                if(event.type == sf::Event::Closed) window->close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                event_code = 'R';
            }
            drawMap();
            RectCollider ballColider = {ball->pos.x, ball->pos.y};
            sf::RectangleShape ballColliderRepresentation(sf::Vector2f(RENDER_COEFICIENT * ballColider.width, RENDER_COEFICIENT * ballColider.height));
            ballColliderRepresentation.setPosition(sf::Vector2f(RENDER_COEFICIENT * ballColider.x, RENDER_COEFICIENT * ballColider.y));
            ballColliderRepresentation.setFillColor(sf::Color(255,255,255,128));
            ballColliderRepresentation.setOutlineColor(sf::Color::Red);
            sf::CircleShape ballRepresentation(2.135 * RENDER_COEFICIENT);
            ballRepresentation.setPosition(sf::Vector2f(ball->pos.x * RENDER_COEFICIENT, ball->pos.y * RENDER_COEFICIENT));
            ballRepresentation.setFillColor(sf::Color(255,127,80));
            for(Object<Robot>* _robot : robots) {
                sf::RectangleShape shape(sf::Vector2f(8 * RENDER_COEFICIENT, 8 * RENDER_COEFICIENT));
                shape.setPosition(sf::Vector2f(_robot->pos.x * RENDER_COEFICIENT, _robot->pos.y * RENDER_COEFICIENT));
                shape.setFillColor(sf::Color(_robot->includedData.color.r, 
                _robot->includedData.color.g, 
                _robot->includedData.color.b));
                shape.setOrigin(sf::Vector2f(4.f * RENDER_COEFICIENT, 4.f * RENDER_COEFICIENT));
                shape.setRotation(_robot->forward);
                window->draw(shape);
            }
            window->draw(ballRepresentation);
            window->draw(ballColliderRepresentation);
            drawScores();
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

        void drawScores() {
            std::cout << "Draw text" << std::endl;
            sf::Font font;
            if(!font.loadFromFile("./arial.ttf")) {
                std::cout << "Erro em carregar a fonte" << std::endl;
                exit(0);
            }
            else {
                sf::Text scoresRepresentation;
                std::string chars;
                chars.append(std::to_string(score1));
                chars += ':';
                chars.append(std::to_string(score2));
                scoresRepresentation.setFont(font);
                scoresRepresentation.setString(chars);
                scoresRepresentation.setPosition(sf::Vector2f(71.86 * RENDER_COEFICIENT, 15 * RENDER_COEFICIENT));
                scoresRepresentation.setCharacterSize(36);
                scoresRepresentation.setFillColor(sf::Color::White);
                window->draw(scoresRepresentation);
                sf::Text timer;
                std::string timer_string;
                timer_string.append(std::to_string(time_intpart));
                timer_string.append(":");
                timer_string.append(std::to_string(time_flt_part));
                timer.setFont(font);
                timer.setString(timer_string);
                timer.setPosition(sf::Vector2f(71.86 * RENDER_COEFICIENT, 10 * RENDER_COEFICIENT));
                timer.setCharacterSize(36);
                timer.setFillColor(sf::Color::White);
                //window->draw(timer);
            }
        }

        void setScores(int score1, int score2) {
            this->score1 = score1;
            this->score2 = score2;
        }

        void setTimer(float timer) {
            time -= timer;
            float temp_time = time / 60;
            time_flt_part = modf(temp_time, &time_intpart);
            time_flt_part *= 60;
        }

        char getEventCode() {
            return event_code;
        }
    private:
        std::unique_ptr<sf::RenderWindow> window;
        std::vector<Object<Robot>*> robots;
        std::shared_ptr<Object<void*>> ball;
        Color _team1Color;
        Color _team2Color;
        int score1, score2;
        double time = 300.f;
        double time_intpart = 0, time_flt_part = 0;
        int index = 0;
        char event_code = ' ';
};

#endif

#endif