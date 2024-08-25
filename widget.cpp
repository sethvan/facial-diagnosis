
#include "widget.h"
#include "./ui_widget.h"
#include "facial_data.h"
#include <QString>
#include <QRegularExpression>
#include <QFont>
#include <QTextCharFormat>
#include <array>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <algorithm>
#include <QDebug>
#include <vector>
#include "indication_multiple_salts.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    header = QString("INDICATION").leftJustified(70) +
             QString("SALT NAME").leftJustified(36) +
             QString("SALT#");
    ui->pushButton->setStyleSheet("background-color: #d8e1ff");
    ui->clearChecksButton->setStyleSheet("background-color: #d8e1ff");
    populate_prominent_checkboxes();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::append_if_match(const QString& input)
{
    if(input.size() && input.at(0).isLetter())
    {
        QRegularExpression re(input, QRegularExpression::CaseInsensitiveOption);

        for(const Indication& indication : indications)
        {
            if(input.size() > indication.description.size())
            {
                continue;
            }
            QRegularExpressionMatch match = re.match(indication.description);
            if(match.hasMatch())
            {
                QString line = indication.description.leftJustified(70, ' ') +
                               salts[indication.salt_number].name.leftJustified(36) +
                               QString::number(indication.salt_number);
                ui->textEdit->append(line);
            }
        }
    }
}

// Button for showing all indications on all tab
void Widget::on_pushButton_clicked()
{
    ui->lineEdit->setText("");
    ui->textEdit->setText(header);
    ui->textEdit->append("");

    for(const Indication& indi : indications)
    {
        QString line = indi.description.leftJustified(70, ' ') +
                       salts[indi.salt_number].name.leftJustified(36) +
                       QString::number(indi.salt_number);
        ui->textEdit->append(line);
    }

}

// for line edits 1-5 on all tab
void Widget::on_any_lineEdit_Changed()
{
    std::array<QString, 5> string_inputs {
        ui->lineEdit->text().trimmed(),
        ui->lineEdit_2->text().trimmed(),
        ui->lineEdit_3->text().trimmed(),
        ui->lineEdit_4->text().trimmed(),
        ui->lineEdit_5->text().trimmed()
    };

    ui->textEdit->setText("");
    ui->textEdit->setText(header);
    ui->textEdit->append("");

    for(const QString& str : string_inputs)
    {
        append_if_match(str);
    }

}

void Widget::populate_prominent_checkboxes()
{
    std::sort(prominents_multiple.begin(), prominents_multiple.end(),
              [](const Indication_Multiple_Salts& indic_a, const Indication_Multiple_Salts& indic_b){
        return indic_a.description < indic_b.description;
    });

    QGroupBox *leftGroupBox = ui->groupBox;
    QGroupBox *rightGroupBox = ui->groupBox_2;
    leftGroupBox->setLayout(new QVBoxLayout);
    rightGroupBox->setLayout(new QVBoxLayout);

    size_t tab1_list_size = prominents_multiple.size() / 2;
    for(size_t i{}; i < prominents_multiple.size(); ++i)
    {
        Indication_Multiple_Salts& prom = prominents_multiple.at(i);

        QCheckBox *checkBox = new QCheckBox(prom.description);
        checkBox->setProperty("prom_index", i);

        if(i < tab1_list_size)
        {
            leftGroupBox->layout()->addWidget(checkBox);
        }
        else
        {
            rightGroupBox->layout()->addWidget(checkBox);
        }

        QObject::connect(checkBox, &QCheckBox::stateChanged,
                         this, &Widget::on_prominentCheckBoxStateChanged);
        salt_boxes.push_back(checkBox); //for unchecking them all when clearing
    }
}

void Widget::on_prominentCheckBoxStateChanged()
{
    QCheckBox *checkBox = qobject_cast<QCheckBox*>(sender());
    if (checkBox)
    {
        // Handle the checkbox state change here
        if (checkBox->checkState() == Qt::Checked)
        {
            prom_indexes.insert(checkBox->property("prom_index").value<int>());
        }
        else
        {
            prom_indexes.erase(checkBox->property("prom_index").value<int>());
        }

        prom_salts.clear();
        for( const int i : prom_indexes)
        {
            prom_salts.insert(prominents_multiple.at(i).get_display_string());
        }

        QString display;
        int j{};
        for(const auto& str : prom_salts)
        {
            if(j++)
            {
                display += ", ";
            }
            display += str;
        }
        ui->lineEdit_6->setText(display);
    }
}


// Line edits on all tab for looking up indications via regex
void Widget::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    on_any_lineEdit_Changed();
}

void Widget::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{
    on_any_lineEdit_Changed();
}

void Widget::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{
    on_any_lineEdit_Changed();
}

void Widget::on_lineEdit_4_cursorPositionChanged(int arg1, int arg2)
{
    on_any_lineEdit_Changed();
}

void Widget::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    on_any_lineEdit_Changed();
}




//clear checks button in prominents tab
void Widget::on_clearChecksButton_clicked()
{
    ui->lineEdit_6->setText("");
    for(const auto check_ptr : salt_boxes)
    {
        check_ptr->setCheckState(Qt::Unchecked);
    }
}

