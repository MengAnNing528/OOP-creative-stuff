#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

//================== Secure input helper features ==================
string safeString()
{
    string line;
    getline(cin, line);
    while (line.empty())
    {
        cout << "String can't be empty. Try again: ";
        getline(cin, line);
    }
    return line;
}

int safeInt()
{
    int value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
            cout << "Error. Enter number: ";
        }
        else
        {
            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
            return value;
        }
    }
}

double safeDouble()
{
    double value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Enter number: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

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
        return TaskType("Bug");
    }

    static TaskType createFeatureTask()
    {
        return TaskType("Feature");
    }

    static TaskType createDocumentationTask()
    {
        return TaskType("Documentation");
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
            cout << "The task type is not recognized. The default value will be set to Bug." << endl;
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
    string taskAssignee; // ФИО или имя исполнителя
    
    enum priorityVariation { LOW, MEDIUM, HIGH, CRITICAL }; // варианты приоритета задачи
    priorityVariation prior;
    string taskPriority; // приоритет задачи («Низкий», «Средний», «Высокий», «Критический»)
    
    enum statusVariation { OPEN, IN_PROGRESS, REVIEW, CLOSED}; // варианты статуса задачи
    statusVariation stat;
    string taskStatus; // статус задачи («Открыта», «В работе», «На проверке», «Закрыта»)

    // Метод для обновления строкового представления статуса
    void updateTaskStatus() {
        switch (stat) {
        case OPEN: taskStatus = "Open"; break;
        case IN_PROGRESS: taskStatus = "In progress"; break;
        case REVIEW: taskStatus = "On review"; break;
        case CLOSED: taskStatus = "Closed"; break;
        }
    }

public:
    // конструктор по умолчанию
    Task(const string& title, const string& description,
        const string& assignee, const string& priority)
        : taskTitle(title), taskDescription(description),taskAssignee(assignee),
        taskPriority(priority), taskStatus("Open") {
        taskId = nextId++;
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
    
    // сеттеры
    void setTaskTitle(string title) { taskTitle = title; }
    void setTaskDescription(string description) { taskDescription = description; }
    void setTaskPriority(string priority) { taskPriority = priority; }
    void setTaskStatus(string status) { taskStatus = status; }
    void setTaskAssignee(string assignee) { taskAssignee = assignee; }

    virtual string getTaskType() const = 0;
    virtual string getDetailedInfo() const = 0;

    void printCard() const {
        cout << "-----------------------------------------" << endl;
        cout << " Task #" << taskId << " : " << taskTitle << " Info" << endl;
        cout << "-----------------------------------------" << endl;
        cout << " Description     : " << taskDescription << endl;
        cout << " Priority        : " << taskPriority << endl;
        cout << " Status          : " << taskStatus << endl;
        cout << " Assignee        : " << taskAssignee << endl;
        cout << " Additional Info : " << getDetailedInfo() << endl;
        cout << "-----------------------------------------------" << endl;
    };

    void advanceStatus() {
        switch (stat) {
        case OPEN:
            stat = IN_PROGRESS;
            break;
        case IN_PROGRESS:
            stat = REVIEW;
            break;
        case REVIEW:
            stat = CLOSED;
            break;
        case CLOSED:
            cout << "Task #" << taskId << " : " << taskTitle << " -- is already closed." << endl;
            return;
        }
        updateTaskStatus();
        cout << "Task #" << taskId << " : " << taskTitle << " -- was transferred to status: " << taskStatus << endl;
    };

    void reopen() {
        if (taskStatus == "CLOSED") {
            taskStatus = "OPEN";
            cout << "Task #" << taskId << " : " << taskTitle << " -- was reopened. Current status: " << taskStatus << endl;
        }
        else {
            cout << "Task #" << taskId << " : " << taskTitle << " -- is not closed yet. Current status: " << taskStatus << endl;
        };
    }

    //tester
    int getId() const { return taskId;  }
};

// Инициализация статической переменной
int Task::nextId = 1;

//================== Derived class BugTask ===================
class BugTask : public Task {
private:
    string stepsToReproduce;
    string severity;
    string getSeverityDescription() const {
        if (severity == "Cosmetic") return "Cosmetic (minor visual defect)";
        if (severity == "Normal") return "Normal (function works incorrectly)";
        if (severity == "Critical") return "Critical (system does not work)";
        if (severity == "Blocker") return "Blocker (work is completely blocked)";
        return "Неизвестно";
    }

public:
    // Конструктор
    BugTask(const string& title, const string& description,
        const string& assignee, const string& priority,
        const string& steps)
        : Task(title, description, assignee, priority),
          stepsToReproduce(steps){
            int choice;
            cout << "\n--- Bug Severity Selection ---" << endl;
            cout << "1 - Cosmetic (minor visual defect)" << endl;
            cout << "2 - Normal (feature works incorrectly)" << endl;
            cout << "3 - Critical (system does not work)" << endl;
            cout << "4 - Blocker (work is completely blocked)" << endl;
            cout << "Enter number (1-4): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    severity = "Cosmetic";
                    break;
                case 2:
                    severity = "Normal";
                    break;
                case 3:
                    severity = "Critical";
                    break;
                case 4:
                    severity = "Blocker";
                    break;
                default:
                    severity = "Normal"; // default value
                    cout << "Invalid choice! Severity set to: Normal" << endl;
            }

            cout << "Selected severity: " << getSeverityDescription() << endl;


        };

    // Деструктор
    ~BugTask() {}

    // Геттеры
    string getStepsToReproduce() const { return stepsToReproduce; }
    string getBugSeverity() const { return severity; }

    // Сеттеры
    void setStepsToReproduce(const string& steps) { stepsToReproduce = steps; }
    void setSeverity(const string& sev){severity = sev;}
    // Переопределённые методы
    string getTaskType() const override { return "Bug"; }

    string getDetailedInfo() const override {
        return "Severity: " + severity + "\n" +
               "Step by step: " + stepsToReproduce;
    }
};

//================== Derived class FeatureTask ===================
class FeatureTask : public Task{
    private:
        string 	businessRequirement;
        double  estimatedHours;

    public:
        //
        FeatureTask(const string& title, const string& description,
        const string& assignee, const string& priority,const string& text,const double& amountime ): 
        Task(title, description, assignee, priority), businessRequirement(text), estimatedHours(amountime){}

        //
        ~ FeatureTask(){}

        //
        string getBusinessRequirement() const { return businessRequirement;}
        double getEstimatedHours() const {return estimatedHours;}

        //Сеттер
        void setBusinessRequirement(const string& text ) {businessRequirement = text;}
        void setEstimatedHours(const double& amountime) {estimatedHours = amountime;}

        //Переопределённые методы
        string getTaskType() const override { return "Feature"; }

        string getDetailedInfo() const override {
            return "Business Requirement:\n" + businessRequirement + "\n" + "Estimated Hours: " + to_string(estimatedHours);
            }
};  

//================== Derived class DocumentationTask ===================
class DocumentationTask : public Task{
    private:
        string section;
        string format;
    public:
        //Конструктор
        DocumentationTask(const string& title, const string& description,
        const string& assignee, const string& priority,const string& sec,const string& form ):
        Task(title, description, assignee, priority), section(sec), format(form) {}
        //Деструктор
        ~ DocumentationTask() {}
        //Геттеры
        string getSection() const {return section;}
        string getFormat() const {return format;}
        //Сеттеры
        void setSection(const string& sec){section = sec;}
        void setFormat(const string& form){format =form;}
        //Переопределённые методы
        string getTaskType() const override {return "Documentation";}
        string getDetailedInfo() const override {return "Section of Documentation:\n " + section + " in " + format + " format";}
};
int main() {

}
