#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;
class PageSet
{


private:
	string* page_id;
	string* page_name;
	int limit;
	int size;


 public:


PageSet() : limit(10), size(0)
{
	page_id = new string[limit];
	page_name = new string[limit];
}



    string GetPageName(const string& pageId) const 
{
	for (int i = 0; i < size; ++i)
	{
		if (page_id[i] == pageId) 
		{
			return page_name[i];
		}
	}
	return "Page not found";
}



void change()
{
	limit *= 2;
	string* newPageIds = new string[limit];
	string* newPageNames = new string[limit];
	for (size_t i = 0; i < size; ++i) 
	{
		newPageIds[i] = page_id[i];
		newPageNames[i] = page_name[i];
	}
	delete[] page_id;
	delete[] page_name;
	page_id = newPageIds;
	page_name = newPageNames;
}

void LoadData(const string& filename) 
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error in opening file: " << filename << endl;
		return;
	}

	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		string pageID, pageName;
		ss >> pageID;
		getline(ss, pageName);
		pageName = pageName.substr(pageName.find_first_not_of(' ')); 
		if (size == limit)
		{
			change();
		}
		page_id[size] = pageID;
		page_name[size] = pageName;
		++size;
	}

	file.close();
}


~PageSet() 
{
	delete[] page_id;
	delete[] page_name;
}




};





class User_
{

	
	
private:
	string** User;
	string* Friend;
	string* user_id;
	string* user_LikedPages;
	int numOfUser;
	int numOfField;
	string CurrentUser;

public:
User_()
{
	User = nullptr;
	Friend = nullptr;
	user_id = nullptr;
	user_LikedPages = nullptr;
	numOfUser = 0;
	numOfField = 0;
}

~User_()
{
	delete[]user_id;
	delete[]Friend;
	delete[]user_LikedPages;
	for (int i = 0; i < numOfUser; i++)
	{
		delete[] User[i];
	}
	delete[] User;

}


void LoadData(const string& Text)
{
	ifstream file("user.txt");
	if (!file.is_open())
	{
		cout << " Error in opening File \n";
	}
	string line;
	getline(file, line);
	stringstream header(line);
	numOfField = 0;
	string Field;
	while (header >> Field)
	{
		numOfField++;
	}
	numOfUser = 0;
	while (getline(file, line))
	{
		numOfUser++;
	}
	file.clear();
	file.seekg(0, ios::beg);
	user_id = new string[numOfUser];
	Friend = new string[numOfUser];
	user_LikedPages = new string[numOfUser];
	User = new string * [numOfUser];
	for (int i = 0; i < numOfUser; i++)
	{
		User[i] = new string[numOfField];
	}
	int userIndex = 0;
	while (getline(file, line))
	{
		stringstream ss(line);
		string userid;
		ss >> userid;
		if (userIndex < numOfUser)
		{
			user_id[userIndex] = userid;
			for (int i = 0; i < numOfField; i++)
			{
				ss >> User[userIndex][i];


			}
			userIndex++;
		}

	}
	file.close();
}


void SetCurrentUser(const string & a)
{
	bool found = false;
	for (int i = 0; i < numOfUser; i++)
	{
		if (user_id[i] == a)
		{
			CurrentUser = a;
			found = true;
			cout << " Current User : " << CurrentUser << "\n";
			cout << User[i][0] << User[i][1] << " is successfully set as current user "<<endl;
			break;

		}
	}
}

void ViewFriendsOfCurrentUser()
{
	for (int i = 0; i < numOfUser; i++) 
	{
		if (user_id[i] == CurrentUser) 
		{
			cout << "Friends of " << User[i][1] << " (" << CurrentUser << "):\n";
			for (int j = 2; j < numOfField; j++) 
			{
				string friend_id = User[i][j];
				for (int k = 0; k < numOfUser; k++) 
				{
					if (user_id[k] == friend_id)
					{
						cout << User[k][0] << User[k][1] <<" "<< friend_id <<endl;
						break;
					}
				}
			}
			return;
		}
	}
	cout << "Current user not set. Please set the current user first."<<endl;
}

void ViewLikedPagesOfCurrentUser(const PageSet& pages)
{
	bool currentUserFound = false;
	for (int i = 0; i < numOfUser; i++) 
	{
		if (user_id[i] == CurrentUser) 
		{
			currentUserFound = true;
			cout << User[i][1] << "  Liked Pages:" << endl;
			for (int j = 2; j < numOfField; j++) {
				if (User[i][j] != "-1") 
				{
					string pageId = User[i][j];
					string pageName = pages.GetPageName(pageId);
					if (pageName != "Page not found") 
					{
						cout << pageId << " " << pageName << endl;
					}
					
				}
			}
			break;
		}
	}
	if (!currentUserFound) 
	{
		cout << "Current user '" << CurrentUser << "' not found. Please set a valid current user." << endl;
	}
}


};






int main()
{
	User_ u1;
	PageSet p1;
	u1.LoadData("user.txt");
	u1.SetCurrentUser("u7");
	u1.ViewFriendsOfCurrentUser();
	p1.LoadData("Page.txt");
	u1.ViewLikedPagesOfCurrentUser(p1);

	
}