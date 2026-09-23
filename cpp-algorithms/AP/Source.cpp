#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

// Функція для обчислення значення y
float func(float x) {
    return std::abs(std::sin(x)) + std::cos(std::abs(x));
}

void drawAxes(sf::RenderWindow& window, sf::Vector2f origin, float x_scale, float y_scale, float x_min, float x_max, float y_min, float y_max, sf::Font& font) {
    sf::Vertex x_axis[] = {
        sf::Vertex(sf::Vector2f(0, origin.y), sf::Color::Black),
        sf::Vertex(sf::Vector2f(800, origin.y), sf::Color::Black)
    };
    sf::Vertex y_axis[] = {
        sf::Vertex(sf::Vector2f(origin.x, 0), sf::Color::Black),
        sf::Vertex(sf::Vector2f(origin.x, 600), sf::Color::Black)
    };
    window.draw(x_axis, 2, sf::Lines);
    window.draw(y_axis, 2, sf::Lines);

    // Малювання чисел на осі X
    for (float x = x_min; x <= x_max; x += (x_max - x_min) / 10.0f) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(static_cast<int>(x)));
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Black);
        float posX = origin.x + (x - (x_min + x_max) / 2.0f) * x_scale;
        text.setPosition(posX, origin.y + 5);
        window.draw(text);
    }

    // Малювання чисел на осі Y
    for (float y = y_min; y <= y_max; y += (y_max - y_min) / 10.0f) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(static_cast<int>(y)));
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Black);
        float posY = origin.y - (y - (y_min + y_max) / 2.0f) * y_scale;
        text.setPosition(origin.x + 5, posY);
        window.draw(text);
    }
}

int main() {
    // Ініціалізація вікна
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph of y = |sin(x)| + cos(|x|)");

    float x_min, x_max;
    std::cout << "Enter the minimum value of x: ";
    std::cin >> x_min;
    std::cout << "Enter the maximum value of x: ";
    std::cin >> x_max;

    const int num_points = 1000;
    std::vector<sf::Vertex> graph(num_points);

    // Обчислення значень функції
    float y_min = func(x_min);
    float y_max = y_min;
    float dx = (x_max - x_min) / (num_points - 1);

    for (int i = 0; i < num_points; ++i) {
        float x = x_min + i * dx;
        float y = func(x);
        graph[i] = sf::Vertex(sf::Vector2f(x, y));
        if (y < y_min) y_min = y;
        if (y > y_max) y_max = y;
    }

    float x_scale = 800.0f / (x_max - x_min);
    float y_scale = 600.0f / (y_max - y_min);

    sf::Vector2f origin(400, 300);
    sf::Vector2f graph_origin((x_min + x_max) / 2.0f, (y_min + y_max) / 2.0f);

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\PC\\OneDrive\\Рабочий стол\\TEST\\arialmt.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Управління графіком
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    origin.x += 10;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    origin.x -= 10;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    origin.y += 10;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    origin.y -= 10;
                }
                else if (event.key.code == sf::Keyboard::Add) {
                    x_scale *= 1.1f;
                    y_scale *= 1.1f;
                }
                else if (event.key.code == sf::Keyboard::Subtract) {
                    x_scale /= 1.1f;
                    y_scale /= 1.1f;
                }
            }
        }

        window.clear(sf::Color::White);

        drawAxes(window, origin, x_scale, y_scale, x_min, x_max, y_min, y_max, font);

        // Малювання графіка
        for (int i = 0; i < num_points - 1; ++i) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(origin.x + (graph[i].position.x - graph_origin.x) * x_scale, origin.y - (graph[i].position.y - graph_origin.y) * y_scale), sf::Color::Red),
                sf::Vertex(sf::Vector2f(origin.x + (graph[i + 1].position.x - graph_origin.x) * x_scale, origin.y - (graph[i + 1].position.y - graph_origin.y) * y_scale), sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}