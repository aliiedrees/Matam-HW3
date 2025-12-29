#include "Task.h"
#include "Person.h"
#include "TaskManager.h"
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
TaskManager::TaskManager() {
    this->persons = new Person[10];
    for (int i = 0; i < 10; i++) {
        this->persons[i] = Person();
    }
}
void TaskManager::assignTask(const string &personName, const Task &task) {
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() == personName) {
            this->persons[i].assignTask(task);
            return;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() == "") {
            this->persons[i] = Person(personName);
            this->persons[i].assignTask(task);
            return;
        }
    }
    throw(std::runtime_error("TaskManager::assignTask() failed"));
}
void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() == personName) {
            this->persons[i].completeTask();
        }
    }
}
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if(priority <= 0) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        for( SortedList<Task>::ConstIterator t = persons[i].getTasks().begin();
            t != persons[i].getTasks().end();
            ++t) {
            if((*t).getType() == type) {
                SortedList<Task> newT  = this->persons[i].getTasks();
                Task temp = Task((*t).getPriority() + priority,(*t).getType() , (*t).getDescription());
                temp.setId((*t).getId());
                newT.remove(t);
                newT.insert(temp);
            }
        }
    }
}
void TaskManager::printAllEmployees() const {
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() != "") {
            cout << this->persons[i] << endl;
        }
    }
}
void TaskManager::printAllTasks() const {
    SortedList<Task> newT = this->persons[0].getTasks();
    for (int i = 1; i < 10; i++) {
        for (SortedList<Task>::ConstIterator t = persons[i].getTasks().begin();
            t != persons[i].getTasks().end();
            ++t) {
            newT.insert(*t);
        }
        }
    for (SortedList<Task>::ConstIterator t = newT.begin();
            t != newT.end();
            ++t) {
        cout << (*t) << endl;
    }
    }
void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> newT = this->persons[0].getTasks();
    for (int i = 1; i < 10; i++) {
        for (SortedList<Task>::ConstIterator t = persons[i].getTasks().begin();
            t != persons[i].getTasks().end();
            ++t) {
if((*t).getType() == type) {newT.insert(*t);
            }
    }
    for (SortedList<Task>::ConstIterator t = newT.begin();
            t != newT.end();
            ++t) {
        cout << (*t) << endl;
            }
}
}