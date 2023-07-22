#include "Dictionary.h"
#include "Trie.h"

Trie ev, ee, ve;
void Dictionary::run()
{
	build();
	process();
}
void Dictionary::build()
{
	(void)_setmode(_fileno(stdin), _O_U16TEXT);
	(void)_setmode(_fileno(stdout), _O_U8TEXT);
	//ee.loadDataSet(EE);
	ve.loadDataSet(VE);
	//ev.loadDataSet(EV);
	//ee.deleteTrie(ee.root);
	//ev.deleteTrie(ev.root);
}

void Dictionary::process()
{
	while(true)
	{
		std::wcout << "1.Eng-Eng\n";
		std::wcout << "2.Eng-Vie\n";
		std::wcout << "3.Vie-Eng\n";
		std::wcout << "4.Exit\n";
		std::wcout << "Select data-set:";
		int data; std::wcin >> data;
		if (data == 4)
		{
			deleteTree();
			break;
		}
		bool back = 0;
		while (!back)
		{
			std::wcout << "1.Search for key word\n";
			std::wcout << "2.Search for definition\n";
			std::wcout << "3.Return\n";
			std::wcout << "Enter your choice:";
			int choice; std::wcin >> choice;
			switch (choice)
			{
			case 1:
			{
				std::wstring inputString;
				std::wcin.ignore();
				std::wcout << "Input:";
				getline(std::wcin, inputString);
				WordDef* find = search(data, inputString);
				if (!find)
					std::wcout << "Can not find this word in dictionary\n";
				else
				{
					std::wcout << "Word: " << find->keyWord << std::endl;
					for (std::wstring item : find->definition)
						std::wcout << item << std::endl;
					std::wcout << std::endl;
				}
				break;
			}
			/*case 2:
			{
				std::wstring inputString;
				getline(std::wcin, inputString);
				WordDef* find = searchDefinition(, inputString);
				if (!find)
					std::wcout << "Can not find this word in dictionary\n";
				else
				{
					std::wcout << "Word: " << find->keyWord << std::endl;
					for (std::wstring item : find->definition)
						std::wcout << item << std::endl;
				}
				break;
			}*/
			case 3:
			{
				back = 1;
				break;
			}
			}
		}
	}
}

