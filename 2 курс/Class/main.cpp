#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
using namespace std;


const int maxn = 100;


class Employee
{
private:
	char* name;
	int year; //year of birth
	float salary;
	char date[11]; //date of receipt

public:
	
	Employee()
	{
		name = new char[31];
		year = 0;
		salary = 0.0;
		date[0] = '\0';
		//printf("Default constructor employee working\n");
	}
	Employee(int n)
	{
		name = new char[n];
		year = 0;
		salary = 0.0;
		date[0] = '\0';
		//printf("Constructor employee working\n");
	}
	~Employee()
	{
		delete[] name;
		//printf("Destructor employee working\n");
	}

	Employee(const Employee& employee_)
	{
		
		name = new char[strlen(employee_.name)+1];
		strcpy(name, employee_.name);
		year = employee_.year;
		salary = employee_.salary;
		strcpy(date, employee_.date);
	}

	Employee operator = (Employee& employee_)
	{
		if (&employee_ == this) return *this;
		delete[] name;
		name = new char[strlen(employee_.name) + 1];
		strcpy(name, employee_.name);
		year = employee_.year;
		salary = employee_.salary;
		strcpy(date, employee_.date);

		return *this;
	}

	void Set_Name(const char* name_)
	{
		strcpy(name, name_);
	}

	void Set_Year(const int year_)
	{
		year = year_;
	}

	void Set_Salary(const float salary_)
	{
		salary = salary_;
	}

	void Set_Date(const char* date_)
	{
		strcpy(date, date_);
	}

	char* Get_Name()
	{
		return name;
	}

	int Get_Year()
	{
		return year;
	}

	float Get_Salary()
	{
		return salary;
	}

	char* Get_Date()
	{
		return date;
	}

	void Print_Info() 
	{
		printf("%-30s  \t| %d\t| %-14.2f| %s\t|", name, year, salary, date);
	}

	int Input_Info() 
	{
		char initials[5];

		if (!scanf("%s %s %d %f %s", name, initials, &year, &salary, date))
			return 4;

		
		strcat(name, " ");
		if (initials[4] != '\0')
			return 3;
		strcat(name, initials);
		return 0;
	}

	bool Sif(const char* str_)
	{
		return !strcmp(name, str_);
	}


};

class Base
{
private:
	Employee* arr;
	int size;
	int max_size;

public:
	
	Base()
	{
		max_size = maxn;
		arr = new Employee[max_size];
		size = 0;
		//printf("Default constructor base working\n");
	}

	Base(int size_)
	{
		int i = 1;
		for (i = 1; 100 * i < size_; ++i);
		max_size = 100 * i;
		arr = new Employee[max_size];
		size = 0;
		//printf("Constructor base working\n");
	}

	~Base()
	{
		delete[] arr;
		//printf("Destructor base working\n");
	}

	Base(const Base& base_)
	{
		arr = new Employee[base_.max_size];
		size = base_.size;
		max_size = base_.max_size;
		for (int i = 0; i < size; ++i)
		{
			arr[i] =	base_.arr[i];
		}
		
	}

	Employee& operator[](int i)
	{
		if (i >= 0 && i < size)
			return arr[i];

		throw 1;
	}

	Employee Get_Employee(int i_)
	{
		return arr[i_];
	}
	

	void Set_Arr(Employee** arr_)
	{
		arr = *arr_;
	}

	void Set_Size(int size_)
	{
		size = size_;
	}

	Employee* Get_Arr()
	{
		return arr;
	}

	int Get_Size()
	{
		return size;
	}

	int Get_Max_Size()
	{
		return max_size;
	}


	int Create_Base_F(const char* file_name_)
	{
		FILE* file;
		fopen_s(&file, file_name_, "r");
		if (!file)
			return 1;


		char surname[31];
		char initials[5];
		int year = 0;
		float salary = 0.0;
		char date[11];
		size = 0;

		while (fscanf(file, "%s %s %d %f %s", surname, initials, &year, &salary, date) != EOF)
		{
			strcat(surname, " ");
			if (initials[4] != '\0')
				return 3;
			strcat(surname, initials);
			arr[size].Set_Name(surname);
			arr[size].Set_Year(year);
			arr[size].Set_Salary(salary);
			arr[size].Set_Date(date);

			size++;
			if (size == max_size)
				Expansion_Base();
		}
		fclose(file);
		return 0;
	}

	int Print_Base()
	{
		printf("            NAME                                | YEAR  |   SALARY      |     DATE      |\n");
		printf("------------------------------------------------|-------|---------------|---------------|\n");
		for (int i = 0; i < size; ++i)
		{
			printf("  %d.\t", i+1);
			arr[i].Print_Info();
			printf("\n");
		}
		printf("------------------------------------------------^-------^---------------^---------------/\n");
		return 0;
	}

	int Add_from_class(Employee& employee_)
	{
		int i;
		for (i = size - 1; (i >= 0) && (strcmp(arr[i].Get_Name(), employee_.Get_Name()) > 0); --i)
		{
			arr[i + 1] = arr[i];
		}
		++i;

		arr[size++] = employee_;

		if (size == max_size)
			Expansion_Base();

		return 0;
	}

	int Add_from_file(char* filename_)
	{

		Base temp;
		temp.Create_Base_F(filename_);


		for (int i = 0; i < temp.Get_Size(); ++i)
		{
			int j = size - 1;
			for (; (j >= 0) && (strcmp(arr[j].Get_Name(), temp.arr[i].Get_Name()) > 0); --j)
			{
				arr[j + 1] = arr[j];
			}
			++j;

			arr[j].Set_Name(temp.arr[i].Get_Name());
			arr[j].Set_Date(temp.arr[i].Get_Date());
			arr[j].Set_Salary(temp.arr[i].Get_Salary());
			arr[j].Set_Year(temp.arr[i].Get_Year());
			size++;

			if (size == max_size)
				Expansion_Base();
		}


		if (size == max_size)
			Expansion_Base();


		return 0;
	}

	/*int Add_from_classes(Employee* employee_, int& size_)
	{

		for (int i = 0; i < size_; ++i)
		{
			int j = size - 1;
			for (; (j >= 0) && (strcmp(arr[j].Get_Name(), employee_[i].Get_Name()) > 0); --j)
			{
				arr[j + 1] = arr[j];
			}
			++j;

			arr[j].Set_Name(employee_[i].Get_Name());
			arr[j].Set_Date(employee_[i].Get_Date());
			arr[j].Set_Salary(employee_[i].Get_Salary());
			arr[j].Set_Year(employee_[i].Get_Year());
			size++;

			if (size == max_size)
				Expansion_Base();
		}
		if (size == max_size)
			return 2;

		return 0;
	}*/

	int Add(const char* name_, int year_, float salary_, const char* date_)
	{
		int i = size - 1;
		for (; (i >= 0) && (strcmp(arr[i].Get_Name(), name_) > 0); --i)
		{
			arr[i + 1] = arr[i];
		}
		++i;

		arr[i].Set_Name(name_);
		arr[i].Set_Date(date_);
		arr[i].Set_Salary(salary_);
		arr[i].Set_Year(year_);
		
		size++;

		if (size == max_size)
			Expansion_Base();

		return 0;
	}
	
	int Delete_Note(const char* name_)
	{
		int index = Find_Data_on_Name(name_);
		if (index < 0)
			return 0;

		for (; index < size; ++index)
			arr[index] = arr[index + 1];

		--size;
		return 0;
	}

	int Find_Data_on_Name(const char* name_)
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i].Sif(name_))
				return i;
		}
		return -1;
	}

	int Edit_Data(const int choice_)
	{
		Print_Base();
		printf("Select a name to change: ");
		char temp_name[31];
		char temp_initials[5];
		if (!scanf("%s %s", temp_name, temp_initials))
			return 4;
		if (temp_initials[4] != '\0')
			return 3;
		strcat(temp_name, " ");
		strcat(temp_name, temp_initials);
		printf("\n");
		switch (choice_)
		{
		case(1):
			char new_name[31];
			char new_initials[5];
			printf("Enter a new name: ");
			if (!scanf("%s %s", new_name, new_initials))
				return 4;
			if (new_initials[4] != '\0')
				return 3;
			strcat(new_name, " ");
			strcat(new_name, new_initials);
			if (Edit_Name(new_name, temp_name) == -1)
				return -1;
			return 0;
		case(2):
			float new_salary;
			printf("Enter a new salary: ");
			if (!scanf("%f", &new_salary))
				return 4;
			Edit_Salary(new_salary, temp_name);
			return 0;

		default:
			printf("The command was not found");
			return 0;
		}
		return 0;
	}

	int Edit_Name(char* name_, char* old_name_)
	{
		int index = Find_Data_on_Name(old_name_);
		if (index == -1)
			return -1;
		int old_year = arr[index].Get_Year();
		float old_salary = arr[index].Get_Salary();
		char old_date[11];
		strcpy(old_date, arr[index].Get_Date());

		Delete_Note(old_name_);
		Add(name_, old_year, old_salary, old_date);

		return 0;
	}

	int Edit_Salary(float salary_, char* name_)
	{
		arr[Find_Data_on_Name(name_)].Set_Salary(salary_);
		return 0;
	}

	int Copy_Base_into_File(const char* file_name_)
	{
		FILE* file;
		fopen_s(&file, file_name_, "w");
		if (!file)
			return 1;

		for (int i = 0; i < size; ++i)
		{
			fprintf(file,"%s %d %f %s\n", arr[i].Get_Name(), arr[i].Get_Year(), arr[i].Get_Salary(), arr[i].Get_Date());
		}

		fclose(file);
		return 0;
	}

	int Expansion_Base()
	{
		Base temp(max_size);

		for (int i = 0; i < max_size; ++i)
		{
			temp[i] = arr[i];
		}
		max_size = max_size * 2;
		delete[] arr;
		arr = new Employee[max_size];

		for (int i = 0; i < temp.max_size; ++i)
		{
			arr[i] = temp[i];
		}
		return 0;
	}

	void Merge(int left, int mid, int right)
	{
		int n1 = mid - left + 1;
		int n2 = right - mid;


		Employee* L = new Employee[right];
		Employee* R = new Employee[right];

		for (int i = 0; i < n1; i++)
		{
			L[i].Set_Name(arr[left + i].Get_Name());
			L[i].Set_Year(arr[left + i].Get_Year());
			L[i].Set_Salary(arr[left + i].Get_Salary());
			L[i].Set_Date(arr[left + i].Get_Date());
		}
		for (int j = 0; j < n2; j++)
		{
			R[j].Set_Name(arr[mid + 1 + j].Get_Name());
			R[j].Set_Year(arr[mid + 1 + j].Get_Year());
			R[j].Set_Salary(arr[mid + 1 + j].Get_Salary());
			R[j].Set_Date(arr[mid + 1 + j].Get_Date());
		}

		int i = 0, j = 0;
		int k = left;

		while (i < n1 && j < n2) {
			if (strcmp(L[i].Get_Name(), R[j].Get_Name()) < 0) {
				arr[k].Set_Name(L[i].Get_Name());
				arr[k].Set_Year(L[i].Get_Year());
				arr[k].Set_Salary(L[i].Get_Salary());
				arr[k].Set_Date(L[i].Get_Date());
				i++;
			}
			else {
				arr[k].Set_Name(R[j].Get_Name());
				arr[k].Set_Year(R[j].Get_Year());
				arr[k].Set_Salary(R[j].Get_Salary());
				arr[k].Set_Date(R[j].Get_Date());
				j++;
			}
			k++;
		}


		while (i < n1) {
			arr[k].Set_Name(L[i].Get_Name());
			arr[k].Set_Year(L[i].Get_Year());
			arr[k].Set_Salary(L[i].Get_Salary());
			arr[k].Set_Date(L[i].Get_Date());
			i++;
			k++;
		}


		while (j < n2) {
			arr[k].Set_Name(R[j].Get_Name());
			arr[k].Set_Year(R[j].Get_Year());
			arr[k].Set_Salary(R[j].Get_Salary());
			arr[k].Set_Date(R[j].Get_Date());
			j++;
			k++;
		}
		delete[] L;
		delete[] R;
	}

	void MergeSort(int left, int right)
	{
		if (left >= right)
			return;

		int mid = left + (right - left) / 2;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, mid, right);
	}
};



int Create_F(const char* file_name_, int& size, Employee* arr)
{
	FILE* file;
	fopen_s(&file, file_name_, "r");
	if (!file)
		return 1;

	char surname[31];
	char initials[5];
	int year = 0;
	float salary = 0.0;
	char date[11];
	size = 0;

	while (fscanf(file, "%s %s %d %f %s", surname, initials, &year, &salary, date) != EOF)
	{
		strcat(surname, " ");
		if (initials[4] != '\0')
			return 3;
		strcat(surname, initials);
		arr[size].Set_Name(surname);
		arr[size].Set_Year(year);
		arr[size].Set_Salary(salary);
		arr[size].Set_Date(date);

		size++;
		if (size > maxn)
			return 2;
	}
	

	return 0;
}

float Request_1(Employee* arr_, int size_, int current_year_, int& k, char** FIO_25years)
{
	k = 0;
	float average_salary = 0;
	char* date_employee = new char[11];
	int year_employee = 0;

	for (int i = 0; i < size_; ++i)
	{
		date_employee = arr_[i].Get_Date();

		year_employee = (date_employee[6] - '0') * 1000 + (date_employee[7] - '0') * 100 + (date_employee[8] - '0') * 10 + (date_employee[9] - '0');

		if (current_year_ - year_employee > 25)
		{
			strcpy(FIO_25years[k], arr_[i].Get_Name());
			++k;
			average_salary += arr_[i].Get_Salary();
		}
	}

	if (k != 0)
		average_salary /= k;

	return average_salary;
}

void Menu()
{
	printf("1. Print base\n");
	printf("2. Add new note\n");
	printf("3. Add new notes from file\n");
	printf("4. Delete note from base\n");
	printf("5. Edit note\n");
	printf("6. Copy base into file\n");
	printf("7. Request 1\n");
	printf("8. Sort base\n");
}


int main()
{
	//setlocale(LC_ALL, "RUS");  //setlocale(LC_ALL, ".1251"); // Не работает
	SetConsoleCP(1251); //из Windows.h для ввода
	SetConsoleOutputCP(1251); //для вывода
	printf("Enter the name file: \n>>");
	char file_name[maxn];
	if (!scanf("%s", file_name))
		return 4;
	

	Base base;
	if (base.Create_Base_F(file_name) == 2)
		base.Expansion_Base();
	printf("\n Done\n\n");

	Employee emp[maxn];
	char file_name3[maxn];

	char file_name6[maxn];

	Employee arr3[maxn];
	char** FIO_25years = new char* [maxn];

	while (1)
	{
		system("cls");
		int choice;
		printf("What do you need?\n");

		Menu();
		printf("> ");
		if (!scanf("%d", &choice))
			return 4;

		system("cls");

		switch (choice)
		{
		case 1:
			base.Print_Base();

			system("pause");
			continue;

		case 2:
			char name2[31];
			char initials2[10];
			int year2;
			float salary2;
			char date2[11];

			printf("Enter name, year of birth, salary, and date of employment: \n> ");
			if (!scanf("%s %s %d %f %s", name2, initials2, &year2, &salary2, date2))
				return 4;

			strcat(name2, " ");
			if (initials2[4] != '\0')
				return 3;
			strcat(name2, initials2);

			base.Add(name2, year2, salary2, date2);

			printf("\nDone\n\n");

			system("pause");
			continue;
		case 3:

			printf("Enter the name file: \n>");
			if (!scanf("%s", file_name3))
				return 4;

			while (base.Add_from_file(file_name3) == 2) { base.Expansion_Base(); }

			printf("\nDone\n\n");
			system("pause");
			continue;

		case 4:

			char name[31];
			char initials[5];

			base.Print_Base();

			printf("Enter the name of whom you want to delete: \n>");
			if (!scanf("%s %s", name, initials))
				return 4;

			strcat(name, " ");
			if (initials[4] != '\0')
				return 3;
			strcat(name, initials);

			base.Delete_Note(name);

			printf("\nDone\n\n");
			system("pause");
			continue;

		case 5:
			int choice_edit;
			printf("What do you want to change?\n");
			printf("1. Name\n");
			printf("2. Salary\n> ");
			if (!scanf("%d", &choice_edit))
				return 4;
			system("cls");

			base.Edit_Data(choice_edit);

			printf("\nDone\n\n");
			system("pause");
			continue;

		case 6:
			printf("Enter the name file: \n> ");
			if (!scanf("%s", file_name6))
				return 4;
			base.Copy_Base_into_File(file_name6);

			printf("\nDone\n\n");
			system("pause");
			continue;

		case 7:

			int number_of_employee;

			for (int i = 0; i < maxn; ++i)
				FIO_25years[i] = new char[31];

			printf("Average salary: %0.2f\n", Request_1(base.Get_Arr(), base.Get_Size(), 2024, number_of_employee, FIO_25years));

			for (int i = 0; i < number_of_employee; ++i)
			{
				printf("%s\n", FIO_25years[i]);
			}
			
			printf("\nDone\n\n");
			system("pause");
			continue;

		case 8:
			base.MergeSort(0, base.Get_Size() - 1);
			printf("\nDone\n\n");
			system("pause");
			continue;

		default:
			int choise_def;
			printf("Do you want to exit?\n> ");
			printf("1. No\n");
			printf("Any one. Yes\n");
			if(!scanf("%d", &choise_def))
				return 4;
			if (choise_def != 1)
				return 0;
			continue;
		}
	}

	return 0;
}