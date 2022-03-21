//
//  env.cpp
//  msdscript_xcode
//
//  Created by Polina Lyubavina on 3/21/22.
//

#include <stdio.h>

#include "env.h"

PTR(Env) Env::empty = NEW(EmptyEnv)();
