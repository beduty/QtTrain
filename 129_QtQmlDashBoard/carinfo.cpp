#include "carinfo.h"
#include "ui_form.h"
#include <QDebug>
#include "carinfoengine.h"
//CarInfo::CarInfo() : QWidget(0), ui(new Ui::Form)
//{
//    ui->setupUi(this);
//    m_engine = new CarInfoEngine(this);
//    /// form.ui에서 UI객체간 메시징을 수행했다. (rpm, speed, gear Slider <--> SpinBox)
//    connect(ui->distanceSlider, &QSlider::valueChanged, ui->distanceBox, &QDoubleSpinBox::setValue);

//    /// QDoubleSpinBox --> QSlider간 연결이 바로 안되는 게 있어서  직접 코딩을 해줬다.
//    /// QDoubleSpinBox의 변화를 받아서 시그널을 보내고, 보낸시그널을 받아서 QSlider값을 업데이트 한다.
//    connect(ui->distanceBox, SIGNAL(valueChanged(double)),this, SIGNAL(distanceChanged(double)));
//    connect(this, &CarInfo::distanceChanged, ui->distanceSlider, &QSlider::setValue);

//    m_engine->setGear(ui->gearBox->value());
//    m_engine->setRpm(ui->rpmBox->value());
//    connect(ui->gearBox, SIGNAL(valueChanged(int)), m_engine, SLOT(setGear(int)));
//    connect(ui->rpmBox, SIGNAL(valueChanged(int)), m_engine, SLOT(setRpm(int)));
//    connect(m_engine, SIGNAL(gearChanged(int)), ui->gearBox, SLOT(setValue(int)));
//    connect(m_engine, SIGNAL(rpmChanged(int)), ui->rpmBox, SLOT(setValue(int)));
//}
CarInfo::CarInfo() : QWidget(0), ui(new Ui::Form) {
    ui->setupUi(this);
    m_engine = new CarInfoEngine(this);
    int val =ui->gearBox->value();
    m_engine->setGear(ui->gearBox->value());
    m_engine->setRpm(ui->rpmBox->value());
    connect(ui->speedBox, SIGNAL(valueChanged(int)),
            this, SIGNAL(speedChanged(int)));
    connect(ui->distanceBox, SIGNAL(valueChanged(double)),
            this, SIGNAL(distanceChanged(double)));

    connect(ui->distanceSlider, &QSlider::valueChanged,
            ui->distanceBox, &QDoubleSpinBox::setValue);
    connect(this, &CarInfo::distanceChanged,
            ui->distanceSlider, &QSlider::setValue);

    connect(ui->gearBox, SIGNAL(valueChanged(int)),
            m_engine, SLOT(setGear(int)));
    connect(ui->rpmBox, SIGNAL(valueChanged(int)),
            m_engine, SLOT(setRpm(int)));
    connect(m_engine, SIGNAL(gearChanged(int)),
            ui->gearBox, SLOT(setValue(int)));
    connect(m_engine, SIGNAL(rpmChanged(int)),
            ui->rpmBox, SLOT(setValue(int)));
}


void CarInfo::setSpeed(int speed){
    ui->speedBox->setValue(speed);
}

void CarInfo::setDistance(double distance){
    ui->distanceBox->setValue(distance);
}

double CarInfo::distance() const{
    return ui->distanceBox->value();
}

CarInfoEngine *CarInfo::engine() const{
    return m_engine;
}

int CarInfo::speed() const{
    return ui->speedBox->value();
}
