// 2019/4/13 13:00����
// δ����֦�Ľ��

#include <iostream>
#include <fstream>
#include <sstream> 
#include <string> 
#include <vector>
#include <list>
#include <sstream>
#include <map>
using namespace std;

int sum; //��Ԫ�����������

list<vector<string> > inputsss; 			// �����洢�� CSV �ļ��ж�ȡ������
map<string, float> outputs;		// �洢������
list<string> group; //�洢ÿ��a�����е�a�ж�Ӧֵ��list��������������ɾ���Ͽ죬
list<string> value; //�洢ÿ�������е���ӦԪ����b�ж�Ӧ��Ȩֵ���˴�������float��������string��vector������Ҫ��ͬ




void func() //ͨ��b�ҳ�����a�ĺ���������������̬��������һ����a������д�����һ����ÿһ��a����Ӧb��Ӧ��ֵ
{

	list<vector<string> >::iterator itList = inputsss.begin(); 	//itList��һ��ָ��inputs��ָ�룬*itList ��ʾlist��һ�����ݣ�vector<string>)	
	list<vector<string> >::iterator iteratorTemp = itList;

	vector<string>::iterator itVector = (*itList).begin();
	string strTemp = itVector[1];
	int i = 0;
	while (itList != inputsss.end())	//����һ��ͽ���
	{
		itVector = (*itList).begin();
		if (itVector[1] == strTemp)
		{
			// ��һ��Ҳ��������
			group.push_back(itVector[0]); //��a�嵽group�е�ĩβ
			value.push_back(itVector[2]); //��Ȩֵc����value��˳���ֵ�ڣ���Ӧ��group
										  // ����뽫ֵ����嵽ĳ��λ����group.insert()���Լ��ٶ�ȥ��
			iteratorTemp = itList;
			/*cout << (*itList)[0] << "  " << (*itList)[1] << "  " << (*itList)[2] << endl;*/

			++itList;	//itListָ��inputs����һ��

			inputsss.erase(iteratorTemp);	//inputsɾ��itListָ����У���������
		}
		else
		{
			++itList;	//itListָ��inputs����һ��
			break;
		}
	}
}

float calculate_val(float a, float b) //��ƽ̨����python�㷨������valueֵ
{
	return 1;
}

//void rewrite_3(list<string>& a1, list<string>& a2, ofstream& file)//a1,a2���Ƕ�̬���� ��a1��a������д���a2��ÿһ��a����Ӧb��Ӧ��ֵ
void rewrite_3(list<string>& a1, list<string>& a2)//a1,a2���Ƕ�̬���� ��a1��a������д���a2��ÿһ��a����Ӧb��Ӧ��ֵ
{
	list<string>::iterator x = a1.begin();		// x ָ�� a1 �ĵ� 1 �� ,�൱�� a1[0]
	list<string>::iterator xxxx = a1.end();
	xxxx--;										// xxxx ָ�� a1 �����һ��Ԫ�� ,

	map<string, float>::iterator itmap;
	string res;
	for (; x != xxxx; x++)	// x��ָ�����һ��Ԫ��
	{
		list<string>::iterator y = x;		// y ָ�� x��xyָ��ͬһ����
		y++; 	// y ָ�� x ����һ��
		for (; y != a1.end(); y++)	// y���������һ����
		{
			// ��a2 ��string תΪfloat
			float a2X = atof((*x).c_str());
			float a2Y = atof((*y).c_str());

			//file << *x << ',' << *y << ',' << calculate_val(a2X, a2Y) << endl;

			res = *x + "@" + *y;
			itmap = outputs.find(res);
			if (itmap != outputs.end())
			{
				itmap->second++;
			}
			else
			{
				outputs.insert(pair<string, float>(res, calculate_val(a2X, a2Y)));
			}
		}
	}
}

bool readCSV(string filename, list<vector<string> >& input)
{
	string  strFileName = filename;						//��0���ļ���
	ifstream file;                                      //��1������һ���ļ��������������
	file.open(strFileName.c_str(), ios::in);            //��2���Զ��ļ��ķ�ʽ���ļ�
	if (!file.is_open())
	{
		cout << endl;
		cout << "��NOTICE��The read file is loaded unsuccessfully!" << endl;
		cout << endl;
		//system("pause");
		return false;
	}
	else
	{
		cout << "��NOTICE��The read file is successfully!" << endl;
	}

	string  strTemp;
	vector<string> vRow;    // �洢 csv ��һ�е����ݣ�����Ϊ vRow[0],vRow[1],vRow[2]

	while (getline(file, strTemp))			// �� file �� ��ȡһ�����ݣ����浽strTemp��
	{

		vRow.clear();
		char*  tmpString;
		char* buf;
		tmpString = strtok_s((char*)strTemp.c_str(), ",", &buf);	// ";" ��csv�еķָ�����

																	// while ѭ���� tmpString ���浽 vRow ��
		while (tmpString)
		{
			if (!strcmp(tmpString, ""))
			{
				break;
			}
			else
			{
				vRow.push_back(tmpString);
			}
			tmpString = strtok_s(NULL, ",", &buf);
		}
		input.push_back(vRow);
	}

	file.close();
	return true;
}




void writeCSV()
{
	//д�ļ�
	ofstream file;
	file.open("1718all_re.csv", ios::out);

	if (!file.is_open())
	{
		cout << "��NOTICE��The write file is loaded unsuccessfully!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "��NOTICE��The write file is successfully!" << endl;
	}

	map<string, float>::iterator it = outputs.begin();
	for (; it != outputs.end(); ++it)
	{
		int startPos = 0;
		string ss = it->first;
		string s1, s2 = "";
		startPos = ss.find_first_of('@');
		if (startPos != string::npos)
		{
			s1 = ss.substr(0, startPos);
			s2 = ss.substr(startPos + 1);
		}
		else
		{
			s1, s2 = ss;		//�����ʾ������		
		}
		file << s1 << ',' << s2 << ',' << it->second << endl;
	}

	file.close();
}


void main()
{
	cout << "please select the data type:	" << endl;
	cout << "	1->origin data			" << endl;
	cout << "	2->intermediate data	" << endl;
	cout << "------------------------------------------" << endl;
	cout << "input: 1" << endl;
	int dataType = 1;
	//cin >> dataType;

	while (true)
	{
		if (dataType == 1)
		{
			if (readCSV("1718all.csv", inputsss))
			{
				break;
			}
		}

		cout << endl;
		cout << "			#################################			" << endl;
		cout << "			#			INPUT ERROR			#			" << endl;
		cout << "			#		please input 1 or 2		#			" << endl;
		cout << "			#################################			" << endl;
		cout << endl;
	}


	//ofstream file;
	//file.open("data.csv", ios::out); // ���ļ�  
	//if (!file.is_open())
	//{
	//	cout << "��NOTICE��The write file is loaded unsuccessfully!" << endl;
	//	system("pause");
	//	return;
	//}
	//else
	//{
	//	cout << "��NOTICE��The write file is successfully!" << endl;
	//}

	//Step1:�ң�b����ĳһԪ������Ӧa���е�����Ԫ��
	while (!inputsss.empty())
	{
		group.clear(); //��ն�̬���飬�ظ�ʹ��
		value.clear();
		func();

		//Step2����д��Ԫ��	
		//rewrite_3(group, value, file);
		rewrite_3(group, value);
	}
	
	writeCSV();
	cout << "Program is finish��" << endl;
	system("pause");
}