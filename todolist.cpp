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
    
    Task(string taskName)
    {
        this->taskName = taskName;
        this->isTaskCompleted = false;
    }

    virtual ~Task()
    {
        cout << "Destructor called for the task: " << taskName << endl;
    }

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

    void addTask(Task *newTask)
    {
        tasks.push_back(newTask);
        totalTasks++;
        totalTasksPending++;
    }

    void deleteTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            if (tasks[index]->getTaskStatus())
            {
                totalTasksCompleted--;
            }
            else
            {
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

    void markTaskCompleted(int index)
    {
        if (index >= 0 && index < tasks.size() && !tasks[index]->getTaskStatus())
        {
            tasks[index]->setIsTaskCompleted();
            totalTasksCompleted++;
            totalTasksPending--;
        }
        else
        {
            cout << "Invalid index or task already completed" << endl;
        }
    }

    void viewTasks() const
    {
        int i = 0;
        for (Task *task : tasks)
        {
            cout << i + 1 << ". " << task->getTaskName() << " [Completed: " << (task->getTaskStatus() ? "Yes" : "No") << "]" << endl;

            PriorityTask *pTask = dynamic_cast<PriorityTask *>(task);
            if (pTask)
            {
                cout << "   -> Priority Level: " << pTask->getPriority() << endl;
            }

            RecurringTask *rTask = dynamic_cast<RecurringTask *>(task);
            if (rTask)
            {
                cout << "   -> Recurrence Interval: " << rTask->getRecurrenceInterval() << " days" << endl;
            }

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
    ToDoList myList;

    myList.addTask(new Task("Complete OOP Assignment"));

    myList.addTask(new PriorityTask("Prepare for Exams", 1));

    myList.addTask(new RecurringTask("Give DBMS CA-5", 2, 30));

    cout << "Total tasks: " << ToDoList::getTotalTasks() << endl;
    cout << "Tasks List:" << endl;
    myList.viewTasks();

    return 0;
}
