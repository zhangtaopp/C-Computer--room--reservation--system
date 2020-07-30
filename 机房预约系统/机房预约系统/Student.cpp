#include "Student.h"
Student::Student()
{
}



//有参构造 参数：学号、姓名、密码
Student::Student(int id, string name, string pwd) {
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//获取机房信息
	ifstream ifs;//读文件
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs>>c.m_ComId&&ifs>>c.m_MaxNum) {
		//将读取的信息放到容器中
		vCom.push_back(c);
	}
	ifs.close();
}

//菜单界面
void Student::operMenu() {
	cout << "欢迎：" << this->m_Name << "登录！" << endl;
	cout << endl;
	cout << endl << "请输入您的身份:" << endl;
	cout << "\t\t--------------------------------------\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|             1.申请预约             |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|             2.查看我的预约         |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|             3.查看所有预约         |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|             4.取消预约             |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|             0.注销登录             |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t--------------------------------------\n";
	cout << "请输入您的选择：";
}


//申请预约
void Student::applyOrder() {
	cout << "机房开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1.周一" << endl;
	cout << "2.周二" << endl;
	cout << "3.周三" << endl;
	cout << "4.周四" << endl;
	cout << "5.周五" << endl;
	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0;//机房编号

	while (true) {
		cin >> date;
		if (date >=1&& date <=5) {
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;

	while (true) {
		cin >> interval;
		if (interval>=1&&interval<=2) {
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	cout << "请选择机房：" << endl;
	for (int i = 0; i < vCom.size(); i++) {
		cout << vCom[i].m_ComId << "号机房容量：" << vCom[i].m_MaxNum << endl;
	}

	while (true) {
		cin >> room;
		if (room>=1&&room<= 3) {
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "预约成功！ 审核中......" << endl;

	ofstream ofs(ORDER_FILE,ios::app);//app追加的方式打开

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";//时间段
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;//1号表示审核中

	ofs.close();

	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder() {
	orderFile of;
	cout << of.m_Size << endl;
	
	if (of.m_Size==0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size;i++) {
		//string 利用.c_str()转const char*
		//利用atoi（const char*）转int	
		
		if (this->m_Id==atoi(of.m_orderDate[i]["stuId"].c_str())) {//找到和自身学号一样的记录找出来
			cout << "预约日期：周" << of.m_orderDate[i]["date"];
			cout << "时段" << (of.m_orderDate[i]["interval"] == "1" ? "上午" : "下午");
			cout << "机房：" << of.m_orderDate[i]["roomId"];
			string status = "状态：";//0 取消预约 1 审核中 2 已预约 -1 预约失效
			if (of.m_orderDate[i]["status"]=="1") {
				status += "审核中......";
			}
			else if (of.m_orderDate[i]["status"] == "2") {
				status += "预约成功！";
			}
			else if (of.m_orderDate[i]["status"] == "-1") {
				status += "审核未通过，预约失败！";
			}
			else {
				status += "预约已取消！";
			}
			cout << status << endl;			
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder() {
	orderFile of;//拿到分割好的所有预约记录
	if (of.m_Size==0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size;i++) {
		cout << i + 1 << "、 ";//显示标号
		cout << "预约日期：周" << of.m_orderDate[i]["date"] << " ";
		cout << "时段：" << (of.m_orderDate[i]["interval"] == "1" ? "上午" : "下午") << " ";
		cout << "学号：" << of.m_orderDate[i]["stuId"] << " ";
		cout << "姓名：" << of.m_orderDate[i]["stuName"] << " ";
		cout << "机房：" << of.m_orderDate[i]["roomId"] << " ";
		string status = "状态：";//0 取消预约 1 审核中 2 已预约 -1 预约失效
	
		if (of.m_orderDate[i]["status"] == "1") {
			status += "审核中......";
		}
		else if (of.m_orderDate[i]["status"] == "2") {
			status += "预约成功！";
		}
		else if (of.m_orderDate[i]["status"] == "-1") {
			status += "审核未通过，预约失败！";
		}
		else {
			status += "预约已取消！";
		}
		cout << status << endl;
		 
	}
	system("pause");
	system("cls");	
}

//取消预约
void Student::cancelOrder() {
	orderFile of;
	if (of.m_Size==0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;

	vector<int> v;//存放最大容器中的下标编号
	int index = 1;
	for (int i = 0; i < of.m_Size;i++) {
		if (this->m_Id == atoi(of.m_orderDate[i]["stuId"].c_str())) {//只能取消自己的
			if (of.m_orderDate[i]["status"]=="1"|| of.m_orderDate[i]["status"]=="2") {//审核中或预约成功的记录可以取消
				v.push_back(i);
				cout << index++ << "、 ";
				cout << "预约日期：周" << of.m_orderDate[i]["date"] << " ";
				cout << "时段：" << (of.m_orderDate[i]["interval"] == "1" ? "上午" : "下午") << " ";
				cout << "机房：" << of.m_orderDate[i]["roomId"] << " ";
				string status = "状态：";//0 取消预约 1 审核中 2 已预约 -1 预约失效

				if (of.m_orderDate[i]["status"] == "1") {
					status += "审核中......";
				}
				else if (of.m_orderDate[i]["status"] == "2") {
					status += "预约成功！";
				}
				cout << status << endl;
			}		
		}
	}
	cout << "请输入取消的记录，0表示返回" << endl;
	int select = 0;

	while (true) {
		cin >> select;
		if (select>=0&&select<=v.size()) {
			if (select == 0) {
				break;
			}
			else {
				//cout << "记录所在位置： " << v[select - 1] << endl;
				of.m_orderDate[v[select-1]]["status"] = "0";//注意输入的下标和v中索引的对应
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	system("pause");
	system("cls");
}