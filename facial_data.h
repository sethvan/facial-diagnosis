
#ifndef FACIAL_DATA_H
#define FACIAL_DATA_H

#include <array>
#include <vector>
#include <QString>
#include "indication.h"
#include "salt.h"

extern const std::array<Salt, 28> salts;
extern std::vector<Indication> indications;
extern std::vector<Indication> prominents;


#endif // FACIAL_DATA_H
