#pragma once
#include "Arch.h"
#include <list>

using namespace ArgumentsData;
int main(int argc, char** argv)
{
    // TESTING EXAMPLES BELOW
    // /f 25 /w gtrp4 /w 35 /n 10000 /file /filetxt 55 /f 25 /w str /numb 1000 /file - работает правильно - стандартный пример
    // /f 00000 /w 11111111111111111111111 /n -1 /n 5.5 /w 5,64 /f 1111111111111111 /n 9999999999999999999999 - работает правильно. при присвоении значения превышающего границы int берется максимальное значнеие.
    // empty test - работает правильно
    // 
    //Функция тест - вместо argc argv заводит свои значения для показа как работает программа. (запускает bLaunch) возвращает тру, если все мейн заданы
    //выход за пределы нормальных значений в тестах - слишком большие числа...
    cVecArgs cObj = cVecArgs();
    cObj.cAddArgument("Main.FileName", { "/f", "/file", "/fpath" }, "Full Path To Output File");        //может добавить в конструктор тип cVariable необходимый аргументу? удобно
    cObj.cAddArgument("NumbOfStrings", {"/n", "/num", "/numb"}, "Number Of Strings In File");
    cObj.cAddArgument("WidthOfString", {"/w", "/width", "/wdth"}, "Number Of Symbols In String");

    cObj.bLaunch(argc, argv);

    system("pause");
    return 0;
}