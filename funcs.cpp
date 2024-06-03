#include "head.h"

int32_t menuChoice()
{
    string userChoice;
    getline(cin, userChoice);
    if (isdigit(userChoice[0]) && userChoice.size() == 1 && stoi(userChoice) < 6 && stoi(userChoice) > 0)
    {
        if (userChoice != "0")
            return stoi(userChoice);
    }
    cerr << "Введите цифру от 1 до 5" << endl;
    return menuChoice();
}

void runApp()
{
    list newPerson;
    newPerson.readFromFile();
    while (1)
    {
        cerr << constText::menu;
        switch (menuChoice())
        {
        case 1:
        {
            cerr << "Задайте содержание нового элемента по образцу:" << endl;
            cerr << "фамилия;имя;отчество;должность;страна;республика;город;улица;дом;квартира" << endl;
            userAddNewPerson(newPerson);
            newPerson.readFromFile();
            break;
        }
        case 2:
        {
            findEls(newPerson);
            break;
        }
        case 3:
        {
            cerr << "\t*** Вывод всего содержимого ***" << endl
                 << endl;
            newPerson.printToConsole();
            cerr << endl
                 << "\t\t  ********" << endl
                 << endl;
            break;
        }
        case 4:
        {
            newPerson.clear();
            cerr << endl
                 << "Данные обнулены" << endl;
            break;
        }
        case 5:
            exit(1);
        }
    }
}

void userAddNewPerson(list &newPerson)
{
    string userInputData;
    getline(cin, userInputData);
    stringstream streamInputData;
    streamInputData << userInputData;
    string checkUserInputData;
    uint8_t count = 0;
    string *dataPerson = new string[5];
    if (dataPerson == nullptr)
    {
        cerr << "Ошибка выделения памяти" << endl;
        return userAddNewPerson(newPerson);
    }
    while (getline(streamInputData, checkUserInputData, ';'))
    {
        if (checkUserInputData == "\0")
        {
            cerr << "Введены недопустимые символы, повтроите попытку" << endl;
            return userAddNewPerson(newPerson);
        }
        count++;
        if (count < 9)
        {
            for (size_t i = 0; i < checkUserInputData.size(); i++)
            {
                if (isdigit(checkUserInputData[i]) || checkUserInputData[i] == ' ' || checkUserInputData[i] == '\0')
                {
                    cerr << "Введены недопустимые символы, повтроите попытку" << endl;
                    return userAddNewPerson(newPerson);
                }
            }
            if (count < 5)
                dataPerson[count - 1] = checkUserInputData + ';';
            else
                dataPerson[4] += checkUserInputData + ';';
        }
        else if (count > 8 && count < 11)
        {
            if (checkUserInputData.size() < 4 && checkUserInputData.size() > 0)
            {
                for (size_t i = 0; i < checkUserInputData.size(); i++)
                {
                    if (checkUserInputData.size() == 1 && checkUserInputData[0] == '-')
                        break;
                    if (!isdigit(checkUserInputData[i]) || checkUserInputData[i] == ' ' || checkUserInputData[i] == '\0')
                    {
                        cerr << "Введены недопустимые символы, повтроите попытку" << endl;
                        return userAddNewPerson(newPerson);
                    }
                }
                dataPerson[4] += count == 9 ? checkUserInputData + ';' : checkUserInputData;
            }
            else
            {
                cerr << "Введите дом и квартиру от 1 до 999 или -" << endl;
                return userAddNewPerson(newPerson);
            }
        }
    }
    newPerson.pushBack(dataPerson);
    newPerson.printInFile();
    delete[] dataPerson;
}

void findEls(list &newPerson)
{
    cerr << "Введите символы, по которым осуществить поиск: ";
    string field;
    getline(cin, field);
    list result = newPerson.findElements(field);
    if (!result.isEmpty())
    {
        cerr << "\t*** Все совпавшие фамилии ***" << endl
             << endl;
        for (Node *node = result.first; node != nullptr; node = node->next)
        {
            for (uint8_t i = 0; i < 5; i++)
                cerr << node->persons[i];
            cerr << endl;
        }
        cerr << endl
             << "\t\t  ********" << endl
             << endl;
    }
    else
        cerr << "Совпадений не найдено" << endl
             << endl;
}