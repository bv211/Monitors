#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

enum MatrixType { CRT, IPS, LED };

enum Menu { EXIT, NEW_MONITORS, PRINT, EDIT, SEARCH };

struct Monitor {
	string product;
	string model;
	float price{};
	float inches{};
	bool is_available{ true };
	MatrixType matrix_type{};
};

string get_matrix_name(MatrixType type);

template <class T>
T get_value(T count);

template <class T>
T get_value();

MatrixType get_value_matrix();

Monitor create_monitor();

void create_monitors(Monitor*& monitors, int& size);

void print_monitor(const Monitor& monitor);

void print_monitors(Monitor* monitors, int size);

void print_list_matrix();

void print_menu();

void edit_monitor(Monitor* monitors, int size);

void search_by_product(Monitor* monitors, int& size);

void select_menu(Monitor* monitors, int& size);

void delete_monitors(Monitor*& monitors) {
	if (monitors != nullptr)
		delete[] monitors;
}

bool is_monitors_empty(Monitor* monitors, int& size) {
	return monitors == nullptr || size == 0;
}

int main() {
	setlocale(0, "");
	SetConsoleCP(1251);

	int size{};
	Monitor* monitors = nullptr;

	select_menu(monitors, size);

	delete_monitors(monitors);

	return 0;
}

string get_matrix_name(MatrixType type) {
	switch (type)
	{
	case CRT:
		return "CRT";

	case IPS:
		return "IPS";

	case LED:
		return "LED";

	default:
		return "UNKNOWN";
	}
}

template <class T>
T get_value(T count) {
	T value{};

	do
	{
		cin >> value;
	} while (value < 0 || value > count);

	cin.ignore();
	return value;
}

template<class T>
T get_value()
{
	T value{};

	do
	{
		cin >> value;
	} while (value < 0);

	return value;
}

MatrixType get_value_matrix() {
	int count = 2;
	int value = get_value(count);
	return (MatrixType)value;
}

Monitor create_monitor() {
	string product;
	string model;
	float price;
	float inches;
	bool is_available = true;
	MatrixType matrix_type;

	cout << "Введите производителя:" << endl;
	getline(cin, product);

	cout << "Введите модель:" << endl;
	getline(cin, model);

	cout << "Выберите матрицу:" << endl;
	print_list_matrix();
	matrix_type = get_value_matrix();

	cout << "Введите дюймы:" << endl;
	inches = get_value<float>();

	cout << "Введите цену:" << endl;
	price = get_value<float>();

	cin.ignore();
	return Monitor{
		product, model,
		price, inches,
		is_available, matrix_type };
}

void print_monitor(const Monitor& monitor) {
	cout << "Производитель: " <<
		monitor.product << endl;

	cout << "Модель: " <<
		monitor.model << endl;

	cout << "Матрица: " <<
		get_matrix_name(monitor.matrix_type) << endl;

	cout << "Дюймы: " <<
		monitor.inches << endl;

	cout << "Цена: $" <<
		monitor.price << endl;

	cout << "Доступен: " <<
		(monitor.is_available ?
			"в наличии" : "нет в наличии") << endl;
}

void print_monitors(Monitor* monitors, int size) {
	if (is_monitors_empty(monitors, size)) {
		cout << "Список пуст!" << endl;
		system("pause");
		return;
	}

	for (int i = 0; i < size; i++) {
		cout << i + 1 << '.' << endl;
		print_monitor(monitors[i]);
		cout << "-------------------" << endl;
	}
}

void print_list_matrix()
{
	cout << MatrixType::CRT << " CRT" << endl;
	cout << MatrixType::IPS << " IPS" << endl;
	cout << MatrixType::LED << " LED" << endl;
}

void print_menu() {
	cout << "1. Создать новый список мониторов" << endl;
	cout << "2. Вывести на экран" << endl;
	cout << "3. Редактировать монитор" << endl;
	cout << "4. Поиск" << endl;
	cout << "0. Выход" << endl;
}

void edit_monitor(Monitor* monitors, int size) {
	if (is_monitors_empty(monitors, size)) {
		cout << "Нет мониторов для редактирования" << endl;
		system("pause");
		return;
	}

	cout << "Выберите монитор для "
		"редактирования" << endl;

	print_monitors(monitors, size);

	int index = get_value(size);
	index = index > 0 ? index - 1 : index;
	monitors[index] = create_monitor();
}

void create_monitors(Monitor*& monitors, int& size) {
	cout << "Введите кол-во мониторов (не больше 10):" << endl;
	int count{ 10 };

	delete_monitors(monitors);

	size = get_value(count);
	monitors = new Monitor[size];

	for (int i = 0; i < size; i++) {
		cout << "Монитор " << i + 1 << endl;
		monitors[i] = create_monitor();
	}
}

void search_by_product(Monitor* monitors, int& size) {
	const int buffer_size = 50;
	char product[buffer_size];
	int count{};

	cout << "Введите производителя" << endl;
	gets_s(product, buffer_size);

	for (int i = 0; i < size; i++) {
		Monitor& monitor = monitors[i];

		auto found = _strnicmp(monitor.product.data(), product, strlen(product));
		if (found != 0)
			continue;

		print_monitor(monitor);
		count++;
	}

	cout << "Найденных элементов: " << count << endl;
}

void select_menu(Monitor* monitors, int& size)
{
	Menu value;
	int count_menu = 4;

	do
	{
		system("cls");
		print_menu();

		value = (Menu)get_value(count_menu);
		system("cls");

		switch (value)
		{
		case EXIT:
			cout << "До свидания!" << endl;
			break;
		case NEW_MONITORS:
			create_monitors(monitors, size);
			break;
		case PRINT:
			print_monitors(monitors, size);
			break;
		case EDIT:
			edit_monitor(monitors, size);
			break;
		case SEARCH:
			search_by_product(monitors, size);
			break;
		}
		system("pause");
	} while (value != Menu::EXIT);
}