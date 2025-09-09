#include<iostream>
#include<string>
#include<limits>
using namespace std;
#define MAX_ORDER 50//limit the maximum order number


void showMenu()
{
	cout << "*******************************" << endl;
	cout << "*****Welcome to CodePizza!*****" << endl;
	cout << "*******************************" << endl;
	cout << "***** 1. Place an order *******" << endl;
	cout << "***** 2. View order queue *****" << endl;
	cout << "***** 3. Bake next order ******" << endl;
	cout << "***** 4. Check the total revenue" << endl;
	cout << "***** 0. Quit *****************" << endl;	
	cout << "*******************************" << endl;
	cout << "please input a number(1,2,3,or 0)" << endl;
	cout << "*******************************" << endl;

}

//one single pizza(categore)
struct Pizza
{
	string m_Size;
	string m_Crust;
	string m_Toppings;
	double m_SinglePrice;
};

//the different orders will contain one or more than one pizzas 
//struct Order
//{
//	int m_PizzaCount;
//	int m_SingleOrderPrice;
//};

//store many orders
struct OrderQueue
{
	int orderCount;//how many orders currently,  after each addition the orderCount will add 1;
	double totalRevenue;//the total revenue
	Pizza pizzaArray[MAX_ORDER];
};



void calculatePrice(OrderQueue* queue)
{
	if (queue->orderCount == 0)
	{
		cout << "the queue is empty!" << endl;
	}
	else
	{
		//the price for size
		double price1 = 0;
		if (queue->pizzaArray[queue->orderCount - 1].m_Size == "Small")
		{
			price1 = 8;
		}
		else if (queue->pizzaArray[queue->orderCount - 1].m_Size == "Medium")
		{
			price1 = 10;
		}
		else
		{
			price1 = 12;
		}

		//the price for crust
		double price2 = 0;
		if (queue->pizzaArray[queue->orderCount - 1].m_Crust == "Deep_Dish")
		{
			price2 = 2;
		}
		else
		{
			price2 = 0;
		}

		//the price for toppings
		int price3 = 1;
		for(char c : queue->pizzaArray[queue->orderCount - 1].m_Toppings)

		//易错：queue-》ordercount-1
		//数组访问：从0编号
		//数组循环写法：退化思路
		{
			if(c == ',')
			price3++;
		}
		/*char c 创建了一个字符变量，不是字符串
		：的作用为增强循环
		：后面的字符串是等待遍历的字符串
		c == ', '就是判断	
		*/

		double price = price1 + price2 + price3;
		double ultimatePrice = price * 1.1;
		queue->pizzaArray[queue->orderCount - 1].m_SinglePrice = ultimatePrice;
	}
}



//place order function
void placeOrder(OrderQueue* queue)
{
	
	while(1)
	{
		string size;
		cout << "size opt(please input Small, Medium, Large)" << endl;
		cin >> size;
		if(size=="Small"||size == "Medium"||size == "Large")
		{
			queue->pizzaArray[queue->orderCount].m_Size = size;
			break;
		}
		cout<<"void input ! "<<endl;
	}
	
	while(1)
	{
		string crust;
		cout << "crust opt(please input Thin, Regular, Deep_Dish)" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> crust;
		if(crust == "Thin"||crust == "Regular"||crust == "Deep_Dish")
		{
			queue->pizzaArray[queue->orderCount].m_Crust = crust;
			break;
		}
		cout<<"void input ! "<<endl;
	}
	
	cout << "toppings opt(please input list/array of strings or integers, pepperoni, cheese, pineapple, ech)" << endl;
	string toppings;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin,toppings);
	queue->pizzaArray[queue->orderCount].m_Toppings = toppings;
	
	queue->orderCount++;//先加一
	calculatePrice(queue);//再计算价格
	cout <<"the price is : "<< queue->pizzaArray[queue->orderCount-1].m_SinglePrice << endl;

	system("pause");
	system("cls");

}

//View order function
void printOrder(OrderQueue* queue)
{
	if (queue->orderCount == 0)
	{
		cout << "the order-queue is empty! " << endl;
	}
	else
	{
		for (int i=0;i<queue->orderCount;i++)
		{
			
			cout << "this is order :" << i+1 << endl;
			cout << "the size is :" << queue->pizzaArray[i].m_Size << endl;
			cout << "the crust is :" << queue->pizzaArray[i].m_Crust << endl;
			cout << "the toppings is :" << queue->pizzaArray[i].m_Toppings << endl;
			cout << "the price is : " << queue->pizzaArray[i].m_SinglePrice << endl;
			cout << "==============================" << endl;
			
		}
	}
	system("pause");
	system("cls");
}

//bake function
void bake(OrderQueue* queue)
{
	if (queue->orderCount == 0)
	{
		cout << "the queue is empty!" << endl;
	}
	else
	{
		//show the info of the first pizza in the queue
		cout << "the currently baking pizza is: " << endl;
		cout << "size : " << queue->pizzaArray[0].m_Size << endl;
		cout << "crust : " << queue->pizzaArray[0].m_Crust << endl;
		cout << "toppings : " << queue->pizzaArray[0].m_Toppings << endl;
		cout << "=======================" << endl;
		cout << "please enjoy your pizza!" << endl;
		
		//remove the first one in the queue
		//all the orders in the line will move forward
		for (int i=0;i<queue->orderCount-1;i++)
		{
			queue->pizzaArray[i] = queue->pizzaArray[i+1];
		}

		//after the circle, the orderCount will be minused one
		queue->orderCount --;
	}
	system("pause");
	system("cls");
}

double totalRevenue = 0;

//check the revenue
void checkRevenue(OrderQueue* queue)
{
	
	for (int i=0;i<queue->orderCount;i++)
	{
		totalRevenue += queue->pizzaArray[i].m_SinglePrice;
	}
	cout << "the total revenue is : " << totalRevenue << endl;
	system("pause");
	system("cls");
}

int main()
{
	OrderQueue queue;//creat an order book to store the orders
	queue.orderCount = 0;
	while (true)
	{
		showMenu();
		int opt;
		cin >> opt;
			switch (opt)
			{
			case 1:
				//placeOrder();
				placeOrder(&queue);
				break;
			case 2:
				//viewOrderQueue();
				calculatePrice(&queue);
				printOrder(&queue);
				break;
			case 3:
				//bakeNextOrder();
				bake(&queue);
				break;
			case 4:
				checkRevenue(&queue);
				break;
			case 0:
				cout << "Welcome next time! " << endl;
				system("pause");
				return 0;

			}
		
	}


	system("pause");
	return 0;
}