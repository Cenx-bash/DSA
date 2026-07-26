#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <optional>
#include <functional>
#include <ranges>
#include <algorithm>

using namespace std;

//=====================================================
// Logger
//=====================================================

class Logger final {

public:

    enum class Level {
        Info,
        Warning,
        Error,
        Debug
    };

    static void log(Level level, const string& message) {

        static mutex lock;

        lock_guard<mutex> guard(lock);

        cout << "[" << levelToString(level) << "] "
             << message << endl;

    }

private:

    static string levelToString(Level level) {

        switch(level) {

            case Level::Info: return "INFO";
            case Level::Warning: return "WARNING";
            case Level::Error: return "ERROR";
            case Level::Debug: return "DEBUG";

        }

        return "UNKNOWN";

    }

};

//=====================================================
// Domain Model
//=====================================================

class Entity {

public:

    virtual ~Entity() = default;

    virtual int id() const = 0;

};

class Student final : public Entity {

private:

    int studentID;
    string name;
    double gpa;

public:

    Student(int id,
            string studentName,
            double grade)

        :

        studentID(id),
        name(move(studentName)),
        gpa(grade)

    {}

    int id() const override {

        return studentID;

    }

    const string& getName() const {

        return name;

    }

    double getGPA() const {

        return gpa;

    }

};

//=====================================================
// Generic Repository
//=====================================================

template<class T>

class Repository {

private:

    unordered_map<int,T> database;

public:

    void save(const T& object) {

        database[object.id()] = object;

    }

    optional<T> find(int id) {

        auto iterator = database.find(id);

        if(iterator == database.end())
            return nullopt;

        return iterator->second;

    }

    void remove(int id) {

        database.erase(id);

    }

    vector<T> all() {

        vector<T> result;

        for(auto& [key,value] : database)
            result.push_back(value);

        return result;

    }

};

//=====================================================
// Service Layer
//=====================================================

class StudentService {

private:

    Repository<Student> repository;

public:

    void seed() {

        repository.save(Student(1,"Karl",3.98));
        repository.save(Student(2,"John",3.71));
        repository.save(Student(3,"Anna",3.90));

    }

    void printLeaderboard() {

        auto students = repository.all();

        ranges::sort(students,

            [](const Student& a,
               const Student& b){

                return a.getGPA() > b.getGPA();

            });

        Logger::log(Logger::Level::Info,
                    "Student Leaderboard");

        for(const auto& student : students){

            cout

                << student.id()

                << " "

                << student.getName()

                << " "

                << student.getGPA()

                << endl;

        }

    }

};

//=====================================================
// Application Layer
//=====================================================

class Application final {

private:

    unique_ptr<StudentService> service;

public:

    Application()

        :

        service(make_unique<StudentService>())

    {}

    void boot() {

        Logger::log(Logger::Level::Info,
                    "Booting Application");

        service->seed();

    }

    void run() {

        Logger::log(Logger::Level::Debug,
                    "Executing Services");

        service->printLeaderboard();

    }

    void shutdown() {

        Logger::log(Logger::Level::Info,
                    "Graceful Shutdown");

    }

};

//=====================================================
// Main
//=====================================================

int main() {

    auto start = chrono::high_resolution_clock::now();

    try {

        Application app;

        app.boot();

        app.run();

        app.shutdown();

    }

    catch(const exception& exception) {

        Logger::log(Logger::Level::Error,
                    exception.what());

    }

    auto end = chrono::high_resolution_clock::now();

    cout << "\nExecution Time : "

         << chrono::duration_cast
         <chrono::microseconds>

         (end-start).count()

         << " us\n";

}
