
// 2019/3/29 9:20����

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

list<vector<string> > inputs; 	//vectorʹ�÷�ʽ������һ����������[]ȡֵ
map<string, float> rewrite;		//�洢���ս��
list<string> group; //�洢ÿ��a�����е�a�ж�Ӧֵ��list��������������ɾ���Ͽ죬
list<string> value; //�洢ÿ�������е���ӦԪ����b�ж�Ӧ��Ȩֵ���˴�������float��������string��vector������Ҫ��ͬ

void func() //ͨ��b�ҳ�����a�ĺ���������������̬��������һ����a������д�����һ����ÿһ��a����Ӧb��Ӧ��ֵ
{

	list<vector<string> >::iterator itList = inputs.begin(); 	//itList��һ��ָ��inputs��ָ�룬*itList ��ʾlist��һ�����ݣ�vector<string>)	
	list<vector<string> >::iterator iteratorTemp = itList;

	vector<string>::iterator itVector = (*itList).begin();
	string strTemp = itVector[1];
	int i = 0;
	while (itList != inputs.end())	//����һ��ͽ���
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

			inputs.erase(iteratorTemp);	//inputsɾ��itListָ����У���������
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
			itmap = rewrite.find(res);
			if (itmap != rewrite.end())
			{
				itmap->second++;
			}
			else
			{
				rewrite.insert(pair<string, float>(res, calculate_val(a2X, a2Y)));
			}
		}
	}
}

void readCSV()
{
	string  strFileName = "D:\\�û�Ŀ¼\\�ҵ��ĵ�\\Tencent Files\\136708924\\FileRecv\\bad_transaction_distinct_56724.csv";			//��0���ļ���
	ifstream file;                                      //��1������һ���ļ��������������
	file.open(strFileName.c_str(), ios::in);            //��2���Զ��ļ��ķ�ʽ���ļ�
	if (!file.is_open())
	{
		cout << "��NOTICE��The read file is loaded unsuccessfully!" << endl;
		system("pause");
		return;
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
		inputs.push_back(vRow);
	}

	file.close();
}


void writeCSV()
{
	//д�ļ�
	ofstream file;
	file.open("D:\\�û�Ŀ¼\\�ҵ��ĵ�\\Tencent Files\\136708924\\FileRecv\\bad_man_map_out.csv", ios::out);

	if (!file.is_open())
	{
		cout << "��NOTICE��The read file is loaded unsuccessfully!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "��NOTICE��The read file is successfully!" << endl;
	}

	map<string, float>::iterator it = rewrite.begin();
	for (; it != rewrite.end(); ++it)
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

	/////map���Դ���
	//map<string, int> mymap;
	//map<string, int>::key_compare mycomp = mymap.key_comp();
	//mymap["a1"] = 2;
	//mymap["a2"] = 5;
	//mymap["a3"] = 10;
	//string key = mymap.rbegin()->first;
	//map<string, int>::iterator it = mymap.begin();
	//do
	//{
	//	it->second++;
	//	cout << it->first << " " << it->second << endl;
	//} while (mycomp((*it++).first, key));


	readCSV();

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
	while (!inputs.empty())
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