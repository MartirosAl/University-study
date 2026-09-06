#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class bell_sort
{
public:
	vector<int> array;

	vector<int> sorting(vector<int>& a_)
	{
		int temp_num;
		vector<int>::iterator maximum_small_iterator = a_.begin();
		vector<int>::iterator maximum_big_iterator = a_.begin();
		vector<int>::iterator iterator_on_border = a_.end() - 1;
		vector<int>::iterator temp_iterator;
		int counter = 0;
		if (a_.size() % 2)
		{	
			for (int j = 0; j < a_.size(); j++)
			{
				if (a_[j] > *maximum_big_iterator)
				{
					maximum_big_iterator = a_.begin() + j;
				}
			}

			temp_num = *(a_.end()-1);
			*(a_.end()-1) = *maximum_big_iterator;
			*maximum_big_iterator = temp_num;
			iterator_on_border = a_.end() - 2;
			counter++;


			for (int i = 0; i < (a_.size())/2; i++)
			{
				maximum_big_iterator = a_.begin();
				maximum_small_iterator = a_.begin();

				//Поиск максимумов
				for (int j = 1; j < (a_.size()-counter); j++)
				{
					if (a_[j] > *maximum_small_iterator)
					{
						if (a_[j] > *maximum_big_iterator)
						{	
							maximum_small_iterator = maximum_big_iterator;
							maximum_big_iterator = a_.begin() + j;
						}
						else
						{
							maximum_small_iterator = a_.begin() + j;
						}
					}
				}

				//Итераторы ломаются когда стираешь...
				//Вставка в нужные места
				temp_num = *maximum_big_iterator;
				*maximum_big_iterator = *(a_.end()-counter-1);
				*(a_.end() - counter - 1) = temp_num;
				

				temp_num = *maximum_small_iterator;
				a_.erase(maximum_small_iterator);
				a_.push_back(temp_num);

				counter += 2;

			}
		}
		else
		{
			for (int i = 0; i < (a_.size()) / 2; i++)
			{
				maximum_big_iterator = a_.begin();
				maximum_small_iterator = a_.begin();

				//Поиск максимумов
				for (int j = 1; j < (a_.size() - counter); j++)
				{
					if (a_[j] > *maximum_small_iterator)
					{
						if (a_[j] > *maximum_big_iterator)
						{
							maximum_small_iterator = maximum_big_iterator;
							maximum_big_iterator = a_.begin() + j;
						}
						else
						{
							maximum_small_iterator = a_.begin() + j;
						}
					}
				}

				//Итераторы ломаются когда стираешь...
				//Вставка в нужные места
				temp_num = *maximum_big_iterator;
				*maximum_big_iterator = *(a_.end() - counter - 1);
				*(a_.end() - counter - 1) = temp_num;


				temp_num = *maximum_small_iterator;
				a_.erase(maximum_small_iterator);
				a_.push_back(temp_num);

				counter += 2;

			}
		}
		array = a_;
		return a_;
	}
	
	friend ostream& operator<<(ostream& stream, const bell_sort& object_)
	{
		if (object_.array.size() % 2)
		{
			for (int j = 0; j < (object_.array.size()/ 2); j++)
				stream << " ";
			stream << object_.array[object_.array.size() / 2] << endl;

			for (int i = 1; i < (object_.array.size() + 1) / 2; i++)
			{
				for (int j = 1; j < object_.array.size() - (i + object_.array.size() / 2); j++)
					stream << " ";
				stream << object_.array[object_.array.size() / 2 - i];
				for (int j = 1; j < (2 * i); j++)
					stream << " ";
				stream << object_.array[object_.array.size() / 2 + i] << endl;
			}
		}
		else
		{
			for (int i = 0; i < object_.array.size() / 2; i++)
			{
				for (int j = 1; j < object_.array.size() - (i + object_.array.size() / 2); j++)
					stream << " ";
				stream << object_.array[object_.array.size() / 2 - i - 1] << " ";
				for (int j = 1; j < (2 * i)+1; j++)
					stream << " ";
				stream << object_.array[object_.array.size() / 2 + i] << endl;
			}
		}

		return stream;
	}
};


int main()
{
	vector<int> a = { 0, 3, 5, 6, 1 };
	vector<int> b = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 };
	bell_sort bell_sort;
	bell_sort.sorting(b);
	
	//for (int i = 0; i < a.size(); i++)
	//	cout << a[i] << " " << endl;

	//for (int i = 0; i < b.size(); i++)
	//	cout << b[i] << " ";
	//cout << endl << endl;

	cout << bell_sort;
	return 0;
}