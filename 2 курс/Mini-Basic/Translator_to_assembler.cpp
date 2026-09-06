#include "Translator_to_assembler.h"

Translator_to_assembler::Translator_to_assembler(string file_name)
{
	start_SA(file_name);
}

void Translator_to_assembler::Generate_assembler_code(string file_name)
{
	ofstream file;
	file.open(file_name);
	if (!file.is_open())
	{
		cerr << "Error opening file: " << file_name << endl;
		return;
	}
	file.clear();
	

	file << "include\\masm32\\include\\masm32rt.inc\n\n.386" << endl;

	file << "\t.data?" << endl << endl;
	for (int i = 0; i <= 286; i++)
	{
		int j = i;
		if (j <= 26 && table_operands[j] == 1)
			file << "\t" << (char)((j % 27) + 'A' - 1) << " dd ?" << endl;
		else if (j <= 286 && table_operands[j] == 1)
		{
			file << "\t";
			if (j % 26 == 0)
			{
				file << "Z";
				j /= 26;
				file << j % 26 - 2;
			}
			else
			{
				file << (char)((j % 26) + 'A' - 1);

				j /= 26;
				file << j % 26 - 1;
			}
			file << " dd ?" << endl;
		}
	}

	file << endl << "\t.data" << endl << endl;

	for (int i = ptr_to_free; i < NTtemp; i++)
	{
		file << "\ttemp" << i << " dd " << table_operands[i] << endl;
	}

	for (int i = 700; i < NTX; i++)
	{
		file << "\ttemp" << i << " dd " << table_operands[i] << endl;
	}

	file << endl << "\t.code" << endl << "\tstart:" << endl;
	file << "\t call label_" << table_number_string[table_atoms[0].attribute1] << endl;
	if (table_operands[44] == 1)
		file << "\t print str$(R0),10,13" << endl;
	if (table_operands[70] == 1)
		file << "\t print str$(R1),10,13" << endl;
	file << "\t exit" << endl;

	int last_lable = -1;
	int flag_label = 0;
	for (auto& i : table_atoms)
	{

		switch (i.type)
		{
		case 0:
			if (last_lable != -1)
			{
				file << "\tlabel_" << table_number_string[last_lable] << " endp" << endl;
			}
			file << "end start" << endl;
			break;

		case 1:
			if (last_lable != -1)
			{
				if (table_number_string[i.attribute1] == -1)
				{
					file << "\t\t" << "call label_" << i.attribute1 << endl;
				}				
				else
				{
					file << "\t\t" << "call label_" << table_number_string[i.attribute1] << endl;
				}

				file << "\t\tret" << endl;

				if (flag_label)
				{
					file << "\tlabel_" << last_lable << " endp" << endl;
				}
				else
				{
					file << "\tlabel_" << table_number_string[last_lable] << " endp" << endl;
				}
			}
			file << "\tlabel_" << table_number_string[i.attribute1] << " proc " << endl;
			last_lable = i.attribute1;
			flag_label = 0;
			break;

		case 2:
			file << "\t\tmov eax, " << N_to_S(i.attribute2) << endl;
			file << "\t\tmov " << N_to_S(i.attribute1) << ", eax" << endl;
			break;

		case 3:
			if (table_number_string[i.attribute1] == -1)
				file << "\t\tcall label_" << i.attribute1 << endl;
			else
				file << "\t\tcall label_" << table_number_string[i.attribute1] << endl;
			break;

		case 4:
			if (table_number_string[i.attribute1] == -1)
				file << "\t\tcall label_" << i.attribute1 << endl;
			else
				file << "\t\tcall label_" << table_number_string[i.attribute1] << endl;
			break;

		case 5:
			file << "\t\tret" << endl;
			break;

		case 6:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tcmp eax, " << N_to_S(i.attribute2) << endl;
			if (table_number_string[i.attribute4] == -1)
			{
				switch (i.attribute3)
				{
				case 1:
					file << "\t\tJE label_" << i.attribute4 << endl;
					break;
				case 2:
					file << "\t\tJS label_" << i.attribute4 << endl;
					break;
				case 3:
					file << "\t\tJNS label_" << i.attribute4 << endl;
					break;
				case 4:
					file << "\t\tJE label_" << i.attribute4 << endl;
					file << "\t\tJS label_" << i.attribute4 << endl;
					break;
				case 5:
					file << "\t\tJE label_" << i.attribute4 << endl;
					file << "\t\tJNS label_" << i.attribute4 << endl;
					break;
				case 6:
					file << "\t\tJNE label_" << i.attribute4 << endl;
					break;
				}
			}
			else
			{
				switch (i.attribute3)
				{
				case 1:
					file << "\t\tJE label_" << table_number_string[i.attribute4] << endl;
					break;
				case 2:
					file << "\t\tJS label_" << table_number_string[i.attribute4] << endl;
					break;
				case 3:
					file << "\t\tJNS label_" << table_number_string[i.attribute4] << endl;
					break;
				case 4:
					file << "\t\tJE label_" << table_number_string[i.attribute4] << endl;
					file << "\t\tJS label_" << table_number_string[i.attribute4] << endl;
					break;
				case 5:
					file << "\t\tJE label_" << table_number_string[i.attribute4] << endl;
					file << "\t\tJNS label_" << table_number_string[i.attribute4] << endl;
					break;
				case 6:
					file << "\t\tJNE label_" << table_number_string[i.attribute4] << endl;
					break;
				}
				break;
			}
			break;

		case 7:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tmov " << N_to_S(i.attribute2) << ", eax" << endl;
			break;

		case 8:
			if (last_lable != -1)
			{
				if (table_number_string[i.attribute1] == -1)
				{
					file << "\t\t" << "call label_" << i.attribute1 << endl;
				}
				else
				{
					file << "\t\t" << "call label_" << table_number_string[i.attribute1] << endl;
				}

				file << "\t\tret" << endl;

				if (flag_label)
				{
					file << "\tlabel_" << last_lable << " endp" << endl;
				}
				else
				{
					file << "\tlabel_" << table_number_string[last_lable] << " endp" << endl;
				}
			}
			file << "\tlabel_" << i.attribute1 << " proc " << endl;
			last_lable = i.attribute1;
			flag_label = 1;
			break;


		case 9:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tcmp eax, " << N_to_S(i.attribute2) << endl;
			if (table_number_string[i.attribute4] == -1)
			{
				file << "\t\tJE label_" << i.attribute4 << endl;
				file << "\t\tJNS label_" << i.attribute4 << endl;
			}
			else
			{
				file << "\t\tJE label_" << table_number_string[i.attribute4] << endl;
				file << "\t\tJNS label_" << table_number_string[i.attribute4] << endl;
			}
			break;

		case 10:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tiadd eax, " << N_to_S(i.attribute2) << endl;
			file << "\t\tmov " << N_to_S(i.attribute1) << ", eax" << endl;
			break;

		case 11:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tiadd eax, " << N_to_S(i.attribute2) << endl;
			file << "\t\tmov " << N_to_S(i.attribute3) << ", eax" << endl;
			break;

		case 12:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tisub eax, " << N_to_S(i.attribute2) << endl;
			file << "\t\tmov " << N_to_S(i.attribute3) << ", eax" << endl;
			break;

		case 13:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tmov ebx, " << N_to_S(i.attribute2) << endl;
			file << "\t\timul ebx" << endl;
			file << "\t\tmov " << N_to_S(i.attribute3) << ", eax" << endl;
			break;

		case 14:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tmov ebx, " << N_to_S(i.attribute2) << endl;
			file << "\t\tidiv ebx" << endl;
			file << "\t\tmov " << N_to_S(i.attribute3) << ", eax" << endl;
			break;

		case 15:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			for (int j = 1; j < i.attribute2; j++)
				file << "\t\timul eax" << endl;
			file << "\t\tmov " << N_to_S(i.attribute3) << ", eax" << endl;
			break;

		case 16:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tinc eax" << endl;
			file << "\t\tmov " << N_to_S(i.attribute2) << ", eax" << endl;
			break;

		case 17:
			file << "\t\tmov eax, " << N_to_S(i.attribute1) << endl;
			file << "\t\tdec eax" << endl;
			file << "\t\tmov " << N_to_S(i.attribute2) << ", eax" << endl;
			break;
		}

		
	}

	file.close();
}

string Translator_to_assembler::N_to_S(int i) const
{
	string res;
	if (i <= 'Z' - 'A' + 1)
	{
		res.push_back((char)(i + 'A' - 1));
	}
	else if (i <= 286)
	{
		if (i % 26 == 0)
		{
			res.push_back('Z');
			res.push_back((char)(i / 27 + '0' - 1));
		}
		else
		{
			res.push_back((char)(i % 26 + 'A' - 1));
			res.push_back((char)(i / 26 + '0' - 1));
		}
	}
	else if (i >= ptr_to_free && i <= NTtemp)
	{
		res = "temp" + to_string((int)i);
	}
	else if (i >= 700 && i < NTX)
	{
		res = "temp" + to_string((int)i);
	}
	else
	{
		res = to_string((int)table_operands[i]);
	}

	return res;
}
