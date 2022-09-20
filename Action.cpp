#include "Action.h"
#include <iostream>

Action::~Action(){

}
Action::Action(std::string name, int priority):
    name(name),
    priority(priority)
{}

int Action::getPriority() const {
    return priority;
}

void Action::setPriority(int p) {
    priority = p;
}

std::string Action::getName() const {
    return name;
}
bool operator<(Action const& a1, Action const& a2) {
    if (a1.priority == a2.priority) {
        return a1.name < a2.name;
    }
    return a1.priority < a2.priority;
}
bool operator==(Action const& a1, Action const& a2) {
    return (a1.priority == a2.priority) && (a1.name == a2.name);
}

bool operator<=(Action const& a1, Action const& a2) {
    return (a1 == a2) || (a1 < a2);
}
bool operator>(Action const& a1, Action const& a2) {
    return !(a1 <= a2);
}
bool operator>=(Action const& a1, Action const& a2) {
    return (a1 > a2) || (a1 == a2);
}

bool operator!=(Action const& a1, Action const& a2) {
    return !(a1 == a2);
}
std::ostream& operator<<(std::ostream& os, Action const&action) {
    os << action.name << "(" << action.priority << ")";
    return os;
}
