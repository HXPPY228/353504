#include "mainwindow.h"
#include "house.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stream_in(&text_in)
    , stream_out(&text_out)
{
    ui->setupUi(this);
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::menu);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    if (!ui->lineEdit->isReadOnly())
        text_in += ui->lineEdit->text();
}

void MainWindow::menu()
{
    auto& out = *ui->textEdit;
    auto& in = *ui->lineEdit;

    while (true) {
        QCoreApplication::processEvents();

        stream_out << "Меню:\n1. Ввести один абзац текста (до нажатия Enter). Сохранить данный текст в текстовый файл с именем «ВойноЛаб20.txt» посредством посимвольной записи.\n"
                             "2. Посимвольно считать из текстового файла с именем «ВойноЛаб20.txt» текст и вывести его на экран.\n"
                             "3. Ввести размер массива и массив типа char, разделяющий символ ' '. Сохранить эти элементы массива в текстовый файл с именем «ВойноЛаб20_0.txt» посредством потокового ввода.\n"
                             "4. Считать из текстового файла с именем «ВойноЛаб20_0.txt» элементы массива посредством потокового вывода и вывести на экран считанный из файла массив, разделяя печатаемые значения символом «пробел».\n"
                             "5. Ввести содержимое полей объекта типа структуры House. Сохранить содержимое всех полей структуры в текстовый файл с именем «ВойноЛаб20_1.txt».\n"
                             "6. Прочитать из текстового файла с именем «ВойноЛаб20_1.txt» все записанные в нем структуры и распечатать содержимое их полей на экран, разделяя содержимое полей знаком '|'.\n"
                             "7. Запросить у пользователя ввести содержимое полей объекта типа вашей структуры. Сохранить содержимое всех полей структуры в бинарный файл с именем «ВойноЛаб20_2.bin»\n"
                             "8. Прочитать из бинарного файла с именем «ВойноЛаб20_2.bin» все записанные в нем структуры и распечатать содержимое их полей на экран, разделяя содержимое полей символами \" ; \".\n"
                             "9. Запросить у пользователя ввести предложение (до нажатия Enter) и дописать данное предложение в текстовый файл с именем «ВойноЛаб20_3.txt» в виде отдельной строки.\n"
                             "10. Построчно считать из текстового файла с именем «ВойноЛаб20_3.txt» все предложения и вывести их на экран.\n"
                             "Выберите пункт меню: \n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        in.setReadOnly(false);
        while (text_in.isEmpty()){
            QCoreApplication::processEvents();
        }
        int choice;
        stream_in >> choice;
        if (stream_in.status() != QTextStream::Ok) {
            text_in.clear();
            stream_in.resetStatus();
        } else {
            text_in.remove(0, stream_in.pos());
            stream_out << choice << '\n';
        }
        stream_in.seek(0);
        in.setText(text_in);
        processMenuChoice(choice);
    }
}

void MainWindow::processMenuChoice(int choice) {
    auto& out = *ui->textEdit;
    auto& in = *ui->lineEdit;
    switch (choice) {
    case 1:
    {
        QString fileName = "ВойноЛаб20.tx   t";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);
        QTextStream file_stream(&file);
        stream_out << "Вы выбрали пункт 1\nВведте абзац текста\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        text_in.clear();
        in.setReadOnly(false);
        while (text_in.isEmpty()){
            QCoreApplication::processEvents();
        }
        in.setReadOnly(true);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для записи\n";
        } else {

            for (int i = 0; i < text_in.length(); ++i) {
                file_stream << text_in.at(i);
            }
            file.close();
            text_in.clear();
            in.setText(text_in);
            stream_in.readAll();
            stream_out << "Текст успешно записан в файл\n";
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 2:
    {
        QString fileName = "ВойноЛаб20.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);
        QTextStream file_stream(&file);
        stream_out << "Вы выбрали пункт 2\nСодержимое файла:\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для чтения\n";
        } else {
            while (!file_stream.atEnd()) {
                QChar character;
                file_stream >> character;
                stream_out << character;
            }
            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 3:
    {
        QString fileName = "ВойноЛаб20_0.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);
        QTextStream file_stream(&file);
        stream_out << "Вы выбрали пункт 3\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для запси\n";
        } else {
            stream_out << "Введте размер массива\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            int n;
            stream_in >> n;
            if (stream_in.status() != QTextStream::Ok || n < 0) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << n << '\n';
            }
            in.setText(text_in);

            char c;
            bool ok = true;
            for (int i = 0; i < n; ++i) {
                stream_out << "Введте символ (" << i+1 << "/" << n << ")\n";
                out.setText(text_out);
                out.moveCursor(QTextCursor::End);
                while (text_in.isEmpty()){
                    QCoreApplication::processEvents();
                }
                stream_in >> c;
                if (stream_in.status() != QTextStream::Ok) {
                    stream_out << "Неверный ввод\n";
                    stream_in.seek(0);
                    stream_in.resetStatus();
                    text_in.clear();
                    ok = false;
                    break;
                } else {
                    text_in.remove(0, stream_in.pos());
                    stream_in.seek(0);
                    stream_out << c << '\n';
                }
                in.setText(text_in);
                file_stream << c << ' ';
            }

            file.close();
            if (ok) stream_out << "Текст успешно записан в файл\n";
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 4:
    {
        stream_out << "Вы выбрали пункт 4\nСодержимое файла:\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        QString fileName = "ВойноЛаб20_0.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);
        QTextStream file_stream(&file);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для чтения\n";
        } else {
            while (!file_stream.atEnd()) {
                QChar character;
                file_stream >> character;
                if (character != ' ')
                    stream_out << character << ' ';
            }
            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 5:
    {
        stream_out << "Вы выбрали пункт 5\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        QString fileName = "ВойноЛаб20_1.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);
        QTextStream file_stream(&file);
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для запси\n";
        } else {
            House house;
            stream_out << "Введте колчество комнат\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            stream_in >> house.rooms;
            if (stream_in.status() != QTextStream::Ok || house.rooms < 0) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.rooms << '\n';
            }
            in.setText(text_in);

            stream_out << "Введте площадь\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            stream_in >> house.area;
            if (stream_in.status() != QTextStream::Ok || house.area < 0) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.area << '\n';
            }
            in.setText(text_in);

            stream_out << "Введте сдается ли в аренду(1 - да, 0 - нет)\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            int t;
            stream_in >> t;
            if (stream_in.status() != QTextStream::Ok) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                house.isTheHouseRentable = t;
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.isTheHouseRentable << '\n';
            }
            in.setText(text_in);

            stream_out << "Введте букву дома\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            stream_in >> house.letterOFHouse;
            if (stream_in.status() != QTextStream::Ok ) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.letterOFHouse << '\n';
            }
            in.setText(text_in);

            file_stream << house.rooms << '\n' << QString::number(house.area, 'g', 100) << '\n' << house.isTheHouseRentable << '\n' << house.letterOFHouse << '\n';

            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 6:
    {
        stream_out << "Вы выбрали пункт 6\nСодержимое файла:\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        QString fileName = "ВойноЛаб20_1.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);
        QTextStream file_stream(&file);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для чтения\n";
        } else {
            int i = 0;
            QString line;
            QVector<QString> vec(4);
            while (!file_stream.atEnd()) {
                line = file_stream.readLine();
                vec[i] = line;
                ++i;
                if (i == 4) {
                    for (int j = 0; j < i; ++j){
                        if (j != 0) stream_out << " | ";
                        stream_out << vec[j];
                    }
                    stream_out << '\n';
                    i = 0;
                }
            }
            for (int j = 0; j < i; ++j){
                if (j != 0) stream_out << " | ";
                stream_out << vec[j];
            }
            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 7:
    {
        stream_out << "Вы выбрали пункт 7\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        QString fileName = QDir::currentPath() + "/ВойноЛаб20_2.bin";
        std::ofstream file(fileName.toStdString(), std::ios::binary | std::ios::app);
        if (!file.is_open()) {
            stream_out << "Не удалось открыть файл" << fileName << "для запси\n";
        } else {
            House house;
            stream_out << "Введте колчество комнат\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            stream_in >> house.rooms;
            if (stream_in.status() != QTextStream::Ok || house.rooms < 0) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.rooms << '\n';
            }
            in.setText(text_in);

            stream_out << "Введте площадь\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            stream_in >> house.area;
            if (stream_in.status() != QTextStream::Ok || house.area < 0) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.area << '\n';
            }
            in.setText(text_in);

            stream_out << "Введте сдается ли в аренду(1 - да, 0 - нет)\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            int t;
            stream_in >> t;
            if (stream_in.status() != QTextStream::Ok) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                house.isTheHouseRentable = t;
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.isTheHouseRentable << '\n';
            }
            in.setText(text_in);

            stream_out << "Введте букву дома\n";
            out.setText(text_out);
            out.moveCursor(QTextCursor::End);
            in.setReadOnly(false);
            while (text_in.isEmpty()){
                QCoreApplication::processEvents();
            }
            stream_in >> house.letterOFHouse;
            if (stream_in.status() != QTextStream::Ok ) {
                stream_out << "Неверный ввод\n";
                stream_in.resetStatus();
                text_in.clear();
                file.close();
                stream_in.seek(0);
                break;
            } else {
                text_in.remove(0, stream_in.pos());
                stream_in.seek(0);
                stream_out << house.letterOFHouse << '\n';
            }
            in.setText(text_in);

            file.write(reinterpret_cast<const char*>(&house), sizeof(house));

            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 8:
    {
        stream_out << "Вы выбрали пункт 8\nСодержимое файла:\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        QString fileName = QDir::currentPath() + "/ВойноЛаб20_2.bin";
        std::ifstream file(fileName.toStdString(), std::ios::binary);
        if (!file.is_open()) {
            stream_out << "Не удалось открыть файл" << fileName << "для чтения\n";
        } else {
            House house;
            while (!file.eof()) {
                file.read(reinterpret_cast<char*>(&house), sizeof(house));
                if (file.eof()) break;
                stream_out << "Количество комнат: " << house.rooms << " ; ";
                stream_out << "Площадь: " << house.area << " ; ";
                stream_out << "Буква дома: " << house.letterOFHouse << " ; ";
                stream_out << "Есть сдается ли в аренду: " << (house.isTheHouseRentable ? "Да" : "Нет") << '\n';
            }
            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 9:
    {
        // QString fileName = QDir::currentPath() + "/ВойноЛаб20_3.txt";
        // QFile file(fileName);

        QString fileName = "ВойноЛаб20_3.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);

        QTextStream file_stream(&file);

        stream_out << "Вы выбрали пункт 9\nВведте абзац текста\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        text_in.clear();
        in.setReadOnly(false);
        while (text_in.isEmpty()){
            QCoreApplication::processEvents();
        }
        in.setReadOnly(true);
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для записи\n";
        } else {
            file_stream << text_in << '\n';
            file.close();
            text_in.clear();
            in.setText(text_in);
            stream_in.readAll();
            stream_out << "Текст успешно записан в файл\n";
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }
    case 10:
    {
        stream_out << "Вы выбрали пункт 10\nСодержимое файла:\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        // QString fileName = QDir::currentPath() + "/ВойноЛаб20_3.txt";
        // QFile file(fileName);

        QString fileName = "ВойноЛаб20_3.txt";
        QFile file(QCoreApplication::applicationDirPath() + "/" + fileName);

        QTextStream file_stream(&file);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            stream_out << "Не удалось открыть файл" << fileName << "для чтения\n";
        } else {
            QString line;
            while (!file_stream.atEnd()) {
                line = file_stream.readLine();
                stream_out << line << '\n';
            }
            file.close();
        }
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
        break;
    }

    default:
        stream_out << "Некорректный ввод. Пожалуйста, выберите пункт меню от 1 до 11.\n";
        out.setText(text_out);
        out.moveCursor(QTextCursor::End);
    }
    stream_out << "\n";
    out.setText(text_out);
    out.moveCursor(QTextCursor::End);
    in.setReadOnly(true);
}

