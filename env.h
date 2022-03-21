//
//  env.h
//  msdscript_xcode
//
//  Created by Polina Lyubavina on 3/21/22.
//

#ifndef env_h
#define env_h

#include <stdio.h>
#include <string>

#include "pointer.h"

class Val;


CLASS(Env) {
    
public:
    static PTR(Env) empty;
    virtual PTR(Val) lookup(std::string find_name) = 0;
    
};


class EmptyEnv : public Env {
    
    PTR(Val) lookup(std::string find_name) {
        throw std::runtime_error("free variable: " + find_name);
    }
    
};


class ExtendedEnv : public Env {
    
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;
    
    PTR(Val) lookup(std::string find_name) {
        if(find_name == name) {
            return val;
        }
        else {
            return rest -> lookup(find_name);
        }
    }
    
};


#endif /* env_h */
