//
//  Entity.h
//  SonicFileSystem
//
//  Created by Doron Roberts-Kedes on 11/17/15.
//
//

#ifndef __SonicFileSystem__Entity__
#define __SonicFileSystem__Entity__

#include <stdio.h>
#include "ofMain.h"
#include "Sound.h"
#include "Directory.h"

class Entity
{
public:
    virtual std::vector<Sound> getSounds() = 0;
    virtual std::vector<Directory> getDirs() = 0;
};

#endif /* defined(__SonicFileSystem__Entity__) */
