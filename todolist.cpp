#include <iostream>
#include <vector>
using namespace std;

class Task
{
protected:
    string taskName;
    bool isTaskCompleted;

public:
    Task() : taskName("Unnamed Task"), isTaskCompleted(false) 
    {
        cout << "Default Constructor called for Task: " << taskName << endl;
    }
    
   
    Task(string taskName) : taskName(taskName), isTaskCompleted(false) {}

    virtual ~Task()
    {
        cout << "Destructor called for the task: " << taskName << endl;
    }

     virtual void displayTaskDetails() const = 0; 

    void setIsTaskCompleted()
    {
        if (!this->isTaskCompleted)
        {
            this->isTaskCompleted = true;
        }
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

class PriorityTask : public Task
{
private:
    int priorityLevel;

public:
    PriorityTask() : Task("Unnamed Priority Task"), priorityLevel(2)
    {
        cout << "PriorityTask Default Constructor called." << endl;
    }
    
    PriorityTask(string name, int priority) : Task(name), priorityLevel(priority)
    {
        cout << "PriorityTask Constructor called for Task: " << taskName << " with Priority: " << priorityLevel << endl;
    }

    ~PriorityTask()
    {
        cout << "Destructor called for PriorityTask: " << taskName << endl;
    }

    void setPriority(int level)
    {
        if (level >= 1 && level <= 3)
            priorityLevel = level;
        else
            cout << "Invalid priority level. Set it to 1 (High), 2 (Medium), or 3 (Low)." << endl;
    }

    int getPriority() const
    {
        return priorityLevel;
    }

     void displayTaskDetails() const override
    {
        cout << "Task: " << taskName << " | Priority Level: " << priorityLevel 
             << " | Completed: " << (isTaskCompleted ? "Yes" : "No") << endl;
    }
};

class RecurringTask : public PriorityTask
{
private:
    int recurrenceInterval; 

public:
    RecurringTask(string name, int priority, int interval)
        : PriorityTask(name, priority), recurrenceInterval(interval) 
    {
        cout << "RecurringTask Constructor called for Task: " << taskName << " with Interval: " << recurrenceInterval << " days." << endl;
    }

    ~RecurringTask()
    {
        cout << "Destructor called for RecurringTask: " << taskName << endl;
    }

    int getRecurrenceInterval() const
    {
        return recurrenceInterval;
    }

    void setRecurrenceInterval(int interval)
    {
        recurrenceInterval = interval;
    }

    void displayTaskDetails() const override
    {
        cout << "Task: " << getTaskName() << " | Priority: " << getPriority() 
             << " | Recurrence Interval: " << recurrenceInterval 
             << " days | Completed: " << (getTaskStatus() ? "Yes" : "No") << endl;
    }
};

class TaskStatistics
{
private:
    static int totalTasks;
    static int totalTasksCompleted;
    static int totalTasksPending;

public:
    static void incrementTotalTasks() { totalTasks++; totalTasksPending++; }
    static void decrementTotalTasks(bool isCompleted)
    {
        totalTasks--;
        if (isCompleted)
            totalTasksCompleted--;
        else
            totalTasksPending--;
    }
    static void markTaskCompleted()
    {
        totalTasksCompleted++;
        totalTasksPending--;
    }
    static int getTotalTasks() { return totalTasks; }
    static int getTotalTasksCompleted() { return totalTasksCompleted; }
    static int getTotalTasksPending() { return totalTasksPending; }
};

int TaskStatistics::totalTasks = 0;
int TaskStatistics::totalTasksCompleted = 0;
int TaskStatistics::totalTasksPending = 0;

class ToDoList
{
private:
    vector<Task *> tasks;
    

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

    void addTask(Task *newTask)
    {
        tasks.push_back(newTask);
        TaskStatistics::incrementTotalTasks();
    }


    void deleteTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            bool isCompleted = tasks[index]->getTaskStatus();
            TaskStatistics::decrementTotalTasks(isCompleted);
            delete tasks[index];
            tasks.erase(tasks.begin() + index);
        }
        else
        {
            cout << "Invalid index" << endl;
        }
    }

    void markTaskCompleted(int index)
    {
        if (index >= 0 && index < tasks.size() && !tasks[index]->getTaskStatus())
        {
            tasks[index]->setIsTaskCompleted();
            TaskStatistics::markTaskCompleted();
        }
        else
        {
            cout << "Invalid index or task already completed" << endl;
        }
    }

    void viewTasks() const
    {
         for (const Task *task : tasks)
        {
            task->displayTaskDetails(); 
        }

    }
};


int main()
{
    ToDoList myList;

    myList.addTask(new PriorityTask("Complete OOP Assignment",2));

    myList.addTask(new PriorityTask("Prepare for Exams", 1));

    myList.addTask(new RecurringTask("Give DBMS CA-5", 2, 30));

    cout << "Total tasks: " << TaskStatistics::getTotalTasks() << endl;
    cout << "Tasks List:" << endl;
    myList.viewTasks();

    myList.markTaskCompleted(0);
    cout << "\nAfter marking task 1 as completed:" << endl;
    myList.viewTasks();

    cout << "\nStatistics:" << endl;
    cout << "Total Tasks: " << TaskStatistics::getTotalTasks() << endl;
    cout << "Completed Tasks: " << TaskStatistics::getTotalTasksCompleted() << endl;
    cout << "Pending Tasks: " << TaskStatistics::getTotalTasksPending() << endl;

    return 0;
}
