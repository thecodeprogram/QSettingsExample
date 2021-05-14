/*
This File Created
By: Burak Hamdi TUFAN
On: https://thecodeprogram.com/
At: 14.05.2021
*/

#include <QCoreApplication>
#include <iostream>
#include <QDebug>

using namespace std;

#include <QSettings>
#include <QVariant>

#include <QSize>
#include <QString>
#include <QStringList>

#include <QMetaType>
#include <QVariant>
#include <QDataStream>

struct UserCLass {
    QString name;
    QString surname;
    QString web;
    int experience;
};

//Declare the user defined class as METATYPE for Meta Object Compiler
Q_DECLARE_METATYPE(UserCLass);


//We need to overload in and out operators
QDataStream& operator<<(QDataStream& dataOut, const UserCLass& u) {
    dataOut << u.name << u.surname << u.web << u.experience;
    return dataOut;
}

QDataStream& operator>>(QDataStream& dataIn, UserCLass& u) {
    dataIn >> u.name;
    dataIn >> u.surname;
    dataIn >> u.web;
    dataIn >> u.experience;
    return dataIn;
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    system("title QSettings Example with QT C++ - Thecodeprogram");
    cout << "Welcome to QSettings example with QT C++..." << endl << endl;

    //First way
    QSettings settings_withAppInfo("Thecodeprogram", "QSettings Example Application");

    //Second ways
    QCoreApplication::setOrganizationName("Thecodeprogram");
    QCoreApplication::setOrganizationDomain("Thecodeprogram.com");
    QCoreApplication::setApplicationName("QSettings Example Application");

    //Initialisation examples of QSetting
    QSettings settings1(QSettings::SystemScope);
    QSettings settings2("thesettings.ini", QSettings::IniFormat);
    QSettings settings3(QSettings::Registry64Format, QSettings::UserScope, "Thecodeprogram", "QSettings Example Application");
    QSettings settings4("Thecodeprogram", "QSettings Example Application");


    //General Data
    settings2.setValue("author", "Burak Hamdi TUFAN");
    settings2.setValue("web", "thecodeprogram.com");
    //Grouped data
    settings2.setValue("Lang/programming", "C++");
    settings2.setValue("Lang/framework", "Qt Framework");
    settings2.setValue("Lang/experience", "6");

    cout << "Author : " << settings2.value("author").toByteArray().constData() << endl;
    cout << "Web : " << settings2.value("web").toByteArray().constData() << endl;
    cout << "Programming Lang : " << settings2.value("Lang/programming").toByteArray().constData() << endl;
    cout << "Framework : " << settings2.value("Lang/framework").toByteArray().constData() << endl;
    cout << "Experience : " << settings2.value("Lang/experience").toByteArray().constData() << " years" << endl;


    cout << endl << "------- ALL KEYS --------" << endl;

    QStringList keys = settings2.allKeys();
    for(int i=0; i<keys.size(); i++)
        cout << "Key : " << i << " / Value : " << keys.at(i).toUtf8().constData() << endl;


    cout<< endl << "------- GROUPS and SUBKEYS --------" << endl ;

    QStringList groups = settings2.childGroups();
    for(int i=0; i<groups.size(); i++){
        cout << "Group : " << i << " = : " << groups.at(i).toUtf8().constData() << endl;
        settings2.beginGroup(groups.at(i).toUtf8().constData());
        QStringList subKeyList = settings2.childKeys();
        for(int j=0; j<subKeyList.size(); j++)
            cout << "--SubKey : " << j << " = : " << subKeyList.at(j).toUtf8().constData() << endl;

        settings2.endGroup();
    }


    cout<< endl << "------- CUSTOM CLASS --------" << endl ;
    qRegisterMetaTypeStreamOperators<UserCLass>("UserCLass");

    UserCLass user;
    user.name = "Burak Hamdi";
    user.surname = "TUFAN";
    user.web = "thecodeprogram.com";
    user.experience = 6;
    settings2.setValue("user/userData", QVariant::fromValue(user));

    QVariant storedData = settings2.value("user/userData");
    UserCLass storedUser = storedData.value<UserCLass>();

    cout<< "Name : " << storedUser.name.toUtf8().constData() << endl;
    cout<< "Surname : " << storedUser.surname.toUtf8().constData() << endl ;
    cout<< "Web : " << storedUser.web.toUtf8().constData() << endl ;
    cout<< "Experience : " << QString::number(storedUser.experience).toUtf8().constData() << " years" << endl ;


    return a.exec();
}
