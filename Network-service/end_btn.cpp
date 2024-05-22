#include "end_btn.h"

end_btn::end_btn(int id)
{
    this->id = id;
    setText("终止");
    connect(this,SIGNAL(clicked(bool)),this,SLOT(on_end_btn_clicked()));
}


void end_btn::on_end_btn_clicked()
{

    emit sendid(this->id);
}
