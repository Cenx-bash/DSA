#include <iostream>
#include <string>

using namespace std;

class Database {

public:

    void connect() {

    }

    void disconnect() {

    }

};

class UserService {

private:

    Database database;

public:

    void login() {

    }

    void registerUser() {

    }

};

class Application {

private:

    UserService service;

public:

    void run() {

    }

};

int main() {

    Application app;

    app.run();

    return 0;
}
