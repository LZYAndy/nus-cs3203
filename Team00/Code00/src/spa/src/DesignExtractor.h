#ifndef AUTOTESTER_DESIGNEXTRACTOR_H
#define AUTOTESTER_DESIGNEXTRACTOR_H

#include "FollowsBank.h"
#include "FollowsStarBank.h"

class DesignExtractor
{
public:
    static void extract_follows_star(FollowsBank* bank_in, FollowsStarBank* bank_out);
};

#endif //AUTOTESTER_DESIGNEXTRACTOR_H
