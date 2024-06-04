#pragma once

#include "namespace_consts.h"

using namespace std;

struct Node
{
    string *persons;
    Node *next;
    Node(string *_persons) : persons(_persons), next(nullptr) {}
};

struct list
{
    Node *first;
    Node *last;

    list() : first(nullptr), last(nullptr) {}

    ~list()
    {
        Node *p = first;
        while (p)
        {
            Node *next = p->next;
            delete p;
            p = next;
        }
    }

    inline bool isEmpty()
    {
        return first == nullptr;
    }

    void clear()
    {
        ofstream myFile(constText::defaultPath);
        myFile.clear();
        first = nullptr;
        last = nullptr;
    }

    void pushBack(string *_val)
    {
        Node *p = new Node(_val);
        if (isEmpty())
        {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void printToConsole()
    {
        if (isEmpty())
            return;
        Node *p = first;
        try
        {
            while (p)
            {
                for (uint8_t i = 0; i < 5; i++)
                    cerr << p->persons[i];
                cerr << endl;
                p = p->next;
            }
        }
        catch (...)
        {
            cerr << "Ошибка печати списка" << endl;
            return;
        }
    }

    void printInFile()
    {
        if (isEmpty())
            return;
        Node *p = last;
        ofstream myFile(constText::defaultPath, ios::app);
        while (p)
        {
            if (myFile.is_open())
            {
                for (uint8_t i = 0; i < 5; i++)
                    myFile << p->persons[i];
                myFile << endl;
                p = p->next;
            }
        }
        myFile.close();
    }

    void readFromFile()
    {
        first = nullptr;
        last = nullptr;
        ifstream myReadFile(constText::defaultPath);
        string myText;
        while (getline(myReadFile, myText))
        {
            string *data = new string[5];
            uint8_t j = 0;
            for (uint8_t i = 0; i < myText.length(); i++)
            {
                if (myText[i] == ';')
                    j++;
                j < 4 ? data[j] += myText[i] : data[4] += myText[i];
            }
            pushBack(data);
        }
        myReadFile.close();
    }

    list findElements(string target, short field)
    {
        list resultList;
        Node *current = first;

        while (current != nullptr)
        {
            if (current->persons[field].find(target) != string::npos)
                resultList.pushBack(current->persons);
            current = current->next;
        }

        return resultList;
    }
};