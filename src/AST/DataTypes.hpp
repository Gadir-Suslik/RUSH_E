#pragma once

#include <unordered_map>
#include <string>
#include <cmath>
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

struct DataTypes {
    virtual std::string tostring() = 0;
    virtual long double ld() = 0;
    virtual bool tobool() = 0;
};

struct DoubleType : public DataTypes {
public:
    double d;

    DoubleType(double db){
        d = db;
    }


    string tostring() override {
        ostringstream s;
        s << d;
        return s.str();
    }

    long double ld() override{
        return d;
    }

    bool tobool() override {
        try
        {
            return (bool)d;
        }
        catch(const std::exception& e)
        {
            cerr << "Error while converting this data type to bool" << endl;
            return 0;  
        }
    }
};

struct StringType : public DataTypes {
    string s;

    StringType(string str){
        s = str;
    }

    string tostring() override {
        return s;
    }

    long double ld() override {
        
        try
        {
            return stold(s);
        }
        catch(const std::exception& e)
        {
            cerr << "Error stold!" << endl;
            return 0;  
        }
        
    }

    bool tobool() override {
        return s != "false";
    }
};

struct Boolean : public DataTypes {
    bool s;

    Boolean(bool ch){
        s = ch;
    }

    string tostring() override {
        return to_string(s);
    }

    long double ld() override {
        
        try
        {
            return (bool)s;
        }
        catch(const std::exception& e)
        {
            cerr << "Error cant convert this datatype to bool" << endl;
            return 0;  
        }
        
    }

    bool tobool() override {
        return s;
    }
};

static unordered_map<string, DataTypes*> vars = {
    {"M_PI", new DoubleType(M_PI)},
    {"M_E", new DoubleType(M_E)},
};

DataTypes* ret(string key){
    return vars[key];
}







