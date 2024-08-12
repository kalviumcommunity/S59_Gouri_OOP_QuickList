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
        this->isTaskCompleted=true;
    }

    void setTask(string newTaskName){
       this-> taskName=newTaskName;
    }

    string getTaskName() const{
        return this->taskName;
    }

    bool getTaskStatus() const{
        return this->isTaskCompleted;
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

     Task taskArray[3] = {
        Task("Task 1: Complete till Milestone 13 in Simulated Work"),
        Task("Task 2: Complete LeetCode problems"),
        Task("Task 3: write the journal ")
        };

     cout << "Tasks from Array of Objects:" << endl;
    for (int i = 0; i < 3; i++)
    {
     cout << taskArray[i].getTaskName() << " [Completed: " << (taskArray[i].getTaskStatus() ? "Yes" : "No") << "]" << endl;
    }

    
    ToDoList myList;
    myList.addTask("Complete OOPs Assignment");
    myList.addTask("Complete all backlogs");

    cout << "Tasks:" << endl;
    myList.viewTasks();
    
    // Task task1("Complete milestones!");
    // cout << task1.getTaskName() << endl;
    // cout << (task1.getTaskStatus()? "Completed":"Not Completed") << endl;

    return 0;
}