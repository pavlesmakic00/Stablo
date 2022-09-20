#ifndef MENU_H
#define MENU_H
#include "Tree.h"
#include <iostream>
class Menu
{
    public:
        Menu();
        void startMenu();
        virtual ~Menu();
    protected:
    private:
        static std::string notExist;
        Tree* tree;
        void printMenu();
        void loadFile(std::string filePath, std::ostream& os);
};

#endif
