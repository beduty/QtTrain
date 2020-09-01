#include <QApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QtDebug>
#include <QMessageBox>

int getWeight(const QString &input){
    QRegularExpression regex("\\A([1-9]\\d{0,3})\\s*(mg|g|kg)\\z");
    /// A([1-9]\\d{0,3})  -->  0,1,2,3 4자리수 숫자 0제외.
    /// \\s*   -->   공백 허용
    /// (mg|g|kg)  -->  ms/g/kg 중 하나.
    regex.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
    /// CaseInsensitiveOption  -->  대문자 소문자 구분하지 않는다.
    QRegularExpressionMatch match = regex.match(input);
    if(match.hasMatch()){
        const QString number = match.captured(1);
        int weight = number.toInt();
        const QString unit = match.captured(2).toLower();
        if(unit == "g"){
            weight *= 1000;
        }
        else if(unit == "kg"){
            weight *= 1000000;
        }
        return weight;
    }else{
        return -1;
    }
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //////////////////////////////////////////////
    QString input = QStringLiteral("123 foo 09 1a 3");
    /// -->  숫자만 찾아낸다!
    QRegularExpression regex("\\b\\d+\\b");
    QRegularExpressionMatchIterator i = regex.globalMatch(input);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        qDebug() << match.captured();
    }

    ///////////////////////////////////////////
    QLineEdit le;
    le.show();
    QObject::connect(&le, &QLineEdit::returnPressed, [&](){
        int result = getWeight(le.text());
        //int result = 1;
        if(result < 0) {
            QMessageBox::warning(&le,
                QObject::tr("Input"),
                QObject::tr("Input doesn't match the regular expression"));
        } else {
            QMessageBox::information(&le,
                QObject::tr("Input"),
                QObject::tr("Input is interpreted as %1 mg").arg(result));
        }
    });
    return app.exec();
}
