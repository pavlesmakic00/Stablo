#include "Menu.h"
#include <string>
#include <sstream>
#include <fstream>
#include <limits>

std::string Menu::notExist = "Stablo ne postoji\n";
Menu::Menu()
{
    tree = nullptr;
}
void Menu::printMenu() {

    std::cout
        << "\n===========================================\n"
        << "                  2-3-4 stabla"
        << "\n===========================================\n"
        << " (0) - Iskljuci program\n"
        << " (1) - Kreiraj stablo\n"
        << " (2) - Obrisi stablo\n"
        << " (3) - Dodaj akciju\n"
        << " (4) - Pretrazi po prioritetu\n"
        << " (5) - Brisanje po prioritetu\n"
        << " (6) - Brisanje akcije najveceg prioriteta\n"
        << " (7) - Ispisivanje stabla\n"
        << " (8) - Ispisivanje u obliku Crveno-Crnog stabla\n"
        << " (9) - Izmena prioriteta akcije\n"
        << "(10) - Ukupni broj akcija sa prioritetom\n"
        << "(11) - Ucitaj stablo iz datoteke\n"
        << "(12) - Ocisti ekran\n";
}

Menu::~Menu()
{
    if (tree != nullptr) {
        delete tree;
        tree = nullptr;
    }
}
void Menu::startMenu() {
    int c;
    using std::cout;
    using std::cin;
    using std::endl;
    system("cls");
    //system("clear");//linux
    printMenu();
    do {

        cout << "Unesite redni broj naredbe: ";
        bool r = (bool)(cin >> c);
        if (r == 0) {
            c = 100;
            cin.ignore(10000, '\n');
            cin.clear();
            std::string s;
            std::getline(cin, s);
        } else {
            cin.ignore(10000, '\n');
            cin.clear();
        }


        int p;
        std::string name;
        std::string filePath;
        int priority;
        Action* a;
        switch (c) {
            case 0:
                break;
            case 1:
                if (tree != nullptr) {
                    cout << "Stablo je vec kreirano\n";
                } else {
                    tree = new Tree();
                    cout << "Stablo je kreirano\n";
                }
                break;
            case 2:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    delete tree;
                    tree = nullptr;
                    cout << "Stablo je obrisano\n";
                }
                break;
            case 3:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << "Unesite ime i prioritet akcije\n";
                    cin >> name >> priority;
                    tree->insert(new Action(name,priority));
                }
                break;
            case 4:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << "Unesite prioritet akcije\n";
                    cin >> p;
                    a = tree->find(p);
                    if (a == nullptr) {
                        cout << "Nista nije pronadjeno\n";
                    } else {
                        cout << "Pronadjena akcija: " << *a << endl;
                    }
                }
                break;
            case 5:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << "Unesite prioritet akcije\n";
                    cin >> p;
                    a = tree->remove(p);
                    if (a == nullptr) {
                        cout << "Nista nije obrisano\n";
                    } else {
                        cout << "Obrisana akcija: " << *a << endl;
                    }
                }
                break;
            case 6:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    a = tree->removeMax();
                    if (a != nullptr) {
                        cout << "Obrisana akcija: " << *a << endl;
                        delete a;
                    }
                }
                break;
            case 7:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << *tree << endl << endl;
                }
                break;
            case 8:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << endl;
                    tree->print(cout) << endl;
                }
                break;
            case 9:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << "Unesite ime i prioritet akcije:\n";
                    cin >> name >> priority;
                    cout << "Unesite novi prioritet: ";
                    int np;
                    cin >> np;
                    tree->changePriority(name,priority,np);
                }

                break;
            case 10:
                if (tree == nullptr) {
                    cout << notExist;
                } else {
                    cout << "Unesite prioritet: ";
                    cin >> p;
                    cout << "Broj akcija sa unetim prioritetom "
                         << tree->findNumberOfElementsWithPriority(p) << endl;
                }
                break;
            case 11:
                cout << "Unesite putanju do datoteke: ";

                std::getline(cin, filePath);
                loadFile(filePath, cout);
                break;
            case 12:
                system("cls");
                //system("clear");
                printMenu();
                break;
            default:
                cout << "Nepostojeca naredba\n";
                break;
        }
    } while (c != 0);
}
void Menu::loadFile(std::string filePath, std::ostream& os) {
    if (tree != nullptr) {
        delete tree;
    }
    tree = new Tree();
    std::string line;
    std::ifstream file;
    std::string name;
    int priority;
    file.open(filePath);
    if (!file.is_open()) {
        os << "Ucitavanje neuspesno\n";
        return;
    }
    while (std::getline(file,line)) {
        std::stringstream ss(line);
        ss >> name >> priority;
        tree->insert(new Action(name,priority));
    }
    os << "Ucitavanje uspesno\n";
    file.close();
}
