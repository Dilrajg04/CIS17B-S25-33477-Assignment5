#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

// Template class for generic package
template<typename T>
class Package {
private:
    T contents;
public:
    Package(T c) : contents(c) {}
    void label() const {
        //Generic package containing: int
        std::cout << "Generic package containing: " << typeid(T).name() << "\n";
    }
};

// Specialization for std::string
template<>
class Package<std::string> {
private:
    std::string contents;
public:
    Package(const std::string& c) : contents(c) {}
    void label() const {
        //Book package: "C++ Primer"
        std::cout << "Book package: \"" << contents << "\"\n";
    }
};

// Partial specialization for pointers
template<typename T>
class Package<T*> {
private:
    T* contents;
public:
    Package(T* c) : contents(c) {}
    void label() const {
        //Fragile package for pointer to type: double
        std::cout << "Fragile package for pointer to type: " << typeid(T).name() << "\n";
    }
};

// Template class for a box of fixed size
template<typename T, int Size>
class Crate {
private:
    std::array<T, Size> storedItems{};
    int itemCount = 0;
public:
    bool addToCrate(const T& item) {
        //Added item to box: "The Pragmatic Programmer" or "Clean Code"
        if (itemCount < Size) {
            storedItems[itemCount++] = item;
            std::cout << "Added item to box: \"" << item << "\"\n";
            return true;
        }
        std::cout << "Box is full. Cannot add item: \"" << item << "\"\n";
        return false;
    }

    void displayContents() const {
        //Box contents
        std::cout << "Box contents:\n";
        for (int i = 0; i < itemCount; ++i)
            std::cout << " - " << storedItems[i] << "\n";
    }
};

// Generic dispatchItem function
template<typename T>
void dispatchItem(const T& item) {
    //Shipping item of type: int or std::string
    std::cout << "Shipping item of type: " << typeid(T).name() << "\n";
}

// Specialization for temperature-sensitive items (double)
template<>
void dispatchItem(const double& item) {
    //Shipping temperature-controlled item: 22.5°C
    std::cout << "Shipping temperature-controlled item: " << item << "°C\n";
}

int main() {
    //Generic package containing: int
    Package<int> intParcel(42);
    intParcel.label();

    //Book package: "C++ Primer"
    Package<std::string> bookParcel("C++ Primer");
    bookParcel.label();

    //Fragile package for pointer to type: double
    double tempSensitive = 3.14;
    Package<double*> fragileParcel(&tempSensitive);
    fragileParcel.label();

    //Added item to box: "The Pragmatic Programmer" and "Clean Code"
    //Box contents
    Crate<std::string, 5> libraryCrate;
    libraryCrate.addToCrate("The Pragmatic Programmer");
    libraryCrate.addToCrate("Clean Code");
    libraryCrate.displayContents();

    //Shipping item of type: int
    dispatchItem(42);
    //Shipping item of type: std::string
    dispatchItem(std::string("std::string"));
    //Shipping temperature-controlled item: 22.5°C
    dispatchItem(22.5);

    return 0;
}

