
#include <iostream>
#include <vector>


using namespace std;

struct Node
{
	int index;
	Node* next;
};


class counting_rhyme_ver1
{
public:

	Node* deleter_list;
	Node* list_names;
	int N;
	int k;
	int index_last_one;

	template<typename T>
	counting_rhyme_ver1(vector<T> arr_, int k_)
	{
		list_names = get_сircular_list(arr_);
		Node* list_names_copy = get_сircular_list(arr_);

		cout << "-> ";
		print_list(list_names_copy);

		N = arr_.size();
		k = k_;
		int del_count = 0;

		for (int i = 1; i < N; i++)
		{
			int o = k;
			for (int j = 1; j < o; j++)
			{
				list_names_copy = list_names_copy->next;
			}

			list_names_copy = pop_from_сircular_list(list_names_copy, del_count);
			cout << "list: ";
			print_list(list_names_copy);
			cout << "del: ";
			print_list(deleter_list);

		}

		index_last_one = list_names_copy->index;
	}

	template<typename T>
	Node* get_сircular_list(vector<T> arr_)
	{
		Node* root = new Node;
		root->index = 1;
		Node* current = root;

		for (int i = 2; i <= arr_.size(); i++)
		{
			current->next = new Node;
			current = current->next;
			current->index = i;
		}
		current->next = root;

		return root;
	}


	Node* pop_from_сircular_list(Node* a_, int& del_count_)
	{

		if (!deleter_list)
		{
			deleter_list = new Node;
			deleter_list->index = a_->index;
			deleter_list->next = NULL;
		}
		else
		{
			Node* dc = deleter_list;
			while (dc->next != NULL)
			{
				dc = dc->next;
			}

			dc->next = new Node;
			dc->next->index = a_->index;
			dc->next->next = NULL;
		}

		Node* prev = a_;

		while (prev->next != a_)
		{
			prev = prev->next;
		}

		prev->next = a_->next;


		delete a_;

		del_count_++;

		return prev->next;
	}

	void print_list(Node* a_)
	{
		if (a_ == NULL)
			return;

		Node* start = a_;
		Node* cur = a_;

		while (cur->next != NULL && cur->next != start)
		{
			cout << cur->index << " ";
			cur = cur->next;
		}

		cout << cur->index << " ";
		cout << endl;
	}
	

};

class counting_rhyme_ver2
{
public:
	vector<int> deliter_list;
	vector<int> list_names;
	int N;
	int k;
	int index_last_one;

	template<typename T>
	counting_rhyme_ver2(vector<T> arr_, int k_)
	{
		
		N = arr_.size();
		k = k_;
		for (int i = 1; i <= N; i++)
		{
			list_names.push_back(i);
		}

		vector<int> list_names_copy = list_names;
		cout << "-> ";
		print_list(list_names_copy);
		
		int i = 0;

		while (list_names_copy.size() > 1)
		{
			if (i + k >= list_names_copy.size())
			{
				i = abs((int)(list_names_copy.size() - k));
			}
			else
				i += (k - 1);

			deliter_list.push_back(list_names_copy[i]);
			list_names_copy.erase(list_names_copy.begin() + i);
			cout << "list: ";
			print_list(list_names_copy);
			cout << "del: ";
			print_list(deliter_list);
		}

		index_last_one = list_names_copy[0];
	}

	template<typename T>
	void print_list(vector<T> a_)
	{
		for (int i = 0; i < a_.size(); i++)
			cout << a_[i] << " ";
		cout << endl;
	}

};

int main()
{
	vector<int> arr = { 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

	int k = 2;

	counting_rhyme_ver2 result(arr, k);

	cout << endl << "Answer: " << result.index_last_one << endl;

	return 0;
}
