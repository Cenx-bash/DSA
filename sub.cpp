#include <iostream>
#include <memory>

using namespace std;

class Subsystem {

public:

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual ~Subsystem() = default;

};

class DatabaseSubsystem : public Subsystem {

public:

    void start() override {

        cout << "Database Connected\n";

    }

    void stop() override {

        cout << "Database Disconnected\n";

    }

};

class CacheSubsystem : public Subsystem {

public:mid.cpp

    void start() override {

        cout << "Cache Initialized\n";

    }

    void stop() override {

        cout << "Cache Cleared\n";

    }

};

int main() {

    unique_ptr<Subsystem> database = make_unique<DatabaseSubsystem>();

    unique_ptr<Subsystem> cache = make_unique<CacheSubsystem>();

    database->start();

    cache->start();

    database->stop();

    cache->stop();

}
