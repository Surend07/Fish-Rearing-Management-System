#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <ctime>
using namespace std;                                          

#include <mysql/jdbc.h>
using namespace sql;

Connection* connector();

void viewfish();

std::string buydate();

void viewcustomer(std::string Customer_ID);

void viewadmin(std::string Admin_ID);

int main()
{
mainsystemout:
	Connection* connection = connector();
	std::string mainsystem, application, details, apps, decision, option, choice, enter, activity;

	std::cout << "\t\t\t\t\t\t##########################################################\n";
	std::cout << "\t\t\t\t\t\t##                                                      ##\n";
	std::cout << "\t\t\t\t\t\t##                                                      ##\n";
	std::cout << "\t\t\t\t\t\t##  *** WELCOME TO FISH REARING MANAGEMENT SYSTEM ***   ##\n";
	std::cout << "\t\t\t\t\t\t##                                                      ##\n";
	std::cout << "\t\t\t\t\t\t##     PLEASE CHOOSE ONE OF THE OPTIONS !               ##\n";
	std::cout << "\t\t\t\t\t\t##                                                      ##\n";
	std::cout << "\t\t\t\t\t\t##     A. ADMIN                                         ##\n";
	std::cout << "\t\t\t\t\t\t##     B. CUSTOMER LOGIN                                ##\n";
	std::cout << "\t\t\t\t\t\t##     C. NEW CUSTOMER REGISTRATION                     ##\n";
	std::cout << "\t\t\t\t\t\t##                                                      ##\n";
	std::cout << "\t\t\t\t\t\t##########################################################\n";
	std::cout << "\n\t\t\t\t\t\tOPTION : ";
	std::cin >> mainsystem;
	std::system("cls");

	if (mainsystem == "A")
	{
	loginout1:
		std::string Admin_ID, Password;
		std::cout << "\nADMIN_ID: ";
		std::cin >> Admin_ID;

		std::cout << "PASSWORD: ";

		int ch, chr;

		do
		{
			ch = _getch();

			if (ch == 13 || ch == ' ')
			{
				break;
			}
			if ((ch == 8 || ch == 127) && !Password.empty())
			{
				std::cout << "\b \b";
				Password.erase(Password.size() - 1);
				chr--;
			}
			else
			{
				Password += ch;
				std::cout << "*";
				chr++;
			}
		} while (ch != 13 || ch != ' ');

		PreparedStatement* ps = connection->prepareStatement("SELECT * FROM Admin WHERE Admin_ID = ? AND Password = ?");

		ps->setString(1, Admin_ID);
		ps->setString(2, Password);

		ResultSet* rs = ps->executeQuery();

		if (rs->next())
		{
			std::cout << "\n\n** WELCOME TO THE PROGRAMME " << rs->getString("Name") << ". HAVE A NICE DAY **\n" << endl;

		}
		else
		{
			std::cout << "\n******************************************************************\n";
			std::cout << "**                                                              **\n";
			std::cout << "**       INVALID ADMIN_ID OR PASSWORD!!!,                       **\n";
			std::cout << "**       PLEASE RE-ENTER THE ADMIN_ID AND PASSWORD              **\n";
			std::cout << "**                                                              **\n";
			std::cout << "******************************************************************\n";
			goto loginout1;
		}

		rs->close();
		ps->close();
		connection->close();

	applicationout:
		std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
		std::cout << "@@                                     @@\n";
		std::cout << "@@         ADMIN APPLICATIONS:         @@\n";
		std::cout << "@@                                     @@\n";
		std::cout << "@@    1) FISH DETAILS                  @@\n";
		std::cout << "@@    2) VIEW TOTAL SALES              @@\n";
		std::cout << "@@    3) VIEW CUSTOMER DETAILS         @@\n";
		std::cout << "@@    4) NEW ADMIN REGISTRATION        @@\n";
		std::cout << "@@    5) UPDATE ADMIN DETAILS          @@\n";
		std::cout << "@@    6) DELETE ADMIN                  @@\n";
		std::cout << "@@    7) EXIT                          @@\n";
		std::cout << "@@                                     @@\n";
		std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
		std::cout << "\nAPPLICATION: ";
		std::cin >> application;

		if (application == "1")
		{
		detailout:
			std::cout << "\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
			std::cout << "&&                               &&\n";
			std::cout << "&&        FISH DETAILS:          &&\n";
			std::cout << "&&                               &&\n";
			std::cout << "&&        A. VIEW                &&\n";
			std::cout << "&&        B. INSERT              &&\n";
			std::cout << "&&        C. UPDATE              &&\n";
			std::cout << "&&        D. DELETE              &&\n";
			std::cout << "&&        E. RETURN              &&\n";
			std::cout << "&&                               &&\n";
			std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
			std::cout << "\nDETAILS: ";
			std::cin >> details;

			if (details == "A")
			{
				connection = connector();
				viewfish();
				connection->close();
				goto detailout;
			}
			else if (details == "B")
			{
				std::string Fish_ID, Name, Lifespan;
				double Price;

			    connection = connector();
				viewfish();

			fishinsertout:
				std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%     EXAMPLE TO CREATE Fish_ID : F0001      %%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "\nFISH_ID: ";
				std::cin >> Fish_ID;

				if (Fish_ID.size() != 5)
				{
					std::cout << "\n******************************************************************\n";
					std::cout << "**                                                              **\n";
					std::cout << "**       INVALID FISH_ID !!!,                                   **\n";
					std::cout << "**       PLEASE TRY AGAIN BY FOLLOWING THE EXAMPLE BELOW        **\n";
					std::cout << "**                                                              **\n";
					std::cout << "******************************************************************\n";
					goto fishinsertout;
				}

				std::cout << "NAME_OF_FISH: ";
				std::cin >> Name;

			priceout:
				std::cout << "PRICE_PER_KILOGRAM_OF_FISH: ";
				while (!(std::cin >> Price))
				{
					std::cout << "\n## PLEASE ENTER NUMBERS ONLY. TRY AGAIN!!! ##" << endl;
					std::cin.clear();
					std::cin.ignore(123, '\n');
					goto priceout;
				}

				std::cout << "LIFESPAN_OF_FISH: ";
				std::cin.ignore();
				getline(std::cin, Lifespan);

				ps = connection->prepareStatement("INSERT INTO Fish(Fish_ID, Name, Price, Lifespan) VALUES (?,?,?,?)");

				ps->setString(1, Fish_ID);
				ps->setString(2, Name);
				ps->setDouble(3, Price);
				ps->setString(4, Lifespan);

				ps->executeQuery();

				ps->close();

				viewfish();
				connection->close();
				goto detailout;
			}
			else if (details == "C")
			{
				std::string Fish_ID, Name, Lifespan;
				double Price;

				connection = connector();
				viewfish();

			fishupdateout:
				std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%     EXAMPLE TO ENTER Fish_ID : F0001       %%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "\nFISH_ID: ";
				std::cin >> Fish_ID;


				if (Fish_ID.size() != 5)
				{
					std::cout << "\n******************************************************************\n";
					std::cout << "**                                                              **\n";
					std::cout << "**       INVALID FISH_ID !!!,                                   **\n";
					std::cout << "**       PLEASE TRY AGAIN BY FOLLOWING THE EXAMPLE BELOW        **\n";
					std::cout << "**                                                              **\n";
					std::cout << "******************************************************************\n";
					goto fishupdateout;
				}

				std::cout << "\n++++++++++++++++++++++++++++++++++\n";
				std::cout << "++                              ++\n";
				std::cout << "++   NEW PRICE OF THE FISH:     ++\n";
				std::cout << "++                              ++\n";
				std::cout << "++++++++++++++++++++++++++++++++++\n";
				
				priceout1:
				std::cout << "PRICE (RM): ";
				while (!(std::cin >> Price))
				{
					std::cout << "\n## PLEASE ENTER NUMBERS ONLY. TRY AGAIN!!! ##" << endl;
					std::cin.clear();
					std::cin.ignore(123, '\n');
					goto priceout1;
				}

				ps = connection->prepareStatement("UPDATE Fish SET Price = ? WHERE Fish_ID = ?");
				ps->setDouble(1, Price);
				ps->setString(2, Fish_ID);

				ps->executeUpdate();

				ps->close();

				viewfish();
				connection->close();

				goto detailout;
			}
			else if (details == "D")
			{
				string Fish_ID;

				Connection* connection = connector();
				viewfish();

			fishdeleteout:
				std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%     EXAMPLE TO ENTER Fish_ID : F0001       %%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "\nFISH_ID: ";
				std::cin >> Fish_ID;

				if (Fish_ID.size() != 5)
				{
					std::cout << "\n******************************************************************\n";
					std::cout << "**                                                              **\n";
					std::cout << "**       INVALID FISH_ID !!!,                                   **\n";
					std::cout << "**       PLEASE TRY AGAIN BY FOLLOWING THE EXAMPLE BELOW        **\n";
					std::cout << "**                                                              **\n";
					std::cout << "******************************************************************\n";
					goto fishdeleteout;
				}

				ps = connection->prepareStatement("DELETE FROM Fish WHERE FISH_ID = ?");

				ps->setString(1, Fish_ID);

				ps->executeQuery();

				ps->close();

				viewfish();
				connection->close();

				goto detailout;

			}
			else if (details == "E")
			{
				goto applicationout;
			}
			else
			{
				goto detailout;
			}
		}
		else if (application == "2")
		{
			std::string Date;
			double Total_Sale = 0, sale1;
			Connection* connection = connector();

		dateout:
			std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "%%                                            %%\n";
			std::cout << "%%     EXAMPLE TO ENTER DATE : 2022-01-01     %%\n";
			std::cout << "%%              [YYYY-MM-DD]                  %%\n";
			std::cout << "%%                                            %%\n";
			std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "INSERT DATE: ";
			std::cin >> Date;

			PreparedStatement* ps = connection->prepareStatement("SELECT * FROM OrderItem WHERE Order_Date = ?");

			ps->setString(1, Date);

			ResultSet* rs = ps->executeQuery();

			if (rs->next())
			{
				ps = connection->prepareStatement("SELECT OrderItem_ID, Customer_ID, Total_Sale FROM OrderItem WHERE Order_Date = ?");
				ps->setString(1, Date);

				rs = ps->executeQuery();

				std::cout << ".......................................................................";
				std::cout << "\n" << "OrderItem_ID";
				std::cout << "\t\t" << "Customer_ID";
				std::cout << "\t\t" << "Total_Sale" << endl;
				std::cout << ".......................................................................\n";


				while (rs->next())
				{

					std::cout << rs->getString("OrderItem_ID");
					std::cout << "\t\t\t" << rs->getString("Customer_ID");
					std::cout << "\t\t\t" << fixed << setprecision(2) << rs->getDouble("Total_Sale") << endl;

				}

				std::cout << ".......................................................................\n";


				ps = connection->prepareStatement("SELECT SUM(Total_Sale) as TOTALSALES FROM OrderItem WHERE Order_Date = ?");
				ps->setString(1, Date);

				rs = ps->executeQuery();
				if (rs->next())
				{
					sale1 = rs->getDouble("TOTALSALES");
				}

				cout << "##THE OVERALL SALES OF THE DAY IS RM " << sale1 << endl;

				goto applicationout;
			}
			else
			{
				std::cout << "\n******************************************************************\n";
				std::cout << "**                                                              **\n";
				std::cout << "**       PLEASE CHOOSE A VALID DATE!!!                          **\n";
				std::cout << "**                                                              **\n";
				std::cout << "******************************************************************\n";
				goto dateout;
			}

		}
		else if (application == "3")
		{
			Connection* connection = connector();

			PreparedStatement* ps = connection->prepareStatement("SELECT * FROM customer");

			ResultSet* rs = ps->executeQuery();

			std::cout << "\n.................................................................................";
			std::cout << "\n" << "Customer_ID";
			std::cout << "\t" << "Name";
			std::cout << "\t\t" << "Phone_Number";
			std::cout << "\t" << "Email" << endl;
			std::cout << ".................................................................................\n";

			while (rs->next())
			{

				std::cout << rs->getString("Customer_ID");
				std::cout << "\t\t" << rs->getString("Name");
				std::cout << "\t\t" << rs->getString("Phone_Number");
				std::cout << "\t" << rs->getString("Email") << endl;

			}

			std::cout << ".................................................................................\n";

			rs->close();
			ps->close();

			goto applicationout;
		}
		else if (application == "4")
		{
			std::string Admin_ID, Name, Password, Phone_Number, Email;

		registerout1:
			std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "%%                                            %%\n";
			std::cout << "%%     EXAMPLE TO CREATE ADMIN_ID : A0001     %%\n";
			std::cout << "%%                                            %%\n";
			std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "\nAdmin_ID: ";
			std::cin >> Admin_ID;

			if (Admin_ID.size() != 5)
			{
				std::cout << "\n******************************************************************\n";
				std::cout << "**                                                              **\n";
				std::cout << "**       INVALID ADMIN_ID !!!,                                  **\n";
				std::cout << "**       PLEASE TRY AGAIN BY FOLLOWING THE EXAMPLE BELOW        **\n";
				std::cout << "**                                                              **\n";
				std::cout << "******************************************************************\n";
				goto registerout1;
			}

			connection = connector();
			ps = connection->prepareStatement("SELECT * FROM Admin WHERE Admin_ID = ?");

			ps->setString(1, Admin_ID);

			rs = ps->executeQuery();

			if (rs->next())
			{
				std::cout << "\n******************************************************************\n";
				std::cout << "**                                                              **\n";
				std::cout << "**       THIS ADMIN_ID HAS TAKEN!!!,                            **\n";
				std::cout << "**       PLEASE CHOOSE OTHER ADMIN_ID                           **\n";
				std::cout << "**                                                              **\n";
				std::cout << "******************************************************************\n";
				goto registerout1;
			}
			else
			{

				std::cout << "NAME: ";
				std::cin.ignore();
				getline(std::cin, Name);
				std::cout << "PASSWORD: ";
				std::cin >> Password;
				std::cout << "PHONE_NUMBER: ";
				std::cin >> Phone_Number;
				std::cout << "EMAIL: ";
				std::cin >> Email;

				ps = connection->prepareStatement("INSERT INTO Admin (Admin_ID, Name, Password, Phone_Number, Email) VALUES (?,?,?,?,?)");

				ps->setString(1, Admin_ID);
				ps->setString(2, Name);
				ps->setString(3, Password);
				ps->setString(4, Phone_Number);
				ps->setString(5, Email);

				ps->executeQuery();

				std::system("cls");

				std::cout << "\n\t\t\t\t\t\t** YOUR REGISTRATION IS SUCCESSFUL. PLEASE LOGIN BACK! ** \n" << endl;
				goto mainsystemout;
			}
		}
		else if (application == "5")
		{
			std::string Password, Phone_Number, Email;

			Connection* connection = connector();
			viewadmin(Admin_ID);

			activityout:
			std::cout << "\n++++++++++++++++++++++++++++++++++\n";
			std::cout << "++                              ++\n";
			std::cout << "++   UPDATE ADMIN DETAILS       ++\n";
			std::cout << "++   A. PASSWORD                ++\n";
			std::cout << "++   B. PHONE_NUMBER            ++\n";
			std::cout << "++   C. EMAIL                   ++\n";
			std::cout << "++                              ++\n";
			std::cout << "++++++++++++++++++++++++++++++++++\n";
			std::cout << "\nOPTION: ";
			std::cin >> activity;

			if (activity == "A")
			{
				std::cout << "\nNEW PASSWORD: ";
				std::cin >> Password;

				connection = connector();
				ps = connection->prepareStatement("UPDATE Admin SET Password = ? WHERE Admin_ID = ?");
				ps->setString(1, Password);
				ps->setString(2, Admin_ID);

				ps->executeUpdate();

				ps->close();
				connection->close();
				std::system("cls");

				viewadmin(Admin_ID);

				goto applicationout;
			}

			if (activity == "B")
			{
				std::cout << "\nNEW PHONE_NUMBER: ";
				std::cin >> Phone_Number;

				ps = connection->prepareStatement("UPDATE Admin SET Phone_Number = ? WHERE Admin_ID = ?");
				ps->setString(1, Phone_Number);
				ps->setString(2, Admin_ID);

				ps->executeUpdate();

				ps->close();

				connection->close();
				std::system("cls");

				viewadmin(Admin_ID);

				goto applicationout;
			}
			else if (activity == "C")
			{
				std::cout << "\nNEW EMAIL: ";
				std::cin >> Email;

				ps = connection->prepareStatement("UPDATE Admin SET Email = ? WHERE Admin_ID = ?");
				ps->setString(1, Email);
				ps->setString(2, Admin_ID);

				ps->executeUpdate();

				ps->close();

				connection->close();
				std::system("cls");

				viewadmin(Admin_ID);

				goto applicationout;
			}
			else
			{
				goto activityout;
			}
		}
		else if (application == "6")
		{
			viewadmin(Admin_ID);

		enterout:
			std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "%%                                                     %%\n";
			std::cout << "%%     ARE YOU SURE WANT TO DELETE THIS ACCOUNT ?      %%\n";
			std::cout << "%%        Y for YES                                    %%\n";
			std::cout << "%%        N for NO                                     %%\n";
			std::cout << "%%                                                     %%\n";
			std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "\nENTER: ";
			std::cin >> enter;

			if (enter == "Y")
			{
				connection = connector();

				ps = connection->prepareStatement("DELETE FROM Admin WHERE Admin_ID = ?");
				ps->setString(1, Admin_ID);
				ps->executeQuery();

				ps->close();

				connection->close();

				std::system("cls");
				goto mainsystemout;
			}
			else if (enter == "N")
			{
				std::system("cls");
				goto applicationout;
			}
			else
			{
				goto enterout;
			}
		}
			else if (application == "7")
			{
				return 0;
			}
			else
			{
				goto applicationout;
			}
		
	}
		else if (mainsystem == "B")
		{
			std::string Customer_ID;

		loginout2:
			std::cout << "\nCUSTOMER_ID: ";
			std::cin >> Customer_ID;

			Connection* connection = connector();

			PreparedStatement* ps = connection->prepareStatement("SELECT * FROM CUSTOMER WHERE Customer_ID = ?");

			ps->setString(1, Customer_ID);

			ResultSet* rs = ps->executeQuery();

			if (rs->next())
			{
				std::cout << "\n** WELCOME TO THE PROGRAMME " << rs->getString("Name") << ". THANK YOU FOR BEING OUR CUSTOMER.**\n " << endl;
				goto appsout;
			}
			else
			{
				std::cout << "\n******************************************************************\n";
				std::cout << "**                                                              **\n";
				std::cout << "**       INVALID CUSTOMER_ID !!!,                               **\n";
				std::cout << "**       PLEASE RE-ENTER THE CUSTOMER_ID                        **\n";
				std::cout << "**                                                              **\n";
				std::cout << "******************************************************************\n";
				goto loginout2;
			}

			rs->close();
			ps->close();
			connection->close();

		appsout:
			std::cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
			std::cout << "@@                                     @@\n";
			std::cout << "@@       CUSTOMER APPLICATIONS:        @@\n";
			std::cout << "@@                                     @@\n";
			std::cout << "@@    1) VIEW FISH DETAILS             @@\n";
			std::cout << "@@    2) ORDER FISH                    @@\n";
			std::cout << "@@    3) UPDATE CUSTOMER DETAILS       @@\n";
			std::cout << "@@    4) DELETE CUSTOMER               @@\n";
			std::cout << "@@    5) EXIT                          @@\n";
			std::cout << "@@                                     @@\n";
			std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
			std::cout << "\nAPPLICATION: ";
			std::cin >> apps;
			std::cout << endl;

			if (apps == "1")
			{
				Connection* connection = connector();
				viewfish();
				connection->close();
				goto appsout;
			}
			else if (apps == "2")
			{
				std::string CustomerFish_ID, Decision, Dati;
				double Total, CustomerWeight, Ototal = 0;
				int OrderItem = 0;

				Dati = buydate();
			
				Connection* connection = connector();
			
				ps = connection->prepareStatement("INSERT INTO OrderItem VALUES (?,?,?,?)");
				ps->setInt(1, NULL);
				ps->setString(2, Customer_ID);
				ps->setString(3, Dati);
				ps->setDouble(4, 0);

				ps->executeQuery();

				ps->close();
			
				ps = connection->prepareStatement("SELECT LAST_INSERT_ID() ");
				rs = ps->executeQuery();
				
				if (rs->next())
					OrderItem = rs->getInt(1);

				rs->close();
				ps->close();

			customerfishout:

				viewfish();

				std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%   EXAMPLE TO ENTER ORDER Fish_ID : F0001   %%\n";
				std::cout << "%%                                            %%\n";
				std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "\nFISH_ID: ";
				std::cin >> CustomerFish_ID;

				if (CustomerFish_ID.size() != 5)
				{
					std::cout << "\n******************************************************************\n";
					std::cout << "**                                                              **\n";
					std::cout << "**       INVALID FISH_ID !!!,                                   **\n";
					std::cout << "**       PLEASE TRY AGAIN BY FOLLOWING THE EXAMPLE BELOW        **\n";
					std::cout << "**                                                              **\n";
					std::cout << "******************************************************************\n";

					goto customerfishout;
				}

				ps = connection->prepareStatement("SELECT Fish_ID, Price FROM Fish WHERE Fish_ID = ?");
				ps->setString(1, CustomerFish_ID);

				rs = ps->executeQuery();
				if (rs->next())
				{
					std::cout << "\nPRICE OF THE FISH PER KILOGRAM: RM ";
					std::cout << fixed << setprecision(2) << rs->getDouble("Price") << endl;
					double price1 = rs->getDouble("Price");

					std::cout << "\n******************************************************************\n";
					std::cout << "**                                                              **\n";
					std::cout << "**       ENTER THE WEIGHT OF THE FISH WANT TO BUY               **\n";
					std::cout << "**       (IN KILOGRAMS)                                         **\n";
					std::cout << "**                                                              **\n";
					std::cout << "******************************************************************\n";
					std::cout << "\nWEIGHT: ";

				CustomerWeightout:
					while (!(std::cin >> CustomerWeight))
					{
						std::cout << "\n## PLEASE ENTER NUMBERS ONLY. TRY AGAIN!!! ##" << endl;
						std::cin.clear();
						std::cin.ignore(123, '\n');
						goto CustomerWeightout;
					}

					if (CustomerWeight < 10)
					{
						Total = price1 * CustomerWeight;
						std::cout << "\nTHE TOTAL PRICE OF THE FISH IS RM " << Total;
					}
					else if ((CustomerWeight >= 10) && (CustomerWeight < 25))
					{
						Total = (price1 * CustomerWeight) * 0.95;
						std::cout << "\nTHE TOTAL PRICE OF THE FISH IS RM " << Total;
					}
					else if (CustomerWeight >= 25)
					{
						Total = (price1 * CustomerWeight) * 0.90;
						std::cout << "\nTHE TOTAL PRICE OF THE FISH IS RM " << Total;
					}

					Ototal += Total;

					ps = connection->prepareStatement("INSERT INTO Orderdetail VALUES (?,?,?,?,?)");
					ps->setInt(1, NULL);
					ps->setString(2, CustomerFish_ID);
					ps->setInt(3, OrderItem);
					ps->setDouble(4, CustomerWeight);
					ps->setDouble(5, Total);

					ResultSet* rs = ps->executeQuery();


				decisionout:
					std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
					std::cout << "%%                                            %%\n";
					std::cout << "%%     DO YOU WISH TO ADD MORE ?              %%\n";
					std::cout << "%%        1) YES                              %%\n";
					std::cout << "%%        2) NO                               %%\n";
					std::cout << "%%                                            %%\n";
					std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
					std::cout << "\nDECISION: ";
					std::cin >> decision;

					if (decision == "1")
					{
						goto customerfishout;
					}
					else if (decision == "2")
					{
						ps = connection->prepareStatement("UPDATE OrderItem SET Total_Sale = ? where OrderItem_ID = ?");
						ps->setDouble(1, Ototal);
						ps->setInt(2, OrderItem);

						ps->executeUpdate();
						ps->close();

						std::string OrderDetail_ID;
						Connection* connection = connector();

						PreparedStatement* ps = connection->prepareStatement("Select * From OrderDetail WHERE OrderItem_ID = ? ");
						ps->setInt(1, OrderItem);

						ResultSet* rs = ps->executeQuery();

						std::cout << "\n..................................................................................................";
						std::cout << "\n" << "Order Detail ID";
						std::cout << "\t\t" << "Fish_ID";
						std::cout << "\t\t" << "OrderItem ID";
						std::cout << "\t\t" << "Weight";
						std::cout << "\t\t" << "Price(RM)\n";
						std::cout << "..................................................................................................\n";

						while (rs->next())
						{

							std::cout << rs->getInt("OrderDetail_ID");
							std::cout << "\t\t\t" << rs->getString("Fish_ID");
							std::cout << "\t\t" << rs->getInt("OrderItem_ID");
							std::cout << "\t\t\t" << fixed << setprecision(2) << rs->getDouble("Weight");
							std::cout << "\t\t" << fixed << setprecision(2) << rs->getDouble("Total_Price") << endl;

						}

						std::cout << "\n..................................................................................................\n";
						std::cout << "## THE TOTAL PRICE IS: RM " << Ototal << endl;
						std::cout << "\n..................................................................................................\n";
					
						rs->close();
						ps->close();
					}

					else
					{
						goto decisionout;
					}
				}

			}
			else if (apps == "3")
			{
				std::string Phone_Number, Email;

				Connection* connection = connector();
				viewcustomer(Customer_ID);

				optionout:
				std::cout << "\n++++++++++++++++++++++++++++++++++\n";
				std::cout << "++                              ++\n";
				std::cout << "++   UPDATE CUSTOMER DETAILS    ++\n";
				std::cout << "++   A. PHONE_NUMBER            ++\n";
				std::cout << "++   B. EMAIL                   ++\n";
				std::cout << "++                              ++\n";
				std::cout << "++++++++++++++++++++++++++++++++++\n";
				std::cout << "\nOPTION: ";
				std::cin >> option;

				if (option == "A")
				{
					std::cout << "\nNEW PHONE_NUMBER: ";
					std::cin >> Phone_Number;

					ps = connection->prepareStatement("UPDATE Customer SET Phone_Number = ? WHERE Customer_ID = ?");
					ps->setString(1, Phone_Number);
					ps->setString(2, Customer_ID);

					ps->executeUpdate();

					ps->close();

					connection->close();
					std::system("cls");

					viewcustomer(Customer_ID);
					goto appsout;
				}
				else if (option == "B")
				{
					std::cout << "\nNEW EMAIL: ";
					std::cin >> Email;

					ps = connection->prepareStatement("UPDATE Customer SET Email = ? WHERE Customer_ID = ?");
					ps->setString(1, Email);
					ps->setString(2, Customer_ID);

					ps->executeUpdate();

					ps->close();

					connection->close();
					std::system("cls");

					viewcustomer(Customer_ID);
					goto appsout;
				}
				else
				{
					goto optionout;
				}
			}
			else if (apps == "4")
			{
				viewcustomer(Customer_ID);

			choiceout:
				std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "%%                                                     %%\n";
				std::cout << "%%     ARE YOU SURE WANT TO DELETE THIS ACCOUNT ?      %%\n";
				std::cout << "%%        Y for YES                                    %%\n";
				std::cout << "%%        N for NO                                     %%\n";
				std::cout << "%%                                                     %%\n";
				std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
				std::cout << "\nCHOICE: ";
				std::cin >> choice;

				if (choice == "Y")
				{
					Connection* connection = connector();

					PreparedStatement* ps = connection->prepareStatement("DELETE FROM Customer WHERE Customer_ID = ?");
					ps->setString(1, Customer_ID);

					ps->executeQuery();

					ps->close();
					connection->close();

					std::system("cls");
					goto mainsystemout;
				}
				else if (choice == "N")
				{
					std::system("cls");
					goto appsout;
				}
				else
				{
					goto choiceout;
				}

			}
			else if (apps == "5")
			{
				return 0;
			}
			else
			{
				goto appsout;
			}


		}
		else if (mainsystem == "C")
		{
			std::string Customer_ID, Name, Phone_Number, Email;

		registerout2:
			std::cout << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "%%                                            %%\n";
			std::cout << "%%   EXAMPLE TO CREATE CUSTOMER_ID : C0001    %%\n";
			std::cout << "%%                                            %%\n";
			std::cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
			std::cout << "\nCustomer_ID: ";
			std::cin >> Customer_ID;

			if (Customer_ID.size() != 5)
			{
				std::cout << "\n******************************************************************\n";
				std::cout << "**                                                              **\n";
				std::cout << "**       INVALID CUSTOMER_ID !!!,                               **\n";
				std::cout << "**       PLEASE TRY AGAIN BY FOLLOWING THE EXAMPLE BELOW        **\n";
				std::cout << "**                                                              **\n";
				std::cout << "******************************************************************\n";
				goto registerout2;
			}

			PreparedStatement* ps = connection->prepareStatement("SELECT * FROM Customer WHERE Customer_ID = ?");

			ps->setString(1, Customer_ID);

			ResultSet* rs = ps->executeQuery();

			if (rs->next())
			{
				std::cout << "\n******************************************************************\n";
				std::cout << "**                                                              **\n";
				std::cout << "**       THIS ADMIN_ID HAS TAKEN!!!,                            **\n";
				std::cout << "**       PLEASE CHOOSE OTHER CUSTOMER_ID                        **\n";
				std::cout << "**                                                              **\n";
				std::cout << "******************************************************************\n";
				goto registerout2;
			}

			std::cout << "NAME: ";
			std::cin.ignore();
			getline(std::cin, Name);
			std::cout << "PHONE_NUMBER: ";
			std::cin >> Phone_Number;
			std::cout << "EMAIL: ";
			std::cin >> Email;

			ps = connection->prepareStatement("INSERT INTO Customer (Customer_ID, Name, Phone_Number, Email) VALUES (?,?,?,?)");

			ps->setString(1, Customer_ID);
			ps->setString(2, Name);
			ps->setString(3, Phone_Number);
			ps->setString(4, Email);

			ps->executeQuery();

			std::system("cls");

			std::cout << "\n\t\t\t\t\t\t** YOUR REGISTRATION IS SUCCESSFUL. PLEASE LOGIN BACK! **\n" << endl;
			goto mainsystemout;

		}
		else
		{
			goto mainsystemout;
		}
	
}

//Call Functions

Connection* connector()
{
	Connection* connection;
	mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();
	connection = driver->connect("tcp://127.0.0.1:3306", "root", "");

	connection->setSchema("frms22");
	return connection;
}

void viewfish()
{
	Connection* connection = connector();
	
	PreparedStatement* ps = connection->prepareStatement("SELECT * FROM Fish");

	ResultSet* rs = ps->executeQuery();

	std::cout << "\n.......................................................................";
	std::cout << "\n" << "Fish_ID";
	std::cout << "\t\t" << "Name";
	std::cout << "\t\t" << "Price(RM)";
	std::cout << "\t" << "Lifespan" << endl;
	std::cout << ".......................................................................\n";

	while (rs->next())
	{

		std::cout << rs->getString("Fish_ID");
		std::cout << "\t\t" << rs->getString("Name");
		std::cout << "\t\t" << fixed << setprecision(2) << rs->getDouble("Price");
		std::cout << "\t\t" << rs->getString("Lifespan") << endl;

	}

	std::cout << ".......................................................................\n";
	rs->close();
	ps->close();
}

void viewcustomer(std::string Customer_ID)
{
	Connection* connection = connector();

	PreparedStatement* ps = connection->prepareStatement("SELECT * FROM Customer WHERE Customer_ID = ?");
	ps->setString(1, Customer_ID);

	ResultSet* rs = ps->executeQuery();

	std::cout << "\n.................................................................................";
	std::cout << "\n" << "Customer_ID";
	std::cout << "\t" << "Name";
	std::cout << "\t\t" << "Phone_Number";
	std::cout << "\t" << "Email" << endl;
	std::cout << ".................................................................................\n";

	if (rs->next())
	{

		std::cout << rs->getString("Customer_ID");
		std::cout << "\t\t" << rs->getString("Name");
		std::cout << "\t\t" << rs->getString("Phone_Number");
		std::cout << "\t" << rs->getString("Email") << endl;

	}

	std::cout << ".................................................................................\n";
	rs->close();
	ps->close();
}

void viewadmin(std::string Admin_ID)
{
	Connection* connection = connector();

	PreparedStatement* ps = connection->prepareStatement("SELECT * FROM Admin WHERE Admin_ID = ?");
	ps->setString(1, Admin_ID);

	ResultSet* rs = ps->executeQuery();

	std::cout << "\n..............................................................................................\n";
	std::cout << "\n" << "Admin_ID";
	std::cout << "\t" << "Name";
	std::cout << "\t\t" << "Password";
	std::cout << "\t" << "Phone_Number";
	std::cout << "\t" << "Email" << endl;
	std::cout << "..............................................................................................\n";

	if (rs->next())
	{

		std::cout << rs->getString("Admin_ID");
		std::cout << "\t\t" << rs->getString("Name");
		std::cout << "\t\t" << rs->getString("Password");
		std::cout << "\t\t" << rs->getString("Phone_Number");
		std::cout << "\t" << rs->getString("Email") << endl;

	}

	std::cout << "..............................................................................................\n";
	rs->close();
	ps->close();
}

std::string buydate()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	
	std::string dati = "20" + std::to_string(ltm->tm_year-100) + "-" + std::to_string(ltm->tm_mon + 1) + "-" + std::to_string(ltm->tm_mday);
	std::cout << "DATE : " << dati;
	return dati;
}
