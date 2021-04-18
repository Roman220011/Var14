#include "govern.h"


government::government() {}
government::government(std::string name, std::string capital, 
							size_t area, size_t population, size_t gdp) 
{
	this->name = name;
	this->capital = capital;
	this->area = area;
	this->population = population;
	this->gdp = gdp;
}

void government::printItem() 
{
	std::cout << this->name    << "\t"
			  << this->capital << "\t"
			  << this->area << "\t"
			  << this->population << "\t"
			  << this->gdp << "\n";
}

void list::edit() 
{
	std::string initial;
    std::string field;

    std::cout << "Введите страну, поле которой хотите изменить: "; 
        std::cin >> initial;
    std::cout << "Введите название поля: "; 
        std::cin >> field;

    std::string bufer;
    size_t value;

    std::cout << "Введите новое значение поля: "; 
    if (field == "name" || field == "capital") {
        std::cin >> bufer;
    } else 
    if (field == "area" || field == "population" || field == "gdp") {
        std::cin >> value;
    }

    for (list * tmp = this; tmp; tmp = tmp->next) 
	{
        if (tmp->data->name == initial) 
		{
			if (field == "name") {
                tmp->data->name = bufer;
            } else 
            if (field == "capital") {
                tmp->data->capital = bufer;
            } else
            if (field == "area") {
                tmp->data->area = value;
            } else
            if (field == "population") {
                tmp->data->population = value;
            } else
            if (field == "gdp") {
                tmp->data->gdp = value;
            }
        }
    }
}

government * list::findAndPrint(std::string initial) 
{
	government * needed = nullptr; 
    for (list * tmp = this; tmp; tmp = tmp->next) 
	{
        if (tmp->data->name == initial) 
		{
            tmp->data->printItem();
			needed = tmp->data;
        }
    }
	return needed;
}

void list::print() 
{
    for (list * tmp = this; tmp; tmp = tmp->next) 
	{
        tmp->data->printItem();
    }
    std::cout << "\n";
};

size_t list::size() 
{
    size_t i = 0;
    for (list * tmp = this; tmp; tmp = tmp->next) {
        i++;
    }
    return i;
}

void createList(list *& tmp, std::string name, std::string capital, 
				size_t area, size_t population, size_t gdp) 
{
	if (!tmp) {
		tmp = new list;
		tmp->data = new government({name, capital, area, population, gdp});
	}
}
void push(list * tmp, std::string name, std::string capital, 
		  size_t area, size_t population, size_t gdp) 
{
	if (!tmp) {
		std::cout << "Список не создан\n";
		return;
	}

	while (tmp) {

		if (!tmp->next) 
		{
			list * item = new list;
			item->data = new government({name, capital, area, population, gdp});
			tmp->next = item;
			return;
		}

		else 
		{
			tmp = tmp->next;
		}

	}

}
void openFile(std::ifstream & f, list *& tmp) 
{
	std::string bufer;

	f.open("in.txt");
	if ( !f.is_open() ) {
		std::cout << "Файл не найден";
		return;
	}

    while( getline(f, bufer) ) {
        size_t pos1 = bufer.find(" ");
        size_t pos2 = bufer.find(" ", pos1 + 1);
        
        std::string name = bufer.substr(0, pos1);
        std::string capital = bufer.substr(pos1 + 1, pos2 - pos1 - 1);

        pos1 = pos2;
        pos2 = bufer.find(" ", pos1 + 1);
        size_t area = stoull( bufer.substr(pos1 + 1, pos2 - pos1 - 1) );

        pos1 = pos2;
        pos2 = bufer.find(" ", pos1 + 1);
        size_t population = stoull( bufer.substr(pos1 + 1, pos2 - pos1 - 1) );

        pos1 = pos2;
        pos2 = bufer.find(" ", pos1 + 1);
        size_t gdp = stoull( bufer.substr(pos1 + 1) );

		if (!tmp) {
			createList(tmp, name, capital, area, population, gdp);
			continue;
		}

        push(tmp, name, capital, area, population, gdp);
    }

	f.close();
}
void writeToFile(std::ofstream & f, list * h) 
{
	if (!h) {
		std::cout << "Список не создан\n";
		return;
	}

	f.open("out.txt");
	if ( !f.is_open() ) {
		std::cout << "Файл не найден";
		return;
	}

	for (list * tmp = h; tmp; tmp = tmp->next) {
        f << tmp->data->name    << "\t"
		  << tmp->data->capital << "\t"
		  << tmp->data->area << "\t"
		  << tmp->data->population << "\t"
		  << tmp->data->gdp << "\n";
	}

	f.close();
}
void erase(list * tmp, std::string compare) 
{
	if (!tmp) {
		std::cout << "Список не создан\n";
		return;
	}

	while (tmp && tmp->next) 
	{
		if (tmp->next->data->name == compare) 
		{
			list * elem = tmp->next->next;
			delete tmp->next->data;
			delete tmp->next;
			tmp->next = elem;
			return;
		}
		else 
		{
			tmp = tmp->next;
		}
	}
}
void add(list *& tmp, std::string name, std::string capital, 
		 size_t area, size_t population, size_t gdp, size_t idx) 
{
	if (!tmp) {
		std::cout << "Список не создан\n";
		return;
	}

	list * inter = tmp;
	if ( idx >= inter->size() ) {
		return;
	}

	list * item = new list;
	item->data = new government({name, capital, area, population, gdp});

	if (idx == 0) {
		item->next = tmp;
		tmp = item;
		return;
	}

	size_t i = 0;
	while (inter) {

		if (i + 1 == idx) 
		{
			item->next = inter->next;
			inter->next = item;
			return;
		}
		else 
		{
			inter = inter->next;
			i++;
		}

	}
}
void sort(list * h) 
{
	if (!h) {
		std::cout << "Список не создан\n";
		return;
	}
    
	for (list * tmp1 = h; tmp1; tmp1 = tmp1->next) 
	{
		for (list * tmp2 = tmp1->next; tmp2; tmp2 = tmp2->next) 
		{
        	if (tmp1->data->name > tmp2->data->name) 
			{
				std::swap(tmp1->data, tmp2->data);
			}
		}
	}
}
void clear(list *& h) 
{
	if (!h) {
		std::cout << "Список не создан\n";
		return;
	}

	while (h) {
		list * tmp = h->next;
		delete h->data;
		delete h;
		h = tmp;
	}
}