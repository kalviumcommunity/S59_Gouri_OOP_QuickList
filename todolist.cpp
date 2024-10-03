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
        Task() : taskName("Unnamed Task"), isTaskCompleted(false) 
    {
        cout << "Default Constructor called for Task: " << taskName << endl;
    }
    
    Task(string taskName)
    {
        this->taskName = taskName;
        this->isTaskCompleted = false;
    }


~Task()
{
    cout<<"Destructor called for the task: "<<taskName<<endl;
}
    void setIsTaskCompleted()
    {
        if (!this->isTaskCompleted){
        this->isTaskCompleted = true;
        }
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
    static int totalTasks;
    static int totalTasksCompleted;
    static int totalTasksPending;

public:

    ToDoList() 
    {
        cout << "ToDoList created. Default Constructor called." << endl;
    }
    
    ~ToDoList() 
    {
        for (Task *task : tasks) 
        {
            delete task;
        }
        cout << "ToDoList Destructor called. All tasks are deleted." << endl;
    }
    
    void addTask(string taskName)
    {
        Task *newTask = new Task(taskName);
        tasks.push_back(newTask);
        totalTasks++;
        totalTasksPending++;
    }

    void deleteTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
             if (tasks[index]->getTaskStatus()) {  
                totalTasksCompleted--;            
            } else {
                totalTasksPending--;              
            }
            totalTasks--;
            delete (tasks[index]);
            tasks.erase(tasks.begin() + index);
        }
        else
        {
            cout << "Invalid index" << endl;
        }


    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size() && !tasks[index]->getTaskStatus()) {
            tasks[index]->setIsTaskCompleted();  
            totalTasksCompleted++;               
            totalTasksPending--;                 
        } else {
            cout << "Invalid index or task already completed" << endl; 
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

     static int getTotalTasks()
    {
        return totalTasks;
    }

    static int getTotalTasksCompleted()
    {
        return totalTasksCompleted;
    }

    static int getTotalTasksPending()
    {
        return totalTasksPending;
    }
};

int ToDoList::totalTasks = 0;
int ToDoList::totalTasksCompleted = 0;
int ToDoList::totalTasksPending = 0;


int main()
{



    // Task *taskArray[3] = {
    //     new Task("Task 1: Complete till Milestone 13 in Simulated Work"),
    //     new Task("Task 2: Complete LeetCode problems"),
    //     new Task("Task 3: write the journal ")};
    

    // cout << "Tasks from Array of Objects:" << endl;
    // for (int i = 0; i < 3; i++)
    // {
    //     cout << taskArray[i]->getTaskName() << " [Completed: " << (taskArray[i]->getTaskStatus() ? "Yes" : "No") << "]" << endl;
    //     delete taskArray[i];
    // }


    ToDoList myList;
    myList.addTask("Complete OOPs Assignment");
    myList.addTask("Complete all backlogs");
    
    cout << "Total tasks:" << myList.getTotalTasks() << endl;
    cout << "Tasks Before deletion:" << endl;
    myList.viewTasks();
     cout << "====================================" << endl;
    myList.markTaskCompleted(0);
    cout << "Tasks After Marking them as completed:" << endl;
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