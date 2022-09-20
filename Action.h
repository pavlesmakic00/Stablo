#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <iostream>
class Action
{
    public:
        Action(std::string name, int priority);
        virtual ~Action();

        int getPriority() const;
        void setPriority(int p);
        std::string getName() const;


        friend bool operator<(Action const&, Action const&);
        friend bool operator>(Action const&, Action const&);
        friend bool operator<=(Action const&, Action const&);
        friend bool operator<=(Action const&, Action const&);
        friend bool operator==(Action const&, Action const&);
        friend bool operator!=(Action const&, Action const&);
        friend std::ostream& operator<<(std::ostream&, Action const&);
    private:
        std::string name;
        int priority;

};

#endif 
