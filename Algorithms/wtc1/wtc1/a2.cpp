/* 
 * Author: ZCY
 * Design: WTC
 * Time: 2019/3/29 
 * 
 */

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <list>
using namespace std;

int sum; //三元表的数据行数

list<vector<string> > inputs; 	//vector使用方式和数组一样，可以用[]取值

list<string> group; //存储每个a分组中的a列对应值，list是链表，随机插入和删除较快，
list<string> value; //存储每个分组中的相应元素与b列对应的权值，此处不能是float，必须是string，vector中类型要相同

//通过b找出所有a的函数，返回两个动态数组结果，一个是a组的序列串，另一个是每一个a与相应b对应的值
void func() 
{

	list<vector<string> >::iterator itList = inputs.begin(); 	//itList是一个指向inputs的指针，*itList 表示list的一个数据（vector<string>)	
	list<vector<string> >::iterator iteratorTemp = itList;

	vector<string>::iterator itVector = (*itList).begin();
	string strTemp = itVector[1];
	int i = 0;
	while (itList != inputs.end())	//遍历一遍就结束
	{
		itVector = (*itList).begin();
		if (itVector[1] == strTemp)
		{
			// 第一个也被包括了
			group.push_back(itVector[0]); //将a插到group中的末尾
			value.push_back(itVector[2]); //将权值c插入value的顺序空值内，对应于group
										  // 如果想将值随机插到某个位置用group.insert()（自己百度去）
			iteratorTemp = itList;
			/*cout << (*itList)[0] << "  " << (*itList)[1] << "  " << (*itList)[2] << endl;*/

			++itList;	//itList指向inputs的下一行

			inputs.erase(iteratorTemp);	//inputs删掉itList指向的行，整体上移
		}
		else
		{
			++itList;	//itList指向inputs的下一行
		}
	}
}

float calculate_val(float a, float b) //跨平台接入python算法，计算value值
{
	return 1;
}

void rewrite_3(list<string>& a1, list<string>& a2, ofstream& file)//a1,a2都是动态数组 ，a1存a组的序列串，a2存每一个a与相应b对应的值
{
	
	list<string>::iterator x = a1.begin();		// x 指向 a1 的第 1 个 ,相当于 a1[0]
	list<string>::iterator xxxx = a1.end();
	xxxx--;										// xxxx 指向 a1 的最后一个元素 ,

	for (; x != xxxx; x++)						// x不指向最后一个元素
	{
		list<string>::iterator y = x;			// y 指向 x，xy指向同一个，
		y++; 									// y 指向 x 的下一个
		for (; y != a1.end(); y++)				// y包括了最后一个数
		{	
			// 将a2 的string 转为float
			float a2X = atof((*x).c_str());
			float a2Y = atof((*y).c_str());

			file << *x << ',' << *y << ',' << calculate_val(a2X, a2Y) << endl;
		}
	}
}

void readCSV()
{
	string  strFileName = "40101_17.csv";						//【0】文件名
	ifstream file;                                      //【1】声明一个文件输入输出流对象
	file.open(strFileName.c_str(), ios::in);            //【2】以读文件的方式打开文件
	if (!file.is_open())
	{
		cout << "【NOTICE】The read file is loaded unsuccessfully!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "【NOTICE】The read file is successfully!" << endl;
	}

	string  strTemp;
	vector<string> vRow;    // 存储 csv 中一行的内容，保存为 vRow[0],vRow[1],vRow[2]

	while (getline(file, strTemp))			// 从 file 中 读取一行数据，保存到strTemp中
	{

		vRow.clear();
		char*  tmpString;
		char* buf;
		tmpString = strtok_s((char*)strTemp.c_str(), ",", &buf);	// ";" 是csv中的分隔符，

																	// while 循环将 tmpString 保存到 vRow 中
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

void main()
{
	readCSV();

	ofstream file;
	file.open("data.csv", ios::out); // 打开文件  
	if (!file.is_open())
	{
		cout << "【NOTICE】The write file is loaded unsuccessfully!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "【NOTICE】The write file is successfully!" << endl;
	}

	//Step1:找：b列中某一元素所对应a列中的所有元素
	while (!inputs.empty())
	{
		group.clear(); //清空动态数组，重复使用
		value.clear();
		func();

		//Step2：重写三元表	
		rewrite_3(group, value, file);
	}
	


	cout << "Program is finish！" << endl;
	system("pause");
}