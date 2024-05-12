#include<iostream>
#include<sstream>
#include<string>
#include<windows.h>
#include<fstream>
using namespace std;

class Post;
class Page;
class User;

class Post
{
    private:
    int num_of_posts;
    int likes[12];
    string * post_id;
    string * date;
    string * owner;
    string * reaction;
    string like[12][12];

    public:
     Post();
    ~Post();
    void readdata_from_post();
    void Display_post_data();
    void view_liked_people(const string&, const User& , const Page&);
    void like_a_Post(User&, const string&);
    string* GetCreator() const
    { 
        return owner; 
    }
    string getreaction(int a) const
    {
        return reaction[a]; 
    }
    int GetTotalPost() const
    {
        return num_of_posts;
    }

    string get_date(int a)const
    {
        return date[a];
    }


};


class Page
{

private:
string * page_id;
string * page_name;
int limit;
int size;


public:
void change();
 Page();
    ~Page();
    void readdata_from_page(const string&);
    string get_page_name(const string&) const;
    bool Ispage(const string& ) const;
    void viewpage(const string&, const Post& ) const;

};



class User 
{

private:
    string** Users;
    string* id;
    int numOfUser;
    int column;
    string current_user;

public:
    User();
    ~User();
    void readdata_from_user(const string&);
    void setUser(const string&);
    void view_friends_Of_User() const;
    void view_liked_pages_of_user(const Page&) const;
    void view_homepage(const Post& p);

    string GetUserName(const string& ) const;
    string GetCurrent() const 
    {
        return current_user;
    }
    bool IsUser(const string& userId) const;

};

void User::view_homepage(const Post& p)
{
    
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == current_user)
        {
            
            cout << " User Name: " << Users[i][0]<<" "<< Users[i][1] << endl;
            break;
        }
    }
    string* creators = p.GetCreator();
    
    for (int j = 0; j<numOfUser; j++)
    {
        if (creators[j] == current_user)
        { 
            cout<< p.getreaction(j)<<endl;
            cout<<p.get_date(j)<<endl;
        }
    }
}




Post::Post() 
{
    readdata_from_post();
}

Post::~Post()
{
    delete[] post_id;
    delete[] date;
    delete[] reaction;
    delete[] owner;
}

void Post::readdata_from_post() 
{
    ifstream file("post.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    file >> num_of_posts;
    post_id = new string[num_of_posts];
    date = new string[num_of_posts];
    reaction = new string[num_of_posts];
    owner = new string[num_of_posts];
    for (int i = 0; i < num_of_posts; i++)
    {
        file >> likes[i];
        file >> post_id[i];
        file >> date[i];
        file.ignore();
        getline(file, reaction[i]);
        getline(file, owner[i]);
        int j = 0;
        while (true) {
            file >> like[i][j];
            if (like[i][j] == "-1" || like[i][j].empty()) break;
            j++;
        }
    }
    file.close();
}


void Post::view_liked_people(const string& postId, const User& users, const Page& pages)
{
    bool Found = false;
    for (int i = 0; i < num_of_posts; i++)
    {
        if (post_id[i] == postId) 
        {
            Found = true;
            cout << "Post ID  " << post_id[i] <<endl;
            cout << "Content  " << reaction[i] <<endl;
            cout << "Creator  " << owner[i] <<endl;
            cout << "Liked by "<<endl;

            int j = 0;
            while (like[i][j] != "-1") 
            {
                string liker = like[i][j];
                if (users.IsUser(liker))
                {
                    cout << users.GetUserName(liker);
                }
                else if (pages.Ispage(liker))
                {
                    cout << pages.get_page_name(liker);
                }
                if (like[i][j + 1] != "-1") 
                {
                    cout << ", ";
                }
                j++;
            }
            cout << endl;
            break;
        }
    }
    if (!Found) 
    {
        cout << "Post with ID " << postId << " not found." << endl;
    }
}


void Post::like_a_Post(User& users, const string& postId) {
    string currentUserId = users.GetCurrent();
    for (int i = 0; i < num_of_posts; i++)
    {
        if (post_id[i] == postId)
        {
            bool Liked = false;
            for (int j = 0; j < 10; j++)
            {
                if (like[i][j] == currentUserId)
                {
                    Liked = true;
                    break;
                }
            }
            if (Liked) {
                cout << " Liked already " << endl;
            }
            else if (likes[i] < 10) 
            {
                int k = likes[i];
                like[i][k] = currentUserId;
                like[i][k + 1] = "-1";
                ++likes[i];
                cout << " Liked the post successfully" << endl;
            }
            else
            {
                cout << "Maximum number of likes reached for this post." << endl;
            }
            break;
        }
    }
}

void Post::Display_post_data() {
    for (int i = 0; i < num_of_posts; i++) {
        cout << "Likes " << likes[i] << endl;
        cout << "Post ID " << post_id[i] << endl;
        cout << "Date " << date[i] << endl;
        cout << "Content " << reaction[i] << endl;
        cout << "Created By: " << owner[i] <<endl;
        cout << "Liked by ";
        for (int j = 0; like[i][j] != "-1"; j++) 
        {
            cout << like[i][j] << " ";
        }
        cout <<endl;
    }
}

                             //function of Page

 Page::Page() : limit(10), size(0)
{
    page_id = new string[limit];
    page_name = new string[limit];
}             

Page::~Page()
{
    delete[] page_id;
    delete[] page_name;
}

void Page::readdata_from_page(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cout << "Error file not opened " << filename << endl;
        return;
    }

    string a;
    while (getline(file, a)) 
    {
        stringstream ss(a);
        string temp_id, temp_name;
        ss >> temp_id;
        getline(ss, temp_name);
        
        if (size == limit)
        {
            change();
        }
        page_id[size] = temp_id;
        page_name[size] = temp_name;
        size++;
    }

    file.close();
}



bool Page::Ispage(const string& pg___id) const
{
    for (int i = 0; i < size; i++) 
    {
        if (page_id[i] == pg___id) 
        {
            return true;
        }
    }
    return false;
}

string Page::get_page_name(const string& pageId) const 
{
    for (int i = 0; i < size; i++)
    {
        if (page_id[i] == pageId) 
        {
            return page_name[i];
        }
    }
    return "false";
}


void Page::viewpage(const string& userId, const Post& p) const
{
    string* creators = p.GetCreator();
    for (int i = 0; i < p.GetTotalPost(); i++)
    {
        if (creators[i] == userId) 
        {
            cout << "Content " << p.getreaction(i) << endl;
        }
    }
}


 void Page::change() {
     limit *= 2;
     string* a = new string[limit];
     string* b = new string[limit];
     for (size_t i = 0; i < size; i++) {
         a[i] = page_id[i];
         b[i] = page_name[i];
     }

     delete[] a;
     delete[] b;
     page_id = a;
     page_name = b;
     size++;
 }



                 // declaration of user functions

  User::User() {
    Users = nullptr;
    id = nullptr;
    numOfUser = 0;
    column = 0;
}

User::~User() {
    delete[] id;
    for (int i = 0; i < numOfUser; i++) {
        delete[] Users[i];
    }
    delete[] Users;
}
          
void User::readdata_from_user(const string& Text) {
    ifstream file(Text);
    if (!file.is_open()) {
        cout << "Error in opening File \n";
    }
    string line;
    getline(file, line);
    stringstream header(line);
    column = 0;
    string a;
    while (header >> a) {
        column++;
    }

    numOfUser = 0;
    while (getline(file, line))
    {
        numOfUser++;
    }
    file.clear();
    file.seekg(0, ios::beg);
    id = new string[numOfUser];
    Users = new string * [numOfUser];
    for (int i = 0; i < numOfUser; i++) 
    {
        Users[i] = new string[column];
    }
    int Index = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string user_idss;
        ss >> user_idss;
        if (Index < numOfUser)
        {
            id[Index] = user_idss;
            for (int i = 0; i < column; i++) 
            {
                ss >> Users[Index][i];
            }
            Index++;
        }
    }
    file.close();
}

string User::GetUserName(const string& userId) const
{
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == userId) 
        {
            return Users[i][0] + " " + Users[i][1];
        }
    }
    return "User not found";
}

void User::setUser(const string& a)
{
    bool user_found = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == a) {
            current_user = a;
            user_found = true;
            cout << "Current User: " << current_user <<endl;
            cout << Users[i][0] << " " << Users[i][1] << " is set as current user"<<endl;
            break;
        }
    }
    if (!user_found)
    {
        cout << "User not found  " << a << endl;
    }
}

bool User::IsUser(const string& Id) const
{
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == Id)
        {
            return true;
        }
    }
    return false;
}

void User::view_liked_pages_of_user(const Page& pages) const 
{
    bool currentUserFound = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == current_user) 
        {
            currentUserFound = true;
            cout << Users[i][0] << " " << Users[i][1] << " " <<" liked pages "<< endl;
            for (int j = 2; j < column; j++)
            {
                string likedPageId = Users[i][j];
                if (pages.Ispage(likedPageId))
                {
                    string pageName = pages.get_page_name(likedPageId);
                    
                        cout << likedPageId << " " << pageName << endl;
                
                }
            }
            break;
        }
    }
    if (!currentUserFound) 
    {
        cout << "Current user " << current_user << " not found. Please set a valid current user." << endl;
    }
}


void User::view_friends_Of_User() const
{
    bool found = false;
    for (int i = 0; i < numOfUser; i++)
    {
        if (id[i] == current_user)
        {
            found = true;
            cout << "Friends of " << Users[i][0] << " " << Users[i][1] <<" "<< current_user <<endl;
            for (int j = 2; j < column; j++)
            {
                string friend_id = Users[i][j];
                for (int k = 0; k < numOfUser; k++) 
                {
                    if (id[k] == friend_id) {
                        cout << Users[k][0] << " " << Users[k][1] << " "<< friend_id <<endl;
                        break;
                    }
                }
            }
            return;
        }
    }
    if (!found) {
        cout << "user not set"<<endl;
    }
}

void run_application()
{
    User user1;
    Page page1;
    Post post1;

    user1.readdata_from_user("user.txt");
    page1.readdata_from_page("page.txt");
    
    string user;
    cout << "Enter User ID: ";
    cin >> user;
    bool found = false;
    do 
    {
        if (user1.IsUser(user)) 
        {
            found = true;
            user1.setUser(user);
        }
        else
        {
            cout << "User not found. Enter User ID: ";
            cin >> user;
        }
    } while (!found);

    int opt;
    do 
    {
        cout << "Menu:\n"
            << "1. View Friends of Current User\n"
            << "2. View Liked People of a Post\n"
            << "3. Like a Post\n"
            << "4. Set User\n"
            << "5. View Liked Pages\n"
            << "6.View Page\n"
            << "7.See Home Page\n"
            << "0. Exit\n"
            << "Enter your choice: ";
        cin >> opt;
        switch (opt) {
        case 1:
            user1.view_friends_Of_User();
            break;
        case 2: {
            string postId;
            cout << "Enter Post ID: ";
            cin >> postId;
            post1.view_liked_people(postId, user1, page1);
            break;
        }
        case 3: {
            string postId;
            cout << "Enter Post ID: ";
            cin >> postId;
            post1.like_a_Post(user1, postId);
            break;
        }
        case 4: {
            cout << "Enter User ID: ";
            cin >> user;
            if (user1.IsUser(user)) 
            {
                user1.setUser(user);
            }
            else
            {
                cout << "User not found.\n";
            }
            break;
        }
        case 5: 
        {
            user1.view_liked_pages_of_user(page1);
            break;
        }
        case 6:
        {
            string Page;
            cout<<"Enter Page : ";
            cin >> Page;
            page1.viewpage(Page, post1);

        }
        case 7:
        {
            user1.view_homepage(post1);
        }
        
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option! Please try again.\n";
        }
    } while (opt != 0);       

    }

int main()
{
    run_application();
}
           
           





