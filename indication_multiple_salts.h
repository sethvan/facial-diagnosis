
#ifndef INDICATION_MULTIPLE_SALTS_H
#define INDICATION_MULTIPLE_SALTS_H

#include <QString>
#include <vector>


class Indication_Multiple_Salts
{
public:
    QString description;
    std::vector<int> salt_numbers;
    Indication_Multiple_Salts(const QString& _description, std::vector<int> _salt_numbers);
    QString get_display_string();

};

extern std::vector<Indication_Multiple_Salts> prominents_multiple;

#endif // INDICATION_MULTIPLE_SALTS_H
