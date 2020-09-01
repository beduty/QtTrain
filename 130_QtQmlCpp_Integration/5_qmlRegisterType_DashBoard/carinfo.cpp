#include "carinfo.h"
#include "ui_carinfo.h"

CarInfo::CarInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarInfo)
{
    ui->setupUi(this);
    // Slider~SpinBox간 Signal, Slot연결은 OK!
    // Slider<--> DoubleSpinBox간 연결이 안된다!! 따로 커스텀 해줘야 한다.
    //   1. distanceSlider -> distanceBox 연결
    connect(ui->distanceSlider, &QSlider::valueChanged,
            ui->distanceBox, &QDoubleSpinBox::setValue);
    //   2. distanceBox -> distanceSlider 연결
    //      - distanceBox 움직이면, Q_PROPERY distance의 NOTIFY를 사용한다.
    ///     - SIGNAL이 들어오면,SIGNAL로 다시 넘겨준다!
    ///     - QPROPERTY NOTIFY 들어오면 slider값 변화
    //    connect(ui->distanceBox, SIGNAL(valueChanged(double)),
    //            this , SIGNAL(distanceChaged(double)));
    //    connect(this, &CarInfo::distanceChaged,
    //            ui->distanceSlider, &QSlider::setValue);
    connect(ui->distanceBox, SIGNAL(valueChanged(double)),
            this , SLOT(setDistance(double)));


    m_engine = new CarInfoEngine(this);
    m_engine->setRpm(ui->rpmBox->value());
    m_engine->setGear(ui->gearBox->value());
    // gearBox와 gearSlider간 연결은 되어있지만,
    // m_engine간 연결이 안 되어 있기 때문에 Connect해준다.
    connect(ui->rpmBox, SIGNAL(valueChanged(int)),m_engine, SLOT(setRpm(int)));
    connect(ui->gearBox, SIGNAL(valueChanged(int)),m_engine, SLOT(setGear(int)));
    connect(m_engine, SIGNAL(gearChanged(int)), ui->gearBox, SLOT(setValue(int)));
    connect(m_engine, SIGNAL(rpmChanged(int)), ui->rpmBox, SLOT(setValue(int)));

    // 프록시 패턴으로 데이터 전달위한 Signal 연결
    connect(ui->speedBox, SIGNAL(valueChanged(int)), this, SIGNAL(speedChanged(int)));
    connect(ui->distanceBox, SIGNAL(valueChanged(double)), this, SIGNAL(distanceChanged(double)));
}

CarInfo::~CarInfo()
{
    delete ui;
}

int CarInfo::speed() const
{
    return ui->speedBox->value();
}

int CarInfo::distance() const
{
    return ui->distanceBox->value();
}

CarInfoEngine *CarInfo::engine() const
{
    return m_engine;
}

void CarInfo::setSpeed(int speed)
{
    ui->speedBox->setValue(speed);
    emit speedChanged(speed);
    // .ui 상에서 연결된 slot으로 speedSlider의 값을 변경시킨다.
}

void CarInfo::setDistance(double distance)
{
    ui->distanceBox->setValue(distance);
    ui->distanceSlider->setValue((int)distance);
    emit distanceChanged(distance);
    // 클래스 생성자에서 연결시킨 signal-slot으로 값을 변경시킨다.
}
