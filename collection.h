#ifndef STACK_H
#define STACK_H

//#pragma once

#include "complexnumber.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

template <typename T> class Stack
{
private:
    class Element
    {
        friend Stack;

    private:
        Element* nextElem;
        T* number;
        Element* prevElem;

    public:
        Element() //по умолчанию
        {
            number = new T();
            nextElem = nullptr;
            prevElem = nullptr;
        }

        Element(T* n) //инициализации
        {
            number = n;
            nextElem = nullptr;
            prevElem = nullptr;
        }

        Element(Element& e) //копирования
        {
            this->nextElem = e.nextElem;
            this->number = new T(*e.number);
            this->prevElem = e.prevElem;
        }

        ~Element() //деструктор
        {
            delete number;
        }

        friend bool operator !=(Element& e1, Element& e2)
        {
            return &e1 != &e2;
        }
    };

    class Iterator
    {
        friend Stack;

    private:
        Element* pos;
        Element* firstEl;
        Element* lastEl;

    public:

        Element& getCurrent()
        {
            return *(this->pos);
        }

        Iterator& next()
        {
            if (pos->nextElem)
                pos = pos->nextElem;
            return *this;
        }

        Iterator& prev()
        {
            if (pos->prevElem)
                pos = pos->prevElem;
            return *this;
        }

        T& value()
        {
            return *(pos->number);
        }

        Element& getLast()
        {
            return *(this->lastEl);
        }

        Element& getFirst()
        {
            return *(this->firstEl);
        }

        Iterator& setOnLast()
        {
            while (pos->prevElem)
                prev();
            return *this;
        }

        Iterator& setOnFirst()
        {
            while (pos->nextElem)
                next();
            return *this;
        }
    };

    Element* element;

    Element* firstElem;

    Element* lastElem;

    int stackSize;

public:
    Iterator* iter;

    T& last()
    {
        return *(lastElem->number);
    }

    Stack()
    {
        element = nullptr;
        firstElem = nullptr;
        lastElem = nullptr;
        stackSize = 0;
    }

    Stack(Stack<T>& s) //конструктор копирования стека
    {
        T cn;
        s.iter->setOnLast();

        while (s.iter->getCurrent() != s.iter->getFirst())
        {
            cn = s.iter->value();
            this->push(new T(cn));
            s.iter->next();
        }
        cn = s.iter->value();
        this->push(new T(cn));

        s.iter->setOnFirst();
    }

    void push(T* n) //помещает элемент в стек
    {
        if (element)
        {
            Element* e = element;

            element = new Element(n);

            (*e).nextElem = element;

            element->prevElem = e;

            firstElem = element;
            iter->firstEl = element;

            ++stackSize;

            iter->pos = element;

        }

        else if (!element)
        {
            element = new Element(n);

            firstElem = element;

            lastElem = element;

            iter = new Iterator();

            iter->pos = element;
            iter->firstEl = element;
            iter->lastEl = element;

            stackSize = 1;
        }
    }

    T* pop() //удаляет элемент из стека
    {
        if (!element) throw(new std::exception);

        Element* e = new Element(*element);
        T* n = new T(*(e->number));

        if (element->prevElem)
        {
            element->prevElem->nextElem = nullptr;

            delete element;

            element = e->prevElem;

            firstElem = element;

            iter->pos = element;

            --stackSize;

            delete e;

            return n;

        }
        else
        {
            delete element;

            element   = nullptr;
            firstElem = nullptr;
            lastElem  = nullptr;
            iter->pos = nullptr;

            --stackSize;

            delete e;

            return n;
        }
    }

    const bool saveToFile(std::string path) //сохранение
    {
        if (!size()) return false;

        std::fstream file(path);
        if (!file.is_open()) return false;

        try
        {
            std::string line;
            T n;
            while (&(*(iter->pos)) != &(iter->getLast()))
            {
                n = iter->value();
                iter->prev();
                line += n.to_string() + "\n";
            }
            line += n.to_string();

            file << line;
            file.close();

            return true;
        }
        catch (std::exception e)
        {
            throw(e);
        }
    }

    bool loadFromFile(std::string path) //загрузка из
    {
        std::fstream file(path);
        if (!file.is_open()) return false;

        try
        {
            std::string line;
            double realPart;
            double imaginePart;

            while (!file.eof())
            {
                std::getline(file, line);

                std::replace(line.begin(), line.end(), 'i', ' ');

                line.erase(std::remove_if(
                    line.begin(),
                    line.end(),
                    [l = std::locale{}](char ch) { return std::isspace(ch); }
                ), line.end());

                std::string delimiter = "+";
                size_t pos = 0;

                pos = line.find(delimiter);
                realPart = std::atof(line.substr(0, pos).c_str());
                line.erase(0, pos + delimiter.length());
                imaginePart = std::atof(line.c_str());

                push(new T(realPart, imaginePart));
            }

            file.close();
            return true;
        }
        catch (std::exception e)
        {
            throw(e);
        }
    }

    const bool operator ==(Stack& s)
    {
        if (this->size() != s.size()) return false;
        bool isEqual = true;

        this->iter->setOnFirst();
        s.iter->setOnFirst();

        while (this->iter->getCurrent() != this->iter->getLast())
        {
            if (this->iter->value() != s.iter->value()) isEqual = false;

            this->iter->prev();
            s.iter->prev();
        }
        if (this->iter->value() != s.iter->value()) isEqual = false;

        this->iter->setOnFirst();
        s.iter->setOnFirst();

        return isEqual;
    }

    void plus()
    {
        if (stackSize > 1)
        {
            T n1 = pop();
            T n2 = pop();

            push(new T(n1 + n2));
        }
    }

    void minus()
    {
        if (stackSize > 1)
        {
            T n1 = pop();
            T n2 = pop();

            push(new T(n1 - n2));
        }
    }

    void multiple()
    {
        if (stackSize > 1)
        {
            T n1 = pop();
            T n2 = pop();

            push(new T(n1 * n2));
        }
    }

    void divide()
    {
        if (stackSize > 1)
        {
            T n1 = pop();

            T n2 = pop();

            try
            {
                push(new T(n1 / n2));
            }
            catch (const std::exception& e)
            {
                std::cerr << "\tin class Stack\n";
                throw std::exception(e);
            }
        }
    }

    const int size() //размер стека
    {
        return stackSize;
    }

    bool empty() //удаление всех обьектов
    {
        T n;

        while (size())
        {
            n = pop();
            delete n;
        }
        return isEmpty();
    }

    const bool isEmpty() //проверка на пустоту
    {
        return !(stackSize > 0);
    }
};


#endif // STACK_H
