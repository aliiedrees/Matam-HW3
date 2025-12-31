#include "Task.h"
#include "Person.h"
#include "TaskManager.h"
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
TaskManager::TaskManager() {
    //this->persons = new Person[10];
    for (int i = 0; i < 10; i++) {
        this->persons[i] = Person();
    }
}
void TaskManager::assignTask(const string &personName, const Task &task) {

    Task result(task.getPriority(), task.getType(), task.getDescription());
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() == personName) {
            result.setId(id);
            this->id += 1;
            this->persons[i].assignTask(result);
            return;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() == "") {
            this->persons[i] = Person(personName);
            result.setId(id);
            this->id += 1;
            this->persons[i].assignTask(result);
            return;
        }
    }
    throw(std::runtime_error("TaskManager::assignTask() failed"));
}
void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < 10; i++) {
        if (this->persons[i].getName() == personName) {
            this->persons[i].completeTask();
            break;
        }
    }
}
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if(priority <= 0) {
        return;
    }
    for (int i = 0; i < 10; i++) {
        SortedList<Task> newT  = this->persons[i].getTasks().apply([type, priority](const Task& task) {
            if (task.getType() == type) {
                int newPriority = task.getPriority() + priority;
                if (newPriority > 100) {
                    newPriority = 100;
                }
                Task result(newPriority, task.getType(), task.getDescription());
                result.setId(task.getId());
                return result;
            }
            return task;
        });
       this->persons[i].setTasks(newT);
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
    SortedList<Task> newT;
    for (int i = 0; i < 10; i++) {
        SortedList<Task> filtered = persons[i].getTasks().filter([type](const Task& task) {
            return task.getType() == type;
        });        
        for (SortedList<Task>::ConstIterator t = filtered.begin();
            t != filtered.end(); ++t) {
               newT.insert(*t);
        }
    }
    for (SortedList<Task>::ConstIterator t = newT.begin();
            t != newT.end();
            ++t) {
        cout << (*t) << endl;
    }
}