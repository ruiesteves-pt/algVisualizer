#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

enum SortAlgorithm { BUBBLE_SORT, HEAP_SORT };

// Utils
void visualizeArray(sf::RenderWindow &window, const std::vector<int> &array) {
    window.clear();
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(10,array[i]));
        bar.setPosition(i * 12, 600 - array[i]);
        window.draw(bar);
    }
    window.display();
}

// Sorting Algorithms
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

void heapify(std::vector<int> &array, int n, int i, sf::RenderWindow &window) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && array[left] > array[largest]) {
        largest = left;
    }

    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(array[i], array[largest]);
        visualizeArray(window, array);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        heapify(array, n, largest, window);
    }
}


void heapSort(sf::RenderWindow &window, std::vector<int> &array) {
    int n = array.size();

    for (int i = n / 2 -1; i >=0; i--) {
        heapify(array, n, i, window);
    }

    for (int i = n - 1; i > 0; i--){
        std::swap(array[0], array[i]);
        visualizeArray(window, array);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        heapify(array, i, 0, window);
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Algorithm Visualizer");

    std::vector<int> array(50);
    std::generate(array.begin(), array.end(), []() {return rand() % 600; });

    SortAlgorithm currentAlgorithm = BUBBLE_SORT;
    bool isSorting = false;

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
       return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10,10);
    text.setString("Current Algorithm: Bubble Sort");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    currentAlgorithm = BUBBLE_SORT;
                    text.setString("Current Algorithm: Bubble Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 600;});
                    isSorting = false;
                }

                if (event.key.code == sf::Keyboard::Num2) {
                    currentAlgorithm = HEAP_SORT;
                    text.setString("Current Algorithm: Heap Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 600;});
                    isSorting = false;
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    isSorting = true;
                }
            }
            
        }

        if (isSorting) {
            if (currentAlgorithm == BUBBLE_SORT) {
                bubbleSort(window, array);
            } else if (currentAlgorithm == HEAP_SORT) {
                heapSort(window, array);
            }
            isSorting = false;
        }

        window.clear();
        visualizeArray(window, array);
        window.draw(text);
        window.display();
    }

    return 0;
}