// Sorting algorithm visualizer in C++
// @ruiesteves August 2024

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <cmath>
#include <map>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum SortAlgorithm {BUBBLE_SORT, HEAP_SORT, QUICK_SORT, MERGE_SORT, SELECTION_SORT};

// Util functions (mainly display)
sf::Color getColor(int value) {
    int r = (value * 23) % 256;
    int g = (value * 59) % 256;
    int b = (value * 97) % 256;
    return sf::Color(r, g, b);
}

void visualizeArray(sf::RenderWindow &window, const std::vector<int> &array, const sf::Font &font, const sf::Text &text, const std::map<int, sf::Color> &partitionColors = {}) {
    window.clear();

    float barWidth = 10.0f;
    float spacing = 2.0f;
    float totalWidth = array.size() * (barWidth + spacing) - spacing;
    float startX = (WINDOW_WIDTH - totalWidth) / 2;

    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, array[i]));
        bar.setPosition(startX + i * (barWidth + spacing), WINDOW_HEIGHT - array[i]);

        if (partitionColors.find(i) != partitionColors.end()) {
            bar.setFillColor(partitionColors.at(i));
        } else {
            bar.setFillColor(getColor(array[i]));
        }
        window.draw(bar);
    }
    window.draw(text);
    window.display();
}

void drawArray(sf::RenderWindow &window, const std::vector<int> &array, const sf::Font &font) {
    float squareSize = 30.0f;
    float startX = (WINDOW_WIDTH - array.size() * squareSize) / 2;
    float startY = WINDOW_HEIGHT - 100.0f;

    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
        square.setFillColor(getColor(array[i]));
        square.setOutlineThickness(2);
        square.setOutlineColor(sf::Color::Black);
        square.setPosition(startX + i * squareSize, startY);

        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(array[i]));
        valueText.setCharacterSize(14);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(startX + i * squareSize + 5, startY + 5);
        window.draw(square);
        window.draw(valueText);
    }
}


void visualizeBarsAndArrayMerge(sf::RenderWindow &window, const std::vector<int> &array, const sf::Font &font, const sf::Text &text, int pivotIndex = -1, int leftIndex = -1, int rightIndex = -1) {
    window.clear();
    float barWidth = 10.0f;
    float spacing = 2.0f;
    float totalWidth = array.size() * (barWidth + spacing) - spacing;
    float startX = (WINDOW_WIDTH - totalWidth) / 2;

    // Draw bars
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(10, array[i]));
        bar.setPosition(startX + i * (barWidth + spacing), 400 - array[i]);

        if (i == pivotIndex) {
            bar.setFillColor(sf::Color::Red);
        } else if (i == leftIndex || i == rightIndex) {
            bar.setFillColor(sf::Color::Green);
        } else {
            bar.setFillColor(sf::Color::White);
        }

        window.draw(bar);
    }

    // Draw array as squares
    float squareSize = 30.0f;
    startX = (WINDOW_WIDTH - array.size() * squareSize) / 2;
    float startY = WINDOW_HEIGHT - 100.0f;

    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
        square.setFillColor(sf::Color::White);
        square.setOutlineThickness(2);
        square.setOutlineColor(sf::Color::Black);
        square.setPosition(startX + i * squareSize, startY);

        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(array[i]));
        valueText.setCharacterSize(14);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(startX + i * squareSize + 5, startY + 5);

        window.draw(square);
        window.draw(valueText);
    }

    window.draw(text);
    window.display();
}



void visualizeBarsAndArray(sf::RenderWindow &window, const std::vector<int> &array, const sf::Font &font, const sf::Text &text, const std::map<int, sf::Color> &partitionColors = {}) {
    window.clear();
    
    float barWidth = 10.0f;
    float spacing = 2.0f;
    float totalWidth = array.size() * (barWidth + spacing) - spacing;
    float startX = (WINDOW_WIDTH - totalWidth) / 2;

    // Draw bars
    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, array[i]));
        bar.setPosition(startX + i * (barWidth + spacing), 400 - array[i]); 

        if (partitionColors.find(i) != partitionColors.end()) {
            bar.setFillColor(partitionColors.at(i));
        } else {
            bar.setFillColor(getColor(array[i]));
        }

        window.draw(bar);
    }

    // Draw array as squares
    float squareSize = 30.0f;
    startX = (WINDOW_WIDTH - array.size() * squareSize) / 2;
    float startY = WINDOW_HEIGHT - 100.0f;

    for (size_t i = 0; i < array.size(); ++i) {
        sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
        if (partitionColors.find(i) != partitionColors.end()) {
            square.setFillColor(partitionColors.at(i));
        } else {
            square.setFillColor(getColor(array[i]));
        }
        square.setOutlineThickness(2);
        square.setOutlineColor(sf::Color::Black);
        square.setPosition(startX + i * squareSize, startY);

        sf::Text valueText;
        valueText.setFont(font);
        valueText.setString(std::to_string(array[i]));
        valueText.setCharacterSize(14);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(startX + i * squareSize + 5, startY + 5);

        window.draw(square);
        window.draw(valueText);
    }

    window.draw(text);
    window.display();
}

void visualizeHeap(sf::RenderWindow &window, const std::vector<int> &array, const sf::Font &font, const sf::Text &text, int sortedIndex) {
    window.clear();

    int n = sortedIndex;
    float nodeRadius = 20.0f;
    float hGap = 40.0f;
    float vGap = 60.0f;

    std::vector<sf::Vector2f> positions(n);
    for (int i = 0; i < n; ++i) {
        float x = WINDOW_WIDTH / 2 + (i - (n / 2)) * hGap;
        float y = 100 + (int)(log2(i + 1)) * vGap;
        positions[i] = sf::Vector2f(x, y);
    }

    // Draw lines first
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            int parent = (i - 1) / 2;
            sf::Vertex line[] = {
                sf::Vertex(positions[parent]),
                sf::Vertex(positions[i])
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    for (int i = 0; i < n; ++i) {
        float x = positions[i].x;
        float y = positions[i].y;

        sf::CircleShape node(nodeRadius);
        node.setFillColor(getColor(array[i]));
        node.setOutlineThickness(2);
        node.setOutlineColor(sf::Color::Black);
        node.setPosition(x - nodeRadius, y - nodeRadius);

        sf::Text nodeValue;
        nodeValue.setFont(font);
        nodeValue.setString(std::to_string(array[i]));
        nodeValue.setCharacterSize(14);
        nodeValue.setFillColor(sf::Color::Black);
        nodeValue.setPosition(x - nodeRadius / 2, y - nodeRadius / 2);

        window.draw(node);
        window.draw(nodeValue);
    }

    drawArray(window, array, font);

    window.draw(text);
    window.display();
}

// Sorting functions
void heapify(std::vector<int> &array, int n, int i, sf::RenderWindow &window, const sf::Font &font, const sf::Text &text, int sortedIndex) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        std::swap(array[i], array[largest]);
        visualizeHeap(window, array, font, text, sortedIndex);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        heapify(array, n, largest, window, font, text, sortedIndex);
    }
}

void heapSort(sf::RenderWindow &window, std::vector<int> &array, const sf::Font &font, const sf::Text &text) {
    int n = array.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i, window, font, text, n);

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        visualizeHeap(window, array, font, text, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        heapify(array, i, 0, window, font, text, i);
    }
}

void bubbleSort(sf::RenderWindow &window, std::vector<int> &array, const sf::Font &font, const sf::Text &text) {
    std::map<int, sf::Color> partitionColors;
    sf::Color partitionColor = sf::Color::White;
    for (size_t i = 0; i < array.size(); ++i) {
        partitionColors[i] = partitionColor;
    }

    for (size_t i = 0; i < array.size() - 1; ++i) {
        for (size_t j = 0; j < array.size() - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                visualizeBarsAndArray(window, array, font, text, partitionColors);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
}

int partition(std::vector<int> &array, int low, int high, sf::RenderWindow &window, const sf::Font &font, const sf::Text &text) {
    int pivot = array[high];
    int i = low - 1;
    std::map<int, sf::Color> partitionColors;
    sf::Color partitionColor = sf::Color::White;
    for (size_t j = 0; j < array.size(); j++) {
        partitionColors[j] = partitionColor;
    }

    partitionColors[high] = sf::Color::Red;
    partitionColors[low] = sf::Color::Red;

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
            visualizeBarsAndArray(window, array, font, text, partitionColors);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    std::swap(array[i + 1], array[high]);
    visualizeBarsAndArray(window, array, font, text, partitionColors);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return i+1;
}

void quickSort(std::vector<int> &array, int low, int high, sf::RenderWindow &window, const sf::Font &font, const sf::Text &text) {
    if (low < high) {
        int pi = partition(array, low, high, window, font, text);
        quickSort(array, low, pi - 1, window, font, text);
        quickSort(array, pi + 1, high, window, font, text);
    }
}



void merge(std::vector<int> &array, int left, int mid, int right, sf::RenderWindow &window, const sf::Font &font, const sf::Text &text) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        visualizeBarsAndArrayMerge(window, array, font, text, -1, left + i, mid + 1 + j);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        visualizeBarsAndArrayMerge(window, array, font, text, -1, left + i, -1);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        visualizeBarsAndArrayMerge(window, array, font, text, -1, -1, mid + 1 + j);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &array, int left, int right, sf::RenderWindow &window, const sf::Font &font, const sf::Text &text) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid, window, font, text);
        mergeSort(array, mid + 1, right, window, font, text);
        merge(array, left, mid, right, window, font, text);
    }
}



void selectionSort(sf::RenderWindow &window, std::vector<int> &array, const sf::Font &font, const sf::Text &text) {
    int n = array.size();
    std::map<int, sf::Color> partitionColors;

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(array[minIndex], array[i]);
        sf::Color partitionColor = sf::Color::White;
        for (size_t j = 0; j < array.size(); j++) {
        partitionColors[j] = partitionColor;
    }
        partitionColors[minIndex] = sf::Color::Red;

        visualizeBarsAndArray(window, array, font, text,partitionColors);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


sf::Color generateRandomColor() {
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return sf::Color(r, g, b);
}


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Algorithm Visualizer");

    std::vector<int> array(20);
    std::srand(std::time(0)); // Initialize random seed
    std::generate(array.begin(), array.end(), []() { return rand() % 100; });

    SortAlgorithm currentAlgorithm = BUBBLE_SORT;
    bool isSorting = false;
    sf::Color partitionColor;

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    // Create text object
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 10);
    text.setString("Current Algorithm: Bubble Sort");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    currentAlgorithm = BUBBLE_SORT;
                    text.setString("Current Algorithm: Bubble Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 200; });
                    isSorting = false;
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    currentAlgorithm = HEAP_SORT;
                    text.setString("Current Algorithm: Heap Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 200; });
                    isSorting = false;
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    currentAlgorithm = QUICK_SORT;
                    text.setString("Current Algorithm: Quick Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 200; });
                    isSorting = false;
                }

                if (event.key.code == sf::Keyboard::Num4) {
                    currentAlgorithm = MERGE_SORT;
                    text.setString("Current Algorithm: Merge Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 200; });
                    isSorting = false;
                }

                if (event.key.code == sf::Keyboard::Num5) {
                    currentAlgorithm = SELECTION_SORT;
                    text.setString("Current Algorithm: Selection Sort");
                    std::generate(array.begin(), array.end(), []() { return rand() % 200; });
                    isSorting = false;
                }


                if (event.key.code == sf::Keyboard::Enter) {
                    isSorting = true;
                }
            }
        }

        if (isSorting) {
            if (currentAlgorithm == BUBBLE_SORT) {
                bubbleSort(window, array, font, text);
            } else if (currentAlgorithm == HEAP_SORT) {
                heapSort(window, array, font, text);
            } else if (currentAlgorithm == QUICK_SORT) {
                quickSort(array, 0, array.size() - 1, window, font, text);
            } else if (currentAlgorithm == MERGE_SORT) {
                mergeSort(array, 0, array.size() - 1, window, font, text);
            }  else if (currentAlgorithm == SELECTION_SORT) {
                selectionSort(window, array, font, text);
            }

            isSorting = false;
        }

        window.clear();
        if (currentAlgorithm == BUBBLE_SORT) {
            std::map<int, sf::Color> partitionColors;
            sf::Color partitionColor = sf::Color::White;
            for (size_t i = 0; i < array.size(); ++i) {
                partitionColors[i] = partitionColor;
            }
            visualizeBarsAndArray(window, array, font, text, partitionColors);
        } else if (currentAlgorithm == HEAP_SORT) {
            visualizeHeap(window, array, font, text, array.size());
        } else if (currentAlgorithm == QUICK_SORT) {
            std::map<int, sf::Color> partitionColors;
            sf::Color partitionColor = sf::Color::White;
            for (size_t i = 0; i < array.size(); ++i) {
                partitionColors[i] = partitionColor;
            }
            visualizeBarsAndArray(window, array, font, text, partitionColors);
        } else if (currentAlgorithm == MERGE_SORT) {
            std::map<int, sf::Color> partitionColors;
            sf::Color partitionColor = sf::Color::White;
            for (size_t i = 0; i < array.size(); ++i) {
                partitionColors[i] = partitionColor;
            }
            visualizeBarsAndArray(window, array, font, text, partitionColors);
        } else if (currentAlgorithm == SELECTION_SORT) {
            std::map<int, sf::Color> partitionColors;
            sf::Color partitionColor = sf::Color::White;
            for (size_t i = 0; i < array.size(); ++i) {
                partitionColors[i] = partitionColor;
            }
            visualizeBarsAndArray(window, array, font, text, partitionColors);
        }
        window.draw(text);
        window.display();
    }

    return 0;
}
