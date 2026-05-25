#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>

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
        stat = OPEN;  
        prior = MEDIUM;
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
        if (taskStatus == "Closed"){
           stat = OPEN;
           updateTaskStatus();
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
class BugTask : public Task {
private:
    string stepsToReproduce;
    string severity;
    string getSeverityDescription() const {
        if (severity == "Cosmetic") return "Cosmetic (minor visual defect)";
        if (severity == "Normal") return "Normal (function works incorrectly)";
        if (severity == "Critical") return "Critical (system does not work)";
        if (severity == "Blocker") return "Blocker (work is completely blocked)";
        return "Unknown";
    }
     void selectSeverity() {
        int choice;
        bool validInput = false;
        
        while (!validInput) {
            cout << "\n--- Bug Severity Selection ---" << endl;
            cout << "1 - Cosmetic (minor visual defect)" << endl;
            cout << "2 - Normal (feature works incorrectly)" << endl;
            cout << "3 - Critical (system does not work)" << endl;
            cout << "4 - Blocker (work is completely blocked)" << endl;
            cout << "Enter number (1-4): ";
            
            cin >> choice;
            
            // Проверка на ошибки ввода
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR: Please enter a number (1-4)!" << endl;
                continue;
            }
            
            // Проверка диапазона
            switch (choice) {
                case 1:
                    severity = "Cosmetic";
                    validInput = true;
                    break;
                case 2:
                    severity = "Normal";
                    validInput = true;
                    break;
                case 3:
                    severity = "Critical";
                    validInput = true;
                    break;
                case 4:
                    severity = "Blocker";
                    validInput = true;
                    break;
                default:
                    cout << "ERROR: Invalid choice! Please enter a number between 1 and 4." << endl;
                    // Не очищаем cin, так как choice уже прочитан корректно, но вне диапазона
                    break;
            }
        }
        
        cout << "Selected severity: " << getSeverityDescription() << endl;
     }

public:
    // Конструктор
    BugTask(const string& title, const string& description,
        const string& assignee, const string& priority,
        const string& steps)
        : Task(title, description, assignee, priority),
          stepsToReproduce(steps){
            selectSeverity();
        }

           

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
vector<Task*> allTasks;

//================== Helper functions ==================
Task* findTaskById(int id) {
    for (auto task : allTasks) {
        if (task->getId() == id) {
            return task;
        }
    }
    return nullptr;
}

// 1. Create task
void createTask() {
    cout << "\n=== Create New Task ===\n";
    cout << "Select task type:\n";
    cout << "1. Bug\n";
    cout << "2. Feature\n";
    cout << "3. Documentation\n";
    cout << "Your choice: ";
    int type = safeInt();
    
    cout << "Enter title: ";
    string title = safeString();
    cout << "Enter description: ";
    string description = safeString();
    cout << "Enter assignee: ";
    string assignee = safeString();
    cout << "Enter priority (Low/Medium/High/Critical): ";
    string priority = safeString();
    
    if (type == 1) {
        cout << "Enter steps to reproduce: ";
        string steps = safeString();
        allTasks.push_back(new BugTask(title, description, assignee, priority, steps));
        cout << "Bug task successfully created! Task ID: " << allTasks.back()->getId() << endl;
    }
    else if (type == 2) {
        cout << "Enter business requirement: ";
        string requirement = safeString();
        cout << "Enter estimated hours: ";
        double hours = safeDouble();
        allTasks.push_back(new FeatureTask(title, description, assignee, priority, requirement, hours));
        cout << "Feature task successfully created! Task ID: " << allTasks.back()->getId() << endl;
    }
    else if (type == 3) {
        cout << "Enter documentation section: ";
        string section = safeString();
        cout << "Enter format (PDF/DOCX/TXT): ";
        string format = safeString();
        allTasks.push_back(new DocumentationTask(title, description, assignee, priority, section, format));
        cout << "Documentation task successfully created! Task ID: " << allTasks.back()->getId() << endl;
    }
    else {
        cout << "Invalid task type!\n";
    }
}

// 2. Show all tasks (brief list)
void showAllTasks() {
    cout << "\n=== All Tasks List ===\n";
    if (allTasks.empty()) {
        cout << "No tasks created.\n";
        return;
    }
    
    cout << "┌──────┬──────────────┬──────────────────────────┬────────────────┬──────────────┬─────────────────┐\n";
    cout << "│  ID  │    Type      │          Title           │    Status      │  Priority    │   Assignee      │\n";
    cout << "├──────┼──────────────┼──────────────────────────┼────────────────┼──────────────┼─────────────────┤\n";
    
    for (auto task : allTasks) {
        printf("│ %4d │ %12s │ %24s │ %14s │ %12s │ %15s │\n",
               task->getId(),
               task->getTaskType().c_str(),
               task->getTaskTitle().substr(0, 24).c_str(),
               task->getTaskStatus().c_str(),
               task->getTaskPriority().c_str(),
               task->getTaskAssignee().substr(0, 15).c_str());
    }
    cout << "└──────┴──────────────┴──────────────────────────┴────────────────┴──────────────┴─────────────────┘\n";
}

// 3. Show task card (polymorphic printCard call)
void showTaskCard() {
    cout << "\n=== Task Card ===\n";
    cout << "Enter task ID: ";
    int id = safeInt();
    
    Task* task = findTaskById(id);
    if (task) {
        task->printCard();  // Polymorphic call
    } else {
        cout << "Task with ID " << id << " not found!\n";
    }
}

// 4. Advance task status
void advanceTaskStatus() {
    cout << "\n=== Advance Task Status ===\n";
    cout << "Enter task ID: ";
    int id = safeInt();
    
    Task* task = findTaskById(id);
    if (task) {
        task->advanceStatus();
    } else {
        cout << "Task with ID " << id << " not found!\n";
    }
}

// 5. Reopen task
void reopenTask() {
    cout << "\n=== Reopen Task ===\n";
    cout << "Enter task ID: ";
    int id = safeInt();
    
    Task* task = findTaskById(id);
    if (task) {
        task->reopen();
    } else {
        cout << "Task with ID " << id << " not found!\n";
    }
}

// 6. Filter by assignee
void filterByAssignee() {
    cout << "\n=== Filter by Assignee ===\n";
    cout << "Enter assignee name: ";
    string name = safeString();
    
    bool found = false;
    cout << "\nTasks for assignee \"" << name << "\":\n";
    cout << "┌──────┬──────────────┬──────────────────────────┬────────────────┬──────────────┐\n";
    cout << "│  ID  │    Type      │          Title           │    Status      │  Priority    │\n";
    cout << "├──────┼──────────────┼──────────────────────────┼────────────────┼──────────────┤\n";
    
    for (auto task : allTasks) {
        if (task->getTaskAssignee() == name) {
            printf("│ %4d │ %12s │ %24s │ %14s │ %12s │\n",
                   task->getId(),
                   task->getTaskType().c_str(),
                   task->getTaskTitle().substr(0, 24).c_str(),
                   task->getTaskStatus().c_str(),
                   task->getTaskPriority().c_str());
            found = true;
        }
    }
    cout << "└──────┴──────────────┴──────────────────────────┴────────────────┴──────────────┘\n";
    
    if (!found) {
        cout << "No tasks found for assignee \"" << name << "\".\n";
    }
}

// 7. Filter by priority
void filterByPriority() {
    cout << "\n=== Filter by Priority ===\n";
    cout << "Enter priority (Low/Medium/High/Critical): ";
    string priority = safeString();
    
    bool found = false;
    cout << "\nTasks with priority \"" << priority << "\":\n";
    cout << "┌──────┬──────────────┬──────────────────────────┬────────────────┬─────────────────┐\n";
    cout << "│  ID  │    Type      │          Title           │    Status      │   Assignee      │\n";
    cout << "├──────┼──────────────┼──────────────────────────┼────────────────┼─────────────────┤\n";
    
    for (auto task : allTasks) {
        if (task->getTaskPriority() == priority) {
            printf("│ %4d │ %12s │ %24s │ %14s │ %15s │\n",
                   task->getId(),
                   task->getTaskType().c_str(),
                   task->getTaskTitle().substr(0, 24).c_str(),
                   task->getTaskStatus().c_str(),
                   task->getTaskAssignee().substr(0, 15).c_str());
            found = true;
        }
    }
    cout << "└──────┴──────────────┴──────────────────────────┴────────────────┴─────────────────┘\n";
    
    if (!found) {
        cout << "No tasks found with priority \"" << priority << "\".\n";
    }
}

// 8. Kanban board (group by status)
void showKanbanBoard() {
    cout << "\n=== KANBAN BOARD ===\n";
    
    string statuses[] = {"Open", "In progress", "On review", "Closed"};
    string statusNames[] = {"OPEN", "IN PROGRESS", "ON REVIEW", "CLOSED"};
    
    for (int s = 0; s < 4; s++) {
        cout << "\n╔══════════════════════════════════════════════════════════════════════╗\n";
        cout << "║  📌 " << statusNames[s] << " (" << statuses[s] << ")\n";
        cout << "╠══════════════════════════════════════════════════════════════════════╣\n";
        
        bool hasTasks = false;
        for (auto task : allTasks) {
            if (task->getTaskStatus() == statuses[s]) {
                cout << "║  #" << task->getId() << " | " 
                     << task->getTaskType() << " | \""
                     << task->getTaskTitle() << "\" | "
                     << task->getTaskPriority() << " | → " 
                     << task->getTaskAssignee() << "\n";
                hasTasks = true;
            }
        }
        
        if (!hasTasks) {
            cout << "║  (no tasks)\n";
        }
        cout << "╚══════════════════════════════════════════════════════════════════════╝\n";
    }
}

// 9. Statistics
void showStatistics() {
    cout << "\n=== STATISTICS ===\n";
    
    map<string, int> statusCount;
    map<string, int> typeCount;
    map<string, int> priorityCount;
    double totalFeatureHours = 0;
    
    for (auto task : allTasks) {
        statusCount[task->getTaskStatus()]++;
        typeCount[task->getTaskType()]++;
        priorityCount[task->getTaskPriority()]++;
        
        if (task->getTaskType() == "Feature" && task->getTaskStatus() != "Closed") {
            FeatureTask* ft = dynamic_cast<FeatureTask*>(task);
            if (ft) {
                totalFeatureHours += ft->getEstimatedHours();
            }
        }
    }
    
    cout << "\n Task count by status:\n";
    cout << "   ├─ Open: " << statusCount["Open"] << "\n";
    cout << "   ├─ In progress: " << statusCount["In progress"] << "\n";
    cout << "   ├─ On review: " << statusCount["On review"] << "\n";
    cout << "   └─ Closed: " << statusCount["Closed"] << "\n";
    
    cout << "\n Task count by type:\n";
    for (auto& p : typeCount) {
        cout << "   ├─ " << p.first << ": " << p.second << "\n";
    }
    
    cout << "\n Task count by priority:\n";
    for (auto& p : priorityCount) {
        cout << "   ├─ " << p.first << ": " << p.second << "\n";
    }
    
    cout << "\n Total estimated hours for open features: " << totalFeatureHours << " hours\n";
}

// 10. Delete task
void deleteTask() {
    cout << "\n=== Delete Task ===\n";
    cout << "Enter task ID to delete: ";
    int id = safeInt();
    
    for (auto it = allTasks.begin(); it != allTasks.end(); ++it) {
        if ((*it)->getId() == id) {
            cout << "Task #" << id << ": \"" << (*it)->getTaskTitle() << "\" will be deleted.\n";
            delete *it;
            allTasks.erase(it);
            cout << "Task successfully deleted!\n";
            return;
        }
    }
    cout << "Task with ID " << id << " not found!\n";
}


void cleanup() {
    for (auto task : allTasks) {
        delete task;
    }
    allTasks.clear();
}


int main() {
    int choice;
    
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                   TASK MANAGEMENT SYSTEM                     ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    
    do {
        cout << "\n┌────────────────────────────────────────────────────────────────┐\n";
        cout << "│ 1.  Create Task                                              │\n";
        cout << "│ 2.  Show All Tasks                                           │\n";
        cout << "│ 3.  Show Task Card                                           │\n";
        cout << "│ 4.  Advance Status                                           │\n";
        cout << "│ 5.  Reopen Task                                              │\n";
        cout << "│ 6.  Filter by Assignee                                       │\n";
        cout << "│ 7.  Filter by Priority                                       │\n";
        cout << "│ 8.  Kanban Board                                             │\n";
        cout << "│ 9.  Statistics                                               │\n";
        cout << "│ 10. Delete Task                                              │\n";
        cout << "│ 0.  Exit                                                     │\n";
        cout << "└────────────────────────────────────────────────────────────────┘\n";
        cout << "Your choice: ";
        choice = safeInt();
        
        switch (choice) {
            case 1: createTask(); break;
            case 2: showAllTasks(); break;
            case 3: showTaskCard(); break;
            case 4: advanceTaskStatus(); break;
            case 5: reopenTask(); break;
            case 6: filterByAssignee(); break;
            case 7: filterByPriority(); break;
            case 8: showKanbanBoard(); break;
            case 9: showStatistics(); break;
            case 10: deleteTask(); break;
            case 0: 
                cout << "\nGoodbye!\n";
                cleanup();
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}
