#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

void visualizeArray(sf::RenderWindow &window, const std::vector<int> &array) {
    window.clear();
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(10,array[i]));
        bar.setPosition(i * 12, 600 - array[i]);
        window.draw(bar);
    }
    window.display();
}

void bubbleSort(sf::RenderWindow &window, std::vector<int> &array) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        for (size_t j = 0; j < array.size() - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j+1]);
                visualizeArray(window,array);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Algorithm Visualizer");

    std::vector<int> array(50);
    std::generate(array.begin(), array.end(), []() {return rand() % 600; });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        bubbleSort(window, array);

        window.clear();
        visualizeArray(window, array);
        window.display();
    }

    return 0;
}