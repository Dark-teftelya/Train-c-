#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

struct Train {
    int id;
    int track;
    sf::RectangleShape shape;
    bool moving = false;
    float currentX = 0.0f;
    float currentY = 0.0f;
    float targetX = 0.0f;
    float targetY = 0.0f;
    float speed = 200.0f; // Пикселей в секунду

    Train() {
        currentX = shape.getPosition().x;
        currentY = shape.getPosition().y;
    }

    void moveTo(float x, float y) {
        targetX = x;
        targetY = y;
        moving = true;
    }

    void update(float deltaTime) {
        if (moving) {
            float dx = targetX - currentX;
            float dy = targetY - currentY;
            float distance = std::sqrt(dx * dx + dy * dy);
            float step = speed * deltaTime;

            if (distance <= step) {
                currentX = targetX;
                currentY = targetY;
                moving = false;
            } else {
                currentX += dx * step / distance;
                currentY += dy * step / distance;
            }
            shape.setPosition(currentX, currentY);
        }
    }
};

class SortingYard {
public:
    void sortTrains(std::vector<Train>& input, std::vector<Train>& output) {
        output = input;
        std::sort(output.begin(), output.end(), [](Train& a, Train& b) {
            return a.id < b.id;
        });
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Train Sorting");
    sf::Clock clock; // Для анимации

    sf::Font font;
    if (!font.loadFromFile("src/OpenSans.ttf")) {
        std::cerr << "Error loading OpenSans.ttf, trying fallback..." << std::endl;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading fallback font!" << std::endl;
            return -1;
        }
    }
    std::cout << "Font loaded!" << std::endl;

    sf::Text instruction;
    instruction.setFont(font);
    instruction.setString("Enter: train_id track (e.g., 101 1)");
    instruction.setCharacterSize(18);
    instruction.setPosition(10.f, 10.f);
    instruction.setFillColor(sf::Color::Black);

    sf::Text userInputText;
    userInputText.setFont(font);
    userInputText.setString("");
    userInputText.setCharacterSize(18);
    userInputText.setPosition(10.f, 40.f);
    userInputText.setFillColor(sf::Color::Green);

    sf::Text controlsHint;
    controlsHint.setFont(font);
    controlsHint.setString("S: Sort trains | R: Reset");
    controlsHint.setCharacterSize(18);
    controlsHint.setPosition(10.f, 70.f);
    controlsHint.setFillColor(sf::Color::Black);

    std::vector<sf::Text> resultLines;
    std::string currentInput;
    std::vector<Train> trains;
    std::vector<Train> sortedTrains;
    SortingYard yard;

    // Текстовые метки для номеров путей (в правой части)
    std::vector<sf::Text> trackLabels;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // Время между кадрами

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!currentInput.empty()) {
                        currentInput.pop_back();
                    }
                } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    std::istringstream iss(currentInput);
                    int id, track;
                    if (iss >> id >> track) {
                        Train newTrain;
                        newTrain.id = id;
                        newTrain.track = track;
                        newTrain.shape.setSize(sf::Vector2f(50, 20));
                        newTrain.shape.setFillColor(sf::Color::Blue);
                        // Начальная позиция в сетке
                        size_t i = trains.size();
                        const float gridStartY = 450.f;
                        const float gridSpacingX = 60.f;
                        const float gridSpacingY = 30.f;
                        const int trainsPerRow = 4;
                        float x = 50.f + (i % trainsPerRow) * gridSpacingX;
                        float y = gridStartY + (i / trainsPerRow) * gridSpacingY;
                        newTrain.shape.setPosition(x, y);
                        newTrain.currentX = x;
                        newTrain.currentY = y;
                        trains.push_back(newTrain);

                        // Добавляем текстовую метку для пути, если она новая
                        bool trackExists = false;
                        for (const auto& label : trackLabels) {
                            if (label.getString() == "Track " + std::to_string(track)) {
                                trackExists = true;
                                break;
                            }
                        }
                        if (!trackExists) {
                            sf::Text trackLabel;
                            trackLabel.setFont(font);
                            trackLabel.setString("Track " + std::to_string(track));
                            trackLabel.setCharacterSize(18);
                            // Позиция: правая часть (x = 600), вертикально по путям
                            trackLabel.setPosition(600.f, 100.f + trackLabels.size() * 60.f);
                            trackLabel.setFillColor(sf::Color::Blue);
                            trackLabels.push_back(trackLabel);
                        }
                    }
                    currentInput.clear();
                } else if (event.text.unicode < 128) {
                    currentInput += static_cast<char>(event.text.unicode);
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    yard.sortTrains(trains, sortedTrains);
                    resultLines.clear();

                    std::map<int, std::vector<Train>> tracksMap;
                    for (auto& train : sortedTrains) {
                        tracksMap[train.track].push_back(train);
                    }

                    float baseY = 100.f;
                    float colSpacing = 200.f;
                    for (const auto& [trackNum, trainList] : tracksMap) {
                        float x = 20.f + (trackNum - 1) * colSpacing;
                        float y = baseY;
                        sf::Text header;
                        header.setFont(font);
                        header.setString("Track " + std::to_string(trackNum) + ":");
                        header.setCharacterSize(18);
                        header.setPosition(x, y);
                        header.setFillColor(sf::Color::Blue);
                        resultLines.push_back(header);
                        y += 25.f;
                        for (auto& train : trainList) {
                            sf::Text t;
                            t.setFont(font);
                            t.setString("Train ID: " + std::to_string(train.id));
                            t.setCharacterSize(16);
                            t.setPosition(x, y);
                            t.setFillColor(sf::Color::Blue);
                            resultLines.push_back(t);
                            y += 20.f;
                        }
                    }

                    // Задаем целевые позиции для анимации к правому краю
                    std::map<int, int> trackTrainCount; // Количество поездов на каждом пути
                    for (auto& train : trains) {
                        // Находим позицию метки пути
                        float trackY = 0.f;
                        for (const auto& label : trackLabels) {
                            if (label.getString() == "Track " + std::to_string(train.track)) {
                                trackY = label.getPosition().y;
                                break;
                            }
                        }
                        // Поезда выстраиваются ниже метки пути
                        float offsetY = (trackTrainCount[train.track] + 1) * 30.f;
                        trackTrainCount[train.track]++;
                        train.moveTo(650.f, trackY + offsetY);
                    }
                } else if (event.key.code == sf::Keyboard::R) {
                    trains.clear();
                    sortedTrains.clear();
                    currentInput.clear();
                    resultLines.clear();
                    trackLabels.clear(); // Очищаем метки путей
                }
            }
        }

        // Обновление поездов с учетом времени
        for (auto& train : trains) {
            train.update(deltaTime);
        }

        userInputText.setString("Input: " + currentInput);

        window.clear(sf::Color::White);
        // Отрисовка меток путей
        for (const auto& label : trackLabels) {
            window.draw(label);
        }
        window.draw(instruction);
        window.draw(userInputText);
        window.draw(controlsHint);

        for (const auto& line : resultLines) {
            window.draw(line);
        }

        for (auto& train : trains) {
            window.draw(train.shape);
        }

        window.display();
    }

    return 0;
}