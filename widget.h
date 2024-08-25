
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <set>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_4_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

    void on_prominentCheckBoxStateChanged();

    void on_clearChecksButton_clicked();

private:
    Ui::Widget *ui;
    QString header;
    std::set<QString> prom_salts;
    std::set<int> prom_indexes;
    std::vector<QCheckBox*> salt_boxes;

    void on_any_lineEdit_Changed();
    void append_if_match(const QString& input);
    void populate_prominent_checkboxes();
};

#endif // WIDGET_H
