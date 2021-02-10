#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <fstream>
#include <QDebug>
#include <QtMath>

using namespace  std;
float readFileStValue(const string &Path, int Column);
float calculateStandartDeviation(std::vector<float> Values);
float getMean(std::vector<float> Values);


//"/home/yusuf/Documents/workspace/build-MacSim-Desktop_Qt_5_15_1_GCC_64bit-Debug/graphs/Incresing User_Cap:1.1ms_beacon:0.11/User:2/Cap:1/Cap:1 - Result For Peer - 0.log"
float readAllFilesOnMainPath(const string &MainPath)
{
    string main_path = MainPath;
    string user_folder_path;
    string cap_forder_path;
    string data_file_path;


    int user_folder_number = 15;
    int cap_number = 25;
    int user_number = 0;


    for(int i=2; i<=user_folder_number; i++)
    {
        user_folder_path = main_path + "/User:" + std::to_string(i) + "/";
        user_number = i;

        for(int k=1; k<=cap_number; k++)
        {
            cap_forder_path = user_folder_path + "Cap:" + to_string(k);

            std::vector<float> data_rates;
            std::vector<float> collisions;


            for(int l=0; l<user_number; l++)
            {
                data_file_path = cap_forder_path + "/Cap:" + to_string(k) + " - Result For Peer - " + to_string(l) + ".log";

                data_rates.push_back(readFileStValue(data_file_path, 3));
                collisions.push_back(readFileStValue(data_file_path, 1));
            }

            qDebug() << QString::fromStdString("User:" + std::to_string(i) + " - Cap:" + std::to_string(k) + " = " +
                                                std::to_string(getMean(data_rates)) + " - " +
                                                std::to_string(calculateStandartDeviation(data_rates)) + " - " +
                                                std::to_string(collisions[0]));

//            qDebug() << QString::fromStdString("User:" + std::to_string(i) + " - Cap:" + std::to_string(k) + " = " + std::to_string(calculateStandartDeviation(data_rates)));

        }

    }


    return 0;
}


float readFileStValue(const string &Path, int Column)
{
    QString line;
    std::vector<float> values;

    QFile file(QString::fromStdString(Path));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);


    while(!in.atEnd())
        line = in.readLine();

    QStringList value_list = line.split("\t\t");

    return value_list.at(Column).toFloat();
}



float calculateStandartDeviation(std::vector<float> Values)
{
    float mean = 0;
    float variance = 0;
    float temp = 0;
    float deviation = 0;
    float confidence = 0;

    mean = getMean(Values);

    for(int i=0; i < (int)Values.size(); i++)
    {
        temp = (Values[i] - mean);
        variance += qPow(temp, 2);;
    }

    variance /= Values.size();

    deviation = sqrt(variance);

    confidence = deviation / sqrt(Values.size());

    return confidence;
}



float getMean(std::vector<float> Values)
{
    float mean = 0;

    for(int i=0; i < (int)Values.size(); i++)
        mean += Values[i];

    mean /= Values.size();

    return mean;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "Enter Main Path" << endl;
    string main_path;
//    cin >> main_path;
    main_path = "/home/yusuf/Documents/workspace/build-MacSim-Desktop_Qt_5_15_1_GCC_64bit-Debug/graphs/Incresing User_Cap:1.1ms_beacon:0.11";

    readAllFilesOnMainPath(main_path);


    return a.exec();
}
