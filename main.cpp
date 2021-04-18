#include "govern.h"

int main(int argc, char *argv[])
{
	int choice = 0;
    std::string name;
	std::string capital;
	size_t area;
	size_t population;
	size_t gdp;
	size_t id;

    list * head = nullptr;
    government * item = nullptr;

    std::ifstream fin;
	std::ofstream fout;

    std::cout << "Меню:\n"
              << "1: Считать данные с файла \"in.txt\".\n"
              << "2: Найти элемент и вывести на экран.\n"
              << "3: Сортировать по алфавиту.\n"
              << "4: Найти и изменить элемент.\n"
              << "5: Добавить элемент в конец списка.\n"
              << "6: Удалить произвольный элемент.\n"
              << "7: Добавить элемент в любое место списка.\n"
              << "8: Записать в файл \"out.txt\".\n"
              << "9: Вывести список.\n"
              << "10: Удалить список.\n"
              << "0: Выйти из программы.\n\n";

    do {
        std::cin >> choice;
        switch (choice) {
            case 1 : 
                openFile(fin, head);
                break;
            case 2 :
                std::cout << "Введите название страны: ";
                std::cin >> name;
                item = new government;
                item = head->findAndPrint(name);
                break;
            case 3 :
                sort(head);
                break;
            case 4 :
                head->edit();
                break;
            case 5 :
				std::cout << "Введите название страны: "; std::cin >> name;
				std::cout << "Введите столицу страны: "; std::cin >> capital;
				std::cout << "Введите площадь страны: "; std::cin >> area;
				std::cout << "Введите численность населения страны: "; std::cin >> population;
				std::cout << "Введите объём ВВП страны: "; std::cin >> gdp;
                push(head, name, capital, area, population, gdp);
                break;
            case 6 :
				std::cout << "Введите название страны: "; std::cin >> name;
                erase(head, name);
                break;
            case 7 :
				std::cout << "Введите место, куда вы хотите вставить новый элемент: "; std::cin >> id;
				std::cout << "Введите название страны: "; std::cin >> name;
				std::cout << "Введите столицу страны: "; std::cin >> capital;
				std::cout << "Введите площадь страны: "; std::cin >> area;
				std::cout << "Введите численность населения страны: "; std::cin >> population;
				std::cout << "Введите объём ВВП страны: "; std::cin >> gdp;
                add(head, name, capital, area, population, gdp, id);
                break;
            case 8 :
                writeToFile(fout, head);
                break;
            case 9 :
                head->print();
                break;
            case 10 :
                clear(head);
                break;
            case 0 :
                break;
            default :
                std::cout << "There is no such a comand.\n";
        }
    } while (choice != 0);

    if (item) {
        delete item;
    }

	return 0;
}