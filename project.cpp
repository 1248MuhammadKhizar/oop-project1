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

string GetUserName(const string& userId) const {
	for (int i = 0; i < numOfUser; ++i) {
		if (user_id[i] == userId) {
			return User[i][0] + " " + User[i][1];
		}
	}
	return "User not found";
}

bool IsUser(const string& a) const 
	{
		for (int i = 0; i < numOfUser; ++i) 
		{
			if (user_id[i] == a) 
			{
				return true; 
			}
		}
		return false; 
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

string get_current_user()
{
	return CurrentUser ;
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


class Post
{
	private:

	int num_of_posts;
	int * likes;
	string * id;
	string * owner;
	string * content;
	string * date;
	string like[12][12];

public:
Post()
{
	ReadData();
}



void ReadData() 
{
	ifstream file("Post.txt");
	if (!file.is_open()) {
		cerr << "Unable to open file." << endl;
		return;
	}
	file >> num_of_posts;
	likes = new int[num_of_posts];
	id = new string[num_of_posts];
	date = new string[num_of_posts];
	content = new string[num_of_posts];
	owner = new string[num_of_posts];
	for (int i = 0; i < num_of_posts; ++i)
	{
		file >> likes[i];
		file >> id[i];
		file >> date[i];
		file.ignore(); 
		getline(file, content[i]);
		getline(file, owner[i]);
		int j = 0;
		while (true) {
			file >> like[i][j];
			if (like[i][j] == "-1" || like[i][j].empty()) break;
			++j;
		}
	}
	file.close();

}

void like_post(User_ & a,string id1)
{
	for(int i=0;i<num_of_posts;i++)
	{
		string current_id=a.get_current_user();
		if(id[i]==id1)
		{
			bool liked=false;
			for (int j = 0; j < 10; ++j)
			{
				if (like[i][j] == current_id){
					liked = true;
					break;
				}
			}
			if (liked)
			{
				cout << "You have already liked this post." << endl;
			}
			else if (likes[i] < 10)
			{
				like[i][likes[i]] = current_id;
				++likes[i];
				cout << " liked the post." << endl;
			}
			else
			{
				cout << "Maximum number of likes reached for this post." << endl;
			}
			break;
		}
	}
	 
}


void view_people_liked(string & p_id,User_ & a,PageSet& pges)
{
bool found=false;
for(int i=0;i<num_of_posts;i++)
{
if(id[i]==p_id)
{

	found=true;
	cout<<"the post is  "<<id[i]<<endl;
	cout<<content[i]<<" "<<endl;
	cout<<"post owner is "<<owner[i]<<endl;
	cout<<"the post is liked by "<<endl;

    for(int j=0;like[i][j]!="-1";j++)
     {
           string likr=like[i][j];
            if (a.IsUser(likr))
				{
					cout << a.GetUserName(likr)<<" ";
				}
				else
				{
					cout << pges.GetPageName(likr)<<" "; 
				}
				cout<<endl;
				break;
   }
}
}



if(!found)
{
	cout<<"post not found  "<<endl;
}


}


};





int main(){
User_ u1;
	PageSet p1;
	Post p2;

	u1.LoadData("Text.txt");
	p1.LoadData("page.txt");
	string user;
	cout << " Enter ID : ";
	cin >> user;
	bool found = false;
	do
	{
		if (user == "u1" || user == "u2" || user == "u3" || user == "u4" || user == "u5" || user == "u6" || user == "u7" || user == "u8" || user == "u9" || user == "u10" || user == "u11" || user == "u12" || user == "u13" || user == "u14" || user == "u15" || user == "u16" || user == "u17" || user == "u18" || user == "u19" || user == "u20")
		{
			found = true;
			u1.SetCurrentUser(user);

		}
		else
		{
			
			cout << " No user Occur with ID :" << user << "\n";
			cout << " Enter ID : ";
			cin >> user;

		}


	} while (found==false);
	
	int opt;
	do
	{
		cout << "Menu:\n";
		cout << "1. View Friends of Current User :\n";
		cout << "2. View Liked People of a Post :\n";
		cout << "3. Like a Post :\n";
		cout << "4. Set User : \n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> opt;
		if (opt == 1)
		{
			u1.ViewFriendsOfCurrentUser();

		}
		else if (opt == 2)
		{
			string postId;
			cout << " Enter Post ID : ";
			cin >> postId;
			p2.view_people_liked(postId, u1, p1);

		}
		else if (opt == 3)
		{
			string postId;
			cout << " Enter Post ID : ";
			cin >> postId;
			p2.like_post(u1, postId);

		}
		else if (opt == 4)
		{
			string user;
			cout << " Enter ID : ";
			cin >> user;
			if (user == "u1" || user == "u2" || user == "u3" || user == "u4" || user == "u5" || user == "u6" || user == "u7" || user == "u8" || user == "u9" || user == "u10" || user == "u11" || user == "u12" || user == "u13" || user == "u14" || user == "u15" || user == "u16" || user == "u17" || user == "u18" || user == "u19" || user == "u20")
			{
				u1.SetCurrentUser(user);

			}

			else
			{
				cout << " No user Occur with ID :" << user << "\n";

			}
		}
		
	} while (opt!=0);

}