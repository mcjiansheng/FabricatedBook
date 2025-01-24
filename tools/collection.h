//
// Created by 48811 on 25-1-24.
//

#ifndef SLAYTHESPIRE_COLLECTION_H
#define SLAYTHESPIRE_COLLECTION_H

#include <stdbool.h>
//#include "card.h"

typedef struct collection {
    char *name;
    char *discribe;
    int value;
    bool get;
} Collection;

void init_collection();

bool all_collections_had();

#endif //SLAYTHESPIRE_COLLECTION_H
