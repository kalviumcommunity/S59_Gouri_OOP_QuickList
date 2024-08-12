#include <iostream>
#include <vector>
using namespace std;

class Task {
    private:
    string taskName;
    bool isTaskCompleted;

    public:
    Task(string name):taskName(name),isTaskCompleted(false){}

    void setIsTaskCompleted(){
        isTaskCompleted=true;
    }

    void setTask(string newTaskName){
        taskName=newTaskName;
    }

    string getTaskName() const{
        return taskName;
    }

    bool getTaskStatus() const{
        return isTaskCompleted;
    }
};

class ToDoList {
private:
    vector<Task> tasks;

public:
void addTask(string taskName) {
        Task newTask(taskName);
        tasks.push_back(newTask);
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            cout << "Invalid index" << endl;
        }
    }

    void viewTasks() const {
        for (int i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].getTaskName()  << " [Completed: " << (tasks[i].getTaskStatus() ? "Yes" : "No") << "]" << endl;
        }
    }
};

int main() {
    //ToDoList class
    ToDoList myList;
    myList.addTask("Complete OOPs Assignment");
    myList.addTask("Complete all backlogs");

    cout << "Tasks:" << endl;
    myList.viewTasks();
    
    Task task1("Complete milestones!");
    cout << task1.getTaskName() << endl;
    cout << task1.getTaskStatus() << endl;

    return 0;
}