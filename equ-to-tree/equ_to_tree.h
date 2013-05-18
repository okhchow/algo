#ifndef __EQU_TO_TREE_H__
#define __EQU_TO_TREE_H__

#include <string>

#define BEDMAS_SIZE ( 3 )

enum ChildDir{ LEFT = 0, RIGHT, DIR_SIZE };
const std::string bedmas[ BEDMAS_SIZE ] = { "+-", "*/", "^" };

struct Node
{
    std::string value;
    Node* child[ DIR_SIZE ];
};

#endif
