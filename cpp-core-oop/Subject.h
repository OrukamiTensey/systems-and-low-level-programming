#ifndef HEALTH_APP_SUBJECT_H
#define HEALTH_APP_SUBJECT_H

#include <vector>
#include <algorithm>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    virtual ~Subject() = default;

    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);

    void notifyObservers();
};

#endif