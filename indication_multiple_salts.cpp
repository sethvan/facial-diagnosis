
#include "indication_multiple_salts.h"
#include "facial_data.h"

Indication_Multiple_Salts::Indication_Multiple_Salts(const QString& _description, std::vector<int> _salt_numbers)
    : description(_description), salt_numbers(_salt_numbers)
{

}



QString Indication_Multiple_Salts::get_display_string()
{
    QString display_string;

    if(salt_numbers.size() > 1)
    {
        std::for_each(salt_numbers.begin(), std::next(salt_numbers.end(), -1),
                      [&display_string](int salt_number){
                          display_string += QString::number(salt_number) + " " +
                                            salts[salt_number].abrev + ", ";
                      });
    }
    display_string += QString::number(salt_numbers.back()) + " " +
                      salts[salt_numbers.back()].abrev;

    return display_string;
}
