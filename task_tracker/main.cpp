#include <iostream>
#include <string>
#include <vector>

using namespace std;

//================== Additional class TaskType ===================
class TaskType
{
private:
    string typeName;
public:
    // Конструктор
    TaskType(string name)
    {
        typeName = name;
    }

    // Геттеры
    string getTypeName() const { return typeName; }

    //question
    // Вывод информации о позиции
    void printTaskType() const
    {
        cout << typeName;
    }

    // Статические методы для создания предопределённых типов
    static TaskType createBugTask()
    {
        return TaskType("Баг");
    }

    static TaskType createFeatureTask()
    {
        return TaskType("Фича");
    }

    static TaskType createDocumentationTask()
    {
        return TaskType("Документация");
    }

    // Метод для получения позиции по строковому вводу
    static TaskType getTypeByString(const string& input)
    {
        string lowerInput = input;
        for (int i = 0; i < lowerInput.length(); i++)
        {
            lowerInput[i] = tolower(lowerInput[i]);
        }

        if (lowerInput == "Баг" || lowerInput == "баг" ||
            lowerInput == "Bug" || lowerInput == "bug")
        {
            return createBugTask();
        }
        else if (lowerInput == "Фича" || lowerInput == "фича" ||
            lowerInput == "Feature" || lowerInput == "feature")
        {
            return createFeatureTask();
        }
        else if (lowerInput == "Документация" || lowerInput == "документация" ||
            lowerInput == "Documentation" || lowerInput == "documentation")
        {
            return createDocumentationTask();
        }
        else
        {
            // По умолчанию возвращаем баг
            cout << "Тип задачи не распознан. Будет установлено значение Баг по умолчанию." << endl;
            return createBugTask();
        }
    }
};

//================== Base abstract class Task ===================
class Task {
private:
    static int nextId; // счётчик id
    int taskId; // уникальный номер id
    string taskTitle; // краткое название задачи
    string taskDescription; // подробное описание задачи
    string taskPriority; // приоритет задачи («Низкий», «Средний», «Высокий», «Критический»)
    string taskStatus; // статус задачи («Открыта», «В работе», «На проверке», «Закрыта»)
    string taskAssignee; // ФИО или имя исполнителя
    TaskType type; //композиция: задвча имеет тип
public:
    // конструктор по умолчанию
    Task() : type(TaskType::createBugTask()) {
        taskId = nextId++; // автоматическое увеличение id
        taskTitle = "New Task";
        taskDescription = "Task to be done";
        taskPriority = "High";
        taskStatus = "In progress";
        taskAssignee = "Nobody";
    }

    // контруктор
    Task(int id, string title, string description,
        string priority, string status, string assignee, const TaskType& t) : type(t)
    {
        // question
        taskId = nextId++;
        // question
        taskDescription = description;
        taskPriority = priority;
        taskStatus = status;
        taskAssignee = assignee;
    }

    ~Task() { 
        // тип уничтожается автоматически вместе с задачей
    }

    // геттеры
    string getTaskTitle() { return taskTitle; }
    string getTaskDescription() { return taskDescription; }
    string getTaskPriority() { return taskPriority; }
    string getTaskStatus() { return taskStatus; }
    string getTaskAssignee() { return taskAssignee; }
    TaskType getTaskType() const { return type; }
    
    // сеттеры
    void setTaskTitle(string title) { taskTitle = title; }
    void setTaskDescription(string description) { taskDescription = description; }
    void setTaskPriority(string priority) { taskPriority = priority; }
    void setTaskStatus(string status) { taskStatus = status; }
    void setTaskAssignee(string assignee) { taskAssignee = assignee; }

    void printDetailedInfo() {
        cout << "-----------------------------------------" << endl;
        cout << "|                Task Info              |" << endl;
        cout << "-----------------------------------------" << endl;
        cout << " Title        : " << taskTitle << endl;
        cout << " Description  : " << taskDescription << endl;
        cout << " Priority     : " << taskPriority << endl;
        cout << " Status       : " << taskStatus << endl;
        cout << " Assignee     : " << taskAssignee << endl;
        cout << " Type         : ";
        type.printTaskType();
        cout << endl;
        cout << "-----------------------------------------------" << endl;
    };

    void printCard();
    void advanceStatus();
    void reopen();

    //tester
    int getId() const { return taskId;  }
};

// Инициализация статической переменной
int Task::nextId = 1;

//================== Derived class BugTask ===================
class BugTask : Task {
private:
    string stepsToReproduce;
    string severity;
public:
    string getTaskType();
    string getDetailedInfo();
};

//================== Derived class FeatureTask ===================
class FeatureTask : Task {
private:
    string businessRequirement;
    double estimatedHours;
public:
    string getTaskType();
    string getDetailedInfo();
};

//================== Derived class DocumentationTask ===================
class DocumentationTask : Task {
private:
    string section;
    string format;
public:
    string getTaskType();
    string getDetailedInfo();
};



/*class KanbanBoard {
    vector<Column> columns; // Todo, InProgress, Done
    map<string, Task> tasks;

    void moveTask(string taskId, Column target);
    void saveToFile(string path);
    void loadFromFile(string path);
};*/

int main() {
    Task myTask1;
    cout << "id: " << myTask1.getId() << endl;
    Task myTask2;
    cout << "id: " << myTask2.getId() << endl;
    Task myTask3;
    cout << "id: " << myTask3.getId() << endl;

    myTask2.printDetailedInfo();
};
