#include <iostream>
#include <string>
#include <vector>

using namespace std;

//================== Base abstract class Task ===================
class Task {
protected:
    int taskId;
    string taskTitle;
    string taskDescription;
    string taskPriority;
    string taskStatus;
    string taskAssignee;
public:
    string getTaskTipe();
    string getDetailedInfo();

    void printCard();
    void advanceStatus();
    void reopen();
};

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
    return 0;
};
