#pragma once

struct jITestable
{
    virtual void test() {
        std::cout << std::endl << "testing class: " << typeid(*this).name() << "..." << std::endl;
    };
};