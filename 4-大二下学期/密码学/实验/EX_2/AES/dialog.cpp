// dialog.cpp
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    input_type_buttons = new QButtonGroup(this);
    input_type_buttons -> addButton(ui->input_ascii, 1);
    input_type_buttons -> addButton(ui->input_hex, 2);
    ui->input_ascii->setChecked(true);  // 默认选择为ASCII类型

    key_type_buttons = new QButtonGroup(this);
    key_type_buttons -> addButton(ui->key_ascii, 1);
    key_type_buttons -> addButton(ui->key_hex, 2);
    ui->key_ascii->setChecked(true);  // 默认选择为ASCII类型

    output_type_buttons = new QButtonGroup(this);
    output_type_buttons -> addButton(ui->output_ascii, 1);
    output_type_buttons -> addButton(ui->output_hex, 2);
    ui->output_ascii->setChecked(true);  // 默认选择为ASCII类型

    connect(ui->input_ascii, SIGNAL(clicked(bool)), this, SLOT(slots_text_type));
    connect(ui->input_hex, SIGNAL(clicked(bool)), this, SLOT(slots_text_type));
    connect(ui->key_ascii, SIGNAL(clicked(bool)), this, SLOT(slots_key_type));
    connect(ui->key_hex, SIGNAL(clicked(bool)), this, SLOT(slots_key_type));
    connect(ui->output_ascii, SIGNAL(clicked(bool)), this, SLOT(slots_output_type));
    connect(ui->output_hex, SIGNAL(clicked(bool)), this, SLOT(slots_output_type));
}

Dialog::~Dialog()
{
    delete ui;
}
