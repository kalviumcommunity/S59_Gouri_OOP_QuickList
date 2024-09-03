#include <iostream>
#include <vector>
using namespace std;

class Task
{
private:
    string taskName;
    bool isTaskCompleted;

public:
    // Task(string name):taskName(name),isTaskCompleted(false){}
    Task(string taskName)
    {
        this->taskName = taskName;
        this->isTaskCompleted = false;
    }

    void setIsTaskCompleted()
    {
        this->isTaskCompleted = true;
    }

    void setTask(string newTaskName)
    {
        this->taskName = newTaskName;
    }

    string getTaskName() const
    {
        return this->taskName;
    }

    bool getTaskStatus() const
    {
        return this->isTaskCompleted;
    }
};

class ToDoList
{
private:
    vector<Task *> tasks;

public:
    void addTask(string taskName)
    {
        Task *newTask = new Task(taskName);
        tasks.push_back(newTask);
    }

    void deleteTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            delete (tasks[index]);
            tasks.erase(tasks.begin() + index);
        }
        else
        {
            cout << "Invalid index" << endl;
        }
    }

    void viewTasks() const
    {
        int i = 0;
        for (Task *task : tasks)
        {
            cout << i + 1 << ". " << task->getTaskName() << " [Completed: " << (task->getTaskStatus() ? "Yes" : "No") << "]" << endl;
            i++;
        }
    }
};

int main()
{

    Task *taskArray[3] = {
        new Task("Task 1: Complete till Milestone 13 in Simulated Work"),
        new Task("Task 2: Complete LeetCode problems"),
        new Task("Task 3: write the journal ")};

    cout << "Tasks from Array of Objects:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << taskArray[i]->getTaskName() << " [Completed: " << (taskArray[i]->getTaskStatus() ? "Yes" : "No") << "]" << endl;
        delete taskArray[i];
    }

    ToDoList myList;
    myList.addTask("Complete OOPs Assignment");
    myList.addTask("Complete all backlogs");

    cout << "Tasks Before deletion:" << endl;
    myList.viewTasks();
    cout << "====================================" << endl;
    myList.deleteTask(0);
    cout << "Tasks After deletion:" << endl;
    myList.viewTasks();

    // Task task1("Complete milestones!");
    // cout << task1.getTaskName() << endl;
    // cout << (task1.getTaskStatus()? "Completed":"Not Completed") << endl;

    return 0;
}