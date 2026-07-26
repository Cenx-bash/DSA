/*
==============================================
File        : mid.cpp
Description : Middleware Engine
Purpose     : Process requests before execution
==============================================
*/

#include <iostream>
#include <string>

class Middleware {

public:

    virtual void execute() = 0;

};

class AuthenticationMiddleware : public Middleware {

public:

    void execute() override {

        std::cout << "Authentication Passed\n";

    }

};

class ValidationMiddleware : public Middleware {

public:

    void execute() override {

        std::cout << "Validation Passed\n";

    }

};

class LoggingMiddleware : public Middleware {

public:

    void execute() override {

        std::cout << "Request Logged\n";

    }

};

int main() {

    AuthenticationMiddleware auth;

    ValidationMiddleware validation;

    LoggingMiddleware logger;

    auth.execute();
    validation.execute();
    logger.execute();

}
