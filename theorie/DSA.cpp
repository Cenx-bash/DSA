#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace Core {

class Application {
public:
    virtual void initialize() = 0;
    virtual void execute() = 0;
    virtual void shutdown() = 0;
};

}

class Program : public Core::Application {

public:

    void initialize() override {

    }

    void execute() override {

    }

    void shutdown() override {

    }

};

int main() {

    unique_ptr<Core::Application> app = make_unique<Program>();

    app->initialize();
    app->execute();
    app->shutdown();

    return 0;
}
